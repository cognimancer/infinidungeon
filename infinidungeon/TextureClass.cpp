#include "TextureClass.h"

TextureClass::TextureClass(void) { Init(); }
TextureClass::TextureClass(const TextureClass& other) { }
TextureClass& TextureClass::operator=(const TextureClass& other) { return *this; }
TextureClass::~TextureClass(void) { Release(); }

void TextureClass::Release(void)
{
	glDeleteTextures(1, &m_nGLTextureID);
}
void TextureClass::Init(void)
{
	m_nGLTextureID = -1;
}
void TextureClass::LoadTexture(std::string a_sFileName)
{
	m_sName = a_sFileName;
	m_sFileName = FolderClass::GetInstance()->Root;
	m_sFileName += FolderClass::GetInstance()->Data;
	m_sFileName += FolderClass::GetInstance()->Textures;
	m_sFileName += m_sName;

	if(m_nGLTextureID == -1)
	{
		 m_nGLTextureID = SOIL_load_OGL_texture
		(
			m_sFileName.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
		);
	}
	else
	{
		m_nGLTextureID = SOIL_load_OGL_texture
		(
			m_sFileName.c_str(),
			SOIL_LOAD_AUTO,
			m_nGLTextureID,
			SOIL_FLAG_INVERT_Y
		);
	}
}
//Accessors
GLuint TextureClass::GetGLTextureID(void){return m_nGLTextureID;}
std::string TextureClass::GetTextureName(void){return m_sName;}
std::string TextureClass::GetTextureFileName(void){return m_sFileName;}