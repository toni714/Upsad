#include "FileUtil.h"

std::string FileUtil::loadFile(const char * const filename)
{
	std::ifstream ifs(filename);
	return std::string{ std::istreambuf_iterator<char>(ifs),std::istreambuf_iterator<char>() };
}

BMPData FileUtil::getBMPData(const char * const filename)
{
std::ifstream file(filename, std::ios::binary);
	if (!file)
	{
		throw std::runtime_error("Failure to open bitmap file.");
	}

	uint8_t* datBuff[2] = {
		new uint8_t[sizeof(BITMAPFILEHEADER)],
		new uint8_t[sizeof(BITMAPINFOHEADER)]
	};

	BITMAPFILEHEADER bmpHeader;
	BITMAPINFOHEADER bmpInfo;

	file.read((char*)&bmpHeader, sizeof(BITMAPFILEHEADER));
	file.read((char*)&bmpInfo, sizeof(BITMAPINFOHEADER));

	const WORD bmpCode = 0x4D42;
	if (bmpHeader.bfType != bmpCode)
	{
		throw std::runtime_error("File \"" + std::string(filename) + "\" isn't a bitmap file\n");
	}

	unsigned long imageSize = bmpInfo.biSizeImage;
	GLuint width = bmpInfo.biWidth;
	GLuint height = bmpInfo.biHeight;

	uint8_t* pixelData = new uint8_t[imageSize];

	file.seekg(bmpHeader.bfOffBits);
	file.read((char*)pixelData, imageSize);

	uint8_t tmpRGB = 0; // Swap buffer
	for (unsigned long i = 0; i < imageSize; i += 3)
	{
		tmpRGB = pixelData[i];
		pixelData[i] = pixelData[i + 2];
		pixelData[i + 2] = tmpRGB;
	}

	delete[] datBuff[0];
	delete[] datBuff[1];
	//delete[] pixels;

	return BMPData{
		width,
		height,
		pixelData
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