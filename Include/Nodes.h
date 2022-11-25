//
// Created by halor on 11/21/2022.
//

#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <memory>

namespace Nodes {
    /* use smart pointers to manage memory (garbage collection)
     * */
    struct Base {
        std::string name;

        explicit Base(std::string &name) {
            //use of explicit keyword for type safety and to prevent implicit conversions (conversion to wrong type)
            this->name = name;
        }
    };

    struct Node : Base {
        static int instances; //static variable to keep track of instances
        Node *Parent;
        std::vector<std::unique_ptr<Node>> Children;

        /* example of intended link of the data tree: (head->b->f->j)
         *               <head>
         *              / / \ \
         *             a b   c d
         *             | |   | |
         *             e f   g h
         *              /\    /\
         *             i j   k l
         * */
    private:
        void add_child(std::string &name) {
            //emplace "this" into Parent's children's vector
            this->Parent->Children.emplace_back(std::make_unique<Node>(name, //name of the node
                                                                       this)); //parent instance of the Node
        }

    public:
        explicit Node(std::string &name,
                      Node *Parent = nullptr)
                : Base(name) {
            //use of explicit keyword for type safety and to prevent implicit conversions (conversion to wrong type)
            this->Parent = Parent;
            if (this->Parent) {
                std::cout << this->name << " -> "
                          << this->Parent->name << std::endl;
                //emplace "this" into Parent's children's vector
                this->add_child(name);
            }
            instances += 1;

        }

        ~Node() {
            instances -= 1;
            std::cout << "Node instance destroyed with name: " << name << std::endl;
        }
    };

    int Node::instances = 0; //initialize static variable
}