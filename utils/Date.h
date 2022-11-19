# pragma once
# include <string>
# include <ctime>
# include <iostream>
# include "Random.h"

using std::string;
using std::stoi;

class Date {
    private:
        time_t time_value = 0;
        tm* date_time;

    public:
        Date() {
            time_value = time(NULL);
            date_time = localtime(&time_value);
            int day = random(1, 31);
            int month = random(0, 11);
            int year = random(100, date_time->tm_year);
            date_time->tm_hour = date_time->tm_min = date_time->tm_sec = 0;
            date_time->tm_year = year;
            date_time->tm_mon = month;
            date_time->tm_mday = day;
            time_value = mktime(date_time);
        }

        Date(string& pString) {
            int day = stoi( pString.substr(0, 2) );
            int month = stoi( pString.substr(3, 2) );
            int year = stoi( pString.substr(6, 4) );
            date_time = localtime(&time_value);
            date_time->tm_year = (year - 1900);
            date_time->tm_mon = (month - 1);
            date_time->tm_mday = (day);
            date_time->tm_hour = date_time->tm_min = date_time->tm_sec = 0;
            time_value = mktime(date_time);
        }

        string* to_string() {
            string* result;
            char buffer[80];
            strftime(buffer, 80, "%d/%m/%Y", date_time);
            result = new string(buffer);
            return result;
        }

        bool in_range(Date& pStart, Date& pEnd, bool pInclusive = true) {
            if (pInclusive) {
                return operator>=(pStart) && operator<=(pEnd);
            } else {
                return operator>(pStart) && operator<(pEnd);
            }
        }

        bool in_range(Date* pStart, Date* pEnd, bool pInclusive = true) {
            return in_range(*pStart, *pEnd, pInclusive);
        }

        bool operator==(Date& pDate) {
            return this->time_value == pDate.time_value;
        }

        bool operator<(Date& pDate) {
            return this->time_value < pDate.time_value;
        }

        bool operator>(Date& pDate) {
            return this->time_value > pDate.time_value;
        }

        bool operator<=(Date& pDate) {
            return this->time_value <= pDate.time_value;
        }

        bool operator>=(Date& pDate) {
            return this->time_value >= pDate.time_value;
        }

        bool operator==(Date* pDate) {
            return operator==(*pDate);
        }

        bool operator<(Date* pDate) {
            return operator<(*pDate);
        }

        bool operator>(Date* pDate) {
            return operator>(*pDate);
        }

        bool operator<=(Date* pDate) {
            return operator<=(*pDate);
        }

        bool operator>=(Date* pDate) {
            return operator>=(*pDate);
        }
};