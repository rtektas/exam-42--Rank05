#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

class bigint 
{
	public:
	std::string str;
	bigint(int n=0){std::ostringstream oss; oss << n; str= oss.str();}
	bigint(const std::string& s):str(s){}
	int to_int() const {return std::atoi(str.c_str());}
	bigint operator+(const bigint& o) const;
	bigint& operator+=(const bigint& o) {*this = *this + o; return *this;}
	bigint operator<<(int shift) const { return (shift <= 0 || str == "0") ? *this : bigint(str + std::string((std::size_t)shift,'0'));}
	bigint operator<<(const bigint& o) const {return *this << o.to_int();}
	bigint& operator<<=(int shift){*this = *this<<shift; return *this;}
	bigint operator<<=(const bigint& o) {*this = *this<< o; return *this;}
	bigint operator>>(int shift) const {std::size_t s= (shift < 0?0 : (std::size_t)shift); return s >=str.size()?bigint(0): bigint(str.substr(0, str.size() -s));}
	bigint operator>>(const bigint& o) const {return *this >> o.to_int();}
	bigint& operator>>=(int shift) {*this = *this >> shift; return *this;}
	bigint& operator>>=(const bigint& o) {*this = *this >> o; return *this;}
	bigint& operator++() {*this += bigint(1); return *this;}
	bigint operator++(int){bigint old = *this; ++*this; return old;}
	bool operator<(const bigint& o) const {return str.size() < o.str.size() || (str.size()== o.str.size() && str < o.str);}
	bool operator==(const bigint& o) const {return str== o.str;}
	bool operator!=(const bigint& o) const {return !(*this== o);}
	bool operator>(const bigint& o) const {return o < *this;}
	bool operator<=(const bigint& o) const {return !(*this > o);}
	bool operator>=(const bigint& o) const {return !(*this < o);}
};

std::ostream& operator<<(std::ostream& os, const bigint& big);

#endif