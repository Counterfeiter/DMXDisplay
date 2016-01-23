// DMX Display Extension
// Copyright (c) 2011-2015 Sebastian Förster


#include "LCD_EADOG.h"
#include <math.h>

void lcd_eadog_writebyte(uint8_t byte);
void lcd_eadog_cursor_off(void);
void lcd_eadog_cursor_underline(void);
void lcd_eadog_cursor_blink(void);
void wtoggle_RS(void);
void ctoggle_RS(void);
void lcd_eadog_Horizontale_Balken(void);
void lcd_eadog_Vertikale_Balken(void);
void lcd_eadog_define_char(void);
void lcd_eadog_spi_init(void);

void lcd_eadog_writebyte(uint8_t byte)
{
	usart_spi_write_single(&LCD_UART_SPI, byte);
}

//*********************************************************************************
//*** Beginn Subfunktionen ********************************************************
	
//*********************************************************************************

void ctoggle_RS(void)	// RS nach Control-Befehl toggeln
{
	gpio_set_pin_high(LCD_RS_O);// CTRL_RS HIGH bringen
	delay_us(1);
	gpio_set_pin_low(LCD_RS_O);		// CTRL_RS Low bringen
}
	
//*********************************************************************************

void wtoggle_RS(void)	// RS nach Schreib-Befehl toggeln
{
	gpio_set_pin_low(LCD_RS_O);		// CTRL_RS Low bringen
	delay_us(1);
	gpio_set_pin_high(LCD_RS_O);		// CTRL_RS HIGH bringen
}

//*********************************************************************************

void lcd_eadog_cursor_off(void)	// Cursor ausschalten
{
	gpio_set_pin_low(LCD_RS_O);		// CTRL_RS Low bringen
	lcd_eadog_writebyte(0b00001100);
	delay_us(100);
	ctoggle_RS ();
}
	
//*********************************************************************************

void lcd_eadog_cursor_underline(void)	// Cursor Unterstrich
{
	gpio_set_pin_low(LCD_RS_O);		// CTRL_RS Low bringen
	lcd_eadog_writebyte(0b00001110);
	delay_us(100);
	ctoggle_RS ();
}
	
//*********************************************************************************

void lcd_eadog_cursor_blink(void)	// Cursor blinkend
{
	gpio_set_pin_low(LCD_RS_O);		// CTRL_RS Low bringen
	lcd_eadog_writebyte(0b00001101);
	delay_us(100);
	ctoggle_RS ();
}
	
//*********************************************************************************	

void lcd_eadog_set_cursor(uint8_t pos)	// Cursor an Position setzen
{
	gpio_set_pin_low(LCD_RS_O);		// CTRL_RS Low bringen
	lcd_eadog_writebyte(128+pos);				//  0..15 -> Zeile 1
								// 16..31 -> Zeile 2
	delay_us(200);				// 32..47 -> Zeile 3
	ctoggle_RS ();
}
	
//*********************************************************************************	

void lcd_eadog_clear_home(void)	// Display löschen, Cursor an Position home setzen
{
	gpio_set_pin_low(LCD_RS_O);		// CTRL_RS Low bringen
	lcd_eadog_writebyte(0b00000001);
	delay_ms(2);
	ctoggle_RS ();
}

	
//*********************************************************************************	

/*void clear_lastpos (void)	// Display löschen, Cursor an letzte Position setzen
	{
		CONTROLPORT &= ~_BV(CTRL_RS);		// CTRL_RS Low bringen
		SPDR = 0b00000010;	
		_delay_ms(1.2);
		ctoggle_RS ();
	}*/

//*********************************************************************************	

void lcd_eadog_set_contrast(uint8_t con)	// Kontrast einstellen (0..15)
{
	gpio_set_pin_low(LCD_RS_O);		// CTRL_RS Low bringen
	lcd_eadog_writebyte(0b00111001);	// Instruction-table 1
	delay_us(100);
	ctoggle_RS();
	con = con & 0x0f;			// nur die unteren 4 bit verwenden
	lcd_eadog_writebyte(0b01110000+con);	// Kontrast setzen
	delay_us(100);
	ctoggle_RS();
	lcd_eadog_writebyte(0b00111000);	// zurück zu Instruction-table 0
	delay_us(100);
	ctoggle_RS();
}
	
//*********************************************************************************	

int lcd_eadog_write_char (char car, FILE *unused)	// Byte an Cursorposition ausgeben 
{
	gpio_set_pin_high(LCD_RS_O);		// CTRL_RS HIGH bringen
	lcd_eadog_writebyte(car);
	delay_us(100);
	wtoggle_RS();
	return 0;
}

//*********************************************************************************	

void lcd_eadog_write_chars (uint8_t *car, uint8_t len)	// Byte an Cursorposition ausgeben 
{
	gpio_set_pin_high(LCD_RS_O);		// CTRL_RS HIGH bringen
	for(uint8_t i = 0; i < len; i++) {
		lcd_eadog_writebyte(car[i]);
		delay_us(100);
		wtoggle_RS();
	}
}
/**************************************************************************************************/

void lcd_eadog_spi_init(void)
{
	
	ioport_configure_pin(LCD_MOSI_O, IOPORT_DIR_OUTPUT	| IOPORT_INIT_LOW);
	ioport_configure_pin(LCD_CLK_O, IOPORT_DIR_OUTPUT	| IOPORT_INIT_LOW);
	// 4 MHz is to fast!
	usart_spi_setup_device(&LCD_UART_SPI,0,SPI_MODE_0,2000000,0);
	delay_us(20);
}

