#include <stdio.h>
#include <iostream>

#include "Application.h"

using namespace aura;

int main(){
    Application app = Application();

    app.Init();
    app.Running();
    app.Close();
    return 0;
}
