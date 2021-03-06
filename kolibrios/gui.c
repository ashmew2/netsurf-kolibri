/* Function 65 on KolibriOS for drawing images in the window */

#include "kolibri_gui.h"

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

enum download_status {
  DOWNLOAD_DOWNLOADING;
  DOWNLOAD_PAUSED;
  DOWNLOAD_FINISHED;
  DOWNLOAD_ERROR;
  DOWNLOAD_STOPPED;
};

struct gui_window {
  
  struct gui_window *next, *prev;
  struct browser_window *bw;

  gui_download_window main_dl;
  
  int width, height;
};

//There needs to be one gui_download_window and more rows (downloads) can be added/removed from it.
//gui_download_window represents one row of the download_window. There should be a parent window gui_window (type)

struct gui_download_window {
  struct gui_download_window *next, *prev;
  struct download_context *ctx;

  FILE *file_handle;
  
  char *name;
  unsigned long bytes_size;
  unsigned long bytes_downloaded;
  unsigned long bytes_remaining;

  double speed;

  //add an enum for DOWNLOAD_PAUSED, DOWNLOAD_RUNNING, DOWNLOAD_FINISHED, DOWNLOAD_STOPPED
  download_status status;
  
  //Need another entry for specifying row number in the download table (might change as downloads are added/removed).
  //or maybe just follow the order of the linked list.

  //progress can be calculated on the fly, not sure if it should have a separate field
  //can have more stuff like time_started (for elapsed time)
  
};


static void gui_window_destroy(struct gui_window *g)
{
  //Take this function to deallocate an allocated gui_window object
  //and modify the linked list appropriately
  //Like closing a tab so that one of the other tabs becomes the first tab etc

  //For now, just exit
  kol_exit();
}


