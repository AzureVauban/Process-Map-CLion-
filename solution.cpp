#include "Include/Nodes.h"

/* Includes:
 * iostream
 * vector
 * memory
 */

int main() {
    //Nodes::TestFunction();
    std::string names[] = {"Node A",
                           "Node B"};
    auto root = std::make_unique<Nodes::Node>(names[0]);
    auto leaf = std::make_unique<Nodes::Node>(names[1], std::move(root));

    return 0;
}