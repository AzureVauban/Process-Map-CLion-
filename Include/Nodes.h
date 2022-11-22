//
// Created by halor on 11/21/2022.
//

#pragma once

#include <iostream>
#include <vector>
namespace Nodes {
    struct Base {
        std::string ingredient = "-";
        int amountonhand = -1;
        int amountneeded = -1;
        int amountmadepercraft = -1;
        int amountresulted = -1;

        Base(std::string &ingredient,
             int &amountonhand,
             int &amountneeded,
             int &amountmadepercraft) {
            this->ingredient = ingredient;
            this->amountonhand = amountonhand;
            this->amountneeded = amountneeded;
            this->amountmadepercraft = amountmadepercraft;
            this->amountresulted = 0;
        }
    };

    struct Node : public Base {
        static int Instances;
        int InstanceKey;
        Node *Parent;
        std::vector<Node *> Children;

        Node(std::string ingredient = "", // NOLINT(google-explicit-constructor)
             Node *Parent = nullptr,
             int amountonhand = 0,
             int amountmadepercraft = 1,
             int amountneeded = 1)
                : Base(ingredient, amountonhand,
                       amountneeded, amountmadepercraft) {
            Instances++;
            this->Children = {};
            this->InstanceKey = Instances;
            this->Parent = Parent;
            if (this->Parent) {
                this->Parent->Children.emplace_back(this);
            }
        }

        ~Node() {
            std::cout << "Node " << this->InstanceKey << " destroyed" << std::endl;
            for (auto &child : this->Children) {
                delete child;
            }
            Instances--;
        }
    };

    int Node::Instances = 0;
    Node* head(Node* node){
        /// Returns the head of the tree
        /// @param node: the node to start from
        /// @return: the head of the tree
        while(node->Parent){
            node = node->Parent;
        }
        return node;
    }
}