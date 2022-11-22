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
TEST_CASE("Instances", "[Instances]") {
    Nodes::Node node;
    REQUIRE(node.Instances == 0);
}