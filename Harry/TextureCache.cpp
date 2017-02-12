#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>


TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath)
{
	//lookup the texture and see if its in the map
	auto mit=_textureMap.find(texturePath);

	if (mit == _textureMap.end())
	{
		//Load the texture
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);
		//Insert it into the map
		_textureMap.insert(make_pair(texturePath, newTexture));
		std::cout << "Loaded after new creation"<<std::endl;
		return newTexture;
	}
	std::cout << "Loaded from Cache" << std::endl;
	return mit->second;
}
