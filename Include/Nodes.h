//
// Created by halor on 11/21/2022.
//

#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <memory>

namespace Nodes {
    void TestFunction() { //test function, placeholder in namespace Nodes
        std::cout << "Test Function from Nodes" << std::endl;
    }

    struct Base {
        std::string ingredient;
    };

    struct Node : Base {
        /* Why is std::shared_ptr used?
         * */
        std::shared_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;

        Node(std::string ingredient,
                      std::shared_ptr<Node> parent = nullptr) {
            this->ingredient = std::move(ingredient);
            this->parent = std::move(parent);
            if (this->parent) {
                std::cout << this->ingredient
                          << " is a sub-node!" << std::endl;
                //emplace node in parent's children vector
                this->parent->children.emplace_back(std::make_shared<Node>(*this));
            }
        }
        ~Node() {
            std::cout << "Node " << this->ingredient << " destroyed!" << std::endl;
        }
    };

    Node* head(Node* node){
    //returns the head node of the tree
    ///@param node: the node to start from
    ///@return: the head node of the tree
        return node;
    }
}