#include "FileUtil.h"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "StringUtil.h"

ModelData FileUtil::getModelData(const char* filename) {
	std::vector<GLuint> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::vector<std::vector<std::vector<GLuint>>> temp_faces;

	std::string fileContent = FileUtil::loadFileToString(filename);
	std::vector<std::string> lines = StringUtil::splitString(fileContent.c_str(), "\n");

	for (const auto& line : lines) {
		std::vector<std::string> pieces = StringUtil::splitString(line, " ");
		if (pieces[0] == "v") {
			temp_vertices.push_back(glm::vec3(std::stod(pieces[1]), std::stod(pieces[2]), std::stod(pieces[3])));
		}
		else if (pieces[0] == "vt") {
			temp_uvs.push_back(glm::vec2(std::stod(pieces[1]), std::stod(pieces[2])));
		}
		else if (pieces[0] == "vn") {
			temp_normals.push_back(glm::vec3(std::stod(pieces[1]), std::stod(pieces[2]), std::stod(pieces[3])));
		}
		else if (pieces[0] == "f") {
			std::vector<std::string> v1_raw = StringUtil::splitString(pieces[1], "/");
			std::vector<GLuint> v1 = std::vector<GLuint>();
			std::vector<std::string> v2_raw = StringUtil::splitString(pieces[2], "/");
			std::vector<std::string> v3_raw = StringUtil::splitString(pieces[3], "/");
			std::vector<std::vector<GLuint>> triangle = {
				{ static_cast<GLuint>(std::stoi(v1_raw[0]) - 1), static_cast<GLuint>(std::stoi(v1_raw[1]) - 1), static_cast<GLuint>(std::stoi(v1_raw[2]) - 1) },
				{ static_cast<GLuint>(std::stoi(v2_raw[0]) - 1), static_cast<GLuint>(std::stoi(v2_raw[1]) - 1) , static_cast<GLuint>(std::stoi(v2_raw[2]) - 1) },
				{ static_cast<GLuint>(std::stoi(v3_raw[0]) - 1),static_cast<GLuint>(std::stoi(v3_raw[1]) - 1) , static_cast<GLuint>(std::stoi(v3_raw[2]) - 1) } };
			temp_faces.push_back(triangle);
		}
	}

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	for (const auto& face : temp_faces) {
		for (int v = 0; v < 3; v++) {
			GLuint vertexIndex = face[v][0];
			GLuint uvIndex = face[v][1];
			GLuint normalIndex = face[v][2];
			Vertex vertex = Vertex(temp_vertices[vertexIndex], temp_uvs[uvIndex], temp_normals[normalIndex]);
			bool found = false;
			for (int i = 0; i < vertices.size(); i++) {
				if (vertices[i] == vertex) {
					indices.push_back(i);
					found = true;
					break;
				}
			}
			if (!found) {
				indices.push_back(static_cast<GLuint>(vertices.size()));
				vertices.push_back(vertex);
			}
		}
	}
	return ModelData(vertices, indices);
}

std::shared_ptr<RawModel> FileUtil::getModelFromFile(const char* filename)
{
	const auto& modelPosition = models.find(filename);
	if (modelPosition != models.end()) {
		return modelPosition->second;
	}
	else {
		GLuint vaoID = createVAO();
		ModelData modelData = getModelData(filename);

		loadModelToVAO(vaoID, modelData);

		//TODO maybe make vertex count an size_t
		std::shared_ptr<RawModel> model = std::make_shared<RawModel>(vaoID, modelData.indices.size());
		models.insert(std::make_pair(filename, model));

		return model;
	}
}

GLuint FileUtil::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	return vaoID;
}

void FileUtil::loadModelToVAO(const GLuint& vaoID, const ModelData& modelData) {
	std::vector<GLfloat> positions;
	std::vector<GLfloat> uv_coordinates;
	std::vector<GLfloat> normals;
	for (const auto& vertex : modelData.vertices) {
		positions.push_back(vertex.position.x);
		positions.push_back(vertex.position.y);
		positions.push_back(vertex.position.z);
		uv_coordinates.push_back(vertex.uv_coordinates.x);
		uv_coordinates.push_back(vertex.uv_coordinates.y);
		normals.push_back(vertex.normal.x);
		normals.push_back(vertex.normal.y);
		normals.push_back(vertex.normal.z);
	}
	//__debugbreak();
	glBindVertexArray(vaoID);
	bufferData(positions, 0, 3, GL_FLOAT);
	bufferData(uv_coordinates, 1, 2, GL_FLOAT);
	bufferData(normals, 2, 3, GL_FLOAT);

	GLuint vboID = createVBO(GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelData.indices.size() * sizeof(GLuint), modelData.indices.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);			//Is this good practice?
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	//Is this good Practice?

	glBindVertexArray(0);	//Unbind VAO (Safety)
}

