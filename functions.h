#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>
#include <iomanip>

#define IMAGE_WIDTH 256
#define IMAGE_HEIGHT 512

void jpg_pixel_read(cv::Mat& image, std::uint8_t* pixelPtr, cv::Scalar_<uint8_t> bgrPixel, int cn, std::string file_name);
void bin_to_hex(std::string array, int itterator, int image_width, int image_height);
std::string remove_extension(std::string& file_name);
void write_array(cv::Mat& image, std::uint8_t* pixelPtr, cv::Scalar_<uint8_t> bgrPixel, int cn, std::string file_name);
void png_pixel_read(cv::Mat& image, std::uint8_t* pixelPtr, cv::Scalar_<uint8_t> bgrPixel, int cn, std::string file_name);
