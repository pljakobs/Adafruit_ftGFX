#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include <ft2build.h>
#include <ftglyph.h>

#include <font.h>

#include FT_FREETYPE_H
#include FT_TRUETYPE_IDS_H

void beautify(char s[]){
  fprintf(stderr,"in string: %s", s);
  int i=0;
  while(s[i]!='\0'){
    if(s[i]==0x20) s[i]=0x5f;
    i++; 
  }
  fprintf(stderr,"%s",s);
}

int main( int argc, char** argv )
{
 
  FontDescriptor fontdescriptor[256];
  FT_Library    library;
  FT_Face       face;
  FT_CharMap    xcm; 
  FT_Glyph      glyph;
  FT_GlyphSlot  slot;
  FT_Matrix     matrix;                 /* transformation matrix */
  FT_Vector     pen;                    /* untransformed origin  */
  FT_Error      error;
  FT_CharMap    charmap;
  FT_BBox       bbox;

  FILE*         file;

  char*         filename;
  char*         text;
  char          pixbuff[256];

  int           c,glyph_index;
  int           target_height;
  int           n, num_chars;
  int           i,j,p,q,offset;
  int           size;

  if ( argc != 3 )
  {
    fprintf ( stderr, "usage: %s font size\n", argv[0] );
    exit( 1 );
  }

  filename      = argv[1];                           /* first argument     */
  size          = atoi(argv[2]);
  fprintf(stderr,"font size %d\n", size);

  fprintf(stderr,"opening library\n");
  error = FT_Init_FreeType( &library );
  if ( error )
  {
    fprintf(stderr,"Error initializing FreeType Library, Code %d", error);
    return(error);
  }else{
    fprintf(stderr,"library opened\n");
  }

  fprintf(stderr,"loading font %s\n", filename);

  error = FT_New_Face( library, filename, 0, &face );
  if ( error )
  {
    fprintf(stderr, "Error error loading Font %s, Code %d", filename, error);
    FT_Done_FreeType(library);
    return(error);
  }else{
    fprintf(stderr,"font face loaded\n");
  }

  char* family_name=face->family_name;
  beautify(family_name);
  char* style_name=face->style_name;
  beautify(style_name);

  fprintf(stderr,"opened %s\n", family_name);
  fprintf(stderr,"       %s\n", style_name);
  fprintf(stderr,"number Glyphs %d\n", face->num_glyphs);

  char* filename_o=malloc(snprintf(NULL,0,"%s_%s_%dpt.c", face->family_name, face->style_name, size)+1);
  sprintf(filename_o,"%s_%s_%dpt.h", face->family_name, face->style_name, size);
  fprintf(stderr,"will output to file %s\n", filename_o);
  file=fopen(filename_o, "w+");
  
  int ff=face->face_flags;
  ff & FT_FACE_FLAG_SCALABLE ? fprintf(stderr,"is scalable\n"):fprintf(stderr,"is fixed size\n");
  ff & FT_FACE_FLAG_FIXED_WIDTH ? fprintf(stderr,"is fixed width\n"):fprintf(stderr,"is porportional width\n");
  ff & FT_FACE_FLAG_SFNT ? fprintf(stderr,"is SFNT formatted\n"):fprintf(stderr,"is not SFNT formatted\n");
  ff & FT_FACE_FLAG_HORIZONTAL ? fprintf(stderr,"contains horizontal glyph metrics\n"):fprintf(stderr,"n");
  ff & FT_FACE_FLAG_TRICKY ? fprintf(stderr,"this is a tricky font\n"):fprintf(stderr,"no tricks here\n");

  int FSType_flags=FT_Get_FSType_Flags(face);
  fprintf(stderr,"Checking embedding flags %d \n",FSType_flags);
  if (FSType_flags == FT_FSTYPE_INSTALLABLE_EMBEDDING) {
    fprintf(stderr,"  can be embedded without condition\n");
  }else if(FSType_flags & FT_FSTYPE_RESTRICTED_LICENSE_EMBEDDING){
    fprintf(stderr,"  can not be freely modified, embedded or exchanged without obtaining a license\n");
  }else if(FSType_flags & FT_FSTYPE_PREVIEW_AND_PRINT_EMBEDDING){
    fprintf(stderr,"  can be embedded for preview and print\n");
  }else if(FSType_flags & FT_FSTYPE_EDITABLE_EMBEDDING){
    fprintf(stderr,"  can be embedded for editing, preview and printing\n");
  }else if(FSType_flags & FT_FSTYPE_NO_SUBSETTING){
    fprintf(stderr,"  can not be subsetted prior to embedding\n");
  }else if(FSType_flags & FT_FSTYPE_BITMAP_EMBEDDING_ONLY){
    fprintf(stderr,"  can only be embedded by way of contained bitmaps\n");
  }

  charmap=face->charmap;
  fprintf(stderr,"current charmap: %d, %d\n",charmap->platform_id, charmap->encoding_id);
  int cm = face->num_charmaps;
  fprintf(stdout,"found %d charmaps\n", cm);
  
  FT_Set_Char_Size(face, size*64,0,72,0);
  fprintf(file,"const unsigned char %s_%s_%dptBitmaps[] PROGMEM = {\n", face->family_name, face->style_name, size);
 
  offset=0;
  for(c=0x20;c<=255;c++){
    if(FF_encoding[c]){
      error=FT_Load_Char(face, FF_encoding[c], FT_LOAD_RENDER);
      if (error){
        fprintf(stderr,"failed loading char %c, mapped to %s", c, FF_encoding[c]);
        fprintf(stderr," error %d\n",error);
      }

      slot=face->glyph;

      FT_Bitmap* b_test;
      b_test=&slot->bitmap;

      error=FT_Render_Glyph(slot, FT_RENDER_MODE_MONO);
      if (error){
        fprintf(stderr,"failed rendering char %c, ",c);
        fprintf(stderr,"error %d\n",error);
      }
      FT_Glyph my_glyph;
      error=FT_Get_Glyph(face->glyph, &my_glyph);
      FT_Glyph_Get_CBox(my_glyph, FT_GLYPH_BBOX_PIXELS , &bbox );
      
      fontdescriptor[c].xMin     = bbox.xMin;
      fontdescriptor[c].xMax     = bbox.xMax;
      fontdescriptor[c].yMin     = bbox.yMin;
      fontdescriptor[c].yMax     = bbox.yMax;
      fontdescriptor[c].offset   = offset;
      fontdescriptor[c].xAdvance = slot->advance.x;
      fontdescriptor[c].yAdvance = slot->advance.y;
      fontdescriptor[c].unicode  = FF_encoding[c];

      for(i=0;i<=b_test->rows-1;i++){
       q=7;
       uint8_t c_byte=0;
        for(j=0;j<=b_test->width-1;j++){
          if(b_test->buffer[i*b_test->width+j]>127) c_byte|=1<<q;
          if(q--<0){
            fprintf(file,"0x%02x, ",c_byte);
            offset++;
            c_byte=0;
            q=7;
          }
        }
        fprintf(file,"0x%02x",c_byte);
        (c<255 || i<=b_test->rows)?fprintf(file,", "):fprintf(file," ");
        offset++;
      }
      c==92?fprintf(file,"//0x%02x <Backslash>\n",c):fprintf(file,"// 0x%02x, U-%04x, %c\n",c,FF_encoding[c],c);
    }else{
      fontdescriptor[c].xMin=0;
      fontdescriptor[c].xMax=0;
      fontdescriptor[c].yMin=0;
      fontdescriptor[c].yMax=0;
      fontdescriptor[c].xAdvance=0;
      fontdescriptor[c].yAdvance=0;
      fontdescriptor[c].offset=0;
      fontdescriptor[c].unicode=0;
    }
  }
  fprintf(file,"};\n\n");
  fprintf(file,"const FontDescriptor %s_%s_%dptDescriptors2[] PROGMEM = {\n", face->family_name, face->style_name, size);
  for(c=0x40;c<=0xff;c++){
    fprintf(file, "\t{ (uint8_t)0x%02x, (uint8_t)0x%02x, (uint8_t)0x%02x, (uint8_t)0x%02x, (uint8_t)0x%02x, (uint8_t)0x%02x, (uint16_t)0x%04x, (uint16_t)0x%04x}", 
        fontdescriptor[c].xMin, 
        fontdescriptor[c].xMax, 
        fontdescriptor[c].yMin, 
        fontdescriptor[c].yMax, 
        fontdescriptor[c].xAdvance, 
        fontdescriptor[c].yAdvance, 
        fontdescriptor[c].offset,
        fontdescriptor[c].unicode);
  
    c<0xff?fprintf(file,",\n"):fprintf(file,"\n");
  }
  fprintf(file,"};\n");
  fclose(file);
  FT_Done_Face    ( face );
  FT_Done_FreeType( library );
  return(0);
}
