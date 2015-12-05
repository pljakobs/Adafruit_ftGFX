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
  FILE*         textfile;

  char*         filename;
  char*         text;
  char          pixbuff[256];

  int           c,glyph_index;
  int           target_height;
  int           n, num_chars;
  int           i,j,p,q,offset;
  int           size;
  int           dpi=114;

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
  
  //create output filename and open file
  char* filename_o=malloc(snprintf(NULL,0,"%s_%s_%dpt.c", face->family_name, face->style_name, size)+1);
  sprintf(filename_o,"%s_%s_%dpt.h", face->family_name, face->style_name, size);
  fprintf(stderr,"will output to file %s\n", filename_o);
  file=fopen(filename_o, "w+");

  //create documentation filename and open file
  char* filename_d=malloc(snprintf(NULL,0,"%s_%s_%dpt.c", face->family_name, face->style_name, size)+1);
  sprintf(filename_d,"%s_%s_%dpt.txt", face->family_name, face->style_name, size);
  fprintf(stderr,"will output docu to file %s\n", filename_d);
  textfile=fopen(filename_d, "w+");
  
  int ff=face->face_flags;
  ff & FT_FACE_FLAG_SCALABLE ? fprintf(textfile,"is scalable\n"):fprintf(stderr,"is fixed size\n");
  ff & FT_FACE_FLAG_FIXED_WIDTH ? fprintf(textfile,"is fixed width\n"):fprintf(stderr,"is porportional width\n");
  ff & FT_FACE_FLAG_SFNT ? fprintf(textfile,"is SFNT formatted\n"):fprintf(stderr,"is not SFNT formatted\n");
  ff & FT_FACE_FLAG_HORIZONTAL ? fprintf(textfile,"contains horizontal glyph metrics\n"):fprintf(stderr,"n");
  ff & FT_FACE_FLAG_TRICKY ? fprintf(textfile,"this is a tricky font\n"):fprintf(stderr,"no tricks here\n");

  int FSType_flags=FT_Get_FSType_Flags(face);
  fprintf(textfile,"Checking embedding flags %d \n",FSType_flags);
  if (FSType_flags == FT_FSTYPE_INSTALLABLE_EMBEDDING) {
    fprintf(textfile,"  can be embedded without condition\n");
  }else if(FSType_flags & FT_FSTYPE_RESTRICTED_LICENSE_EMBEDDING){
    fprintf(textfile,"  can not be freely modified, embedded or exchanged without obtaining a license\n");
  }else if(FSType_flags & FT_FSTYPE_PREVIEW_AND_PRINT_EMBEDDING){
    fprintf(textfile,"  can be embedded for preview and print\n");
  }else if(FSType_flags & FT_FSTYPE_EDITABLE_EMBEDDING){
    fprintf(textfile,"  can be embedded for editing, preview and printing\n");
  }else if(FSType_flags & FT_FSTYPE_NO_SUBSETTING){
    fprintf(textfile,"  can not be subsetted prior to embedding\n");
  }else if(FSType_flags & FT_FSTYPE_BITMAP_EMBEDDING_ONLY){
    fprintf(textfile,"  can only be embedded by way of contained bitmaps\n");
  }

  charmap=face->charmap;
  fprintf(textfile,"current charmap: %d, %d\n",charmap->platform_id, charmap->encoding_id);
  int cm = face->num_charmaps;
  fprintf(textfile,"found %d charmaps\n", cm);
  
  FT_Set_Char_Size(face, size*64,0,dpi,0);
  fprintf(file,"const unsigned char %s_%s_%dptBitmaps[] PROGMEM = {\n", face->family_name, face->style_name, size);
 
  offset=0;
  uint8_t ft_minchar=0x20;
  uint8_t ft_threshhold=127;
  for(c=ft_minchar;c<=255;c++){
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
      fontdescriptor[c].xAdvance = slot->advance.x/64;
      fontdescriptor[c].yAdvance = size;
      //fontdescriptor[c].yAdvance = slot->advance.y/64;
      //fontdescriptor[c].xAdvance = face->glyph->linearHoriAdvance/64;
      //fontdescriptor[c].yAdvance = face->glyph->linearVertAdvance/64;
      fontdescriptor[c].unicode  = FF_encoding[c];

      int doc_yMax  = bbox.yMax;

      fprintf(textfile,"/***********************************************\n");
      fprintf(textfile,"*\n");
      fprintf(textfile,"* Next char: 0x%02x, %d, %c \n",c,c,c);
      fprintf(textfile,"* Encoding : 0x%02x, %d, %c \n",FF_encoding[c],FF_encoding[c],FF_encoding[c]);
      fprintf(textfile,"*\n");
      fprintf(textfile,"************************************************\n");

      fprintf(textfile,"* fontdescriptor[0x%02x].xMin     = %d;\n", c, fontdescriptor[c].xMin); 
      fprintf(textfile,"* fontdescriptor[0x%02x].xMax     = %d;\n", c, fontdescriptor[c].xMax); 
      fprintf(textfile,"* fontdescriptor[0x%02x].yMin     = %d;\n", c, fontdescriptor[c].yMin); 
      fprintf(textfile,"* fontdescriptor[0x%02x].yMax     = %d;\n", c, fontdescriptor[c].yMax); 

      fprintf(textfile,"* fontdescriptor[0x%02x].offset   = 0x%04x;\n", c, fontdescriptor[c].offset); 
      fprintf(textfile,"* fontdescriptor[0x%02x].xAdvance = %d;\n", c, fontdescriptor[c].xAdvance); 
      fprintf(textfile,"* fontdescriptor[0x%02x].yadvance = %d;\n", c, fontdescriptor[c].yAdvance); 
      fprintf(textfile,"* fontdescriptor[0x%02x].unicode  = U-%04x;\n", c, fontdescriptor[c].unicode); 

      fprintf(textfile,"************************************************\n*\n");

      fprintf(file," // Offset: 0x%04x width: %02d (%02d-%02d) height: %02d (%02d-%02d) xAdvance: %02d yAdvance: %02d \n", offset, bbox.xMax-bbox.xMin, bbox.xMax, bbox.xMin, bbox.yMax-bbox.yMin,bbox.yMax,bbox.yMin, slot->advance.x/64, slot->advance.y/64);
      for(i=0;i<=b_test->rows-1;i++){
        fprintf(textfile,"* % 2d\t",doc_yMax);
        q=7;
        uint8_t c_byte=0;
        for(j=0;j<=b_test->width-1;j++){
          if(b_test->buffer[i*b_test->width+j]>ft_threshhold) c_byte|=1<<q;
          (b_test->buffer[i*b_test->width+j]>ft_threshhold)?fprintf(textfile,"@"):(doc_yMax==0)?fprintf(textfile,"-"):fprintf(textfile,".");
          if(q--==0){
            fprintf(file,"0x%02x, ",c_byte);
            offset++;
            c_byte=0;
            q=7;
            fprintf(textfile,"|");
          }
        }
        if ((b_test->width % 8)!=0){
          fprintf(file,"0x%02x, ",c_byte);
          offset++;
        }
        fprintf(file,"\n");
        fprintf(textfile,"\n");
        doc_yMax--;
        //(c<255 || i<=b_test->rows)?fprintf(file,", "):fprintf(file," ");
      }
      c==92?fprintf(file,"// 0x%02x <Backslash>\n",c):fprintf(file,"// 0x%02x, U-%04x, %c\n",c,FF_encoding[c],c);
      
      // fprintf(file,"/* \n");
      // fprintf(file,"*/ \n");
      
    }else{
      // empty fontdescriptor signifies non-printing char
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

  fprintf(textfile,"/***********************************************\n\n\n");
  fprintf(file,"};\n\n");
  fprintf(file,"const FontDescriptor %s_%s_%dptDescriptors2[] PROGMEM = {\n", face->family_name, face->style_name, size);
  for(c=ft_minchar;c<=0xff;c++){
    //fprintf(file, "\t// U-%04x, %c\n", c, c);
    fprintf(file, "\t{ (int8_t)0x%02x,\t(int8_t)0x%02x,\t(int8_t)0x%02x,\t(int8_t)0x%02x,\t(int8_t)0x%02x,\t(int8_t)0x%02x,\t(uint16_t)0x%04x,\t(uint16_t)0x%04x}", 
        fontdescriptor[c].xMin, 
        fontdescriptor[c].xMax, 
        fontdescriptor[c].yMin, 
        fontdescriptor[c].yMax, 
        fontdescriptor[c].xAdvance, 
        fontdescriptor[c].yAdvance, 
        fontdescriptor[c].offset,
        fontdescriptor[c].unicode,
        c,c);
  
    c<0xff?fprintf(file,",\t// U-%04x, %c\n",c,c==92?0x20:c):fprintf(file,"\t// U-%04x, %c\n",c,c);
  }
  fprintf(file,"};\n");
  fclose(file);
  FT_Done_Face    ( face );
  FT_Done_FreeType( library );
  return(0);
}
