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
        struct headerstuple {
            std::string first; // index of the subnode
            std::string second; // ingredient of the subnode
            std::string third; // Parent Ingredient of the subnode
            std::string fourth; // generation
            headerstuple(int first, std::string &second, std::string &third, const int fourth) {
                std::stringstream ss;
                // convert the index to a string
                ss << first;
                this->first = ss.str();
                this->second = second;
                this->third = third;
                //clear ss
                ss.str(std::string());
                //convert generation into a string
                ss << fourth;
                this->fourth = ss.str();
            }
        };
        std::vector<headerstuple> headers = {};
        // create a vector of headers
        headers.emplace_back(headerstuple(-1, subnodes[0].second->ingredient,
                                          subnodes[0].second->Parent->ingredient,
                                          -1));
        //overwrite the headers with the correct values
        headers[0].first = "Index";
        headers[0].second = "Ingredient";
        headers[0].third = "Parent Ingredient";
        headers[0].fourth = "Generation";
        //create a vector of vectors of strings
        for (auto &subnode: subnodes) {
            headers.emplace_back(headerstuple(subnode.first,  //index of subnode in search vector
                                              subnode.second->ingredient, //ingredient of subnode
                                              subnode.second->Parent->ingredient, //parent ingredient of subnode
                                              subnode.second->generation)); //generation of subnode
        }
        //align the headers
        int Longest[4] = {0, 0, 0, 0};
        for (int i = 0; i < headers.size(); i++) {
            //find the longest string in each column
            if (headers[i].first.length() > Longest[0]) {
                Longest[0] = headers[i].first.length();
            }
            if (headers[i].second.length() > Longest[1]) {
                Longest[1] = headers[i].second.length();
            }
            if (headers[i].third.length() > Longest[2]) {
                Longest[2] = headers[i].third.length();
            }
            if (headers[i].fourth.length() > Longest[3]) {
                Longest[3] = headers[i].fourth.length();
            }
        }
        //add 1 Space to each column
        for (auto &num: Longest) {
            num += 1;
        }
        //append whitespace to the end of each string to make them all the same length
        for (auto &header: headers) {
            //append WS to the end of all strings in the first column
            //append the '|' character to the end of each string in ALL elements
            while (header.first.length() < Longest[0]) {
                header.first += " ";
            }
            header.first += "|";
            //append WS to the end of all strings in the second column
            while (header.second.length() < Longest[1]) {
                header.second += " ";
            }
            header.second += "|";
            //append WS to the end of all strings in the third column
            while (header.third.length() < Longest[2]) {
                header.third += " ";
            }
            header.third += "|";
            //append WS to the end of all strings in the fourth column
            while (header.fourth.length() < Longest[3]) {
                header.fourth += " ";
            }
        }
        //output the headers
        for (auto &header: headers) {
            std::cout << header.first
                      << header.second
                      << header.third
                      << header.fourth << std::endl;
        }
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