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

TEST_CASE("Node Child Link 1", "[Creation]")
{
    //test if the child link is correctly created
    std::string ingredient = "Head";
    auto head = std::make_unique<Nodes::Node>(ingredient);
    REQUIRE(Nodes::Node::instances == 1);
}

TEST_CASE("Node Child Link 2", "[Creation]")
{
    /* test if the child sub-node is correctly created and linked to the parent node
     * */
    std::string names[] = {"Node A", "Node B"};
    auto head = std::make_unique<Nodes::Node>(names[0]);
    auto child = std::make_unique<Nodes::Node>(names[1], std::move(head));
    // Add a debug point to see if the child node is linked to the parent node
    REQUIRE(Nodes::Node::instances == 2); //check if there are 2 instances created
    REQUIRE_FALSE(child->Parent == head); //check if the child node is linked to the parent node
    // check if the Parent has 1 instance in the Children vector
}