#pragma once
#include <libbitmap.h>
#include <iostream>
#include <string>
#include <filesystem>



struct IImageSizeExtractor{

    virtual int getWidth() const = 0;

    virtual int getHeight() const = 0;

};

class BitmapEx : public IImageSizeExtractor, public Bitmap {
public:
    BitmapEx(){}

    BitmapEx(size_t width, size_t height) {
        createBlankBitmap(width, height);
    }

    int getWidth() const override{
        return static_cast<int>(m_width);
    }

    int getHeight() const override{
        return static_cast<int>(m_height);
    }

private:
    void createBlankBitmap(size_t width, size_t height) {
        // Allocate memory for the blank bitmap
        m_buffer = new uint8_t[get_pixel_array_size(width, height, 24)];

        // Set the width and height
        m_width = width;
        m_height = height;
    }
    size_t get_pixel_array_size(size_t width, size_t height, size_t bits_per_pixel) {
        // Рассчитываем количество байтов на строку (выравнивание до байта)
        size_t bytes_per_row = ((width * bits_per_pixel + 31) / 32) * 4;

        // Общий размер массива пикселей (байты)
        return bytes_per_row * height;
    }
};

class ImageSizeExtractor: public IImageSizeExtractor {
private:
    size_t width{};
    size_t height{};

public:
    ImageSizeExtractor(const std::string& filename) : filename(filename) {
        extractSize();
    }

    int getWidth() const override{
        return width;
    }

    int getHeight() const override{
        return height;
    }

private:
    std::string filename;

    void extractSize() {
        std::filesystem::path filePath(filename);
        if (filePath.extension().string() != ".bmp" && filePath.extension().string() != ".BMP")
        {
            throw std::invalid_argument("wrong extension");
        }
        std::string stem = filePath.stem().string();
        size_t underscorePos = stem.find_last_of('_');
        size_t xPosition = stem.find('x', underscorePos);

        if (underscorePos != std::string::npos && xPosition != std::string::npos) {
            size_t countW = 0;
            size_t countH = 0;
            try {
                width = std::stoi(stem.substr(underscorePos + 1, xPosition - underscorePos - 1), &countW);
                height = std::stoi(stem.substr(xPosition + 1), &countH);
            }
            catch (...) {
                extractSizeByOpening(filePath);
            }
            if ((countH != (stem.size() - xPosition - 1)) && (countH != (xPosition = underscorePos - 1))) {
                extractSizeByOpening(filePath);
            }
        }
        else {
            extractSizeByOpening(filePath);
        }
    }

    void extractSizeByOpening(std::filesystem::path filePath)
    {

        if (!std::filesystem::exists(filePath)) {
            throw std::invalid_argument("File does not exist: " + filename);
        }

        BitmapEx bmp;
        if (!bmp.load(filename)) {
            throw std::invalid_argument("File does not exist: " + filename);
        }
        width = bmp.getWidth();
        height = bmp.getHeight();
    }
};