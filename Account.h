//
// Created by hp on 11/12/2025.
//

#ifndef ACCOUNT_H
#define ACCOUNT_H


#include <string>
#include <vector>
#include "Transaction.h"
#include "Date.h"

class Account {

public:
    // Costruttore di default
    Account();

    // Costruttore con nome del proprietario
    explicit Account(const std::string& ownerName);

    // Getter e setter per il nome del proprietario
    const std::string& getOwnerName() const;
    void setOwnerName(const std::string& name);

    // Aggiunge una nuova transazione al conto
    void addTransaction(const Transaction& transaction);

    // Restituisce la lista delle transazioni (in sola lettura)
    const std::vector<Transaction>& getTransactions() const;

    // Calcola il saldo attuale del conto
    double getBalance() const;

    void saveToFile(const std::string& filename)const;
    void loadFromFile(const std::string& filename);

    void searchByDate(const Date& date);

private:
    std::string ownerName;                 // Nome del titolare del conto
    std::vector<Transaction> transactions; // Lista di transazioni

};



#endif //ACCOUNT_H
