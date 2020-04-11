#include "MacroEngine.h"
#include <iostream>

MacroEngine::MacroEngine() {
    display = XOpenDisplay(0);
    window    = DefaultRootWindow(display);
    owner_events    = True;
    pointer_mode = GrabModeAsync;
    keyboard_mode = GrabModeSync;
    registeredKeys.reserve(10);
    ignoredMods = 0;
    XSelectInput(display, window, KeyPressMask);
}
MacroEngine::~MacroEngine() {
    for(auto &x: registeredKeys){
        XUngrabKey(display, x.sym, x.modifiers, window);
    }
    XCloseDisplay(display);
}

void MacroEngine::registerHotKey(char keysym, const std::string &name, int modifiers) {
    int keycode = XKeysymToKeycode(display, XStringToKeysym(&keysym));

    registeredKeys.emplace_back(name, keysym, modifiers);
    XGrabKey(display, keycode, modifiers, window, owner_events, pointer_mode, keyboard_mode);

//    if(ignoredMods & Mod2Mask){
//        unsigned int newModifiers = modifiers + Mod2Mask;
//        registeredKeys.emplace_back(name, keysym, newModifiers);
//        XGrabKey(display, keycode, newModifiers, window, owner_events, pointer_mode, keyboard_mode);
//    }
//    if(ignoredMods & LockMask){
//        unsigned int newModifiers = modifiers + LockMask;
//        registeredKeys.emplace_back(name, keysym, newModifiers);
//        XGrabKey(display, keycode, newModifiers, window, owner_events, pointer_mode, keyboard_mode);
//    }
//    if(ignoredMods & Mod3Mask){
//        unsigned int newModifiers = modifiers + Mod3Mask;
//        registeredKeys.emplace_back(name, keysym, newModifiers);
//        XGrabKey(display, keycode, newModifiers, window, owner_events, pointer_mode, keyboard_mode);
//    }

//    if(MacroEngine::ignoreNumLock && MacroEngine::ignoreCapsLock){
//        unsigned int newModifiers = modifiers + Mod2Mask + LockMask;
//        registeredKeys.emplace_back(name, keysym, newModifiers);
//        XGrabKey(display, keycode, newModifiers, window, owner_events, pointer_mode, keyboard_mode);
//    }
//    if(MacroEngine::ignoreNumLock && MacroEngine::ignoreScrollLock){
//        unsigned int newModifiers = modifiers + Mod2Mask + Mod3Mask;
//        registeredKeys.emplace_back(name, keysym, newModifiers);
//        XGrabKey(display, keycode, newModifiers, window, owner_events, pointer_mode, keyboard_mode);
//    }
//    if(MacroEngine::ignoreScrollLock && MacroEngine::ignoreCapsLock){
//        unsigned int newModifiers = modifiers + Mod3Mask + LockMask;
//        registeredKeys.emplace_back(name, keysym, newModifiers);
//        XGrabKey(display, keycode, newModifiers, window, owner_events, pointer_mode, keyboard_mode);
//    }
}

bool MacroEngine::nextEvent() {
    XNextEvent(display, &ev);
    std::cout << ev.type << " ";
    switch(ev.type)
    {
        case KeyPress:
            std::cout << ev.xkey.keycode << ' ' << ev.xkey.state << '\n';
            for(auto &x : registeredKeys){
                if(ev.xkey.keycode == x.sym && ev.xkey.state == x.modifiers){
                    std::cout << "Hot key pressed!" << '\n';
                }
            }
            break;
        default:
            break;
    }
    return exit;
}

bool MacroEngine::registerCallback(std::string name, std::string functionName) {
    return false;
}

void MacroEngine::setIgnoredMod(unsigned int Mod) {
    ignoredMods |= Mod;
}

void MacroEngine::removeIgnoredMod(unsigned int Mod) {
    ignoredMods &= ~Mod;
}

void MacroEngine::quit() {
    exit = true;
}
