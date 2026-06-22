#pragma once
#include <iostream>
#include <unordered_map>
#include "raylib.h"
#include "keyAction.h"
#include "define.h"


enum Context
{
	GAME = 1,
	UI = 2,
	CONSOLE = 3,
};


struct inputContext
{
	std::unordered_map<Context, inputContext> subContexts;
	std::unordered_map<KeyboardKey, std::string> actions;
};


class InputSystem
{
public:
	void LoadInputContext();
	void CheckInputs(float dt);
	Context GetCurrentContext();
	void SetCurrentContext(Context newContext);
	void RestoreContext();

	static KeyAction* CreateKeyAction(const std::string& actionKey);
	static KeyAction* GetActionFromKey(const std::string& actionKey);

	static const std::string& GetStringBuffer();
	static void PopStringBuffer();
	static void ClearStringBuffer();
private:
	Context currentContext;
	Context previousContext;

	std::unordered_map<Context, inputContext> inputContextMap; // Map with all context - actions key hierarchy
	static std::unordered_map<std::string, KeyAction> keyActionsList; // map with all acttion key - action
	static std::string stringBuffer;

	std::vector<KeyboardKey> keyPressed; // Vector with all current pressed key
};