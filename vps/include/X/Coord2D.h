#ifndef Coord2D_h
#define Coord2D_h

typedef float prec; 

struct Coord2D {
	prec x, y;

	Coord2D(prec x=0.0, prec y=0.0) 
	{ 
		this->x = x;
		this->y = y;
	}

	Coord2D& operator*= (prec s)
	{
		x*=s; y *=s; return *this;
	}

	Coord2D operator* (prec s) const
	{
		return Coord2D (x*s, y*s); 
	}

	Coord2D& operator/= (prec s)
	{
		x/=s; y/=s; return *this;
	}

	Coord2D operator/ (prec s) const
	{
		return Coord2D (x/s, y/s); 
	}

	Coord2D& operator+= (prec s)
	{
		x+=s; y+=s; return *this;
	}

	Coord2D operator+ (prec s) const
	{
		return Coord2D (x+s, y+s); 
	}

	Coord2D& operator+=(const Coord2D& other)
	{
		x+=other.x; y +=other.y; return *this;
	}

	Coord2D operator+(const Coord2D& other) const
	{
		return Coord2D(x+other.x, y+other.y); 
	}

	bool isInQuadrant(prec xpos, prec ypos, prec l) const
	{ 
		return ((x >= xpos) && (x <= xpos+l) && (y >= ypos) && (y <= ypos+l)); 
	}
};

#include <math.h>
inline prec dist(const Coord2D& c0, const Coord2D& c1)
{
	register prec x = c1.x-c0.x;
	register prec y = c1.y-c0.y;

	return ::sqrt(x*x + y*y);
}

inline bool operator==(const Coord2D& c0, const Coord2D& c1)
{
	return ((c0.x==c1.x) && (c0.y==c1.y));
}

inline bool operator!=(const Coord2D& c0, const Coord2D& c1)
{
	return ((c0.x!=c1.x) || (c0.y!=c1.y));
}

inline bool operator<=(const Coord2D& c0, const Coord2D& c1)
{
	return ((c0.x <= c1.x) && (c0.y <= c1.y));
}

inline bool operator>=(const Coord2D& c0, const Coord2D& c1)
{
	return ((c0.x >= c1.x) && (c0.y >= c1.y));
}

inline bool operator < (const Coord2D& c0, const Coord2D& c1)
{
	Coord2D center(0,0);

	return dist(center, c0) < dist(center, c1);
}

inline bool operator>(const Coord2D& c0, const Coord2D& c1)
{
	return ((c0.x > c1.x) && (c0.y > c1.y));
}


/*
inline Coord2D identity_element(plus<Coord2D>)
{
        return Coord2D(0.0,0.0);
}
*/

#endif
