#include <iostream>

#include <opencv2/opencv.hpp>

#include "filters.hpp"

using namespace std;
using namespace cv;

Mat image;

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "ERROR: You need pass one image." << "\n";
        return 1;
    }

    image = imread(argv[1], 0);

    imshow("negative", Laplacian(image));

    waitKey();
    destroyAllWindows();

    return 0;
}

