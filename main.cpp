#include <iostream>
#include <string>
#include <sstream>
//#include <iomanip>

#include "Include/Nodes.h"

Nodes::Node *populate(Nodes::Node *head);

Nodes::Node *subpopulate(Nodes::Node *Parent, const std::string &ingredient);

void trail(Nodes::Node *node);

bool duplicate(const std::vector<std::string> &Inputs, const std::string &Input);

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
    std::cout << "Population of Tree: " << head->population << std::endl;
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
        //strip remove leading and trailing whitespace
        ingredient.erase(0, ingredient.find_first_not_of(' '));
        if (ingredient.empty()) {
            //check if the ingredient is empty
            break;
        } else if (head->ingredient == ingredient) {
            //check if the ingredient is the same as the parent ingredient
            std::cout << "Invaild Input, you're trying to make this item from itself" << std::endl;
        } else if (Nodes::head(head)->ingredient == ingredient) {
            //check if the ingredient is the same as the head ingredient
            std::cout << "Invalid input, you're trying to make this item!" << std::endl;
        } else if (duplicate(ingredients, ingredient)) {
            //check if the ingredient is a duplicate
            std::cout << "You have already entered this ingredient" << std::endl;
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

Nodes::Node *subpopulate(Nodes::Node *Parent, const std::string &Ingredient) {
    ///@brief This function will create a sub-node with the given ingredient
    ///@param Parent The parent node to create the sub-node from
    ///@param Ingredient The ingredient to create the sub-node from
    ///@return The sub-node created
    std::vector<std::pair<int, Nodes::Node *>> subnodes;
    if (!Nodes::head(Parent)->Search(Ingredient, subnodes).empty() && Parent->Parent) {
        //append whitespace to the ingredient to get the correct alignment
        int lenlongestStr = 0;
        int lenlongestParStr = 0;
        std::vector<std::pair<int, std::string>> Ingredients;
        std::vector<std::pair<int, std::string>> ParentIngredients;
        for (auto &itemname: subnodes) {
            //check if the length of the Node instances ingredient is longer than the current longest string length
            if (itemname.second->ingredient.length() > lenlongestStr) {
                // for Node
                lenlongestStr = itemname.second->ingredient.length();
            }
            if (itemname.second->Parent->ingredient.length() > lenlongestParStr) {
                // for Parent
                lenlongestParStr = itemname.second->Parent->ingredient.length();
            }
            //add the ingredient to the vector
            Ingredients.emplace_back(itemname.first,
                                     itemname.second->ingredient);
            ParentIngredients.emplace_back(itemname.first,
                                           itemname.second->Parent->ingredient);
        }
        //format output to align the ingredients
        lenlongestStr += 2;
        for (int i = 0; i < Ingredients.size(); i++) {
            //append WS for alignment
            while (Ingredients.at(i).second.length() < lenlongestStr) {
                Ingredients.at(i).second += " | ";
            }
            //append WS on Parent Ingredient
            while (ParentIngredients.at(i).second.length() < lenlongestParStr) {
                ParentIngredients.at(i).second += " | ";
            }
            Ingredients.at(i).second += ParentIngredients.at(i).second;
            //append generation number to the string
            std::stringstream ss;
            ss << subnodes.at(i).second->generation;
            std::string generation = ss.str();
            Ingredients.at(i).second += " | " + generation;
            //prepend the index to the Ingredients as a string
            std::stringstream ssbuffer;
            ssbuffer << Ingredients.at(i).first;
            Ingredients.at(i).second = ssbuffer.str() + ": " + Ingredients.at(i).second;
        }
        //output the ingredients
        std::cout << "Which of these Nodes do you want to clone:" << std::endl;
        //add column headers
        std::vector<std::string> headers = {"Index", //append WS (longest string length + 2)
                                            "Ingredient",
                                            "Parent Ingredient",
                                            "Generation"};
        //align the headers
        /*
         aligning Index
        while (headers[0].length() != headers[0].length() + lenlongestStr) {
            //append WS to "Index" to align with Ingredient
            headers[0] += " ";
        }
         */

        //output column headers
        for (auto &header: headers) {
            std::cout << header << " | ";
        }
        std::cout << std::endl;
        for (int i = 0; i < Ingredients.size(); i++) {
            std::cout << Ingredients[i].second << std::endl;
        }
        std::cout << std::endl;
        //prompt the user to select the ingredient they want to clone
        int selection_index = 0;
        //todo finish creating this function
        return new Nodes::Node(Ingredient, Parent);
    }
    //call search function on the head of the ingredient
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

bool duplicate(const std::vector<std::string> &Inputs, const std::string &Input) {
    ///@brief This function will check if the input is a duplicate
    ///@param Inputs The vector of inputs to check
    ///@param Input The input to check
    ///@return True if the input is a duplicate, false if it is not
    for (auto &input: Inputs) {
        if (input == Input) {
            return true;
        }
    }
    return false;
}