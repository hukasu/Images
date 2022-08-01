/**
 * @file image_buffer.cpp
 * @author Lucas Farias
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "image_buffer.hpp"

#include <utility>

ImageBuffer::ImageBuffer() {
    this->data = nullptr;
    this->width = 0;
    this->height = 0;
    this->format = ImageFormat::ImageFormat_UNKNOWN;
}

ImageBuffer::ImageBuffer(
    uint8_t *data,
    uint32_t width,
    uint32_t height,
    ImageFormat format
) {
    this->data = data;
    this->width = width;
    this->height = height;
    this->format = format;
}

ImageBuffer::ImageBuffer(
    ImageBuffer &&othr
) {
    this->data = std::move(othr.data);
    othr.data = nullptr;
    this->width = std::move(othr.width);
    this->height = std::move(othr.height);
    this->format = std::move(othr.format);
}

ImageBuffer::~ImageBuffer() {
    delete[] data;
}

ImageBuffer& ImageBuffer::operator=(ImageBuffer othr) noexcept {
    this->data = std::move(othr.data);
    othr.data = nullptr;
    this->width = std::move(othr.width);
    this->height = std::move(othr.height);
    this->format = std::move(othr.format);

    return *this;
}

bool ImageBuffer::operator==(ImageBuffer const &othr) noexcept {
    ImageBuffer *test = this;
    if (this != &othr) {
        return false;
    } else if (this->width != othr.width) {
        return false;
    }
    return false;
}