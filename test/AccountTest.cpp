//
// Created by hp on 19/12/2025.
//
#include <gtest/gtest.h>
#include "Transaction.h"
#include "Account.h"
#include "Date.h"

TEST(AccountTest, DefaultConstructor) {
    Account account;

    EXPECT_TRUE(account.getOwnerName().empty());
    EXPECT_DOUBLE_EQ( account.getBalance(),0.0);
    EXPECT_TRUE(account.getTransactions().empty());
}

TEST(AccountTest, FullConstructor) {
    Account account("John Snow");
    Transaction t1(
        TransactionType::Income,
        1500.0,
        Date(2025, 1, 10),
        "Stipendio",
        "Lavoro"
    );

    Transaction t2(
        TransactionType::Expense,
        80.0,
        Date(2025, 1, 12),
        "Spesa supermercato",
        "Spesa"
    );

    account.addTransaction(t1);
    account.addTransaction(t2);

    EXPECT_EQ(account.getOwnerName(), "John Snow");
    EXPECT_DOUBLE_EQ( account.getBalance(),1420.0);
    EXPECT_EQ(account.getTransactions().size(), 2);
}


