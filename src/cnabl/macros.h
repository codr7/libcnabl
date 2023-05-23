#ifndef MACROS_H
#define MACROS_H

#define cl_align(base, size) ({						\
      __auto_type _base = base;						\
      __auto_type _size = cl_min((size), _Alignof(max_align_t));	\
      (_base) + _size - ((ptrdiff_t)(_base)) % _size;			\
    })									\

#define cl_baseof(p, t, m) ({			\
      uint8_t *_p = (uint8_t *)p;		\
      _p ? ((t *)(_p - offsetof(t, m))) : NULL;	\
    })

#define _cl_id(x, y)				\
  x##y

#define cl_id(x, y)				\
  _cl_id(x, y)

#define cl_max(x, y) ({				\
      __auto_type _x = x;			\
      __auto_type _y = y;			\
      _x > _y ? _x : _y;			\
    })						\

#define cl_min(x, y) ({				\
      __auto_type _x = x;			\
      __auto_type _y = y;			\
      _x < _y ? _x : _y;			\
    })						\

#define cl_unique(x)				\
  cl_id(x, __COUNTER__)

#endif
