#include "st7789.hpp"
#include <cstdio>


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

st7789::st7789(){
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
	lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);
#if CONFIG_INVERSION
	ESP_LOGI(TAG, "Enable Display Inversion");
	//lcdInversionOn(&dev);
	lcdInversionOff(&dev);
#endif
    InitFontxMem(fx16G,ILGH16XB_FNT,ILGH16XB_FNT_len); // 8x16Dot Gothic
	InitFontxMem(fx24G,ILGH24XB_FNT,ILGH24XB_FNT_len); // 12x24Dot Gothic
	InitFontxMem(fx32G,ILGH32XB_FNT,ILGH32XB_FNT_len); // 16x32Dot Gothic
}

st7789* st7789::getInstance(){
    std::lock_guard<std::mutex> lock(mutex_);
    if(singleton==nullptr) singleton=new st7789();
    return singleton;
}
