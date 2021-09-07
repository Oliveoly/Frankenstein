#pragma once
#include "SpecialAttack.h"

class Special_None : public SpecialAttack
{
public:
	Special_None() { buff_duration = 0; };
	void action(float x, float y, int dir) { return; }
};
