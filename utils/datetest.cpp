# include "Date.h"

int main() {
    string begin = "21/01/1996";
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

    return 0;
}