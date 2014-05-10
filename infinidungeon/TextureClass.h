/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _TEXTURECLASS_H
#define _TEXTURECLASS_H
#include <string>
#include <GL\freeglut.h>
#include <SOIL\SOIL.h>
#include "FolderClass.h"

class TextureClass
{
	GLuint m_nGLTextureID;
	std::string m_sName;
	std::string m_sFileName;
public:
	TextureClass(void); //Constructor
	TextureClass(const TextureClass& other); //Copy Constructor
	TextureClass& operator=(const TextureClass& other); //Copy Assignment Operator
	void Release(void); //Release the fields in the class
	~TextureClass(void); //Destructor

	void LoadTexture(std::string a_sFileName);
//Accessors
	GLuint GetGLTextureID(void); //Returns the OpenGL Identifier
	__declspec(property(get = GetGLTextureID)) GLuint GLTextureID;
	std::string GetTextureName(void); //Returns the name of the texture
	__declspec(property(get = GetTextureName)) std::string TextureName;
	std::string GetTextureFileName(void); //Returns the filename of the texture
	__declspec(property(get = GetTextureFileName)) std::string TextureFileName;

private:
	void Init(void); //Initializes the variables
};
#endif //_TEXTURECLASS_H
