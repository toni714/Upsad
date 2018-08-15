#include "FileUtil.h"

#include "OBJWrapper.h"

RawModel * FileUtil::getModelFromFile(const char * filename)
{
	const auto& modelPosition = models.find(filename);
	if (modelPosition != models.end()) {
		return modelPosition->second;
	}
	else {
		GLuint vaoID = createVAO();
		ModelData modelData = FileUtil::getModelData(filename);

		loadToVAO(vaoID, modelData);

		//TODO maybe make vertex count an size_t
		RawModel* model = new RawModel(vaoID, modelData.indices.size());
		models.insert(std::make_pair(filename, model));

		return model;
	}
}



std::ifstream FileUtil::openFile(const char * filename)
{
	std::ifstream file = std::ifstream(filename, std::ios::in | std::ios::binary);
	if (!file) {
		throw std::runtime_error(std::string("File could not be opened: ")+filename);
	}
	return file;
}

uint8_t * FileUtil::readPixelDataFromBitmap(std::ifstream& file, const DWORD & dataOffset, const DWORD & imageSize)
{
	uint8_t* pixelData = new uint8_t[imageSize];
	file.seekg(dataOffset);
	file.read((char*)pixelData, imageSize);
	return pixelData;
}

bool FileUtil::hasValidBitmapSignature(std::ifstream & file)
{
	return readValueFromFile<WORD>(file, offsetof(BITMAPFILEHEADER, bfType))==BITMAP_SIGNATURE;
}

std::string FileUtil::loadFile(const char * const filename)
{
	std::ifstream ifs(filename);
	return std::string{ std::istreambuf_iterator<char>(ifs),std::istreambuf_iterator<char>() };
}

BMPData FileUtil::getBMPData(const char * const filename)
{
	std::ifstream file = openFile(filename);

	if (!hasValidBitmapSignature(file)) {
		throw std::runtime_error(std::string("Given File is not in BMP-Format: ") + filename);
	}

	//These are in order of appearance in the bitmap header (maybe this is faster?)
	auto pixelDataOffset=readValueFromFile<DWORD>(file, offsetof(BITMAPFILEHEADER, bfOffBits));
	auto width=readValueFromFile<LONG>(file, sizeof(BITMAPFILEHEADER) + offsetof(BITMAPINFOHEADER, biWidth));
	auto height=readValueFromFile<LONG>(file, sizeof(BITMAPFILEHEADER) + offsetof(BITMAPINFOHEADER, biHeight));
	auto imageSize=readValueFromFile<DWORD>(file, sizeof(BITMAPFILEHEADER) + offsetof(BITMAPINFOHEADER, biSizeImage));

	uint8_t* pixelData=readPixelDataFromBitmap(file, pixelDataOffset, imageSize);
	
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

ModelData FileUtil::getModelData(const char * filename)
{
	OBJWrapper ow = OBJWrapper(filename);

	auto m_vertices = ow.getVertices();

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
		ow.getIndices()
	};
}







ImageTexture * FileUtil::getTextureFromFile(const char * filename)
{
	const auto& texturePosition = textures.find(filename);
	if (texturePosition != textures.end()) {
		return texturePosition->second;
	}
	else {
		GLuint textureID = createTexture();

		loadTextureData(textureID, FileUtil::getBMPData(filename));

		ImageTexture* texture = new ImageTexture(textureID);
		textures.insert(std::make_pair(filename, texture));

		return texture;
	}
}

void FileUtil::loadTextureData(const GLuint& textureID, const BMPData& textureData) {
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, textureData.colorFormat, GL_UNSIGNED_BYTE, textureData.pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint FileUtil::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	return vaoID;
}

GLuint FileUtil::createVBO(const GLenum& target)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(target, vboID);
	vbos.push_back(vboID);
	return vboID;
}

GLuint FileUtil::createTexture()
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	return textureID;
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

void FileUtil::loadToVAO(const GLuint& vaoID, const ModelData& modelData) {
	glBindVertexArray(vaoID);
	bufferData(modelData.vertices, 0, 3, GL_FLOAT);
	bufferData(modelData.uvs, 1, 2, GL_FLOAT);
	bufferData(modelData.normals, 2, 3, GL_FLOAT);

	createVBO(GL_ELEMENT_ARRAY_BUFFER);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelData.indices.size() * sizeof(GLuint), modelData.indices.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);			//Is this good practice?
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	//Is this good Practice?

	glBindVertexArray(0);	//Unbind VAO (Safety)
}

void FileUtil::cleanup()
{
	for (const auto &textureID : textures) {
		delete textureID.second;
	}
	textures.clear();

	glDeleteBuffers((GLsizei)vbos.size(), vbos.data());

	for (const auto &model : models) {
		delete model.second;
	}
	models.clear();

	//This crashes....
	/*for (auto it = textureData.begin(); it != textureData.end(); it++) {
	delete[] * it;
	}*/
}

std::unordered_map<std::string, RawModel*> FileUtil::models;
std::vector<GLuint> FileUtil::vbos;
std::unordered_map<std::string, ImageTexture*> FileUtil::textures;
std::vector<uint8_t*> FileUtil::textureData;