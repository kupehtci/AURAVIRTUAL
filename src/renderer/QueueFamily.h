#pragma once
//
// Created by Daniel Laplana Gimeno on 26/2/24.
//

#ifndef AURAVIRTUAL_QUEUEFAMILY_H
#define AURAVIRTUAL_QUEUEFAMILY_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <optional>

namespace aura {

    struct QueueFamilyIndices{
        std::optional<uint32_t> _graphicsFamily;
        std::optional<uint32_t> _presentFamily;

        inline bool IsCompleted(){
            return (_graphicsFamily.has_value() && _presentFamily.has_value());
        }
    };

    class QueueFamily {

    public:
        QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);
    };

} // aura

#endif //AURAVIRTUAL_QUEUEFAMILY_H
