#include "IOManager.h"
#include "Error.h"
#include <fstream>
bool IOManager::readFileToBuffer(std::string filePath,std::vector<unsigned char>& buffer)
{ 
	std::ifstream file(filePath, std::ios::binary);
	//Error Checking
	if (file.fail())
	{
		fatalError(filePath);
		return false;
	}

	//Determine size of file
	//seek to the end
	file.seekg(0, std::ios::end);
	
	//Get the file size
	int fileSize = file.tellg();
	
	//seek back to begin to rread;
	file.seekg(0, std::ios::beg);

	//Reduce file size by header files
	fileSize -= file.tellg();

	//Read now.

	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize);
	file.close();

	return true;

}