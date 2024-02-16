#include "Application.h"

namespace aura{

    Application* Application::instance = nullptr;

    Application::Application() {
        _isRunning = true;
        _platform = ApplicationPlatform::notdefined;
        if(Application::instance == nullptr) { Application::instance = this; }
    }

    void Application::Init() {
        // Detect platform
        _platform = ApplicationPlatform::MacOS;

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

    void Application::CreateSingleton() {
        instance = this;
    }
}
