#pragma once
#include "Vertex.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class Glyph {
public: Glyph(){}
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color)
		{
			texture = Texture;
			depth = Depth;

			topLeft.color = color;
			topLeft.setPosition(destRect.x, destRect.y + destRect.w);//w is the y component of 
			topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

			bottomLeft.color = color;
			bottomLeft.setPosition(destRect.x, destRect.y);//w is the y component of 
			bottomLeft.setUV(uvRect.x, uvRect.y);

			bottomRight.color = color;
			bottomRight.setPosition(destRect.x + destRect.z, destRect.y);//z is the x component of 
			bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

			topRight.color = color;
			topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);//z is the x component of 
			topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		}
	GLuint texture;
	float depth;
	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

class RenderBatch {
public:
	RenderBatch(GLuint Offset,GLuint NumVertices,GLuint Texture):	offset(Offset),
																	numVertices(NumVertices),
																	texture(Texture)
	{}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;

};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();
	void begin(GlyphSortType sortType=GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRect,const glm::vec4& uvRect,GLuint texture,float depth,const Color& color);
	void renderBatch();

private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();
	static bool compareFrontToBack(Glyph* a, Glyph *b);
	static bool compareBackToFront(Glyph* a, Glyph *b);
	static bool compareTexture(Glyph* a, Glyph *b);
	GLuint m_vbo;
	GLuint m_vao;

	std::vector<Glyph> m_glyphs;
	std::vector<Glyph* > m_glyphPointers;
	std::vector<RenderBatch> m_renderBatches;
	GlyphSortType m_sortType;

	
};

