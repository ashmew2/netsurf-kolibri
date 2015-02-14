#include <menuet/os.h>
#include "kolibri_gui.h"
#include "box_lib.h"

const char header[] = "HelloWorld test";
const char string[] = "Hello, World!";

void draw_window(void)
{
  	char fname[256];
	dword mouse_dd;
	edit_box file_box = {0,9*8-5,WND_H - 16-32,0xffffff,0x6a9480,0,0x808080,0,255,(dword)&fname,(dword)&mouse_dd,0};

	__menuet__window_redraw(1);
	kol_wnd_define(0,0,1024,768, 0x13FFFFFF, 1, "Netsurf - KolibriOS");
	kol_btn_define(20,20,30,30, 0x1300000a, 0x00FF0000);
	kol_btn_define(60,20,30,30, 0x1300000b, 0x0000FF00);
	kol_btn_define(100,20,30,30, 0x1300000c, 0x000000FF);
	kol_btn_define(140,20,30,30, 0x1300000d, 0x00111111);
	kol_btn_define(180,20,30,30, 0x1300000e, 0x00FFFFFF);
	kol_btn_define(220,20,30,30, 0x1300000f, 0x00FF0000);	
        __menuet__window_redraw(2);

	file_box.flags &= ~2;
	file_box.left = 64;
	file_box.top = y - 1;
	file_box.width = 98;
	edit_box_draw((DWORD)&file_box);


	
}

void main(void)
{
  unsigned int btn_id;
  char btn[20];
  
	draw_window();
	
	for (;;)
	{
		switch (__menuet__wait_for_event())
		{
		case 1:
			draw_window();
			break;
		case 2:
			// key pressed, read it and ignore
			__menuet__getkey();
			break;
		case 3:

		  // btn_id = kol_btn_get();
		  btn_id = __menuet__get_button_id();		  
		  sprintf(btn, "Button ID %u\n", btn_id);
		  __menuet__debug_out(btn);
		  
		  if(btn_id == 10)
		    __menuet__debug_out("Previous button Pressed\n");
		  else 		  if(btn_id == 11)
		    __menuet__debug_out("Next button Pressed\n");
		  else 		  if(btn_id == 12)
		    __menuet__debug_out("Refresh button Pressed\n");
		  else 		  if(btn_id == 13)
		    __menuet__debug_out("Home button Pressed\n");
		  else 		  if(btn_id == 14)
		    __menuet__debug_out("Tab button Pressed\n");
		  else 		  if(btn_id == 15)
		    __menuet__debug_out("STOP button Pressed\n");
		  else
		    {
		    __menuet__debug_out("Unknown button Pressed\n");
		    }
			// button pressed; we have only one button, close
		}
	}
	return;
}
