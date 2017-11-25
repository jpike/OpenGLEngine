#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>
#include <Windows.h>
#include "Graphics/Color.h"
#include "Graphics/OpenGL/GraphicsDevice.h"
#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/OpenGL/Renderer.h"
#include "Graphics/OpenGL/Shaders/ShaderProgram.h"
#include "Graphics/Triangle.h"
#include "Windowing/Win32Window.h"

using namespace GRAPHICS;
using namespace GRAPHICS::OPEN_GL;
using namespace GRAPHICS::OPEN_GL::SHADERS;

// GLOBALS.
// Global to provide access to them within the window procedure.
/// The window for the application.
static std::unique_ptr<WINDOWING::Win32Window> g_window = nullptr;

/// @todo   Document.
static std::unique_ptr<Renderer> g_renderer = nullptr;

/// The main window callback procedure for processing messages sent to the main application window.
/// @param[in]  window - Handle to the window.
/// @param[in]  message - The message.
/// @param[in]  w_param - Additional information depending on the type of message.
/// @param[in]  l_param - Additional information depending on the type of message.
/// @return     The result of processing the message.
LRESULT CALLBACK MainWindowCallback(
    HWND window,
    UINT message,
    WPARAM w_param,
    LPARAM l_param)
{
    LRESULT messageProcessingResult = 0;

    switch (message)
    {
        case WM_CREATE:
            break;
        case WM_SIZE:
            break;
        case WM_DESTROY:
            break;
        case WM_CLOSE:
        {
            PostQuitMessage(EXIT_SUCCESS);
            break;
        }
        case WM_ACTIVATEAPP:
            break;
        case WM_SYSKEYDOWN:
            break;
        case WM_SYSKEYUP:
            break;
        case WM_KEYUP:
            //OutputDebugString("KEYUP\n");
            break;
        case WM_KEYDOWN:
        {
            const float move_speed = 0.1f;
            int virtual_key_code = static_cast<int>(w_param);
            switch (virtual_key_code)
            {
                case VK_UP:
                    g_renderer->Camera.WorldPosition.Y += move_speed;
                    g_renderer->Camera.LookAtWorldPosition.Y += move_speed;
                    break;
                case VK_DOWN:
                    g_renderer->Camera.WorldPosition.Y -= move_speed;
                    g_renderer->Camera.LookAtWorldPosition.Y -= move_speed;
                    break;
                case VK_LEFT:
                    g_renderer->Camera.WorldPosition.X -= move_speed;
                    g_renderer->Camera.LookAtWorldPosition.X -= move_speed;
                    break;
                case VK_RIGHT:
                    g_renderer->Camera.WorldPosition.X += move_speed;
                    g_renderer->Camera.LookAtWorldPosition.X += move_speed;
                    break;
                case 0x57: // W
                    g_renderer->Camera.WorldPosition.Z -= move_speed;
                    g_renderer->Camera.LookAtWorldPosition.Z -= move_speed;
                    break;
                case 0x53: // S
                    g_renderer->Camera.WorldPosition.Z += move_speed;
                    g_renderer->Camera.LookAtWorldPosition.Z += move_speed;
                    break;
            }

            std::string camera_position;
            camera_position += std::to_string(g_renderer->Camera.WorldPosition.X) + ",";
            camera_position += std::to_string(g_renderer->Camera.WorldPosition.Y) + ",";
            camera_position += std::to_string(g_renderer->Camera.WorldPosition.Z) + "\n";
            OutputDebugString(camera_position.c_str());
            break;
        }
        /// @todo case WM_SETCURSOR:
            /// @todo break;
        case WM_PAINT:
        {
            PAINTSTRUCT paint;
            /// @todo HDC device_context = BeginPaint(window, &paint);
            BeginPaint(window, &paint);

            /// @todo   Copy rendered stuff to window here!

            EndPaint(window, &paint);
            break;
        }
        default:
            messageProcessingResult = DefWindowProcA(window, message, w_param, l_param);
            break;
    }

    return messageProcessingResult;
}

