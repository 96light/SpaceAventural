#pragma once
	#include "utilities.h" 



class Texture
{
private:
	GLuint		m_iTextGlId;
	GLuint		m_iTextID;
	Vector2		m_textureSize;
public:
	int			Init(const char *szFileName,GLuint wapMode,GLuint filterMode);
	void		Set2DTextureId(GLuint);
	GLuint		Get2DTextureId();
	GLuint		Get2DTextureAdd();
	Vector2		GetTextureSize();
};
