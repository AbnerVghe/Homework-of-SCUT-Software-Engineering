#include<bits/stdc++.h>
#define double long double
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f
#define Pi 3.1416

const double eqs = 1e-10;

class CShape{
public:
	string name;
	int num;

	CShape(string _name = ""): name(_name){};
	virtual ~CShape(){};

	virtual double Area() = 0;
	virtual bool IsShape() = 0;
};

class CCircle: public CShape{
private:
	double radius;
	static int cnt;
public:
	CCircle(string _name = "", double _radius = 0): CShape(_name), radius(_radius){
		if(IsShape()) num = ++cnt;
	};

	~CCircle(){};
	
	double Area() override{
		return Pi * radius * radius;
	}

	bool IsShape() override{
		return radius >= eqs;
	}
};

class CTriangle: public CShape{
private:
	double edge[3];
	static int cnt;
public:
	CTriangle(string _name = "", double edge1 = 0, double edge2 = 0, double edge3 = 0): CShape(_name){
		edge[0] = edge1, edge[1] = edge2, edge[2] = edge3;
		sort(edge, edge+3);

		if(IsShape()) num = ++cnt;
	}

	~CTriangle(){};

	double Area() override{
		if(!IsShape()) return 0;

		double p = (edge[0]+edge[1]+edge[2]) / 2;
		double S = sqrt(p * (p-edge[0]) * (p-edge[1]) * (p-edge[2]));
		return S;
	}

	bool IsShape() override{
		foreach(0, 2, i){
			if(edge[i] < eqs) return 0;
		}

		return edge[0]+edge[1]>edge[2];
	}
};

class CRectangle: public CShape{
private:
	double lon, wid;
	static int cnt;
public:
	CRectangle(string _name = "", double _lon = 0, double _wid = 0): CShape(_name), lon(_lon), wid(_wid){
		if(IsShape()) num = ++cnt;
	};

	~CRectangle(){};

	double Area() override{
		return lon * wid;
	}

	bool IsShape() override{
		return lon >= eqs && wid >= eqs;
	}
};

class MyInput{
    public:
        string data[10];
		int dataCnt = 0;

        MyInput(string line, int t){
            int j = 0;
            for(int i = 0; i < t; i++){
				if(j < line.length()) dataCnt++;
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

double turnToNum(string str){
    int i = 0, sign = 1;
    if(str[i] == '-'){
        sign = -1;
        i++;
    }

    double ans = 0;
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

int CCircle::cnt = 0;
int CTriangle::cnt = 0;
int CRectangle::cnt = 0;

bool cmp(CShape *p1, CShape *p2){
	return p1->Area() < p2->Area();
}

signed main(){
	string line;
	vector<CShape *> p;

	while(getline(cin, line)){
		if(!line.length()) break;

		MyInput IN(line, 6);
		//cout << IN.dataCnt << '\n';
		string name = IN[0];
		
		if(name == "Circle" && IN.dataCnt >= 2){
			CCircle* t = new CCircle(name, turnToNum(IN[1]));
			if(t->IsShape()) p.push_back(t);
			else delete t;
		}
		else if(name == "Triangle" && IN.dataCnt >= 4){
			CTriangle* t = new CTriangle(name, turnToNum(IN[1]), turnToNum(IN[2]), turnToNum(IN[3]));
			if(t->IsShape()) p.push_back(t);
			else delete t;
		}
		else if(name == "Rectangle" && IN.dataCnt >= 3){
			CRectangle* t = new CRectangle(name, turnToNum(IN[1]), turnToNum(IN[2]));
			if(t->IsShape()) p.push_back(t);
			else delete t;
		}

	}

	if (p.size() == 0) return 0;

	double maxn = p[0]->Area();
	int id = 0;
	foreach(1, p.size()-1, i){
		double area = p[i]->Area();
		if(area > maxn) maxn = area, id = i;
		else if(fabs(area - maxn) < eqs) id = i;
	}
	CShape *p3 = p[id];
	//cout << '\n';
	string ans = p3->name + to_string(p3->num);
	
	sort(p.begin(), p.end(), cmp);
	
	//cout << fixed << setprecision(2);
	//foreach(1, cnt, i) cout << p[i]->Area() << ' ';
	//cout << '\n';

	int i1 = (p.size()-1)/2, i2 = p.size()/2;
	CShape *p1 = p[i1], *p2 = p[i2];
	cout << fixed << setprecision(2) << (p1->Area() + p2->Area()) / 2 << '\n';
	cout << ans << '\n';	

	foreach(0, p.size()-1, i) delete p[i];
}