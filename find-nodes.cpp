
#include <iostream>
#include <string.h> //strcmp()
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

#define OUTPUT_FILE "output.png"
#define WINDOW_NAME "Node Finder"

bool window = false;

Mat img;


int lower_threshold = 110;
int min_area = 35;
int max_area = 300;



void detect( int, void* )
{
    Mat working;
    Mat marked;

    // a bunch of experimentally determined values...

    bitwise_not(img, working);
    distanceTransform(working, working, CV_DIST_L2, 3);
    normalize(working, working, 0, 255, NORM_MINMAX, CV_8UC1);
    threshold(working, working, lower_threshold, 255, THRESH_BINARY);


    SimpleBlobDetector::Params params;
    params.filterByInertia     = false;
    params.filterByConvexity   = false;
    //find only white blobs
    params.filterByColor       = true;
    params.blobColor           = 255;
    //look for circles
    params.filterByCircularity = true;
    params.minCircularity      = 0.3;
    params.filterByArea        = true;
    params.minArea             = (float) min_area;
    params.maxArea             = (float) max_area;

    params.minDistBetweenBlobs = 1.0f;

    if(!window)
    {
        std::cout << "Starting detection..." << std::endl;
    }

    SimpleBlobDetector detector(params);
    vector<KeyPoint> keypoints;
    detector.detect(working, keypoints);

    std::cout << "Found " << keypoints.size() << " nodes" << std::endl;

    
    if(window)
    {
        drawKeypoints(working, keypoints, working);
        imshow(WINDOW_NAME, working);
    }
    else
    {
        drawKeypoints(img, keypoints, marked);
        imwrite(OUTPUT_FILE, marked);
        std::cout << "Wrote " << OUTPUT_FILE << std::endl;
    }
}


int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "Usage: find_nodes [options] <image-file>" << endl << endl;
        cout << "Options:" << endl << endl;
        cout << "    --window    displays the marked output in a window. WARNING:" << endl;
        cout << "                only use this with small sample images.Never use" << endl;
        cout << "                it with the full map (cuz it's freakin' huge)." << endl;
        return -1;
    }

    int img_arg = 1; //for the case without --window

    if( (argc == 3) && (strcmp(argv[1], "--window") == 0) )
    {
        img_arg = 2;
        window = true;
    }

    cout << "Loading image..." << endl;
    img = imread(argv[img_arg], IMREAD_GRAYSCALE);


    if(! img.data )
    {
        cout << "Failed to load image: " << argv[img_arg] << std::endl ;
        return -1;
    }

    if(window)
    {
        namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);

        createTrackbar("threshold",
                       WINDOW_NAME,
                       &lower_threshold,
                       255,
                       detect);

        createTrackbar("min area",
                       WINDOW_NAME,
                       &min_area,
                       500,
                       detect);

        createTrackbar("max area",
                       WINDOW_NAME,
                       &max_area,
                       500,
                       detect);
    }

    //run the initial detection
    detect(0, NULL);

    waitKey(0);
    return 0;
}
