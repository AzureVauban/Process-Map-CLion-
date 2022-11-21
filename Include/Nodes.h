//
// Created by halor on 11/17/2022.
//

#pragma once

#include <iostream>
#include <utility>
#include <vector>

namespace Nodes {

    struct Base {
        std::string ingredient;
        int amountonhand;
        int amountneeded;
        int amountmadepercraft;
        int amountresulted;

        Base(std::string ingredient = "",
             int amountonhand = 0,
             int amountmadepercraft = 0,
             int amountneeded = 0) {
            this->ingredient = ingredient;
            this->amountonhand = amountonhand;
            this->amountmadepercraft = amountmadepercraft;
            this->amountneeded = amountneeded;
            this->amountresulted = 0;
        }
    };

    struct Node : public Base {
        Node *Parent;
        static int instances;
        int instancekey = 0;
        int generation;
        int population = 0;

        std::vector<std::pair<int, Node *>> Children;
        std::vector<std::pair<const std::string &, int>> ResultedAmountsBuffer;

        Node(std::string ingredient = "",
             Node *Parent = nullptr,
             int amountonhand = 0,
             int amountmadepercraft = 1,
             int amountneeded = 1)
                : Base(ingredient,
                       amountonhand,
                       amountmadepercraft,
                       amountneeded) {
            this->Children = {};
            this->Parent = Parent;
            this->instancekey = instances;
            if (this->Parent) {
                this->generation = this->Parent->generation + 1;
                this->Parent->Children.emplace_back(this->instancekey, this);
            } else {
                this->generation = 0;
            }
            instances++;
            this->population = this->CountNodes(this->population);
        }

        ~Node() {
            //recursively deallocate all sub-nodes
            for (auto &child: Children) {
                delete child.second;
            }
        }

        int CountNodes(int &countpopulation) { //todo test this function
            ///@brief This function will count how many Node instances are in the ingredient tree
            ///@param countpopulation The countpopulation of the ingredient tree
            ///@return The countpopulation of the ingredient tree
            countpopulation += 1;
            //recursively call this function on each sub-node
            for (auto &child: this->Children) {
                child.second->CountNodes(countpopulation);
            }
            return countpopulation;
        }

        void UpdatePopulation(const int countpopulation) {
            ///@brief This function will update the CountNodes variable of all Nodes in a tree
            ///@param countpopulation The countpopulation of the ingredient tree
            this->population = countpopulation;
            //recursively call this function on each sub-node
            for (auto &child: this->Children) {
                child.second->UpdatePopulation(countpopulation);
            }
        }

        std::vector<std::pair<int, Node *>> Search(const std::string &Ingredient,
                                                   std::vector<std::pair<int, Node *>> &Results) {
            ///@brief This function will search for a Node with the given ingredient
            ///@param Ingredient The ingredient to search for
            ///@param Results The vector of results to add to
            ///@return The vector of results
            ///@note This function will search recursively through all sub-nodes
            if (this->ingredient == Ingredient) {
                Results.emplace_back(this->instancekey, this);
            }
            //recursively call this function on each sub-node
            for (auto &child: this->Children) {
                child.second->Search(Ingredient, Results);
            }
            return Results;
        }

        int recursivearithmetic() {
            if (this->Parent) {
                this->Parent->recursivearithmetic();
            }
            return this->amountresulted;
        }

        int reversearithmetic(Node *node, const int desiredamount) {
            for (auto &child: node->Children) {
                child.second->reversearithmetic(child.second, amountonhand);
            }
            return node->amountonhand;
        }
    };

    int Node::instances = 0;

    Node *head(Node *node) {
        ///@brief This function will return the head node of the tree
        ///@param node The node to find the head of
        ///@return The head Node of the ingredient tree
        while (node->Parent) { //traverse to the head of the ingredient tree
            node = node->Parent;
        }
        return node;
    }

    Node *clone(Node *Target,
                Node *Parent,
                const bool clonesubnodes) {
        /// @brief Create a `clone of the Parent node
        /// @param Target Node to clone from
        /// @param Parent Node to clone to
        /// @param clonesubnodes Whether or not to clone subnodes
        /// @return a clone of a argument node
        return new Node(Target->ingredient,
                        Parent,
                        Target->amountonhand,
                        Target->amountmadepercraft,
                        Target->amountneeded);
    }

    namespace temporary {
        //temporary functions for testing output to Console
        std::vector<std::string> AllIngredients(const Node *node, //* start this function off with head Node
                                                std::vector<std::string> &Ingredients) {
            ///@brief This function will return a vector of all ingredients in the tree
            ///@param node The node add the ingredient to the vector from
            ///@param Ingredients The vector of ingredients
            ///@return The vector of ingredients
            Ingredients.emplace_back(node->ingredient);
            for (auto &child: node->Children) {
                AllIngredients(child.second, Ingredients);
            }
            return Ingredients;
        }

        std::vector<std::string> AlignAllIngredients(Node *StartingNode) {
            ///@brief This function will return a vector of all ingredients in the tree and print them to the console
            ///@param StartingNode The node to start the alignment from
            ///@return The vector of ingredients
            std::vector<std::string> Ingredients;
            Ingredients = AllIngredients(head(StartingNode), Ingredients);
            //find the length of the longest string
            int lengthLongeststring = Ingredients[0].length();
            for (auto &ingredient: Ingredients) {
                if (ingredient.length() > lengthLongeststring) {
                    lengthLongeststring = ingredient.length();
                }
            }
            lengthLongeststring += 1;
            //append whitespace to the end of each string to make them all the same length
            for (auto &ingredient: Ingredients) {
                while (ingredient.length() < lengthLongeststring) {
                    ingredient.append(" ");
                }
            }
            //test output alignment
            for (int i = 0; i < Ingredients.size(); i++) {
                std::cout << i << ": " << Ingredients[i] << "| " << &Ingredients[i] << std::endl;
            }
            //return the modified vector
            return Ingredients;
        }
    }
} // Node
