#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>

std::string helloWorld(const std::string &t_name) {
    return "Hello " + t_name + "!";
}

int main() {
    chaiscript::ChaiScript chai;
    chai.add(chaiscript::fun(&helloWorld), "helloWorld");

    chai.eval_file("/home/stefan/ClionProjects/chaitest/test.chai");
}