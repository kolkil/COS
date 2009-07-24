/*
 o---------------------------------------------------------------------o
 |
 | COS Vector
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C Object System framework.
 |
 | The C Object System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C Object System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: Vector.c,v 1.5 2009/07/24 12:36:27 ldeniau Exp $
 |
*/

#include <cos/Vector.h>

// NOTE-TODO: to move to IntVector.h once ready
#include <cos/IntVector.h>

#include <cos/gen/object.h>
#include <cos/gen/init.h>

makclass(Vector, ValueSequence);

// NOTE-TODO: move to IntVector.c once ready
makclass(IntVector, Vector);

// ------ Vector cluster front-end

defmethod(OBJ, galloc, mVector)
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Vector)
  retmethod(_1);
endmethod

#if 0
// ----- constructors from a vector

defmethod(OBJ, ginitWithIntPtr, mVector, (U32)n, (I32*)val)
  retmethod( ginitWith(_1, aIntVectorRef(n,val)) );
endmethod

defmethod(OBJ, ginitWithLngPtr, mVector, (U32)n, (I64*)val)
  retmethod( ginitWith(_1, aLngVectorRef(n,val)) );
endmethod

defmethod(OBJ, ginitWithFltPtr, mVector, (U32)n, (F64*)val)
  retmethod( ginitWith(_1, aFltVectorRef(n,val)) );
endmethod

defmethod(OBJ, ginitWithCpxPtr, mVector, (U32)n, (C64*)val)
  retmethod( ginitWith(_1, aCpxVectorRef(n,val)) );
endmethod

#endif
