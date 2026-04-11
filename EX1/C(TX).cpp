#include <iostream>
#include <string>
using namespace std;

class Fraction{
    private:
        long numerator, denominator;
    public:
        Fraction(long n=0, long d=0): numerator(n), denominator(d){}

        void add(const Fraction &other){
            numerator=numerator*other.denominator+denominator*other.numerator;
            denominator*=other.denominator;
        }
        void subtract(const Fraction &other){
            numerator=numerator*other.denominator-denominator*other.numerator;
            denominator*=other.denominator;
        }
        void multiply(const Fraction &other){
            numerator*=other.numerator;
            denominator*=other.denominator;
        }
        void divide(const Fraction &other){
            numerator*=other.denominator;
            denominator*=other.numerator;
        }
        long gcd(long a, long b){
            a=abs(numerator);
            b=abs(denominator);
            while(b!=0){
                int temp=b;
                b=a%b;
                a=temp;
            }
            return a;
        }
        void simplify(){
            if(denominator==0) return;
            int divisor=gcd(numerator,denominator);
            numerator/=divisor;
            denominator/=divisor;

            if(denominator<0){
                numerator=-numerator;
                denominator=-denominator;
            }
        }
        void print(){
            cout<<numerator;
            if(denominator!=1){
                cout<<"/"<<denominator<<endl;
            }
        }
};

int main(){
    long n,d;
    char comma;

    if(cin>>n>>comma>>d){
        Fraction res(n,d);
        res.simplify();

        string op;
        while(cin>>ws && getline(cin,op,',')){
            long opN,opD;
            if(cin>>opN>>comma>>opD){
                Fraction other(opN,opD);
                if(op=="add") res.add(other), res.simplify();
				else if(op=="sub") res.subtract(other), res.simplify();
				else if(op=="mul") res.multiply(other), res.simplify();
				else if(op=="div") res.divide(other), res.simplify();
            }
        }
        res.simplify();
        res.print();
    }
    return 0;
}