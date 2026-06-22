#include "keyAction.h"


KeyAction::KeyAction(std::string name)
{
	this->name = name;
}


std::string KeyAction::GetActionName()
{
	return name;
}


void KeyAction::TriggerPressAction(float deltaTime)
{
	if (pressCallback)
	{
		pressCallback(deltaTime);
	}
}


void KeyAction::TriggerReleaseAction(float deltaTime)
{
	if (releaseCallback)
	{
		releaseCallback(deltaTime);
	}
}

void KeyAction::TriggerHoldAction(float deltaTime)
{
	if (holdCallback)
	{
		holdCallback(deltaTime);
	}
}