/*
Converts images to 50x50 .PNG for Cascade learning
To run program correctly, pass the name of image in pos_img when running
EX:  ./Format_IMG Test.jpg
*/

#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"

int main(int argc, char** argv) {
     cv::Mat img_rs;
//     const int MAX_SIZE = 255; TEST
//     char* filename[MAX_SIZE]; TEST
     const cv::String keys =
	     "{help h     |                    | Prints help message     }"
	     "{@image 	   |<none>              | image used for resizing }"
          "{@height    |50                  | Sets the height of image}"
	     "{@width     |50                  | Sets the width of image }"
	     "{path       |../img/pos_img/     | path to image files     }"
          "{new_path   |../img/cvt_pos_img/ | New path for imgs       }";

     cv::CommandLineParser parser(argc, argv, keys);

     // If Help is passed, output help message
     if (parser.has("help")) {
     	parser.printMessage();
     }

     // Grabs image from Command Parser for reimaging
     cv::String img_name = parser.get<cv::String>(0);
     cv::String img_path = parser.get<cv::String>("path");
     cv::String img_np   = parser.get<cv::String>("new_path");

     cv::String img_fp   = img_path + img_name;
     cv::String img_nfp  = img_np + img_name;

     // Concatinate ending extension
     std::size_t ext_loc = img_name.find(".jpeg");
     std::cout << ext_loc;

     cv::Mat img = cv::imread(img_fp);
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
     try {
	 cv::imwrite((img_nfp + ".png"), img_rs, compression_params);
      // Move file to new location
     }
     catch (cv::Exception& ex) {
	 fprintf(stderr, "Exception coverting image to PNG: %s\n",
		 ex.what());
	 return 1;
     }

     // CATCH move file to new location

     return 0;
}