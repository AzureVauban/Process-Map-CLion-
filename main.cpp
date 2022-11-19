#include <iostream>
#include <string>
//#include <iomanip>

#include "Include/Nodes.h"

Nodes::Node *populate(Nodes::Node *head);

Nodes::Node *subpopulate(Nodes::Node *Parent, const std::string &ingredient);

void trail(Nodes::Node *node);

int main() {
    // prompt user to type in the name of the item they want to create
    std::string ingredient; // name of the head ingredient item the user wants to create
    while (true) {
        std::cout << "What is the name of the ingredient you want to create?" << std::endl;
        std::getline(std::cin, ingredient);
        // strip leading and trailing whitespace from ingredient
        ingredient.erase(0, ingredient.find_first_not_of(' '));
        std::cout << std::endl;
        if (ingredient.empty()) {
            std::cout << "Please enter a valid ingredient name" << std::endl;
        } else {
            break;
        }
    }
    auto head = populate(new Nodes::Node(ingredient));
    Nodes::temporary::AlignAllIngredients(head);
    std::cout << "Populate of Tree: " << head->population << std::endl;
    delete head;
    return 0;
}

Nodes::Node *populate(Nodes::Node *head) {
    ///@brief This function will populate the tree with nodes
    ///@param node The head to populate
    ///@return The head Node of the ingredient tree
    std::cout << "Type in the ingredients you need to create " << head->ingredient << ":" << std::endl;
    // output the ingredient trail
    if (head->Parent) {
        std::cout << "TRAIL: ";
        trail(head);
    }
    // prompt the user to type in their ingredients
    std::vector<std::string> ingredients;
    while (true) {
        std::string ingredient;
        std::getline(std::cin, ingredient);
        if (ingredient.empty()) {
            break;
        } else {
            ingredients.emplace_back(ingredient);
        }
    }
    // create sub-nodes with each ingredient
    for (auto &ingredient: ingredients) {
        subpopulate(head, ingredient);
        //update the population of the ingredient tree
        int p = 0;
        Nodes::head(head)->UpdatePopulation(Nodes::head(head)->CountNodes(p));
    }
    // recursively call this function on each sub-head
    for (auto &subnode: head->Children) {
        populate(subnode.second);
    }
    // return the head of the ingredient tree
    if (head->Parent) {
        Nodes::head(head);
    }
    return head;
}

Nodes::Node *subpopulate(Nodes::Node *Parent,const std::string &Ingredient) {
    return new Nodes::Node(Ingredient, Parent);
}

void trail(Nodes::Node *node) {
    ///@brief This function will output the ingredient trail
    ///@param node The node to output the ingredient trail of
    while (true) {
        if (node->Parent) {
            std::cout << node->ingredient << " -> ";
            node = node->Parent;
        } else {
            std::cout << node->ingredient << std::endl;
            break;
        }
    }
}