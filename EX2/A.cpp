#include<bits/stdc++.h>
#define double long double
using namespace std;

const double eqs = 1e-8;

bool is_equal(const double& a, const double& b){
    return fabs(a-b) < eqs;
}

class MyInput{
    private:
        string data[10];
    public:
        explicit MyInput(string line){
            string tmp = "";
            for(int i = 0, j = 0; i <= line.length(); i++){
                if(line[i] != ',' && i != line.length()){
                    tmp += line[i];
                }
                else{
                    data[j++] = tmp;
                    tmp = "";
                }
            }
        }

        string GetInput(const int &index) const{
            return data[index];
        }

};

template<typename T>
void TurnToNum(T &num, string str){
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

class Point{
    private:
        double x, y;
        friend class Quadrilateral;
    public:
        explicit Point(const double& x = 0, const double& y = 0){
            this->x = x;
            this->y = y;
        }
};

class Quadrilateral{
    private:
        Point p[4];
        double line[4];
    public:
        Quadrilateral(){};

        void insPoint(const double& x, const double& y, const int& index){
            p[index].x = x;
            p[index].y = y;
        }

        double cal(Point p1, Point p2) const{
            const double x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
            return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
        }

        void formLines(){
            for(int i = 0; i < 4; i++){
                line[i] = cal(p[i], p[(i+1)%4]);
            }
        }

        bool is_valid() const{
            if(is_equal(line[0], line[2])+is_equal(line[1], line[3]) != 2){
                //cout << "ERR1\n";
                return 0;
            }
            if(!is_equal(cal(p[0], p[2]), cal(p[1], p[3]))){
                //cout << "ERR2\n";
                return 0;
            }    
            for(int i = 0; i < 4; i++){
                if(is_equal(0, line[i])){
                    /*cout << "ERR3\n";
                    cout << i << '<-line\n';*/
                    return 0;
                } 
                
            }

            return 1;
        }

        void area() const{
            if(is_valid()){
                cout << fixed << setprecision(4) << line[0]*line[1];
            }
            else cout << 0;
            cout << '\n';
        }
};

int main(){
    string str;

    /*Quadrilateral test;
    test.insPoint(1, 0, 0);
    test.insPoint(0, 1, 1);
    test.insPoint(-1, 0, 2);
    test.insPoint(0, -1, 3);
    test.formLines();
    cout <<  test.area() << '\n';*/

    while(getline(cin, str)){
        if(str.length() == 0) break;
        MyInput IN(str);
        Quadrilateral Q;
        for(int i = 0; i < 4; i++){
            double x, y;
            TurnToNum(x, IN.GetInput(2*i)), TurnToNum(y, IN.GetInput(2*i+1));
            Q.insPoint(x, y, i);
        }
        Q.formLines();
        Q.area();
    }
}