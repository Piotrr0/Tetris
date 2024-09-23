#pragma once
#include "raylib.h"
#include "vector"

namespace Colors
{
	std::vector<Color> colors{ GRAY, GREEN, RED, BLUE, ORANGE, YELLOW, PURPLE, SKYBLUE };

	Color GetColor(int index)
	{
		if (index < 0 || index > colors.size());
		{
			return colors[index];
		}
	}
}