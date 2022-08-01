/**
 * @file image_decoder.hpp
 * @author Lucas Farias
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef __IMAGES__DECODER__HPP__
#define __IMAGES__DECODER__HPP__

#include "image_buffer.hpp"

#include <istream>

class ImageDecoder {
public:
    // Decodes image
    virtual ImageBuffer decode(std::istream& stream, size_t length) = 0;
    // Tests if image is of correct format
    virtual bool isImage(std::istream& stream, size_t length) = 0;
};

#endif // __IMAGES__DECODER__HPP__
