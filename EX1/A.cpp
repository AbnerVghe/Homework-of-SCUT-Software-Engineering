#include<bits/stdc++.h>
using namespace std;

class Book{
    private:
        string BookName;
        string BarCode;
        int Number;
        double Price;
    public:
        explicit Book(string _BookName = "", string _BarCode = "", int _Number = 0, double _Price = 0)
        : BookName(_BookName), BarCode(_BarCode), Number(_Number), Price(_Price)
        {
        }

        void Display() const{
            cout << BookName << ':' << Number << '\n';
        }

        string getBarCode() const{
            return BarCode;
        }

        void Borrow(int num){
            if(num <= Number){
                Number -= num;
            }
        }

        void Restore(int num){
            Number += num;
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
    int i;
    T num = 0;
    for(i = 0; i < str.length() && str[i] != '.'; i++){
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
    _num = num;
}

int main(){
    int n;
    cin >> n;
    cin.ignore();
    vector<Book> Books(n);
    string line;
    for(int i = 0; i < n; i++){
        getline(cin, line);
        MyInput IN(line, 4);
        
        string BookName = IN.getData(0), BarCode = IN.getData(1);
        int Number;
        turnToNum(Number, IN.getData(2));
        double Price;
        turnToNum(Price, IN.getData(3));
        Book tmpBook(BookName, BarCode, Number, Price);
        Books[i] = tmpBook;
    }
    
    while(getline(cin, line)){
        if(line.length() == 0) break;//读到空行退出
        MyInput IN(line, 3);
        int aimIndex = -1;
        for(int i = 0; i < n; i++){
            if(IN.getData(1) == Books[i].getBarCode()){
                aimIndex = i;
                break;
            }
        }
        if(aimIndex == -1) continue;

        Book &aimBook = Books[aimIndex];
        int num;
        turnToNum(num, IN.getData(2));
        string str = IN.getData(2);
        
        if(IN.getData(0) == "borrow"){
            aimBook.Borrow(num);
        }
        else if(IN.getData(0) == "restore"){
            aimBook.Restore(num);
        }
    }
    for(int i = 0; i < n; i++){
        Books[i].Display();
    }
    
}
