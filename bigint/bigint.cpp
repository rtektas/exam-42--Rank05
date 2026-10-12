#include "bigint.hpp"
bigint bigint::operator+(const bigint& o) const
{
	std::string result;
	int left= str.size() -1, right = o.str.size() -1, carry = 0;
	while(left >= 0 || right >= 0 || carry)
	{
		int sum= carry + (left >= 0 ? str[left--] - '0' : 0) + (right >= 0 ? o.str[right--] - '0' : 0);
		result = char('0'+ sum%10) + result; carry = sum/10;
	}
	return bigint(result);
}

std::ostream& operator<<(std::ostream& os, const bigint& big)
{
	return os << big.str;
}