template<typename T>
void FileUtil::bufferData(std::vector<T> data, const int& attribute, const int& dimensions, const GLenum& type)
{
	GLuint bufferID = createVBO(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, dimensions, type, GL_FALSE, 0, nullptr);
	glDisableVertexAttribArray(attribute);
}

GLuint FileUtil::createVBO(const GLenum& target)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	return vboID;
}

std::shared_ptr<ImageTexture> FileUtil::getTextureFromFile(const char * filename)
{
	const auto& texturePosition = textures.find(filename);
	if (texturePosition != textures.end()) {
		return texturePosition->second;
	}
	else {
		GLuint textureID = createTexture();

		loadTextureData(textureID, getBMPData(filename));

		std::shared_ptr<ImageTexture> texture = std::make_shared<ImageTexture>(textureID);
		textures.insert(std::make_pair(filename, texture));

		return texture;
	}
}

GLuint FileUtil::createTexture()
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	return textureID;
}

BMPData FileUtil::getBMPData(const char * const filename)
{
	std::ifstream file = openFile(filename);

	if (!hasValidBitmapSignature(file)) {
		throw std::runtime_error(std::string("Given File is not in BMP-Format: ") + filename);
	}

	//These are in order of appearance in the bitmap header (maybe this is faster?)
	auto pixelDataOffset = readValueFromFile<DWORD>(file, offsetof(BITMAPFILEHEADER, bfOffBits));
	auto width = readValueFromFile<LONG>(file, sizeof(BITMAPFILEHEADER) + offsetof(BITMAPINFOHEADER, biWidth));
	auto height = readValueFromFile<LONG>(file, sizeof(BITMAPFILEHEADER) + offsetof(BITMAPINFOHEADER, biHeight));
	auto imageSize = readValueFromFile<DWORD>(file, sizeof(BITMAPFILEHEADER) + offsetof(BITMAPINFOHEADER, biSizeImage));

	uint8_t* pixelData = readPixelDataFromBitmap(file, pixelDataOffset, imageSize);

	if (COLOR_LOADING_FORMAT == GL_RGB) {
		//TODO extraxct this into a Function (swap R and B values)
		uint8_t swapBuffer = 0;
		for (unsigned long curentPixel = 0; curentPixel < imageSize; curentPixel += 3)
		{
			swapBuffer = pixelData[curentPixel];
			pixelData[curentPixel] = pixelData[curentPixel + 2];
			pixelData[curentPixel + 2] = swapBuffer;
		}
	}

	//TODO delete[] pixelData;

	return BMPData{
		(GLuint)width,
		(GLuint)height,
		COLOR_LOADING_FORMAT,
		pixelData
	};
}

bool FileUtil::hasValidBitmapSignature(std::ifstream & file)
{
	return readValueFromFile<WORD>(file, offsetof(BITMAPFILEHEADER, bfType)) == BITMAP_SIGNATURE;
}

uint8_t * FileUtil::readPixelDataFromBitmap(std::ifstream& file, const DWORD & dataOffset, const DWORD & imageSize)
{
	uint8_t* pixelData = new uint8_t[imageSize];
	file.seekg(dataOffset);
	file.read((char*)pixelData, imageSize);
	return pixelData;
}

void FileUtil::loadTextureData(const GLuint& textureID, const BMPData& textureData) {
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, textureData.colorFormat, GL_UNSIGNED_BYTE, textureData.pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::ifstream FileUtil::openFile(const char * filename)
{
	std::ifstream file = std::ifstream(filename, std::ios::in | std::ios::binary);
	if (!file) {
		throw std::runtime_error(std::string("File could not be opened: ") + filename);
	}
	return file;
}

std::string FileUtil::loadFileToString(const char * const filename)
{
	std::ifstream ifs(filename);
	return std::string{ std::istreambuf_iterator<char>(ifs),std::istreambuf_iterator<char>() };
}

void FileUtil::cleanup()
{
	textures.clear();

	glDeleteBuffers((GLsizei)vbos.size(), vbos.data());

	models.clear();

	//This crashes....
	/*for (auto it = textureData.begin(); it != textureData.end(); it++) {
	delete[] * it;
	}*/
}

std::unordered_map<std::string, std::shared_ptr<RawModel>> FileUtil::models;
std::vector<GLuint> FileUtil::vbos;
std::unordered_map<std::string, std::shared_ptr<ImageTexture>> FileUtil::textures;
std::vector<uint8_t*> FileUtil::textureData;