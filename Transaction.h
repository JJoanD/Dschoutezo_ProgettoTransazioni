//
// Created by hp on 11/12/2025.
//

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include  "Date.h"

enum class TransactionType {
    Income,
    Expense
}; // si utilizza un enum class per differenziare i diversi tipi di transazione


class Transaction {
public:
    Transaction();

    Transaction(TransactionType type,
                double amount,
                const Date& date,
                const std::string &description,
                const std::string &category = "");

    // Getter
    TransactionType getType() const;

    double getAmount() const;

    const Date &getDate() const;

    const std::string &getDescription() const;

    const std::string &getCategory() const;

    // Setter
    void setType(TransactionType type);

    void setAmount(double amount);

    void setDescription(const std::string &description);

    void setDate(const Date &date);

    void setCategory(const std::string &category);

    void toString() const;

    std::string serialize() const;     // Converte la transazione in una riga di testo per il file

    static Transaction deserialize(const std::string& line);     // Crea una transazione a partire da una riga di testo del file


private:
    TransactionType type;
    double amount;
    Date date;
    std::string description;
    std::string category;
};


#endif //TRANSACTION_H
