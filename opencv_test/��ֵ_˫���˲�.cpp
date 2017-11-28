#include <opencv2/opencv.hpp>
#include <highgui.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <cv.h>


using namespace cv;
using namespace std;


Mat g_srcImage,g_dstImage4,g_dstImage5;
int g_nMedianBlurValue=10;  //中值滤波参数值
int g_nBilateralFilterValue=10;  //双边滤波参数值

//轨迹条回调函数

static void on_MedianBlur(int, void *);           //中值滤波器
static void on_BilateralFilter(int, void*);       //双边滤波器


int main(  )
{
       system("color 5E");

       //载入原图
       g_srcImage= imread( "F:/qt_program/opencv_test/pics/pic1.jpg", 1 );
       if(!g_srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }

       //克隆原图到四个Mat类型中
       g_dstImage4= g_srcImage.clone( );
       g_dstImage5= g_srcImage.clone( );

       //显示原图
       namedWindow("【<0>原图窗口】", 1);
       imshow("【<0>原图窗口】",g_srcImage);


       //=================【<4>中值滤波】===========================
       //创建窗口
       namedWindow("【<4>中值滤波】", 1);
       //创建轨迹条
       createTrackbar("参数值：", "【<4>中值滤波】",&g_nMedianBlurValue, 50,on_MedianBlur );
       on_MedianBlur(g_nMedianBlurValue,0);
       //=======================================================


       //=================【<5>双边滤波】===========================
       //创建窗口
       namedWindow("【<5>双边滤波】", 1);
       //创建轨迹条
       createTrackbar("参数值：", "【<5>双边滤波】",&g_nBilateralFilterValue, 50,on_BilateralFilter);
       on_BilateralFilter(g_nBilateralFilterValue,0);
       //=======================================================


       //输出一些帮助信息
       cout<<endl<<"\t嗯。好了，请调整滚动条观察图像效果~\n\n"
              <<"\t按下“q”键时，程序退出~!\n"
              <<"\n\n\t\t\t\tby浅墨";
       while(char(waitKey(1))!= 'q') {}

       return 0;
}



//-----------------------------【on_MedianBlur( )函数】------------------------------------
//            描述：中值滤波操作的回调函数
//-----------------------------------------------------------------------------------------------
static void on_MedianBlur(int, void *)
{
       medianBlur( g_srcImage, g_dstImage4, g_nMedianBlurValue*2+1 );
       imshow("【<4>中值滤波】", g_dstImage4);
}


//-----------------------------【on_BilateralFilter( )函数】------------------------------------
//            描述：双边滤波操作的回调函数
//-----------------------------------------------------------------------------------------------
static void on_BilateralFilter(int, void *)
{
       bilateralFilter( g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2,g_nBilateralFilterValue/2 );
       imshow("【<5>双边滤波】", g_dstImage5);
}
