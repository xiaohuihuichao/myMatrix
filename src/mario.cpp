#include "mario.h"

uchar Gk_GetGray(IMGDATA *src, int row, int col)
{
	if (NULL == src)
	{
		Gk_ErrorPrint("Error in Func Gk_GetGray: input parameter points to NULL.");
		return 0;
	}

	if (row < 0 || col < 0
		|| row >= src->iRows || col >= src->iCols)
	{
		Gk_ErrorPrint("Error in Func Gk_GetGray: the index is out of image.");
		return 0;
	}

	uchar *pSrcData = src->pUdata + row*src->iStride;

	return pSrcData[col];
}




bool Gk_SetGray(IMGDATA *src, int row, int col, uchar data)
{
	if (NULL == src)
	{
		Gk_ErrorPrint("Error in Func Gk_SetGray: input parameter points to NULL.");
		return false;
	}

	if (row < 0 || col < 0
		|| row >= src->iRows || col >= src->iCols)
	{
		Gk_ErrorPrint("Error in Func Gk_SetGray: the index is out of image.");
		return false;
	}

	uchar *pSrcData = src->pUdata + row*src->iStride;
	pSrcData[col] = data;

	return true;
}




bool Gk_InitRECT(Gk_RECT *rect, int row, int col, int height, int width)
{
	if (NULL == rect)
	{
		Gk_ErrorPrint("Error in Func initRECT: input parameter points to NULL.");
		return false;
	}

	rect->iRows = row;
	rect->iCols = col;
	rect->iHeight = height;
	rect->iWidth = width;

	return true;
}




bool Gk_ProdMatrix(double *src1, int row1, int col1, double *src2, int row2, int col2
							, double *dst, int dstRow, int dstCol)
{
	if (NULL == src1 || NULL == src2 || NULL == dst)
	{
		Gk_ErrorPrint("Error in func Gk_ProdMatrix: input parameter point to NULL.");
		return false;
	}

	if (col1 != row2)
	{
		Gk_ErrorPrint("Error in func Gk_ProdMatrix: the size of input matrixes are wrong.");
		return false;
	}

	if (dstRow != row1 || dstCol != col2)
	{
		Gk_ErrorPrint("Error in func Gk_ProdMatrix: the size of output matrix is wrong.");
		return false;
	}

	for (int row = 0; row < dstRow; ++row)
	{
		for (int col = 0; col < dstCol; ++col)
		{
			int indexDst = row * dstCol + col;
			
			dst[indexDst] = 0;
			for (int m = 0; m < col1; ++m)
			{
				int indexSrc1 = row * col1 + m;
				int indexSrc2 = m * col2 + col;
				dst[indexDst] += src1[indexSrc1] * src2[indexSrc2];
			}	//for m
		}	//for col
	}	//for row

	return true;
}




