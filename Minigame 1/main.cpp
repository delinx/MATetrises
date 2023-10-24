#include "raylib.h"

#include "LOG.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

class Playfield
{
      public:
    struct Grid
    {
        unsigned int WIDTH;
        unsigned int HEIGHT;
        int         *grid;

        Grid(unsigned int width, unsigned int height)
        {
            WIDTH  = width;
            HEIGHT = height;
            grid   = new int[WIDTH * HEIGHT];
            for(size_t i = 0; i < WIDTH * HEIGHT; i++)
            {
                grid[i] = 0;
            }
        }
        ~Grid()
        {
            delete[] grid;
        }

        void set(unsigned int x, unsigned int y, int value)
        {
            grid[x + WIDTH * y] = value;
        }

        int get(unsigned int x, unsigned int y)
        {
            return grid[x + WIDTH * y];
        }

        void zero()
        {
            for(size_t i = 0; i < WIDTH * HEIGHT; i++)
            {
                grid[i] = 0;
            }
        }

        void fill(int num)
        {
            for(size_t i = 0; i < WIDTH * HEIGHT; i++)
            {
                grid[i] = num;
            }
        }

        void recolour(int color)
        {
            for(size_t i = 0; i < WIDTH * HEIGHT; i++)
            {
                if(grid[i] != 0)
                {
                    grid[i] = color;
                }
            }
        }
    };

    void printGrid(Grid *grid)
    {
        LOG log("debug_grid");

        std::string buffer = "Tetris grid as char array \n";
        for(unsigned int h = 0; h < grid->HEIGHT; h++)
        {
            for(unsigned int w = 0; w < grid->WIDTH; w++)
            {
                buffer += static_cast<char>(48 + grid->get(w, h));
            }
            buffer += "\n";
        }

        log.debug(buffer);
    }

