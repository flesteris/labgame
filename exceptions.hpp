#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <sstream>
#include <SDL_ttf.h>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <exception>

class map_file_missing : public std::runtime_error
{
private:
    static std::string format_message(const std::string &filename)
    {
        std::stringstream ss;
        ss << "Map file missing: " << filename;
        return ss.str();
    }

public:
    map_file_missing(const std::string &filename) : std::runtime_error(format_message(filename)){}
};

class font_load_error : public std::runtime_error
{
private:
    static std::string format_message(const std::string &filename)
    {
        std::stringstream ss;
        ss << "Failed to load font: " << filename << " SDL_ttf Error: " << TTF_GetError();
        return ss.str();
    }

public:
    font_load_error(const std::string &filename) : std::runtime_error(format_message(filename)){}
};


class SDL_Init_error : public std::runtime_error
{
private:
    static std::string format_message()
    {
        std::stringstream ss;
        ss << "SDL_Init could not initialize! SDL_Init Error: " << SDL_GetError();
        return ss.str();
    }

public:
    SDL_Init_error() : std::runtime_error(format_message()){}
};



class TTF_Init_error : public std::runtime_error
{
private:
    static std::string format_message()
    {
        std::stringstream ss;
        ss << "SDL_TTF could not initialize! SDL_TTF Error: " << TTF_GetError();
        return ss.str();
    }

public:
    TTF_Init_error() : std::runtime_error(format_message()){}
};


class SDL_texture_error : public std::runtime_error
{
private:
    static std::string format_message()
    {
        std::stringstream ss;
        ss << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError();
        return ss.str();
    }

public:
    SDL_texture_error() : std::runtime_error(format_message()){}
};


class TTF_render_error : public std::runtime_error
{
private:
    static std::string format_message()
    {
        std::stringstream ss;
        ss << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError();
        return ss.str();
    }

public:
    TTF_render_error() : std::runtime_error(format_message()){}
};


class SDL_window_error : public std::runtime_error
{
private:
    static std::string format_message()
    {
        std::stringstream ss;
        ss << "SDL_CreateWindow Error: " << SDL_GetError();
        return ss.str();
    }

public:
    SDL_window_error() : std::runtime_error(format_message()){}
};


class SDL_renderer_error : public std::runtime_error
{
private:
    static std::string format_message()
    {
        std::stringstream ss;
        ss << "SDL_CreateRenderer Error: " << SDL_GetError();
        return ss.str();
    }

public:
    SDL_renderer_error() : std::runtime_error(format_message()){}
};


class SDL_bmp_load_error : public std::runtime_error
{
private:
    static std::string format_message(const std::string &filename)
    {
        std::stringstream ss;
        ss << "Failed to load .bmp file or its not found:" << filename << " Error: " << SDL_GetError();
        return ss.str();
    }

public:
    SDL_bmp_load_error(const std::string &filename) : std::runtime_error(format_message(filename)){}
};


#endif // EXCEPTIONS_HPP
