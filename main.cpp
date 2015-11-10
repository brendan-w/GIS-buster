
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
    Mat working;
    Mat marked;

    bitwise_not(img, working);
    distanceTransform(working, working, CV_DIST_L2, 3);
    normalize(working, working, 0, 255, NORM_MINMAX, CV_8UC1);
    threshold(working, working, 180, 255, THRESH_BINARY);


    SimpleBlobDetector::Params params;
    params.filterByInertia     = false;
    params.filterByConvexity   = false;
    //find only black
    params.filterByColor       = true;
    params.blobColor           = 0;
    //look for circles
    params.filterByCircularity = true;
    params.minCircularity      = 0.1;
    //I measured them to be about ~22 pixels in diameter
    params.filterByArea        = true;
    params.minArea             = (float) min_area;
    params.maxArea             = (float) max_area;

    params.minDistBetweenBlobs = 1.0f;


    std::cout << "Starting detection..." << std::endl;

    SimpleBlobDetector detector(params);
    vector<KeyPoint> keypoints;
    detector.detect(working, keypoints);
    drawKeypoints(img, keypoints, marked);

    std::cout << "Found " << keypoints.size() << " blobs" << std::endl;

    imshow(window_name, working);
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
