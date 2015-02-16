#ifndef EDIT_BOX_H
#define EDIT_BOX_H

struct edit_box {
unsigned int width;
unsigned int left;
unsigned int top;
unsigned int color;
unsigned int shift_color;
unsigned int focus_border_color;
unsigned int blur_border_color ;
unsigned int text_color;
unsigned int max;
unsigned int text;
unsigned int mouse_variable;
unsigned int flags;
unsigned int size;
unsigned int pos;
unsigned int offset;
unsigned int cl_curs_x;
unsigned int cl_curs_y;
unsigned int shift;
unsigned int shift_old;
};

#endif
