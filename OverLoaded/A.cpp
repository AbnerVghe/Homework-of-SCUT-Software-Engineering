#include<bits/stdc++.h>
using namespace std;

class Rational{
    private:
        long long numerator, denominator; 
    public:
        Rational(long long _numerator = 0, long long _denominator = 1){ 
            numerator = _numerator;
            denominator = _denominator;
            reduce();
        }

        void reduce(){
            if(numerator == 0) denominator = 1;
            //if(denominator == 0) return;

            if (denominator < 0) {
                numerator = -numerator;
                denominator = -denominator;
            }

            long long gcd = __gcd(abs(numerator), abs(denominator)); 
            if (gcd != 0) {
                numerator /= gcd;
                denominator /= gcd;
            }

            if (denominator < 0) {
                numerator = -numerator;
                denominator = -denominator;
            }
        }

        void disPlay(){
            reduce();
            cout << numerator;
            if(denominator != 1){
                cout << '/' << denominator;
            }
            cout << '\n';
        }

        Rational operator + (const Rational& a){
            Rational res;
            res.numerator = numerator*a.denominator + denominator*a.numerator;
            res.denominator = a.denominator*denominator;
            res.reduce();
            return res;
        }

        Rational operator - (const Rational& a){
            Rational res;
            res.numerator = numerator*a.denominator - denominator*a.numerator;
            res.denominator = a.denominator*denominator;
            res.reduce();
            return res;
        }

        friend Rational operator * (const Rational&, const Rational&); 
        friend Rational operator / (const Rational&, const Rational&);
        friend ostream &operator << (ostream &, const Rational&);
};

ostream &operator << (ostream& output, const Rational& x){
    output << x.numerator;
    if(x.denominator != 1){
        output << '/' << x.denominator;
    }       
    return output; 
}

Rational operator * (const Rational& a, const Rational& b){
    Rational res;
    res.numerator = a.numerator*b.numerator;
    res.denominator = a.denominator*b.denominator;
    res.reduce();
    return res;
}

Rational operator / (const Rational& a, const Rational& b){
    Rational res;
    res.numerator = a.numerator*b.denominator;
    res.denominator = a.denominator*b.numerator;
    res.reduce();
    return res;
}



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
        
        //if(d == 0) continue;

        Rational tmp(c, d);

        if(opt == "add") rtn = rtn + tmp;
        else if(opt == "sub") rtn = rtn - tmp;
        else if(opt == "mul") rtn = rtn * tmp;
        else if(opt == "div" && c != 0){
            rtn = rtn / tmp;
        } 
    }
    cout << rtn << '\n';
}