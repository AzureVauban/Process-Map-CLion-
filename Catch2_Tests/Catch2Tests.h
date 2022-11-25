//
// Created by halor on 11/21/2022.
//

#ifndef CATCH2_TESTS_CATCH2TESTS_H
#define CATCH2_TESTS_CATCH2TESTS_H

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../Include/Nodes.h"
//fake test methods
namespace Catch2Tests {
    int sum(int a, int b) {
        return a + b;
    } //placeholder function

    int subtraction(int a, int b) {
        return a - b;
    } //placeholder function
    static int testCount = 1;

    std::string TestConcluded() {
        std::string s = "TEST " + std::to_string(testCount) + " CONCLUDED";
        Catch2Tests::testCount += 1;
        return s;
    }
}

#endif //CATCH2_TESTS_CATCH2TESTS_H
