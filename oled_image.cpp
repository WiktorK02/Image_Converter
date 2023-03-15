#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace cv;
using namespace std;

void int_to_hex(int pixwrite, int i) {
	std::ostringstream x;
	x << "0x" << std::hex << pixwrite;
	std::string result = x.str();
	
	//if condition to seperate each pixelnumber
	if (i == 0) {
		cout << result;
	}
	else {
		cout << ","<<result;
	}
}

int main()
{
	Mat image;
	image = imread("logo.png", IMREAD_UNCHANGED);
    	resize(image, image, Size(128, 64), INTER_LINEAR);
	uint8_t* pixelPtr = (uint8_t*)image.data;
	int cn = image.channels();
	Scalar_<uint8_t> bgrPixel;

	int itterator = 0;

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			bgrPixel.val[3] = pixelPtr[i * image.cols * cn + j * cn + 3]; // Transparecy
			
			if(bgrPixel.val[3] == 0){
				int_to_hex(0, itterator);
				itterator++;
			}
			else {
				int_to_hex(1, itterator);
				itterator++;
			}
		}
	}


	return 0;
}