    /// True: collision
    /// False: No collision
    bool checkGridCollision(Grid *gridBG, Grid *gridFG, unsigned int Px,
                            unsigned int Py)
    {
        LOG log("collision");
        // this loop returns true if we detect collison
        for(unsigned int Fx = 0; Fx < gridFG->WIDTH; Fx++)
        {
            for(unsigned int Fy = 0; Fy < gridFG->HEIGHT; Fy++)
            {
                // checking  if foreground grid is in bounds of
                // backgrgound grid
                if(Fx + Px < gridBG->WIDTH && Fy + Py < gridBG->HEIGHT)
                {
                    if(gridFG->get(Fx, Fy) != 0 &&
                       gridBG->get(Fx + Px, Fy + Py) != 0)
                    {
                        log.debug("Collided at " + std::to_string(Fx) + ":" +
                                  std::to_string(Fy) + " of shape and " +
                                  std::to_string(Fx + Px) + ":" +
                                  std::to_string(Fy + Py) +
                                  " of grid which contain [" +
                                  std::to_string(gridFG->get(Fx, Fy)) + "] and " +
                                  "[" +
                                  std::to_string(gridBG->get(Fx + Px, Fy + Py)) +
                                  "]");
                        return true;
                    }
                }
                else
                {
                    if(gridFG->get(Fx, Fy) != 0)
                    {
                        log.debug("Collided at " + std::to_string(Fx) + ":" +
                                  std::to_string(Fy) + " of shape and " +
                                  std::to_string(Fx + Px) + ":" +
                                  std::to_string(Fy + Py) +
                                  " of grid which contain [" +
                                  std::to_string(gridFG->get(Fx, Fy)) + "] and " +
                                  "[" +
                                  std::to_string(gridBG->get(Fx + Px, Fy + Py)) +
                                  "]");
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /// merges two grids
    /// gridBG has to be bigger or same size as gridFG, BG is layer 0, FG is
    /// layer
    /// 1
    Grid *mergeGrids(Grid *gridBG, Grid *gridFG, unsigned int xOffset,
                     unsigned int yOffset)
    {
        LOG   log("merging");
        Grid *tmpGrid = new Grid(gridBG->WIDTH, gridBG->HEIGHT);

        // copy background grid
        for(unsigned int Bx = 0; Bx < gridBG->WIDTH; Bx++)
        {
            for(unsigned int By = 0; By < gridBG->HEIGHT; By++)
            {
                tmpGrid->set(Bx, By, gridBG->get(Bx, By));
            }
        }

        // overlay the foreground grid on top
        for(unsigned int Fx = 0; Fx < gridFG->WIDTH; Fx++)
        {
            for(unsigned int Fy = 0; Fy < gridFG->HEIGHT; Fy++)
            {
                if(Fx + xOffset < gridBG->WIDTH &&
                   Fy + yOffset < gridBG->HEIGHT)
                {
                    int tmp = gridFG->get(Fx, Fy);
                    if(tmp != 0)
                    {
                        tmpGrid->set(Fx + xOffset, Fy + yOffset, tmp);
                    }
                }
            }
        }
        return tmpGrid;
    }

    void previewMergedGrids(Grid *gridBG, Grid *gridFG, unsigned int xOffset,
                            unsigned int yOffset)
    {
        LOG   log("preview_merged_grid");
        Grid *tmp = mergeGrids(gridBG, gridFG, xOffset, yOffset);
        printGrid(tmp);
        delete tmp;
    }

    Grid *makeShape(int shapeID)
    {  // list of all possible shapes in the neutral rotation
        // 0         1       2       3       4       5       6
        // . . . .   . . .   . . .   . X .   X X X   . . X   X . .
        // X X X X   . O X   X O .   X O X   X O X   X O X   X O X
        // . .o. .   X X .   . X X   . . .   X X X   . . .   . . .
        // . . . .
        Playfield::Grid *shape;
        switch(shapeID)
        {
            case 0:
                shape = new Grid(4, 4);
                shape->set(0, 1, 1);
                shape->set(1, 1, 1);
                shape->set(2, 1, 1);
                shape->set(3, 1, 1);
                break;
            case 1:
                shape = new Grid(3, 3);
                shape->set(1, 1, 1);
                shape->set(2, 1, 1);
                shape->set(0, 2, 1);
                shape->set(1, 2, 1);
                break;
            case 2:
                shape = new Grid(3, 3);
                shape->set(0, 1, 1);
                shape->set(1, 1, 1);
                shape->set(1, 2, 1);
                shape->set(2, 2, 1);
                break;
            case 3:
                shape = new Grid(3, 3);
                shape->set(1, 0, 1);
                shape->set(0, 1, 1);
                shape->set(1, 1, 1);
                shape->set(2, 1, 1);
                break;
            case 4:
                shape = new Grid(3, 3);
                shape->fill(1);
                break;
            case 5:
                shape = new Grid(3, 3);
                shape->set(2, 0, 1);
                shape->set(0, 1, 1);
                shape->set(1, 1, 1);
                shape->set(2, 1, 1);
                break;
            case 6:
                shape = new Grid(3, 3);
                shape->set(0, 0, 1);
                shape->set(0, 1, 1);
                shape->set(1, 1, 1);
                shape->set(2, 1, 1);
                break;
        }
        return shape;
    }

    Grid *getRandomShape()
    {
        srand((unsigned int)(time(NULL) + rand()));
        int rnd = rand() % 7;
        return makeShape(rnd);
    }

    enum ROTATION
    {
        CLOCKWISE,
        ANTICLOCKWISE
    };

    Grid *rotateShape(Grid *shape, ROTATION _rot)
    {
        // Transpose the matrix (i.e. switch index [i][j] to [j][i])
        Grid *tmpGrid    = new Grid(shape->WIDTH, shape->HEIGHT);
        Grid *resultGrid = new Grid(shape->WIDTH, shape->HEIGHT);
        for(unsigned int Sx = 0; Sx < shape->WIDTH; Sx++)
        {
            for(unsigned int Sy = 0; Sy < shape->HEIGHT; Sy++)
            {
                tmpGrid->set(Sx, Sy, shape->get(Sy, Sx));
            }
        }

        // Mirror each column (i.e. switch index [i][j] to [i][size-j])
        //
        // Mirror columns for anti-clockwise
        // Mirror rows for clockwise
        for(unsigned int Sx = 0; Sx < shape->WIDTH; Sx++)
        {
            for(unsigned int Sy = 0; Sy < shape->HEIGHT; Sy++)
            {
                if(_rot == ROTATION::ANTICLOCKWISE)
                {
                    resultGrid->set(Sx, Sy, tmpGrid->get(Sx, shape->HEIGHT - 1 - Sy));
                }
                else
                {
                    resultGrid->set(Sx, Sy, tmpGrid->get(shape->WIDTH - 1 - Sx, Sy));
                }
            }
        }

        delete tmpGrid;
        return resultGrid;
    }
};

int main()
{
    LOG log("main");
    std::cout << log.COLOR.CRESET << std::endl;

    log.debug("TetrisCrawler");
    Playfield field;

    // initicialize grids
    Playfield::Grid *backgroundGrid = new Playfield::Grid(10, 20);

    Playfield::Grid *shapeGrid = field.makeShape(6);
    // shapeGrid                    = field.rotateShape(shapeGrid, Playfield::ROTATION::CLOCKWISE);
    Playfield::Grid *DisplayGrid = new Playfield::Grid(10, 20);

    // current falling shape position
    int shapeX = 0;
    int shapeY = 0;
    // TODO: move this to tick logic, we remove old display grid and make new one
    delete DisplayGrid;
    DisplayGrid = field.mergeGrids(backgroundGrid, shapeGrid, (unsigned int)shapeX, (unsigned int)shapeY);

    InitWindow(180 * 3, 320 * 2, "T-e-t-r-i-s");

    RenderTexture2D virtualCanvasGrid = LoadRenderTexture(180, 320);
    SetTextureFilter(virtualCanvasGrid.texture, TEXTURE_FILTER_POINT);

    RenderTexture2D virtualCanvasRows = LoadRenderTexture(20, 320);
    SetTextureFilter(virtualCanvasRows.texture, TEXTURE_FILTER_POINT);

    // time for ticks
    float time = 0.0f;
    float lastTick = GetFrameTime();

    // sounds
    InitAudioDevice();  // Initialize audio device
    Sound tickSound = LoadSound("tick.wav");
    SetSoundVolume(tickSound, 0.025f);
    Sound moveSound = LoadSound("move.wav");
    SetSoundVolume(moveSound, 0.5f);
    Sound solveSound = LoadSound("solve.wav");
    SetSoundVolume(solveSound, 0.5f);

    bool fallingShape = true;
    int  stuck        = 0;
    int  move         = 0;
    int  rotate       = 0;

    const float normalSpeed = 0.250f;
    const float fastSpeed   = 0.100f;

    float tickTimeDelay = normalSpeed;

    SetTargetFPS(1000);
    while(!WindowShouldClose())
    {
        time += GetFrameTime();
        if(IsKeyPressed(KEY_RIGHT))
        {
            move = 1;
        }
        if(IsKeyPressed(KEY_LEFT))
        {
            move = -1;
        }
        if(IsKeyPressed(KEY_UP))
        {
            rotate = 1;
        }
        if(IsKeyPressed(KEY_DOWN))
        {
            rotate = -1;
        }
        if(IsKeyDown(KEY_SPACE))
        {
            tickTimeDelay = fastSpeed;
        }
        else
        {
            tickTimeDelay = normalSpeed;
        }

        if(time > lastTick + tickTimeDelay)
        {
            lastTick = time;
            PlaySound(tickSound);

            // falling logic
            // Check if we have a shape, if not spawn one
            // is there any input? If yes then check collision for that input,
            // move if allowed to move
            // if there is no input then check if we can fall down
            // if we cannot fall down and there is no input then
            // make it a part of background, and spawn new background
            // check for solved rows in background grid
            if(!fallingShape)
            {
                // check for full line, remove if found
                for(unsigned int y = 0; y < backgroundGrid->HEIGHT; y++)
                {
                    bool noEmptySpots = true;
                    for(unsigned int x = 0; x < backgroundGrid->WIDTH; x++)
                    {
                        if(backgroundGrid->get(x, y) == 0)
                        {
                            noEmptySpots = false;
                        }
                    }
                    if(noEmptySpots)
                    {
                        // TODO: remove empty row, merge
                        log.debug("Empy row at index " + std::to_string(y));
                        PlaySound(solveSound);
                        // zero out the row
                        for(unsigned int r_x = 0; r_x < backgroundGrid->WIDTH; r_x++)
                        {
                            backgroundGrid->set(r_x, y, 0);
                        }
                        // move rest of rows down
                        for(unsigned int r_y = y; r_y > 0; r_y--)
                        {
                            // log.debug("Moving down rows " + std::to_string(r_y - 1) + " to " + std::to_string(r_y));
                            for(unsigned int r_x = 0; r_x < backgroundGrid->WIDTH; r_x++)
                            {
                                backgroundGrid->set(r_x, r_y, backgroundGrid->get(r_x, r_y - 1));
                            }
                        }
                        // add score and account modifier
                        int modifier = 20 - (int)y;
                        log.info("Multiplier of " + std::to_string(modifier) + " added");
                    }
                }
                // spawn new shape if there is no current falling shape
                shapeX = 3;
                shapeY = 0;
                delete shapeGrid;
                shapeGrid = field.getRandomShape();
                shapeGrid->recolour(rand() % 7 + 1);
                DisplayGrid  = field.mergeGrids(backgroundGrid, shapeGrid, (unsigned int)shapeX, (unsigned int)shapeY);
                fallingShape = true;
            }
            else
            {
                // if there is new input for left/right movement check for legality
                if(move != 0 && stuck == 0)
                {
                    log.debug("Checking move collision " + std::to_string(move));
                    int _shapeX = shapeX + move;
                    if(!field.checkGridCollision(backgroundGrid, shapeGrid, (unsigned int)_shapeX, (unsigned int)shapeY))
                    {
                        PlaySound(moveSound);
                        shapeX = _shapeX;
                    }
                    move = 0;
                }
                // if there is new input for rotation check for legality
                if(rotate != 0 && stuck == 0)
                {
                    log.debug("Rotation call");
                    if(rotate == 1)
                    {
                        Playfield::Grid *tmp = field.rotateShape(shapeGrid, Playfield::ROTATION::CLOCKWISE);
                        if(!field.checkGridCollision(backgroundGrid, tmp, (unsigned int)shapeX, (unsigned int)shapeY))
                        {
                            log.debug("Rotation clockwise");
                            PlaySound(moveSound);
                            delete shapeGrid;
                            shapeGrid = tmp;
                        }
                        else
                        {
                            delete tmp;
                        }
                    }
                    else
                    {
                        Playfield::Grid *tmp = field.rotateShape(shapeGrid, Playfield::ROTATION::ANTICLOCKWISE);
                        if(!field.checkGridCollision(backgroundGrid, tmp, (unsigned int)shapeX, (unsigned int)shapeY))
                        {
                            log.debug("Rotation anti-clockwise");
                            PlaySound(moveSound);
                            delete shapeGrid;
                            shapeGrid = tmp;
                        }
                        else
                        {
                            delete tmp;
                        }
                    }
                    rotate = 0;
                }
                if(stuck < 2)  // if we are not considered stuck
                {
                    // check if shape can fall one step lower
                    if(!field.checkGridCollision(backgroundGrid, shapeGrid, (unsigned int)shapeX, (unsigned int)shapeY + 1))
                    {
                        DisplayGrid = field.mergeGrids(backgroundGrid, shapeGrid, (unsigned int)shapeX, (unsigned int)shapeY + 1);
                        shapeY++;
                        stuck = 0;
                    }
                    else
                    {
                        stuck += 1;
                    }
                }
                else  // we are stuck, solidify
                {
                    log.debug("We are stuck, merging");
                    backgroundGrid = field.mergeGrids(backgroundGrid, shapeGrid, (unsigned int)shapeX, (unsigned int)shapeY);
                    stuck          = 0;
                    fallingShape   = false;
                }
            }
            move   = 0;
            rotate = 0;
        }

        // virtul screen 180x320 px
        BeginTextureMode(virtualCanvasGrid);
        ClearBackground(WHITE);
        //// draw tetris grid
        bool _colorChecker = false;
        for(int y = 0; y < 20; y++)
        {
            for(int x = 0; x < 10; x++)
            {
                if(_colorChecker)
                {
                    DrawRectangle(x * 18, y * 16, 18, 16, Color { 30, 30, 30, 255 });
                }
                else
                {
                    DrawRectangle(x * 18, y * 16, 18, 16, Color { 60, 60, 60, 255 });
                }
                _colorChecker = !_colorChecker;
            }
            _colorChecker = !_colorChecker;
        }
        //// draw BG shapes and FG shape
        /// draw BG matrix
        for(unsigned int x = 0; x < DisplayGrid->WIDTH; x++)
        {
            for(unsigned int y = 0; y < DisplayGrid->HEIGHT; y++)
            {
                if(DisplayGrid->get(x, y) != 0)
                {
                    Color clr;
                    switch(DisplayGrid->get(x, y))
                    {
                        case 1:
                            clr = Color { 100, 201, 211, 255 };
                            break;
                        case 2:
                            clr = Color { 68, 98, 165, 255 };
                            break;
                        case 3:
                            clr = Color { 240, 175, 205, 255 };
                            break;
                        case 4:
                            clr = Color { 230, 230, 70, 255 };
                            break;
                        case 5:
                            clr = Color { 100, 190, 90, 255 };
                            break;
                        case 6:
                            clr = Color { 140, 90, 170, 255 };
                            break;
                        case 7:
                            clr = Color { 230, 65, 55, 255 };
                            break;
                    }
                    DrawRectangle((int)x * 18, 320 - ((int)y * 16) - 16, 18, 16, clr);
                }
            }
        }
        EndTextureMode();

        BeginTextureMode(virtualCanvasRows);
        DrawRectangle(0, 0, 20, 320, RED);
        _colorChecker = false;
        for(int y = 0; y < 20; y++)
        {
            for(int x = 0; x < 2; x++)
            {
                if(_colorChecker)
                {
                    DrawRectangle(0, y * 16, 20, 16, Color { 30, 50, 30, 255 });
                }
                else
                {
                    DrawRectangle(0, y * 16, 20, 16, Color { 60, 80, 60, 255 });
                }

                DrawText(("x" + std::to_string(20 - y)).c_str(), 2, y * 16 + 4, 1, WHITE);
                _colorChecker = !_colorChecker;
            }
            _colorChecker = !_colorChecker;
        }
        EndTextureMode();


        // scale to window
        // TODO: Scaling to any size of window
        BeginDrawing();
        ClearBackground(DARKBROWN);
        DrawTextureEx(virtualCanvasGrid.texture, Vector2 { 0.f, 0.f }, 0.f, 2.f, WHITE);
        DrawTexturePro(virtualCanvasRows.texture, Rectangle { 0.f, -0.f, 20.f, -320.f },
                       Rectangle { 36.f * 10, 0.f, 40.f, 640.f }, Vector2 { 0.f, 0.f }, 0.f, WHITE);
        DrawFPS(400, 600);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

// every collision turn we check if can move down, if cannot move down we add
// +1 to counter, any movement resets that counter, if counter reaches +2 then
// block is frozen

// TODO
// Ability to check collision for current position + offset
//
// Ideas for game elements:
// * some rows take multiple activations to trigger, so like example spawning a
// strong unit might require to trigger that row N times ( maybe even every X
// seconds activation goes backwards decreasing the progress )
//
// * sounds for every turn, sounds on fail to do action (blocked by collision),
// sound for solving something
