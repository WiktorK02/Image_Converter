#include "functions.h"

void jpg_pixel_read(cv::Mat& image, std::uint8_t* pixelPtr, cv::Scalar_<uint8_t> bgrPixel, int cn, std::string file_name) {

	int itterator = 1;
	int byteitterator = 0;
	char valueofpixel;
	std::string arr;

	int min_rgb_value = 0;
	int max_rgb_value = 0;

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
			int r = static_cast<int>(pixel[0]);
			int g = static_cast<int>(pixel[1]);
			int b = static_cast<int>(pixel[2]);

			//check if min and max brightness
			if ((r + g + b) > max_rgb_value) {
				max_rgb_value = (r + g + b);
			}
			if ((r + g + b) < min_rgb_value) {
				min_rgb_value = (r + g + b);
			}
		}
	}
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
			int r = static_cast<int>(pixel[0]);
			int g = static_cast<int>(pixel[1]);
			int b = static_cast<int>(pixel[2]);

			//check if avarage value is greater specific value  
			if ((r + g + b) <= 150 + (min_rgb_value + max_rgb_value) / 2) {

				valueofpixel = '0';
				arr.push_back(valueofpixel);//push to 8-bit array
			}
			else {

				valueofpixel = '1';
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

				std::cout << std::endl;
			}
			//tab every new line
			if (itterator % 128 == 1) {

				std::cout << "\t";
			}

			itterator++;
		}
	}
}

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
	if (itterator == image_height * image_width) {
		std::cout << hexStr;
	}
	else {
		std::cout << hexStr << ", ";
	}
}

std::string remove_extension(std::string& file_name) {
	file_name = file_name.substr(0, file_name.find("."));
	return file_name;
}

void png_pixel_read(cv::Mat& image, std::uint8_t* pixelPtr, cv::Scalar_<uint8_t> bgrPixel, int cn, std::string file_name) {

	int itterator = 1;
	int byteitterator = 0;
	char valueofpixel;
	std::string arr;

	for (int i = 0; i < image.rows; i++)
	{

		for (int j = 0; j < image.cols; j++)
		{
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

				std::cout << std::endl;
			}
			//tab every new line
			if (itterator % 128 == 1) {

				std::cout << "\t";
			}

			itterator++;
		}
	}
	std::cout << "};";//close array 
}

void write_array(cv::Mat& image, std::uint8_t* pixelPtr, cv::Scalar_<uint8_t> bgrPixel, int cn, std::string file_name) {

	remove_extension(file_name);
	std::cout << "const unsigned char " << file_name << "[] PROGMEM = {" << std::endl;

	//if image is .jpg do:
	jpg_pixel_read(image, pixelPtr, bgrPixel, cn, file_name);

	//if image is .png do:
	//png_pixel_read(image, pixelPtr, bgrPixel, cn, file_name);

	std::cout << "};";//close array 
}