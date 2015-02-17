#include "edit_box.h"
#define __stdcall __attribute__((stdcall))

extern unsigned int (* __stdcall edit_box_draw)();

dword_func *edit_box_draw =(dword_func*) &aEdit_box_draw;
dword_func *edit_box_key =(dword_func*) &aEdit_box_key;
dword_func *edit_box_mouse =(dword_func*) &aEdit_box_mouse;
dword_func *edit_box_set_text =(dword_func*) &aEdit_box_set_text;

//char lib_path[] = "/sys/lib/box_lib.obj";
char lib_path[] = "/sys/lib/box_lib.obj";
dword lib_path_addr = (dword)lib_path;
dword dummy = 0;

struct edit_box{
dword width, left, top, color, shift_color, focus_border_color, blur_border_color,
text_color, max, text, mouse_variable, flags, size, pos, offset, cl_curs_x, cl_curs_y, shift, shift_old;
};

void BOX_INIT()
{
  const IMP_ENTRY *imp;

  imp = __kolibri__cofflib_load("/sys/lib/box_lib.obj");
  if (imp == NULL)
    kol_exit();

  box_init = ( __stdcall  int(*)()) 
    __kolibri__cofflib_getproc (imp, "lib_init");
  if (box_init == NULL)
  {
  __menuet__debug_out("box_init() is NULL. Exiting.\n");
  kol_exit();
  }
 else
   __menuet__debug_out("\nbox_init() initialised properly.\n");

  /*dword_func *edit_box_draw =(dword_func*) &aEdit_box_draw;
    dword_func *edit_box_key =(dword_func*) &aEdit_box_key;
    dword_func *edit_box_mouse =(dword_func*) &aEdit_box_mouse;
  */
  
  edit_box_draw = ( __stdcall  unsigned int (*)(char*, char*)) 
		__kolibri__cofflib_getproc  (imp, "get");

  if (edit_box_draw == NULL)
  {
    __menuet__debug_out("http_get() is NULL. Exiting.\n");
    kol_exit();
  }

  __menuet__debug_out("box_lib_init init...\n");
/* HTTP_YAY(); */

__menuet__debug_out("ok...\n");






/* 
	kol_struct_import *k = kol_cofflib_load(lib_path);

	if (k == NULL)
	{
		sprintf(debuf, "cannot load library %S", lib_path);
		rtlDebugOutString(debuf);
		return;
	}

	edit_box_draw = (dword_func*)kol_cofflib_procload(k, "edit_box");
	edit_box_key = (dword_func*)kol_cofflib_procload(k,"edit_box_key");
	edit_box_mouse = (dword_func*)kol_cofflib_procload(k,"edit_box_mouse");
	kos_SetMaskForEvents(0x27);

	if (edit_box_draw == NULL || edit_box_key == NULL || edit_box_mouse == NULL)
		rtlDebugOutString("some of functions cannot be loaded!");
*/
}
