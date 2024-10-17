//
// Created by Daniel Laplana Gimeno on 26/2/24.
//
#include "QueueFamily.h"

#include <vector>
#include <iostream>

namespace aura {

    QueueFamilyIndices QueueFamily::FindQueueFamilies(const VkPhysicalDevice& device/*, const VkSurfaceKHR& surface*/){
        QueueFamilyIndices indices;

        //|-------------------------------------------|
        //|         PREVIOUS QUEUE VALIDATION         |
        //|-------------------------------------------|
//        // Get queue families
//        uint32_t familyCount = 0;
//        vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, nullptr);
//        std::vector<VkQueueFamilyProperties> families(familyCount);
//        vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, families.data());
//
//        // Iterate through families until one that supports requirements is found
//        bool found = false;
//        for (int i = 0; !found && i < families.size(); ++i) {
//            const auto& family = families[i];
//
//            // Check for graphics support
//            if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
//                indices._graphicsFamily = i;
//            }
//
//            // Check for surface presentation support
//            VkBool32 presentSupport = false;
//            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
//            if (presentSupport) {
//                indices._presentFamily = i;
//            }
//
//            found = indices.IsCompleted();
//        }

        //|-------------------------------------------|
        //|            NEW QUEUE VALIDATION           |
        //|-------------------------------------------|
        uint32_t familyCount = 0;

        vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(familyCount);

        vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices._graphicsFamily = i;
            }
            // Previous
//            if(indices._graphicsFamily.has_value()) {break; }

            // New
            if(indices.IsCompleted()){
                break;
            }

            i++;
        }

        return indices;
    }
}