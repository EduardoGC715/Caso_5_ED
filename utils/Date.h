# pragma once
# include <string>
# include <ctime>
# include <iostream>
using std::string;
using std::stoi;

class Date {
    private:
        time_t time_value = 0;

    public:
        Date(string& pString) {
            // TODO: Buscar alternativa a substr para evitar 02/MM/YYYY vs 2/MM/YYYY
            int day = stoi( pString.substr(0, 2) );
            int month = stoi( pString.substr(3, 2) );
            int year = stoi( pString.substr(6, 4) );
            tm* date_time = localtime(&time_value);
            date_time->tm_year = (year - 1900);
            date_time->tm_mon = (month - 1);
            date_time->tm_mday = (day);
            date_time->tm_hour = date_time->tm_min = date_time->tm_sec = 0;
            time_value = mktime(date_time);
            // printf("Date: %s", ctime(&time_value));
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