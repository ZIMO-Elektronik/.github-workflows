#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <workflows/workflows.hpp>

TEST(workflows, add) { EXPECT_EQ(workflows::add(2, 2), 4); }