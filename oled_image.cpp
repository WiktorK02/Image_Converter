#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>
#include <iomanip>

#define IMAGE_WIDTH 128
#define IMAGE_HEIGHT 64

using namespace cv;
using namespace std;

//bin to hex converter function
void bin_to_hex(std::string array, int itterator, int image_width, int image_height) {

	std::string binaryStr = array; // binary string
	std::bitset<8> binary(binaryStr); // convert to bitset

	// convert bitset to integer and cast to unsigned int
	unsigned int decimal = static_cast<unsigned int>(binary.to_ulong());

	// output as hex with leading 0x and leading zeroes if needed
	std::stringstream hexStream;
	hexStream << "0x" << std::setfill('0') << std::setw(2) << std::hex << decimal;
	std::string hexStr = hexStream.str();
	
	//in order to return c++ array
	if(itterator == image_height * image_width){
		std::cout << hexStr;
	}
	else{ 
		std::cout << hexStr << ", ";
	}
}

//fucnction that removes every char that is after '.' in file name 
string remove_extension(std::string& file_name) {
	 file_name = file_name.substr(0, file_name.find("."));
	 return file_name;
}

//function that write whole png byte array(base on tranparency)
void png_write_array(cv::Mat &image, std::uint8_t* pixelPtr, cv::Scalar_<uint8_t> bgrPixel, int cn, std::string file_name) {
	
	int itterator = 1;
	int byteitterator = 0;
	char valueofpixel;
	string arr;
	
	remove_extension(file_name);
	
	std::cout << "const unsigned char "<<file_name<< "[] PROGMEM = {" << endl;

	for (int i = 0; i < image.rows; i++)
	{

		for (int j = 0; j < image.cols; j++)
		{
			//bgrPixel.val[0] = pixelPtr[i * image.cols * cn + j * cn + 0]; R
			//bgrPixel.val[1] = pixelPtr[i * image.cols * cn + j * cn + 1]; G
			//bgrPixel.val[2] = pixelPtr[i * image.cols * cn + j * cn + 2]; B
			bgrPixel.val[3] = pixelPtr[i * image.cols * cn + j * cn + 3]; // Transparecy

			if (bgrPixel.val[3] == 0) {

				valueofpixel = '1';//if transparency = 0 return 1, else return 0
				arr.push_back(valueofpixel);//push to 8-bit array
			}
			else {

				valueofpixel = '0';
				arr.push_back(valueofpixel);
			}

			//every 8 bits print hex number
			if (itterator % 8 == 0) {
				bin_to_hex(arr, itterator, IMAGE_WIDTH, IMAGE_HEIGHT);
				arr = ""; // for next hexdecimal number
				byteitterator += 1;

			}
			//endl every 16 numbers
			if (itterator % 128 == 0) {

				std::cout << endl;
			}
			//tab every new line
			if (itterator % 128 == 1) {

				std::cout << "\t";
			}

			itterator++;
		}
	}
	cout << "};";//close array 
}

int main()
{
	cv::Mat image;
	
	std::string file_name = "logo.png";
	image = imread(file_name, IMREAD_UNCHANGED);
	resize(image, image, Size(IMAGE_WIDTH, IMAGE_HEIGHT), INTER_LINEAR);
	
	std::uint8_t* pixelPtr = (std::uint8_t*)image.data;
	int cn = image.channels();
	cv::Scalar_<uint8_t> bgrPixel;

	png_write_array(image, pixelPtr, bgrPixel, cn, file_name);

	return 0;
}
