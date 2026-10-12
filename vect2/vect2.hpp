#ifndef VECT2_HPP
#define VECT2_HPP
#include <iostream>

class vect2
{
	public:
	int x;
	int y;
	vect2(int a=0, int b=0): x(a), y(b) {}

	int& operator[](int i)
	{
		if(i==0)
		{
			return x;
		}
		return y;
	}

		const int& operator[](int i) const
	{
		if(i==0)
		{
			return x;
		}
		return y;
	}

	vect2 operator+(const vect2& o) const {return vect2(x+o.x, y+o.y);}
	vect2 operator-(const vect2& o) const {return vect2(x-o.x, y-o.y);}
	vect2 operator-() const {return vect2(-x,-y);}
	vect2 operator*(int s) const {return vect2(x*s,y*s);}

	vect2& operator+=(const vect2& o) {x+=o.x; y+=o.y; return *this;}
	vect2& operator-=(const vect2& o) {x-=o.x; y-=o.y; return *this;}
	vect2& operator*=(int s) {x*=s; y*=s; return *this;}

	vect2& operator++() {++x;++y; return *this;}
	vect2 operator++(int) {vect2 t= *this; ++(*this); return t;}
	vect2& operator--() {--x;--y; return *this;}
	vect2 operator--(int) {vect2 t= *this; --(*this); return t;}

	bool operator==(const vect2& o) const {return x==o.x && y==o.y;}
	bool operator!=(const vect2& o) const {return !(*this==o);}

};

vect2 operator*(int s, const vect2& o);
std::ostream& operator<<(std::ostream& os, const vect2& o);

#endif