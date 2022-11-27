#include "Include/Nodes.h"
namespace temptest {
    struct A {
        std::string ingredient;
        int amountonhand;
        int amountneeded;
        int amountmadepercraft;
        int amountresulted;

        explicit A(std::string ingredient = "",
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

    struct B : public A {
        B *Parent;
        static int instances;
        int instance_key = 0;
        int generation;
        std::vector<std::pair<int, B *>> Children;
        std::vector<std::pair<const std::string &, int>> ResultedAmountsBuffer;

        explicit  B(std::string ingredient = "",
                    B *Parent = nullptr,
                    int amountonhand = 0,
                    int amountmadepercraft = 1,
                    int amountneeded = 1)
                : A(std::move(ingredient),
                    amountonhand,
                    amountmadepercraft,
                    amountneeded) {
            this->Children = {};
            this->Parent = Parent;
            this->instance_key = instances;
            if (this->Parent) {
                this->generation = this->Parent->generation + 1;
                this->Parent->Children.emplace_back(this->instance_key, this);
            } else {
                this->generation = 0;
            }
            instances++;
            //this->population = this->CountNodes(this->population);
        }

        ~B() {
            //recursively deallocate all sub-nodes
            for (auto &child: Children) {
                delete child.second;
            }
        }
    };
}
/* Includes:
 * iostream
 * vector
 * memory
 */

int main() {
    //Nodes::TestFunction();
    std::string names[] = {"B A",
                           "B B"};
    //auto root = std::make_unique<Nodes::Node>(names[0]);
    //auto leaf = std::make_unique<Nodes::Node>(names[1], std::move(root));
    auto head = new temptest::B("Head");
    auto child = new temptest::B("Child",head);
    return 0;
}