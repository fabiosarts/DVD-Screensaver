#ifndef utils_h__
#define utils_h__

#include <cstdlib>

namespace utils
{
	int getRandomRange(const int& start, const int& end)
	{
		return rand() % (end - start) + start;
	}
}
#endif // utils_h__