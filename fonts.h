//
//  fonts.h
//  
#include <stdint.h>
/*
#ifndef _font_h
#include "font.h"
#endif
*/

#ifndef _fonts_h
#define _fonts_h

typedef struct _FontProperties {
  uint8_t      height;
  int8_t       ascender;
  int8_t       descender;
  int8_t       underline_position;
  uint8_t      underline_thickness;
  int16_t      flags;
  char         family[32];
  char         style[32];
} FontProperties;

typedef struct _FontDescriptor {
  int8_t       xMin;
  int8_t       xMax;
  int8_t       yMin;
  int8_t       yMax;
  int8_t       xAdvance;
  uint16_t     offset;
  uint16_t     unicode;
} FontDescriptor;

/*
#include "./Fonts/Liberation_Mono_Bold_8pt.h"
#include "./Fonts/Liberation_Mono_Bold_12pt.h"
#include "./Fonts/Liberation_Mono_Bold_16pt.h"

#define LIBMONOBOLD_12 2
extern const unsigned char Liberation_Mono_Bold_8ptBitmaps[];
extern const FontDescriptor Liberation_Mono_Bold_8ptDescriptors2[];

#define LIBMONOBOLD_12 2
extern const unsigned char Liberation_Mono_Bold_12ptBitmaps[];
extern const FontDescriptor Liberation_Mono_Bold_12ptDescriptors2[];

#define LIBMONOBOLD_12 2
extern const unsigned char Liberation_Mono_Bold_16ptBitmaps[];
extern const FontDescriptor Liberation_Mono_Bold_16ptDescriptors2[];
*/

//#include "./Fonts/Waree_Book.h"
//#include "./Fonts/Waree_Bold.h"
//#include "./Fonts/Waree_Oblige.h"
//#include "./Fonts/Waree_BoldOblige.h"


#include "./Fonts/Open_Sans_Bold_10pt.h"
#define OPENSANSBOLD_10 1
extern const FontProperties Open_Sans_Bold_10ptProperties;
extern const unsigned char Open_Sans_Bold_10ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_10ptDescriptors2[];

#include "./Fonts/Open_Sans_Bold_12pt.h"
#define OPENSANSBOLD_12 2
extern const FontProperties Open_Sans_Bold_12ptProperties;
extern const unsigned char Open_Sans_Bold_12ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_12ptDescriptors2[];

#include "./Fonts/Open_Sans_Bold_14pt.h"
#define OPENSANSBOLD_14 3
extern const FontProperties Open_Sans_Bold_14ptProperties;
extern const unsigned char Open_Sans_Bold_14ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_14ptDescriptors2[];

#include "./Fonts/Open_Sans_Bold_16pt.h"
#define OPENSANSBOLD_16 4
extern const FontProperties Open_Sans_Bold_16ptProperties;
extern const unsigned char Open_Sans_Bold_16ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_16ptDescriptors2[];

#include "./Fonts/Open_Sans_Bold_18pt.h"
#define OPENSANSBOLD_18 5
extern const FontProperties Open_Sans_Bold_18ptProperties;
extern const unsigned char Open_Sans_Bold_18ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_18ptDescriptors2[];

#include "./Fonts/Open_Sans_Bold_20pt.h"
#define OPENSANSBOLD_20 6
extern const FontProperties Open_Sans_Bold_20ptProperties;
extern const unsigned char Open_Sans_Bold_20ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_20ptDescriptors2[];

#include "./Fonts/Open_Sans_Bold_24pt.h"
#define OPENSANSBOLD_24 8
extern const FontProperties Open_Sans_Bold_24ptProperties;
extern const unsigned char Open_Sans_Bold_24ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_24ptDescriptors2[];

#include "./Fonts/Open_Sans_Bold_28pt.h"
#define OPENSANSBOLD_28 10
extern const FontProperties Open_Sans_Bold_28ptProperties;
extern const unsigned char Open_Sans_Bold_28ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_28ptDescriptors2[];

/*
#include "./Fonts/Segment7_Standard_12pt.h"
#define SEGMENT7_12 11
extern const FontProperties Segment7_Standard_12Properties;
extern const unsigned char Segment7_Standard_12ptBitmaps[];
extern const FontDescriptor Segment7_Standard_12ptDescriptors2[];

#include "./Fonts/Segment7_Standard_24pt.h"
#define SEGMENT7_24 12
extern const FontProperties Segment7_Standard_24Properties;
extern const unsigned char Segment7_Standard_24ptBitmaps[];
extern const FontDescriptor Segment7_Standard_24ptDescriptors2[];

#include "./Fonts/Segment7_Standard_36pt.h"
#define SEGMENT7_36 13
extern const FontProperties Segment7_Standard_36Properties;
extern const unsigned char Segment7_Standard_36ptBitmaps[];
extern const FontDescriptor Segment7_Standard_36ptDescriptors2[];
*/
#endif
