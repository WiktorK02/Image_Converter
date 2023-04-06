#include "functions.h"

int main()
{
	cv::Mat image;
	
	std::string file_name = "img6.jpg";
	image = imread(file_name, cv::IMREAD_UNCHANGED);
	resize(image, image, cv::Size(IMAGE_WIDTH, IMAGE_HEIGHT), cv::INTER_LINEAR);
	
	std::uint8_t* pixelPtr = (std::uint8_t*)image.data;
	int cn = image.channels();
	cv::Scalar_<uint8_t> bgrPixel;

	write_array(image, pixelPtr, bgrPixel, cn, file_name);
	return 0;
}

