#include "X/XWindow.h"
#include "icon_bitmap"

XWindow::XWindow(int w, int h, char w_name[])
	{
                construct(0,0,w,h, w_name, "OW",0,0,0);
		sc = 1.0;

		origin = w/2;
		cerr << "X::origin " << origin << endl;

                putGC(&gcBlue1,1,"blue1");
                putGC(&gcBlue2,1,"blue2");
                putGC(&gcBlue3,1,"blue3");
                putGC(&gcBlue4,1,"blue4");

                putGC(&gcRed1,1,"red1");
                putGC(&gcRed2,1,"red2");
                putGC(&gcRed3,1,"red3");
                putGC(&gcRed4,1,"red4");

                putGC(&gcPurple1,1,"purple1");
                putGC(&gcPurple2,1,"purple2");
                putGC(&gcPurple3,1,"purple3");
                putGC(&gcPurple4,1,"purple4");

                putGC(&gcGreen1,1,"green1");
                putGC(&gcGreen2,1,"green2");
                putGC(&gcGreen3,1,"green3");
                putGC(&gcGreen4,1,"green4");

                putGC(&gcCyan1,1,"cyan1");
                putGC(&gcCyan2,1,"cyan2");
                putGC(&gcCyan3,1,"cyan3");
                putGC(&gcCyan4,1,"cyan4");

                putGC(&gcMagenta1,1,"magenta1");
                putGC(&gcMagenta2,1,"magenta2");
                putGC(&gcMagenta3,1,"magenta3");
                putGC(&gcMagenta4,1,"magenta4");

                putGC(&gcYellow1,1,"yellow1");
                putGC(&gcYellow2,1,"yellow2");
                putGC(&gcYellow3,1,"yellow3");
                putGC(&gcYellow4,1,"yellow4");

                putGC(&gcOrange1,1,"orange1");
                putGC(&gcOrange2,1,"orange2");
                putGC(&gcOrange3,1,"orange3");
                putGC(&gcOrange4,1,"orange4");

                putGC(&gcLtBlue,1,"LtBlue");
                putGC(&gcBlack,1,"Black");
                putGC(&gcWhite,1,"White");

                putGC(&gcGray,1,"Gray");


                // putTextGC(&gcWhite,"-*-helvetica-bold-o-*-*-*-120-75-75-*-*-iso8859-1");
                putTextGC(&gcWhite,"-*-helvetica-bold-o-*-*-66-*-75-75-*-*-iso8859-1");
		//cerr << "X::setCol " << endl; cerr.flush();
		setCol(Black);

}

XWindow::XWindow(int xx,int yy,int w,int h,char w_name[],
	char i_name[],Pixmap i_p,int argc,char** argv) {
	construct(xx, yy, w, h, w_name, i_name, i_p,argc,argv);
}

int XWindow::getWidth() {
  return width;
}

int XWindow::getHeight() {
  return height;
}

int XWindow::scale(int v)
{
  // cerr <<  v << ":" << origin << ":" << sc <<  ":" << (int)(((double)(v+origin))/sc) << endl;
  return (int)(((double)(v+origin*sc))/sc);
}

void XWindow::setCol(Color c)
{
	switch (c) {
		case Blue1:
			col = gcBlue1;
			break;
		case Blue2:
			col = gcBlue2;
			break;
		case Blue3:
			col = gcBlue3;
			break;
		case Blue4:
			col = gcBlue4;
			break;

		case Red1:
			col = gcRed1;
			break;
		case Red2:
			col = gcRed2;
			break;
		case Red3:
			col = gcRed3;
			break;
		case Red4:
			col = gcRed4;
			break;

		case Purple1:
			col = gcPurple1;
			break;
		case Purple2:
			col = gcPurple2;
			break;
		case Purple3:
			col = gcPurple3;
			break;
		case Purple4:
			col = gcPurple4;
			break;
			case Green1:
			col = gcGreen1;
			break;
		case Green2:
			col = gcGreen2;
			break;
		case Green3:
			col = gcGreen3;
			break;
		case Green4:
			col = gcGreen4;
			break;

    case Cyan1:
			col = gcCyan1;
			break;
		case Cyan2:
			col = gcCyan2;
			break;
		case Cyan3:
			col = gcCyan3;
			break;
		case Cyan4:
			col = gcCyan4;
			break;

    case Magenta1:
			col = gcMagenta1;
			break;
		case Magenta2:
			col = gcMagenta2;
			break;
		case Magenta3:
			col = gcMagenta3;
			break;
		case Magenta4:
			col = gcMagenta4;
			break;

    case Yellow1:
			col = gcYellow1;
			break;
		case Yellow2:
			col = gcYellow2;
			break;
		case Yellow3:
			col = gcYellow3;
			break;
		case Yellow4:
			col = gcYellow4;
			break;

    case Orange1:
			col = gcOrange1;
			break;
		case Orange2:
			col = gcOrange2;
			break;
		case Orange3:
			col = gcOrange3;
			break;
		case Orange4:
			col = gcOrange4;
			break;

    case Black:
			col = gcBlack;
			break;
		case White:
			col = gcWhite;
			break;
		case Gray:
			col = gcGray;
			break;

    default:
			col = gcBlack;
			break;
	}
}

