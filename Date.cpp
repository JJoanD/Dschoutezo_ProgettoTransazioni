//
// Created by hp on 08/01/2026.
//


#include "Date.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

Date::Date(int year, int month, int day) : y_(year), m_(month), d_(day) {
    if (!isValid()) {
        throw std::runtime_error("Data non valida");
    }
}

bool Date::isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(int y, int m) {
    switch (m) {
        case 1:  return 31;
        case 2:  return isLeapYear(y) ? 29 : 28;
        case 3:  return 31;
        case 4:  return 30;
        case 5:  return 31;
        case 6:  return 30;
        case 7:  return 31;
        case 8:  return 31;
        case 9:  return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
}

bool Date::isValid() const {
    if (y_ < 1) return false;
    if (m_ < 1 || m_ > 12) return false;
    int dim = daysInMonth(y_, m_);
    if (dim == 0) return false;
    return d_ >= 1 && d_ <= dim;
}

std::string Date::toISO() const {
    std::ostringstream oss; //crea una string scrivibile come stream
    oss << y_ << '-'
        << std::setw(2) << std::setfill('0') << m_ << '-' //forza mese e giorno a due cifre,mettendo lo 0 davanti
        << std::setw(2) << std::setfill('0') << d_;
    return oss.str();
}

Date Date::fromISO(const std::string& iso) {
    // atteso: YYYY-MM-DD
    int y = 0, m = 0, d = 0;
    char sep1 = 0, sep2 = 0;

    std::istringstream iss(iso); //crea uno stream a partire dalla variabile in ingresso
    if (!(iss >> y >> sep1 >> m >> sep2 >> d) || sep1 != '-' || sep2 != '-') { //controllo validità e in contemporanea assegnazione valori
        throw std::runtime_error("Formato data non valido (atteso YYYY-MM-DD): " + iso);
    }

    Date dt(y, m, d); // valida nel costruttore
    return dt;
}

bool operator==(const Date& a, const Date& b) {
    return a.y_ == b.y_ && a.m_ == b.m_ && a.d_ == b.d_;
}

bool operator<(const Date& a, const Date& b) {
    if (a.y_ != b.y_) return a.y_ < b.y_;
    if (a.m_ != b.m_) return a.m_ < b.m_;
    return a.d_ < b.d_;
}
