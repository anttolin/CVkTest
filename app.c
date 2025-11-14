#include "debug.h"
#include "app.h"
#include <stdlib.h>
#include <string.h>

static GLFWwindow *getWindow(int width, int height){
    if(!glfwInit()) return NULL;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(width, height, "el titulo", NULL, NULL);
    return window;
}

static VkInstance *GetInstance(){
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
    
    const char **layerNames = NULL;
    uint32_t count = 0;
    #if DEBUG
    const char *layer1 = "VK_LAYER_KHRONOS_validation";
    #define LAYER_COUNT 1 // modify acording to the numbers of layers.
    VkLayerProperties *prop;
    vkEnumerateInstanceLayerProperties(&count, NULL);
    vkEnumerateInstanceLayerProperties(&count, prop);
    for (uint32_t i = 0; i < count; i++) {
        if (!strcmp(prop[i].layerName, layer1)) {
            *layerNames = layer1;
            break;
        }
    }
    count = LAYER_COUNT;
    #endif
    
    VkInstanceCreateInfo createInfo = (VkInstanceCreateInfo){
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .ppEnabledLayerNames = layerNames,
        .enabledLayerCount = count,
        .enabledExtensionCount = glfwExtensionCount,
        .ppEnabledExtensionNames = glfwExtensions
    };
    VkInstance *instance;
    vkCreateInstance(&createInfo, NULL, instance);
    return instance;
}

app_t *app_init(int window_width, int window_height){
    app_t *app = malloc(sizeof(app_t));
    if(initWindow(app, window_width, window_height)) return NULL; // error: couldnt init window
    if(initVk(app)) return NULL; // error: couldnt init Vulkan.
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
    free(app);
}