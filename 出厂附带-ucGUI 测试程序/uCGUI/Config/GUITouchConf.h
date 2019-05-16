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
File        : GUITouch.Conf.h
Purpose     : Configures touch screen module
----------------------------------------------------------------------
*/


#ifndef GUITOUCH_CONF_H
#define GUITOUCH_CONF_H
#include "ili93xx.h"


#define GUI_TOUCH_AD_LEFT     	0

#if (LCD_SIZE_TYPE==1)
#define GUI_TOUCH_AD_RIGHT      320
#elif (LCD_SIZE_TYPE==2)
#define GUI_TOUCH_AD_RIGHT      480
#elif (LCD_SIZE_TYPE==3)
#define GUI_TOUCH_AD_RIGHT      800
#endif

#define GUI_TOUCH_AD_TOP   	    0

#if (LCD_SIZE_TYPE==1)
#define GUI_TOUCH_AD_BOTTOM     240
#elif (LCD_SIZE_TYPE==2)
#define GUI_TOUCH_AD_BOTTOM     320
#elif (LCD_SIZE_TYPE==3)
#define GUI_TOUCH_AD_BOTTOM     480
#endif

#define GUI_TOUCH_SWAP_XY    0

#define GUI_TOUCH_MIRROR_X   0 //il9325:0; il9320:1

#define GUI_TOUCH_MIRROR_Y   0

#endif /* GUITOUCH_CONF_H */
