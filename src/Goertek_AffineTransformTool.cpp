#include "Goertek_AffineTransformTool.h"


bool Gk_FindHomography(std::vector<Gk_Point> *from, std::vector<Gk_Point> *to, double *H)
{
	if (NULL == from || NULL == to)
	{
		Gk_ErrorPrint("Error in func Gk_FindHomography: input parameter point to NULL.");
		return false;
	}

	if (from->size() != to->size())
	{
		Gk_ErrorPrint("Error in func Gk_FindHomography: the size of input points is not equal.");
		return false;
	}

	if (from->size() < 4 || to->size() < 4)
	{
		Gk_ErrorPrint("Error in func Gk_FindHomography: the size of points is not enough.");
		return false;
	}


	//X * H = Y
	double *X = new double[from->size() * 4];
	double *Y = new double[to->size() * 2];


	/*
			x1		y1		x1*y1		1				c1		c5					X1		Y1
			x2		y2		x2*y2		1				c2		c6					X2		Y2
			x3		y3		x3*y3		1				c3		c7					X3		Y3
			x4		y4		x4*y4		1				c4		c8					X4		Y4
			...
			...
			X    size x 4									H    4 x 2						Y    size x 2
	*/

	for (unsigned int i = 0; i < from->size(); ++i)
	{
		X[i * 4 + 0] = (double)from->at(i).x;		//x
		X[i * 4 + 1] = (double)from->at(i).y;		//y
		X[i * 4 + 2] = X[i * 4 + 0] * X[i * 4 + 1];		//x * y
		X[i * 4 + 3] = 1.;		//1

		Y[i * 2 + 0] = (double)to->at(i).x;		//x
		Y[i * 2 + 1] = (double)to->at(i).y;		//y
	}
	//X_T	4 * size
	double *XT = new double[4 * from->size()];
	//X_T * X		4 * 4
	double *XTX = new double[4 * 4];
	//(X_T * X)_Inv	4 * 4
	double *XTX_Inv = new double[4 * 4];
	//X_T * Y	4 * 2
	double *XTY = new double[4 * 2];

	//XT
	if (!Gk_MatrixTransform(X, from->size(), 4, XT, 4, from->size()))
	{
		Gk_ErrorPrint("Error in func Gk_FindHomography: Gk_MatrixTransform return false.");
		return false;
	}

	//XT * X = XTX
	if (!Gk_ProdMatrix(XT, 4, from->size(), X, from->size(), 4, XTX, 4, 4))
	{
		Gk_ErrorPrint("Error in func Gk_ProdMatrix: Gk_ProdMatrix return false.");
		return false;
	}

	//XTX inverse = XTX_Inv
	if (!Gk_invMatrix_LU(XTX, 4, XTX_Inv))
	{
		Gk_ErrorPrint("Error in func Gk_ProdMatrix: Gk_invMatrix_LUs return false.");
		return false;
	}

	//XT * Y = XTY
	if (!Gk_ProdMatrix(XT, 4, from->size(), Y, to->size(), 2, XTY, 4, 2))
	{
		Gk_ErrorPrint("Error in func Gk_ProdMatrix: Gk_ProdMatrix return false.");
		return false;
	}

	if (!Gk_ProdMatrix(XTX_Inv, 4, 4, XTY, 4, 2, H, 4, 2))
	{
		Gk_ErrorPrint("Error in func Gk_ProdMatrix: Gk_ProdMatrix return false.");
		return false;
	}
	
	delete[]XTY;
	delete[]XTX_Inv;
	delete[]XTX;
	delete[]XT;
	delete[]Y;
	delete[]X;
	return true;
}






bool Gk_AffineTransformTool_Point(Gk_Point *point, Gk_Point *resultPoint, double *H)
{
	if (NULL == point || NULL == resultPoint)
	{
		Gk_ErrorPrint("Error in func Gk_AffineTransformTool_Point: input point to NULL.");
		return false;
	}

	int resultX = 0;
	int resultY = 0;


	resultX = (int)(point->x * H[0 * 2 + 0] + point->y * H[1 * 2 + 0] + point->x * point->y * H[2 * 2 + 0] + H[3 * 2 + 0]);
	resultY = (int)(point->x * H[0 * 2 + 1] + point->y * H[1 * 2 + 1] + point->x * point->y * H[2 * 2 + 1] + H[3 * 2 + 1]);

	resultPoint->x = resultX;
	resultPoint->y = resultY;

	return true;
}





