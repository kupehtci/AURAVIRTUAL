#ifndef AURAVIRTUAL_SINGLETON_H
#define AURAVIRTUAL_SINGLETON_H

#pragma once
#include "Assertion.h"

namespace aura{

    template<class T>
    class Singleton{
    public:
        static T* m;


        Singleton(){}
        ~Singleton(){}

        inline static void Create(){
             if(!m){
                 m = new T();
             }
             else{
                 Assertion::Assert((char*)"Unable to create Singleton");
             }
        }

        inline static T GetInstance(){
            return *m;
        }

        inline static T* GetInstancePtr(){
            return m;
        }
    };

    // Initilize as NULL

    template < class T >
    T* Singleton<T>::m = NULL;


}

#endif //AURAVIRTUAL_SINGLETON_H
