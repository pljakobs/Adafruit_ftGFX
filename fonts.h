//
//  fonts.h
//  
#include <stdint.h>

typedef struct _FontDescriptor {
  int8_t       xMin;
  int8_t       xMax;
  int8_t       yMin;
  int8_t       yMax;
  int8_t       xAdvance;
  int8_t       yAdvance;
  uint16_t     offset;
  uint16_t     unicode;
} FontDescriptor;
/*
#ifndef _font_h
#include "font.h"
#endif
*/

#ifndef _fonts_h
#define _fonts_h
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

#include "./Fonts/Open_Sans_Regular_12pt.h"
#define OPENSANSREG_12 1
extern const unsigned char Open_Sans_Regular_12ptBitmaps[];
extern const FontDescriptor Open_Sans_Regular_12ptDescriptors2[];

#include "./Fonts/Open_Sans_Bold_12pt.h"
#define OPENSANSBOLD_12 2
extern const unsigned char Open_Sans_Bold_12ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_12ptDescriptors2[];

#include "./Fonts/Open_Sans_Regular_14pt.h"
#define OPENSANSREG_14 3
extern const unsigned char Open_Sans_Regular_14ptBitmaps[];
extern const FontDescriptor Open_Sans_Regular_14ptDescriptors2[];

#include "./Fonts/Open_Sans_Bold_14pt.h"
#define OPENSANSBOLD_14 4
extern const unsigned char Open_Sans_Bold_14ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_14ptDescriptors2[];

#include "./Fonts/Open_Sans_Regular_24pt.h"
#define OPENSANSREG_24 5
extern const unsigned char Open_Sans_Regular_24ptBitmaps[];
extern const FontDescriptor Open_Sans_Regular_24ptDescriptors2[];

#include "./Fonts/Open_Sans_Bold_24pt.h"
#define OPENSANSBOLD_24 6
extern const unsigned char Open_Sans_Bold_24ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_24ptDescriptors2[];

#include "./Fonts/Open_Sans_Regular_36pt.h"
#define OPENSANSREG_36 5
extern const unsigned char Open_Sans_Regular_36ptBitmaps[];
extern const FontDescriptor Open_Sans_Regular_36ptDescriptors2[];

#include "./Fonts/Open_Sans_Bold_36pt.h"
#define OPENSANSBOLD_36 6
extern const unsigned char Open_Sans_Bold_36ptBitmaps[];
extern const FontDescriptor Open_Sans_Bold_36ptDescriptors2[];

#endif
