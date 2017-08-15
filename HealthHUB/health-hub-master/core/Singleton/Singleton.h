#ifndef SINGLETON_H
#define SINGLETON_H

#include <assert.h>

template <typename T>
class Singleton
{
public:
    static T& getInstance(){
        if (Singleton::_instance == 0)
        {
            Singleton::_instance = CreateInstance();
        }
        return *(Singleton::_instance);
    }

protected:
    virtual ~Singleton(){
        if(Singleton::_instance != 0)
        {
            delete Singleton::_instance;
        }
        Singleton::_instance = 0;
    }

    inline explicit Singleton(){
        assert(Singleton::_instance == 0);
        Singleton::_instance = static_cast<T*>(this);
    };

private:
    static T* _instance;
    static T* CreateInstance(){
        return new T();
    }
};

template<typename T>
T* Singleton<T>::_instance = 0;

#endif // SINGLETON_H