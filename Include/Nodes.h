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
         * Why is std::move used?
         * Why is explicit keyword used?
         * */
        std::shared_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;

        explicit Node(std::string ingredient,
                      std::shared_ptr<Node> parent = nullptr) {
            this->ingredient = std::move(ingredient);
            this->parent = std::move(parent);
            if (this->parent) {
                std::cout << "This (" << this->ingredient
                          << ") is a sub-node!" << std::endl;
            }
        }

        ~Node() {
            std::cout << "Node " << this->ingredient << " destroyed!" << std::endl;
        }
    };
}