#ifndef __X_include__
#define __X_include__


#define WINDOW_NAME_LENGTH 40
#define ICON_NAME_LENGTH 10

extern "C" {
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "X11/Xos.h"
#include "X11/Xatom.h"

}
#include <iostream>

using namespace std;

#ifdef Status
#undef Status
typedef int Status;
#endif

//#include "taco/taco.h"
//#include "taco/rmi/ArrayPtr.h"
#include "Coord2D.h"

/** \file XWindow.h
 * \brief X-window interface
 * This file provides a simple interface for using a X-window as output.
 */

enum Color {
        Blue1, Blue2, Blue3, Blue4,
        Red1, Red2, Red3, Red4,
        Purple1, Purple2, Purple3, Purple4,
        Green1, Green2, Green3, Green4,
        Cyan1, Cyan2, Cyan3, Cyan4,
        Magenta1, Magenta2, Magenta3, Magenta4,
        Yellow1, Yellow2, Yellow3, Yellow4,
        Orange1, Orange2, Orange3, Orange4,
        Gray, LtBlue, White, Black
};

/** \brief Interface class for X outputs.
 *
 * This Interface allows creation of a X-window, and simple output of text and rectangles in it.
 */
class XWindow {
private:
	Display* display;
	int screen_num;
	char* progname;
	Window win;
	unsigned int x,y;
	unsigned int width, height;
	unsigned int border_width;
	unsigned int display_width, display_height;
	char* window_name;
	char* icon_name;
	Pixmap icon_pixmap;
	XSizeHints* size_hints;
	XIconSize* size_list;
	XWMHints* wm_hints;
	XClassHint* class_hints;
	XTextProperty windowName,iconName;
	int count;
	XEvent report;
	XFontStruct *font_info;
	char* display_name;
	int window_size;

	double sc;
	double origin;

	GC gcBlue1;
	GC gcBlue2;
	GC gcBlue3;
	GC gcBlue4;
	GC gcRed1;
	GC gcRed2;
	GC gcRed3;
	GC gcRed4;
	GC gcPurple1;
	GC gcPurple2;
	GC gcPurple3;
	GC gcPurple4;
	GC gcGreen1;
	GC gcGreen4;
	GC gcGreen3;
	GC gcGreen2;
	GC gcCyan1;
	GC gcCyan2;
	GC gcCyan3;
	GC gcCyan4;
	GC gcMagenta1;
	GC gcMagenta2;
	GC gcMagenta3;
	GC gcMagenta4;
	GC gcYellow1;
	GC gcYellow2;
	GC gcYellow3;
	GC gcYellow4;
	GC gcOrange1;
	GC gcOrange2;
	GC gcOrange3;
	GC gcOrange4;
	GC gcBlack;
	GC gcWhite;
	GC gcLtBlue;
	GC gcGray;

	GC col;
 
public:
	/*
	* \brief Recommended Constructor
	*
	* This constructor creates a blackfilled window.
	* \param w is the horizontal pixelcount of the window
	* \param h is the vertical pixelcount of the window
	* \param w_name is the string displayed at upper left of the window
	*/
	XWindow(int w, int h, char w_name[]);
	XWindow(int xx,int yy,int w,int h,char w_name[],
		char i_name[],Pixmap i_p,int argc,char** argv);

	int getWidth();
	int getHeight();

	int scale(int v);
	void setScale(double s);
	void setCol(Color c);

	void construct(int xx,int yy,int w,int h, char w_name[],
		char i_name[],Pixmap i_p,int argc,char** argv);

	void putGC(GC* gc, int lineWidth, unsigned long color);
	void putGC(GC* gc, int lineWidth, char color_name[]);
	void putGC(GC* gc, int lineWidth, int gr,int re,int bl);
	void putTextGC(GC* gc, char* fontname);

	void nextEvent();
	void checkEvent();
	int keyPressed();
	int expose();
	void configureNotify();

	void line(Color color,int x1,int y1,int x2,int y2);
	void flushline(Color color,int x1,int y1,int x2,int y2);
	void point(Color color,int x,int y);
//	void pointList(Color color, ArrayPtr<Coord2D> p, int num);
	void fpoint(Color color,int x,int y);  
	void square(Color color,int x,int y,int len);
	void fsquare(Color color,int x,int y,int len);
	void drawpoints(Color color, Coord2D* points, int num);

	/* \brief draws a filled rectangle
	*
	* \param color is the border and fill color of the rectangle
	* \param x is the horizontal position of the upper left corner
	* \param y is the vertical position of the upper left corner
	* \param w is the width of the rectangle
	* \param h is the height of the rectangle
	*/
	void fillRectangle(Color color,int x,int y,int w,int h);
	/* \brief draws a string
	*
	* \param color is the border and fill color of the rectangle
	* \param x is the horizontal position where the text starts
	* \param y is the vertical position of the virtual bottom line
	* \param string is the message to write
	* \param len specifies the number of characters to write
	*/
	void write(Color c,int x,int y,const char* string,int len);
	/* \brief make changes visible
	*
	* Must be used to make a written string or drawed rectangle visible
	* in the X-window.
	*/
	void flush();

//  Bool always(Display *, XEvent *, char *);

  ~XWindow();
};

#endif

