#include <iostream>
#include <string>
#include <sstream>
#include <utility>
/*
ONLY USE AUTO FORMATTING IN CLION IDE
*/
#include "Include/Nodes.h"
/*
Main.cpp should only contain populate, input, and their respective utility functions
Nodes.h should include utility for Node functions and other functions
*/
//prompt input from user
int promptint() {
    ///@brief Prompts user for string input and returns it as an int
    ///@return integer  
    std::stringstream ss;
    std::string input;
    int output;
    std::getline(std::cin, input);
    //strip whitespace
    input.erase(0, input.find_first_not_of(' '));
    //check if each character is a digit (no negs or decimals)

    ss << input;
    ss >> output;
    return output;
}

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
    subnodes = Nodes::head(Parent)->Search(Ingredient, subnodes);
    if (subnodes.size() == 1) {
        // if there is only one ingredient from the search
        std::cout << "Do you want to make a clone of " << Ingredient << "?" << std::endl;
        return new Nodes::Node(Ingredient, Parent);
    } else if (subnodes.size() > 1) {
        // if there are multiple ingredients from the search
        //prompt the user to select the Node they want to clone
        std::cout << "Which verison of " << Ingredient << " do you want to make a clone of:" << std::endl;
        //create headers for the table
        struct columns {
            std::string Index;
            std::string Parent;
            std::string Generation;
            std::string Choice;

            columns(std::string Choice = "Choice",
                    std::string Index = "Index",
                    std::string Parent = "Parent Item",
                    std::string Generation = "Generation"
            ) {
                this->Index = Index;
                this->Parent = Parent;
                this->Generation = Generation;
                this->Choice = Choice;
            }
        };
        std::vector<columns> headers = {columns()};
        int LongestLengthAlign[4] = {6, //choice
                                     5, //index
                                     11, //parent
                                     10};//generation
        //create the table
        for (int i = 0; i < subnodes.size(); i++) {
            //create the row
            headers.emplace_back(std::to_string(i + 1),
                                 std::to_string(subnodes.at(i).first),
                                 subnodes[i].second->ingredient,
                                 std::to_string(subnodes[i].second->generation));
            //check if the row is longer than the headers
            for (int j = 0; j < 4; j++) {
                if (headers.at(i).Index.length() > LongestLengthAlign[j]) {
                    LongestLengthAlign[j] = headers.at(i).Index.length();
                }
            }

        }
        for (auto &i: LongestLengthAlign) {
            i += 1;
        }
        //append whitespace to each string to align the columns
        for (auto &header: headers) {
            //align the Choice column
            while (header.Choice.length() < LongestLengthAlign[0]) {
                header.Choice += " ";
            }
            //align the Index column
            while (header.Index.length() < LongestLengthAlign[1]) {
                header.Index += " ";
            }
            //align the Parent column
            while (header.Parent.length() < LongestLengthAlign[2]) {
                header.Parent += " ";
            }
            //align the Generation column
            while (header.Generation.length() < LongestLengthAlign[3]) {
                header.Generation += " ";
            }
        }
        const int width = headers[0].Choice.length() +
                          headers[0].Index.length() +
                          headers[0].Parent.length() +
                          headers[0].Generation.length() + 4;
        //output the table upper boundary
        for (int i = 0; i < width; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
        //output the table
        for (auto &header: headers) {
            std::cout << header.Choice << "|"
                      << header.Index << "|"
                      << header.Parent << "|"
                      << header.Generation << std::endl;
        }
        //output the table lower boundary
        for (int i = 0; i < width; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
        std::cout << "Enter the number (Choice) of the item you want to clone (Type 0 if you do not want to clone): "
                  << std::endl;
        return new Nodes::Node(Ingredient, Parent);
    } else {
        // if there are no ingredients from the search
        return new Nodes::Node(Ingredient, Parent
        );
    }
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

bool duplicate(const std::vector<std::string> &Inputs,
               const std::string &Input) {
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