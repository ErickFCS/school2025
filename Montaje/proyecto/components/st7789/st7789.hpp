extern "C"{
    #include "st7789or.h"
    #include <cstring>
}
#include "ILGH16XB.c" 
#include "ILGH24XB.c"
#include "ILGH32XB.c"
#include <mutex>

//matenmodio las fuentes
//TODO: es probable que esto no funcione y haya que arreglarlo creando particiones en la memoria para guardar las funetes
void InitFontxMem(FontxFile* fx, const uint8_t* data, size_t len);


// va a funcionar como un singleton porque de todas maneras si crearas mas de uno todos usarina los mismos pines (y paja)
class st7789{
public:
    //el "gh" es por el nombre de la fuente, el numero es el tamaño
    enum fonts{
        gh16=0,
        gh24,
        gh32
    };

    st7789(st7789 &other)=delete;
    void operator=(const st7789 &)=delete;
    ~st7789(){}
    
    static st7789* getInstance();//iniciador para evitar multiples instancias
    
    //renderisa el buffer actual y lo deja vacio
    void render();
    //vacia le buffer(lo tapa de negro)
    void cleanBuffer();

    void turnBacklight(bool to);
    
    void fillScreen(uint16_t color);
    
    
    void drawPixel(uint16_t x, uint16_t y, uint16_t color);
    //TODO: pensar como implementar esto de forma comoda de usar. por ahora no existe
    void drawPixels(uint16_t color);
    
    void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
    
    void drawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
    void drawFillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
    void drawRectAngle(uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint16_t color);
    void drawFillSquare(uint16_t x0, uint16_t y0, uint16_t size, uint16_t color);
    void drawSquare(uint16_t x0, uint16_t y0, uint16_t size, uint16_t color);
    
    void drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
    void drawFillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);

    int drawChar(st7789::fonts font, uint16_t x, uint16_t y, uint8_t ascii, uint16_t color);
    int drawString(st7789::fonts font, uint16_t x, uint16_t y, uint8_t * ascii, uint16_t color);


protected:
    st7789();

private:
	TFT_t dev;
    static st7789 *singleton;
    static std::mutex mutex_;
    FontxFile fonts_m[3][2];
};

