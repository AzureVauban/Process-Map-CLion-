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
    std::cout << Catch2Tests::TestConcluded() << std::endl;
}

TEST_CASE("Node Child Link 2", "[Creation]")
{
    /* test if the child_node sub-node is correctly created and linked to the parent node
     * */
    std::string names[] = {"Node A",
                           "Node B"};
    auto root = new Nodes::Node(names[0]);
    auto child_node = new Nodes::Node(names[1], root);
    // Add a debug point to see if the child_node node is linked to the parent node
    REQUIRE(Nodes::Node::instances == 2); //check if there are 2 instances created
   // REQUIRE_FALSE(child_node->Parent.get()->name ==
   //               root.get()->name); //check if the child_node node is linked to the parent node
    std::cout << Catch2Tests::TestConcluded() << std::endl;
}