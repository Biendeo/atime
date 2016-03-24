#ifndef ATIME_H
#define ATIME_H

#ifdef __cplusplus
#include <ctime>
#include <string>

class atime {
	public:

	enum WEEKDAY {
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY,
		SUNDAY
	};

	enum MONTH {
		JANUARY,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULY,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER
	};

	atime() {
		timeData = static_cast<time_t>(0);
	};

	atime(time_t time) {
		this->timeData = time;
	};

	atime &operator=(atime otherTime) {
		this->timeData = otherTime.timeData;
		return *this;
	}

	atime &operator=(time_t otherTime) {
		this->timeData = otherTime;
		return *this;
	}

	time_t operator+=(atime &otherTime) {
		timeData += otherTime.timeData;
		return timeData;
	}

	time_t operator+=(time_t &otherTime) {
		timeData += otherTime;
		return timeData;
	}

	friend time_t operator+(atime leftTime, time_t rightTime) {
		return leftTime.timeData + rightTime;
	}

	friend time_t operator+(time_t leftTime, atime rightTime) {
		return rightTime + leftTime;
	}

	friend time_t operator+(atime leftTime, atime rightTime) {
		return leftTime.timeData + rightTime.timeData;
	}

	std::string display(std::string format) {
		size_t foundPos;

		while ((foundPos = format.find("a")) != std::string::npos) {
			format.replace(foundPos, 1, "\v");
		}

		while ((foundPos = format.find("YYYY")) != std::string::npos) {
			format.replace(foundPos, 4, std::to_string(getYear()));
		}
		
		while ((foundPos = format.find("MMM")) != std::string::npos) {
			format.replace(foundPos, 3, "\t");
		}

		while ((foundPos = format.find("MM")) != std::string::npos) {
			format.replace(foundPos, 2, leadZeroes(std::to_string(getMonth()), 2));
		}

		while ((foundPos = format.find("M")) != std::string::npos) {
			format.replace(foundPos, 1, std::to_string(getMonth()));
		}
		
		while ((foundPos = format.find("dd")) != std::string::npos) {
			format.replace(foundPos, 2, leadZeroes(std::to_string(getDayOfMonth()), 2));
		}

		while ((foundPos = format.find("d")) != std::string::npos) {
			format.replace(foundPos, 1, std::to_string(getDayOfMonth()));
		}
		
		while ((foundPos = format.find("hh")) != std::string::npos) {
			format.replace(foundPos, 2, leadZeroes(std::to_string(getHour()), 2));
		}
		
		while ((foundPos = format.find("h")) != std::string::npos) {
			format.replace(foundPos, 1, std::to_string(getHour()));
		}

		while ((foundPos = format.find("mm")) != std::string::npos) {
			format.replace(foundPos, 2, leadZeroes(std::to_string(getMinutes()), 2));
		}

		while ((foundPos = format.find("ss")) != std::string::npos) {
			format.replace(foundPos, 2, leadZeroes(std::to_string(getSeconds()), 2));
		}

		while ((foundPos = format.find("EEE")) != std::string::npos) {
			format.replace(foundPos, 3, weekdayToStrShort(intToWeekday(getDayOfWeek())));
		}

		while ((foundPos = format.find("\t")) != std::string::npos) {
			format.replace(foundPos, 1, monthToStrShort(intToMonth(getMonth())));
		}

		while ((foundPos = format.find("\v")) != std::string::npos) {
			if (isAM()) {
				format.replace(foundPos, 1, "AM");
			} else {
				format.replace(foundPos, 1, "PM");
			}
		}

		return format;
	}

	std::string display() {
		return display("EEE dd/MM/YYYY hh:mm:ss");
	}

	time_t time() {
		return timeData;
	}

	atime &now() {
		timeData = std::time(NULL);
		return *this;
	}

