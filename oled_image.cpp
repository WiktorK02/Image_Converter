#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace cv;
using namespace std;

int main()
{
	Mat image;
	image = imread("Resized.png", IMREAD_UNCHANGED);
    	resize(image, image, Size(128, 64), INTER_LINEAR);
	//im = imwrite("Resized.png", image);//save file 
	int itterator = 0;
	uint8_t* pixelPtr = (uint8_t*)image.data;
	int cn = image.channels();
	Scalar_<uint8_t> bgrPixel;
	for (int i = 0; i < image.rows; i++)
	{
		int k;
		for (int j = 0; j < image.cols; j++)
		{
			bgrPixel.val[0] = pixelPtr[i * image.cols * cn + j * cn + 0]; // B
			bgrPixel.val[1] = pixelPtr[i * image.cols * cn + j * cn + 1]; // G
			bgrPixel.val[2] = pixelPtr[i * image.cols * cn + j * cn + 2]; // R

			// do something with BGR values...
			if(bgrPixel.val[0] == 255 && bgrPixel.val[1] == 255 && bgrPixel.val[2] == 255){
				k = 0;
				cout << k;
			}
			else {
				k = 1;
				cout << k;
			}
		}
	}


	return 0;
}
