//
// Created by halor on 11/21/2022.
//

#pragma once

#include <iostream>

namespace Nodes {
    struct Base{
        Base() {
            std::cout << "Base constructor called" << std::endl;
        }
        ~Base() {
            std::cout << "Base destructor called" << std::endl;
        }
    };

    struct Node : public Base{
        Node() {
            std::cout << "Node constructor called" << std::endl;
        }
        ~Node() {
            std::cout << "Node destructor called" << std::endl;
        }
    };
}