//
// Created by hp on 19/12/2025.
//

#include <gtest/gtest.h>
#include "Transaction.h"
#include <chrono>


// Utility per confrontare due year_month_day
static void expectSameDate(const std::chrono::year_month_day& a,
                           const std::chrono::year_month_day& b) {
    EXPECT_EQ(int(a.year()), int(b.year()));
    EXPECT_EQ(unsigned(a.month()), unsigned(b.month()));
    EXPECT_EQ(unsigned(a.day()), unsigned(b.day()));
}

TEST(TransactionTest, ConstructorAndGetters_WorkCorrectly) {
    using namespace std::chrono;

    // Arrange
    Transaction t(TransactionType::Income, 100.0,
                  year{2025}/month{1}/day{10},
                  "Stipendio", "Lavoro");

    // Act + Assert
    EXPECT_EQ(t.getType(), TransactionType::Income);
    EXPECT_DOUBLE_EQ(t.getAmount(), 100.0);
    expectSameDate(t.getDate(), year{2025}/month{1}/day{10});
    EXPECT_EQ(t.getDescription(), "Stipendio");
    EXPECT_EQ(t.getCategory(), "Lavoro");
}

TEST(TransactionTest, SerializeDeserialize_RoundTripPreservesData) {
    using namespace std::chrono;

    // Arrange
    Transaction original(TransactionType::Expense, 80.5,
                         year{2025}/month{1}/day{12},
                         "Spesa al supermercato", "Spesa");

    // Act
    std::string row = original.serialize();
    Transaction parsed = Transaction::deserialize(row);

    // Assert
    EXPECT_EQ(parsed.getType(), original.getType());
    EXPECT_DOUBLE_EQ(parsed.getAmount(), original.getAmount());
    expectSameDate(parsed.getDate(), original.getDate());
    EXPECT_EQ(parsed.getDescription(), original.getDescription());
    EXPECT_EQ(parsed.getCategory(), original.getCategory());
}