#ifndef AURAVIRTUAL_APPLICATION_H
#define AURAVIRTUAL_APPLICATION_H

#include "Renderer.h"

namespace aura{

    enum ApplicationPlatform{MacOS = 0, Linux, Windows, notdefined};

    class Application {
    public:
        //region Attributes
        bool _isRunning;
        ApplicationPlatform _platform;

        // Manager references
        Renderer* _renderer;

        //endregion

    public:
        Application();

        void Init();
        void Running();
        void Close();
    };
}

#endif //AURAVIRTUAL_APPLICATION_H