	int getYear() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_year + YEAR_DIFFERENCE_TO_MK;
	}

	int getMonth() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_mon + 1;
	}

	int getDayOfMonth() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_mday;
	}

	int getDayOfYear() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_yday;
	}

	int getDayOfWeek() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_wday;
	}

	int getHour() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_hour;
	}

	int getMinutes() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_min;
	}

	int getSeconds() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_sec;
	}

	bool isAM() {
		if (getHour() < 12) {
			return true;
		} else {
			return false;
		}
	}

	bool isPM() {
		return !isAM();
	}

	void setYear(int year) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_year = year - YEAR_DIFFERENCE_TO_MK;
		timeData = mktime(timeStruct);
	}
	
	void setMonth(int month) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_mon = month - 1;
		timeData = mktime(timeStruct);
	}

	void setMonth(MONTH month) {

	}

	void setDayOfMonth(int day) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_mday = day;
		timeData = mktime(timeStruct);
	}

	void setDayOfYear(int day) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_yday = day;
		timeData = mktime(timeStruct);
	}

	void setDayOfWeek(int day) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_yday = day;
		timeData = mktime(timeStruct);
	}

	void setHour(int hour) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_hour = hour;
		timeData = mktime(timeStruct);
	}

	void setMinutes(int minutes) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_min = minutes;
		timeData = mktime(timeStruct);
	}

	void setSeconds(int seconds) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_sec = seconds;
		timeData = mktime(timeStruct);
	}
	
	static MONTH intToMonth(int i) {
		switch (i) {
			case 1:
				return JANUARY;
			case 2:
				return FEBRUARY;
			case 3:
				return MARCH;
			case 4:
				return APRIL;
			case 5:
				return MAY;
			case 6:
				return JUNE;
			case 7:
				return JULY;
			case 8:
				return AUGUST;
			case 9:
				return SEPTEMBER;
			case 10:
				return OCTOBER;
			case 11:
				return NOVEMBER;
			case 12:
				return DECEMBER;
			default:
				// TODO: Decide what happens with invalid input.
				return JANUARY;
		}
	}
	
	static std::string monthToStrShort(MONTH month) {
		switch (month) {
			case JANUARY:
				return "Jan";
			case FEBRUARY:
				return "Feb";
			case MARCH:
				return "Mar";
			case APRIL:
				return "Apr";
			case MAY:
				return "May";
			case JUNE:
				return "Jun";
			case JULY:
				return "Jul";
			case AUGUST:
				return "Aug";
			case SEPTEMBER:
				return "Sep";
			case OCTOBER:
				return "Oct";
			case NOVEMBER:
				return "Nov";
			case DECEMBER:
				return "Dec";
			default:
				// TODO: Decide what happens with invalid input.
				return "???";
		}
	}

	static WEEKDAY intToWeekday(int i) {
		switch (i) {
			case 0:
				return MONDAY;
			case 1:
				return TUESDAY;
			case 2:
				return WEDNESDAY;
			case 3:
				return THURSDAY;
			case 4:
				return FRIDAY;
			case 5:
				return SATURDAY;
			case 6:
				return SUNDAY;
			default:
				// TODO: Decide what happens with invalid input.
				return MONDAY;
		}
	}

	static std::string weekdayToStrShort(WEEKDAY weekday) {
		switch (weekday) {
			case MONDAY:
				return "Mon";
			case TUESDAY:
				return "Tue";
			case WEDNESDAY:
				return "Wed";
			case THURSDAY:
				return "Thu";
			case FRIDAY:
				return "Fri";
			case SATURDAY:
				return "Sat";
			case SUNDAY:
				return "Sun";
			default:
				// TODO: Decide what happens with invalid input.
				return "???";
		}
	}

	private:
	time_t timeData;

	static const int YEAR_DIFFERENCE_TO_MK = 1900;

	std::string leadZeroes(std::string str, int desiredLength) {
		for (int i = str.length(); i < desiredLength; i++) {
			str.append("0");
		}
		return str;
	}
};

#else

#endif


#endif