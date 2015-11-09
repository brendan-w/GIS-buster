
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;


char* window_name = "Node Finder";

int min_area = 1;
int max_area = 500;

Mat img;


void detect( int, void* )
{
    Mat marked;

    bitwise_not(img, marked);
    distanceTransform(marked, marked, CV_DIST_L2, 3);
    normalize(marked, marked, 0.0, 1.0, NORM_MINMAX);
    threshold(marked, marked, 0.75, 1.0, THRESH_BINARY);

    std::cout << "Found " << 0 << " blobs" << std::endl;

    imshow(window_name, marked);
}


int main(int argc, char* argv[])
{
    // if( argc != 2)
    // {
    //     cout << "Usage: find_nodes map_fixed.png" << endl;
    //     return -1;
    // }

    // img = imread(argv[1], IMREAD_GRAYSCALE);
    img = imread("small_map_fixed.png", IMREAD_GRAYSCALE);

    if(! img.data )
    {
        cout << "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow(window_name, WINDOW_AUTOSIZE);

    createTrackbar( "min area",
                    window_name, &min_area,
                    500, detect );

    createTrackbar( "max area",
                    window_name, &max_area,
                    500, detect );

    detect(0, NULL);

    waitKey(0);
    return 0;
}
