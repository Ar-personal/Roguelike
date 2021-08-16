#pragma once

#include "System.h"


class Event;


class PlayerControlSystem : public System
{
public:
	void Init();

	void Update();

private:
	std::bitset<8> mButtons;

	void InputListener(Event& event);
};