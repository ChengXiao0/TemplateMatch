#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include "utils.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    /*
    cout << argc << endl;
    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }*/
    if (argc != 3) {
        cout << "argv Error, please check your argv" << endl;
    }
    string templDir = argv[1];
    string imgDir = argv[2];
    cout << templDir << endl << imgDir << endl;
    vector<string> templSet = imgList(templDir);
    Mat img = imread(imgDir);
    //先打开目标图片
    Mat templ, result;      //img为待测图 templ是目标图片  result是结构图
    vector<string>::iterator it;//声明一个迭代器，来访问vector容器，作用：遍历或者指向vector容器的元素 
    for (it = templSet.begin(); it != templSet.end(); it++)
    {
        string tepmlPath = templDir + "\\" + *it;
        cout << *it << endl;
        templ = imread(tepmlPath);
        if (templ.data == NULL) {
            continue;
        }
        else {
            //resize(templ, templ, Size(65, 65));
            //1.构建结果图像resultImg(注意大小和类型)
            //如果原图(待搜索图像)尺寸为W x H, 而模版尺寸为 w x h, 则结果图像尺寸一定是(W-w+1)x(H-h+1)
            //结果图像必须为单通道32位浮点型图像
            int result_cols = img.cols - templ.cols + 1;       //result的尺寸大小
            int result_rows = img.rows - templ.rows + 1;
            result.create(result_cols, result_rows, CV_32FC1);

            //2.模版匹配
            //这里我们使用的匹配算法是标准平方差匹配 method=CV_TM_SQDIFF_NORMED，数值越小匹配度越好
            matchTemplate(img, templ, result, TM_SQDIFF_NORMED);
            //3.正则化(归一化到0-1)
            normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

            //4.找出resultImg中的最大值及其位置
            double minVal = -1;
            double maxVal;
            Point minLoc;
            Point maxLoc;
            Point matchLoc;
            cout << "匹配度：" << minVal << endl;
            // 定位极值的函数
            minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
            cout << "匹配度：" << minVal << endl;
            cout << "minPosition: " << minLoc << endl;
            cout << "maxPosition: " << maxLoc << endl;

            matchLoc = minLoc;
            //5.根据resultImg中的最大值位置在源图上画出矩形和中心点
            Point center = Point(minLoc.x + templ.cols / 2, minLoc.y + templ.rows / 2);
            rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 0), 2, 8, 0);
            circle(img, center, 2, Scalar(0, 0, 255), 2);
        }

    }
    namedWindow("img", WINDOW_NORMAL);
    imshow("img", img);
    waitKey(0);

    return 0;
}