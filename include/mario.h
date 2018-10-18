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
		RECT�ṹ��
		��iRow��iCol��iHeight��iWidth�ĸ���Ա����
	*/
	typedef struct Gk_RECT
	{
		int iRows;
		int iCols;
		int iHeight;
		int iWidth;
	} Gk_RECT;



	/*
		Point�ṹ��
		��x, y������Ա����
	*/
	typedef struct Gk_Point
	{
		int x;
		int y;
	} Gk_Point;



	/************************************************************************************************************************
	���ܣ�			����ͼ��ĳ������ĻҶ�ֵ
	��������		Gk_SetGray
	�������룺	IMGDATA *src1, int row, int col, uchar data
	����	��			bool ������ͼ��ָ�벻Ϊ��������û��Խ�磬��������Ҷ�ֵ�󷵻�true�����򷵻�false

	ע���������ͼ��ֻ���ǻҶ�ͼ��
	*************************************************************************************************************************/
	bool Gk_SetGray(IMGDATA *src, int row, int col, uchar data);



	/************************************************************************************************************************
	���ܣ�			���ͼ��ĳ������ĻҶ�ֵ
	��������		Gk_GetGray
	�������룺	IMGDATA *src1, int row, int col
	����	��			������ͼ��ָ�벻Ϊ��������û��Խ�磬�򷵻���ȷ�ĻҶ�ֵ������ͳһ����0

	ע���������ͼ��ֻ���ǻҶ�ͼ��
	*************************************************************************************************************************/
	uchar Gk_GetGray(IMGDATA *src, int row, int col);



	/************************************************************************************************************************
	���ܣ�				���ṹ��RECT��ʼ��
	��������			Gk_InitRECT
	������
			���룺		RECT *rect, int row, int col, int height, int width
			�����		����bool���������RECTָ�벻Ϊ�գ��򷵻�true�����򷵻�false

	ע���������ͼ��ֻ���ǻҶ�ͼ��
	*************************************************************************************************************************/
	bool Gk_InitRECT(Gk_RECT *rect, int row, int col, int height, int width);



	/************************************************************************************************************************
	���ܣ�				�������
	��������			Gk_ProdMatrix
	������
			���룺		double *src1, int row1, int col1, double *src2, int row2, int col2, int dstRow, int dstCol
						src1��src2Ϊ������˵ľ���
						row1, col1, row2, col2�ֱ�Ϊsrc1��src2������������
						dstRow, dstColΪ��������dst������������
			�����		double *dst
							����bool
	*************************************************************************************************************************/
	bool Gk_ProdMatrix(double *src1, int row1, int col1, double *src2, int row2, int col2
		, double *dst, int dstRow, int dstCol);



	/************************************************************************************************************************
	���ܣ�				ʹ��LU�ֽ�Է�������
	��������			Gk_invMatrix_LU
	������
			double *src, int n, double *dst
			���룺
				double *src, int n
				src1Ϊ������ķ���nΪ�÷���Ľ���
			�����		
					double *dst�������
	���أ�bool

	ע�⣺����������������ͬ�Ĵ�С���Ҷ�����Ϊn*n�ķ���
			�����뷽�������ʽΪ0��������õ��������ֵ����NAN���򷵻�false
	*************************************************************************************************************************/
	bool Gk_invMatrix_LU(double *src, int n, double *dst);



	/************************************************************************************************************************
	���ܣ�				����������ʽ
	��������			Gk_GetDet
	������
					double *src, int n
			���룺
					double *src, int n
					srcΪ���뷽��nΪ����Ľ���
			�����
					����doubleΪ���������ʽ

	ע�⣺����������Ϊn*n�ķ���
	*************************************************************************************************************************/
	double Gk_GetDet(double *src, int n);



	/************************************************************************************************************************
	���ܣ�				�����������ǰn����ֵ����
	��������			Gk_SwapArray
	������
			double *src1, double *src2, int n
			���룺
					double *src1, double *src2, int n
					src1��src2��Ϊ�������飬nΪ�����ĸ���
			�����
					����ֵbool���������ɹ����򷵻�true

	ע�⣺�������������n��Ԫ�أ���������Խ��
	*************************************************************************************************************************/
	bool Gk_SwapArray(double *src1, double *src2, int n);



	bool Gk_MatrixTransform(double *src, int rowSrc, int colSrc, double *dst, int rowDst, int colDst);



#ifdef __cplusplus    
}
#endif

#endif