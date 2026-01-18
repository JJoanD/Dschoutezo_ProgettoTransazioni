//
// Created by hp on 08/01/2026.
//

#ifndef DATE_H
#define DATE_H



#pragma once
#include <string>

class Date {
public:
    Date() = default;
    Date(int year, int month, int day);

    int year() const { return y_; }
    int month() const { return m_; }
    int day() const { return d_; }

    // "2025-01-12"
    std::string toISO() const;

    // Legge "YYYY-MM-DD"
    static Date fromISO(const std::string& iso);

    // Validazione base (inclusi anni bisestili)
    bool isValid() const;

    // Confronti utili (per ordinare transazioni, ecc.)
    friend bool operator==(const Date& a, const Date& b);
    friend bool operator<(const Date& a, const Date& b);

private:
    int y_{1970};
    int m_{1};
    int d_{1};

    static bool isLeapYear(int y);
    static int daysInMonth(int y, int m);
};

#endif //DATE_H
