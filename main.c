/*
 * Scan Matrix Example #1
 *
 * ==========================================================================
 *
 *  Copyright 2006 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 *
 * ==========================================================================
 */

#include "cmios.h"
#include "pic18f452.h"


/////////////////////////////////////////////////////////////////////////////
// Local variables
/////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "sm_simple.h"

#include "variables.h" //keyboard mapping

#include "midinotes.c"
////////////////////////////////////////////////////////////////////////////
// Global variables
/////////////////////////////////////////////////////////////////////////////


// status of application (see bitfield declaration in main.h)
app_flags_t app_flags;




void Init(void) __wparam
{
	// initialize the shift registers
	MIOS_SRIO_NumberSet(16);           // use up to 16 shift registers
	MIOS_SRIO_UpdateFrqSet(1);         // set update frequency
	// Touch sensor sensitivity *must* be 0, otherwise Port D.4 (CORE::J14) cannot be used as Clock Output
	MIOS_SRIO_TS_SensitivitySet(0);    // disable touch sensors
	// initialize the scan matrix driver
	SM_Init();
}


/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS in the mainloop when nothing else is to do
/////////////////////////////////////////////////////////////////////////////
void Tick(void) __wparam
{
  // call the scan matrix button handler
  SM_ButtonHandler();
}

/////////////////////////////////////////////////////////////////////////////
// This function is periodically called by MIOS. The frequency has to be
// initialized with MIOS_Timer_Set
/////////////////////////////////////////////////////////////////////////////
void Timer(void) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when the display content should be 
// initialized. Thats the case during startup and after a temporary message
// has been printed on the screen
/////////////////////////////////////////////////////////////////////////////

void DISPLAY_Init(void) __wparam
{
	app_flags.DISPLAY_UPDATE_REQ = 1;
	MIOS_LCD_CursorSet(0x00);	//DEBUG
	MIOS_LCD_PrintCString("C64 KEYBOARD TEST");
}




/////////////////////////////////////////////////////////////////////////////
//  This function is called in the mainloop when no temporary message is shown
//  on screen. Print the realtime messages here
/////////////////////////////////////////////////////////////////////////////
void DISPLAY_Tick(void) __wparam
{

  // update display only when requested to minimize the CPU load
  if( !app_flags.DISPLAY_UPDATE_REQ )
    return;
  app_flags.DISPLAY_UPDATE_REQ = 0;


}




/////////////////////////////////////////////////////////////////////////////
//  This function is called by MIOS when a complete MIDI event has been received
/////////////////////////////////////////////////////////////////////////////
void MPROC_NotifyReceivedEvnt(unsigned char evnt0, unsigned char evnt1, unsigned char evnt2) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when a MIDI event has been received
// which has been specified in the MIOS_MPROC_EVENT_TABLE
/////////////////////////////////////////////////////////////////////////////
void MPROC_NotifyFoundEvent(unsigned entry, unsigned char evnt0, unsigned char evnt1, unsigned char evnt2) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when a MIDI event has not been completly
// received within 2 seconds
/////////////////////////////////////////////////////////////////////////////
void MPROC_NotifyTimeout(void) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when a MIDI byte has been received
/////////////////////////////////////////////////////////////////////////////
void MPROC_NotifyReceivedByte(unsigned char byte) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS before the shift register are loaded
/////////////////////////////////////////////////////////////////////////////
void SR_Service_Prepare(void) __wparam
{

  // call the Scan Matrix Driver
  SM_PrepareCol();

}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS after the shift register have been loaded
/////////////////////////////////////////////////////////////////////////////
void SR_Service_Finish(void) __wparam
{
  // call the Scan Matrix Driver
  SM_GetRow();
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when an button has been toggled
// pin_value is 1 when button released, and 0 when button pressed
/////////////////////////////////////////////////////////////////////////////
void DIN_NotifyToggle(unsigned char pin, unsigned char pin_value) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when an encoder has been moved
// incrementer is positive when encoder has been turned clockwise, else
// it is negative
/////////////////////////////////////////////////////////////////////////////
void ENC_NotifyChange(unsigned char encoder, char incrementer) __wparam
{
}




/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when a pot has been moved
/////////////////////////////////////////////////////////////////////////////
void AIN_NotifyChange(unsigned char pin, unsigned int pin_value) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is NOT called by MIOS, but by the scan matrix handler
// in sm_simple.asm, when a pin of the scan matrix has been toggled
// Note: in addition to "pin" and "value", the "sm_button_column" and
// "sm_button_row" are available as global variables (defined in sm_simple.h)
/////////////////////////////////////////////////////////////////////////////



void SM_NotifyToggle(unsigned char pin, unsigned char value) __wparam
{
	MIOS_LCD_CursorSet(0x00);	//DEBUG
	MIOS_LCD_PrintBCD2(pin);	//DEBUG

	//MIOS_LCD_CursorSet(0x40);	//DEBUG
	//MIOS_LCD_PrintBCD2(note_map[pin][1]);	//DEBUG
	MIOS_LCD_PrintCString("/ASCII:");
	MIOS_LCD_PrintChar(note_map[pin][1]);	//DEBUG
	
	MIOS_LCD_PrintCString("/MIDI:");
	MIOS_LCD_PrintBCD2(note_map[pin][0]);	//DEBUG


	GET_NCHR(note_map[pin][0]);

  // print Column and Row
  MIOS_LCD_CursorSet(0x40 + 0);
  MIOS_LCD_PrintCString("Col");
  MIOS_LCD_PrintBCD2(sm_button_column);
  MIOS_LCD_PrintCString("/Row");
  MIOS_LCD_PrintBCD2(sm_button_row);


    //Play note
	MIOS_MIDI_TxBufferPut(144 + 0);//MIDI CHANNEL 1
	MIOS_MIDI_TxBufferPut(note_map[pin][0]+24);// Transpose :  +24
	MIOS_MIDI_TxBufferPut(value ? 0x00 : 0x7f);


	return;
}



