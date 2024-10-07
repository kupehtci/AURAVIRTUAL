#include "Renderer.h"
#include "Application.h"
#include <iostream>
#include <vector>

//#define mDEBUG
#define vkDEBUG             // // Vulkan debug options using validation layers

namespace aura{

    Renderer::Renderer(){
        _graphicsAPI = GraphicsAPI::Vulkan;
        _window = nullptr;
        _windowSize = WindowSize();
        _isWindowResizable = true;
        _appInfo = VkApplicationInfo();
        _createInfo = VkInstanceCreateInfo();
        _enableValidationLayers = true;
        _vkphysicalDevice = VK_NULL_HANDLE;
    }

    Renderer::Renderer(int width, int height){
        _graphicsAPI = GraphicsAPI::Vulkan;
        _window = nullptr;
        _windowSize = WindowSize(width, height);
        _isWindowResizable = true;
        _appInfo = VkApplicationInfo();
        _createInfo = VkInstanceCreateInfo();
        _enableValidationLayers = true;
        _vkphysicalDevice = VK_NULL_HANDLE;
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

            // Create Vulkan instance
            this->CreateInstance();

            // Select compatible GPU for Vulkan
            PickPhysicalDevice();

            // Create Logical Device for the picked device
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
        // Actually in use
    }

    void Renderer::Close(){
        glfwDestroyWindow(_window);
        vkDestroyInstance(_vkinstance, nullptr);
        glfwTerminate();
    }

#ifdef mDEBUG
    void Renderer::Hello() {
        std::cout << "Hello from Renderer" << std::endl;
    }
#endif

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
        if(glfwExtensions == NULL){
            std::cout << "Failed to find platform surface extensions" << std::endl;
            //abort();
        }

        if(Application::instance->_platform == ApplicationPlatform::MacOS){
            // Complete Create Info
            _createInfo = {};
            _createInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            _createInfo.pApplicationInfo = &_appInfo;

#ifdef mDEBUG
            uint32_t extensionCount = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

            std::cout << extensionCount << " vk extensions supported" << std::endl;
            std::cout << glfwExtensionCount << " glfw extensions supported" << std::endl;
#endif
            // Resolve VK_ERROR_INCOMPATIBLE_DRIVER in MACOS
            const char** requiredExtensions = (const char**)malloc((glfwExtensionCount + 1) * sizeof(const char*));
            for(int i = 0; i < glfwExtensionCount; i++){
                requiredExtensions[i] = glfwExtensions[i];
            }
            requiredExtensions[glfwExtensionCount] = (VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
            _createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

            _createInfo.enabledExtensionCount = glfwExtensionCount + 1;
            _createInfo.ppEnabledExtensionNames = requiredExtensions;
        }
        else if(Application::instance->_platform == ApplicationPlatform::Linux || Application::instance->_platform == ApplicationPlatform::Windows){

            // TODO Remain to check compatibility
            _createInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            _createInfo.pApplicationInfo = &_appInfo;
            _createInfo.enabledExtensionCount = glfwExtensionCount;
            _createInfo.ppEnabledExtensionNames = glfwExtensions;
            _createInfo.enabledLayerCount = 0;
        }

        // Check vulkan validation layers
        if (_enableValidationLayers && !CheckValidationLayerSupport()) {
            std::cout << "Validation layers not avaliable" << std::endl;
            _enableValidationLayers = false;
            throw std::runtime_error("validation layers requested, but not available!");
        }

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
            abort();
        }
        else{
            std::cout << "Success creating VKinstance" << std::endl;
        }
    }

    bool Renderer::CheckValidationLayerSupport(){

        uint8_t validationLayersCount = 1;
        const char** validationLayers = (const char**)malloc(validationLayersCount * sizeof(const char*));
        validationLayers[0] = "VK_LAYER_KHRONOS_validation";

        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        // check if all of the layers in validationLayers exist in the availableLayers

        for(int i = 0; i < validationLayersCount; i++){

            const char* layerName = validationLayers[i];
            bool layerFound = false;

            for(int j = 0; j < layerCount; j++){
                if (strcmp(layerName, availableLayers[j].layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if(!layerFound){
                return false;
            }
        }

        if (_enableValidationLayers) {
            _createInfo.enabledLayerCount = 1;
            _createInfo.ppEnabledLayerNames = validationLayers;
        } else {
            _createInfo.enabledLayerCount = 0;
        }

        return true;
    }

    void Renderer::PickPhysicalDevice(){
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(_vkinstance, &deviceCount, nullptr);

        // If not there is not available GPU that suppport vulkan
        if(deviceCount == 0){
            std::cout << "Failed to find available GPUs that supports Vulkan" << std::endl;
            abort();
        }

        // Get the devices (GPUs) and check if they are suitable.
        // Then select the first one.
        VkPhysicalDevice* devices = (VkPhysicalDevice*)malloc(deviceCount * sizeof(VkPhysicalDevice));
        vkEnumeratePhysicalDevices(_vkinstance, &deviceCount, devices);

        std::cout << "Number of devices detected: " << deviceCount << std::endl;

        for(int i = 0; i < deviceCount; i++){
            if(IsDeviceSuitable(devices[i])) {
                _vkphysicalDevice = devices[i];
                break;
            }
        }

        if(_vkphysicalDevice == VK_NULL_HANDLE){
            std::cout << "Failed to find suitable GPUs that supports Vulkan" << std::endl;
            return;
        }
        free(devices);
        // At this step we have the appropriate PhysicalDevice selected and ready to use
    }

    /**
     * Check is the device is Suitable for vulkan
     * @param device
     * @return
     */
    bool Renderer::IsDeviceSuitable(VkPhysicalDevice device){

        // we need to determine the appropriate queue family that support graphics command that are implemented for the device
        QueueFamily queueFamily =  QueueFamily();
        QueueFamilyIndices indices =  queueFamily.FindQueueFamilies(device);

        if(!indices._graphicsFamily.has_value()){
            std::cout << "Graphics family has no value" << std::endl;
        }
        else{
            std::cout << "Graphics family correctly validated" << std::endl;
        }

        // Retrieve the actual evaluated device properties
        VkPhysicalDeviceProperties deviceProps;
        vkGetPhysicalDeviceProperties(device, &deviceProps);

        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        std::cout << "GPU picked: " << deviceProps.deviceName << std::endl;
        std::cout << "Max Geometry 2D avaliable: " << deviceProps.limits.maxImageDimension2D << std::endl;

        // Check if dedicated cart can render shaders
        return ((deviceProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU || deviceProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
                /*&& deviceFeatures.geometryShader*/);

    }
    // endregion
    /**
     * Find appropriate Queue family suitable for the Physical Device selected
     * @param device
     * @return
     */
    uint32_t Renderer::FindQueueFamilies(VkPhysicalDevice device){

    }
}
