#include <iostream>
#include <string>

#include "NodeUtility.h"

NodeUtility::Node *populate(NodeUtility::Node *node);

int main() {
    //prompt user to type in the name of the item they want to create
    std::string ingredient; //name of the head ingredient item the user wants to create
    while (true) {
        std::cout << "What is the name of the ingredient you want to create: ";
        std::getline(std::cin, ingredient);
        //strip leading and trailing whitespace from ingredient
        ingredient.erase(0, ingredient.find_first_not_of(' '));
        std::cout << std::endl;
        if (ingredient.empty()) {
            std::cout << "Please enter a valid ingredient name" << std::endl;
        } else {
            break;
        }
    }
    auto head = populate(new NodeUtility::Node(ingredient));
    delete head;
    return 0;
}

NodeUtility::Node *populate(NodeUtility::Node *node) {
    ///@brief This function will populate the tree with nodes
    ///@param node The node to populate
    ///@return The head Node of the ingredient tree
    //prompt the user to type in their ingredients
    std::cout << "Type in the ingredients you need to create " << node->ingredient << ":"<< std::endl;
    //output the ingredient trail
    //create sub-nodes with each ingredient
    //recursively call this function on each sub-node
    //return the head of the ingredient tree
    if (node->Parent != nullptr) {
        NodeUtility::head(node);
    }
    return head(node);
}