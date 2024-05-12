
#ifndef MC_DRAW_EXPORT_H
#define MC_DRAW_EXPORT_H

#ifdef MC_DRAW_STATIC_DEFINE
#  define MC_DRAW_EXPORT
#  define MC_DRAW_NO_EXPORT
#else
#  ifndef MC_DRAW_EXPORT
#    ifdef mc_draw_EXPORTS
        /* We are building this library */
#      define MC_DRAW_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define MC_DRAW_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef MC_DRAW_NO_EXPORT
#    define MC_DRAW_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef MC_DRAW_DEPRECATED
#  define MC_DRAW_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef MC_DRAW_DEPRECATED_EXPORT
#  define MC_DRAW_DEPRECATED_EXPORT MC_DRAW_EXPORT MC_DRAW_DEPRECATED
#endif

#ifndef MC_DRAW_DEPRECATED_NO_EXPORT
#  define MC_DRAW_DEPRECATED_NO_EXPORT MC_DRAW_NO_EXPORT MC_DRAW_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MC_DRAW_NO_DEPRECATED
#    define MC_DRAW_NO_DEPRECATED
#  endif
#endif

#endif /* MC_DRAW_EXPORT_H */
