#include "FileUtil.h"

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