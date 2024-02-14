#include "Renderer.h"

namespace aura{

    Renderer::Renderer(){
        _graphicsAPI = GraphicsAPI::Vulkan;
        _window = nullptr;
        _windowSize = WindowSize();
        _isWindowResizable = true;
        _appInfo = VkApplicationInfo();
        _createInfo = VkInstanceCreateInfo();
    }

    Renderer::Renderer(int width, int height){
        _graphicsAPI = GraphicsAPI::Vulkan;
        _window = nullptr;
        _windowSize = WindowSize(width, height);
        _isWindowResizable = true;
        _appInfo = VkApplicationInfo();
        _createInfo = VkInstanceCreateInfo();
    }


    void Renderer::Init()
    {
        if (!glfwInit())
        {
            std::cout << "GLFW not initialized" << std::endl;
            abort();
        }


        if (true){

            if(_graphicsAPI == GraphicsAPI::Vulkan){
                // Avoid OpenGL to be initialized
                glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            }

            if(_isWindowResizable){
                glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
            }
            else {
                glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            }

            _window = glfwCreateWindow(640, 480, "GLFW CMake starter", NULL, NULL);

            uint32_t extensionCount = 0;
        }
        else{
            std::cout << "No graphics API avaliable";
            abort();
        }

    }

    void Renderer::Update(){
        while (!glfwWindowShouldClose(_window)) {
            glfwPollEvents();

            LateUpdate();
        }
    }

    void Renderer::LateUpdate() {

    }

    void Renderer::Close(){
        glfwDestroyWindow(_window);

        glfwTerminate();
    }

    void Renderer::Hello() {
        std::cout << "Hello from Renderer" << std::endl;
    }


    // region Private Methods

    void Renderer::CreateInstance() {

        // Complete Application Info
        _appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        _appInfo.pApplicationName = "AURAVIRTUAL";
        _appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        _appInfo.pEngineName = "No Engine";
        _appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        _appInfo.apiVersion = VK_API_VERSION_1_0;

        // Complete Create Info
        _createInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        _createInfo.pApplicationInfo = &_appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        _createInfo.enabledExtensionCount = glfwExtensionCount;
        _createInfo.ppEnabledExtensionNames = glfwExtensions;
        _createInfo.enabledLayerCount = 0;

        // Create instance
        if(vkCreateInstance(&_createInfo, nullptr, &_vkinstance) != VkResult::VK_SUCCESS){
            std::cout << "Failed to create VkInstance" << std::endl;
            abort();
        }
    }

    // endregion
}
