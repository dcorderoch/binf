#include <stdio.h> // for printf(), scanf(), NULL, FILE, fopen()
#include <unistd.h> // for sleep()
#include <stdbool.h> // for bool type
#include <regex.h> // for regular expressions POSIX
#include <stdlib.h> // for malloc() & free()
#include <string.h> // for strlen(), memcpy() & memset()
#include <stdlib.h> // for srand(), rand()
#include <time.h> // for time()
#include <sys/types.h> // for stat() and struct stat type
#include <sys/stat.h> // for stat() and struct stat type

void createFile(char * pValidFilePath);
void deleteFile(char * pValidFilePath);
int getFileSize(char * pValidFilePath);

int main() //int argc, char const *argv[])
{
	char * testFile = "/tmp/test.bin";
	//char * testFile2 = "/tmp/test2.bin";
	int test = getFileSize(testFile);
	printf("the size (in bytes) of %s is: %d\n", testFile, test);
	//printf("the \n", );
	//createFile(testFile2);
	deleteFile(testFile);

	return 0;
}

void createFile(char * pValidFilePath)
{
	printf("start createFile() Function\n");
	FILE * TheFile;
	TheFile = fopen (pValidFilePath, "wb");
	//fwrite((void*)0,0,0,TheFile);
	fclose(TheFile);
	printf("end createFile() Function\n");
}

void deleteFile(char * pValidFilePath)
{
	int status = 0;
	status = remove(pValidFilePath);

	if( status == 0 )
	{
		printf("%s file deleted successfully.\n",pValidFilePath);
	}
	else
	{
		printf("Unable to delete the file\n");
		perror("Error");
	}
}

int getFileSize(char * pValidFilePath)
{
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
}
