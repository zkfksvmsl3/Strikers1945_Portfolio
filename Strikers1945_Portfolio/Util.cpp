#include "stdafx.h"

namespace UTIL
{
	/*float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}*/

	float GetDistance(const float startX, const float startY, const float endX, const float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	float GetAngle(const float x1, const float y1, const float x2, const float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;
		float angle = 0;
		float distance = sqrtf(x * x + y * y);

		if (distance == 0)
		{

		}
		else
		{
			angle = acosf(x / distance);
		}

		if (y2 > y1)
		{
			angle = PI2 - angle;
			if (angle >= PI2)
			{
				angle -= PI2;
			}
		}

		return angle;
	}
}