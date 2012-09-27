#ifndef _PCD8544_H_
#define _PCD8544_H_

#define PCD8544_WIDTH		84
#define PCD8544_HEIGHT		48

#define PCD8544_RESET		PB0
#define PCD8544_DATA		PB1
#define PCD8544_SCE		PB2
#define PCD8544_DDR		DDRB
#define PCD8544_PORT		PORTB

/* PCD8544 - Commands */
#define PCD8544_EXTENDED_CMD	0x21
#define PCD8544_STANDARD_CMD	0x20
#define PCD8544_NORMAL_MODE	0x0C
#define PCD8544_INVERT_MODE	0x0D

/* PCD8544 - Settings */
#define PCD8544_VOP		0xA8
#define PCD8544_TEMP_COEFF	0x04
#define PCD8544_BIAS_MODE	0x16

void pcd8544Init(void);
void pcd8544SetContrast(unsigned char);
void pcd8544SetXY(unsigned char, unsigned char);
void pcd8544Clear(void);
void pcd8544SmallChar(char);
void pcd8544SmallStr(const char*);

#endif /* _PCD8544_H_ */
