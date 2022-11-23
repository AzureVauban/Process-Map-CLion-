#include "Include/Nodes.h"

/* Includes:
 * iostream
 * vector
 * memory
 */

int main() {
    //Nodes::TestFunction();
    auto head = std::make_shared<Nodes::Node>("head");
    auto child1 = std::make_shared<Nodes::Node>("child1", head);
    return 0;
}