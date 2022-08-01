/**
 * @file bmp.cpp
 * @author Lucas Farias
 * @brief
 * @version 0.1
 * @date 2022-04-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "bmp.hpp"

#include <array>

BMPCodec::BMPHeader BMPCodec::readHeader(std::istream &stream) {
	BMPHeader header;
	std::array<uint8_t, BMP_HEADER_LENGTH> buffer;

	// Read header bytes
	stream.read(reinterpret_cast<char *>(buffer.data()), BMP_HEADER_LENGTH);

	// Set header values
	header.signature = BMPSignature((buffer[0] << 8) | buffer[1]);
	header.file_size = (buffer[5] << 24) | (buffer[4] << 16) | (buffer[3] << 8) | buffer[2];
	header.reserved1 = (buffer[7] << 8) | buffer[6];
	header.reserved2 = (buffer[9] << 8) | buffer[8];
	header.data_offset = (buffer[13] << 24) | (buffer[12] << 16) | (buffer[11] << 8) | buffer[10];

	return header;
}

BMPCodec::BMPInfoHeader BMPCodec::readInfoHeader(std::istream &stream) {
	BMPInfoHeader header;
	std::array<uint8_t, BMP_INFO_HEADER_V5_LENGTH> buffer;

	// Read header size
	stream.read(reinterpret_cast<char *>(buffer.data()), sizeof(header.size));
	header.size = (buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | buffer[0];
	switch (header.size) {
	case BMP_INFO_HEADER_V1_LENGTH:
		header.version = BMPInfoVersion::BMPInfoVersion_V1;
		break;
	case BMP_INFO_HEADER_V2_LENGTH:
		header.version = BMPInfoVersion::BMPInfoVersion_V2;
		break;
	case BMP_INFO_HEADER_V3_LENGTH:
		header.version = BMPInfoVersion::BMPInfoVersion_V3;
		break;
	case BMP_INFO_HEADER_V4_LENGTH:
		header.version = BMPInfoVersion::BMPInfoVersion_V4;
		break;
	case BMP_INFO_HEADER_V5_LENGTH:
		header.version = BMPInfoVersion::BMPInfoVersion_V5;
		break;
	default:
		header.version = BMPInfoVersion::BMPInfoVersion_Unknown;
	}
	
	// Read remaining header bytes
	stream.read(reinterpret_cast<char *>(buffer.data() + sizeof(header.size)), header.size - sizeof(header.size));
	// Set header values
	header.width = (buffer[7] << 24) | (buffer[6] << 16) | (buffer[5] << 8) | buffer[4];
	header.height = (buffer[11] << 24) | (buffer[10] << 16) | (buffer[9] << 8) | buffer[8];
	header.planes = (buffer[13] << 8) | buffer[12];
	header.bit_count = BMPBitCount((buffer[15] << 8) | buffer[14]);
	header.compression = BMPCompression((buffer[19] << 24) | (buffer[18] << 16) | (buffer[17] << 8) | buffer[16]);
	header.image_size = (buffer[23] << 24) | (buffer[22] << 16) | (buffer[21] << 8) | buffer[20];
	header.x_resolution = (buffer[27] << 24) | (buffer[26] << 16) | (buffer[25] << 8) | buffer[24];
	header.y_resolution = (buffer[31] << 24) | (buffer[30] << 16) | (buffer[29] << 8) | buffer[28];
	header.colors_used = (buffer[35] << 24) | (buffer[34] << 16) | (buffer[33] << 8) | buffer[32];
	header.colors_important = (buffer[39] << 24) | (buffer[38] << 16) | (buffer[37] << 8) | buffer[36];

	if (header.size >= BMP_INFO_HEADER_V2_LENGTH) {
		header.red_mask = (buffer[43] << 24) | (buffer[42] << 16) | (buffer[41] << 8) | buffer[40];
		header.green_mask = (buffer[47] << 24) | (buffer[46] << 16) | (buffer[45] << 8) | buffer[44];
		header.blue_mask = (buffer[51] << 24) | (buffer[50] << 16) | (buffer[49] << 8) | buffer[48];
	}
	if (header.size >= BMP_INFO_HEADER_V3_LENGTH) {
		header.alpha_mask = (buffer[55] << 24) | (buffer[54] << 16) | (buffer[53] << 8) | buffer[52];
	}
	if (header.size >= BMP_INFO_HEADER_V4_LENGTH) {
		header.color_space = BMPColorProfile((buffer[56] << 24) | (buffer[57] << 16) | (buffer[58] << 8) | buffer[59]);
		header.red_coord.x_coord = (buffer[63] << 24) | (buffer[62] << 16) | (buffer[61] << 8) | buffer[60];
		header.red_coord.y_coord = (buffer[67] << 24) | (buffer[66] << 16) | (buffer[65] << 8) | buffer[64];
		header.red_coord.z_coord = (buffer[71] << 24) | (buffer[70] << 16) | (buffer[69] << 8) | buffer[68];
		header.green_coord.x_coord = (buffer[75] << 24) | (buffer[74] << 16) | (buffer[73] << 8) | buffer[72];
		header.green_coord.y_coord = (buffer[79] << 24) | (buffer[78] << 16) | (buffer[77] << 8) | buffer[76];
		header.green_coord.z_coord = (buffer[83] << 24) | (buffer[82] << 16) | (buffer[81] << 8) | buffer[80];
		header.blue_coord.x_coord = (buffer[87] << 24) | (buffer[86] << 16) | (buffer[85] << 8) | buffer[84];
		header.blue_coord.y_coord = (buffer[91] << 24) | (buffer[90] << 16) | (buffer[89] << 8) | buffer[88];
		header.blue_coord.z_coord = (buffer[95] << 24) | (buffer[94] << 16) | (buffer[93] << 8) | buffer[92];
		header.red_gamma = (buffer[99] << 24) | (buffer[98] << 16) | (buffer[97] << 8) | buffer[96];
		header.green_gamma = (buffer[103] << 24) | (buffer[102] << 16) | (buffer[101] << 8) | buffer[100];
		header.blue_gamma = (buffer[107] << 24) | (buffer[106] << 16) | (buffer[105] << 8) | buffer[104];
	}
	if (header.size >= BMP_INFO_HEADER_V5_LENGTH) {
		header.intent = BMPIntent((buffer[111] << 24) | (buffer[110] << 16) | (buffer[109] << 8) | buffer[108]);
		header.profile_data = (buffer[115] << 24) | (buffer[114] << 16) | (buffer[113] << 8) | buffer[112];
		header.profile_size = (buffer[119] << 24) | (buffer[118] << 16) | (buffer[117] << 8) | buffer[116];
		header.reserved = (buffer[123] << 24) | (buffer[122] << 16) | (buffer[121] << 8) | buffer[120];
	}

	return header;
}

void BMPCodec::encode(std::ostream &stream, ImageBuffer buffer) {
	throw "NotImplementedYet";
}

ImageBuffer BMPCodec::decode(std::istream &stream, size_t length) {
	if (!isImage(stream, length)) {
		throw "Not a BMP image.";
	}

	BMPHeader header = readHeader(stream);
	BMPInfoHeader info_header = readInfoHeader(stream);

	
	uint8_t *decoded = new uint8_t[info_header.width * info_header.height * (info_header.bit_count)];

	throw "NotImplementedYet";
}

bool BMPCodec::isImage(std::istream &stream, size_t length) {
	size_t rewind_pos = stream.tellg();
	BMPHeader header = readHeader(stream);
	stream.seekg(rewind_pos, std::ios::beg);

	switch (header.signature) {
	case BMPSignature::BMPSignature_BM:
	case BMPSignature::BMPSignature_BA:
	case BMPSignature::BMPSignature_CI:
	case BMPSignature::BMPSignature_CP:
	case BMPSignature::BMPSignature_IC:
	case BMPSignature::BMPSignature_PT:
		break;
	default:
		return false;
	}

	if (length != header.file_size) {
		return false;
	} else if (length < header.data_offset) { // Data offset outside of file
		return false;
	} else {
		return true;
	}
}