struct gui_window * gui_window_create(struct browser_window *bw, 
					  struct gui_window *existing, 
					  gui_window_create_flags flags)
{
  //Flags are for saying if we want a new window, a tabbed window or nothing.
  //Use them later, create window for now

  struct gui_window new_window = (struct gui_window *)calloc(struct gui_window);
  new_window->next = NULL;	
  new_window->prev = NULL;	

  new_window->bw = bw;  
  bw->window = new_window; //or the old one itself??

  new_window->width = 1024;
  new_window->height = 768;
  
  new_window->main_dl = NULL;
  
  kol_wnd_define(0,0,gui_window->width , gui_window->height,  0x13FFFFFF, 1, "Netsurf - KolibriOS");

  /* GW_CREATE_NONE  /\* New window *\/ */
  /* GW_CREATE_CLONE /\* Clone existing window *\/ */
  /* GW_CREATE_TAB   /\* In same window as existing *\/ */

  //add maintainer code for adding to linked list of windows

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

static void gui_window_redraw_window(struct gui_window *g)
{
  //Call function 12 subfunction 1 here
}

static void gui_window_update_rect(struct gui_window *g, const struct rect *rect)
{
  //This seems like Function 15, Subfunction 9, but Not sure about this yet.

}

static bool gui_window_get_scroll(struct gui_window *g, int *sx, int *sy)
{

//Function 37, Subfunction 7
//Set sx and sy to whatever F37 wants
}

static void gui_window_set_scroll(struct gui_window *g, int sx, int sy)
{
  //Not sure what to use right now. Function 37,subfn7 gets the scroll data from somewhere
  //figure out what that "somewhere" is and dump this scroll data there

}

static void gui_window_get_dimensions(struct gui_window *g, int *width, int *height,
			       bool scaled)
{
  //Report the parameters of gui_window *g->width and height here?
  //sysfuncs doesn't seem to contain a function to accomplish this.
  //Is a function needed if we already know?
  //Maybe the width height changes if user resizes the window. 
  //Need to consider this.

	LOG(("width: %i", *width));
	LOG(("height: %i", *height));
}

static void gui_window_update_extent(struct gui_window *g)
{
  //Not sure what to do with this right now. (If anything at all is required)
}

static void nskol_window_reformat(struct gui_window *gw)
{
	GtkAllocation alloc;

	if (gw != NULL) {
		//browser_window_reformat must be called with the new width and height of the newly sized window

	  browser_window_reformat(gw->bw, false, gw->width, gw->height);
	  //We must always update the gui_window gw to reflect the current size of the window
	}
}

/**
 * Core asks front end for clipboard contents.
 *
 * \param  buffer  UTF-8 text, allocated by front end, ownership yeilded to core
 * \param  length  Byte length of UTF-8 text in buffer
 */
static void gui_get_clipboard(char **buffer, size_t *length)
{
  
  
  int clipboard_address = kol_get_clipboard_data();
  char *clipboard_data = NULL;

  if(clipboard_address!=1 && clipboard_address!=-1)
    clipboard_data = (char *)clipboard_address;

  *length = strlen(clipboard_data);
  
  memcpy(*buffer, clipboard_data, *length);
  //The data is copied into buffer and length is set to buffer length.

}


/**
 * Core tells front end to put given text in clipboard
 *
 * \param  buffer    UTF-8 text, owned by core
 * \param  length    Byte length of UTF-8 text in buffer
 * \param  styles    Array of styles given to text runs, owned by core, or NULL
 * \param  n_styles  Number of text run styles in array
 */
static void gui_set_clipboard(const char *buffer, size_t length,
		nsclipboard_styles styles[], int n_styles)
{
  //ignoring styles for now. Will add them later (fancy stuff :P)
  kol_set_clipboard_data(buffer, (int)length);
}

static struct gui_download_window * gui_download_window_create(struct download_context *ctx, struct gui_window *parent)
{
  gui_download_window *new_dl_window = (gui_download_window *)malloc(sizeof(gui_download_window));
  FILE *write_handle;

  write_handle = fopen(download_context_get_filename(ctx), "wb"); //This is probably correct (wb mode)

  new_dl_window->next = NULL;
  new_dl_window->next = NULL;
  new_dl_window->bytes_size = download_context_get_total_length(ctx);
  new_dl_window->bytes_downloaded = 0;
  new_dl_window->bytes_remaining = new_dl_window->bytes_size;

  new_dl_window->file_handle = ;

  new_dl_window->status = DOWNLOAD_DOWNLOADING;

  if(parent->main_dl == NULL)
    parent->main_dl = new_dl_window;
  else
    {
      gui_download_window *temp = parent->main_dl;
      
      while(temp->next!=NULL)
	temp = temp->next;
      
      temp->next = new_dl;
      new_dl->prev = temp;      
    }
  //Need a function such as add_download_to_gui which creates a row in the download window which is pointed to by the
  // parent gui window.

}

nserror gui_download_window_data(struct gui_download_window *dw, const char *data, unsigned int size)
{
  //Seems like this function is responsible for getting the downloaded data. 
  //Not sure if the file pointer should be written here. But apparently, it should be.
  //Download_window should have a low lying file handle to which bytes are being written.

  if(dw->file_handle)
    fwrite(data, sizeof(char), size, dw->file_handle); //Handle fwrite errors? They shouldn't occur normally.
  else
    {
      //error condition! The file stream we opened earlier didn't work out well, ABORT.
      dw->status = DOWNLOAD_ERROR; //Invalidates the file transfer. use the download status enum here.
      //This status can be used to "Clear" the downloaded files etc 
    }
}

void gui_download_window_error(struct gui_download_window *dw, const char *error_msg)
{
  dw->status = DOWNLOAD_ERROR;
}

void gui_download_window_done(struct gui_download_window *dw)
{
  dw->status = DOWNLOAD_FINISHED;
  fclose(dw->file_handle);
  
  LOG(("Download finished...it's size/downloaded/remaining : %lu/%lu/%lu", dw->bytes_size, dw->bytes_downloaded, dw->bytes_remaining));

  dw->bytes_remaining = 0;
  dw->speed = 0.00;

  //Consider some auto clear mode where finished downloads are automatically cleared, Shouldn't be too hard.
}

const char *fetch_filetype(const char *unix_path)
{
  //can add more mime types (check out gtk/fetch.c gtk_fetch_filetype_init function)
  int len = strlen(unix_path);

  for(; len > 0; len--)
    if(unix_path[len]=='.')
      break;

  if(!strcmp(unix_path + len, ".png"))
    return "image/png";
  else   if(!strcmp(unix_path + len, ".css"))
    return "text/css";
  else   if(!strcmp(unix_path + len, ".html"))
    return "text/html";
  else   if(!strcmp(unix_path + len, ".txt"))
    return "text/plain";
  else
    return "text/plain";

}


static struct gui_fetch_table fetch_table = {
	.filetype = fetch_filetype,
	
};

static struct gui_download_table download_table = {
	.create = gui_download_window_create,
	.data = gui_download_window_data,
	.error = gui_download_window_error,
	.done = gui_download_window_done,
};

static struct gui_clipboard_table clipboard_table = {
	.get = gui_get_clipboard,
	.set = gui_set_clipboard,
};

static struct gui_window_table window_table = {
	.create = gui_window_create,
	.destroy = gui_window_destroy,
	.redraw = gui_window_redraw_window,
	.update = gui_window_update_rect,
	.get_scroll = gui_window_get_scroll,
	.set_scroll = gui_window_set_scroll,
	.get_dimensions = gui_window_get_dimensions,
	.update_extent = gui_window_update_extent,
	.reformat = nskol_window_reformat,

	//add more optional entries here from desktop/gui.h or gtk/window.c
}

static struct gui_browser_table nskol_browser_table = {
	.schedule = nskol_schedule,
	.quit = gui_quit,
	//add this optional stuff later once mandatory features work
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
