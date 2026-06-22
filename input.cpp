#include "input.h"

std::unordered_map<std::string, KeyAction> InputSystem::keyActionsList;
std::string InputSystem::stringBuffer;

void InputSystem::LoadInputContext()
{
    currentContext = Context::GAME;

    inputContextMap[Context::GAME] = {
        {},
        {
            { KEY_W, "MoveForward" },
            { KEY_S, "MoveBackward" },
            { KEY_A, "MoveLeft" },
            { KEY_D, "MoveRight" },
            { KEY_SPACE, "Dash" },
#ifdef DEBUG
            { KEY_GRAVE, "ToggleConsole" },
#endif
        }
    };

    inputContextMap[Context::UI] = {
        {},
        {
            { KEY_W, "NavigateUp" },
            { KEY_S, "NavigateDown" },
            { KEY_A, "NavigateLeft" },
            { KEY_D, "NavigateRight" },
            { KEY_ENTER, "Select" },
#ifdef DEBUG
            { KEY_GRAVE, "ToggleConsole" },
#endif
        }
    };

#ifdef DEBUG
    inputContextMap[Context::CONSOLE] = {
        {},
        {
            { KEY_GRAVE, "ToggleConsole" },
            { KEY_BACKSPACE, "PopInputChar" },
            { KEY_ENTER, "ExecuteCommand" },
        }
    };
#endif
}


Context InputSystem::GetCurrentContext()
{
    return currentContext;
}


void InputSystem::SetCurrentContext(Context newContext)
{
    previousContext = currentContext;
    currentContext = newContext;
}


void InputSystem::RestoreContext()
{
    currentContext = previousContext;
}


bool ShouldHandleText(Context context)
{
    return context == Context::CONSOLE;
}


void InputSystem::CheckInputs(float dt)
{
    const auto& actions = inputContextMap[currentContext].actions;
    
    int key = GetKeyPressed();

    while (key > 0)
    {
        auto actionIt = actions.find(static_cast<KeyboardKey>(key));
        if (actionIt != actions.end())
        {
            auto action = GetActionFromKey(actionIt->second);
            if (action != nullptr)
            {
                action->TriggerPressAction(dt);
            }
        }
        else if (ShouldHandleText(currentContext))
        {
            if (key >= 32 && key <= 125)
            {
                stringBuffer += (char)key;
            }
        }
        keyPressed.push_back(static_cast<KeyboardKey>(key));
        key = GetKeyPressed();
    }

    auto pressedKey = std::vector<KeyAction*>();

    for (auto keyIt = keyPressed.begin(); keyIt != keyPressed.end();) {
        auto actionIt = actions.find(*keyIt);
        auto action = actionIt != actions.end() ? GetActionFromKey(actionIt->second) : nullptr;

        if (IsKeyReleased (*keyIt) )
        {
            if (action != nullptr)
            {
                action->TriggerReleaseAction(dt);
            }
            
            keyIt = keyPressed.erase(keyIt);
        }
        else
        {
            if (action != nullptr)
            {
                action->TriggerHoldAction(dt);
                pressedKey.push_back(GetActionFromKey(actionIt->second));
            }
            ++keyIt;
        }
    }
}


KeyAction* InputSystem::CreateKeyAction(const std::string& actionKey)
{
    keyActionsList[actionKey] = KeyAction(actionKey);
    return &keyActionsList[actionKey];
}


KeyAction* InputSystem::GetActionFromKey(const std::string& actionKey)
{
    auto it = keyActionsList.find(actionKey);
    if (it != keyActionsList.end())
    {
        return &it->second;
    }
    return nullptr;
}


const std::string& InputSystem::GetStringBuffer()
{
    return stringBuffer;
}


void InputSystem::PopStringBuffer()
{
    if (!stringBuffer.empty())
    {
        stringBuffer.pop_back();
    }
}


void InputSystem::ClearStringBuffer()
{
    stringBuffer.clear();
}