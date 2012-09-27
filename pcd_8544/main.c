#include <avr/io.h>
#include <util/delay.h>
#include "pcd8544.h"
#include "../sw_spi/spi.h"

const char infoString[] = "Hello, World!";

int
main(void)
{
	spiInit();
	pcd8544Init();
	pcd8544SetContrast(32);

	pcd8544SetXY(6, 2);
	pcd8544SmallStr(infoString);

	while (1) {
	}

	/* never reached */
	return 0;
}
