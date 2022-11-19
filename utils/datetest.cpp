# include "Date.h"

int main() {
    string begin = "01/01/1970";
    string end = "07/10/2012";

    string dates[] = {
        "05/09/1989",
        "01/12/1999",
        "03/09/2006",
        "21/05/2030"
    };
    
    Date begin_date(begin);
    Date end_date(end);

    printf("\n");
    for (int index = 0; index < 4; ++index) {
        string* date = dates + index;
        Date curr_date(*date);
        bool result = curr_date.in_range(begin_date, end_date);
        printf("Curr_date in range(begin, end): %d\n\n", result);
    }

    for (int i = 0; i < 9; ++i) {
        Date rand_date;
        printf("to_string: %s\n\n", rand_date.to_string()->c_str());
    }

    return 0;
}