/*
		uchar Gk_GetGray(IMGDATA *src, int row, int col);

		bool Gk_SetGray(IMGDATA *src, int row, int col, uchar data);

		bool Gk_InitRECT(RECT *rect, int row, int col, int height, int width);

		bool Gk_ProdMatrix(double *src1, int row1, int col1, double *src2, int row2, int col2, double *dst, int dstRow, int dstCol);

		bool Gk_invMatrix_LU(double *src, int n, double *dst);

		double Gk_GetDet(double *src, int n);

		bool Gk_SwapArray(double *src1, double *src2, int n);
*/

#ifndef MARIO_H_
#define MARIO_H_

#ifdef __cplusplus    
extern "C" {
#endif

#include "Goertek_BasicFunc.h"
#include <memory.h>



	/*
		RECT结构体
		有iRow，iCol，iHeight，iWidth四个成员变量
	*/
	typedef struct Gk_RECT
	{
		int iRows;
		int iCols;
		int iHeight;
		int iWidth;
	} Gk_RECT;



	/*
		Point结构体
		有x, y两个成员变量
	*/
	typedef struct Gk_Point
	{
		int x;
		int y;
	} Gk_Point;



	/************************************************************************************************************************
	功能：			设置图像某个坐标的灰度值
	函数名：		Gk_SetGray
	函数输入：	IMGDATA *src1, int row, int col, uchar data
	返回	：			bool 若输入图像指针不为空且坐标没有越界，则设置完灰度值后返回true，否则返回false

	注意事项：输入图像只能是灰度图像
	*************************************************************************************************************************/
	bool Gk_SetGray(IMGDATA *src, int row, int col, uchar data);



	/************************************************************************************************************************
	功能：			获得图像某个坐标的灰度值
	函数名：		Gk_GetGray
	函数输入：	IMGDATA *src1, int row, int col
	返回	：			若输入图像指针不为空且坐标没有越界，则返回正确的灰度值，否则统一返回0

	注意事项：输入图像只能是灰度图像
	*************************************************************************************************************************/
	uchar Gk_GetGray(IMGDATA *src, int row, int col);



	/************************************************************************************************************************
	功能：				给结构体RECT初始化
	函数名：			Gk_InitRECT
	参数：
			输入：		RECT *rect, int row, int col, int height, int width
			输出：		返回bool，若输入的RECT指针不为空，则返回true，否则返回false

	注意事项：输入图像只能是灰度图像
	*************************************************************************************************************************/
	bool Gk_InitRECT(Gk_RECT *rect, int row, int col, int height, int width);



	/************************************************************************************************************************
	功能：				矩阵相乘
	函数名：			Gk_ProdMatrix
	参数：
			输入：		double *src1, int row1, int col1, double *src2, int row2, int col2, int dstRow, int dstCol
						src1和src2为两个相乘的矩阵，
						row1, col1, row2, col2分别为src1和src2的行数与列数
						dstRow, dstCol为输出矩阵的dst的行数与列数
			输出：		double *dst
							返回bool
	*************************************************************************************************************************/
	bool Gk_ProdMatrix(double *src1, int row1, int col1, double *src2, int row2, int col2
		, double *dst, int dstRow, int dstCol);



	/************************************************************************************************************************
	功能：				使用LU分解对方阵求逆
	函数名：			Gk_invMatrix_LU
	参数：
			double *src, int n, double *dst
			输入：
				double *src, int n
				src1为待求逆的方阵，n为该方阵的阶数
			输出：		
					double *dst，逆矩阵
	返回：bool

	注意：输入和输出必须有相同的大小，且都必须为n*n的方阵
			若输入方阵的行列式为0，或者求得的逆矩阵数值中有NAN，则返回false
	*************************************************************************************************************************/
	bool Gk_invMatrix_LU(double *src, int n, double *dst);



	/************************************************************************************************************************
	功能：				求矩阵的行列式
	函数名：			Gk_GetDet
	参数：
					double *src, int n
			输入：
					double *src, int n
					src为输入方阵，n为方阵的阶数
			输出：
					返回double为方阵的行列式

	注意：输入矩阵必须为n*n的方阵
	*************************************************************************************************************************/
	double Gk_GetDet(double *src, int n);



	/************************************************************************************************************************
	功能：				将两个数组的前n个数值交换
	函数名：			Gk_SwapArray
	参数：
			double *src1, double *src2, int n
			输入：
					double *src1, double *src2, int n
					src1和src2均为输入数组，n为交换的个数
			输出：
					返回值bool，若交换成功，则返回true

	注意：输入矩阵至少有n个元素，否则会造成越界
	*************************************************************************************************************************/
	bool Gk_SwapArray(double *src1, double *src2, int n);



	bool Gk_MatrixTransform(double *src, int rowSrc, int colSrc, double *dst, int rowDst, int colDst);



#ifdef __cplusplus    
}
#endif

#endif