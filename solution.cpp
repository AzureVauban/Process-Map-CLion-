#include <iostream>
#include "Include/Nodes.h"

Nodes::Node *populate(Nodes::Node *Parent) {
    if (Parent->Parent) {
        return Nodes::head(Parent);
    }
    return Parent;
}

int main() {
    std::cout << "CLion is cool!" << std::endl;

    return 0;
}