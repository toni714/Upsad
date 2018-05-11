#include "FileUtil.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

std::string FileUtil::loadFile(const char * const filename)
{
	std::ifstream ifs(filename);
	std::string content{ std::istreambuf_iterator<char>(ifs),std::istreambuf_iterator<char>() };
	return content;
}

GLuint FileUtil::load_BMP(const char * const filename)
{
	uint8_t* datBuff[2] = { nullptr, nullptr }; // Header buffers

	uint8_t* pixels = nullptr; // Pixels

	BITMAPFILEHEADER* bmpHeader = nullptr; // Header
	BITMAPINFOHEADER* bmpInfo = nullptr; // Info

										 // The file... We open it with it's constructor
	std::ifstream file(filename, std::ios::binary);
	if (!file)
	{
		throw std::runtime_error("Failure to open bitmap file.");
	}

	// Allocate byte memory that will hold the two headers
	datBuff[0] = new uint8_t[sizeof(BITMAPFILEHEADER)];
	datBuff[1] = new uint8_t[sizeof(BITMAPINFOHEADER)];

	file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
	file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

	// Construct the values from the buffers
	bmpHeader = (BITMAPFILEHEADER*)datBuff[0];
	bmpInfo = (BITMAPINFOHEADER*)datBuff[1];

	// Check if the file is an actual BMP file
	if (bmpHeader->bfType != 0x4D42)
	{
		throw std::runtime_error("File \"" + std::string(filename) + "\" isn't a bitmap file\n");
	}

	// First allocate pixel memory
	pixels = new uint8_t[bmpInfo->biSizeImage];

	// Go to where image data starts, then read in image data
	file.seekg(bmpHeader->bfOffBits);
	file.read((char*)pixels, bmpInfo->biSizeImage);

	// We're almost done. We have our image loaded, however it's not in the right format.
	// .bmp files store image data in the BGR format, and we have to convert it to RGB.
	// Since we have the value in bytes, this shouldn't be to hard to accomplish
	uint8_t tmpRGB = 0; // Swap buffer
	for (unsigned long i = 0; i < bmpInfo->biSizeImage; i += 3)
	{
		tmpRGB = pixels[i];
		pixels[i] = pixels[i + 2];
		pixels[i + 2] = tmpRGB;
	}

	// Set width and height to the values loaded from the file
	GLuint w = bmpInfo->biWidth;
	GLuint h = bmpInfo->biHeight;

	GLuint textureID = Utility::modelHelper->loadTexture(w, h, pixels);
	// Delete the two buffers.
	delete[] datBuff[0];
	delete[] datBuff[1];
	//delete[] pixels;

	return textureID;
}

RawModel * FileUtil::loadOBJ(const char * filename)
{
	tinyobj::attrib_t vertexAttributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string errorString;

	bool success = tinyobj::LoadObj(&vertexAttributes, &shapes, &materials, &errorString, filename);
	if (!success) {
		throw std::runtime_error(errorString);
	}

	std::vector<Vertex> m_vertices = std::vector<Vertex>();
	std::vector<unsigned int> m_indices = std::vector<unsigned int>();

	std::unordered_map<Vertex, uint32_t> vertices;

	for (tinyobj::shape_t shape : shapes) {
		for (tinyobj::index_t index : shape.mesh.indices) {
			glm::vec3 pos = {
				vertexAttributes.vertices[3 * index.vertex_index + 0],
				vertexAttributes.vertices[3 * index.vertex_index + 1],
				vertexAttributes.vertices[3 * index.vertex_index + 2]
			};

			glm::vec3 normal = {
				vertexAttributes.normals[3 * index.normal_index + 0],
				vertexAttributes.normals[3 * index.normal_index + 1],
				vertexAttributes.normals[3 * index.normal_index + 2]
			};

			glm::vec2 uv = {//Are they flipped?
				vertexAttributes.texcoords[2 * index.texcoord_index + 0],
				vertexAttributes.texcoords[2 * index.texcoord_index + 1]
			};

			Vertex vert(pos, normal, uv);

			if (vertices.count(vert) == 0) {
				vertices[vert] = vertices.size();
				m_vertices.push_back(vert);
			}
			m_indices.push_back(vertices[vert]);
		}
	}

	std::vector<float> u_vertices = std::vector<float>();
	std::vector<float> u_uvs = std::vector<float>();
	std::vector<float> u_normals = std::vector<float>();
	for (auto it = m_vertices.begin(); it != m_vertices.end(); it++) {
		u_vertices.push_back(it->pos.x);
		u_vertices.push_back(it->pos.y);
		u_vertices.push_back(it->pos.z);
		u_uvs.push_back(it->uvCoord.x);
		u_uvs.push_back(it->uvCoord.y);
		u_normals.push_back(it->normal.x);
		u_normals.push_back(it->normal.y);
		u_normals.push_back(it->normal.z);
	}
	//normals are missing here
	return Utility::modelHelper->loadToVAO(u_vertices, u_uvs, m_indices);
}