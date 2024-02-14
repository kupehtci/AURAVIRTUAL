#include "Application.h"

namespace aura{

    Application::Application() {
        _isRunning = true;
        _platform = ApplicationPlatform::MacOS;

    }

    void Application::Init() {

        // Detect platform


        // Create managers
        Renderer::Create();

        // Get references
        _renderer = Renderer::GetInstancePtr();

        // Initialize managers
        _renderer->Init();

        _isRunning = true;
    }

    void Application::Running() {
        while(_isRunning){
            _renderer->Update();

            // Handle window close
            if(glfwWindowShouldClose(_renderer->_window)){
                _isRunning = false;
            }
        }
    }

    void Application::Close(){
        _renderer->Close();
    }
}
