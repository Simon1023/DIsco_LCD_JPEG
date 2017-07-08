#include "mbed.h"
#include "LCD_DISCO_F769NI.h"

extern "C"{
#include "MIAT_System.h"
#include "Transmission_mode.h"
}

LCD_DISCO_F769NI lcd;
DigitalOut led_red(LED1);
DigitalOut led_green(LED2);

//UART_HandleTypeDef huart6;

Serial uart6(PC_6,PC_7);

uint8_t color_image[NUM_OF_COLOR_PIXELS] = {0};
uint32_t index = 0;

uint8_t bRead = FALSE;
uint8_t bGet = FALSE;

#if 0
/* USART6 init function */
static void MX_USART6_UART_Init(void)
{

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_7B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    printf("\rHAL_UART_Init ERROR\n");
	}
}
#endif

/*
static int UART_GetStart()
{
	
	uart6.gets(buffer, 4);
}
*/

static void UART_ReadData()
{
	if(bGet == TRUE)
		return;
	
	if(index == 0)
	{
		bRead = TRUE;
	}
	
	color_image[index] = uart6.getc();
	index++;
	
	if(index == NUM_OF_COLOR_PIXELS)
	{
		bGet = TRUE;
		bRead = FALSE;
		index = 0;
	}
		
}

static void UART_SendReady()
{
	//uart6.printf("Ready");
	//HAL_Delay(10);
	//uart6.gets(buffer, 4);
	
	uart6.putc(0xA5);
	
	DEBUG("\rUART_SendReady\n");
}

static void LCD_DrawBitmap(int32_t width, int32_t height, uint8_t* pBuf)
{

    int c_x = height;
    int c_y = 0;
		unsigned int index = 0;
	
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //int pixel = pBuf[index]|pBuf[index+1]<<8|pBuf[index+2]<<16|0xFF<<24;						
						int pixel = 0xFF000000|pBuf[index+2]<<16|pBuf[index+1]<<8|pBuf[index];
					
						//printf("\r[%d]:0x%x\n",index,pixel);
					
            //Because our image contains quite a bit of white space,
            //we check to see if the pixel is white, and avoid calling
            //the pixel function to paint it hoping to improve speed.
            //Unfortunately, speed didn't improve much at all.
            //if (pixel != 0xFFFFFF)
							lcd.DrawPixel(x,y, pixel);
						
            c_y = c_y + 1;
						index = index+3;
        }
        c_y = 0;
        c_x = c_x-1;
    }
}

int main()
{
		printf("\rmain\n");

		uint32_t tickstart = 0;
	
	//MX_USART6_UART_Init();
	
		led_green = 0;
    led_red = 1;

    //lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"MBED EXAMPLE", CENTER_MODE);
    //wait(2);
    lcd.Clear(LCD_COLOR_BLUE);
    lcd.SetBackColor(LCD_COLOR_BLUE);
    lcd.SetTextColor(LCD_COLOR_WHITE);
    lcd.DisplayStringAt(0, LINE(15), (uint8_t *)"Simon's project", RIGHT_MODE);

    led_green = 1;
    led_red = 0;

		//uart6.baud(115200);
		uart6.baud(921600);
		uart6.format(8, SerialBase::None, 1);
		uart6.attach(&UART_ReadData);
	
		UART_SendReady();
		
    while(1) 
		{
/*
			if(bRead == FALSE && (HAL_GetTick()-tickstart>1000))
			{
				UART_SendReady();
				tickstart = HAL_GetTick();
				//HAL_Delay(100);
				
				//wait_us(10);
			}
*/			
			if(bGet)
			{
				DEBUG("\rDrawBitmap\n");
				
				//lcd.DrawBitmap(0,0,color_image);
				LCD_DrawBitmap(NC, NR, color_image);
				
				bGet = FALSE;
				
				UART_SendReady();
			}
			
    }
}
