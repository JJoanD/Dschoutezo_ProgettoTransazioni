//
// Created by hp on 11/12/2025.
//

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <chrono>

enum class TransactionType {
    Income,
    Expense
}; // si utilizza un enum class per differenziare i diversi tipi di transazione


class Transaction {
public:
    Transaction();

    Transaction(TransactionType type,
                double amount,
                const std::chrono::year_month_day &date,
                const std::string &description,
                const std::string &category = "");

    // Getter
    TransactionType getType() const;

    double getAmount() const;

    const std::chrono::year_month_day &getDate() const;

    const std::string &getDescription() const;

    const std::string &getCategory() const;

    // Setter
    void setType(TransactionType type);

    void setAmount(double amount);

    void setDate(const std::chrono::year_month_day &date);

    void setDescription(const std::string &description);

    void setCategory(const std::string &category);

    void toString(bool colored = false) const;

    // Converte la transazione in una riga di testo per il file
    std::string serialize() const;

    // Crea una transazione a partire da una riga di testo del file
    static Transaction deserialize(const std::string& line);

private:
    TransactionType type;
    double amount;
    std::chrono::year_month_day date;
    std::string description;
    std::string category;
};


#endif //TRANSACTION_H
