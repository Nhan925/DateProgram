#include <iostream>
#include <string> //De thuc hien cac thao tac voi xau
#include <cmath> //De dung ham ceil()
using namespace std;

//Cac ham dung trong chuong trinh
void StringToNum(string s, int& day, int& month, int& year);
bool CheckDate(int day, int month, int year);
bool LeapYear(int year);
int DaysOfMonth(int month, int year);
string Yesterday(int day, int month, int year);
void UsualTomorrow(string& date, int day, int month, int year);
string Tomorrow(int day, int month, int year);
string KDaysBefore(string date, int k);
string KDaysAfter(string date, int k);
string DayOfWeek(int day, int month, int year);
int WeekOfYear(string date, int year);

//Chuong trinh chinh
int main() {
	cout << "DD/MM/YYYY (YYYY thuoc [1000; 9999]): ";
	string date;
	getline(cin, date);
	int day = 0, month = 0, year = 0;
	StringToNum(date, day, month, year);
	if (CheckDate(day, month, year)) cout << "Hop le !\n";
	else {
		cout << "Khong hop le !\n";
		return 0;
	}
	cout << "So ngay cua thang " << month << " nam " << year << " la: " << DaysOfMonth(month, year) << endl;
	cout << "Ngay hom qua la: " << Yesterday(day, month, year) << endl;
	cout << "Ngay mai la: " << Tomorrow(day, month, year) << endl;
	int k = 0;
	cout << "Nhap k: ";
	cin >> k;
	cout << "Ngay " << k << " truoc do: " << KDaysBefore(date, k) << endl;
	cout << "Ngay " << k << " ke tiep: " << KDaysAfter(date, k) << endl;
	cout << "Ngay nhap vao la: " << DayOfWeek(day, month, year) << endl;
	cout << "Ngay nhap vao thuoc tuan thu: " << WeekOfYear(date, year) << endl;
	return 0;
}

//Bien chuoi ki tu ngay/thang/nam thanh ba so nguyen luu trong day, month, year
void StringToNum(string s, int& day, int& month, int& year) {
	day = (s[0] - '0') * 10 + (s[1] - '0');
	month = (s[3] - '0') * 10 + (s[4] - '0');
	year = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');
}

//Kiem tra nam nhuan
bool LeapYear(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) return 1;
	else return 0;
}

//Kiem tra tinh hop le cua ngay thang nam
bool CheckDate(int day, int month, int year) {
	if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) return 0;
	switch (month) {
	case 4: case 6: case 9: case 11: {
		if (day > 30) return 0;
		break;
	}
	case 2: {
		if (LeapYear(year)) {
			if (day > 29) return 0;
		}
		else if (day > 28) return 0;
		
		break;
	}
	}
	return 1;
}

//So ngay cua thang
int DaysOfMonth(int month, int year) {
	switch (month) {
	case 4: case 6: case 9: case 11: {
		return 30;
		break;
	}
	case 2: {
		if (LeapYear(year)) return 29;
		else return 28;
		break;
	}
	default: {
		return 31;
		break;
	}
	}
}

//Ngay hom qua cua ngay nhap vao
string Yesterday(int day, int month, int year) {
	string date;
	if (day == 1) {
		switch (month) {
		case 1: {
			date =  "31/12/" + to_string(year - 1);
			break;
		}
		case  3: {
			if (LeapYear(year)) date = "29/02/" + to_string(year);
			else date = "28/02/" + to_string(year);
			break;
		}
		case 8: {
			date = "31/07/" + to_string(year);
			break;
		}
		case 5: case 7: case 10: case 12: {
			if (month - 1 > 9) date = "30/" + to_string(month - 1) + '/' + to_string(year);
			else date = "30/0" + to_string(month - 1) + '/' + to_string(year);
			break;
		}
		default: {
			if (month - 1 > 9) date = "31/" + to_string(month - 1) + '/' + to_string(year);
			else date = "31/0" + to_string(month - 1) + '/' + to_string(year);
			break;
		}
		}
	}
	else {
		string dayday;
		day--;
		if (day > 9) dayday = to_string(day);
		else dayday = '0' + to_string(day);
		if (month > 9) date = dayday + '/' + to_string(month) + '/' + to_string(year);
		else date = dayday + '/' + '0' + to_string(month) + '/' + to_string(year);
	}
	return date;
}