//*********************************************************************************

void lcd_eadog_Horizontale_Balken(void) 
{
	for(uint8_t i=0;i<8;i++) {
		lcd_eadog_writebyte(0b00010000);
		delay_us(30);
		wtoggle_RS ();
	}
	for(uint8_t i=0;i<8;i++) {
		lcd_eadog_writebyte(0b00011000);
		delay_us(30);
		wtoggle_RS ();
	}
	for(uint8_t i=0;i<8;i++) {
		lcd_eadog_writebyte(0b00011100);
		delay_us(30);
		wtoggle_RS ();
	}
	for(uint8_t i=0;i<8;i++) {
		lcd_eadog_writebyte(0b00011110);
		delay_us(30);
		wtoggle_RS ();
	}
	for(uint8_t i=0;i<8;i++) {
		lcd_eadog_writebyte(0b00011111);
		delay_us(30);
		wtoggle_RS ();
	}
}
void lcd_eadog_Vertikale_Balken(void) 
{
	for(uint8_t i=0;i<8;i++) {
		if(i>6)
			lcd_eadog_writebyte(0b00011111);
		else
			lcd_eadog_writebyte(0b00000000);
		delay_us(30);
		wtoggle_RS();
	}
	for(uint8_t i=0;i<8;i++) {
		if(i>5)
			lcd_eadog_writebyte(0b00011111);
		else
			lcd_eadog_writebyte(0b00000000);
		delay_us(30);
		wtoggle_RS();
	}
	for(uint8_t i=0;i<8;i++) {
		if(i>4)
			lcd_eadog_writebyte(0b00011111);
		else
			lcd_eadog_writebyte(0b00000000);
		delay_us(30);
		wtoggle_RS();
	}
	for(uint8_t i=0;i<8;i++) {
		if(i>3)
			lcd_eadog_writebyte(0b00011111);
		else
			lcd_eadog_writebyte(0b00000000);
		delay_us(30);
		wtoggle_RS();
	}
	for(uint8_t i=0;i<8;i++) {
		if(i>2)
			lcd_eadog_writebyte(0b00011111);
		else
			lcd_eadog_writebyte(0b00000000);
		delay_us(30);
		wtoggle_RS ();
	}
	for(uint8_t i=0;i<8;i++) {
		if(i>1)
			lcd_eadog_writebyte(0b00011111);
		else
			lcd_eadog_writebyte(0b00000000);
		delay_us(30);
		wtoggle_RS();
	}
	for(uint8_t i=0;i<8;i++) {
		if(i>0)
			lcd_eadog_writebyte(0b00011111);
		else
			lcd_eadog_writebyte(0b00000000);
		delay_us(30);
		wtoggle_RS();
	}
	for(uint8_t i=0;i<8;i++) {
		lcd_eadog_writebyte(0b00011111);
		delay_us(30);
		wtoggle_RS();
	}
}

void lcd_eadog_define_char(void)
{
	gpio_set_pin_low(LCD_RS_O);

	lcd_eadog_writebyte(0b01000000);
	delay_us(100);
	ctoggle_RS();
	gpio_set_pin_high(LCD_RS_O);
	delay_us(100);

	//Aussehen
	lcd_eadog_Vertikale_Balken();

	gpio_set_pin_low(LCD_RS_O);
	lcd_eadog_writebyte(0b10000000);
	delay_us(100);
		
}

	
void lcd_eadog_init(void)	// Display initialisieren
{
	lcd_eadog_spi_init();			// SPI Initalisieren
	
	gpio_set_pin_low(LCD_CSB_O);
	
	delay_ms(50);
	gpio_set_pin_low(LCD_RS_O);	// CTRL_RS Low bringen
	
	//5V init
	/*
	lcd_eadog_writebyte(0b00111001);	// Datenlänge, Zeilenzahl, doppelte Höhe, Instruction-table 1
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0b00010101);	// Bias, Fixed-on-high (3-Line) and fixed on low (other apps)
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0b01010000);	// Icon-Display on/off, Booster on/off, Contrast set (internal-follower-mode)
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0b01101100);	// Spannungsfolger und Verstärkung setzen
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0b01111101);	// Kontrast setzen
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0b00111000);	// zurück zu Instruction-table 0
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0b00001100);	// Display, Cursorposition (Unterstrich), Cursor blinken
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0b00000001);	// Display löschen, Cursor home
	delay_ms(2);
	ctoggle_RS ();
	lcd_eadog_writebyte(0b00000110);	// Cursor auto-increment
	*/
	//3.3 V init
	lcd_eadog_writebyte(0b00111001);	// Datenlänge, Zeilenzahl, doppelte Höhe, Instruction-table 1
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0x14);	// Bias
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0x55);	// Icon-Display on/off, Booster on/off, Contrast set (internal-follower-mode)
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0x6D);	// Spannungsfolger und Verstärkung setzen
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0x78);	// Kontrast setzen
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0b00111000);	// zurück zu Instruction-table 0
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0b00001100);	// Display, Cursorposition (Unterstrich), Cursor blinken
	delay_ms(2);
	ctoggle_RS();
	lcd_eadog_writebyte(0b00000001);	// Display löschen, Cursor home
	delay_ms(2);
	ctoggle_RS ();
	lcd_eadog_writebyte(0b00000110);	// Cursor auto-increment
	
	delay_ms(2);
	ctoggle_RS();

	lcd_eadog_define_char();
}
 
