#include "st7789.hpp"

st7789::st7789(){
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
	lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);
}

st7789* st7789::getInstance(){
    std::lock_guard<std::mutex> lock(mutex_);
    if(singleton==nullptr) singleton=new st7789();
    return singleton;
}
