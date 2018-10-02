#include <iostream>
#include <fstream>
#include <string>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"

int main(int argc, char** argv) {
     cv::Mat img_rs;
//     const int MAX_SIZE = 255;
//     char* filename[MAX_SIZE];
     const cv::String keys =
	     "{help h     |      | Prints help message      }"
	     "{@image 	   |      | image used for resizing  }"
          "{@height    |50    | Sets the height of image }"
	     "{@width     |50    | Sets the width of image  }"
	     "{path       |.     | path to image files      }";

     cv::CommandLineParser parser(argc, argv, keys);

     // If Help is passed, output help message
     if (parser.has("help")) {
     	parser.printMessage();
     }

     // Grabs image from Command Parser for reimaging
     cv::String img_name = parser.get<cv::String>(0);
     cv::Mat img = cv::imread("/home/kryptic/OpenCV_Practice/index.png");
     cv::resize(img, img_rs, cv::Size(parser.get<double>(1),parser.get<double>(2)),
                0, 0, cv::INTER_NEAREST);

     // Checks if parser has thrown any errors
     if (!parser.check()) {
          parser.printErrors();
          return 0;
     }

     // Parameters to compress image to PNG
     std::vector<int> compression_params;
     compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
     compression_params.push_back(9);

     // Writes image to location
	cv::imwrite("Test.png", img_rs);

     return 0;
}
