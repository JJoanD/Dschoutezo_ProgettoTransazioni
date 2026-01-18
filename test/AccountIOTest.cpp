//
// Created by hp on 16/01/2026.
//
#include <gtest/gtest.h>

#include "Account.h"
#include "Transaction.h"
#include "Date.h"

#include <filesystem>
#include <string>
#include <fstream>

// Helper: crea un path "unico" per il file di test
static std::string makeTempFilename(const std::string& baseName) {
    namespace fs = std::filesystem;
    fs::path p = fs::current_path() / (baseName + ".txt");
    return p.string();
}

TEST(AccountIOTest, SaveToFileTest) {
    const std::string filename = makeTempFilename("account_io_test_roundtrip");

    // Creazione account
    Account original("Joan");
    original.addTransaction(Transaction(
        TransactionType::Expense, 80.0, Date(2025, 1, 12),
        "Spesa al supermercato", "Spesa"
    ));

   //Salvo su file
    std::cout << "WD test: " << std::filesystem::current_path() << "\n";
    std::cout << "File assoluto: " << std::filesystem::absolute(filename) << "\n";
    original.saveToFile(filename);
    ASSERT_TRUE(std::filesystem::exists(filename))
    << "File NON trovato qui: " << std::filesystem::absolute(filename);

    //
    Account loaded;
    loaded.loadFromFile(filename);

    //Confronto tra i due account
    EXPECT_EQ(loaded.getOwnerName(), original.getOwnerName());
    EXPECT_EQ(loaded.getTransactions().size(), original.getTransactions().size());
    EXPECT_DOUBLE_EQ(loaded.getBalance(), original.getBalance());

    const auto& a = original.getTransactions();
    const auto& b = original.getTransactions();

    ASSERT_EQ(a.size(), b.size()); // se la dimensione non è la stessa non ha senso continuare
    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i].getType(), b[i].getType());
        EXPECT_EQ(a[i].getAmount(), b[i].getAmount());
        EXPECT_EQ(a[i].getDate() , b[i].getDate());
        EXPECT_EQ(a[i].getCategory(), b[i].getCategory());
        EXPECT_EQ(a[i].getDescription(),b[i].getDescription());
    }

    std::filesystem::remove(filename);
}

TEST(AccountIOTest, LoadFromFileTest) {
    const std::string filename = "bad_file.txt";
    {
        std::ofstream out(filename);
        out << "Joan\n";
        out << "EXPENSE;2025-01-12;13.0;Pizzeria-Osvaldo;Uscite\n";
    }

    Account acc;
    acc.loadFromFile(filename);
    //EXPECT_THROW(acc.loadFromFile(filename), std::runtime_error);
    EXPECT_EQ(acc.getOwnerName(), "Joan");
    EXPECT_DOUBLE_EQ(acc.getBalance(), -13.0);

    ASSERT_EQ(acc.getTransactions().size(), 1);
    const auto& a=acc.getTransactions();
    for (const auto& x : a) {
      EXPECT_EQ(x.getType(), TransactionType::Expense);
      EXPECT_EQ(x.getDate(), Date(2025, 1, 12));
      EXPECT_EQ(x.getDescription(), "Pizzeria-Osvaldo");
      EXPECT_EQ(x.getCategory(), "Uscite");
    }

    std::filesystem::remove(filename);
}
