// x, y - position; w, h - size; cs - color and style; c - caption; b - boder
void kolibri_window_define(unsigned x, unsigned y, unsigned w, unsigned h, unsigned cs, unsigned b, char *t)
{
asm volatile ("int $0x40"::"a"(0), "b"(x*65536+w), "c"(y*65536+h), "d"(cs), "D"(t), "S"(b) );
}

void kol_sleep(unsigned d)
{
asm volatile ("int $0x40"::"a"(5), "b"(d));
}

void kol_paint_string(unsigned x, unsigned y, char *ss, unsigned c)
{
  asm volatile ( "int $0x40"::"a"(4), "b"(x*65536+y), "c"(c), "d"(ss) );
}

void kol_paint_image(unsigned x, unsigned y, unsigned w, unsigned h, char *d)
{
asm volatile ("int $0x40"::"a"(7), "c"(w*65536+h), "d"(x*65536+y), "b"(d));
}


int main()
{//0xXYRRGGBB Y=3, 
  kolibri_window_define(100,100,500,500,0x13FFFFFF,1,"KFTP"); //Kolibri FTP
  
  kol_paint_string(105,105,"FTP ADDRESS : ",0x80FF0000);
  kol_sleep(10000);
  //wait_for_event()?
}
