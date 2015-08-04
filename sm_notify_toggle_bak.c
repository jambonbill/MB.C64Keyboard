


/////////////////////////////////////////////////////////////////////////////
// This function is NOT called by MIOS, but by the scan matrix handler
// in sm_simple.asm, when a pin of the scan matrix has been toggled
// Note: in addition to "pin" and "value", the "sm_button_column" and
// "sm_button_row" are available as global variables (defined in sm_simple.h)
/////////////////////////////////////////////////////////////////////////////


void SM_NotifyToggle(unsigned char pin, unsigned char value) __wparam
{
	last_mx_pin=pin;		//MAP KEYBOARD

  
  // send pin number and value as Note On Event
  //MIOS_MIDI_TxBufferPut(0x90);
  //MIOS_MIDI_TxBufferPut(pin);
  //MIOS_MIDI_TxBufferPut(value ? 0x00 : 0x7f);
  
  //MIOS_LCD_PrintBCD1(sm_button_column);
  //MIOS_LCD_PrintCString("*");
  //MIOS_LCD_PrintBCD1(sm_button_row);

	// request display update
	// app_flags.DISPLAY_UPDATE_REQ = 1;



	//Live play mode (keyb)
	if(mode==1){//PLAY
		NOTE(value);
	}



	if(mode==2){//DEBUG MODE
		MIOS_LCD_CursorSet(0x10); // upper right
		MIOS_LCD_PrintCString("#");
		MIOS_LCD_PrintBCD2(pin);//status
		chr=note_map[pin][1];
		MIOS_LCD_PrintChar(chr);//status
		//MIOS_LCD_PrintCString(":");
		//MIOS_LCD_PrintChar(pin);//status
	}else{
		//MIOS_LCD_CursorSet(0x0d); //
		//MIOS_LCD_PrintHex1(arp_n);//status
	}



	// ARPEGGIATOR
	if(mode==4){
		if(value){
			//arppos--;
			rem_arp();
		}else{
			//arppos++;
			add_arp();
		}
	}





	
	if(CTRL && value){
		switch(pin){

			case 17://"P" PATTERN
				PATTERN();
				return;
				break;

			case 25://"I"
				//INPUT=1;//Ctrl + I -> Start reading inkeys
				INKEY(0x00);
				CTRL=0;
				return;
				break;



			case 29://O Load
				LOAD();
				break;
				
			case 33://Y RND
				gen_random_number();
				break;


			case 35://V Paste pattern
				MIOS_LCD_PrintCString("Past");
				break;


			case 39:// B -> Bank select.
				//MIOS_LCD_PrintCString("Past");
				break;


			case 41://"R"
				//RECORD=1;//Ctrl + R -> Start recording pattern
				REC();
				CTRL=0;
				return;
				break;


			case 47://C Copy pattern
				MIOS_LCD_PrintCString("Copy");
				break;

			case 54://S
				SAVE();
				break;

			default:
				break;
		}
	}


	if(INPUT){
		if(value)INKEY(pin);
		return;
	}

	if(RECORD){
		if(value)REC();
		return;
	}


	switch(pin){
		case 0://<- INST/DEL
			//MIOS_LCD_PrintCString("Inst/Del");
			if(COMMODORE && SHIFT)MIOS_Reset();
			break;

		case 1://RETURN
		break;

		case 2://CRSR-
			if(!value){
				prg[midi_channel]++;
				PRG_CHNG();
			}
		break;

		case 3://CRSR|
			if(!value){
				prg[midi_channel]--;
				PRG_CHNG();
			}
		break;

		case 4://F7

			if(!SHIFT){
				//transpose=0;
				TRANSPOSE(0);
			}else{
				TRANSPOSE(48);
			}
			//MIOS_LCD_PrintCString("TRANSPOSE +");
			break;

		case 5://F5

			if(!SHIFT){
				TRANSPOSE(12);
			}else{
				TRANSPOSE(60);
				//transpose=60;
			}
			break;

		case 6://F3

			if(!SHIFT){
				//transpose=24;
				TRANSPOSE(24);
			}else{
				//transpose=72;
				TRANSPOSE(72);
			}
			break;

		case 7://F1

			if(!SHIFT){
				//transpose=36;
				TRANSPOSE(36);
			}else{
				//transpose=84;
				TRANSPOSE(84);
			}
			break;




		case 12:// CLEAR HOME
			MIOS_LCD_Clear();
			ALL_NOTE_OFF();
			def();
			break;



		case 14:// =
		break;

		case 15:// RSHIFT
		break;

		case 16:// +
			if(SHIFT){
				//MIOS_LCD_Clear();
				if(MCLOCK_BPMGet()<255)MCLOCK_BPMSet(MCLOCK_BPMGet()+1);
				break;
			}
			break;



		case 20:// -
			if(SHIFT){
				//MIOS_LCD_Clear();
				if(MCLOCK_BPMGet()>48)MCLOCK_BPMSet(MCLOCK_BPMGet()-1);
				break;
			}


		case 24:// 9 (Shift -> Midi Chn 9)
			if(CTRL){
				midi_channel=8;
				MIDICHN();
				break;
			}
			break;



		case 28:// 0 (Shift -> Midi Chn 10)
			if(CTRL){
				midi_channel=9;
				MIDICHN();
			}
			break;


		case 32:// 7 (Shift -> Midi Chn 7)
			if(CTRL){
				midi_channel=6;
				MIDICHN();
			}
			break;


		case 36:// 8 (Shift -> Midi Chn 8)
			if(CTRL){
				midi_channel=7;
				MIDICHN();
			}
			break;


		case 40:// 5 (Shift -> Midi Chn 5)
			if(CTRL){
				midi_channel=4;
				MIDICHN();
			}
			break;


	
		case 44:// 6 (Shift -> Midi Chn 6)
			if(CTRL){
				midi_channel=5;
				MIDICHN();
			}
			break;

		case 48:// 3 (Shift -> Midi Chn 3)
			if(CTRL){
				midi_channel=2;
				MIDICHN();
				break;
			}
			if(COMMODORE && value){
				MERGER();
				break;
			}
			break;


		case 51:// LSHIFT
			if(value){
				SHIFT=0;
				//MIOS_LCD_PrintCString("     ");
			}else{
				SHIFT=1;
				MIOS_LCD_PrintCString("SHFT");
			}
			break;

		case 52:// 4 (Shift -> Midi Chn 4)
			
			if(COMMODORE){
				mode=4;
			}

			if(CTRL){
				midi_channel=3;
				MIDICHN();
			}
			break;


		case 56:// 1 (Shift -> Midi Chn 1)
			if(COMMODORE){
				mode=1;
			}
			if(CTRL){
				midi_channel=0;
				MIDICHN();
			}
			break;


		case 58:// CTRL

			if(value){
				CTRL=0;
				//MIOS_LCD_PrintCString("    ");
			}else{
				CTRL=1;
				MIOS_LCD_PrintCString("CTRL");
			}
			break;

		case 59:// RUN/STOP
			if(!value)break;
			MIOS_LCD_CursorSet(0x10); // upper right
			if(RUNSTOP==0){
				RUNSTOP=1;
				//MIOS_LCD_PrintCString("RUN ");
				MCLOCK_DoPlay();
			}else{
				MIOS_LCD_PrintCString("STOP");
				STOP();
			}
			break;

		case 60:// 2 (Shift -> Midi Chn 2)
			
			if(COMMODORE){
				mode=2;
				MIOS_LCD_PrintCString("[DEBUG]MODE");
				MIOS_LCD_PrintBCD1(mode);
				break;
			}

			if(CTRL){
				midi_channel=1;
				MIDICHN();
				break;
			}
			break;


		case 62://<- COMMODORE KEY
			
			if(value){
				COMMODORE=0;
				//MIOS_LCD_PrintCString("     ");
				//MIOS_LCD_Clear();
				def();
			}else{
				COMMODORE=1;
				MIOS_LCD_CursorSet(0x00);
				MIOS_LCD_PrintCString("1:PLAY   5:SAVE");
				MIOS_LCD_CursorSet(0x40);
				MIOS_LCD_PrintCString("2:DEBUG  6:EDIT");
				MIOS_LCD_CursorSet(0x80);
				MIOS_LCD_PrintCString("3:MERGER 7:AIN");
				MIOS_LCD_CursorSet(0xc0);
				MIOS_LCD_PrintCString("4:ARPEG  8:MON");
			}
			break;


		case 63://space bar
			if(!value){
				MIOS_LCD_PrintCString("SPAC");
				SPACE=1;
				//MCLOCK_DoPause();

			}else{
				SPACE=0;
				//MIOS_LCD_PrintCString("    ");
			}
			break;

		default: break;
	}
}

