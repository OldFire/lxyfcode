#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include "opencv2/core/core.hpp"
#include <iostream>
#include <cv.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char* imageName = "F:/qt_program/src/pic/a1.jpg";

    Mat image;
    image = imread( imageName, CV_LOAD_IMAGE_COLOR);

    if( !image.data )
    {
      printf( " No image data \n " );
      return -1;
    }

    Mat gray_image;
    cvtColor( image, gray_image, CV_BGR2GRAY );


    imwrite( "F:/qt_program/src/pic/Gray_Image.jpg", gray_image );

    namedWindow( imageName, CV_WINDOW_AUTOSIZE );
    namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

    imshow( imageName, image );
    imshow( "Gray image", gray_image );

    waitKey(0);
    return a.exec();
}
