#include "app.h"
#include <stdlib.h>
#include <string.h>

static uint_fast8_t initWindow(app_t *app_p, int width, int height){
    if(!glfwInit()) return 1;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    app_p->window = glfwCreateWindow(width, height, "el titulo", NULL, NULL);
    if(app_p->window) return 0;
    else return 1;
}

static uint_fast8_t initVk(app_t *app){
    // CREATE INSTANCE
    VkApplicationInfo appInfo = (VkApplicationInfo){
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Hello Triangle",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "No engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0
    };

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkInstanceCreateInfo createInfo = (VkInstanceCreateInfo){
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,

        // VALIDATION LAYERS
        #ifdef DEBUG
            const char *layer1 = "VK_LAYER_KHRONOS_validation"
            app->validationLayers = malloc(sizeof(void*) * 2);
            app->validationLayers[0] = malloc(strlen(layer1) + 1);
            strcpy(app->validationLayers[0], layer1);
            app->validationLayers[1] = NULL;
            ...
        #else
            .enabledLayerCount = 0,
        #endif
        .enabledExtensionCount = glfwExtensionCount,
        .ppEnabledExtensionNames = glfwExtensions
    };

    if (vkCreateInstance(&createInfo, NULL, &app->instance)) return 1;

    return 0;
}

app_t *app_init(int window_width, int window_height){
    app_t *app = malloc(sizeof(app_t));
    if(initWindow(app, window_width, window_height)) return NULL; // error: couldnt init window
    if(initVk(app)) return NULL; // error: couldnt init Vulkan.

    // Validation Layers
    const char *layer1 = "VK_LAYER_KHRONOS_validation";
    app->validationLayers = malloc(sizeof(void*) * 2);
    app->validationLayers[0] = malloc(strlen(layer1) + 1);
    strcpy(app->validationLayers[0], layer1);
    app->validationLayers[1] = NULL;
    
    return app;
}

void app_run(app_t *app){
    while (!glfwWindowShouldClose(app->window))
    {
        glfwPollEvents();
    }
}

void app_free(app_t *app){
    vkDestroyInstance(app->instance, NULL);
    glfwDestroyWindow(app->window);
    glfwTerminate();
    for (uint_fast8_t i = 0; app->validationLayers[i]; i++) free(app->validationLayers[i]);
    free(app->validationLayers);
    free(app);
}