#include "lib.h"

#include <gtest/gtest.h>


TEST(helloworld, version_more_than_zero) {
    ASSERT_GT(hello::version(), 0);
}
