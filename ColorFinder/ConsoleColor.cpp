#include "ColorFinder_Header.h"

using namespace cv;
//using namespace std;


int console(int argc, const char* argv[]) {
    // Get the path to the image, if it was given
    // if no arguments were given.

        cv::String filename;
        if (argc > 1) {
            filename = String(argv[1]);
        }

        //filename = "C:\\Users\\Esli\\Pictures\\lena.png";
        // The following lines show how to apply a colormap on a given image
        // and show it with cv::imshow example with an image. An exception is
        // thrown if the path to the image is invalid.
        if (!filename.empty()) {
            Mat img0;
            img0 = imread(filename, 1);
                
            // Throw an exception, if the image can't be read:

            if (img0.empty()) {
                std::cout << "Sample image is empty. Please adjust your path, so it points to a valid input image!";
                return -5;
            }

            imshow("Original Image", img0);



            
            //system("pause");
            waitKey(0);

            destroyAllWindows();

        }

    

    return 0;
}

/*
    // Create an empty window


    */

    //delete mode;