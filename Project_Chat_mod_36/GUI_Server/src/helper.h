#pragma once

#include "chat.h"


ActionType ToActionType(std::string_view sw);
std::string ToString(ActionType act);

std::string HandleMessage(Chat& chat, const std::string& msg);

std::string PrepareMessage(const Chat& chat, const std::pair<ActionType, std::string>& input);

void HandleResponse(Chat& chat, ActionType type, std::string& msg);