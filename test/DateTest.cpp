//
// Created by hp on 15/01/2026.
//
#include <gtest/gtest.h>
#include "Date.h"

TEST(DateTest, ToISO_ProducesCorrectFormat) {
    Date d(2025, 1, 12);
    EXPECT_EQ(d.toISO(), "2025-01-12");
}

TEST(DateTest, FromISO_ParsesCorrectly) {
    Date d = Date::fromISO("2025-01-12");
    EXPECT_EQ(d, Date(2025, 1, 12));
}

TEST(DateTest, FromISO_RejectsWrongFormat) {
    EXPECT_THROW(Date::fromISO("2025/01/12"), std::runtime_error);
    EXPECT_THROW(Date::fromISO("2025-Jan-12"), std::runtime_error);
}
