#include "Goertek_BasicFunc.h"

int Gk_ImgCreateMemstorage(int iRow, int iCol, int iChannel, IMGDATA* imgData)
{
	imgData->iRows = iRow;
	imgData->iCols = iCol;
	imgData->iChannels = iChannel;
	imgData->iStride = WINDOWSTRIDE(iCol);
	imgData->pUdata = (uchar*)malloc(sizeof(uchar)* imgData->iRows * imgData->iStride*imgData->iChannels);

	if (NULL == imgData->pUdata)
	{
		Gk_ErrorPrint("Func Gk_ImgCreateMemstorage:Create Memstorge error");
		return ERROR;
	}

	return OK;

}

int Gk_ImgReleaseMemstorage(IMGDATA* imgData)
{
	free(imgData->pUdata);
	imgData->pUdata = NULL;

	return OK;
}

void Gk_ImgMemsetMemstorage(IMGDATA* imgData)
{
	unsigned int iSizeNum = sizeof(uchar)* imgData->iRows * imgData->iStride*imgData->iChannels;
	memset(imgData->pUdata, 0, iSizeNum);
}


void Gk_ErrorPrint(char* cStr)
{
	printf(cStr);
	printf("\n");
	system("pause");
}

