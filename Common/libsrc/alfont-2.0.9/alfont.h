/* AllegroFont - a wrapper for FreeType 2 */
/* to render TTF and other font formats with Allegro */

            
/* FreeType 2 is copyright (c) 1996-2000 */
/* David Turner, Robert Wilhelm, and Werner Lemberg */
/* AllegroFont is copyright (c) 2001, 2002 Javier Gonz lez */

/* See FTL.txt (FreeType Project License) for license */


#ifndef ALFONT_H
#define ALFONT_H


#include <allegro.h>

#include "alfontdll.h"


#ifdef __cplusplus
extern "C" {
#endif


/* common define */

#define ALFONT_MAJOR_VERSION        1
#define ALFONT_MINOR_VERSION        9
#define ALFONT_SUB_VERSION          1
#define ALFONT_VERSION_STR          "1.9.1"
#define ALFONT_DATE_STR             "24/11/2002"
#define ALFONT_DATE                 20021124    /* yyyymmdd */

/* error codes */

#define ALFONT_OK                   0
#define ALFONT_ERROR                -1

/* font adjustment flags (AGS compatibility hacks) */

// Force reupdate the font even if the face size matches the request
#define ALFONT_FLG_FORCE_RESIZE       0x01
// Make ascender equal to formal font height
#define ALFONT_FLG_ASCENDER_EQ_HEIGHT 0x02
// When resizing a font, select the first result even if the actual
// pixel height is different from the requested size;
// otherwise will search for the point size which results in pixel
// height closest to the requested size.
#define ALFONT_FLG_SELECT_NOMINAL_SZ  0x04
// Precalculate maximal glyph control box, that is maximal graphical
// extent of any glyph in the font (which may exceed font's height).
// Note that this requires FreeType to load each glyph one by one.
#define ALFONT_FLG_PRECALC_MAX_CBOX   0x08


/* includes */


/* structs */
typedef struct ALFONT_FONT ALFONT_FONT;

/* API */

ALFONT_DLL_DECLSPEC char* alfont_get_name(ALFONT_FONT *f);

ALFONT_DLL_DECLSPEC int alfont_init(void);
ALFONT_DLL_DECLSPEC void alfont_exit(void);

ALFONT_DLL_DECLSPEC ALFONT_FONT *alfont_load_font(const char *filepathname);
ALFONT_DLL_DECLSPEC ALFONT_FONT *alfont_load_font_from_mem(const char *data, int data_len);
ALFONT_DLL_DECLSPEC void alfont_destroy_font(ALFONT_FONT *f);

ALFONT_DLL_DECLSPEC int alfont_set_font_size(ALFONT_FONT *f, int h);
ALFONT_DLL_DECLSPEC int alfont_set_font_size_ex(ALFONT_FONT *f, int h, int flags);
ALFONT_DLL_DECLSPEC int alfont_get_font_height(ALFONT_FONT *f);
/* Returns the real font graphical height */
ALFONT_DLL_DECLSPEC int alfont_get_font_real_height(ALFONT_FONT *f);
/* Returns the real font graphical extent (top, bottom) */
ALFONT_DLL_DECLSPEC void alfont_get_font_real_vextent(ALFONT_FONT *f, int *top, int *bottom);

ALFONT_DLL_DECLSPEC int alfont_text_mode(int mode);

ALFONT_DLL_DECLSPEC void alfont_textout_aa(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color);
ALFONT_DLL_DECLSPEC void alfont_textout(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color);
ALFONT_DLL_DECLSPEC void alfont_textout_aa_ex(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color, int bg);
ALFONT_DLL_DECLSPEC void alfont_textout_ex(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color, int bg);

ALFONT_DLL_DECLSPEC void alfont_textout_centre_aa(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color);
ALFONT_DLL_DECLSPEC void alfont_textout_centre(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color);
ALFONT_DLL_DECLSPEC void alfont_textout_centre_aa_ex(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color, int bg);
ALFONT_DLL_DECLSPEC void alfont_textout_centre_ex(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color, int bg);

ALFONT_DLL_DECLSPEC void alfont_textout_right_aa(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color);
ALFONT_DLL_DECLSPEC void alfont_textout_right(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color);
ALFONT_DLL_DECLSPEC void alfont_textout_right_aa_ex(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color, int bg);
ALFONT_DLL_DECLSPEC void alfont_textout_right_ex(BITMAP *bmp, ALFONT_FONT *f, const char *s, int x, int y, int color, int bg);

ALFONT_DLL_DECLSPEC void alfont_textprintf(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, const char *format, ...);
ALFONT_DLL_DECLSPEC void alfont_textprintf_aa(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, const char *format, ...);
ALFONT_DLL_DECLSPEC void alfont_textprintf_ex(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, int bg, const char *format, ...);
ALFONT_DLL_DECLSPEC void alfont_textprintf_aa_ex(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, int bg, const char *format, ...);

ALFONT_DLL_DECLSPEC void alfont_textprintf_centre(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, const char *format, ...);
ALFONT_DLL_DECLSPEC void alfont_textprintf_centre_aa(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, const char *format, ...);
ALFONT_DLL_DECLSPEC void alfont_textprintf_centre_ex(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, int bg, const char *format, ...);
ALFONT_DLL_DECLSPEC void alfont_textprintf_centre_aa_ex(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, int bg, const char *format, ...);

ALFONT_DLL_DECLSPEC void alfont_textprintf_right(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, const char *format, ...);
ALFONT_DLL_DECLSPEC void alfont_textprintf_right_aa(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, const char *format, ...);
ALFONT_DLL_DECLSPEC void alfont_textprintf_right_ex(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, int bg, const char *format, ...);
ALFONT_DLL_DECLSPEC void alfont_textprintf_right_aa_ex(BITMAP *bmp, ALFONT_FONT *f, int x, int y, int color, int bg, const char *format, ...);

ALFONT_DLL_DECLSPEC int alfont_text_height(ALFONT_FONT *f);
ALFONT_DLL_DECLSPEC int alfont_text_length(ALFONT_FONT *f, const char *str);

ALFONT_DLL_DECLSPEC int alfont_is_fixed_font(ALFONT_FONT *f);
ALFONT_DLL_DECLSPEC int alfont_is_scalable_font(ALFONT_FONT *f);

ALFONT_DLL_DECLSPEC const int *alfont_get_available_fixed_sizes(ALFONT_FONT *f);
ALFONT_DLL_DECLSPEC int alfont_get_nof_available_fixed_sizes(ALFONT_FONT *f);

ALFONT_DLL_DECLSPEC int alfont_get_char_extra_spacing(ALFONT_FONT *f);
ALFONT_DLL_DECLSPEC void alfont_set_char_extra_spacing(ALFONT_FONT *f, int spacing);

#ifdef __cplusplus
}
#endif

#endif
