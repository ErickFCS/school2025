extern "C"{
    #include "st7789or.h"
    #include <cstring>
}
#include "ILGH16XB.c" 
#include "ILGH24XB.c"
#include "ILGH32XB.c"
#include <mutex>

//matenmodio las fuentes
//TODO: es probable que esto no funcione y haya que arreglarlo creando particiones ne la memoria para guardar las funetes
void InitFontxMem(FontxFile* fx, const uint8_t* data, size_t len);


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
    FontxFile fx16G[2];
	FontxFile fx24G[2];
	FontxFile fx32G[2];
	FontxFile fx32L[2];
};

