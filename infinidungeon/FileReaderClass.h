/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _FILEREADERCLASS_H
#define _FILEREADERCLASS_H

#include <string>

enum Results
{
	ERROR_FREE,
	ERROR_FILE_MISSING,
	ERROR_CONTEXT,
	ERROR_MEMORY,
	ERROR_GENERAL,
	ERROR_NAME,
	ERROR_NOT_INITIALIZED,
	ERROR_FILE,
	DONE,
	RUNNING
};

class FileReaderClass
{
	FILE* m_pFile;
public:
	std::string m_sLine;
private:
	void Init(void);
public:
	FileReaderClass(void);
	
	FileReaderClass(const FileReaderClass& other);
	FileReaderClass& operator=(const FileReaderClass& other);
	~FileReaderClass(void);
	
	void Release(void);

	void Rewind(void) const;

	Results ReadFile(std::string a_sFileName);
	void CloseFile(void);
	Results ReadNextLine(bool bSkipComments = true);
	Results RemoveBlanks(char** szInput) const; //Modified by AndrewWilkinson88@gmail.com
};
#endif //_EMPTY_H
