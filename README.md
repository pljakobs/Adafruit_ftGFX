Adafruit_ftGFX_Library
======================

Enhanced multifont version of the Adafruit_GFX library, created by Peter Jakobs, based on Paul Kourany's 
work on the Adafruit_mfGFX_Library.

This library supports any compatible Adafruit_GFX display driver.  
With this programme, a simple Linux / Cygwin compilable programme called "makefont" is provided. 
Using this, ftGFX compatible fonts can be created on any system that supports FreeType.

Please note that, despite there are free and open font licenses, you may not necessarily be allowed to 
embed / include / distribute all fonts, even in the ftGFX format. Always consider the license under which
a font is provided and, if in doubt, ask the developer / publisher.

BE AWARE that though font data does not take up RAM, they do however take up PROGMEM space so having
too many fonts may prove problematic.

the default font is Open_Sans_Regular_12pt, so this will definitively break your layout if you try to 
just straight away replace the original Adafruit_GFX library. But that's already true to the fact that
the font baseline is different, so there's no point.

This is the core graphics library for all our displays, providing a common set of graphics
primitives (points, lines, circles, etc.).  It needs to be paired with a hardware-specific
library for each display device we carry (to handle the lower-level functions).

Adafruit_GFX
------------

Adafruit invests time and resources providing this open source code, please support Adafruit
and open-source hardware by purchasing products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
BSD license, check license.txt for more information.
All text above must be included in any redistribution.

To download, click the DOWNLOAD ZIP button, uncompress and rename the uncompressed folder
Adafruit_mfGFX. Confirm that the Adafruit_mfGFX folder contains Adafruit_mfGFX.cpp and
Adafruit_GFX.h.

Place the Adafruit_mfGFX library folder your <arduinosketchfolder>/Libraries/ folder. You may need
to create the Libraries subfolder if its your first library. Restart the IDE.






