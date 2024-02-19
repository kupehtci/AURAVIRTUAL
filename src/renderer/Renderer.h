#pragma once

#ifndef AURAVIRTUAL_RENDERER_H
#define AURAVIRTUAL_RENDERER_H

#include <stdio.h>
#include <exception>
//#include "ApplicationPlatform.h"
#include "Singleton.h"

//#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


namespace aura{

    struct WindowSize{
        uint16_t height;
        uint16_t width;

        WindowSize(){
            height = 480;
            width = 600;
        }

        WindowSize(int w, int h){
            width = w;
            height = h;
        }
    };

    struct Color{
        uint8_t r;
        uint8_t g;
        uint8_t b;

        Color() : r(0), g(0), b(0){}
        Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}
    };

    enum GraphicsAPI{ Vulkan = 0, SDL, none};

    class Renderer: public Singleton<Renderer>{
    public:
        GraphicsAPI _graphicsAPI;
        GLFWwindow* _window;
        WindowSize _windowSize;
        bool _isWindowResizable;

        VkApplicationInfo _appInfo;
        VkInstanceCreateInfo _createInfo;
        VkInstance _vkinstance;
        VkPhysicalDevice _vkphysicalDevice;

    private:
        bool _enableValidationLayers;

    public:

        Renderer();
        Renderer(int width, int height);

        void Init();
        void Update();
        void LateUpdate();
        void Close();

        // Testing methods
        void Hello();

    private:
        void CreateInstance();
        bool CheckValidationLayerSupport();
        void PickPhysicalDevice();

        // Getters and setters
        inline bool AreValidationLayersEnabled(){
            return _enableValidationLayers;
        }


        // Usable methods

    private:
        bool IsDeviceSuitable(VkPhysicalDevice device);
    };
}


#endif //AURAVIRTUAL_RENDERER_H
