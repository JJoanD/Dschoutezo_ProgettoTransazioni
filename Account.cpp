//
// Created by hp on 11/12/2025.
//

#include "Account.h"
#include <fstream>
#include <stdexcept>

// Costruttore di default
Account::Account()
    : ownerName(""), transactions() {}

// Costruttore con nome del proprietario
Account::Account(const std::string& ownerName)
    : ownerName(ownerName), transactions() {}

// Getter per il nome del proprietario
const std::string& Account::getOwnerName() const {
    return ownerName;
}

// Setter per il nome del proprietario
void Account::setOwnerName(const std::string& name) {
    ownerName = name;
}

// Aggiunge una nuova transazione al conto
void Account::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

// Restituisce la lista delle transazioni (in sola lettura)
const std::vector<Transaction>& Account::getTransactions() const {
    return transactions;
}

double Account::getBalance() const {
    double balance = 0.0;
    for (const auto&  t : transactions) {
        if (t.getType()==TransactionType::Income)
            balance += t.getAmount();
        else if (t.getType()==TransactionType::Expense)
            balance -= t.getAmount();
    }


    return balance;
}


void Account::saveToFile(const std::string& filename) const {

    std::ofstream writeFile(filename); //se non esiste lo crea , se esiste lo sovrascrive
    if (!writeFile) {
        throw std::runtime_error("Impossibile aprire il file per scrittura");
    }

    // Prima riga: nome del proprietario
    writeFile << ownerName << "\n";

    // Transazioni
    for (const auto& t : transactions) {
        writeFile << t.serialize() << "\n";
    }
}

void Account::loadFromFile(const std::string& filename) {

    std::ifstream readFile(filename);
    if (!readFile) {
        throw std::runtime_error("Impossibile aprire il file per lettura");
    }

    transactions.clear();

    std::string line;

    // ---------- PROPRIETARIO ----------
    std::getline(readFile, line);
    ownerName = line;

    // ---------- TRANSAZIONI ----------
    while (std::getline(readFile, line)) {

        if (line.empty()) continue;  // salta righe vuote

        Transaction t = Transaction::deserialize(line);
        transactions.push_back(t);
    }
}
