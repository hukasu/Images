/**
 * @file image_buffer.hpp
 * @author Lucas Farias
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef __IMAGES__BUFFER__HPP__
#define __IMAGES__BUFFER__HPP__

#include <cinttypes>

#include "image_enum.hpp"

class ImageBuffer {
    uint8_t *data;
    uint32_t width;
    uint32_t height;
    ImageFormat format;

public:
    ImageBuffer();
    ImageBuffer(uint8_t *data, uint32_t width, uint32_t height, ImageFormat format);
    ImageBuffer(const ImageBuffer &othr) = delete;
    ImageBuffer(ImageBuffer &&othr);

    ~ImageBuffer();

    ImageBuffer& operator=(ImageBuffer othr) noexcept;

    bool operator==(ImageBuffer const &othr) noexcept;
};

#endif // __IMAGES__BUFFER__HPP__
