// DMX Display Extension
// Copyright (c) 2011-2015 Sebastian Förster

#ifndef _LCD_EADOG_h_
#define _LCD_EADOG_h_

#include <asf.h>
#include <stdlib.h>
#include <stdio.h>

extern void		lcd_eadog_set_cursor (unsigned char pos);
extern void		lcd_eadog_clear_home (void);
extern void		lcd_eadog_set_contrast (unsigned char con);
extern int		lcd_eadog_write_char (char car, FILE *unused);
extern void		lcd_eadog_init(void);
extern void		lcd_eadog_write_chars (uint8_t *car, uint8_t len);

#endif
