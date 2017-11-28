#include <opencv2/opencv.hpp>
#include <highgui.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <cv.h>

using namespace cv;
using namespace std;

//
int main()
{
    Mat girl=imread("F:/qt_program/opencv_test/pics/girl.png"); //载入图像到Mat
    namedWindow("1"); //创建一个名为 "【1】动漫图"的窗口
    imshow("1",girl);//显示名为 "【1】动漫图"的窗口

    //-----------------------------------【二、初级图像混合】--------------------------------------
    //     描述：二、初级图像混合
    //-----------------------------------------------------------------------------------------------
    //载入图片
    Mat image= imread("F:/qt_program/opencv_test/pics/game.png");
    namedWindow("2");
    imshow("2",image);

    Mat logo= imread("F:/qt_program/opencv_test/pics/logo.png");
    namedWindow("3");
    imshow("3",logo);

    //定义一个Mat类型，用于存放，图像的ROI
    Mat imageROI;
    //方法一
    imageROI=image(Rect(600,280,logo.cols,logo.rows));


    //方法二
    //imageROI=image(Range(250,250+logo.rows),Range(300,300+logo.cols));

    //将logo加到原图上
    addWeighted(imageROI,0.5,logo,0.3,0.,imageROI);

    //显示结果
    namedWindow("4");
    imshow("4",image);

//    -----------------------------------【三、图像的输出】--------------------------------------
//         描述：将一个Mat图像输出到图像文件
//    -----------------------------------------------------------------------------------------------
 //   输出一张jpg图片到工程目录下
    imwrite("dota_logo.jpg",image);

    waitKey();

    return 0;
}
