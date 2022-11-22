#include <iostream>
#include "Include/Nodes.h"

Nodes::Node *populate(Nodes::Node *Parent) {
    /// @brief prompts the user to create the ingredient tree
    /// @param Parent node that all subnodes will be created with
    /// @return the head of the ingredient tree
    if (Parent->Parent) {
        return Nodes::head(Parent);
    }
    return Parent;
}
Nodes::Node *subpopulate(Nodes::Node *Parent, std::string &Ingredient) {
    /// @brief creates a subnode to link to the parent during the tree creation
    /// @param Parent Parent node to line returned subnode to
    /// @param Ingredient Name of the ingredient the subnode will store
    /// @return a subnode of the Parent
    return new Nodes::Node(Ingredient, Parent);
}
int main() {
    std::cout << "CLion is cool!" << std::endl;

    return 0;
}