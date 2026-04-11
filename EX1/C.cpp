#include<bits/stdc++.h>
using namespace std;

class Rational{
    private:
        long long numerator, denominator; 
    public:
        Rational(long long _numerator = 1, long long _denominator = 1){ 
            numerator = _numerator;
            denominator = _denominator;
            reduce();
        }

        void reduce(){
            if(denominator == 0) return;

            if (denominator < 0) {
                numerator = -numerator;
                denominator = -denominator;
            }

            long long gcd = __gcd(numerator, denominator); 
            if (gcd != 0) {
                numerator /= gcd;
                denominator /= gcd;
            }
        }

        void add(long long a, long long b){ 
            long long n = numerator*b + denominator*a; 
            long long d = denominator*b;
            numerator = n;
            denominator = d;
            reduce();
        }

        void sub(long long a, long long b){
            long long n = numerator*b - denominator*a;
            long long d = denominator*b;
            numerator = n;
            denominator = d;
            reduce();
        }

        void mul(long long a, long long b){
            numerator *= a;
            denominator *= b;
            reduce();
        }

        void div(long long a, long long b){
            numerator *= b;
            denominator *= a;
            reduce();
        }

        void disPlay(){
            reduce();
            cout << numerator;
            if(denominator != 1){
                cout << '/' << denominator;
            }
            cout << '\n';
        }
};

class MyInput{
    public:
        string data[10];

        MyInput(string line, int t){
            int j = 0;
            for(int i = 0; i <= t; i++){
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
};

template<typename T>
void turnToNum(T &num, string str){
    int i = 0, sign = 1;
    if(str[i] == '-'){
        sign = -1;
        i++;
    }

    T ans = 0;
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

    num = ans*sign;
}

signed main(){
    string line;
    getline(cin, line);
    MyInput IN(line, 2);
    long long a, b;  
    turnToNum(a, IN.getData(0));
    turnToNum(b, IN.getData(1));
    if(b == 0) return 0;
    Rational rtn(a, b);
    while(getline(cin, line)){
        if(line.length() == 0) break;

        MyInput IN(line, 3);
        string opt = IN.getData(0);
        long long c, d;  
        turnToNum(c, IN.getData(1));
        turnToNum(d, IN.getData(2));
        
        if(d == 0) continue;

        if(opt == "add") rtn.add(c, d);
        else if(opt == "sub") rtn.sub(c, d); 
        else if(opt == "mul") rtn.mul(c, d); 
        else if(opt == "div" && c != 0){
            rtn.div(c, d);
        } 
    }
    rtn.disPlay();
}