int pinCS = 10; // Attach CS to this pin, DIN to MOSI(11) and CLK to SCK(13) (cf http://arduino.cc/en/Reference/SPI )
// CS = 10
// DIN = 11
// CLK = 13
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays, true); // use update fx = + h*v*8 bytes
extern uint8_t font_cp1251_0508[]; // cp1251 font

uint8_t matrix_brightness=0;
uint8_t matrix_delay1=50;


void matrix_init() {
    matrix_set_brightness(matrix_brightness);
	
	// Adjust to your own needs
	//  matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
	//  matrix.setPosition(1, 1, 0); // The second display is at <1, 0>
	//  matrix.setPosition(2, 2, 0); // The third display is at <2, 0>
	//  matrix.setPosition(3, 3, 0); // And the last display is at <3, 0>
	//  ...
	matrix.setRotation(0, 1);
	matrix.setRotation(1, 1);
	matrix.setRotation(2, 1);
	matrix.setRotation(3, 1);
	//matrix.setRotation(3, 2);    // The same hold for the last display
	matrix.setFont(font_cp1251_0508);
	matrix.setTextWrap(false);
	matrix.fillScreen(LOW);
	matrix.update();
}


void matrix_set_brightness(uint8_t b) {
	matrix.setIntensity(b);
}

void matrix_begin() {
	matrix.fillScreen(LOW);
	matrix.setCursor(0,0);
}

void matrix_end() {
	matrix.update();
}

void matrix_end(max7219_update_fx_e fx, bool reverse) {
	matrix.update((max7219_update_fx_e) fx, reverse, matrix_delay1);
}

// only line width
int matrix_text_width(char *s) {
	int w=0;
	if (s) {
		char c;
		while ((c=*(s++))) w+=matrix.getCharWidth(c, 1);
	}
	return w;
}

int matrix_text_width_P(char const *s) {
	int w=0;
	if (s) {
		char c;
		while ((c=pgm_read_byte_near(s++))) w+=matrix.getCharWidth(c, 1);
	}
	return w;
}

void matrix_print(char c) {
	matrix.write(c);
}


void matrix_setCursor(int x, int y) {
	matrix.setCursor(x,y);
}

void matrix_print(char* s) {
	if (!s) return;
	char c;
	while ((c = *(s++))) {
		matrix.write(c);
		//todo: check if position is out of disp range
	}
}

void matrix_print(char* s, int xOffset=0, int width=0) {
	if (!s) return;
	int x = matrix.getCursorX()-xOffset;
	int y = matrix.getCursorY();
	if (y>=matrix.height() || y<-matrix.font_height) return;
	int xMax = min(width>0? x+width : matrix.width(), matrix.width())-1;
//Serial.print("xMax="); Serial.println(xMax);
	byte c;
	while ((c=*s++) &&x<=xMax) {
		int cw = matrix.drawChar(x, y, c, HIGH, LOW, 1);
		// Serial.print("drawChar "); Serial.print(c); Serial.print(" width="); Serial.println(cw);
		x+=cw;
		// todo: move coordinates
	}
	
	// fill rest part of line
	// todo: not necessary if full display repaint
	if (x<=xMax) {
		int x0 = max(x, 0);
		int y0 = max(y, 0);
		matrix.fillRect(x0, y0, xMax-x, matrix.font_height, LOW);
	}
}

void matrix_print_P(const char* s, int xOffset, int width)
{
	if (!s) return;
	int x = matrix.getCursorX()-xOffset;
	int y = matrix.getCursorY();
	if (y>=matrix.height() || y<-matrix.font_height) return;
	int xMax = min(width>0? x+width : matrix.width(), matrix.width())-1;
	byte c;
	while ((c=pgm_read_byte_near(s++)) &&x<=xMax) {
		int cw = matrix.drawChar(x, 0, c, HIGH, LOW, 1);
		// Serial.print("drawChar "); Serial.print(c); Serial.print(" width="); Serial.println(cw);

		// todo: check if it's visible
		x+=cw;
	}

	// fill rest part of line 
	// todo: not necessary if full display repaint
	if (x<=xMax) {
		int x0 = max(x, 0);
		int y0 = max(y, 0);
		matrix.fillRect(x0, y0, xMax-x, matrix.font_height, LOW);
	}
}



void matrix_now_print(char *s, int xOffset, uint8_t delayAfter) {
	matrix_begin();
	matrix_print(s, xOffset, 0);  // auto width
	matrix_end();
	if (delayAfter) delay(delayAfter);
}



void matrix_now_print_P(const char *s, int xOffset, uint8_t delayAfter) {
	matrix_begin();
	matrix_print_P(s, xOffset, 0);
	matrix_end();
	if (delayAfter) delay(delayAfter);
}


