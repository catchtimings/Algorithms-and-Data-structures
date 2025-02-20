#pragma once
#include <iostream>

struct stats {
	size_t comparison_count{ 0 };
	size_t copy_count { 0 };

	stats& operator+=(const stats& s);
	stats& operator=(const stats& s);
	stats& operator/=(const size_t& value);
};
stats operator+(stats left, const stats& right);
stats operator/(stats left, const size_t& value);

std::ostream& operator<<(std::ostream& os, const stats& s);
