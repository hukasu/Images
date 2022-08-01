/**
 * @file images.cpp
 * @author Lucas Farias
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "image.hpp"

#include <fstream>

#include "bmp/bmp.hpp"
#include "qoi/qoi.hpp"

#include "image_exceptions.hpp"

Image::Image() {
    this->format = FileFormat::FileFormat_UNKNOWN;
}

Image::Image(ImageBuffer image_buffer) {
    this->buffer = std::move(image_buffer);
}

Image::Image(Image &&othr) {
    this->buffer = std::move(othr.buffer);
}

Image::~Image() {}

Image& Image::operator=(Image othr) noexcept {
    this->buffer = std::move(othr.buffer);

    return *this;
}

bool Image::operator==(Image const &othr) noexcept {
    return false;
}

Image Image::openImage(
    std::filesystem::path path,
    FileFormat format
) {
    if (std::filesystem::exists(path)) {
        std::ifstream file = std::ifstream(path);

        file.seekg(0, std::ios::end);
        size_t length = file.tellg();
        file.seekg(0, std::ios::beg);

        return openImage(file, length, format);
    } else {
        throw FileNotFoundException(path);
    }
}

Image Image::openImage(
    std::istream& stream,
    size_t length,
    FileFormat format
) {
    Image image;
    if (format == FileFormat::FileFormat_BMP) {
        image = decodeImage<BMPCodec>(stream, length);
    } else if (format == FileFormat::FileFormat_QOI) {
        image = decodeImage<QOICodec>(stream, length);
    } else throw UnknownFileFormatException(format);

    return std::move(image);
}

void Image::saveImage(std::filesystem::path path, FileFormat format) {
    throw "Not implemented yet";
}

void Image::saveImage(std::ostream &stream, FileFormat format) {
    throw "Not implemented yet";
}