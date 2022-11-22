//
// Created by halor on 11/21/2022.
//

#ifndef CATCH2_TESTS_CATCH2TESTS_H
#define CATCH2_TESTS_CATCH2TESTS_H

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../Include/Nodes.h"
//fake test methods
namespace Catch2Tests { //remove this later
    int sum(int &a, int &b) {
        return a + b;
    }
}
#endif //CATCH2_TESTS_CATCH2TESTS_H
