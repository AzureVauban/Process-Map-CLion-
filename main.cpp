#include <iostream>
#include <string>
//#include <iomanip>

#include "Include/NodeUtility.h"

NodeUtility::Node *populate(NodeUtility::Node *node);

void trail(NodeUtility::Node *node);

namespace TempFunctions {
    //namespace for functions to refactor or utilize later
    struct simpleNode{
        std::string Ingredient;
        simpleNode* Next;
        std::vector<simpleNode*> Prev;
        //constructor
        simpleNode(std::string Ingredient = "",
                   simpleNode* Next = nullptr)
        {
            this->Ingredient = Ingredient;
            this->Next = Next;
            if (this->Next)
            {
                this->Next->Prev.emplace_back(this);
            }
        }

        //setters
        void setIngredient(std::string &basicString) {
            this->Ingredient = basicString;
        }
        //destructor
        ~simpleNode() {
            for (auto &i : Prev)
            {
                delete i;
            }
        }

        //getters
        std::vector<std::string> AllIngredients(std::vector<std::string>& Ingredients){
            Ingredients.emplace_back(this->Ingredient);
            for (auto &i : this->Prev)
            {
                i->AllIngredients(Ingredients);
            }
            return Ingredients;
        }
    };

    //namespace Prototypes
    bool HasDuplicate( //check if the vector has a duplicate string
            const std::vector<std::pair<int, std::string>> UserInputs,
            const std::string Ingredient); //todo pass arguments by reference
    std::vector<std::string> alignoutput(std::vector<std::string> &lines);

    //namespace Definitions
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
            if (TempFunctions::HasDuplicate(ingredients, ingredient)) { //if the user input is repeated
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

    std::vector<std::pair<int, std::string>> MockPopulate(const std::string &Head,
                                                          const std::string &Parent,
                                                          std::vector<std::pair<int, std::string>> &GlobalIngredients) {

        ///@brief This function will mock populate the tree
        ///@param Head The head ingredient
        ///@param Parent The parent ingredient
        ///@param GlobalIngredients The vector of ingredients to populate the tree with
        ///@return The vector of ingredients to populate the tree with
        //todo finish and debug this function
        //set positional index to start at
        int beginIndex = 0; //the index to start at
        if (!GlobalIngredients.empty()) {
            beginIndex = GlobalIngredients.size() - 1;
        }
        //@Note use emplace back std::make_pair
        auto ingredients = TempFunctions::IngredientsInput(Head, Parent);
        // set the positional index to end at
        int endIndex = ingredients.size() - 1 + beginIndex;
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
        //todo finish and debug this function
        ///@param UserInputs The vector of user inputs
        ///@return True if there are duplicates, false if there are not
        for (const auto &input: UserInputs) {
            if (input.second == Ingredient) {
                return true;
            }
        }
        return false;
    }

    void OutputToFile(std::ostream &output, const std::vector<std::pair<int, std::string>> &UserInputs) {
        ///@brief This function will output the user inputs to a file
        ///@param output The output stream to output to
        ///@param UserInputs The vector of user inputs to output
        //todo finish and debug this function
    }

    std::vector<std::string> alignoutput(std::vector<std::string> &lines) {
        ///@brief This function will align the output
        ///@param lines The vector of strings to align
        ///@return The vector of strings aligned
        ///@Note utilize the std::setw() function and iomanip library
        //figure out what is the longest string in the vector
        //append whitespace to the end of the strings to align output
        //return the vector of strings for output
        //todo finish and debug this function
        return lines;
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
    std::vector<std::pair<int, std::string>> myInputs = {};
    myInputs = TempFunctions::MockPopulate(ingredient, "", myInputs);
    for (const auto &input: myInputs) { //output all the inputs to the console
        std::cout << input.first << " : " << input.second << std::endl;
    }
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