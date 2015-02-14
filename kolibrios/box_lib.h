dword_func *edit_box_draw =(dword_func*) &aEdit_box_draw;
dword_func *edit_box_key =(dword_func*) &aEdit_box_key;
dword_func *edit_box_mouse =(dword_func*) &aEdit_box_mouse;



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


http_get = ( __stdcall  unsigned int (*)(char*, char*)) 
		__kolibri__cofflib_getproc  (imp, "get");
if (http_get == NULL)
  {
    __menuet__debug_out("http_get() is NULL. Exiting.\n");
    kol_exit();
  }
http_free = ( __stdcall  void (*)(unsigned int)) 
		__kolibri__cofflib_getproc  (imp, "free");
if (http_free == NULL)
  {
    __menuet__debug_out("http_free() is NULL. Exiting.\n");
    kol_exit();
  }	
http_receive = ( __stdcall  int (*)(unsigned int))
		__kolibri__cofflib_getproc  (imp, "receive");

if (http_receive == NULL)
  {
    __menuet__debug_out("http_receive() is NULL. Exiting.\n");
    kol_exit();
  }

http_find_header_field = ( __stdcall  char *(*)(struct http_msg*, char *)) 
		__kolibri__cofflib_getproc  (imp, "find_header_field");
if (http_find_header_field == NULL)
  {
    __menuet__debug_out("http_find_header_field() is NULL. Exiting.\n");
    kol_exit();
  }

http_unescape_url = ( __stdcall  char *(*)(char *))
  __kolibri__cofflib_getproc  (imp, "unescape");

if(http_unescape_url == NULL)
  {
    __menuet__debug_out("http_unescape_url() is NULL. Exiting.\n");
    kol_exit();
  }

 http_post = ( __stdcall  char *(*)(char *, char *, char *, int))
  __kolibri__cofflib_getproc  (imp, "post");

 if(http_post == NULL)
   {
     __menuet__debug_out("http_post() is NULL. Exiting.\n");
     kol_exit();
  }


 http_send = ( __stdcall  int (*)(struct http_msg *, char *, unsigned int))
  __kolibri__cofflib_getproc  (imp, "send");

 if(http_send == NULL)
   {
     __menuet__debug_out("http_send() is NULL. Exiting.\n");
     kol_exit();
  }

 
 http_disconnect = ( __stdcall  void (*)(struct http_msg *))
  __kolibri__cofflib_getproc  (imp, "disconnect");

 if(http_disconnect == NULL)
   {
     __menuet__debug_out("http_disconnect() is NULL. Exiting.\n");
     kol_exit();
  }

 

__menuet__debug_out("HTTP init...\n");
HTTP_YAY();

__menuet__debug_out("ok...\n");






 
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
}
