#include "image.h"


Color :: Color () : r(0), g(0), b(0) {

}

Color :: Color (float r, float g, float b) : r(r), g(g), b(b) {

}

Image :: Image (uint16_t width, uint16_t height) : i_width(width), i_height(height), i_color (std :: vector <Color> (height * width)) {

}

Color Image :: GetColor (uint16_t x, uint16_t y) const {

    return i_color[y * i_width + x];

}

void Image :: SetColor (const Color& col, uint16_t x, uint16_t y) {

    i_color[y * i_width + x].r = col.r;
    i_color[y * i_width + x].g = col.g;
    i_color[y * i_width + x].b = col.b;

}

void Image :: Export(const std :: string& path) {

    std :: ofstream file;
    file.open (path, std :: ios :: out | std :: ios :: binary);

    unsigned char bmp[3] = {0, 0, 0};
    const int cnt = ((4 - (i_width * 3) % 4) % 4);

    const int HeadSize = 14;
    const int StructHeadSize = 40;
    const int FileSize = HeadSize + StructHeadSize + i_width * i_height * 3 + cnt * i_height;

    unsigned char FileHead[HeadSize];

    FileHead[0] = 'B';
    FileHead[1] = 'M';

    FileHead[2] = FileSize;
    FileHead[3] = FileSize >> 8;
    FileHead[4] = FileSize >> 16;
    FileHead[5] = FileSize >> 24;

    FileHead[6] = 0;
    FileHead[7] = 0;
    FileHead[8] = 0;
    FileHead[9] = 0;

    FileHead[10] = HeadSize + StructHeadSize;
    FileHead[11] = 0;
    FileHead[12] = 0;
    FileHead[13] = 0;

    unsigned char StructHead[StructHeadSize];

    StructHead[0] = StructHeadSize;
    StructHead[1] = 0;
    StructHead[2] = 0;
    StructHead[3] = 0;

    StructHead[4] = i_width;
    StructHead[5] = i_width >> 8;
    StructHead[6] = i_width >> 16;
    StructHead[7] = i_width >> 24;

    StructHead[8] = i_height;
    StructHead[9] = i_height >> 8;
    StructHead[10] = i_height >> 16;
    StructHead[11] = i_height >> 24;

    StructHead[12] = 1;
    StructHead[13] = 0;

    StructHead[14] = 24;
    StructHead[15] = 0;

    for (int i = 16; i < StructHeadSize; i++)
        StructHead[i] = 0;

    file.write (reinterpret_cast <char*> (FileHead), HeadSize);
    file.write (reinterpret_cast <char*> (StructHead), StructHeadSize);

    for (uint16_t y = 0; y < i_height; y++) {
        for (uint16_t x = 0; x < i_width; x++) {

            unsigned char r = static_cast <unsigned char> (GetColor(x, y).r * 255.0f);
            unsigned char g = static_cast <unsigned char> (GetColor(x, y).g * 255.0f);
            unsigned char b = static_cast <unsigned char> (GetColor(x, y).b * 255.0f);

            unsigned char color[] = {b, g, r};

            file.write (reinterpret_cast <char*> (color), 3);

        }

        file.write(reinterpret_cast <char*> (bmp), cnt);

    }

    file.close();

}

void create (std :: vector <std :: vector <uint64_t > >& ASM, uint16_t width, uint16_t height, const std :: string& path) {

    Image image(width, height);

    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < height; x++) {

            if (ASM[x][y] == 0)
                image.SetColor (Color (1, 1, 1), x, y);

            if (ASM[x][y] == 1)
                image.SetColor (Color (0, 128, 0), x, y);

            if (ASM[x][y] == 2)
                image.SetColor (Color (128, 0, 128), x, y);

            if (ASM[x][y] == 3)
                image.SetColor (Color (1, 1, 0), x, y);

            if (ASM[x][y] > 3)
                image.SetColor (Color (0, 0, 0), x, y);

        }
    }

    image.Export(path);

}



