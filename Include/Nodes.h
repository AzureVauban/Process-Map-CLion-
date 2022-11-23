//
// Created by halor on 11/21/2022.
//

#pragma once

#include <iostream>
#include <vector>
#include <memory>

namespace Nodes {
    struct Base {
        std::string ingredient;

        explicit Base(std::string &ingredient) {
            //use of explicit keyword for type safety and to prevent implicit conversions (conversion to wrong type)
            this->ingredient = ingredient;
        }
    };

    struct Node : Base {
        static int instances; //static variable to keep track of instances
        std::unique_ptr<Node> Parent;

        explicit Node(std::string &ingredient,
                      std::unique_ptr<Node> Parent = nullptr)
                : Base(ingredient) {
            std::cout << "Node created with ingredient: " << ingredient << std::endl;
            instances+=1;
            this->Parent = std::move(Parent);
        }

        ~Node() {
            instances -= 1;
            std::cout << "Node destroyed with ingredient: " << ingredient << std::endl;
        }
    };

    int Node::instances = 0; //initialize static variable

    Node *head(Node *node) {
        //returns the head node of the tree
        ///@param node: the node to start from
        ///@return: the head node of the tree
        return node;
    }
}