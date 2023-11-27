#include "entities.h"

bool is_digit(const std::string & s)
{
	for (int ind = 0; ind < s.length(); ind++)
	{
		if (ind == 0) {
			if (!isdigit(s[ind])) {
				return false;
			}

		}
		else {
			if (!isdigit(s[ind]) && s[ind] != '.') {
				return false;
			}
		}
	}
	return true;
}

bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
