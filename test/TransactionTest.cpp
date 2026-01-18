//
// Created by hp on 19/12/2025.
//

#include <gtest/gtest.h>
#include "Transaction.h"

// Utility per confrontare due year_month_day

TEST(TransactionTest, ConstructorAndGetters_WorkCorrectly) {

    // Arrange
    Transaction t(TransactionType::Income, 100.0,
                   Date(2026,1,15),
                  "Stipendio", "Lavoro");

    // Act + Assert
    EXPECT_EQ(t.getType(), TransactionType::Income);
    EXPECT_DOUBLE_EQ(t.getAmount(), 100.0);
    EXPECT_EQ(t.getDate(), Date(2026,1,15));
    EXPECT_EQ(t.getDescription(), "Stipendio");
    EXPECT_EQ(t.getCategory(), "Lavoro");
}

TEST(TransactionTest, SerializeDeserialize_RoundTripPreservesData) {

    // Arrange
    Transaction original(TransactionType::Expense, 80.5,
                          Date(2026,1,12),
                         "Spesa al supermercato", "Spesa");

    // Act
    std::string row = original.serialize();
    Transaction obtained = Transaction::deserialize(row);

    // Assert
    ASSERT_EQ(obtained.getType(), original.getType()); //faccio assert perchè se sono due tipi diversi non ha senso continuare
    EXPECT_DOUBLE_EQ(obtained.getAmount(), original.getAmount());
    EXPECT_EQ(obtained.getDate(), original.getDate());
    EXPECT_EQ(obtained.getDescription(), original.getDescription());
    EXPECT_EQ(obtained.getCategory(), original.getCategory());
}