#ifndef GOERTEK_AFFINE_TRANSFORM_TOOL_H_
#define GOERTEK_AFFINE_TRANSFORM_TOOL_H_

#ifdef __cplusplus    
//extern "C" {
#endif

#include "Goertek_BasicFunc.h"
#include "mario.h"
#include <vector>


	/************************************************************************************************************************
	函数：		Gk_FindHomography
	功能：		获得从from点集到to点集的透视变换矩阵H
	               x*h[0][0] + y*h[1][0] + x*y*h[2][0] + h[3][0] = X
				   x*h[0][1] + y*h[1][1] + x*y*h[2][1] + h[3][1] = Y
									from * H = to
	参数：
			输入：
					from点集、to点集
			输出：
					H为从from点集到to点集的透视变换矩阵H，大小为4*2
			返回：
					透视变换矩阵H计算成功，则返货true；否则返回false
	注：为了求透视变换，from和to的点集中的点要一一对应，要得到该透视变换，每个点集中至少要有4个点。
	*****************************************************************************************************************************/
	bool Gk_FindHomography(std::vector<Gk_Point> *from, std::vector<Gk_Point> *to, double *H);
	



	bool Gk_AffineTransformTool_Point(Gk_Point *point, Gk_Point *resultPoint, double *H);




	bool Gk_AffineTransformTool_Points(std::vector<Gk_Point> *points, std::vector<Gk_Point> *resultPoints, double *H);



	

	/************************************************************************************************************************
	函数：		Gk_AffineTransformTool
	功能：		根据透视变换矩阵H将src中的点填到dst中
					
	参数：
			输入：
					src
			输出：
					dst
			返回：
					若填点完成，则返回true；否则返回false
	注：矩阵H表示的是从dst到src的透视变换
	*****************************************************************************************************************************/
	bool Gk_AffineTransformTool_Image(IMGDATA *src, IMGDATA *dst, double *H);



#ifdef __cplusplus    
//}
#endif

#endif