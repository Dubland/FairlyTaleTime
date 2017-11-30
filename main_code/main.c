//#define USE_STDPERIPH_DRIVER
#define STM32F40_41xxx

//#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
 
//Quick hack, approximately 1ms delay
void ms_delay(int ms)
{
   while (ms-- > 0) {
      volatile int x=5971;
      while (x-- > 0)
         __asm("nop");
   }
}

static uint8_t lastButtonStatus = RESET;

void init_GPIO(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 |
                               GPIO_Pin_13 | GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &gpio);
}

//Flash orange LED at about 1hz
int main(void)
{
    init_GPIO();

    GPIOD->BSRRL = 0xF000;
    ms_delay(500);
    GPIOD->BSRRH = 0xF000;

    static uint32_t counter = 0;

    while (1) {
        uint8_t currentButtonStatus = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
        if (lastButtonStatus != currentButtonStatus && currentButtonStatus != RESET) {
            counter++;
            GPIO_ResetBits(GPIOD, GPIO_Pin_15);
            GPIO_SetBits(GPIOD, GPIO_Pin_14);
        }
        lastButtonStatus = currentButtonStatus;
    }
}
