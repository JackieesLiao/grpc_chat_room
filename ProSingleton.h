#ifndef PROSINGLETON_H
#define PROSINGLETON_H
#include "global.h"
#include <memory>
#include <iostream>
template<typename T>
class Singleton{
public:
    static std::shared_ptr<T> GetInstance(){
        //只初始化一次
        static std::once_flag s_flag;
        std::call_once(s_flag,[&](){
            _instance = std::shared_ptr<T>(new T);
        });
        return _instance;
    }
    ~Singleton(){
        std::cout << "Destruct all instance\n";
    }
    void PrintRawAddress(){
        std::cout << _instance.get() << std::endl;
    }

    static std::shared_ptr<T> _instance;
protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator= (const Singleton<T>&) = delete;
};
template<typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;
#endif // PROSINGLETON_H
