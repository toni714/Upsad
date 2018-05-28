#include "FileUtil.h"

std::string FileUtil::loadFile(const char * const filename)
{
	std::ifstream ifs(filename);
	std::string content{ std::istreambuf_iterator<char>(ifs),std::istreambuf_iterator<char>() };
	return content;
}

BMPData FileUtil::getBMPData(const char * const filename)
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

	// Delete the two buffers.
	delete[] datBuff[0];
	delete[] datBuff[1];
	//delete[] pixels;

	return BMPData{
		w,
		h,
		pixels
	};
}

ModelData FileUtil::getModelData(const char * filename)
{
	OBJWrapper ow = OBJWrapper(filename);

	auto m_vertices = ow.getVertices();
	auto m_indices = ow.getIndices();

	std::vector<float> u_vertices = std::vector<float>();
	std::vector<float> u_uvs = std::vector<float>();
	std::vector<float> u_normals = std::vector<float>();
	for (const auto& it : m_vertices) {
		u_vertices.push_back(it.pos.x);
		u_vertices.push_back(it.pos.y);
		u_vertices.push_back(it.pos.z);
		u_uvs.push_back(it.uvCoord.x);
		u_uvs.push_back(it.uvCoord.y);
		u_normals.push_back(it.normal.x);
		u_normals.push_back(it.normal.y);
		u_normals.push_back(it.normal.z);
	}

	return  ModelData{
		u_vertices,
		u_uvs,
		u_normals,
		m_indices
	};
}