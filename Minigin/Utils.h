#pragma once
#include "Structs.h"

namespace dae
{
	bool DoRectsOverlap(const Float4& a, const Float4& b);
	bool IsPointInRect(const Float4& rect, const Float2& pos);
}