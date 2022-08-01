/**
 * @file enum.hpp
 * @author Lucas Farias
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef __IMAGE__ENUM__HPP__
#define __IMAGE__ENUM__HPP__

#include <cinttypes>

enum class FileFormat {
    FileFormat_UNKNOWN,
    FileFormat_BMP,
    FileFormat_QOI
};

enum class ImageFormat : uint16_t {
    ImageFormat_UNKNOWN,
    ImageFormat_R8G8B8,
    ImageFormat_B8G8R8,
    ImageFormat_R8G8B8A8,
    ImageFormat_A8B8G8R8,
};

#endif // __IMAGE__ENUM__HPP__