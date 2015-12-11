/*
This is the core graphics library for all our displays, providing a common
set of graphics primitives (points, lines, circles, etc.).  It needs to be
paired with a hardware-specific library for each display device we carry
(to handle the lower-level functions).

Adafruit invests time and resources providing this open source code, please
support Adafruit & open-source hardware by purchasing products from Adafruit!
 
Copyright (c) 2013 Adafruit Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/


#ifdef __AVR__
 #include <avr/pgmspace.h>
#else
  #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif

#include "Adafruit_ftGFX.h"
#include <stdint.h>

#ifndef _fonts_h
#include "fonts.h"
#endif

Adafruit_GFX::Adafruit_GFX(int16_t w, int16_t h):
  WIDTH(w), HEIGHT(h)
{
  _width    = WIDTH;
  _height   = HEIGHT;
  rotation  = 0;
  cursor_y  = cursor_x    = 0;
  textsize  = 1;
  textcolor = textbgcolor = 0xFFFF;
  wrap      = true;
  setFont(OPENSANSBOLD_12);		
  }

void Adafruit_GFX::setFont(uint8_t f) {
  font = f;
  switch(font) {

 	#ifdef OPENSANSBOLD_10
	case OPENSANSBOLD_10:
		fontProp = &Open_Sans_Bold_10ptProperties;
		fontData = Open_Sans_Bold_10ptBitmaps;
		fontDesc = Open_Sans_Bold_10ptDescriptors2;
		fontKern = 0;
		break;
	#endif
	
	#ifdef OPENSANSBOLD_12
	case OPENSANSBOLD_12:
		fontProp = &Open_Sans_Bold_12ptProperties;
		fontData = Open_Sans_Bold_12ptBitmaps;
		fontDesc = Open_Sans_Bold_12ptDescriptors2;
		fontKern = 0;
		break;
	#endif
	
	#ifdef OPENSANSBOLD_14
	case OPENSANSBOLD_14:
		fontProp = &Open_Sans_Bold_14ptProperties;
		fontData = Open_Sans_Bold_14ptBitmaps;
		fontDesc = Open_Sans_Bold_14ptDescriptors2;
		fontKern = 0;
		break;
	#endif
	
	#ifdef OPENSANSBOLD_16
	case OPENSANSBOLD_16:
		fontProp = &Open_Sans_Bold_16ptProperties;
		fontData = Open_Sans_Bold_16ptBitmaps;
		fontDesc = Open_Sans_Bold_16ptDescriptors2;
		fontKern = 0;
		break;
	#endif
	
	#ifdef OPENSANSBOLD_18
	case OPENSANSBOLD_18:
		fontProp = &Open_Sans_Bold_18ptProperties;
		fontData = Open_Sans_Bold_18ptBitmaps;
		fontDesc = Open_Sans_Bold_18ptDescriptors2;
		fontKern = 0;
		break;
	#endif
	
	#ifdef OPENSANSBOLD_20
	case OPENSANSBOLD_20:
		fontProp = &Open_Sans_Bold_20ptProperties;
		fontData = Open_Sans_Bold_20ptBitmaps;
		fontDesc = Open_Sans_Bold_20ptDescriptors2;
		fontKern = 0;
		break;
	#endif
	
	#ifdef OPENSANSBOLD_24
	case OPENSANSBOLD_24:
		fontProp = &Open_Sans_Bold_24ptProperties;
		fontData = Open_Sans_Bold_24ptBitmaps;
		fontDesc = Open_Sans_Bold_24ptDescriptors2;
		fontKern = 0;
		break;
	#endif
	
	#ifdef SEGMENT7_24
	case SEGMENT7_24:
		fontProp = &Segment7_Standard_24ptProperties;
		fontData = Segment7_Standard_24ptBitmaps;
		fontDesc = Segment7_Standard_24ptDescriptors2;
		fontKern = 0;
		break;
	#endif
	
	#ifdef SEGMENT7_12
	case SEGMENT7_12:
		fontProp = &Segment7_Standard_12ptProperties;
		fontData = Segment7_Standard_12ptBitmaps;
		fontDesc = Segment7_Standard_12ptDescriptors2;
		fontKern = 0;
		break;
	#endif
	
	#ifdef SEGMENT7_36
	case SEGMENT7_36:
		fontProp = &Segment7_Standard_36ptProperties;
		fontData = Segment7_Standard_36ptBitmaps;
		fontDesc = Segment7_Standard_36ptDescriptors2;
		fontKern = 0;
		break;
	#endif

 	default:
    font = OPENSANSBOLD_12;
	  fontProp = &Open_Sans_Bold_12ptProperties;
    fontData = Open_Sans_Bold_12ptBitmaps;
	  fontDesc = Open_Sans_Bold_12ptDescriptors2;
    fontKern = 0;
     break;
  }

  //fontStart = pgm_read_byte(fontData+FONT_START);
  //fontEnd = pgm_read_byte(fontData+FONT_END);

}

// Draw a circle outline
void Adafruit_GFX::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0  , y0+r, color);
  drawPixel(x0  , y0-r, color);
  drawPixel(x0+r, y0  , color);
  drawPixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

void Adafruit_GFX::drawCircleHelper( int16_t x0, int16_t y0,
               int16_t r, uint8_t cornername, uint16_t color) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    } 
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}

void Adafruit_GFX::fillCircle(int16_t x0, int16_t y0, int16_t r,
			      uint16_t color) {
  drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}

// Used to do circles and roundrects
void Adafruit_GFX::fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
    uint8_t cornername, int16_t delta, uint16_t color) {

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

// Bresenham's algorithm - thx wikpedia
void Adafruit_GFX::drawLine(int16_t x0, int16_t y0,
			    int16_t x1, int16_t y1,
			    uint16_t color) {
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

// Draw a rectangle
void Adafruit_GFX::drawRect(int16_t x, int16_t y,
			    int16_t w, int16_t h,
			    uint16_t color) {
  drawFastHLine(x, y, w, color);
  drawFastHLine(x, y+h-1, w, color);
  drawFastVLine(x, y, h, color);
  drawFastVLine(x+w-1, y, h, color);
}

void Adafruit_GFX::drawFastVLine(int16_t x, int16_t y,
				 int16_t h, uint16_t color) {
  // Update in subclasses if desired!
  drawLine(x, y, x, y+h-1, color);
}

void Adafruit_GFX::drawFastHLine(int16_t x, int16_t y,
				 int16_t w, uint16_t color) {
  // Update in subclasses if desired!
  drawLine(x, y, x+w-1, y, color);
}

void Adafruit_GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
			    uint16_t color) {
  // Update in subclasses if desired!
  for (int16_t i=x; i<x+w; i++) {
    drawFastVLine(i, y, h, color);
  }
}

void Adafruit_GFX::fillScreen(uint16_t color) {
  fillRect(0, 0, _width, _height, color);
}

// Draw a rounded rectangle
void Adafruit_GFX::drawRoundRect(int16_t x, int16_t y, int16_t w,
  int16_t h, int16_t r, uint16_t color) {
  // smarter version
  drawFastHLine(x+r  , y    , w-2*r, color); // Top
  drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
  drawFastVLine(x    , y+r  , h-2*r, color); // Left
  drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
  // draw four corners
  drawCircleHelper(x+r    , y+r    , r, 1, color);
  drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

// Fill a rounded rectangle
void Adafruit_GFX::fillRoundRect(int16_t x, int16_t y, int16_t w,
				 int16_t h, int16_t r, uint16_t color) {
  // smarter version
  fillRect(x+r, y, w-2*r, h, color);

  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

// Draw a triangle
void Adafruit_GFX::drawTriangle(int16_t x0, int16_t y0,
				int16_t x1, int16_t y1,
				int16_t x2, int16_t y2, uint16_t color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}

// Fill a triangle
void Adafruit_GFX::fillTriangle ( int16_t x0, int16_t y0,
				  int16_t x1, int16_t y1,
				  int16_t x2, int16_t y2, uint16_t color) {

  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1,
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }
}

void Adafruit_GFX::drawBitmap(int16_t x, int16_t y,
			      const uint8_t *bitmap, int16_t w, int16_t h,
			      uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++ ) {
      if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
	drawPixel(x+i, y+j, color);
      }
    }
  }
}

uint16_t Adafruit_GFX::getStringWidth(String s){
	uint8_t i=0;
	uint16_t w=0;
	//uint8_t c=s[0];
	while(uint8_t c=s[i++]){
		w+=pgm_read_byte(&fontDesc[c-0x20].xAdvance)+fontKern;
	}
	return w;
}

uint8_t Adafruit_GFX::getCharHeight(){
	return (fontProp->height);
	}
	
size_t Adafruit_GFX::write(uint8_t c) {
  
  if (c == 0x0a || c == 0x0c) {
    cursor_y += fontProp->height;	//all chars are same height so use height of space char
    cursor_x  = 0;
	Serial.print("cr/lf\n");
  } else {
    drawFastChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize); 				// draw character "c"

	uint16_t w = pgm_read_byte(&fontDesc[c-0x20].xAdvance);							// get character width
	uint16_t h = fontProp->height;							// get character height
    //if (fontKern > 0 && textcolor != textbgcolor) {										// if necessary, get kerning value
    //  fillRect(cursor_x+w*textsize,cursor_y,fontKern*textsize,h*textsize,textbgcolor);	// fill kenrning space
    //}
    cursor_x += textsize*(w+fontKern);													// advance over kerning 
    if (wrap && (cursor_x > (_width - textsize*w))) {									// line wrap
      cursor_y += textsize*h;
      cursor_x = 0;
    }
  }
  return 1;
}

void Adafruit_GFX::drawFastChar(int16_t x, int16_t y, unsigned char c,
                                    uint16_t color, uint16_t bg, uint8_t size) {
  // Update in subclasses if desired!
  drawChar(x,y,c,color,bg,size);
}

 /*
   * Anatomy of an ft-char
   *
   * the construction and metrics are mainly directly taken from the FreeType definitions of a glyph
   *
   *
   *               +----------------------------+
   *	     	   |							|
   *	           |	          ____yMax    		|
   *               |	    ###### #			 	      y
   *               |	   #      #			        	A
   *               |   +#        #|			      	d
   *               |   | #      # |			      	v
   *		       |   | ######   |			      	a
   *               |   |  #       |			      	n
   *	origin --> +---+---#####--+---+-		    c
   *	           |   | #      # |   |			    e
   *               |  /   ######__/___yMin		  |
   *	          xMin           /    |			|
   *	      	   |		     xMax |	        |
   *               +------xAdvance----+---------+
   *
   *	Spacing from one character to the next				:	xAdvance
   *	Spacing from start of character cell to character	:	xMin
   *	Width of actual character							:	xMax - xMin
   *	Height of actual character							:	yMax - yMin (beware: yMin below base line is 
   +															negative!)
   *	Spacing from one line to the next					:   height
   *
   *    character packing in bitmap array: 
   *		Lines are padded to the next full byte (nine bit wide characters take up 16 Bits etc)
   *		Columns are not padded
   *		every character takes up (xMax - xMin)%8 * (yMax - yMin) bytes
   *		
   *	when writing code using Adafruit_ftGFX ft fonts, you need to be aware of the differing anchor point: 
   *	it's not the top left pixel of the character cell, but the leftmost pixel of the baseline.
   *	the advantage is that all correctly constructed fonts will always sit correctly on the baseline.
   *	the disadvantage is that you may have to observe the yMax value to place text correctly in a cell.
   *
   *	ToDo: provide a function that returns the y offset for the baseline for a selected font
   *	ToDo: find a way to figure out the overall cell size (above and below the baseline) and absolute max 
   *	height of a charset
   *
   *	Drawing:
   *	fill the cell to be inhabited by the character
   *		x=Cursor_x+xMin;
   *		y=Cursor_y-xMax;
   *		w=xMax-xMin;
   *		h=yMax-yMin;
   *		bitmap=*(font start + offset)
   *
   *	icrement cursor_x by xAdvance
   *
   *	The fields are defined in 
   *    typedef struct _FontDescriptor {
   *		int8_t       xMin;
   *		int8_t       xMax;
   *		int8_t       yMin;
   *		int8_t       yMax;
   *		int8_t       xAdvance;
   *		uint16_t     offset;
   *		uint16_t     unicode;
   *		} FontDescriptor;
   *
   */
 
 
