#include "Renderer.h"
#include "Application.h"


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



        if (_graphicsAPI == GraphicsAPI::Vulkan && glfwVulkanSupported() == GLFW_TRUE){

            std::cout << "Vulkan is supported" << std::endl;

            PFN_vkCreateInstance pfnCreateInstance = (PFN_vkCreateInstance)glfwGetInstanceProcAddress(NULL, "vkCreateInstance");

            glfwWindowHint(GLFW_RESIZABLE, _isWindowResizable);

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Avoid OpenGL to be initialized

            _window = glfwCreateWindow((int)_windowSize.width, (int)_windowSize.height, "Aura Virtual", NULL, NULL);

            this->CreateInstance();
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
        _appInfo.pEngineName = "AURAVIRTUAL";
        _appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        _appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 2);


        unsigned int glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        if(!glfwExtensions){
            std::cout << "Failed to find platform surface extensions" << std::endl;
            //abort();
        }

        // Resolve VK_ERROR_INCOMPATIBLE_DRIVER
        if(Application::instance->_platform == ApplicationPlatform::MacOS){
            // Complete Create Info
            _createInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            _createInfo.pApplicationInfo = &_appInfo;

            uint32_t extensionCount = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

            std::cout << extensionCount << " extensions supported" << std::endl;
            std::cout << glfwExtensionCount << " glfw extensions supported" << std::endl;

            _createInfo.enabledExtensionCount = (glfwExtensionCount);
            _createInfo.ppEnabledExtensionNames = glfwExtensions;
        }
//        else if(Application::instance->_platform == ApplicationPlatform::Linux || Application::instance->_platform == ApplicationPlatform::Windows){
//
//            _createInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//            _createInfo.pApplicationInfo = &_appInfo;
//            _createInfo.enabledExtensionCount = glfwExtensionCount;
//            _createInfo.ppEnabledExtensionNames = glfwExtensions;
//            _createInfo.enabledLayerCount = 0;
//        }

        // Create instance
        VkResult instanceCreateResult = vkCreateInstance(&_createInfo, nullptr, &_vkinstance);
        if(instanceCreateResult != VkResult::VK_SUCCESS){
            std::cout << "Failed to create VkInstance" << std::endl;

            switch(instanceCreateResult){
                case VK_ERROR_INCOMPATIBLE_DRIVER:
                    std::cout << "Unable to create instance: Incompatible driver" << std::endl;
                    break;
                case VK_ERROR_OUT_OF_HOST_MEMORY:
                    std::cout << "Unable to create instance: Host out of memory" << std::endl;
                    break;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                    std::cout << "Unable to create instance: Device out of memory" << std::endl;
                    break;
                case VK_ERROR_INITIALIZATION_FAILED:
                    std::cout << "Unable to create instance: Initialization failed" << std::endl;
                    break;
                case VK_ERROR_LAYER_NOT_PRESENT:
                    std::cout << "Unable to create instance: Layer not present" << std::endl;
                    break;
                case VK_ERROR_EXTENSION_NOT_PRESENT:
                    std::cout << "Unable to create instance: Extension not present" << std::endl;
                    break;
                default:
                    std::cout << "Unable to create instance: Not defined error" << std::endl;
                    break;
            }
            //abort();
        }
        else{
            std::cout << "Success creating VKinstance" << std::endl;
        }
    }

    // endregion
}
