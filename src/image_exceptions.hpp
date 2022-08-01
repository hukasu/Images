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
#ifndef __IMAGES__EXCEPTIONS__HPP__
#define __IMAGES__EXCEPTIONS__HPP__

#include <sstream>

#include <stdexcept>
#include <exception>

#include <filesystem>

enum class FileFormat;

class FileNotFoundException : public std::runtime_error {
    std::filesystem::path file_path;
public:
    explicit FileNotFoundException(std::filesystem::path path)
        : std::runtime_error("No file with path was found.") {
        this->file_path = path;
    }
    virtual ~FileNotFoundException() {}
    virtual std::filesystem::path getFilePath() const {
        return file_path;
    }
};

class WrongFileFormatException : public std::runtime_error {
    FileFormat image_format;
public:
    explicit WrongFileFormatException(FileFormat image_format)
        : std::runtime_error("Could not open file with given format.") {
        this->image_format = image_format;
    }
    virtual ~WrongFileFormatException() {}
    virtual FileFormat getImageFormat() const {
        return image_format;
    }
};

class UnknownFileFormatException : public std::runtime_error {
    FileFormat image_format;
public:
    explicit UnknownFileFormatException(FileFormat image_format)
        : std::runtime_error("Unknown file format.") {
        this->image_format = image_format;
    }
    virtual ~UnknownFileFormatException() {}
    virtual FileFormat getImageFormat() const {
        return image_format;
    }
};

#endif // __IMAGES__EXCEPTIONS__HPP__