// Draw a character
void Adafruit_GFX::drawChar(int16_t x, int16_t y, unsigned char c,
			    uint16_t color, uint16_t bg, uint8_t size) {

	if (c < 0x20 || pgm_read_word(&fontDesc[c-0x20].unicode)==0x0000){										// skip if below 0x40 or non unicode encoded
    c = 0;
	return;
  }
  /*
	if((x >= _width)            || // Clip right										// leave out clipping for now
		(y >= _height)           || // Clip bottom
		((x + (fontDesc[c].width * size) - 1) < 0) || // Clip left
		((y + (fontDesc[c].height * size) - 1) < 0))   // Clip top
		((x + pgm_read_byte(&fontDesc[c].width) * size) - 1) < 0 || // Clip left
		((y + pgm_read_byte(&fontDesc[c].height) * size) - 1) < 0)   // Clip top
	return; 
  */
	
	uint8_t	 ft_byte_count, ft_height, ft_width;
	uint16_t ft_offset;
	
	FontDescriptor ft_fd;
  fontProperties ft_fp;

	//Serial.printf("==================================\nAdafruit_ftGFX::drawChar(0x%02x)=%c\n",c,c);
	
	ft_fd.xMin = pgm_read_byte(&fontDesc[c-0x20].xMin);
	ft_fd.xMax = pgm_read_byte(&fontDesc[c-0x20].xMax);
	ft_fd.yMin = pgm_read_byte(&fontDesc[c-0x20].yMin);
	ft_fd.yMax = pgm_read_byte(&fontDesc[c-0x20].yMax);
	
	ft_fd.xAdvance = pgm_read_byte(&fontDesc[c-0x20].xAdvance);
 	ft_fd.offset   = pgm_read_word(&fontDesc[c-0x20].offset);
	ft_fd.unicode  = pgm_read_word(&fontDesc[c-0x20].unicode);

  ft_fp.height             = fontProp->height;
  ft_fp.ascender           = fontProp->ascender+1;
  ft_fp.descender          = fontProp->descender+1;
  ft_fp.underline_position = fontProp->underline_position+1;
  ft_fp.underline_thickness= fontProp->underline_thickness;
  ft_fp.flags              = fontProp->flags;
 
	Serial.printf("ft_fd{\n");
	Serial.printf("	xMin %d\n", ft_fd.xMin);
	Serial.printf("	xMax %d\n", ft_fd.xMax);
	Serial.printf("	yMin %d\n", ft_fd.yMin);
	Serial.printf("	yMax %d}\n", ft_fd.yMax);

  Serial.printf("ft_fp{\n");
  Serial.printf(" height %d\n", ft_fp.height);
  Serial.printf(" ascender %d\n", ft_fp.ascender);
  Serial.printf(" descender %d\n", ft_fp.descender);
  Serial.printf(" underline_position %d\n", ft_fp.underline_position);
  Serial.printf(" underline_thickness %d\n", ft_fp.underline_thickness);
  Serial.printf(" flags %d}\n", ft_fp.flags);
  
	ft_height  = ft_fd.yMax-ft_fd.yMin; 				// FontHeight
	ft_width   = ft_fd.xMax-ft_fd.xMin;					// FontWidth
	ft_offset  = ft_fd.offset;
/*
  fillRect(x            ,y-ft_fp.ascender  ,ft_fd.xAdvance ,ft_fp.height , bg);
  drawRect(x            ,y-ft_fp.ascender  ,ft_fd.xAdvance ,ft_fp.height , 0xffff);
	for(uint8_t i=0; i<ft_height;i++){
		(ft_width%8)?ft_byte_count=(ft_width >> 3)+1:ft_byte_count=ft_width >> 3; 
		//Serial.printf("	byte_count: 0x%02x\n", ft_byte_count);
		for(uint8_t j=0; j<ft_byte_count;j++){
			uint8_t bitline=pgm_read_byte(fontData+ft_offset++);
			//Serial.printf("bitline: 0x%02x, ",bitline);
			for(uint8_t k=7;k>=0 && k<8;k--){
				(bitline & 1<<k)?drawPixel(x+ft_fd.xMin+(j+1)*8-k,y-ft_fd.yMax+i,color):drawPixel(x+ft_fd.xMin+(j+1)*8-k,y-ft_fd.yMax+i,bg);
				//(bitline & (1<<k))?Serial.printf("@"):Serial.printf(".");
			}
		}
		//Serial.printf("\n");
	}
  Serial.print("====================\n");
  //Serial.printf("x: %d\ny: %d\nw: %d\nh: %d\n", x, y-ft_fd.yAdvance-ft_fd.yMin, ft_fd.xAdvance, ft_fd.yAdvance);
  drawRect(x            ,y-ft_fp.ascender  ,ft_fd.xAdvance ,ft_fp.height , 0xffff);
  */
  y+=ft_fp.ascender;
  fillRect(x            ,y ,ft_fd.xAdvance ,ft_fp.height , bg);
  drawRect(x            ,y ,ft_fd.xAdvance ,ft_fp.height , 0xffff);
	for(uint8_t i=0; i<ft_height;i++){
		(ft_width%8)?ft_byte_count=(ft_width >> 3)+1:ft_byte_count=ft_width >> 3; 
		//Serial.printf("	byte_count: 0x%02x\n", ft_byte_count);
		for(uint8_t j=0; j<ft_byte_count;j++){
			uint8_t bitline=pgm_read_byte(fontData+ft_offset++);
			//Serial.printf("bitline: 0x%02x, ",bitline);
			for(uint8_t k=7;k>=0 && k<8;k--){
				(bitline & 1<<k)?drawPixel(x+ft_fd.xMin+(j+1)*8-k,y-ft_fd.yMax+i,color):drawPixel(x+ft_fd.xMin+(j+1)*8-k,y-ft_fd.yMax+i,bg);
				//(bitline & (1<<k))?Serial.printf("@"):Serial.printf(".");
			}
		}
		//Serial.printf("\n");
	}
  Serial.print("====================\n");
  //Serial.printf("x: %d\ny: %d\nw: %d\nh: %d\n", x, y-ft_fd.yAdvance-ft_fd.yMin, ft_fd.xAdvance, ft_fd.yAdvance);
  drawRect(x            ,y-ft_fp.ascender  ,ft_fd.xAdvance ,ft_fp.height , 0xffff);

}

