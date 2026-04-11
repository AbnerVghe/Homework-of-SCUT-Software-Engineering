#include<bits/stdc++.h>
using namespace std;

class Complex{
    private:
        double realPart, imaginaryPart;
    public:
        Complex(double _realPart = 0, double _imaginaryPart = 0){
            realPart = _realPart;
            imaginaryPart = _imaginaryPart;
        }

        void disPlay() const{
            cout << fixed << setprecision(2);
            cout << '(' << realPart << ',' << imaginaryPart << ')';
        }

        void add(double a, double b){
            realPart += a;
            imaginaryPart += b;
        }

        void mul(double a, double b){
            double r = realPart*a - imaginaryPart*b;
            double i = realPart*b + imaginaryPart*a;
            realPart = r, imaginaryPart = i;
        }

        void div(double a, double b){
            double p = a*a + b*b;
            double r = (realPart*a + imaginaryPart*b) / p;
            double i = (a*imaginaryPart - b*realPart) / p;
            realPart = r, imaginaryPart = i;
        }

        void sub(double a, double b){
            realPart -= a;
            imaginaryPart -= b;
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
void turnToNum(T &_num, string str){
    int i = 0, sign = 1;
    if(str[0] == '-'){
        i++;
        sign = -1;
    }
    T num = 0;
    for(; i < str.length() && str[i] != '.'; i++){
        num *= 10;
        num += str[i] - '0';
    }

    if (i < str.length() && str[i] == '.') {
        i++;
        double j = 0.1;
        while (i < str.length()) {
            num += j * (str[i] - '0');
            j /= 10;
            i++;
        }
    }
    _num = num * sign;
}

int main(){
    string line;
    getline(cin, line);
    MyInput IN(line, 2);
    double a, b;
    turnToNum(a, IN.getData(0));
    turnToNum(b, IN.getData(1));
    Complex com(a, b);
    while(getline(cin, line)){
        if(line.length() == 0) break;

        MyInput IN(line, 3);
        string opt = IN.getData(0);
        double c, d;
        turnToNum(c, IN.getData(1));
        turnToNum(d, IN.getData(2));
        //cout << c << ' ' << d << '\n';
        if(opt == "add") com.add(c, d);
        else if(opt == "sub") com.sub(c, d); 
        else if(opt == "mul") com.mul(c, d); 
        else if(opt == "div") com.div(c, d); 
    }
    com.disPlay();
    
    
}
