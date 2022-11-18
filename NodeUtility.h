//
// Created by halor on 11/17/2022.
//

#pragma once

#include <iostream>
#include <utility>
#include <vector>

namespace NodeUtility {

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
        int instancekey = 0;
        const int generation = 0;
        int population = 0;

        std::vector<std::pair<int, Node *>> Children;
        std::vector<std::pair<const std::string &, int>> ResultedAmountsBuffer;

        Node(std::string ingredient = "", Node *Parent = nullptr)
                : Base(ingredient) {
            this->Children = {};
            this->Parent = Parent;
            std::cout << "New Node called " << ingredient << " was made!" << std::endl;
        }

        ~Node() {
            std::cout << "Node called " << ingredient << " was deleted!" << std::endl;
            //recursively deallocate all sub-nodes
            for (auto &child: Children) {
                delete child.second;
            }
        }
        virtual int Population(int &countpopulation){ //todo test this function
            ///@brief This function will count how many Node instances are in the ingredient tree
            ///@param countpopulation The countpopulation of the ingredient tree
            ///@return The countpopulation of the ingredient tree
            countpopulation += 1;
            //recursively call this function on each sub-node
            for (auto &child: this->Children) {
                child.second->Population(countpopulation);
            }
            return countpopulation;
        }
        virtual int recursivearithmetic() {
            if (this->Parent)
            {
                this->Parent->recursivearithmetic();
            }
            return this->amountresulted;
        }

        virtual int reversearithmetic(Node *node, const int desiredamount) {
            return node->amountonhand;
        }
    };

    Node *head(Node *node) {
        ///@brief This function will return the head node of the tree
        ///@param node The node to find the head of
        ///@return The head Node of the ingredient tree
        while (node->Parent) { //traverse to the head of the ingredient tree
            node = node->Parent;
        }
        return node;
    }
} // Node

