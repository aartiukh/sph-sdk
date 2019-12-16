/**
* @file ROperationsTestSuite.cpp
* @ROperationsTestSuite class defines R-operations test suite
* @author Anton Artiukh (artyukhanton@gmail.com)
* @date Created May 05, 2019
**/

#include "ROperationsTestSuite.h"

#include "ROperations.h"

#include <gtest/gtest.h>
#include <cmath>

namespace SPHAlgorithms
{
namespace TestEnvironment
{

void ROperationsTestSuite::testConjunction()
{
    EXPECT_DOUBLE_EQ(2. - std::sqrt(2.), ROperations::conjunction(1., 1.));
    EXPECT_DOUBLE_EQ(3. - std::sqrt(5.), ROperations::conjunction(2., 1.));
}

void ROperationsTestSuite::testDisjunction()
{
    EXPECT_DOUBLE_EQ(2. + std::sqrt(2.), ROperations::disjunction(1., 1.));
    EXPECT_DOUBLE_EQ(3. + std::sqrt(5.), ROperations::disjunction(2., 1.));
}

} // namespace TestEnvironment
} // namespace SPHAlgorithms

using namespace SPHAlgorithms::TestEnvironment;

TEST(ROperationsTestSuite, testConjunction)
{
    ROperationsTestSuite::testConjunction();
}

TEST(ROperationsTestSuite, testDisjunction)
{
    ROperationsTestSuite::testDisjunction();
}
