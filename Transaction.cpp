//
// Created by hp on 11/12/2025.
//

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#include "Transaction.h"
#include <sstream>
#include <stdexcept>
#include  <format>
#include <iostream>

// Costruttore di default
Transaction::Transaction()
    : type(TransactionType::Income),
      amount(0.0),
      date(0,0,0),
      description(""),
      category("") {}

// Costruttore completo
Transaction::Transaction(TransactionType type,double amount,const Date& date,const std::string& description,const std::string& category)
        : type(type),
          amount(amount),
          date(date),
          description(description),
          category(category) {}

// Getter
TransactionType Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
const Date &Transaction::getDate() const {return date;}
const std::string& Transaction::getDescription() const { return description; }
const std::string& Transaction::getCategory() const { return category; }

// Setter
void Transaction::setType(TransactionType t) { type = t; }
void Transaction::setAmount(double a) { amount = a; }
void Transaction::setDate(const Date &date) {this->date = date;}
void Transaction::setDescription(const std::string& desc) { description = desc; }
void Transaction::setCategory(const std::string& cat) { category = cat; }

//altro
void Transaction::toString(bool colored) const
{
    const char* color = "";
    const char* reset = "";

    if (colored) {
        color = (type == TransactionType::Income ? GREEN : RED);
        reset = RESET;
    }

    std::cout
      << "- "
      << (type == TransactionType::Income ? "[ENTRATA] " : "[USCITA] ")
      << description
      << " | " << color << " Importo: " << (type == TransactionType::Income? "+" : "-" )<< amount << reset
      << " | Data: " << this->getDate().toISO() 
      << " | Categoria: " << category << "\n"
      ;
}

std::string Transaction::serialize() const {
    std::ostringstream newLine;

    // Tipo: "INCOME" o "EXPENSE"
    std::string typeTrans = (type == TransactionType::Income ? "INCOME" : "EXPENSE");

    // Formato: tipo;YYYY-MM-DD;amount;description;category
    newLine << typeTrans << ";"
        << date.toISO() << ";"
        << amount << ";"
        << description << ";"
        << category;

    return newLine.str();
}


Transaction Transaction::deserialize(const std::string& line) {

    std::stringstream ss(line);   // flusso sulla riga
    std::string part;             // campo temporaneo

    // ---------- TIPO ----------
    std::getline(ss, part, ';');
    TransactionType tType;

    if (part == "INCOME") {
        tType = TransactionType::Income;
    } else if (part == "EXPENSE") {
        tType = TransactionType::Expense;
    } else {
        throw std::runtime_error("Tipo di transazione non valido");
    }

    // ---------- DATA ----------
    if (!std::getline(ss, part, ';'))
        throw std::runtime_error("Riga malformata: manca DATE");

    Date date = Date::fromISO(part);

    // ---------- IMPORTO ----------
    std::getline(ss, part, ';');
    double amount = std::stod(part);

    // ---------- DESCRIZIONE ----------
    std::string description;
    std::getline(ss, description, ';');

    // ---------- CATEGORIA ----------
    std::string category;
    std::getline(ss, category);   // fino a fine riga

    return Transaction(tType, amount, date, description, category);
}


