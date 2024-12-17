#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "pico/stdlib.h"

#include "ili9341.h"
#include "gfx.h"

#define RGB565(R, G, B) ((uint16_t)((R & 0b11111000) << 8) | ((G & 0b11111100) << 3) | (B >> 3))


// Simple test of the 320x240 EP-0065 TFT28 LCD Display
// in 16bpp mode (rgb 565)

// a frame buffer takes 150K of RAM (Pico has 246K in total) but makes drawing much faster
#define USE_FRAME_BUFFER

int main()
{
    stdio_init_all();

    static const uint16_t RED = RGB565(200, 16, 44);
    static const uint16_t WHITE = RGB565(255, 255, 255);
    static const uint16_t BLUE = RGB565(1, 33, 105);

    const uint led_pin = 25;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    bool led_state = true;
    gpio_put(led_pin, led_state);

    // initialise LCD display driver
    //
    LCD_initDisplay();
    LCD_setRotation(1);
#ifdef USE_FRAME_BUFFER
    GFX_createFramebuf();
#endif

    // draw image
    //
    absolute_time_t draw_start_time = get_absolute_time();
    GFX_setClearColor(BLUE);
    GFX_clearScreen();
    GFX_fillRect(0, 80, 320, 80, WHITE);
    GFX_fillRect(133, 0, 53, 240, WHITE);

    for (int y=0; y<=54; y+=1) {
        GFX_drawLine(0, 26-y, 320, 267-y, WHITE);
        GFX_drawLine(0, 267-y, 320, 26-y, WHITE);
    }

    GFX_fillRect(0, 96, 320, 48, RED);
    GFX_fillRect(144, 0, 32, 240, RED);

    for (int x=0; x<=25; x+=1) {
        GFX_drawLine(-x, 0, 106-x, 80, RED);
        GFX_drawLine(213-x, 80, 320-x, 0, RED);
        GFX_drawLine(103+x, 160, x, 240, RED);
        GFX_drawLine(213+x, 160, 320+x, 240, RED);
    }
    absolute_time_t draw_end_time = get_absolute_time();

    // transfer frame buffer to LCD
    //
    absolute_time_t transfer_start_time = get_absolute_time();
#ifdef USE_FRAME_BUFFER
    GFX_flush();
#endif
    absolute_time_t transfer_end_time = get_absolute_time();

    // blink LED until USB serial port is connected
    //
    while(!stdio_usb_connected()) {
        sleep_ms(500);
        led_state = !led_state;
        gpio_put(led_pin, led_state);
    }

    // show timings
    //
    printf("Draw time %llu micro-seconds\n", draw_end_time - draw_start_time);
    printf("Transfer time %llu micro-seconds\n", transfer_end_time - transfer_start_time);

    for(;;);
}