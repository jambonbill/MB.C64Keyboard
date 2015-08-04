






const char note_map[64][2] = { // 1st value : note  - 2nd value : ASCII CODE
// <- 1 char ->
	{0x80,63},	// 0 - INST/DEL
	{0x80,63},	// 1 - RETURN
	{0x80,0x7E},	// 2 - CRSR RIGHT
	{0x80,0x7F},	// 3 - CRSR LEFT
	{0x80,0xC0},	// 4 - F7
	{0x80,0xC1},	// 5 - F5
	{0x80,0xC2},	// 6 - F3
	{0x80,0xC3},	// 7 - F1
	{32,36},	// 8 - �
	{31,42},	// 9 - *
	{0x80,93},	//10 - ]
	{16,63},//11 - ?
	{0x80,0xDB},	//12 RIGHT SHIFT
	{0x80,61},	//13 - "="
	{33,63},	//14 - "UP"
	{34,63},	//15 - CLEAR/HOME
		{0x80,43},// 16 - "+"
	{28,80},// 17 - pP
	{13,76},// 18 - lL
	{12,60},	// 19 - <
	{14,62},	// 20 - >
	{15,91},// 21 - [
	{29,64},	// 22 - @
	{30,45},	// 23 - "-"
	{25,57},// 24 - NUM : 9
	{24,73},// 25 - iI
	{10,74},// 26 - jJ
	{9,78},	// 27 - nN
	{11,77},// 28 - mM
	{0x80,75},// 29 - kK
	{26,79},	// 30 - oO
	{27,48},// 31 - NUM : 0
		{22,55},//32 - NUM : 7
	{21,89},// 33 - yY
	{6,71},	// 34 - gG
	{5,86},	// 35 - vV
	{7,66},	// 36 - bB
	{8,72},// 37 - H
	{23,85},	// 38 - H
	{0x80,56},	// 39 - NUM : 8
	{18,53},// 40 - NUM : 5
	{17,82},// 41 - rR
	{3,68},	// 42 - dD
	{2,88},	// 43 - xX
	{4,67},	// 44 - cC
	{0x80,70},	// 45 - fF
	{19,84},	// 46 - tT
	{20,54},	// 47 - NUM :6
		{15,51},// 48 - NUM :3
	{14,87},// 49 - wW
	{0x80,65},	// 50 - aA
	{0x80,0xDB},	// 51 - LEFT SHIFT
	{0,90},	// 52 - zZ
	{1,83},// 53 - sS
	{16,69},	// 54 - eE
	{0x80,52},	// 55 - NUM :4
	{0x80,49},	// 56 NUM :1
	{0x80,0xF8},	// 57 - ESC
	{0x80,0xFF},	// 58 - CTRL
	{0x80,0xE0},	// 59 - RUN/STOP
	{0x80,0x20},// 60 - SPACEBAR
	{0x80,0xFC},// 61 -COMMODORE
	{12,81},	// 62 - qQ
	{13,50},	// 63 - NUM :2
};
