#pragma once
#include <iostream>
#include <unordered_map>
#include <functional>


class KeyAction
{
public:
	KeyAction() = default;
	KeyAction(std::string name);

	std::string GetActionName();

	template<typename Callable>
	void BindPressAction(Callable&& callback)
	{
		this->pressCallback = std::forward<Callable>(callback);
	}

	template<typename Callable>
	void BindReleaseAction(Callable&& callback)
	{
		this->releaseCallback = std::forward<Callable>(callback);
	}
	
	template<typename Callable>
	void BindHoldAction(Callable&& callback)
	{
		this->holdCallback = std::forward<Callable>(callback);
	}
	
	void TriggerPressAction(float deltaTime);
	void TriggerReleaseAction(float deltaTime);
	void TriggerHoldAction(float deltaTime);
private:
	std::string name;
	std::function<void(float)> pressCallback;
	std::function<void(float)> releaseCallback;
	std::function<void(float)> holdCallback;
};
