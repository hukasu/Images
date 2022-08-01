/**
 * @file qoi.cpp
 * @author Lucas Farias
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "qoi.hpp"

#include <array>

#include <stdexcept>

const std::array<uint8_t, 8> QOICodec::END_MARKER = {0, 0, 0, 0, 0, 0, 0, 1};

size_t QOICodec::hashPixel(
    uint8_t r,
    uint8_t g,
    uint8_t b,
    uint8_t a
) {
    return (r * 3 + g * 5 + b * 7 + a * 11) % 64;
}

void QOICodec::seenPixel(
    std::array<std::array<uint8_t, 4>, 64> &seen,
    uint8_t r,
    uint8_t g,
    uint8_t b,
    uint8_t a
) {
    uint64_t hash = hashPixel(r, g, b, a);
}

QOICodec::QOIHeader QOICodec::readHeader(std::istream& stream) {
    QOIHeader header;
    std::array<uint8_t, QOI_HEADER_LENGTH> buffer;

    // Read header bytes
    stream.read(reinterpret_cast<char*>(buffer.data()), QOI_HEADER_LENGTH);

    // Set header values
    std::memcpy(header.magic, buffer.data(), 4);
    header.width = (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6 ] << 8) | buffer[7 ];
    header.height = (buffer[8] << 24) | (buffer[9] << 16) | (buffer[10] << 8) | buffer[11];
    header.channels = buffer[12];
    header.color_space = buffer[13];

    return header;
}

void QOICodec::encode(std::ostream& stream, ImageBuffer buffer) {
    throw "NotImplementedYet";
}

ImageBuffer QOICodec::decode(std::istream& stream, size_t length) {
    if (!isImage(stream, length)) {
        throw "Stream does not contain QOI Image";
    }

    // Read header
    QOIHeader header = readHeader(stream);

    uint8_t* decoded = new uint8_t[header.width * header.height * header.channels];

    std::array<std::array<uint8_t, 4>, 64> previous_seen;
    previous_seen.fill(std::array<uint8_t, 4> {0});
    std::array<uint8_t, 4> previous_pixel {0, 0, 0, 255};

    uint64_t pixel_count = 0;
    for (uint64_t i = 0; i < (length - QOI_HEADER_LENGTH - QOI_END_MARKER_LENGTH); ) {
        uint8_t byte;
        stream.read(reinterpret_cast<char*>(&byte), 1);
        i++;

        std::array<uint8_t, 4> cur_pixel = previous_pixel;
        uint8_t run = 1;
        if (static_cast<QOIOp>(byte) == QOIOp::QOIOp_RGB) {
            stream.read(reinterpret_cast<char*>(cur_pixel.data()), 3);
            i += 3;
            cur_pixel[3] = previous_pixel[3];
            seenPixel(previous_seen, cur_pixel[0], cur_pixel[1], cur_pixel[2], cur_pixel[3]);
        } else if (static_cast<QOIOp>(byte) == QOIOp::QOIOp_RGBA) {
            stream.read(reinterpret_cast<char*>(cur_pixel.data()), 4);
            i += 4;
            seenPixel(previous_seen, cur_pixel[0], cur_pixel[1], cur_pixel[2], cur_pixel[3]);
        } else if (static_cast<QOIOp>(byte & 0b11000000) == QOIOp::QOIOp_Index) {
            uint8_t index = (byte & 0b00111111);
            cur_pixel = previous_seen[index];
        } else if (static_cast<QOIOp>(byte & 0b11000000) == QOIOp::QOIOp_Diff) {
            uint8_t r_diff = (byte & 0b00110000) >> 4;
            uint8_t g_diff = (byte & 0b00001100) >> 2;
            uint8_t b_diff = (byte & 0b00000011);

            cur_pixel[0] += r_diff - QOI_DIFF_BIAS;
            cur_pixel[1] += g_diff - QOI_DIFF_BIAS;
            cur_pixel[2] += b_diff - QOI_DIFF_BIAS;
        } else if (static_cast<QOIOp>(byte & 0b11000000) == QOIOp::QOIOp_Luma) {
            uint8_t g_diff = (byte & 0b00111111);
            
            stream.read(reinterpret_cast<char*>(&byte), 1);
            i++;
            uint8_t r_diff = ((byte & 0b11110000) >> 4) + g_diff;
            uint8_t b_diff = (byte & 0b00001111) + g_diff;

            cur_pixel[0] += r_diff - QOI_LUMA_BIAS;
            cur_pixel[1] += g_diff - QOI_LUMA_BIAS;
            cur_pixel[2] += b_diff - QOI_LUMA_BIAS;
        } else if (static_cast<QOIOp>(byte & 0b11000000) == QOIOp::QOIOp_Run) {
            run = (byte & 0b00111111) - QOI_RUN_BIAS;
        }

        for (uint8_t j = 0; j < run; j++) {
            std::memcpy((decoded + (pixel_count * header.channels)), cur_pixel.data(), header.channels);
            pixel_count++;
        }

        previous_pixel = cur_pixel;
    }
    
    if (pixel_count != (header.width * header.height)) {
        throw "Malformed QOI file";
    }

    std::array<uint8_t, 8> end_marker;
    stream.read(reinterpret_cast<char*>(end_marker.data()), 8);

    if (end_marker != END_MARKER) {
        throw "Malformed QOI file";
    }

    if (header.channels == 3)
        return ImageBuffer(decoded, header.width, header.height, ImageFormat::ImageFormat_R8G8B8);
    else if (header.channels == 4)
        return ImageBuffer(decoded, header.width, header.height, ImageFormat::ImageFormat_R8G8B8A8);
    else
        throw "Malformed QOI file";
}

bool QOICodec::isImage(std::istream& stream, size_t length) {
    size_t rewind_pos = stream.tellg();
    QOIHeader header = readHeader(stream);
    stream.seekg(rewind_pos, std::ios::beg);

    // Checking magic
    int cmp = std::memcmp(header.magic, "qoif", 4);

    if (cmp != 0) {
        return false;
    } else if (header.channels < 3 || header.channels > 4) {
        return false;
    } else if (header.color_space > 1) {
        return false;
    } else {
        return true;
    }
}