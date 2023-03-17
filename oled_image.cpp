#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>
#include <iomanip>
using namespace cv;
using namespace std;

int main()
{
	Mat image;
	image = imread("beans.png", IMREAD_UNCHANGED);
	resize(image, image, Size(128, 64), INTER_LINEAR);
	uint8_t* pixelPtr = (uint8_t*)image.data;
	int cn = image.channels();
	Scalar_<uint8_t> bgrPixel;

	int itterator = 1;
	int bititterator = 0;
	char valueofpixel;
	string arr;
	
	for (int i = 0; i < image.rows; i++)
	{
		
		for (int j = 0; j < image.cols; j++)
		{
			//bgrPixel.val[0] = pixelPtr[i * image.cols * cn + j * cn + 0]; R
			//bgrPixel.val[1] = pixelPtr[i * image.cols * cn + j * cn + 1]; G
			//bgrPixel.val[2] = pixelPtr[i * image.cols * cn + j * cn + 2]; B
			bgrPixel.val[3] = pixelPtr[i * image.cols * cn + j * cn + 3]; // Transparecy

			if (bgrPixel.val[3] == 0) {
				
				valueofpixel = '1';
				arr.push_back(valueofpixel);//push to 8-bit array
			}
			else {
				
				valueofpixel = '0';
				arr.push_back(valueofpixel);
			}
			
			//every 8 bits
			if (itterator % 8 == 0) {

				std::string binaryStr = arr; // binary string
				std::bitset<8> binary(binaryStr); // convert to bitset

				// convert bitset to integer and cast to unsigned int
				unsigned int decimal = static_cast<unsigned int>(binary.to_ulong());

				// output as hex with leading 0x and leading zeroes if needed
				std::stringstream hexStream;
				hexStream << "0x" << std::setfill('0') << std::setw(2) << std::hex << decimal;
				std::string hexStr = hexStream.str();
				std::cout << hexStr << ", ";

				arr = ""; // for next hexdecimal number
				bititterator += 1;

			}
			//endl every 16 hex numbers
			if (bititterator == 16) {
				cout << endl;
				bititterator = 0;
			}

			itterator++;
		}
	}


	return 0;
}
