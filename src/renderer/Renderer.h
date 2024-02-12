#pragma once

#ifndef AURAVIRTUAL_RENDERER_H
#define AURAVIRTUAL_RENDERER_H

#include <stdio.h>
#include <exception>
#include "Singleton.h"

//#include <vulkan/vulkan.h>
//#include <GLFW/glfw3.h>

namespace aura{

    struct WindowSize{
        int height;
        int width;
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
//        GLFWwindow* _window;

    public:

        Renderer(){
            _graphicsAPI = GraphicsAPI::Vulkan;
            //_window = nullptr;
        }

        void Init();
        void Update();
        void LateUpdate();
        void Close();

        // Testing methods
        void Hello();
    };
}


#endif //AURAVIRTUAL_RENDERER_H
