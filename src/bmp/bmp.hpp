/**
 * @file bmp.hpp
 * @author Lucas Farias
 * @brief
 * @version 0.1
 * @date 2022-04-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#ifndef __BMP__HPP__
#define __BMP__HPP__

#include "../image_encoder.hpp"
#include "../image_decoder.hpp"

#define BMP_HEADER_LENGTH 14
#define BMP_INFO_HEADER_V1_LENGTH 40
#define BMP_INFO_HEADER_V2_LENGTH 52
#define BMP_INFO_HEADER_V3_LENGTH 56
#define BMP_INFO_HEADER_V4_LENGTH 108
#define BMP_INFO_HEADER_V5_LENGTH 124

class BMPCodec : public ImageEncoder, public ImageDecoder {
	enum class BMPInfoVersion : uint8_t {
		BMPInfoVersion_Unknown = 0,
		BMPInfoVersion_V1 = 1,
		BMPInfoVersion_V2 = 2,
		BMPInfoVersion_V3 = 3,
		BMPInfoVersion_V4 = 4,
		BMPInfoVersion_V5 = 5
	};

	enum class BMPOrientation {
		BMPOrientation_TopDown,
		BMPOrientation_BottomUp
	};

	enum class BMPSignature : uint16_t {
		BMPSignature_BM = 'BM',
		BMPSignature_BA = 'BA',
		BMPSignature_CI = 'CI',
		BMPSignature_CP = 'CP',
		BMPSignature_IC = 'IC',
		BMPSignature_PT = 'PT'
	};

	enum class BMPBitCount : uint16_t {
		BMPBitCount_Implied = 0,
		BMPBitCount_Monochrome = 1,
		BMPBitCount_16Colors = 4,
		BMPBitCount_256Colors = 8,
		BMPBitCount_A4R4B4G4 = 16,
		BMPBitCount_R8B8G8 = 24,
		BMPBitCount_A8R8B8G8 = 32
	};

	enum class BMPCompression : uint32_t {
		BMPCompression_RGB = 0,
		BMPCompression_RLE8 = 1,
		BMPCompression_RLE4 = 2,
		BMPCompression_BITFIELDS = 3,
		BMPCompression_JPEG = 4,
		BMPCompression_PNG = 5,
		BMPCompression_ALPHABITFIELDS = 6
	};
	
	enum class BMPColorProfile : uint32_t {
		BMPColorSpace_CalibratedRGB = 0,
		BMPColorSpace_sRGB = 'sRGB',
		BMPColorSpace_Windows = 'Win ',
		BMPColorSpace_ProfileLinked = 'LINK',
		BMPColorSpace_ProfileEmbeded = 'MBED'
	};

	enum class BMPIntent : uint32_t {
		BMPIntent_Business = 1,
		BMPIntent_Graphics = 2,
		BMPIntent_Images = 4,
		BMPIntent_Abs_Colorimetric = 8
	};
	
	struct BMPColorCoordinate {
		uint32_t x_coord; // 2.30 Fixed Point
		uint32_t y_coord; // 2.30 Fixed Point
		uint32_t z_coord; // 2.30 Fixed Point
	};

	struct BMPHeader {
		BMPSignature signature;
		uint32_t file_size;
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t data_offset;
	};

	struct BMPInfoHeader {
		BMPInfoVersion version;
		uint32_t size;
		int32_t width;
		int32_t height;
		uint16_t planes;
		BMPBitCount bit_count;
		BMPCompression compression;
		uint32_t image_size;
		int32_t x_resolution; // Pixels per meter
		int32_t y_resolution; // Pixels per meter
		uint32_t colors_used;
		uint32_t colors_important;
		uint32_t red_mask;
		uint32_t green_mask;
		uint32_t blue_mask;
		uint32_t alpha_mask;
		BMPColorProfile color_space;
		BMPColorCoordinate red_coord;
		BMPColorCoordinate green_coord;
		BMPColorCoordinate blue_coord;
		uint32_t red_gamma; // 16.16 Fixed Point
		uint32_t green_gamma; // 16.16 Fixed Point
		uint32_t blue_gamma; // 16.16 Fixed Point
		BMPIntent intent;
		uint32_t profile_data;
		uint32_t profile_size;
		uint32_t reserved;
	};

	BMPHeader readHeader(std::istream &stream);
	BMPInfoHeader readInfoHeader(std::istream &stream);

public:
	virtual void encode(std::ostream &stream, ImageBuffer buffer) override;

	virtual ImageBuffer decode(std::istream &stream, size_t length) override;
	virtual bool isImage(std::istream &stream, size_t length) override;
};

#endif // __BMP__HPP__