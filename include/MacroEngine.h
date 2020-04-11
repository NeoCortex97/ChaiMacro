#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <utility>
#include <vector>
#include <string>

struct hkey{
    char sym;
    unsigned int modifiers;
    std::string name;
    hkey(std::string name, char sym, unsigned int mod):name(std::move(name)), sym(sym), modifiers(mod){};
};

class MacroEngine{
public:
    MacroEngine();
    virtual ~MacroEngine();
    void setIgnoredMod(unsigned int Mod);
    void removeIgnoredMod(unsigned int Mod);
    void registerHotKey(char keysym, const std::string &name, int modifiers);
    bool registerCallback(std::string name, std::string functionName);
    bool nextEvent();
    void quit();

protected:
    Display* display;
    Window window;
    Bool owner_events;
    bool exit;
    int pointer_mode;
    int keyboard_mode;
    unsigned int ignoredMods;
    XEvent ev;
    std::vector<hkey> registeredKeys;
};

