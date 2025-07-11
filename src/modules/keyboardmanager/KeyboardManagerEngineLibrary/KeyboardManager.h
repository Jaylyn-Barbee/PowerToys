#pragma once
#include <common/hooks/LowlevelKeyboardEvent.h>
#include <common/utils/EventWaiter.h>
#include <keyboardmanager/common/Input.h>
#include "State.h"

namespace KBMEditor
{
    class KeyboardManagerState;
}

class KeyboardManager
{
public:
    static const inline DWORD StartHookMessageID = WM_APP + 1;

    // Constructor
    KeyboardManager();

    ~KeyboardManager()
    {
        if (editorIsRunningEvent)
        {
            CloseHandle(editorIsRunningEvent);
        }
    }

    void StartLowlevelKeyboardHook();
    void StopLowlevelKeyboardHook();

    void StartLowlevelMouseHook();
    void StopLowlevelMouseHook();

    bool HasRegisteredRemappings() const;

    static KBMEditor::KeyboardManagerState* keyboardManagerState;

private:
    // Returns whether there are any remappings available without waiting for settings to load
    bool HasRegisteredRemappingsUnchecked() const;

    // Contains the non localized module name
    std::wstring moduleName = KeyboardManagerConstants::ModuleName;

    // Low level hook handles
    static HHOOK hookHandle;
    static HHOOK mouseHookHandle;

    // Required for Unhook in old versions of Windows
    static HHOOK hookHandleCopy;
    static HHOOK mouseHookHandleCopy;

    // Static pointer to the current KeyboardManager object required for accessing the HandleKeyboardHookEvent function in the hook procedure
    static KeyboardManager* keyboardManagerObjectPtr;

    // Variable which stores all the state information to be shared between the UI and back-end
    State state;

    // Object of class which implements InputInterface. Required for calling library functions while enabling testing
    KeyboardManagerInput::Input inputHandler;

    // Auto reset event for waiting for settings changes. The event is signaled when settings are changed
    EventWaiter settingsEventWaiter;

    std::atomic_bool loadingSettings = false;

    HANDLE editorIsRunningEvent = nullptr;

    // Hook procedure definition
    static LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);

    static LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);

    void LoadSettings();

    // Function called by the hook procedure to handle the events. This is the starting point function for remapping
    intptr_t HandleKeyboardHookEvent(LowlevelKeyboardEvent* data) noexcept;

    intptr_t HandleMouseHookEvent(const MSLLHOOKSTRUCT* data, WPARAM wParam) noexcept;
};
