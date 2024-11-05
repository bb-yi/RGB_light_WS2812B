#ifndef _RGB_WS2812B_H_
#define _RGB_WS2812B_H_
#include "main.h"
#define MAX_LED_NUM 19

struct rgb_WS2812B
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};
void reset_led(void);
void send_24bit_color(struct rgb_WS2812B color);
void set_all_led_color(uint8_t color_array[MAX_LED_NUM][3]);
void set_led_color(uint8_t led_num, uint8_t RED, uint8_t GREEN, uint8_t BLUE);
void write_all_led_color(uint8_t val);
void set_all_led_one_color(uint8_t RED, uint8_t GREEN, uint8_t BLUE);
void HSVtoRGB(uint8_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b);
#endif