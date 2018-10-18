#ifndef GOERTEK_AFFINE_TRANSFORM_TOOL_H_
#define GOERTEK_AFFINE_TRANSFORM_TOOL_H_

#ifdef __cplusplus    
//extern "C" {
#endif

#include "Goertek_BasicFunc.h"
#include "mario.h"
#include <vector>


	/************************************************************************************************************************
	������		Gk_FindHomography
	���ܣ�		��ô�from�㼯��to�㼯��͸�ӱ任����H
	               x*h[0][0] + y*h[1][0] + x*y*h[2][0] + h[3][0] = X
				   x*h[0][1] + y*h[1][1] + x*y*h[2][1] + h[3][1] = Y
									from * H = to
	������
			���룺
					from�㼯��to�㼯
			�����
					HΪ��from�㼯��to�㼯��͸�ӱ任����H����СΪ4*2
			���أ�
					͸�ӱ任����H����ɹ����򷵻�true�����򷵻�false
	ע��Ϊ����͸�ӱ任��from��to�ĵ㼯�еĵ�Ҫһһ��Ӧ��Ҫ�õ���͸�ӱ任��ÿ���㼯������Ҫ��4���㡣
	*****************************************************************************************************************************/
	bool Gk_FindHomography(std::vector<Gk_Point> *from, std::vector<Gk_Point> *to, double *H);
	



	bool Gk_AffineTransformTool_Point(Gk_Point *point, Gk_Point *resultPoint, double *H);




	bool Gk_AffineTransformTool_Points(std::vector<Gk_Point> *points, std::vector<Gk_Point> *resultPoints, double *H);



	

	/************************************************************************************************************************
	������		Gk_AffineTransformTool
	���ܣ�		����͸�ӱ任����H��src�еĵ��dst��
					
	������
			���룺
					src
			�����
					dst
			���أ�
					�������ɣ��򷵻�true�����򷵻�false
	ע������H��ʾ���Ǵ�dst��src��͸�ӱ任
	*****************************************************************************************************************************/
	bool Gk_AffineTransformTool_Image(IMGDATA *src, IMGDATA *dst, double *H);



#ifdef __cplusplus    
//}
#endif

#endif