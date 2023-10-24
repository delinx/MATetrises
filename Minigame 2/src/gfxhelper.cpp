#include "gfxhelper.hpp"
#include <raylib.h>

void FLIPPING_CIRCLE::flip()
{
    if(state)
    {
        color = primaryColor;
        state = !state;
    }
    else
    {
        color = secondaryColor;
        state = !state;
    }
}

FLIPPING_CIRCLE::FLIPPING_CIRCLE(Color _primaryColor, Color _secondaryColor)
{
    primaryColor = _primaryColor;
    secondaryColor = _secondaryColor;
};

void FLIPPING_CIRCLE::draw(i32 x, i32 y, f32 radious)
{
    DrawCircle(x, y, radious, color);
}

void Sprite::tick()
{
    if(actualX != x)
    {
        actualX = actualX > x ? actualX - 1 : actualX + 1;
    }
    if(actualY != y)
    {
        actualY = actualY > y ? actualY - 1 : actualY + 1;
    }
}

void Sprite::move(i32 _x, i32 _y)
{
    x = _x;
    y = _y;
}

void Sprite::moveInstant(i32 _x, i32 _y)
{
    x = _x;
    y = _y;
    actualX = _x;
    actualY = _y;
}


Sprite::Sprite(i32 _x, i32 _y, i32 _size, LOGIC::Grid *_grid)
{
    x = _x;
    y = _y;
    actualX = x;
    actualY = y;
    size = _size;
    grid = _grid;

    // TODO: Convert canvas into boxes
}

Sprite::~Sprite()
{
    delete grid;
}

void Sprite::draw()
{
    for(usize gX = 0; gX < grid->WIDTH; gX++)
    {
        for(usize gY = 0; gY < grid->HEIGHT; gY++)
        {
            i32 value = grid->get(gX, gY);
            if(value != 0)
            {
                Color clr;
                // gX * size, gY * size
                switch(value)
                {
                    case 1:
                        clr = WHITE;
                        break;
                    case 100:
                        clr = Color { 30, 30, 30, 255 };
                        break;
                    case 101:
                        clr = Color { 60, 60, 60, 255 };
                        break;
                    case 10:
                        clr = Color { 100, 201, 211, 255 };
                        break;
                    case 11:
                        clr = Color { 68, 98, 165, 255 };
                        break;
                    case 12:
                        clr = Color { 240, 175, 205, 255 };
                        break;
                    case 13:
                        clr = Color { 230, 230, 70, 255 };
                        break;
                    case 14:
                        clr = Color { 100, 190, 90, 255 };
                        break;
                    case 15:
                        clr = Color { 140, 90, 170, 255 };
                        break;
                    case 16:
                        clr = Color { 230, 65, 55, 255 };
                        break;
                    case 1000:
                        clr = GOLD;
                        break;
                }
                if(value != 100 && value != 101)
                {
                    DrawRectangle(actualX + (gX * size), actualY + (gY * size), size, size, clr);

                    DrawRectangle(actualX + (gX * size) + 4, actualY + (gY * size) + 4, size - 8, size - 8, Color { 0, 0, 0, 50 });

                    DrawRectangleLinesEx(Rectangle {
                                             (f32)(actualX + (gX * size) + 4),
                                             (f32)(actualY + (gY * size) + 4),
                                             (f32)size - 8,
                                             (f32)size - 8,
                                         },
                                         1.f, GRAY);

                    DrawRectangleLinesEx(Rectangle {
                                             (f32)(actualX + (gX * size)),
                                             (f32)(actualY + (gY * size)),
                                             (f32)size,
                                             (f32)size,
                                         },
                                         1.f, DARKGRAY);
                }
                else
                {
                    DrawRectangle(actualX + (gX * size), actualY + (gY * size), size, size, clr);
                }
            }
            else
            {
                if(Debug)
                {
                    DrawRectangle(actualX + (gX * size), actualY + (gY * size), size, size, BLACK);
                }
            }
        }
    }
}
