#include <stdio.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"



#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 574
#define FPS 60

#define GUI_TEXT_SIZE 20
#define GUI_TEXT_MARGIN 10



int main ()
{
    // Set window config flags
    SetConfigFlags(
            FLAG_VSYNC_HINT          // Set to try enabling V-Sync on GPU
            | FLAG_WINDOW_HIGHDPI    // Set to support HighDPI
            // | FLAG_MSAA_4X_HINT      // Set to try enabling MSAA 4x (will smooth image, but may cause issues)
            // | FLAG_FULLSCREEN_MODE   // Set to run program in fullscreen
            // | FLAG_WINDOW_RESIZABLE  // Set to allow resizable window
            // | FLAG_WINDOW_ALWAYS_RUN // Set to allow windows running while minimized
            // | FLAG_WINDOW_MINIMIZED  // Set to minimize window (iconify)
            // | FLAG_WINDOW_MAXIMIZED  // Set to maximize window (expanded to monitor)
    );

    SetTargetFPS(FPS);

    // Create the window and OpenGL context
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World from Raylib");

    // Set text size for raygui elements
    GuiSetStyle(DEFAULT, TEXT_SIZE, GUI_TEXT_SIZE);

    // Load a texture from the resources directory
    Texture logo = LoadTexture("resources/logo.png");
    if (!IsTextureValid(logo)) {
        printf("Couldn't load Texture!");
        return 0;
    }

    static bool show_text = false;

    // Game loop
    while (!WindowShouldClose())  // run the loop until the user presses ESCAPE or presses the Close button on the window
    {
        // Drawing
        BeginDrawing();

            ClearBackground(DARKGRAY);

            Vector2 logo_pos = { (WINDOW_WIDTH - logo.width) * 0.5, 100 };
            DrawTexture(logo, logo_pos.x, logo_pos.y, WHITE);

            static int BUTTON_WIDTH = 200;
            if (GuiButton((Rectangle){ logo_pos.x + logo.width * 0.5 - BUTTON_WIDTH * 0.5
                                     , logo_pos.y + logo.height + 100
                                     , BUTTON_WIDTH
                                     , GUI_TEXT_SIZE + GUI_TEXT_MARGIN }, "Play"))
            {
                show_text = !show_text;
            }

            if (show_text)
            {
                DrawText("Hello, World!", 200, WINDOW_HEIGHT - 100, GUI_TEXT_SIZE, WHITE);
            }

        EndDrawing();
    }

    // Cleanup
    // Unload our texture so it can be cleaned up
    UnloadTexture(logo);

    // Destroy the window and cleanup the OpenGL context
    CloseWindow();
    return 0;
}