void XWindow::setScale(double s)
{
	sc = s;
}
  
void XWindow::construct(int xx,int yy,int w,int h,char w_name[],char i_name[],Pixmap i_p,int argc,char** argv)
{
	width = w;
	height = h;
	border_width = 4;
	window_name = w_name;
	icon_name = i_name;
	display_name = NULL;
	if(!(size_hints = XAllocSizeHints())) {
		cout << "Error: XAllocSizeHints" << endl;
		exit(0);	
	}
	if(!(wm_hints = XAllocWMHints())) {
		cout << "Error: XAllocWMHints" << endl;
		exit(0);	
	}
	if(!(class_hints = XAllocClassHint())) {
		cout << "Error: XAllocClassHint" << endl;
		exit(0);	
	}
	if((display = XOpenDisplay(display_name)) == NULL) {
		cout << "No connection to X-server" << endl;
		exit(-1);
	}
	if (argv)
		progname = argv[0];
	else
		progname = "kingkong";

	window_size = 0;
	screen_num     = DefaultScreen(display);
	width = w;
	height = h;
	x = xx;
	y = yy;
	win = XCreateSimpleWindow(display,
			RootWindow(display,screen_num),
			x,y,width,height,border_width,
			BlackPixel(display,screen_num),
			BlackPixel(display,screen_num));
	if(XGetIconSizes(display, RootWindow(display,screen_num),
			&size_list,&count)==0) {
		//cout << "No icon sizes" << endl;
	}
	icon_pixmap = XCreateBitmapFromData(display,win,
			icon_bitmap_bits,icon_bitmap_width,
			icon_bitmap_height);
	size_hints->flags      = PPosition | PSize | PMinSize; 
	size_hints->min_width  = 30;
	size_hints->min_height = 20;
	if(XStringListToTextProperty((char**) &window_name,1,
			&windowName)==0) {
		cout << "Allocation for windowname failed" << endl;
		exit(-1);
	}
	if(XStringListToTextProperty((char**) &icon_name, 1, 
			&iconName) == 0) {
		cout << "Allocation for iconname failed" << endl;
		exit(-1);
	}
	wm_hints->initial_state = NormalState;
	wm_hints->input         = True;
	wm_hints->icon_pixmap   = icon_pixmap;
	wm_hints->flags    = StateHint | IconPixmapHint | InputHint;
	
//	class_hints->res_name = progname;
	class_hints->res_class = "Basicwin";
	XSetWMProperties(display,win,&windowName,&iconName,
				argv, argc, size_hints, wm_hints, class_hints);
	XSetWMProperties(display,win,&windowName,&iconName,
			NULL, 1, size_hints, wm_hints, class_hints);


	XSelectInput(display,win,ExposureMask | KeyPressMask |
				ButtonPressMask | StructureNotifyMask);
	XMapWindow(display,win);
	//
	//
	while(1) {
		nextEvent();
		if (expose() == 0) {
			configureNotify();
			break;
		}
	}
}




