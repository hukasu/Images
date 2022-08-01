/**
 * @file images.hpp
 * @author Lucas Farias
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef __IMAGES__HPP__
#define __IMAGES__HPP__

#include <filesystem>
#include <ios>

#include "image_buffer.hpp"
#include "image_enum.hpp"
#include "image_encoder.hpp"
#include "image_decoder.hpp"

class Image {
    ImageBuffer buffer;
    FileFormat format;

    template<class DecoderClass>
    static Image decodeImage(std::istream& stream, size_t length) {
        DecoderClass decoder;
        return Image(decoder.decode(stream, length));
    }

public:
    Image();
    Image(ImageBuffer buffer);
    Image(const Image &othr) = delete;
    Image(Image &&othr);

    ~Image();

    Image& operator=(Image othr) noexcept;
    bool operator==(Image const &othr) noexcept;

    // Reads image from file
    static Image openImage(std::filesystem::path path, FileFormat format);
    // Reads image from stream at current cursor location and with given length
    static Image openImage(std::istream &stream, size_t length, FileFormat format);

    // Writes image to file
    void saveImage(std::filesystem::path path, FileFormat format);
    // Writes image to stream at current cursor location
    void saveImage(std::ostream &stream, FileFormat format);
};

#endif // __IMAGES__HPP__