bool Gk_invMatrix_LU(double *src, int n, double *dst)
{
	if (NULL == src || NULL == dst)
	{
		Gk_ErrorPrint("Error in Gk_invMatrix_LU: input matrix point to NULL.");
		return false;
	}

	const double EPSINON = 1e-8;
	double det = Gk_GetDet(src, n);

	__int64 & ref = *(__int64 *)&det;
	if ((ref & 0x7FF0000000000000) == 0x7FF0000000000000 && (ref & 0xfffffffffffff) != 0)	
	{
		Gk_ErrorPrint("Error in Gk_invMatrix_LU: the det of input array is NAN. -1.#IND");
		return false;
	}

	if (det <= EPSINON && det >= -1 * EPSINON)
	{
		Gk_ErrorPrint("Error in Gk_invMatrix_LU: the det of input array is equal to 0.");
		return false;
	}

	//create l l_inverse and u u_inversematrix
	double *l = new double[n * n];
	double *l_inverse = new double[n * n];
	double *u = new double[n * n];
	double *u_inverse = new double[n * n];

	memset(dst, 0, sizeof(double)* n * n);
	memset(l, 0, sizeof(double) * n * n);
	memset(l_inverse, 0, sizeof(double) * n * n);
	memset(u, 0, sizeof(double) * n * n);
	memset(u_inverse, 0, sizeof(double) * n * n);

	//计算矩阵对角线
	for (int i = 0; i < n; ++i)
	{
		l[i * n + i] = 1;
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			double s = 0;
			for (int k = 0; k < i; ++k)
			{
				s += l[i*n + k] * u[k*n + j];			//按行计算u值
			}
			u[i*n + j] = src[i*n + j] - s;
		}

		for (int j = i + 1; j < n; ++j)
		{
			double s = 0;
			for (int k = 0; k < i; ++k)
			{
				s += l[j*n + k] * u[k*n + i];
			}
			l[j*n + i] = (src[j*n + i] - s) / u[i*n + i];			//按列计算l值
		}
	}


	for (int i = 0; i < n; ++i)			//按行序，行内从高到底，计算l的逆矩阵
	{
		l_inverse[i*n + i] = 1;
	}
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			double s = 0;
			for (int k = 0; k < i; ++k)
			{
				s += l[i*n + k] * l_inverse[k*n + j];
			}
			l_inverse[i*n + j] = -s;
		}
	}


	for (int i = 0; i < n; ++i)			//按列序，列内按照从下到上，计算u的逆矩阵
	{
		u_inverse[i*n + i] = 1 / u[i*n + i];
	}
	for (int i = 1; i < n; ++i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			double s = 0;
			for (int k = j + 1; k <= i; ++k)
			{
				s += u[j*n + k] * u_inverse[k*n + i];
			}
			u_inverse[j*n + i] = -s / u[j*n + j];
		}
	}


	//u_inverse * l_inverse
	Gk_ProdMatrix(u_inverse, n, n, l_inverse, n, n, dst, n, n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			__int64 & ref = *(__int64 *)&dst[i*n + j];
			if ((ref & 0x7FF0000000000000) == 0x7FF0000000000000 && (ref & 0xfffffffffffff) != 0)
			{
				Gk_ErrorPrint("Error in Gk_invMatrix_LU: the output array is NAN. -1.#IND");
				return false;
			}
		}
	}


	delete []u_inverse;
	delete []u;
	delete []l_inverse;
	delete []l;
	return true;
}




bool Gk_SwapArray(double *src1, double *src2, int n)
{
	if (NULL == src1 || NULL == src2)
	{
		Gk_ErrorPrint("Error in func Gk_SwapArray: input array point to NULL.");
		return false;
	}

	if (src1 == src2)
	{
		Gk_ErrorPrint("Error in func Gk_SwapArray: two input arrays point to the same memory directory.");
		return false;
	}

	double temp = 0;
	for (int i = 0; i < n; ++i)
	{
		temp = src1[i];
		src1[i] = src2[i];
		src2[i] = temp;
	}

	return true;
}




double Gk_GetDet(double *src, int n)
{
	if (NULL == src)
	{
		Gk_ErrorPrint("Error in func Gk_SwapArray: input array point to NULL.");
		return 0;
	}

	double *array = new double[n * n];
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			array[i*n + j] = src[i*n + j];
		}
	}

	//记录行变换次数
	int iter = 0;

	//行列式结果
	double det = 1;

	for (int i = 0; i < n; ++i)
	{
		if (0 == array[i*n + i])
		{
			for (int j = i; j < n; ++j)
			{
				if (array[j*n + i] != 0)
				{
					Gk_SwapArray(array + i*n, array + j*n, n);
					++iter;
				}
			}
		}

		for (int k = i + 1; k < n; ++k)
		{
			double scale = -1 * array[k*n + i] / array[i*n + i];

			for (int u = 0; u < n; ++u)
			{
				array[k*n + u] = array[k*n + u] + array[i*n + u] * scale;
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		det *= array[i*n + i];
	}

	if (1 == iter % 2)
	{
		det *= -1;
	}

	delete []array;
	return det;
}




bool Gk_MatrixTransform(double *src, int rowSrc, int colSrc, double *dst, int rowDst, int colDst)
{
	if (NULL == src || NULL == dst)
	{
		Gk_ErrorPrint("Error in func Gk_MatrixTransform: input array point to NULL.");
		return false;
	}
	if (rowSrc != colDst || colSrc != rowDst)
	{
		Gk_ErrorPrint("Error in func Gk_MatrixTransform: the size of input array is wrong.");
		return false;
	}


	for (int i = 0; i < rowSrc; ++i)
	{
		for (int j = 0; j < colSrc; ++j)
		{
			dst[j*colDst + i] = src[i*colSrc + j];
		}
	}

	return true;
}