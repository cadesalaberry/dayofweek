#include <stdio.h>
#include <string.h>

char week[7][9] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};


int get_day_from_DDMMYYYY(char const input[]) {

	return atoi(input) / 1000000;
}


int get_month_from_DDMMYYYY(char const input[]) {

	int day = get_day_from_DDMMYYYY(input);

	int tmp = atoi(input);
	tmp = tmp - day * 1000000;
	int month = tmp / 10000;

	return month;
}


int get_year_from_DDMMYYYY(char const input[]) {

	int day = get_day_from_DDMMYYYY(input);
	int month = get_month_from_DDMMYYYY(input);

	int tmp = atoi(input);
	tmp = tmp - day * 1000000;
	tmp = tmp - month * 10000;
	int year = tmp;

	return year;
}


/**
 * Validates the the char array is of the form: "DDMMYYYY"
 * with coherent values for day, month and year.
 */
int validate(char const input[]) {

	int size = strlen(input);

	// Checks that the input has the right size.
	if (size != 8) {
		printf("Size matters. found %i.\n", size);
		return 0;
	}

	// Checks that the characters are all digits.
	int i;
	for (i = 0; i < size; i++) {

		if (isdigit(input[i])) {
			continue;
		} else {
			printf("'%c' is not a digit.\n", input[i]);
			return 0;
		}
	}

	int day 	= get_day_from_DDMMYYYY(input);
	int month 	= get_month_from_DDMMYYYY(input);
	int year 	= get_year_from_DDMMYYYY(input);

	if (1 > day || day > 31) {
		printf("The day %i is not in range.\n", day);
		return 0;
	}
	if (1 > month || month > 12) {
		printf("The month %i is not in range.\n", month);
		return 0;
	}
	if (1 > year || year > 9999) {
		printf("The year %i is not in range.\n", year);
		return 0;
	}

	return 1;
}


int dayofweek(int day, int month, int year) {

	int adjustment, mm, yy;
 
	adjustment = (14 - month) / 12;
	mm = month + 12 * adjustment - 2;
	yy = year - adjustment;

	return (day + (13 * mm - 1) / 5 +
		yy + yy / 4 - yy / 100 + yy / 400) % 7;
}


int main(int argc, char const *argv[]) {	

	char birthday[100];
	
	printf("What is yout birthday (format: DDMMYYYY) : ");
	scanf("%s", birthday);
	
	if (!validate(birthday)) {
		printf("Your input is invalid.\n");
		return -1;
	}

	int day 	= get_day_from_DDMMYYYY(birthday);
	int month 	= get_month_from_DDMMYYYY(birthday);
	int year 	= get_year_from_DDMMYYYY(birthday);

	int week_index = dayofweek(day,month,year);

	printf("The %i/%i/%i is a %s.\n",
		day, month, year, week[week_index]);

	printf("The following 5 years on which the %i/%i falls on a %s are:\n",
		day, month, week[week_index]);

	int i;
	int tmp_year = year + 1;

	for (i = 0; i < 5; tmp_year++) {

		if (dayofweek(day, month, tmp_year) == week_index) {
			printf("%i\n", tmp_year);
			i++;
		}
	}

	return 0;
}