Please distribute this file with the GFC runtime environment.

==========================
GFC - Games Fundamental Classes
==========================

Games Fundamental Classes - GFC - is a library created to facilitate building simple 2D games in C++
by Jarek Francik - purposely developed as an aid to the Games Fundamentals and Game Science modules
taught at Kingston University, London.

/* The GFC source code is available from:
http://gamesfundamentals.com/?page_id=560 */

This library is distributed under the terms of the zlib license.

GFC has been build on top of SDL (Simple DirectMedia Layer), a cross platform graphics library written by Sam Lantinga, 
with extensions by various authors. SDL is available under the terms of GNU LGPL license at:
http://www.libsdl.org/


Copyright (C) 2009-2014 Jarek Francik, Kingston University London

Version 1.0 20/03/2009
Version 1.1 11/04/2009
Version 1.2 25/04/2009
Version 1.4 11/02/2011
Version 1.5 6/11/2011
Version 1.6 24/03/2012
Version 1.7 7/04/2012
Version 1.71 14/03/2013
Version 2.00 5/12/2013
Version 2.01 12/12/2013
Version 2.02  8/01/2014
Version 2.03 17/01/2014
Version 2.04 23/01/2014
Version 2.05 26/01/2014
Version 2.06 17/02/2014
Version 2.10 10/03/2014


Planned Future Extensions
===================

1. Bezier curves
2. Textured polygons
3. Dynamic link to Box2D

Changes in Versions 2.10
===================

This is a major update - may require source code modifications for existing projects

1. CSprite::OnUpdate: change of deltaTime parameter type from Uint32 to Sint32
    to allow Updates going back in time.
    WARNING: May break compatibility!
2. Distributed with zlib license
3. SDL upgraded to version 1.2.15
4. New interface for loading images into sprites: LoadImage, SetImage and AddImage
5. New interface for sprite animation (SetAnimation)
6. Thick lines and rounded rectangles added in CGraphics

Changes in Versions 2.06
===================

This version has nener been released

1. Bug fix: problems with transparency with some graphics data formats,
    and particularly with rotating sprites - fixed
2. Bug fix - rotating sprites were sometimes shaky - fixed
3. Path list support for file loading (graphics and sound) 
4. Cached file input for graphics and sound
5. Simplified interface for playing sounds

Changes in Versions 2.05
===================

1. Bug fix: Normalize function for a zero length vector
2. Bug fix: text output following font size change


Changes in Versions 2.03 - 2.04
========================

1. Bug fix - text position after font size changed 

Changes in Versions 2.03 - 2.04
========================

1. CVector Reflect function
2. New framework for game levels
3. More precised timing for Update
4. Bug fixes

Changes in Versions 2.00/2.01/2.02
==========================

Total rebuild, change of most of class interfaces, in particular:

1. Change of sprite coordinates and size from integer to float vector
2. Support for vector oriented calculations
2. Change of the Y coordination direction (Y is pointing up)
3. New functions in CSprite (Get/SetMass, Accelerate, ApplyForce)

THE LIBRARY IS NOW NOT COMPATIBLE WITH 1.* VERSIONS!


Changes in Version 1.71
======================

1. Fixed problem with sdl_gfc.dll: it was dependent on debug version of MVC runtime - thanks to Andy Walker for spotting this!

2. Fixed problem with CSprite::SetDirection(double, double): parameters (0, 0) will not alter the direction

Changes in Version 1.7
======================

1. Sound API

2. Using a bitmap file that does not exist does not crash the application any more - instead, default pattern is shown

3. Speed and velocity related functions in CSprite class reorganised to become more physically consistent:
   - new GetSpeed and SetSpeed functions to replace GetVelocity and SetVelocity
   - new SetVelocity function to replace SetMotion
   - GetVelocity(), SetVelocity(double) and SetMotion(double, double) are now obsolete but kept for compatibility reasons

4. Redesigned text output functionality in CGraphics object:
   - mix-typed text output may be pushed using << operator
   - most standard C++ stream manipulators may be used, for example: endl, hex, setprecision
   - special manipulators added like left, right, center, bottom, font, color and many other to facilitate text output
   Example of the new-style text output:

      *g << top << left << "Score: " << score << right << "Time: " << timetext(GetTime()) << flush;
      if (IsGameOver())
      {
        *g << vcenter << center << font(32) << color(CColor::Red()) << "GAME OVER";
        *g << endl << font(20) << "SCORE: " << score << flush;
      }
   


Changes in Version 1.6
======================

1. Bug fixed
Description: SetVelocity did not impose any motion unless preceded by SetDirection
Cause: m_vX and m_vY both initialised to 0 in CSprite::CSprite
Solution: m_vY initialised to 1
Result: Fixed

2. <sstream> included as standard
#include <sstream> added to gfc.h

3. GFC_VERSION added in gfc.h
Added: #define GFC_VERSION	160

4. Some problems with displaying semi-transparent images are fixed
This fix involved upgrade of SDL_gfx library from ver. 2.0.18 to ver. 2.0.23


Changes in Version 1.5
======================

1. Removing items from collections added:
- CSprite::MarkAsRemoved
- CSprite::IsMarkedAsRemoved
- marked_as_removed

2. CSpriteVector added


Changes in Version 1.41
=======================

- IsKeyDown function added
- CSprite::SetX & CSprite::SetY functions added


Changes in Version 1.4
======================

1. Copy Constructor added to CGraphics class

2. New CGraphics derived classes: 
- CGraphicsFragment - graphics file based on a rectangular fragment of another graphics object or file
- CGraphicsTile - as above, but the fragment based on a regular subdivision of the larger Graphics object
into a set of tiles - determined by number of columns and rows.

3. CSpriteBitmap class functionality moved to CSprite. CSpriteBitmap is kept for backward compatibility
but it has empty implementation

4. Repertoire of constructors for CSprite class enhanced - to reflect new functionality taken over from 
CSpriteBitmap

5. New family of functions added to CSprite to operate on named properties:
- GetProperty
- SetProperty

6. New image and animation functions added to CSprite:
- ClearImage
- SetImageFromFile
- SetImage
- SetAnimation

7. New pixel-wise collision detection added:
- HitTestPixel

8. New low level graphics functions in CSprite class:
- GetGraphics
- GetRotoGraphics
- PrepareGraphics

9. CSprite::OnDraw is no longer a pure virtual function, and CSprite is no longer an abstract class

