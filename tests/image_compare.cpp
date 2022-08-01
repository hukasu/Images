/**
 * @file image_compare.cpp
 * @author Lucas Farias
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string>
#include <regex>

#include "image.hpp"
#include "image_enum.hpp"

Image openFile(std::string format, std::filesystem::path path) {
    if (format == "bmp") {
        return std::move(Image::openImage(path, FileFormat::FileFormat_BMP));
    } else if (format == "qoi") {
        return std::move(Image::openImage(path, FileFormat::FileFormat_QOI));
    } else {
        throw "Unknown format";
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << "<image 1> <image 2>" << std::endl;
        std::cerr << "Images are passed as follows:" << std::endl;
        std::cerr << "\t-<format>=<path>" << std::endl;
        std::cerr << "Formats:" << std::endl;
        std::cerr << "\tbmp" << std::endl;
        std::cerr << "\tqoi" << std::endl;
        return 1;
    }

    std::regex arg_re = std::regex("-(bmp|qoi)=(.*)", std::regex_constants::extended);
    std::cmatch file1, file2;
    std::regex_search(argv[1], file1, arg_re);
    std::regex_search(argv[2], file2, arg_re);

    if (file1.size() > 0 && file2.size() > 0) {
        Image image1 = openFile(file1[1].str(), std::filesystem::path(file1[2].str()));
        Image image2 = openFile(file2[1].str(), std::filesystem::path(file2[2].str()));

        return image1 == image2;
    }

    return 1;
}