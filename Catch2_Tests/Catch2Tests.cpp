//
// Created by halor on 11/21/2022.
//

#include "Catch2Tests.h"
/* TEST CASES NEEDED TO BE ADDED
 * - means not yet added
 * = means added
 *
 * - ref count of Nodes is 0 at program termination
 * - Instances are correctly created and destroyed
 * - recursive math methods return the correct result
 * - search (recursively) returns the correct result
 * - subpopulation function returns the correct result
 * - population function returns the correct result
 * - population function returns the correct result (int)
 */

TEST_CASE("Node Child Link 1","[Creation]")
{
    //test if the sub-node is correctly created and placed into head
    auto head = std::make_shared<Nodes::Node>("head");
    auto child1 = std::make_shared<Nodes::Node>("child 1", head);
    REQUIRE(head->children.size() == 1);
}
