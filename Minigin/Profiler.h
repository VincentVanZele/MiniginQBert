// dear imgui: standalone example application for SDL2 + OpenGL
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)

#include <chrono>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#include <GL/gl.h>



#include "FlamePlot.h"
#include "backends/imgui_impl_sdl.h"

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h> // Initialize with gl3wInit()
#include <array>
#include <chrono>
#include <imgui_widget_flamegraph.h>
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

class Profiler
{
public:

    enum Stage
    {
        SdlInput,
        Plot,
        NewFrame,
        DemoWindow,
        SampleWindow,
        AnotherWindow,
        ProfilerWindow,
        ImGuiRender,
        OpenGL,
        ImGuiRenderOpenGL,
        SwapWindow,
        Rendering,

        _StageCount,
    };

    struct Scope
    {
        ImU8 _level;
        std::chrono::system_clock::time_point _start;
        std::chrono::system_clock::time_point _end;
        bool _finalized = false;
    };

    struct Entry
    {
        std::chrono::system_clock::time_point _frameStart;
        std::chrono::system_clock::time_point _frameEnd;
        std::array<Scope, _StageCount> _stages;
    };

    void Frame()
    {
        auto& prevEntry = _entries[_currentEntry];
        _currentEntry = (_currentEntry + 1) % _bufferSize;
        prevEntry._frameEnd = _entries[_currentEntry]._frameStart = std::chrono::system_clock::now();
    }

    void Begin(Stage stage)
    {
        assert(_currentLevel < 255);
        auto& entry = _entries[_currentEntry]._stages[stage];
        entry._level = _currentLevel;
        _currentLevel++;
        entry._start = std::chrono::system_clock::now();
        entry._finalized = false;
    }

    void End(Stage stage)
    {
        assert(_currentLevel > 0);
        auto& entry = _entries[_currentEntry]._stages[stage];
        assert(!entry._finalized);
        _currentLevel--;
        assert(entry._level == _currentLevel);
        entry._end = std::chrono::system_clock::now();
        entry._finalized = true;
    }

    ImU8 GetCurrentEntryIndex() const
    {
        return (_currentEntry + _bufferSize - 1) % _bufferSize;
    }

    static const ImU8 _bufferSize = 100;
    std::array<Entry, _bufferSize> _entries;

private:
    ImU8 _currentEntry = _bufferSize - 1;
    ImU8 _currentLevel = 0;
};

static const std::array<const char*, Profiler::_StageCount> stageNames = 
{
    "SDL Input",
    "Plot",
    "New Frame",
    "Demo Window",
    "Sample Window",
    "Another Window",
    "Profiler Window",
    "ImGui::Render",
    "OpenGL",
    "ImGui_ImplOpenGL3_RenderDrawData",
    "SDL_GL_SwapWindow",
    "Rendering",
};

static void ProfilerValueGetter(float* startTimestamp, float* endTimestamp, ImU8* level, const char** caption, const void* data, int idx)
{
    auto entry = reinterpret_cast<const Profiler::Entry*>(data);
    auto& stage = entry->_stages[idx];
    if (startTimestamp)
    {
        std::chrono::duration<float, std::milli> fltStart = stage._start - entry->_frameStart;
        *startTimestamp = fltStart.count();
    }
    if (endTimestamp)
    {
        *endTimestamp = stage._end.time_since_epoch().count() / 1000000.0f;

        std::chrono::duration<float, std::milli> fltEnd = stage._end - entry->_frameStart;
        *endTimestamp = fltEnd.count();
    }
    if (level)
    {
        *level = stage._level;
    }
    if (caption)
    {
        *caption = stageNames[idx];
    }
}

// Main code
int main(int, char**)
{
       // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'misc/fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    bool show_profiler_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    bool firstFrame = true;
    Profiler profiler;
    while (!done)
    {
        profiler.Frame();
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        profiler.Begin(Profiler::Stage::SdlInput);
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }
        profiler.End(Profiler::Stage::SdlInput);

        // Start the Dear ImGui frame
        profiler.Begin(Profiler::Stage::Plot);
        profiler.Begin(Profiler::Stage::NewFrame);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
        profiler.End(Profiler::Stage::NewFrame);

        // 4. Show Profiler
        profiler.Begin(Profiler::Stage::ProfilerWindow);
        if (show_profiler_window && !firstFrame)
        {
            ImGui::Begin("Profiler Window", &show_profiler_window);
            auto& entry = profiler._entries[profiler.GetCurrentEntryIndex()];
            ImGuiWidgetFlameGraph::PlotFlame("CPU", &ProfilerValueGetter, &entry, Profiler::_StageCount, 0, "Main Thread", FLT_MAX, FLT_MAX, ImVec2(400, 0));
            ImGui::End();
        }
        profiler.End(Profiler::Stage::ProfilerWindow);
        profiler.End(Profiler::Stage::Plot);

        // Rendering
        profiler.Begin(Profiler::Stage::Rendering);
        profiler.Begin(Profiler::Stage::ImGuiRender);
        ImGui::Render();
        profiler.Begin(Profiler::Stage::OpenGL);
        openGl::glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        profiler.Begin(Profiler::Stage::ImGuiRenderOpenGL);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        profiler.End(Profiler::Stage::ImGuiRenderOpenGL);
        profiler.End(Profiler::Stage::OpenGL);
        profiler.End(Profiler::Stage::ImGuiRender);
        profiler.Begin(Profiler::Stage::SwapWindow);
        SDL_GL_SwapWindow(window);
        profiler.End(Profiler::Stage::SwapWindow);
        profiler.End(Profiler::Stage::Rendering);

        firstFrame = false;
    }
}