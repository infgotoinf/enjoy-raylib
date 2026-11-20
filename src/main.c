#include "raylib.h"
#include "raygui.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif



// Defining constants
//--------------------------------------------------------------------------------------------------
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 574
#define FPS 60

#define GUI_TEXT_SIZE 20
#define GUI_TEXT_MARGIN 10



// Defining global variables
//--------------------------------------------------------------------------------------------------
static Texture logo;



// Functions
//--------------------------------------------------------------------------------------------------
static void UpdateDrawFrame()
{
    // Drawing
    BeginDrawing();

        ClearBackground(DARKGRAY);

        Vector2 logo_pos = { (float)(WINDOW_WIDTH - logo.width) * 0.5f, 100 };
        DrawTexture(logo, (int)logo_pos.x, (int)logo_pos.y, WHITE);

        // Draw raygui button
        static bool show_text = false;
        static const int BUTTON_WIDTH = 200;
        if (GuiButton((Rectangle){ (float)logo_pos.x + (float)(logo.width - BUTTON_WIDTH) * 0.5f
                                 , logo_pos.y + (float)logo.height + 100.f
                                 , BUTTON_WIDTH
                                 , GUI_TEXT_SIZE + GUI_TEXT_MARGIN }, "Play"))
        {
            show_text = !show_text;
        }

        if (show_text)
        {
            DrawText("Hello, World!", 200, WINDOW_HEIGHT - 200, GUI_TEXT_SIZE, WHITE);
        }

        DrawText("Hello, World!", 200, WINDOW_HEIGHT - 100, GUI_TEXT_SIZE, WHITE);

    EndDrawing();
}



//--------------------------------------------------------------------------------------------------
// Main function
//--------------------------------------------------------------------------------------------------
int main ()
{
    // Configuration and initialisation
    //----------------------------------------------------------------------------------------------
    // Set window config flags
    SetConfigFlags(
            FLAG_VSYNC_HINT          // Try enabling V-Sync on GPU
            | FLAG_WINDOW_HIGHDPI    // Support HighDPI
            | FLAG_MSAA_4X_HINT      // Try enabling MSAA 4x (smoothes image, but may cause issues)
            // | FLAG_FULLSCREEN_MODE   // Run program in fullscreen
            // | FLAG_WINDOW_RESIZABLE  // Allow resizable window
            // | FLAG_WINDOW_ALWAYS_RUN // Allow windows running while minimized
            // | FLAG_WINDOW_MINIMIZED  // Minimize window (iconify)
            // | FLAG_WINDOW_MAXIMIZED  // Maximize window (expanded to monitor)
    );

    // Create the window and OpenGL context
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World from Raylib");

    // Set text size for raygui elements
    GuiSetStyle(DEFAULT, TEXT_SIZE, GUI_TEXT_SIZE);


    // Loading textures
    //----------------------------------------------------------------------------------------------
    logo = LoadTexture("assets/logo.png");
    if (!IsTextureValid(logo)) {
        TraceLog(LOG_ERROR, "Couldn't load Texture!");
        return 0;
    }


    //----------------------------------------------------------------------------------------------
    // Main loop
    //----------------------------------------------------------------------------------------------
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, FPS, 1);
#else
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) // Detect window close button
    {
        UpdateDrawFrame();
    }
#endif


    //----------------------------------------------------------------------------------------------
    // Cleanup
    //----------------------------------------------------------------------------------------------
    // Unload textures
    UnloadTexture(logo);

    // Destroy the window and cleanup the OpenGL context
    CloseWindow();
    return 0;
}
