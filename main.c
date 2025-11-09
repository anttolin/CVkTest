#include <stdlib.h>
#include <stdio.h>

#define DEBUG 
#include "app.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
    app_t *app = app_init(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!app) return 1;
    app_run(app);
    app_free(app);
    
    return 0;
}