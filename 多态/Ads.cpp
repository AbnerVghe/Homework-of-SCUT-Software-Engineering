#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;

class MyInput
{
private:
	string data[10];
	int j = 0;

public:
	MyInput(string& in)
	{
		string temp = "";
		for (size_t i = 0;i < in.size();i++)
		{
			if (in[i] == ',')
			{
				data[j++] = temp;
				temp = "";
			}
			else
				temp = temp + in[i];
		}
		data[j] = temp;
	}
	string operator[](int index)
	{
		if (index > j) return "0";
		return data[index];
	}
};

class CShape
{
private:
	string name;
public:
	CShape(string _name = "")
	{
		name = _name;
	}
	string Getname()
	{
		return name;
	}
	virtual double Area() = 0;
	virtual bool IsShape() = 0;
	virtual int Getid() = 0;
	virtual ~CShape() {};
};

class CCircle :public CShape
{
private:
	double radius;
	static unsigned int count1;
	unsigned int id;

public:
	CCircle(string _name = "", double _r = 0) :CShape(_name), radius(_r)
	{
		count1++;
		id = count1;
	}
	bool IsShape()override
	{
		return radius > 0;
	}
	double Area()override
	{
		return 3.1416 * radius * radius;
	}
	static int Getcount1()
	{
		return count1;
	}
	int Getid()override
	{
		return id;
	}
	~CCircle()override  //因为main中是创建完对象(count++)再通过IsShape()判断是否为有效数据，若无效则删除
	{                   //若delete(析构)后count的值不--，则会导致id错误  下面三角形，矩形同理
		count1--;
	}
};
unsigned int CCircle::count1 = 0;

class CTriangle :public CShape
{
private:
	double s1;
	double s2;
	double s3;
	static unsigned int count2;
	unsigned int id;

public:
	CTriangle(string _name = "", double _s1 = 0, double _s2 = 0, double _s3 = 0) 
		:CShape(_name), s1(_s1), s2(_s2), s3(_s3)
	{
		count2++;
		id = count2;
	}
	bool IsShape()override
	{
		return ( (s1 + s2) > s3)&&( (s2 + s3) > s1) && ( (s3 + s1) > s2 ) 
			&& (s1 > 0 && s2 > 0 && s3 > 0);
	}
	double Area()override
	{
		if (IsShape() == true)
		{
			double p = (s1 + s2 + s3) / 2;
			double area = p * (p - s1) * (p - s2) * (p - s3);
			return sqrt(area);
		}
		else
		{
			return 0;
		}
	}
	static int Getcount2()
	{
		return count2;
	}
	int Getid()override
	{
		return id;
	}
	~CTriangle()override
	{
		count2--;
	}
};
unsigned int CTriangle::count2 = 0;

class CRectangle :public CShape
{
private:
	double s1;
	double s2;
	static unsigned int count3;
	unsigned int id;

public:
	CRectangle(string _name = "", double _s1 = 0, double _s2 = 0) :CShape(_name), s1(_s1), s2(_s2)
	{
		count3++;
		id = count3;
	}
	bool IsShape()override
	{
		return s1 > 0 && s2 > 0;
	}
	double Area()override
	{
		return s1 * s2;
	}
	static int Getcount3()
	{
		return count3;
	}
	int Getid()override
	{
		return id;
	}
	~CRectangle()override
	{
		count3--;
	}
};
unsigned int CRectangle::count3 = 0;

int main()
{
	vector<CShape*>v;
	string line;
	while (getline(cin, line))
	{
		if (line.empty())
		{
			continue;
		}
		MyInput in(line);
		if (in[0] == "Circle")
		{
			CCircle* circle = new CCircle(in[0],stod(in[1]));
			if (circle->IsShape())
			{
				v.push_back(circle);
			}
			else
			{
				delete circle;
			}
		}
		else if (in[0] == "Triangle")
		{
			CTriangle* triangle = new CTriangle(in[0], stod(in[1]),stod(in[2]),stod(in[3]));
			if (triangle->IsShape())
			{
				v.push_back(triangle);
			}
			else
			{
				delete triangle;
			}
		}
		else if (in[0] == "Rectangle")
		{
			CRectangle* rectangle = new CRectangle(in[0], stod(in[1]),stod(in[2]));
			if (rectangle->IsShape())
			{
				v.push_back(rectangle);
			}
			else
			{
				delete rectangle;
			}
		}
		else
		{
			continue;
		}
	}

	vector<double>a;//其实最后一个的面积就是对应最晚出现的最大面积
	for (CShape* t : v)
	{
		a.push_back(t->Area());
	}
	size_t n = a.size();
	for (size_t i = 0; i < n - 1; i++)
	{
		for (size_t j = 0; j < n - i - 1; j++) //升序
		{
			if (a[j] > a[j + 1]) 
			{
				double temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}

	double mid;
	if (n % 2 == 1)
	{
		mid = a[n / 2];
	}
	else
	{
		mid = (a[(n / 2) - 1] + a[n / 2]) / 2;
	}
	
	double maxArea = -1;
	unsigned int id = 0;
	string name = "";
	for (CShape* t : v)
	{
		double Area = t->Area();
		if (Area >= maxArea)
		{
			maxArea = Area;
			name = t->Getname();
			id = t->Getid();
		}
	}

	cout << fixed << setprecision(2) << mid << endl 
		 << name << id << endl;

	for (CShape* t : v)
	{
		delete t;
	}

	return 0;
}