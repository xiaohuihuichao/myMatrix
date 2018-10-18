#ifndef GOERTEK_BASIC_FUNC_H_
#define GOERTEK_BASIC_FUNC_H_

#ifdef __cplusplus    
extern "C" {          
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include <stdbool.h>

#define OK 0
#define ERROR -1

#define MEM_ALIGNMENT           4
#define WINDOWSTRIDE(n) (((n) + MEM_ALIGNMENT - 1) & ~(MEM_ALIGNMENT - 1))

typedef unsigned char uchar;

typedef struct IMG_DATA
{
	int iRows;
	int iCols;
	int iChannels;
	int iStride;
	uchar* pUdata;
} IMGDATA;




/*Function declaration*/
int Gk_ImgCreateMemstorage(int iRow, int iCol, int iChannel, IMGDATA* imgData);
void Gk_ImgMemsetMemstorage(IMGDATA* imgData);
int Gk_ImgReleaseMemstorage(IMGDATA* imgData);
void Gk_ErrorPrint(char* cStr);




#ifdef __cplusplus
}
#endif

#endif