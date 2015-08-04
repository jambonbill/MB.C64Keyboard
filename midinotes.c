
const char note_name[12][3] = {
  "C-","C#","D-","D#","E-","F-","F#","G-","G#","A-","A#","B-",
};

/////////////////////////////////////////////////////////////////////////////
// DISPLAY LITTERAL NOTES
/////////////////////////////////////////////////////////////////////////////
void GET_NCHR(unsigned char note){// DISPLAY LITTERAL NOTES !!!

	unsigned char n=0;	// 8bit is enough
	unsigned char oct=0;// octave number

	if(note==0x80){
		MIOS_LCD_CursorSet(0x51);
		MIOS_LCD_PrintCString("NUL");//
		return;
	}

	if(note==0x81){
		MIOS_LCD_CursorSet(0x51);
		MIOS_LCD_PrintCString("PAD");//
		return;
	}

	do{
		oct++;
		n=oct*12;
	}

	while(n<=note);
	oct--;
	//nn=note-12*oct;//Note number

	MIOS_LCD_CursorSet(0x51);
	MIOS_LCD_PrintCString(note_name[note-12*oct]);//
	MIOS_LCD_PrintBCD1(oct);
	return ; 
}

/////////////////////////////////////////////////////////////////////////////
// ALL_NOTE_OFF
/////////////////////////////////////////////////////////////////////////////
void ALL_NOTE_OFF(){//KILL EVERY NOTES 
	//MIOS_MIDI_TxBufferPut(0xB0);//Controller Chn 1
	unsigned char i=0;
	for(i=0;i<15;i++){
		MIOS_MIDI_TxBufferPut(176 + i);//Controller Chn i
		MIOS_MIDI_TxBufferPut(123);//ALL NOTE OFF // http://www.borg.com/~jglatt/tech/midispec/ctllist.htm
		MIOS_MIDI_TxBufferPut(0x00);
	}
	return;
}


/////////////////////////////////////////////////////////////////////////////
// PLAY NOTES FROM KEYBOARD
/////////////////////////////////////////////////////////////////////////////
void KEY_NOTE(unsigned char value) // SEND A NOTE ON KEY PRESS
{
/*
	if(last_mx_pin==0){
		MIOS_LCD_CursorSet(0x80);	
		MIOS_LCD_PrintCString("ALL NOTES OFF");
		ALL_NOTE_OFF();
		return;
	}

	if(note_map[last_mx_pin][0]==0x80){
		return;//Do not send stupid datas !
	}

	MIOS_MIDI_TxBufferPut(144 + midi_channel);
	MIOS_MIDI_TxBufferPut(note_map[last_mx_pin][0]+transpose);
	MIOS_MIDI_TxBufferPut(value ? 0x00 : 0x7f);

	//DISPLAY
	//if(value==0)GET_NCHR(note_map[last_mx_pin][0]+transpose);//keydown only
*/
	return ; 
}
