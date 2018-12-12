#include "CompressedMapLoader.h"

//Function Derived from MiniZ  
static int tinfl_put_buf_func(const void* pBuf, int len, void *pUser)
{
	std::vector <unsigned char> *ptr = (std::vector <unsigned char>*)pUser;
	unsigned char* raw = (unsigned char*)pBuf;
	for (int i = 0; i < len; i++)
	{
		ptr->push_back(raw[i]);
	}

	return 1;
}

//Uses MiniZ to uncompress the file from the MapGenerator Tool
void CompressedMapLoader::UncompressMapTxtFile(std::string fileLocation, std::vector<int> &uncompressedData)
{
	std::vector<unsigned char> compressedData;
	LoadFile(fileLocation, compressedData);

	size_t size = compressedData.size();
	std::vector <unsigned char> output;

	int status = tinfl_decompress_mem_to_callback(&compressedData.at(0), &size, 
		tinfl_put_buf_func, &output, TINFL_FLAG_PARSE_ZLIB_HEADER);

	if (status < 1)
	{
		throw std::exception();
	}

	//outputs size will be 4 times the amount due to the unsigned char byte size
	//Reduce it to fit the size of ints within Output 
	int newsize = output.size() / sizeof(int);
	uncompressedData.resize(newsize);

	memcpy(&uncompressedData.at(0), &output.at(0), size);
}

//Loads in the file using C -- This is due to C++ not correcly reading in the txt file
void CompressedMapLoader::LoadFile(std::string fileLocation, std::vector<unsigned char> &compressedData)
{
	std::FILE *f = fopen(fileLocation.c_str(), "rb");

	if (f == NULL)
	{
		throw std::exception();
	}

	const int chunk = 1024; 
	size_t nread = 0;

	while (true)
	{
		char buf[chunk];

		int ar = fread(buf, 1, chunk, f);
		if (ar <= 0) break;

		for (int i = 0; i < ar; i++)
		{
			compressedData.push_back(buf[i]);
		}
	}

	fclose(f);
}
