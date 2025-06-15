extern "C"{
    #include "st7789or.h"
}
#include <mutex>

// va a funcionar como un singleton porque de todas maneras si crearas mas de uno todos usarina los mismos pines (y paja)
class st7789{
public:
    st7789(st7789 &other)=delete;
    void operator=(const st7789 &)=delete;
    ~st7789(){}
    
    static st7789* getInstance();//iniciador para evitar multiples instancias
    
protected:
    st7789();

private:
	TFT_t dev;
    static st7789 *singleton;
    static std::mutex mutex_;
};

