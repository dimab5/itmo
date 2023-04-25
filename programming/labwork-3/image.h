#pragma once
#include "main.h"


struct Color {

    float r, g, b;
    Color ();
    Color (float r, float g, float b);

};

struct Image {

    Image (uint16_t width, uint16_t height);

    Color GetColor (uint16_t x, uint16_t y) const;

    void SetColor (const Color& col, uint16_t x, uint16_t y);

    void Export (const std :: string& path);

    uint16_t i_width;
    uint16_t i_height;
    std :: vector <Color> i_color;

};

void create (std :: vector <std :: vector <uint64_t > >& ASM, uint16_t width, uint16_t height, const std :: string& path);