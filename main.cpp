#include <iostream>
#include <string>

#include "NodeUtility.h"

NodeUtility::Node *populate(NodeUtility::Node *node);

void trail(NodeUtility::Node *node);

namespace TempFunctions {
    //namespace for functions to refactor or utilize later
    std::vector<std::pair<int, std::string>> IngredientsInput(const std::string headingredient = "Head",
                                                              const std::string parentingredient = "Parent") {
        //prompt the user to type in their ingredients
        std::vector<std::pair<int, std::string>> ingredients;
        std::cout << "Type in the ingredients you need to create " << parentingredient << ":" << std::endl;
        while (true) {
            std::string ingredient;
            std::getline(std::cin, ingredient);
            //strip leading and trailing whitespace from ingredient
            bool IsDuplicate = false;
            //parse through the vector if it is not empty
            if (!ingredients.empty()) {
                for (auto &i: ingredients) {
                    if (i.second == ingredient) {
                        IsDuplicate = true;
                        break;
                    }
                }
            }
            if (IsDuplicate) { //if the user input is repeated
                std::cout << "You already typed that ingredient in!" << std::endl;
            } else if (ingredient.empty()) { //if the user input is empty break out of the loop
                break;
            } else if (headingredient == ingredient) { //if the user input is the same as the head ingredient
                std::cout << "You cannot use the same ingredient as the head ingredient!" << std::endl;
            } else if (parentingredient == ingredient) { //if the user input is same as parent ingredient
                std::cout << "You cannot use the same ingredient as the parent ingredient!" << std::endl;
            } else {
                ingredients.emplace_back(std::make_pair(ingredients.size(), ingredient));
            }
        }
        //out the ingredients
        std::cout << "INPUTS:" << std::endl;
        for (const auto &ingredient: ingredients) {
            std::cout << ingredient.first << " : "
                      << ingredient.second << std::endl;
        }
        //return the vector of strings
        return ingredients;
    }

    std::vector<std::pair<int, std::string>> MockPopulate(const std::string Head = "Head",
                                                          const std::string Parent = "Parent",
                                                          std::vector<std::pair<int, std::string>> GlobalIngredients = {}) {

        ///@brief This function will mock populate the tree
        ///@param Head The head ingredient
        ///@param Parent The parent ingredient
        ///@param GlobalIngredients The vector of ingredients to populate the tree with
        ///@return The vector of ingredients to populate the tree with
        //todo finish and debug this function
        //set positional index to start at
        int beginIndex = 0; //the index to start at
        if (!GlobalIngredients.empty()) {
            beginIndex = GlobalIngredients.size()-1;
        }
        //@Note use emplace back std::make_pair
        auto ingredients = TempFunctions::IngredientsInput(Head, Parent);
        // set the positional index to end at
        int endIndex = ingredients.size()-1+beginIndex;
        //add the ingredients to the global vector
        for (auto &ingredient: ingredients) {
            GlobalIngredients.emplace_back(std::make_pair(GlobalIngredients.size(), ingredient.second));
        }
        //recursively call function on the new sttrings in the vector
        for (int i = beginIndex; i <= endIndex; ++i) {
            MockPopulate(Head, GlobalIngredients.at(i).second, GlobalIngredients);
        }
        // return the modifed vector
        return GlobalIngredients;
    }

    bool HasDuplicate(
            const std::vector<std::pair<int, std::string>> UserInputs,
            const std::string Ingredient) {   ///@brief This function will check if the user inputs have any duplicates
        ///@param UserInputs The vector of user inputs
        ///@return True if there are duplicates, false if there are not
        //todo finish and debug this function
        return false;
    }

    void OutputToFile(std::ostream &output, const std::vector<std::pair<int, std::string>> &UserInputs) {
        ///@brief This function will output the user inputs to a file
        ///@param output The output stream to output to
        ///@param UserInputs The vector of user inputs to output
        //todo finish and debug this function
    }
}

int main() {
    //prompt user to type in the name of the item they want to create
    std::string ingredient; //name of the head ingredient item the user wants to create
    while (true) {
        std::cout << "What is the name of the ingredient you want to create?" << std::endl;
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
    TempFunctions::MockPopulate(ingredient);
    //auto head = populate(new NodeUtility::Node(ingredient));
    //delete head;
    return 0;
}

NodeUtility::Node *populate(NodeUtility::Node *node) {
    ///@brief This function will populate the tree with nodes
    ///@param node The node to populate
    ///@return The head Node of the ingredient tree
    std::cout << "Type in the ingredients you need to create " << node->ingredient << ":" << std::endl;
    //output the ingredient trail
    if (node->Parent) {
        //trail(node);
    }
    //prompt the user to type in their ingredients
    std::vector<std::string> ingredients;
    while (true) {
        std::string ingredient;
        std::getline(std::cin, ingredient);
        //strip leading and trailing whitespace from ingredient
        bool IsDuplicate = false;
        //parse through the vector if it is not empty
        if (!ingredients.empty()) {
            for (auto &i: ingredients) {
                if (i == ingredient) {
                    IsDuplicate = true;
                    break;
                }
            }
        }
        if (IsDuplicate) { //if the user input is repeated
            std::cout << "You already typed that ingredient in!" << std::endl;
        } else if (ingredient.empty()) { //if the user input is empty break out of the loop
            break;
        } else if (head(node)->ingredient == ingredient) { //if the user input is the same as the head ingredient
            std::cout << "You cannot use the same ingredient as the head ingredient!" << std::endl;
        } else if (node->Parent->ingredient == ingredient) { //if the user input is same as parent ingredient
            std::cout << "You cannot use the same ingredient as the parent ingredient!" << std::endl;
        } else {
            ingredients.emplace_back(ingredient);
        }
    }
//create sub-nodes with each ingredient
//recursively call this function on each sub-node
//return the head of the ingredient tree
    if (node->Parent) {
        NodeUtility::head(node);
    }
    return node;
}

void trail(NodeUtility::Node *node) {
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