/**
 * @file image_encoder.hpp
 * @author Lucas Farias
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef __IMAGES__ENCODER__HPP__
#define __IMAGES__ENCODER__HPP__

#include "image_buffer.hpp"

#include <ostream>

class ImageEncoder {
public:
    virtual void encode(std::ostream& stream, ImageBuffer buffer) = 0;
};

#endif // __IMAGES__ENCODER__HPP__