/// The entry point to the application.
/// @param[in]  application_instance - A handle to the current instance of the application.
/// @param[in]  previous_application_instance - Always NULL.
/// @param[in]  command_line_string - The command line parameters for the application.
/// @param[in]  window_show_code - Controls how the window is to be shown.
/// @return     An exit code.  0 for success.
int CALLBACK WinMain(
    HINSTANCE application_instance,
    HINSTANCE previous_application_instance,
    LPSTR command_line_string,
    int window_show_code)
{
    // REFERENCE UNUSED PARAMETERS TO PREVENT COMPILER WARNINGS.
    previous_application_instance;
    command_line_string;
    window_show_code;

    // DEFINE PARAMETERS FOR THE WINDOW TO BE CREATED.
    // The structure is zeroed-out initially since it isn't necessary to set all fields.
    WNDCLASSEX window_class = {};

    window_class.cbSize = sizeof(window_class);

    // Ensure that the window gets re-drawn when the client area is moved or re-sized.
    // A unique device context is allocated for each window in the class which can
    // potentially provide performance improvements by Windows not having to re-obtain
    // or re-allocate a device context.
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

    window_class.lpfnWndProc = MainWindowCallback;
    window_class.hInstance = application_instance;
    window_class.lpszClassName = "WindowClass";

    // CREATE THE WINDOW.
    g_window = WINDOWING::Win32Window::Create(window_class, "Window Title", 400, 400);
    bool window_created = (nullptr != g_window);
    if (!window_created)
    {
        OutputDebugString("Failed to create window.");
        return EXIT_FAILURE;
    }

    // GET THE DEVICE CONTEXT OF THE WINDOW.
    HDC device_context = GetDC(g_window->WindowHandle);
    bool device_context_retrieved = (NULL != device_context);
    if (!device_context_retrieved)
    {
        OutputDebugString("Failed to get window device context.");
        return EXIT_FAILURE;
    }

    // INITIALIZE OPEN GL.
    bool open_gl_initialized = GRAPHICS::OPEN_GL::Initialize(device_context);
    if (!open_gl_initialized)
    {
        OutputDebugString("Failed to initialize OpenGL.");
        return EXIT_FAILURE;
    }

    // CREATE THE GRAPHICS DEVICE.
    std::shared_ptr<GraphicsDevice> graphics_device = GraphicsDevice::Create(device_context);
    bool graphics_device_created = (nullptr != graphics_device);
    if (!graphics_device_created)
    {
        OutputDebugString("Failed to create the graphics device.");
        return EXIT_FAILURE;
    }

    // CREATE THE RENDERER.
    g_renderer = Renderer::Create(graphics_device);
    bool renderer_created = (nullptr != g_renderer);
    if (!renderer_created)
    {
        OutputDebugString("Failed to create the renderer.");
        return EXIT_FAILURE;
    }

    g_renderer->Camera.WorldPosition = MATH::Vector3f(0.0f, 0.0f, 1.0f);
    g_renderer->Camera.LookAtWorldPosition = MATH::Vector3f(0.0f, 0.0f, 0.0f);
    g_renderer->Camera.UpDirection = MATH::Vector3f(0.0f, 1.0f, 0.0f);

    // CREATE A TRIANGLE.
    const Color WHITE(1.0f, 1.0f, 1.0f);
    Object3D triangle = Triangle::CreateEquilateral(
        Color(1.0f, 0.0f, 0.0f),
        Color(0.0f, 1.0f, 0.0f), 
        Color(0.0f, 0.0f, 1.0f));

    // RUN A MESSAGE LOOP.
    float angle_in_radians = 0.0f;
    auto start_time = std::chrono::high_resolution_clock::now();
    bool running = true;
    while (running)
    {
        // PROCESS ANY MESSAGES FOR THE APPLICATION WINDOW.
        MSG message;
        auto message_received = [&]()
        {
            const HWND ALL_MESSAGES_FOR_CURRENT_THREAD = NULL;
            const UINT NO_MIN_MESSAGE_RESTRICTION = 0;
            const UINT NO_MAX_MESSAGE_RESTRICTION = 0;

            return PeekMessageA(
                &message,
                ALL_MESSAGES_FOR_CURRENT_THREAD,
                NO_MIN_MESSAGE_RESTRICTION,
                NO_MAX_MESSAGE_RESTRICTION,
                PM_REMOVE);
        };
        while (message_received())
        {
            // STOP RUNNING THE APPLICATION IF THE USER DECIDED TO QUIT.
            if (message.message == WM_QUIT)
            {
                running = false;
                break;
            }

            // TRANSLATE VIRTUAL KEY MESSAGES TO CHARACTER MESSAGES.
            // The return value is not checked since failure is not problematic
            // and the only thing that could be done is logging.
            TranslateMessage(&message);

            // DISPATCH THE MESSAGE TO THE WINDOW PROCEDURE.
            // The return value is simply the return value from the window procedure.
            // Nothing value could be done with it besides logging, so it is ignored.
            DispatchMessage(&message);
        }
        
        /// @todo   Update/render here!
#if 1
        auto current_time = std::chrono::high_resolution_clock::now();
        float total_elapsed_time = std::chrono::duration_cast<std::chrono::duration<float>>(current_time - start_time).count();
#endif

        g_renderer->ClearScreen(Color(0.0f, 0.0f, 0.0f, 1.0f));

        angle_in_radians = 0.5f * total_elapsed_time;
        triangle.RotationInRadians.X = MATH::Angle<float>::Radians(angle_in_radians);
        triangle.RotationInRadians.Y = MATH::Angle<float>::Radians(angle_in_radians);
        triangle.RotationInRadians.Z = MATH::Angle<float>::Radians(angle_in_radians);
        g_renderer->Draw(triangle);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            error = error;
        }

        g_renderer->DisplayScreen();
    }

    return EXIT_SUCCESS;
}