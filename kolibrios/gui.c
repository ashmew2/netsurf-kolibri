/* Function 65 on KolibriOS for drawing images in the window */
inline void f65(unsigned x, unsigned y, unsigned w, unsigned h, char *d) 
{
    asm("pusha");
    asm ("nop"::"D"(0), "c"(w*65536+h), "d"(x*65536+y), "b"(d));
    asm ("xor %eax, %eax");
    asm ("movl %eax, %ebp");
    asm ("pushl $32");
    asm ("popl %esi");
    asm ("int $0x40"::"a"(65));
    asm("popa");
}



struct gui_window {
  
  struct gui_window *next, *prev;
  struct browser_window *bw;
  
  int width, height;
  
};


struct gui_window * kolibri_create_window(struct browser_window *bw, 
					  struct gui_window *existing, 
					  gui_window_create_flags flags)
{
  
}

static void gui_quit(void)
{
  LOG(("Exiting to Kolibri OS.."));
  
  //Make sure stuff like download windows etc and other children are killed before exiting.
  kol_exit();
}

nserror nskol_schedule(int t, void (*callback)(void *p), void *p)
{
  //Need a way to do this under KolibriOS
  // Set a timed callback function, need some sort of a timer thread.

        /* _nsgtk_callback_t *cb; */

        /* /\* Kill any pending schedule of this kind. *\/ */
        /* schedule_remove(callback, p); */
	/* if (t < 0) { */
	/* 	return NSERROR_OK; */
	/* } */

	/* cb = malloc(sizeof(_nsgtk_callback_t)); */
        /* cb->callback = callback; */
        /* cb->context = p; */
        /* cb->callback_killed = false; */
        /* /\* Prepend is faster right now. *\/ */
        /* LOG(("queued a callback to %p(%p) for %d msecs time", callback, p, t)); */
        /* queued_callbacks = g_list_prepend(queued_callbacks, cb); */
        /* g_timeout_add(t, nsgtk_schedule_generic_callback, cb); */

	return NSERROR_OK;

}


static struct gui_browser_table nskol_browser_table = {
	.schedule = nskol_schedule,
	.quit = gui_quit,
	/* .launch_url = gui_launch_url, */
	/* .create_form_select_menu = gui_create_form_select_menu, */
	/* .cert_verify = gui_cert_verify, */
        /* .login = gui_401login_open, */
};


/*Will be the entry from our OS*/
int main()
{
  	struct netsurf_table nskol_table = {
		.browser = &nskol_browser_table,
		.window = nskol_window_table,
		.clipboard = nskol_clipboard_table,
		.download = nskol_download_table,
		.fetch = nskol_fetch_table,
		.llcache = filesystem_llcache_table,
		.search = nskol_search_table,
		.search_web = nskol_search_web_table,
	};

}
