
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

#define MAP_IMG "map_fixed.png"
#define OUTPUT_POINTS "output.points"
#define WINDOW_NAME "Node Finder"
#define WINDOW_X 800
#define WINDOW_Y 500


bool window = false;

Mat img;

int current = 0;
Vector<KeyPoint> keypoints;
// ^ using .class_id to mark approval


void write_points(vector<KeyPoint> keypoints)
{
    ofstream f;
    f.open(OUTPUT_POINTS);

    for(KeyPoint k : keypoints)
    {
        //only write points that the user has approved
        if(k.class_id)
        {
            f << k.pt.x << ", " << k.pt.y << endl;
        }
    }

    f.close();
}

void read_points()
{
    ifstream f;
    f.open(OUTPUT_POINTS);

    while(!f.eof())
    {

    }

    f.close();
}


void display_current_point()
{
    KeyPoint p = keypoints[current];

    int x = ((int) p.pt.x) - (WINDOW_X / 2);
    int y = ((int) p.pt.y) - (WINDOW_Y / 2);

    Rect r(x, y, WINDOW_X, WINDOW_Y);

    Mat cropped = img(r);

    imshow(cropped);
}


int main()
{
    cout << "Loading image..." << endl;
    img = imread(MAP_IMG, IMREAD_GRAYSCALE);


    if(! img.data )
    {
        cout << "Failed to load image: " << MAP_IMG << std::endl ;
        return -1;
    }

    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);

    char k = 0;
    while((k != 'q') && (current >= keypoints.size()))
    {
        display_current_point();
        k = waitKey(0);

        //only the delete key will reject a point
        keypoints[current].class_id = !(k == 127);

        current++;
    }

    return 0;
}