// print integer number
// no wrap support!
void matrix_printNumI(int16_t value, uint8_t fixedWidth) {
	int x = matrix.getCursorX();
	int y = matrix.getCursorY();
	
	if (value<0) {
		x+=matrix.drawChar(x, y, '-', HIGH, LOW, 1); // todo: process warp char?
		value = abs(value);
	}

	uint8_t w=0; //=fixedWidth;
	uint8_t zeroWidth = matrix.getCharWidth('0', 1);
	int v=value;
	// auto determine width
	for (uint8_t i=0; !fixedWidth || i<fixedWidth; i++) {
		if (v>0) {
			x+=matrix.getCharWidth('0'+v%10, 1); // todo: wrap?
			v/=10;
		} 
		else {
			if (!fixedWidth) break;
			x+=zeroWidth;
		}
		w++;
	}
	if (!w) { 
		x+=zeroWidth;
		w++; // zero has 1 digit
	}
	
	// set it's position (as at end of operation)
	matrix.setCursor(x, y);
	
	// convert
	for (int i=0; i<w;i++) {
		uint8_t d = value % 10;
		char c = '0'+d;
		x-=matrix.getCharWidth('0' + value%10, 1);
		matrix.drawChar(x, y, c, HIGH, LOW, 1); // todo: wrap?
		value/=10;
	}
}

void matrix_printNumFloat(float value, uint8_t fixedWidth, uint8_t decDigs) {

	if (!decDigs) {
		matrix_printNumI(round(value), fixedWidth);
		return;
	}

	int x = matrix.getCursorX();
	int y = matrix.getCursorY();

	if (value<0) {
		x+=matrix.drawChar(x, y, '-', HIGH, LOW, 1); // todo: process warp char?
		value = abs(value);
	}
	
	// make its integer
	for(uint8_t i=0; i<decDigs;i++) value*=10;
	long valueI = round(value); // just long!

	uint8_t zeroWidth = matrix.getCharWidth('0', 1);
	uint8_t pointWidth = matrix.getCharWidth('.', 1);
	
	// auto determine width
	long v = valueI;
	uint8_t w=0; //=fixedWidth;
	for (uint8_t i=0;!fixedWidth || i<fixedWidth; i++) {
//Serial.print("x="); Serial.println(x);

		if (v>0) {
			x+=matrix.getCharWidth('0'+(v % 10), 1); // todo: wrap?
			v/=10;
		} 
		else {
			if (!fixedWidth) break;
			x+=zeroWidth;
		}
		w++;
	}
	// zero has 1 digit
 	if (!w) { 
		x+=zeroWidth;
		w++;
	}
	// add decimal point
	x+=pointWidth;
	w++;
// Serial.print("w="); Serial.print(w);Serial.print("\tx="); Serial.print(x);

	// set it's position (as at end of operation)
	matrix.setCursor(x, y);
	
	// convert
	for (int i=0; i<w;i++) {
		char c;
		if (!decDigs) {
			c='.';
			x-=pointWidth;
			decDigs=0xff;
		}
		else {
			c = '0'+(valueI % 10);
			x-=matrix.getCharWidth(c, 1);
			valueI/=10;
			if (decDigs) decDigs--;
		}
		matrix.drawChar(x, y, c, HIGH, LOW, 1); // todo: wrap?
	}
}




void matrix_scroll_text(char *s, bool scrollIn, bool scrollOut) {
	int sw = matrix_text_width(s);
	int w = matrix.width();

	// Serial.print("matrix width="); Serial.println(w);
	// Serial.print("text width="); Serial.println(sw);

	int xOffset;
	if (scrollIn) {
		xOffset=-w+1;
		while (xOffset<0) {
			matrix_now_print(s, xOffset, matrix_delay1);
			xOffset++;
		}
	} else xOffset=0;

	matrix_now_print(s, xOffset, true);

	if (scrollOut) {
		while (xOffset<sw) {
			xOffset++;
			matrix_now_print(s, xOffset, matrix_delay1);
		}
	}
}

void matrix_scroll_text_P(const char *s, bool scrollIn, bool scrollOut) {
	int sw = matrix_text_width_P(s);
	int w = matrix.width();

	// Serial.print("matrix width="); Serial.println(w);
	// Serial.print("text width="); Serial.println(sw);

	int xOffset;
	if (scrollIn) {
		xOffset=-w+1;
		while (xOffset<0) {
			matrix_now_print_P(s, xOffset, matrix_delay1);
			xOffset++;
		}
	} else xOffset=0;

	matrix_now_print_P(s, xOffset, matrix_delay1);

	if (scrollOut) {
		while (xOffset<sw) {
			xOffset++;
			matrix_now_print_P(s, xOffset, matrix_delay1);
		}
	}
}



void matrix_fade(bool trueForIn, bool clearAfterOut) {
	if (trueForIn) {
		for (uint8_t b = 1; b<=matrix_brightness; b++) {
			matrix.setIntensity(b);
			delay(matrix_delay1);
		}
		} else {
		for (int b = matrix_brightness-1; b >= 0; b--) {
			matrix.setIntensity(b);
			delay(matrix_delay1);
		}
		if (clearAfterOut) {
			matrix_begin();
			matrix_end();
			matrix.setIntensity(matrix_brightness);
		}
	}
}

void matrix_flash() {
	int b = matrix_brightness;
	uint8_t b_h = max(b+5, matrix_brightness);
	uint8_t b_l = min(0, b-2);
	b--;
	while (b>=b_l) {
		matrix.setIntensity(b);
		delay(matrix_delay1>>2);
		b--;
	}
	
	b++;
	
	while (b<=b_h) {
		matrix.setIntensity(b);
		delay(matrix_delay1>>1);
		b++;
	}
	
	b--;
	while (b>=matrix_brightness) {
		matrix.setIntensity(b);
		delay(matrix_delay1>>2);
		b--;
	}
}