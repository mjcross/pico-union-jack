# Test of ILI9341-based LCD Display

Displays a coloured Union jack, optionally using the framebuffer.

## Hardware
Part number: [KL-TFT028B](https://wiki.52pi.com/index.php?title=EP-0065)

Supplier: [GeeekPi 2.8inch TFT LCD 240x320 Screen](https://www.amazon.co.uk/gp/product/B091C7YMZG)

## Software
Based on [tvlad1234/pico-displayDrivs](https://github.com/tvlad1234/pico-displayDrivs/blob/main/gfx/gfx.c) but
I fixed the missing headers and CMakelists.

## Wiring
|Pico   |RP2020          |ILI9341    |                      |
|-------|----------------|-----------|----------------------|
|pin 21 |gp16, spi0 RX   |L_RST      |Reset                 |
|pin 22 |gp17, spi0 CSn  |L_CS       |LCD Chip Select       |
|pin 23 |gnd             |GND        |                      |
|pin 24 |gp18, spi0 SCK  |SCLK       |Serial Clock          |
|pin 25 |gp19, spi0 TX   |MOSI       |Master Out Slave In   |
|pin 26 |gp20            |L_DC       |LCD Data/Command      |
|pin 39 |Vsys            |VCC        |+5V                   |

## API
### GFX Framebuffer
By default, the GFX library writes pixels directly to the screen. If desired, an internal framebuffer can be used (which is recomended in cases where speed is desired). The framebuffer is created using `GFX_createFramebuf()`, which automatically tells the library to write to the framebuffer. The buffer can then be pushed to the screen by calling `GFX_flush()`. If needed, the buffer can be destroyed by calling `GFX_destroyFramebuf()`. Doing so will revert to writing pixels directly to the screen.

### Pixel
`GFX_drawPixel(int16_t x, int16_t y, uint16_t color);` draws a single pixel
### Text
`GFX_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
                          uint16_t bg, uint8_t size_x, uint8_t size_y);` puts a single character on screen\
`GFX_write(uint8_t c);` writes a character to the screen, handling the cursor position and text wrapping automatically\
`GFX_setCursor(int16_t x, int16_t y);` places the text cursor at the specified coordinates\
`GFX_setTextColor(uint16_t color);` sets the text color\
`GFX_setTextBack(uint16_t color);` sets the text background color\
`GFX_setFont(const GFXfont *f);`  sets the used font, using the same format as [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library) \
`GFX_printf` prints formatted text
### Whole Screen
`GFX_fillScreen(uint16_t color);` fills the screen with a specified color\
`GFX_setClearColor(uint16_t color);` sets the color the screen should be cleared with\
`GFX_clearScreen();` clears the screen, filling it with the color specified using the function above
### Lines
`GFX_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);` draws a line from (x0,y0) to (x1,y1)\
`GFX_drawFastHLine(int16_t x, int16_t y, int16_t l, uint16_t color);` draws a horizontal line\
`GFX_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);` draws a vertical line
### Shapes
`GFX_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);` draws a rectangle\
`GFX_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)` draws a circle\
`GFX_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);` draws a filled rectangle\
`GFX_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);` draws a filled circle