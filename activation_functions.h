
#ifndef BRAIN_ACTIVATION_FUNCTIONS
#define BRAIN_ACTIVATION_FUNCTIONS

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

namespace brain
{
	float Sigmoid(float t_value)
	{
		return 1.0f / (1.0f + std::powf(float(M_E), -t_value));
	}
}

#endif
