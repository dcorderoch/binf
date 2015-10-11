// include statements

#include <stdio.h> // for printf(), scanf(), NULL, FILE, fopen()
#include <unistd.h> // for sleep()
#include <stdbool.h> // for bool type
#include <stdlib.h> // for malloc() & free()
#include <string.h> // for strlen(), memcpy() & memset()
#include <stdlib.h> // for srand(), rand()
#include <time.h> // for time()
#include <sys/types.h> // for stat() and struct stat type
#include <sys/stat.h> // for stat() and struct stat type
// ############################################################################
// constant and variable definitions
// ############################################################################
// function signatures

// create a file at the pValidFilePath URI
void createFile(char * pValidFilePath);

// get the filesize of the file at the pValidFilePath URI
int getFileSize(char * pValidFilePath);

// delete the file at the pValidFilePath URI
void deleteFile(char * pValidFilePath);

// add data of size pDataSize at the end of the file at the pValidFilePath URI
void append2File(char * pValidFilePath, void * pData, int pDataSize);

// delete information anywhere in the file
void deleteLast(char * pValidFilePath,int pSizeOfData);
// ############################################################################
// main function definition

int main() //int argc, char const *argv[])
{
	char * testFile = "./test.bin";
	createFile(testFile);

	int test = getFileSize(testFile);
	printf("the size (in bytes) of %s is: %d\n", testFile, test);

	int therealdata = 65;

	char * data = (char*)(&therealdata); // 65 is 'A' in ASCII
	append2File(testFile,(void*)data,sizeof(therealdata));

	test = getFileSize(testFile);
	printf("the size (in bytes) of %s is: %d\n", testFile, test);

	therealdata = 67;

	data = (char*)(&therealdata); // 65 is 'A' in ASCII
	append2File(testFile,(void*)data,sizeof(therealdata));

	test = getFileSize(testFile);
	printf("the size (in bytes) of %s is: %d\n", testFile, test);

	deleteLast(testFile,sizeof(therealdata));

	test = getFileSize(testFile);
	printf("the size (in bytes) of %s is: %d\n", testFile, test);

	deleteFile(testFile);

	return 0;
}
// ############################################################################
// function definitions

void deleteLast(char * pValidFilePath,int pSizeOfData)
{
	printf("start deleteLast Function\n");
	int Thefilesize = getFileSize(pValidFilePath);
	if (pSizeOfData < Thefilesize)
	{
		int result = truncate(pValidFilePath,Thefilesize - pSizeOfData);
		if (result == 0)
		{
			printf("successfully deleted %d bytes from file %s\n", pSizeOfData,pValidFilePath);
		}
		else
		{
			printf("could not delete %d bytes from file %s\n", pSizeOfData,pValidFilePath);
		}
	}
	else
	{
		printf("filesize smaller than size of data to delete\n");
	}
	printf("end deleteLast Function\n");
}

void append2File(char * pValidFilePath, void * pData, int pDataSize)
{
	printf("start append2File() Function\n");
	FILE * TheFile;
	TheFile = fopen(pValidFilePath, "a+b"); // append to a file
	fwrite(pData,sizeof(char),(size_t)pDataSize,TheFile);
	fclose(TheFile);
	printf("end append2File() Function\n");
}

void createFile(char * pValidFilePath)
{
	printf("start createFile() Function\n");
	FILE * TheFile;
	TheFile = fopen (pValidFilePath, "w+b");
	fclose(TheFile);
	printf("end createFile() Function\n");
}

void deleteFile(char * pValidFilePath)
{
	printf("start deleteFile() Function\n");
	int status = 0;
	status = remove(pValidFilePath);

	if( status == 0 )
	{
		printf("%s file deleted successfully.\n",pValidFilePath);
	}
	else
	{
		printf("Unable to delete the file\n");
		perror("Error deleting file");
	}
	printf("end deleteFile() Function\n");
}

int getFileSize(char * pValidFilePath)
{
	printf("start getFileSize() Function\n");
	struct stat st;
	if(!stat(pValidFilePath, &st))
	{
		return st.st_size;
	}
	else
	{
		printf("error, file not found when trying to get filesize\n");
		return -1;
	}
	printf("end getFileSize() Function\n");
}
