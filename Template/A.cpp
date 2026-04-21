#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

template<class T1, class T2>
class Pair{
    public:
        T1 key;
        T2 value;
        
        Pair(T1 _key): key(_key), value(-1){}
        
        Pair(T1 _key, T2 _value):key(_key), value(_value){}
        
        bool operator < (const Pair &x) const{
            return value < x.value;
        }

        void print() const{
            cout << key << ':' << value << '\n';
        }

        Pair(Pair &x): key(x.key), value(x.value){}
};

bool is_num(string s){
    for(auto c: s){
        if(c < '0' || c > '9') return 0;
    }
    return 1;
}

template<class T>
T turnToNum(string str){
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

    return ans*sign;
}

signed main(){
    string key, value;
    Pair<string, int> type1("Def");
    Pair<string, double> type2("Def");
    while(getline(cin, key, ',')){
        if(!key.length()) break;
        getline(cin, value);
        if(is_num(key)){
            int val = turnToNum<int>(value);
            Pair<string, int> tmp(key, val);
            if(type1 < tmp) type1 = tmp;
        }
        else{
            double val = turnToNum<double>(value);
            Pair<string, double> tmp(key, val);
            if(type2 < tmp) type2 = tmp;
        }
    }
    type1.print();
    type2.print();
}