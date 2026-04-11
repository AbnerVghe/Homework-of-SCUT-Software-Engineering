#include<bits/stdc++.h>
using namespace std;

class MyString{
    private:
        char *p;
    public:
        MyString(){
            p = new char[100];
            p[0] = 0;
        };

        MyString(const char *p){
            this->p = new char[100];
            strcpy(this->p, p);
        }

        MyString(const MyString &x){
            p = new char[100];
            strcpy(p, x.p);
        }

        ~MyString(){
            delete[] p;
        }

        void SetNewString(const char *x){
            strcpy(p, x);
        }

        MyString& operator = (const MyString& x){
            delete[] p;

            p = new char[100];
            strcpy(p, x.p);

            return *this;
        }

        MyString operator + (const MyString& x){
            MyString tmp(p);
            strcat(tmp.p, x.p);
            return tmp;
        }

        friend ostream& operator << (ostream&, const MyString&);
};

ostream& operator << (ostream& output,const MyString& x){
    output << x.p;
    return output;
}

signed main(){
    MyString s1("First"), s2("Second");
    MyString s3=s1;
    MyString s4;
    s4=s2;

    s3.SetNewString("long string");
    s4.SetNewString("scut");

    cout<<s1<<"  "<<s3<<endl;   //s1,s3应该显示不一样的内容
    cout<<s2<<"  "<<s4<<endl;   //s2,s4应该显示不一样的内容

    MyString s5=s3+s4;
    cout<<s5<<endl;  //应该显示s3,s4合并在一起的内容
}