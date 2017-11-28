#include <opencv2/opencv.hpp>
#include <highgui.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <cv.h>


using namespace cv;
using namespace std;



int g_nContrastValue; //对比度值
int g_nBrightValue;  //亮度值
Mat g_srcImage,g_dstImage;



static void ContrastAndBright(int, void *)
{

       //创建窗口
       namedWindow("1", 1);

       //三个for循环，执行运算 g_dstImage(i,j) =a*g_srcImage(i,j) + b
       for(int y = 0; y < g_srcImage.rows; y++ )
       {
              for(int x = 0; x < g_srcImage.cols; x++ )
              {
                     for(int c = 0; c < 3; c++ )
                     {
                            g_dstImage.at<Vec3b>(y,x)[c]= saturate_cast<uchar>( (g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y,x)[c] ) + g_nBrightValue );
                     }
              }
       }

       //显示图像
       imshow("1", g_srcImage);
       imshow("2", g_dstImage);
}


int main(  )
{
       //改变控制台前景色和背景色
       system("color5F");

       //读入用户提供的图像
       g_srcImage= imread( "F:/qt_program/opencv_test/pics/pic1.jpg");
              if(!g_srcImage.data ) { printf("Oh，no，读取g_srcImage图片错误~！\n"); return false; }
       g_dstImage= Mat::zeros( g_srcImage.size(), g_srcImage.type() );

       //设定对比度和亮度的初值
       g_nContrastValue=80;
       g_nBrightValue=80;

       //创建窗口
       namedWindow("2", 1);

       //创建轨迹条
       createTrackbar("对比度：", "2",&g_nContrastValue,300,ContrastAndBright );
       createTrackbar("亮   度：","2",&g_nBrightValue,200,ContrastAndBright );

       //调用回调函数
       ContrastAndBright(g_nContrastValue,0);
       ContrastAndBright(g_nBrightValue,0);

       //输出一些帮助信息
       cout<<endl<<"\t嗯。好了，请调整滚动条观察图像效果~\n\n"
                     <<"\t按下“q”键时，程序退出~!\n"
                     <<"\n\n\t\t\t\tby浅墨";

       //按下“q”键时，程序退出
   while(char(waitKey(1)) != 'q') {}
       return 0;
}
