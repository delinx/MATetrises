#ifndef GFXHELPER_HPP
#define GFXHELPER_HPP
#include "log.hpp"
#include "logic.hpp"
#include "raylib.h"
#include "types.hpp"
#include <iostream>

/// Visual Debug Elements
/// - Circle ticker changes color on every call
class FLIPPING_CIRCLE
{
      public:
    Color primaryColor = RED;
    Color secondaryColor = YELLOW;
    /// flips between primaryColor and secondaryColor
    void flip();
    /// raylib draw function wrapper
    void draw(i32 x, i32 y, f32 radious);
    FLIPPING_CIRCLE(Color _primaryColor, Color _secondaryColor);

      private:
    bool state = true;
    Color color = primaryColor;
};

/// lerp XY
/// Rotate
class Sprite
{
      public:
    Sprite(i32 _x, i32 _y, i32 _size, LOGIC::Grid *_grid);
    ~Sprite();

    bool Debug = false;

    i32 x;
    i32 y;

    LOGIC::Grid *grid;

    i32 size;

    void tick();
    void move(i32 _x, i32 _y);
    void moveInstant(i32 _x, i32 _y);

    void draw();

      private:
    i32 actualX;
    i32 actualY;
};

class TextPopup
{
      public:
    std::string text;
    i32 x;
    i32 y;
    i32 size;
    Color color;
    f32 displayDuration;

    TextPopup(std::string _text, i32 _x, i32 _y, i32 _size, Color _color, f32 displayDuration);
    void draw(f32 time);
};


#endif  // GFXHELPER_HPP
