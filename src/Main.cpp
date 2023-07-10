#include "Application.hpp"

int main(int argc, const char ** cpargv) {
    Application app;
    
    app.Setup();

    while(app.IsRunning()) {
        app.Input();
        app.Update();
        app.Render();
    }

    app.Destroy();

    return 0;
}

