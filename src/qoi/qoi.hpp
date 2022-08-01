/**
 * @file qoi.hpp
 * @author Lucas Farias
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef __QOI__HPP__
#define __QOI__HPP__

#include <array>

#include "../image_encoder.hpp"
#include "../image_decoder.hpp"

#define QOI_HEADER_LENGTH 14
#define QOI_END_MARKER_LENGTH 8
#define QOI_DIFF_BIAS 2
#define QOI_LUMA_BIAS 32
#define QOI_RUN_BIAS -1

class QOICodec : public ImageEncoder, public ImageDecoder {
    enum class QOIOp : uint8_t {
        QOIOp_RGB = 0b11111110,
        QOIOp_RGBA = 0b11111111,
        QOIOp_Index = 0b00000000,
        QOIOp_Diff = 0b01000000,
        QOIOp_Luma = 0b10000000,
        QOIOp_Run = 0b11000000
    };
    static const std::array<uint8_t, 8> END_MARKER;
    
    struct QOIHeader {
        char magic[4];
        uint32_t width;
        uint32_t height;
        uint8_t channels;
        uint8_t color_space;
    };

    size_t hashPixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a); 
    void seenPixel(std::array<std::array<uint8_t, 4>, 64>& seen, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    QOIHeader readHeader(std::istream& stream);

public:
    virtual void encode(std::ostream& stream, ImageBuffer buffer) override;

    virtual ImageBuffer decode(std::istream& stream, size_t length) override;
    virtual bool isImage(std::istream& stream, size_t length) override;
};

#endif // __QOI__HPP__