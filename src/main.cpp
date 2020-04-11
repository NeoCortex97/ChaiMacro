#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>
#include "MacroEngine.h"

using std::cout;

int main() {
    MacroEngine me = MacroEngine();

    chaiscript::ChaiScript chai;
    chai.add(chaiscript::const_var(ShiftMask), "ShiftMod");
    chai.add(chaiscript::const_var(LockMask), "ShiftLockMod");
    chai.add(chaiscript::const_var(ControlMask), "CtrlMod");
    chai.add(chaiscript::const_var(Mod1Mask), "AltMod");
    chai.add(chaiscript::const_var(Mod2Mask), "NumLockMod");
    chai.add(chaiscript::const_var(Mod3Mask), "ScrollLockMod");
    chai.add(chaiscript::const_var(Mod4Mask), "WindowsMod");
    chai.add(chaiscript::const_var(Mod5Mask), "AltGrMod");

    //chai.add(chaiscript::fun(std::bind(&MacroEngine::setIgnoredMod, me, std::placeholders::_1)), "setIgnoredMods");
    chai.add(chaiscript::fun(&MacroEngine::setIgnoredMod, &me), "setIgnoredMod");
    chai.add(chaiscript::fun(&MacroEngine::removeIgnoredMod, &me), "removeIgnoredMod");
    chai.add(chaiscript::fun(&MacroEngine::registerHotKey, &me), "registerHotKey");
    chai.add(chaiscript::fun(&MacroEngine::registerCallback, &me), "registerCallback");

    chai.eval_file("/home/stefan/CLionProjects/chaitest/test.chai");
    int i = 0;
    while(true)
    {
        std::cout << "test" << i << '\n';
        bool shouldQuit = me.nextEvent();
        if(shouldQuit)
            break;
        ++i;
    }
    return 0;
}