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
    //�ȴ�Ŀ��ͼƬ
    Mat templ, result;      //imgΪ����ͼ templ��Ŀ��ͼƬ  result�ǽṹͼ
    vector<string>::iterator it;//����һ����������������vector���������ã���������ָ��vector������Ԫ�� 
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
            //1.�������ͼ��resultImg(ע���С������)
            //���ԭͼ(������ͼ��)�ߴ�ΪW x H, ��ģ��ߴ�Ϊ w x h, ����ͼ��ߴ�һ����(W-w+1)x(H-h+1)
            //���ͼ�����Ϊ��ͨ��32λ������ͼ��
            int result_cols = img.cols - templ.cols + 1;       //result�ĳߴ��С
            int result_rows = img.rows - templ.rows + 1;
            result.create(result_cols, result_rows, CV_32FC1);

            //2.ģ��ƥ��
            //��������ʹ�õ�ƥ���㷨�Ǳ�׼ƽ����ƥ�� method=CV_TM_SQDIFF_NORMED����ֵԽСƥ���Խ��
            matchTemplate(img, templ, result, TM_SQDIFF_NORMED);
            //3.����(��һ����0-1)
            normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

            //4.�ҳ�resultImg�е����ֵ����λ��
            double minVal = -1;
            double maxVal;
            Point minLoc;
            Point maxLoc;
            Point matchLoc;
            cout << "ƥ��ȣ�" << minVal << endl;
            // ��λ��ֵ�ĺ���
            minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
            cout << "ƥ��ȣ�" << minVal << endl;
            cout << "minPosition: " << minLoc << endl;
            cout << "maxPosition: " << maxLoc << endl;

            matchLoc = minLoc;
            //5.����resultImg�е����ֵλ����Դͼ�ϻ������κ����ĵ�
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