void XWindow::putGC(GC* gc, int lineWidth, unsigned long color) {
	unsigned long valuemask = 0;
	XGCValues values;
	int dash_offset = 0;
	//static char dash_list[] = {12,24};
	char dash_list[] = {12,24};
	int list_length = 2;
	*gc = XCreateGC(display,win,valuemask,&values);
	XSetForeground(display,*gc,color);
	XSetLineAttributes(display,*gc,lineWidth,LineSolid,
					CapRound,JoinRound);
	XSetDashes(display,*gc,dash_offset,dash_list,list_length);
}

void XWindow::putGC(GC* gc, int lineWidth, char color_name[]) {
  XColor xc,ex_xc;
	XAllocNamedColor(display,DefaultColormap(display,
		screen_num),color_name,&xc,&ex_xc);
	putGC(gc,lineWidth,xc.pixel);
}

void XWindow::putGC(GC* gc, int lineWidth, int gr,int re,int bl) {
	XColor xc;
	xc.red = re;
	xc.green = gr;
	xc.blue = bl;
	xc.flags = DoRed||DoGreen||DoBlue;
	XAllocColor(display,DefaultColormap(display,
  	screen_num),&xc);
	putGC(gc,lineWidth,xc.pixel);
}

void XWindow::putTextGC(GC* gc, char* fontname) {
        XFontStruct* font_info;
	cerr <<  "X::putTextGC " << fontname << endl; cerr.flush();

        font_info = XLoadQueryFont(display,fontname);
        if (!font_info) {
		cerr <<  "X::putTextGC no fontinfo for " << fontname << endl; cerr.flush();
		return;
	}

        XSetFont(display,*gc,font_info->fid);
}

void XWindow::nextEvent() {
	XNextEvent(display,&report);
}
Bool always(Display *, XEvent *, char *){
  return true;
}
void XWindow::checkEvent() {
	if (XCheckIfEvent(display,&report,always,0))
		configureNotify();
}

int XWindow::keyPressed() {
	return (report.type == KeyPress);
}

int XWindow::expose() {
	int result;
	if(report.type == Expose) {
		result = report.xexpose.count;
	} else {
		result = -1;
	}
	return result;
}

void XWindow::configureNotify() {
	if (report.type == ConfigureNotify) {
		width = report.xconfigure.width;
		height = report.xconfigure.height;
	}
} 

  
void XWindow::line(Color color,int x1,int y1,int x2,int y2) {
	setCol(color);
	XDrawLine (display,win,col,scale(x1),
		scale(y1),scale(x2),scale(y2));
}

void XWindow::flushline(Color color,int x1,int y1,int x2,int y2) {
	setCol(color);
	XDrawLine (display,win,col,scale(x1),
		scale(y1),scale(x2),scale(y2));
	cerr << "flushline " <<(int) color << " " << scale(x1) << " " << scale(y1)
		<< " p2 " << scale(x2) << " " << scale(y2) << endl;
	cerr.flush();
	flush();
}

void XWindow::point(Color color,int x,int y) {
	setCol(color);
	XDrawPoint (display,win,col,scale(x),scale(y));
}

/*void XWindow::pointList(Color color, ArrayPtr<Coord2D> p, int num){
	Coord2D* points = new Coord2D[num];

	Future<int> done;
	int i;
	p.fetch(points, num, done);
	i = done;

	drawpoints(color, points, num);
	delete [] points;
}
  */
void XWindow::fpoint(Color color,int x,int y) {
//	point (color, x, y);
//	flush();
}

void XWindow::square(Color color,int x,int y,int len) {
	line(color, x, y+len, x+len, y+len);
	line(color, x, y, x+len, y);
	line(color, x, y+len,  x, y);
	line(color, x+len, y+len, x+len, y);
	// flush();
}

void XWindow::fsquare(Color color,int x,int y,int len) {
	square(color, x, y, len);
	flush();
}

void XWindow::drawpoints(Color color, Coord2D* points, int num)
{
	for (register int i =0; i<num; i++)
		point(color, (int)points[i].x, (int)points[i].y);
}

void XWindow::fillRectangle(Color color,int x,int y,int w,int h) {
	setCol(color);
	XFillRectangle(display,win,col,x,y,w,h);
//	flush();
}

void XWindow::write(Color c,int x,int y,const char* string,int len) {
  setCol(c);
  XDrawString(display,win,col, x,y,string,len);
}

void XWindow::flush() {
	XSync (this->display,1);
}



XWindow::~XWindow(){
	XCloseDisplay(display);
}
