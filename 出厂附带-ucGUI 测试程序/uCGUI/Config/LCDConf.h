/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDConf_1375_C8_C320x240.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H
#include "ili93xx.h"

/*********************************************************************
*
*                   General configuration of LCD
*
**********************************************************************
*/

#if (LCD_SIZE_TYPE==1)
#define LCD_XSIZE      (320)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (240)   /* Y-resolution of LCD, Logical coor. */
#elif (LCD_SIZE_TYPE==2)
#define LCD_XSIZE      (480)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (320)   /* Y-resolution of LCD, Logical coor. */
#elif (LCD_SIZE_TYPE==3)
#define LCD_XSIZE      (800)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (480)   /* Y-resolution of LCD, Logical coor. */
#endif

//#define LCD_BITSPERPIXEL (8)
#define LCD_BITSPERPIXEL (16)
#define LCD_FIXEDPALETTE   (565)
#define LCD_SWAP_RB        (1)
//#define LCD_SWAP_XY        (1)

#define LCD_INIT_CONTROLLER()  LCDX_Init();

#define LCD_CONTROLLER 4531


 
#endif /* LCDCONF_H */

 
