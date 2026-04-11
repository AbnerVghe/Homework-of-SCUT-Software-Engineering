#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

class DateTime;

class Time{
	private:
		int hour, minute, second;

	public:
		Time(int _hour = 0, int _minute = 0, int _second = 0): hour(_hour), minute(_minute), second(_second){}

		void addTime(const int& t){
			second += t;
			while(second<0){
				second += 60;
				minute--;
			}
			int deltaMin = second / 60;
			second %= 60;
			
			minute += deltaMin;
			while(minute<0){
				minute += 60;
				hour--;
			}
			int deltaHour = minute / 60;
			minute %= 60;

			hour += deltaHour;
		}

		void flattenHour(){
			hour %= 24;
		}

		/*int getHour() const{
			return hour;
		}

		void setHour(const int& t){
			hour = t;
		}*/

		/*void printTime() const{
			if(1<=hour && hour<=9) cout << 0;
			cout << hour << ':';
			if(1<=minute && minute<=9) cout << 0;
			cout << minute << ':';
			if(1<=second && second<=9) cout << 0;
			cout << second;
			//cout << '\n';
		}*/
	friend class DateTime;
	friend ostream& operator<<(ostream&, const DateTime&);
};

const int daylmt[20] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Date{
	protected:
		int year, month, day, lmt;

		void calLmt(){
			if(month == 2){
				if(year%400==0 || (year%100!=0 && year%4==0)) lmt = 29;
				else lmt = 28; 
			}
			else lmt = daylmt[month];
		}

	public:
		Date(int _year = 0, int _month = 1, int _day = 1): year(_year), month(_month), day(_day){
			calLmt();
		}
		
		void addDay(const int& t){
			day += t;
			while(1){
				if(day < 1){
					month--;
					if(month < 1){
						month = 12;
						year--;
					}
					calLmt();
					day += lmt;
				}
				else if(day > lmt){
					day -= lmt;
					month++;
					if(month > 12){
						month = 1;
						year++;
					}
					calLmt();
				}
				else{
					break;
				}
				//if(1<=day || day<=lmt) break;
			}
		}

		/*void printDate() const{
			cout << year << '-';
			if(1<=month && month<=9) cout << 0;
			cout << month << '-';
			if(1<=day && day<=9) cout << 0;
			cout << day;
			//cout << '\n';
		}*/
};

class DateTime: public Date, public Time{
	public:
		DateTime(int _year = 0, int _month = 1, int _day = 1, int _hour = 0, int _minute = 0, int _second = 0): Date(_year, _month, _day), Time(_hour, _minute, _second){}

		/*DateTime operator + (const int& t){
			helpIncrement(t);
			return *this;
		}*/

		DateTime& operator += (const int& t){
			helpIncrement(t);
			return *this;
		}

		void helpIncrement(const int& t){
			addTime(t);
			int deltaDay = 0;
			while(1){
				if(hour<0){
					hour += 24;
					deltaDay--;
				}
				else if(hour>=24){
					hour -= 24;
					deltaDay++;
				}
				else break;
			}
			addDay(deltaDay);
		}

		friend ostream& operator << (ostream&, const DateTime&);
};

ostream& operator << (ostream& output, const DateTime& D){
	output << D.year << '-';
	if(1<=D.month && D.month<=9) output << 0;
	output << D.month << '-';
	if(1<=D.day && D.day<=9) output << 0;
	output << D.day;

	output << ' ';
	
	if(0<=D.hour && D.hour<=9) output << 0;
	output << D.hour << ':';
	if(0<=D.minute && D.minute<=9) output << 0;
	output << D.minute << ':';
	if(0<=D.second && D.second<=9) output << 0;
	output << D.second;

	return output;
}

class MyInput{
    public:
        string data[10];

        MyInput(string line, int t){
            int j = 0;
            for(int i = 0; i < t; i++){
                data[i] = "";
                while(j < line.length() && line[j] != ',' && line[j] != 0){
                    if(line[j] == ' ') break;
                    data[i] += line[j];
                    j++;
                }
                if(j < line.length()) j++;
            }
        }

        string getData(int index) const{
            return data[index];
        }

		string operator [](int index) const{
			return data[index];
		}
};

int turnToNum(string str){
    int i = 0, sign = 1;
    if(str[i] == '-'){
        sign = -1;
        i++;
    }

    int ans = 0;
    while(str[i] != '.' && i < str.length()){
        ans *= 10;
        ans += str[i] - '0';
        i++;
    }
    i++;
    double j = 0.1;
    while(i < str.length()){
        ans += j*(str[i] - '0');
        j /= 10;
        i++;
    }

    return ans*sign;
}

signed main(){
	//ios::sync_with_stdio(0);
	//cin.tie(0); cout.tie(0);
	
	string line;
	getline(cin, line);
	MyInput IN(line, 6);
	int a[10];
	foreach(0, 5, i){
		if(IN[i] != "") a[i+1] = turnToNum(IN[i]);
		else a[i+1] = 0;
	}
	DateTime D(a[1], a[2], a[3], a[4], a[5], a[6]);
	string str;
	cin >> str;
	int num = turnToNum(str);
	D += num;
	cout << D << endl;
}