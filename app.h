#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <inttypes.h>

typedef struct app {
    GLFWwindow *window;
    VkInstance instance;
} app_t;

app_t *app_init(int window_width, int window_height);
void app_run(app_t *app); 
void app_free(app_t *app);