bool Gk_AffineTransformTool_Points(std::vector<Gk_Point> *points, std::vector<Gk_Point> *resultPoints, double *H)
{
	if (NULL == points || NULL == resultPoints)
	{
		Gk_ErrorPrint("Error in func Gk_AffineTransformTool_Point: input point to NULL.");
		return false;
	}

	Gk_Point result;
	int resultX = 0;
	int resultY = 0;
	for (unsigned int i = 0; i < points->size(); ++i)
	{

		resultX = (int)(points->at(i).x * H[0 * 2 + 0] + points->at(i).y * H[1 * 2 + 0] + points->at(i).x * points->at(i).y * H[2 * 2 + 0] + H[3 * 2 + 0]);
		resultY = (int)(points->at(i).x * H[0 * 2 + 1] + points->at(i).y * H[1 * 2 + 1] + points->at(i).x * points->at(i).y * H[2 * 2 + 1] + H[3 * 2 + 1]);

		result.x = resultX;
		result.y = resultY;

		resultPoints->push_back(result);
		/*
		if (!Gk_AffineTransformTool_Point(&(points->at(i)), &result, H))
		{
			resultPoints->push_back(result);
		}
		*/
	}

	return true;
}





bool Gk_AffineTransformTool_Image(IMGDATA *src, IMGDATA *dst, double *H)
{
	if (NULL == src || NULL == dst || NULL == H)
	{
		Gk_ErrorPrint("Error in func Gk_AffineTransformTool_Image: input point to NULL.");
		return false;
	}
	if (src->iChannels != dst->iChannels)
	{
		Gk_ErrorPrint("Error in func Gk_AffineTransformTool_Image: the channel of input and output is not equal.");
		return false;
	}

	int X = 0;
	int Y = 0;

	uchar *pDstData = NULL;
	uchar *pSrcData = NULL;
	Gk_Point point;
	//Gk_Point resultPoint;
	for (int y = 0; y < dst->iRows; ++y)
	{
		pDstData = dst->pUdata + y*dst->iStride*dst->iChannels;

		for (int x = 0; x < dst->iCols; ++x)
		{
			point.x = x;
			point.y = y;

			//Gk_AffineTransformTool_Point(&point, &resultPoint, H);
			//X = resultPoint.x;
			//Y = resultPoint.y;

			X = (int)(x * H[0 * 2 + 0] + y * H[1 * 2 + 0] + x * y * H[2 * 2 + 0] + H[3 * 2 + 0]);
			Y = (int)(x * H[0 * 2 + 1] + y * H[1 * 2 + 1] + x * y * H[2 * 2 + 1] + H[3 * 2 + 1]);

			//点在dst范围内
			if (src->iRows > Y && src->iCols > X
				&& Y > 0 && X > 0)
			{
				pSrcData = src->pUdata + Y*src->iStride*src->iChannels;
				for (int channel = 0; channel < dst->iChannels; ++channel)
				{
					pDstData[x*dst->iChannels + channel] = pSrcData[X*src->iChannels + channel];
				}
			}	//if
		}	//for x
	}	//for y

	/*
	if (1 == src->iChannels)
	{
	for (int y = 0; y < dst->iRows; ++y)
	{
	for (int x = 0; x < dst->iCols; ++x)
	{
	X = (int)(x * H[0 * 2 + 0] + y * H[1 * 2 + 0] + x * y * H[2 * 2 + 0] + H[3 * 2 + 0]);
	Y = (int)(x * H[0 * 2 + 1] + y * H[1 * 2 + 1] + x * y * H[2 * 2 + 1] + H[3 * 2 + 1]);

	//点在dst范围内
	if (src->iRows > Y && src->iCols > X
	&& Y > 0 && X > 0)
	{
	uchar data = Gk_GetGray(src, Y, X);
	Gk_SetGray(dst, y, x, data);
	}	//if
	}	//for x
	}	//for y
	}	//if channel
	else if (3 == src->iChannels)
	{
	uchar *pDstData = NULL;
	uchar *pSrcData = NULL;
	for (int y = 0; y < dst->iRows; ++y)
	{
	pDstData = dst->pUdata + y*dst->iStride*dst->iChannels;

	for (int x = 0; x < dst->iCols; ++x)
	{
	X = (int)(x * H[0 * 2 + 0] + y * H[1 * 2 + 0] + x * y * H[2 * 2 + 0] + H[3 * 2 + 0]);
	Y = (int)(x * H[0 * 2 + 1] + y * H[1 * 2 + 1] + x * y * H[2 * 2 + 1] + H[3 * 2 + 1]);

	//点在dst范围内
	if (src->iRows > Y && src->iCols > X
	&& Y > 0 && X > 0)
	{
	pSrcData = src->pUdata + Y*src->iStride*src->iChannels;

	pDstData[x*dst->iChannels + 0] = pSrcData[X*src->iChannels + 0];
	pDstData[x*dst->iChannels + 1] = pSrcData[X*src->iChannels + 1];
	pDstData[x*dst->iChannels + 2] = pSrcData[X*src->iChannels + 2];
	}	//if
	}	//for x
	}	//for y
	}	//else if channel
	*/

	return true;
}