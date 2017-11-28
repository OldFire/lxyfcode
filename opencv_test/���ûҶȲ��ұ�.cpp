#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

#define QUAN_VAL          (100)

void CreateLookupTable(Mat& table, uchar quan_val)
{
    table.create(1, 256, CV_8UC1);

    uchar *p = table.data;
    for (int i = 0; i < 256; ++i)
    {
        p[i] = quan_val*(i / quan_val);
    }
}

int main(int argc, char *argv[])
{
    Mat img;
    Mat out;

    img = imread("F:/qt_program/src/pic/a1.jpg", 1);

    Mat table;//定义查找表
    //创建灰度级别是100的查找表
    CreateLookupTable(table, QUAN_VAL);
    //使用查找表直接计算出量化灰度级后的图像并将其保存到out1中
    LUT(img, table, out);

    namedWindow("源图像", CV_WINDOW_NORMAL);
    imshow("源图像", img);
    namedWindow("利用查询表灰度等级变换后", CV_WINDOW_NORMAL);
    imshow("利用查询表灰度等级变换后", out);

    waitKey(0);

    return 0;
}