//Ngay mau cua cac ngay khong dac biet, ho tro cho ham Tomorrow
void UsualTomorrow(string& date, int day, int month, int year) {
	string dayday;
	day++;
	if (day > 9) dayday = to_string(day);
	else dayday = '0' + to_string(day);
	if (month > 9) date = dayday + '/' + to_string(month) + '/' + to_string(year);
	else date = dayday + '/' + '0' + to_string(month) + '/' + to_string(year);
}

//Ngay mai cua ngay nhap vao
string Tomorrow(int day, int month, int year) {
	string date;
	switch (month) {
	case 12: {
		if (day == 31) date = "01/01/" + to_string(year + 1);
		else UsualTomorrow(date, day, month, year);
		break;
	}
	case 2: {
		if (LeapYear(year)) {
			if (day == 29) date = "01/03/" + to_string(year);
			else UsualTomorrow(date, day, month, year);
		}
		else {
			if (day == 28) date = "01/03/" + to_string(year);
			else UsualTomorrow(date, day, month, year);
		}
		break;
	}
	case 4: case 6: case 9: case 11: {
		if (day == 30)
			if (month + 1 > 9) date = "01/" + to_string(month + 1) + '/' + to_string(year);
			else date = "01/0" + to_string(month + 1) + '/' + to_string(year);	
		else UsualTomorrow(date, day, month, year);
		break;
	}
	default: {
		if (day == 31)
			if (month + 1 > 9) date = "01/" + to_string(month + 1) + '/' + to_string(year);
			else date = "01/0" + to_string(month + 1) + '/' + to_string(year);
		else UsualTomorrow(date, day, month, year);
		break;
	}
	}
	return date;
}

//Ngay k truoc ngay nhap vao
string KDaysBefore(string date, int k) {
	if (k == 0) return date;
	int day = 0, month = 0, year = 0;
	StringToNum(date, day, month, year);
	if (k == 1) return Yesterday(day, month, year);
	return KDaysBefore(Yesterday(day, month, year), k-1);
}

//Ngay ke tiep ngay nhap vao
string KDaysAfter(string date, int k) {
	if (k == 0) return date;
	int day = 0, month = 0, year = 0;
	StringToNum(date, day, month, year);
	if (k == 1) return Tomorrow(day, month, year);
	return KDaysAfter(Tomorrow(day, month, year), k - 1);
}

//Thu trong tuan cua ngay nhap vao
string DayOfWeek(int day, int month, int year) {
	if (month == 1 || month == 2) {
		month = 12 + month;
		year--;
	}
	double temp = day + 2 * month + (3 * (month + 1) / 5.0) + year + (year / 4.0) - (year / 100.0) + (year / 400.0) + 2;
	int mod = int(temp) % 7;
	if (mod == 0) return "Thu Bay";
	else if (mod == 1) return "Chu Nhat";
	else if (mod == 2) return "Thu Hai";
	else if (mod == 3) return "Thu Ba";
	else if (mod == 4) return "Thu Tu";
	else if (mod == 5) return "Thu Nam";
	else if (mod == 6) return "Thu Sau";
	return "";
}

//Tuan trong nam cua ngay nhap vao
int WeekOfYear(string date, int year) {
	string StartDay = "01/01/" + to_string(year);
	int count = 1;
	while (StartDay != date) {
		StartDay = KDaysAfter(StartDay, 1);
		count++;
	}
	return ceil(count / 7.0);
}