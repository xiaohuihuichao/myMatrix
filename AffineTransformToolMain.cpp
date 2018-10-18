#include "Goertek_Config.h"
#include "Goertek_AffineTransformTool.h"

#include <opencv2\opencv.hpp>
#include<time.h>


char FILE_PATH[50] = "../data/numberPlate4.bmp";

char SAVE_PATH[50] = "../data/numberPlate4result.bmp";

#define WINDOWNAME			"src"

#define DSTROW						300
#define DSTCOL						800


std::vector<Gk_Point> from;
std::vector<Gk_Point> to;
Gk_Point point;
int nPoint = 0;

/*
Mat   IMGDATA
bool Gk_ImgCreateMemstorage(row, col, channels, &IMGDATA)			给IMGDATA申请内存
void Gk_ImgMensetMenstorage(&IMGDATA)										IMGDATA的数据初始化为0
bool Gk_GetImgData(Mat, &IMGDATA)												Mat -> IMGDATA
*/

void on_MouseHandle(int event, int x, int y, int flags, void *param=NULL);

int main(int argc, char **argv)
{
	//Mat img = imread(FILE_PATH, CV_LOAD_IMAGE_GRAYSCALE);
	Mat img = imread(FILE_PATH);

	if (0 == img.data)
	{
		Gk_ErrorPrint("Error in Func main: please input right image path.");
		return -1;
	}

	IMGDATA imgSrc, imgDst;

	/*CreateMemstorage*/
	if (ERROR == Gk_ImgCreateMemstorage(img.rows, img.cols, img.channels(), &imgSrc)
		|| ERROR == Gk_ImgCreateMemstorage(DSTROW, DSTCOL, img.channels(), &imgDst))
	{
		return -1;
	}

	Gk_ImgMemsetMemstorage(&imgSrc);
	Gk_ImgMemsetMemstorage(&imgDst);

	/*Get img data*/
	if (ERROR == Gk_GetImgData(img, &imgSrc))
	{
		return -1;
	}

	from.clear();
	to.clear();
	
	//左上
	Gk_Point point1;
	point1.x = 1;
	point1.y = 1;
	to.push_back(point1);

	//右上
	point1.x = DSTCOL;
	point1.y = 1;
	to.push_back(point1);

	//左下
	point1.x = 1;
	point1.y = DSTROW;
	to.push_back(point1);

	//右下
	point1.x = DSTCOL;
	point1.y = DSTROW;
	to.push_back(point1);

	namedWindow(WINDOWNAME, WINDOW_NORMAL);
	Gk_ShowImgData(&imgSrc, WINDOWNAME);

	setMouseCallback(WINDOWNAME, on_MouseHandle);
	double *H = new double[4 * 2];
	
	cout << "开始取点..." << endl;
	waitKey(0);
	cout << "取点结束" << endl;

	clock_t startTime = clock();
	if (!Gk_FindHomography(&to, &from, H))
	{
		return -1;
	}

	if (!Gk_AffineTransformTool(&imgSrc, &imgDst, H))
	{
		return -1;
	}
	clock_t time = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
	cout << "运行时间：" << time << "ms\n";

	Gk_SaveImgData(&imgDst, SAVE_PATH);
	Gk_ShowImgData(&imgDst, "dst");

	waitKey(0);
	delete[]H;
	return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void *param)
{
	if (nPoint < 4)
	{
		switch (event)
		{
		case EVENT_LBUTTONUP:
			point.x = x;
			point.y = y;
			from.push_back(point);
			++nPoint;
			cout << "Point[" << nPoint << "]:\t(" << x << ", " << y << ")\n";
			return;
		default:
			return;
		}
	}
}