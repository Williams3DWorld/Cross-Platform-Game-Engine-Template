#define TINYOBJLOADER_IMPLEMENTATION

#include "assets.hpp"
#include "sdl-wrapper.hpp"
#include <SDL_image.h>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <iostream>

std::string ast::assets::loadTextFile(const std::string& path)
{
    // Open a file operation handle to the asset file.
    SDL_RWops* file{SDL_RWFromFile(path.c_str(), "r")};

    // Determine how big the file is.
    size_t fileLength{static_cast<size_t>(SDL_RWsize(file))};

    // Ask SDL to load the content of the file into a data pointer.
    void* data{SDL_LoadFile_RW(file, nullptr, 1)};

    // Construct a new string based on the data pointer.
    std::string result(static_cast<char*>(data), fileLength);

    // Free up the original SDL managed data pointer.
    SDL_free(data);

    // Hand back the resulting string which is the content of the file.
    return result;
}

ast::Bitmap ast::assets::loadBitmap(const std::string& path)
{
    SDL_RWops* file{SDL_RWFromFile(path.c_str(), "rb")};
    SDL_Surface* source{IMG_Load_RW(file, 1)};
    SDL_Rect imageFrame{0, 0, source->w, source->h};

    uint32_t redMask;
    uint32_t greenMask;
    uint32_t blueMask;
    uint32_t alphaMask;

#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    redMask = 0xff000000;
    greenMask = 0x00ff0000;
    blueMask = 0x0000ff00;
    alphaMask = 0x000000ff;
#else
    redMask = 0x000000ff;
    greenMask = 0x0000ff00;
    blueMask = 0x00ff0000;
    alphaMask = 0xff000000;
#endif

    SDL_Surface* target{SDL_CreateRGBSurface(
        0,
        imageFrame.w, imageFrame.h,
        32,
        redMask, greenMask, blueMask, alphaMask)};

    SDL_BlitSurface(source, &imageFrame, target, &imageFrame);

    SDL_FreeSurface(source);

    return ast::Bitmap(target);
}
