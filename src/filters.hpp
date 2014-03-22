#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int Convolution(Mat image, int i, int j, int (*mask)[3]);
Mat Laplacian(Mat image);
Mat Gaussian(Mat image);
Mat Negative(Mat image);

int Convolution(Mat image, int i, int j, double (*mask)[3]) {
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
    double mask[3][3] = {{0,-1,0},{-1,4,-1},{0,-1,0}};

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

void CalculateGaussianMask(double kernel[][3])
{
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    double sum = 0.0;

    for (int x = -1; x <= 1; x++) {
        for(int y = -1; y <= 1; y++) {
            r = sqrt(x*x + y*y);
            kernel[x + 1][y + 1] = (exp(-(r*r)/s))/(M_PI * s);
            sum += kernel[x + 1][y + 1];
        }
    }

    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            kernel[i][j] /= sum;
}

Mat Gaussian(Mat image) {
    double mask[3][3];

    CalculateGaussianMask(mask);

    Mat clone = image.clone();

    for (int i=0; i<clone.rows; i++) {
        for (int j=0; j<clone.cols; j++) {
            clone.at<uchar>(i, j) = Convolution(image, i, j, mask);
        }
    }

    return clone;
}

