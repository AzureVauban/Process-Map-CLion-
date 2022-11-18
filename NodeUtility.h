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

        Base(std::string ingredient = "", int amountonhand = 0) {
            this->ingredient = ingredient;
            this->amountonhand = amountonhand;
        }
    };

    struct Node : public Base {
        Node *Parent;
        std::vector<std::pair<int, Node *>> Children;

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
    };

    Node *head(Node *node) {
        ///@brief This function will return the head node of the tree
        ///@param node The node to find the head of
        ///@return The head Node of the ingredient tree
        while(node->Parent) {
            node = node->Parent;
        }
        return node;
    }
} // Node

