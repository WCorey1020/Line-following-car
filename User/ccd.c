#include "ccd.h"
#include "main.h"
#include "spi.h"
#include "uart.h"
#include "string.h"

static uint8_t CCD_RX[CCD_FRAME_SIZE];
static uint8_t dummy[64];  
uint8_t CCD_Valid[100];
uint16_t CCDReadFrame(void)
{
    uint16_t done = 0;

    memset(CCD_RX, 0x00, CCD_FRAME_SIZE);

    // 等待DR就绪
    while(HAL_GPIO_ReadPin(DR_GPIO_Port, DR_Pin) == GPIO_PIN_SET);
    // 拉低CS，开始SPI读取CCD
    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

    while (done < CCD_FRAME_SIZE)
    {
        uint16_t chunk = CCD_FRAME_SIZE - done;
        if (chunk > 64)
        {
            chunk = 64;
        }
        // SPI收发，超时2000ms
        if (HAL_SPI_TransmitReceive(&hspi1, dummy, &CCD_RX[done], chunk, 2000) != HAL_OK)
        {
            break;
        }
        done += chunk;
    }

    // 读完拉高CS
    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
    memcpy(CCD_Valid, &CCD_RX[10], 100);
    return done;
}
int16_t CCD_GetPosition(void)
{
    uint32_t sum_pixel = 0;
    uint32_t sum_weight = 0;
    uint8_t threshold = 80; 
    for(uint16_t i=0; i<100; i++)
    {
        // 二值化
        if(CCD_Valid[i] < threshold)
        {
            sum_weight += i;    // 像素位置作为权重
            sum_pixel += 1;
        }
    }

    float center = (float)sum_weight / sum_pixel;
    return center;
}
