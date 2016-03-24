#ifndef ATIME_H
#define ATIME_H

#ifdef __cplusplus
#include <ctime>
#include <string>

class atime {
	public:
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

		while ((foundPos = format.find("YYYY")) != std::string::npos) {
			format.replace(foundPos, 4, std::to_string(getYear()));
		}
		
		while ((foundPos = format.find("MM")) != std::string::npos) {
			// TODO: Format this with a leading 0 if necessary.
			format.replace(foundPos, 2, std::to_string(getMonth()));
		}
		
		while ((foundPos = format.find("dd")) != std::string::npos) {
			// TODO: Format this with a leading 0 if necessary.
			format.replace(foundPos, 2, std::to_string(getDayOfMonth()));
		}
		
		while ((foundPos = format.find("EEE")) != std::string::npos) {
			// TODO: Make a day of week string.
			format.replace(foundPos, 3, std::to_string(getDayOfWeek()));
		}
		
		while ((foundPos = format.find("hh")) != std::string::npos) {
			// TODO: Format this with a leading 0 if necessary.
			format.replace(foundPos, 2, std::to_string(getHour()));
		}

		
		while ((foundPos = format.find("mm")) != std::string::npos) {
			// TODO: Format this with a leading 0 if necessary.
			format.replace(foundPos, 2, std::to_string(getMinute()));
		}

		while ((foundPos = format.find("ss")) != std::string::npos) {
			// TODO: Format this with a leading 0 if necessary.
			format.replace(foundPos, 2, std::to_string(getSecond()));
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
		return localtime(&timeData)->tm_year + 1900;
	}

	int getMonth() {
		return localtime(&timeData)->tm_mon + 1;
	}

	int getDayOfMonth() {
		return localtime(&timeData)->tm_mday;
	}

	int getDayOfYear() {
		return localtime(&timeData)->tm_yday;
	}

	int getDayOfWeek() {
		return localtime(&timeData)->tm_wday;
	}

	int getHour() {
		return localtime(&timeData)->tm_hour;
	}

	int getMinute() {
		return localtime(&timeData)->tm_min;
	}

	int getSecond() {
		return localtime(&timeData)->tm_sec;
	}

	private:
	time_t timeData;
};

#else

#endif


#endif