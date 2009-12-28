/*
 o---------------------------------------------------------------------o
 |
 | COS Functor composition
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
 | $Id: Functor_cmp.c,v 1.5 2009/12/28 00:18:54 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

makclass(ComposeFun, Functor);

useclass(ComposeFun);

// ----- ctors

static inline struct ComposeFun*
ComposeFun_alloc(U32 size)
{
  OBJ _cmp = gallocWithSize(ComposeFun, size * sizeof(OBJ));
  struct ComposeFun *cmp = STATIC_CAST(struct ComposeFun*, _cmp);

  cmp->size = size;
  
  return cmp;
}

defmethod(OBJ, galloc, pmComposeFun)
  retmethod(_1); // lazy alloc
endmethod

defmethod(OBJ, ginitWith, pmComposeFun, ComposeFun) // clone
  retmethod( ginitWith((OBJ)ComposeFun_alloc(self2->size),_2) );
endmethod

defmethod(OBJ, ginitWith, pmComposeFun, Array) // clone
  retmethod( ginitWith((OBJ)ComposeFun_alloc(self2->size),_2) );
endmethod

defmethod(OBJ, ginitWith, ComposeFun, ComposeFun) // copy
  PRT(_1);
  test_assert(self->size == self2->size, "incompatible composition size");
  
  OBJ *src = self2->fun;
  OBJ *fun = self->fun;
  OBJ *end = self->fun + self->size;

  while (fun < end)
    *fun++ = gretain(*src++);

  UNPRT(_1);
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, ComposeFun, Array) // from array
  PRT(_1);
  test_assert(self->size == self2->size, "incompatible composition size");

  OBJ *obj   = self2->object;
  I32  obj_s = self2->stride;
  OBJ *fun   = self->fun + self->size;
  OBJ *end   = self->fun;

  while (fun-- > end) { // reverse references
    *fun = gretain(*obj);
    obj += obj_s;
  }

  UNPRT(_1);
  retmethod(_1);
endmethod

// ----- dtor

defmethod(OBJ, gdeinit, ComposeFun)
  for (U32 i = 0; i < self->size; i++)
    grelease(self->fun[i]);

  retmethod(_1);
endmethod

// ----- arity

defmethod(I32, garity, ComposeFun)
  retmethod( garity(self->fun[0]) );
endmethod

// ----- compose

defmethod(OBJ, gcompose, Functor)
  retmethod(_1);
endmethod

defmethod(OBJ, gcompose, Array)
  retmethod(gautoDelete(gnewWith(ComposeFun,_1)));
endmethod

// ----- eval

defmethod(OBJ, gevalEnv, ComposeFun, Container)
  OBJ *fun = self->fun;
  OBJ *end = self->fun + self->size;
  struct Array *env = atArray(0);
  OBJ *arg = env->object;
  
  forward_message(*fun++, _2);

  while (fun != end) {
    *arg = RETVAL;
    RETVAL = gevalEnv(*fun++, (OBJ)env);
  }

endmethod

