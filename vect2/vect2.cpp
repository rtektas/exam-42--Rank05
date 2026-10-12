#include "vect2.hpp"
vect2 operator*(int s, const vect2& o)
{
	return vect2(o.x*s, o.y*s);
}

std::ostream& operator<<(std::ostream& os, const vect2& o)
{
	os << "{" << o.x << ", " << o.y << "}";
	return os;
}