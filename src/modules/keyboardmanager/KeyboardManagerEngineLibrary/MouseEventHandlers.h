#pragma once

#include <Windows.h>
#include <optional>
#include <string>
#include <vector>
#include "State.h" // Replace with actual path to your State class header

namespace KeyboardManagerInput
{
    class InputInterface;
}

namespace MouseEventHandlers
{
    // Handles a single mouse button remap (clicks)
    intptr_t HandleSingleMouseRemapEvent(KeyboardManagerInput::InputInterface& ii, const MSLLHOOKSTRUCT* mouseData, WPARAM wParam, State& state) noexcept;

    // Handles mouse wheel remapping (vertical/horizontal scroll)
    intptr_t HandleMouseWheelRemapEvent(KeyboardManagerInput::InputInterface& ii, const MSLLHOOKSTRUCT* mouseData, WPARAM wParam, State& state) noexcept;

    // Handles app-specific mouse shortcut remapping
    intptr_t HandleAppSpecificMouseShortcutRemapEvent(KeyboardManagerInput::InputInterface& ii, const MSLLHOOKSTRUCT* mouseData, WPARAM wParam, State& state) noexcept;

    // Add more handlers as needed
}
