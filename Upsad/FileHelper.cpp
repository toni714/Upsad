#include "FileHelper.h"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "StringUtil.h"
#include "OpenGLHelper.h"
#include "ModelHelper.h"

ModelData FileHelper::getModelDataFromFile(const std::string& filename) {
	std::vector<GLuint> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::vector<std::vector<std::vector<GLuint>>> temp_faces;

	std::string fileContent = FileHelper::loadFileToString(filename);
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

std::shared_ptr<ImageTexture> FileHelper::getTextureFromFile(const char * filename)
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

GLuint FileHelper::createTexture()
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	return textureID;
}

BMPData FileHelper::getBMPData(const char * const filename)
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

bool FileHelper::hasValidBitmapSignature(std::ifstream & file)
{
	return readValueFromFile<WORD>(file, offsetof(BITMAPFILEHEADER, bfType)) == BITMAP_SIGNATURE;
}

uint8_t * FileHelper::readPixelDataFromBitmap(std::ifstream& file, const DWORD & dataOffset, const DWORD & imageSize)
{
	uint8_t* pixelData = new uint8_t[imageSize];
	file.seekg(dataOffset);
	file.read((char*)pixelData, imageSize);
	return pixelData;
}

void FileHelper::loadTextureData(GLuint textureID, const BMPData& textureData) {
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, textureData.colorFormat, GL_UNSIGNED_BYTE, textureData.pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::ifstream FileHelper::openFile(const char * filename)
{
	std::ifstream file = std::ifstream(filename, std::ios::in | std::ios::binary);
	if (!file) {
		throw std::runtime_error(std::string("File could not be opened: ") + filename);
	}
	return file;
}

std::string FileHelper::loadFileToString(const std::string& filename)
{
	std::ifstream ifs(filename);
	return std::string{ std::istreambuf_iterator<char>(ifs),std::istreambuf_iterator<char>() };
}

void FileHelper::cleanup()
{
	textures.clear();

	//This crashes....
	/*for (auto it = textureData.begin(); it != textureData.end(); it++) {
	delete[] * it;
	}*/
}

std::unordered_map<std::string, std::shared_ptr<ImageTexture>> FileHelper::textures;
std::vector<uint8_t*> FileHelper::textureData;