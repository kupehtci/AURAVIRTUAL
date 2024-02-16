#ifndef AURAVIRTUAL_APPLICATION_H
#define AURAVIRTUAL_APPLICATION_H

#include "ApplicationPlatform.h"
#include "Renderer.h"

namespace aura{



    class Application {
        friend class Renderer;
    public:
        //region Attributes
        bool _isRunning;
        ApplicationPlatform _platform;

        // Manager references
        Renderer* _renderer;

        //Singleton
        static Application* instance;
        //endregion

    public:
        Application();

        void Init();
        void Running();
        void Close();

    private:
        void CreateSingleton();
    };
}

#endif //AURAVIRTUAL_APPLICATION_H
