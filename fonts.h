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

#include "./Fonts/Caladea_Regular_8pt.h"
#include "./Fonts/Caladea_Regular_16pt.h"
#include "./Fonts/Caladea_Regular_24pt.h"

#define CALAREG_8 2
extern const unsigned char Caladea_Regular_8ptBitmaps[];
extern const FontDescriptor Caladea_Regular_8ptDescriptors2[];

#define CALAREG_16 3
extern const unsigned char Caladea_Regular_16ptBitmaps[];
extern const FontDescriptor Caladea_Regular_16ptDescriptors2[];

#define CALAREG_24 4
extern const unsigned char Caladea_Regular_24ptBitmaps[];
extern const FontDescriptor Caladea_Regular_24ptDescriptors2[];

#endif
