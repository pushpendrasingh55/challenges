#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct my_date_t {
    uint8_t date;       /*< date */
    uint8_t month;      /*< month */
    uint16_t year;      /*< year   */
} my_date_t;

typedef enum status_t {
    SUCCESS,    /**< Function has successfully converted the string to structure */
    NULL_PTR,   /**< Function is given NULL pointers to work with */
    INCORRECT   /**< Incorrect values for date or month or year */
} status_t;

status_t convertStringToDate(const char* dateString, my_date_t* date) {
    if (dateString == NULL || date == NULL) {
        return NULL_PTR; // Return NULL_PTR if any of the pointers is NULL
    }

    // Check if the date string has the expected length
    if (strlen(dateString) != 10) {
        return INCORRECT; // Return INCORRECT if the length is not correct
    }

    // Extract the date, month, and year from the string
    char dateStr[3];
    char monthStr[3];
    char yearStr[5];
    memcpy(dateStr, dateString, 2);
    dateStr[2] = '\0';
    memcpy(monthStr, dateString + 3, 2);
    monthStr[2] = '\0';
    memcpy(yearStr, dateString + 6, 4);
    yearStr[4] = '\0';

    // Convert the extracted strings to integers
    int day = atoi(dateStr);
    int month = atoi(monthStr);
    int year = atoi(yearStr);

    // Validate the converted values
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
        return INCORRECT; // Return INCORRECT if any value is out of range
    }

    // Assign the converted values to the date structure
    date->date = (uint8_t)day;
    date->month = (uint8_t)month;
    date->year = (uint16_t)year;

    return SUCCESS; // Return SUCCESS if the conversion is successful
}

int main() {
    char dateString[11];
    printf("Enter date in the format dd/mm/yyyy: ");
    scanf("%s", dateString);

    my_date_t date;
    status_t status = convertStringToDate(dateString, &date);

    if (status == SUCCESS) {
        printf("Conversion successful!\n");
        printf("Day: %d\n", date.date);
        printf("Month: %d\n", date.month);
        printf("Year: %d\n", date.year);
    } else if (status == NULL_PTR) {
        printf("Error: NULL pointers given!\n");
    } else if (status == INCORRECT) {
        printf("Error: Incorrect date format or values!\n");
    }

    return 0;
}