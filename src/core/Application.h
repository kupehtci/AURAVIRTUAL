#ifndef AURAVIRTUAL_APPLICATION_H
#define AURAVIRTUAL_APPLICATION_H

#include "Renderer.h"

namespace aura{

    class Application {
    public:
        bool _isRunning;

        //Managers references
        Renderer* _renderer;
    public:
        Application();

        // State function
        void Init();
        void Running();
        void Close();
    };
}

#endif //AURAVIRTUAL_APPLICATION_H
