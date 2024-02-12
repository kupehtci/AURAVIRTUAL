#include "Renderer.h"

namespace aura{

    void Renderer::Init()
    {
        if (glfwVulkanSupported())
        {
            std::cout << "Vulkan supported" << std::endl;
        }
    }

    void Renderer::Update(){

    }

    void Renderer::LateUpdate() {

    }

    void Renderer::Close(){

    }
}
