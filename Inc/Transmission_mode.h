
#ifndef TRANSMISSION_MODE_H
#define TRANSMISSION_MODE_H

#define USB_SEND_IMAGE 	0
#define UART_SEND_IMAGE 1


#define GRAY_IMAGE 8
#define COLOR_IMAGE 24


#define NR 240
#define NC 320
#define NUM_OF_COLOR_PIXELS (NR * NC * 3)
#define NUM_OF_PIXELS (NC * NR)

#define SEND_MODE 	UART_SEND_IMAGE
#define IMAGE_TYPE 	COLOR_IMAGE

#endif