void Adafruit_GFX::setCursor(int16_t x, int16_t y) {
  cursor_x = x;
  cursor_y = y;
}

void Adafruit_GFX::setTextSize(uint8_t s) {
  textsize = (s > 0) ? s : 1;
}

void Adafruit_GFX::setTextColor(uint16_t c) {
  // For 'transparent' background, we'll set the bg 
  // to the same as fg instead of using a flag
  textcolor = textbgcolor = c;
}

void Adafruit_GFX::setTextColor(uint16_t c, uint16_t b) {
  textcolor   = c;
  textbgcolor = b; 
}

void Adafruit_GFX::setTextWrap(boolean w) {
  wrap = w;
}

uint8_t Adafruit_GFX::getRotation(void) {
  return rotation;
}

void Adafruit_GFX::setRotation(uint8_t x) {
  rotation = (x & 3);
  switch(rotation) {
   case 0:
   case 2:
    _width  = WIDTH;
    _height = HEIGHT;
    break;
   case 1:
   case 3:
    _width  = HEIGHT;
    _height = WIDTH;
    break;
  }
}

// Return the size of the display (per current rotation)
int16_t Adafruit_GFX::width(void) {
  return _width;
}
 
int16_t Adafruit_GFX::height(void) {
  return _height;
}

void Adafruit_GFX::invertDisplay(boolean i) {
  // Do nothing, must be subclassed if supported
}
