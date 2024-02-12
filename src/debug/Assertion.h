#ifndef AURAVIRTUAL_ASSERTION_H
#define AURAVIRTUAL_ASSERTION_H

#include <stdio.h>
#include <iostream>

namespace aura {

    class Assertion {

    public:

        static void Assert(char* msg){
            std::cout << msg << std::endl;
        }
    };

}


#endif //AURAVIRTUAL_ASSERTION_H
