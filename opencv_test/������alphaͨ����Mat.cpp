﻿#include <opencv2/opencv.hpp>
#include <highgui.h>
#include "opencv2/core/core.hpp"
#include <iostream>
#include <cv.h>

using namespace std;
using namespace cv;

void createAlphaMat(Mat &mat)
{
for(int i = 0; i < mat.rows; ++i) {
        for(int j = 0; j < mat.cols; ++j) {
               Vec4b&rgba = mat.at<Vec4b>(i, j);
               rgba[0]= UCHAR_MAX;
               rgba[1]= saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);
               rgba[2]= saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);
               rgba[3]= saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
        }
}
}

int main( )
{
//创建带alpha通道的Mat
Mat mat(480, 640, CV_8UC4);
createAlphaMat(mat);

vector<int>compression_params;
compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
compression_params.push_back(9);

try{
        imwrite("Alpha.png", mat, compression_params);

        namedWindow( "imageName", CV_WINDOW_AUTOSIZE );
        imshow( "imageName", mat );
}
catch(runtime_error& ex) {
        printf("图像转换成PNG格式发生错误：%s\n", ex.what());
        return 1;
}

printf("PNG图片文件的alpha数据保存完毕~\n");

waitKey(0);
return 0;
}
