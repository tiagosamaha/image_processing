#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int Convolution(Mat image, int i, int j, int (*mask)[3]);
Mat Laplacian(Mat image);
Mat Negative(Mat image);

int Convolution(Mat image, int i, int j, int (*mask)[3]) {
    int value = 0;

    for (int k=-1; k<=1; k++) {
        for (int h=-1; h<=1; h++) {
            value += image.at<uchar>(i+k, j+h) * mask[k+1][h+1];
        }
    }

    return value;
}

Mat Laplacian(Mat image) {
    int value;
    int mask[3][3] = {{0,-1,0},{-1,4,-1},{0,-1,0}};

    Mat clone = image.clone();

    for (int i=0; i<clone.rows; i++) {
        for (int j=0; j<clone.cols; j++) {
            value = Convolution(image, i, j, mask);
            if (value < -10)
                clone.at<uchar>(i, j) = 0;
            else
                clone.at<uchar>(i, j) = 255;
        }
    }

    return clone;
}

Mat Negative(Mat image) {
    Mat clone = image.clone();

    for (int j=0; j<clone.rows; j++) {
        for (int i=0; i<clone.cols; i++) {
            clone.at<uchar>(j,i) = 255 - clone.at<uchar>(j,i);
        }
    }

    return clone;
}

