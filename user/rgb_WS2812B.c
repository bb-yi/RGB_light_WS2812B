#include "rgb_WS2812B.h"
void set_a_bit(uint8_t val)
{
    if (val != 1)
    {
        GPIOA->BSRR = GPIO_PIN_8;
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        GPIOA->BSRR = (uint32_t)GPIO_PIN_8 << 16u;
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }
    else
    {
        GPIOA->BSRR = GPIO_PIN_8;
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        GPIOA->BSRR = (uint32_t)GPIO_PIN_8 << 16u;
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }
}

void reset_led(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_Delay(1);
}

struct rgb_WS2812B color;
void send_24bit_color(struct rgb_WS2812B color)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        set_a_bit((color.green >> (7 - i)) & 0x01);
    }
    for (i = 8; i < 16; i++)
    {
        set_a_bit((color.red >> (15 - i)) & 0x01);
    }
    for (i = 16; i < 24; i++)
    {
        set_a_bit((color.blue >> (23 - i)) & 0x01);
    }
}
uint8_t led_color[MAX_LED_NUM][3];
void set_all_led_color(uint8_t color_array[MAX_LED_NUM][3])
{
    reset_led();
    for (uint8_t i = 0; i < MAX_LED_NUM; i++)
    {
        color.red = color_array[i][0];
        color.green = color_array[i][1];
        color.blue = color_array[i][2];
        send_24bit_color(color);
    }
}
void set_led_color(uint8_t led_num, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{

    led_color[led_num][0] = RED > 255 ? 255 : RED;
    led_color[led_num][1] = GREEN > 255 ? 255 : GREEN;
    led_color[led_num][2] = BLUE > 255 ? 255 : BLUE;
}

void set_all_led_one_color(uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{
    for (uint8_t i = 0; i < MAX_LED_NUM; i++)
    {
        set_led_color(i, RED, GREEN, BLUE);
    }
}
void write_all_led_color(uint8_t val)
{
    memset(led_color, val, sizeof(led_color));
}
void HSVtoRGB(uint8_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b)
{
    float H = h * 3.6;   // 将 H 从 0-100 映射到 0-360
    float S = s / 100.0; // 将 S 从 0-100 映射到 0-1
    float V = v / 100.0; // 将 V 从 0-100 映射到 0-1

    float C = V * S; // 色调区间
    float X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
    float m = V - C;

    float r_prime, g_prime, b_prime;

    if (H >= 0 && H < 60)
    {
        r_prime = C;
        g_prime = X;
        b_prime = 0;
    }
    else if (H >= 60 && H < 120)
    {
        r_prime = X;
        g_prime = C;
        b_prime = 0;
    }
    else if (H >= 120 && H < 180)
    {
        r_prime = 0;
        g_prime = C;
        b_prime = X;
    }
    else if (H >= 180 && H < 240)
    {
        r_prime = 0;
        g_prime = X;
        b_prime = C;
    }
    else if (H >= 240 && H < 300)
    {
        r_prime = X;
        g_prime = 0;
        b_prime = C;
    }
    else
    {
        r_prime = C;
        g_prime = 0;
        b_prime = X;
    }

    *r = (uint8_t)((r_prime + m) * 255);
    *g = (uint8_t)((g_prime + m) * 255);
    *b = (uint8_t)((b_prime + m) * 255);
}
