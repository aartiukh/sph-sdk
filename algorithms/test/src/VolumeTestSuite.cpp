//
// Created by aa on 29.08.20.
//

#include "VolumeTestSuite.h"

#include "Area.h"

#include <gtest/gtest.h>

namespace SPHAlgorithms::TestEnvironment
{

void VolumeTestSuite::testDefaultCtor()
{
  ASSERT_NO_THROW({ Volume v; });
}

} // namespace SPHAlgorithms::TestEnvironment

using namespace SPHAlgorithms::TestEnvironment;

TEST(VolumeTestSuite, testDefaultCtor)
{
  VolumeTestSuite::testDefaultCtor();
}