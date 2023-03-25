//
// Created by aa on 29.08.20.
//

#include "VolumeTestSuite.h"

#include "Area.h"

#include <gtest/gtest.h>

namespace SPHSDK::TestEnvironment
{

void VolumeTestSuite::testDefaultCtor()
{
  ASSERT_NO_THROW({ Volume v; });
}

} // namespace SPHSDK::TestEnvironment

using namespace SPHSDK::TestEnvironment;

TEST(VolumeTestSuite, testDefaultCtor)
{
  VolumeTestSuite::testDefaultCtor();
}
