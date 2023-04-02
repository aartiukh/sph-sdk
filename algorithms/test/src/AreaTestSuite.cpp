//
// Created by aa on 29.08.20.
//

#include "AreaTestSuite.h"

#include "Area.h"

#include <gtest/gtest.h>

namespace SPHSDK::TestEnvironment {

void AreaTestSuite::testDefaultCtor()
{
  ASSERT_NO_THROW({Area a;});
}

void AreaTestSuite::testAreaFunction()
{
  Area a;

  ASSERT_EQ(0, a.areaFunction(0, 0));
}
void AreaTestSuite::testIsInsideArea()
{
  Area a;
  Point2F p;

  ASSERT_FALSE(a.isInsideArea(p));
}

} // SPHSDK::TestEnvironment

using namespace SPHSDK::TestEnvironment;

TEST(AreaTestSuite, testDefaultCtor)
{
    AreaTestSuite::testDefaultCtor();
}

TEST(AreaTestSuite, testAreaFunction)
{
  AreaTestSuite::testAreaFunction();
}

TEST(AreaTestSuite, testIsInsideArea)
{
  AreaTestSuite::testIsInsideArea();
}
