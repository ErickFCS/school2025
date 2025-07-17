#include "st7789.hpp"
#include <cstdio>
#include "esp_log.h"

#define TAG "st7789"

void InitFontxMem(FontxFile* fx, const char* data, unsigned int len)
{
    //    Limpia toda la estructura:
    memset(fx, 0, sizeof(FontxFile));

    //    Crea un FILE* que lee de `data[0..len-1]`:
    //    fmemopen no acepta const, por eso el cast:
    fx->file = fmemopen((void*)data, len, "rb");
    if (fx->file == NULL) {
        // fallo al crear el FILE*, marca inválido y sal:
        fx->valid = false;
        return;
    }

    //    No hay fichero de "extensión" (.GLY), así que fonts queda NULL:
    fx->fonts = NULL;
    fx->fsz   = len;     // para info interna

    //    Indica que ya está abierto (evita que OpenFontx intente fopen(path)):
    fx->opened = true;

    //    Llama a OpenFontx para que lea cabecera, ancho, alto, etc.
    //    OpenFontx llenará fx->w, fx->h, fx->bc, fx->valid, ...
    fx->valid = OpenFontx(fx);
}


// Definiciones de los miembros estáticos
st7789* st7789::singleton = nullptr;


st7789::st7789(){
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
	lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);
#if CONFIG_INVERSION
	ESP_LOGI(TAG, "Enable Display Inversion");
	//lcdInversionOn(&dev);
	lcdInversionOff(&dev);
#endif
    //InitFontxMem(fonts_m[gh16],ILGH16XB_FNT,ILGH16XB_FNT_len); // 8x16Dot Gothic
	//InitFontxMem(fonts_m[gh24],ILGH24XB_FNT,ILGH24XB_FNT_len); // 12x24Dot Gothic
	//InitFontxMem(fonts_m[gh32],ILGH32XB_FNT,ILGH32XB_FNT_len); // 16x32Dot Gothic
    ESP_LOGI(TAG,"termino el constructor");
}

st7789* st7789::getInstance(){
    if(singleton==nullptr) singleton=new st7789();
    ESP_LOGI(TAG,"termino el getinstance");
    return singleton;
}
void st7789::turnBacklight(bool to){
    if(to) lcdBacklightOn(&dev);
    else lcdBacklightOff(&dev);
}

void st7789::render(){lcdDrawFinish(&dev);}
void st7789::fillScreen(uint16_t color){lcdFillScreen(&dev, BLACK);}

void st7789::drawPixel(uint16_t x, uint16_t y, uint16_t color){lcdDrawPixel(&dev,x,y,color);}
void st7789::drawPixels(uint16_t color){}

void st7789::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){lcdDrawLine(&dev,x1,y1,x2,y2,color);}

void st7789::drawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){lcdDrawRect(&dev,x1,y1,x2,y2,color);}
void st7789::drawFillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){lcdDrawFillRect(&dev,x1,y1,x2,y2,color);}
void st7789::drawRectAngle(uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint16_t color){lcdDrawRectAngle(&dev,xc,yc,w,h,angle,color);}
void st7789::drawFillSquare(uint16_t x0, uint16_t y0, uint16_t size, uint16_t color){lcdDrawFillSquare(&dev,x0,y0,size,color);}
void st7789::drawSquare(uint16_t x0, uint16_t y0, uint16_t size, uint16_t color){lcdDrawRect(&dev,x0,y0,x0+size,y0+size,color);}

void st7789::drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color){lcdDrawCircle(&dev,x0,y0,r,color);}
void st7789::drawFillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color){lcdDrawFillCircle(&dev,x0,y0,r,color);}

int st7789::drawChar(st7789::fonts font, uint16_t x, uint16_t y, uint8_t ascii, uint16_t color){return 0;}
int st7789::drawString(st7789::fonts font, uint16_t x, uint16_t y, uint8_t * ascii, uint16_t color){return 0;}
