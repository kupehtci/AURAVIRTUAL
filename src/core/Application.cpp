#include "Application.h"

namespace aura{

    Application::Application() {
        _isRunning = true;
    }

    void Application::Init() {
        // Create managers
        Renderer::Create();

        // Get references
        _renderer = Renderer::GetInstancePtr();

        // Initialize managers
        _renderer->Init();
    }

    void Application::Running() {
        while(isRunning){

        }
    }

    void Application::Close(){

    }
}
