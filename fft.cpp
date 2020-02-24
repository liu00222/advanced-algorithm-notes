#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;
#define pi 3.1415926535 
#define nn 8
struct  Complex
{
	double real;
	double imag;
	int num;
	Complex(int i=0,int j=0){real=i,imag=j;}
};
Complex q(1,0);
Complex operator+ (Complex const & lhs, Complex const & rhs)
{
	Complex temp;
	temp.real =lhs.real+rhs.real;
	temp.imag = lhs.imag+ rhs.imag;
	return temp;
}
Complex operator- (Complex const & lhs, Complex const & rhs)
{
	Complex temp;
	temp.real = lhs.real - rhs.real;
	temp.imag = lhs.imag - rhs.imag;
	return temp;
}
Complex operator* (Complex const & lhs, Complex const & rhs)
{
	Complex temp;
	temp.real = lhs.real * rhs.real - lhs.imag * rhs.imag;
	temp.imag= lhs.real * rhs.imag + lhs.imag * rhs.real;
	return temp;
}
Complex operator* ( const int &lhs, Complex const & rhs)
{
	Complex temp;
	temp.real=lhs*rhs.real;
	temp.imag=lhs*rhs.imag;
	return temp;
}
vector<Complex> operator* (vector<Complex>const&a,vector<Complex>const&b)
{
	Complex y;
    vector<Complex> temp(a.size(),y);
    for (size_t i=0;i<a.size();i++)
    {
		temp[i]=a[i]*b[i];
    }
	return temp;
}
Complex operator/(Complex &a,double b)
{
   Complex temp;
   temp.real=a.real/b;
   temp.imag=a.imag/b;
   return temp;
}
vector<Complex> operator/(vector<Complex>&a,double b)
{
	vector<Complex>temp(a.size(),0);
    for (size_t i=0;i<a.size();i++)
    {
		temp[i]=a[i]/b;
    }
	return temp;
}
istream &operator>>(istream&is, Complex &item)
{
	is >> item.real>>item.imag;
	return is;
}
vector<Complex> recursive_FFT(vector<Complex> const&a)
{
	size_t n = a.size();
	if (n == 1) return a;
	struct  Complex wn, w;
	wn.real = cos(2 * pi / n), wn.imag = sin(2 * pi / n);
	w.real = 1, w.imag = 0;
	vector<Complex>a0, a1;
	a0.reserve(n / 2);
	a1.reserve(n / 2);
	for (int i = 0; i<n / 2; i++)
	{
		a0.push_back(a[i * 2]);
		a1.push_back(a[i * 2 + 1]);
	}
	vector<Complex>y0 = recursive_FFT(a0);
	vector<Complex>y1 = recursive_FFT(a1);
	vector<Complex>y;
	y.resize(n);
	for (int k = 0; k<n / 2; k++)
	{
		y[k] = y0[k] + w*y1[k]; 
		y[k + n / 2] = y0[k] - w*y1[k];
		w = w*wn;
	}
	return y;
}
vector<Complex> recursive_FFT_opposite(vector<Complex> const&a)
{
	size_t n = a.size();
	if (n == 1) 
	{
		return a;
	}
	struct  Complex wn, w;
	wn.real = cos(-2 * pi / n), wn.imag = sin(-2 * pi / n);
	w.real = 1, w.imag = 0;
	vector<Complex>a0, a1;
	a0.reserve(n / 2);
	a1.reserve(n / 2);
	for (int i = 0; i<n / 2; i++)
	{
		a0.push_back(a[i * 2]);
		a1.push_back(a[i * 2 + 1]);
	}
	vector<Complex>y0 = recursive_FFT_opposite(a0);
	vector<Complex>y1 = recursive_FFT_opposite(a1);
	vector<Complex>y;
	y.resize(n);
	for (int k = 0; k<n / 2; k++)
	{
		y[k] = y0[k] + w*y1[k];
		y[k + n / 2] = y0[k] - w*y1[k];
		w = w*wn;
	}
	return y;
}
vector<Complex> Polynomial_multiplication(vector<Complex> &a,vector<Complex> &b)
{
	Complex y;
	int i=0;
	int t=a.size();
	while (i!=t)
	{
		a.push_back(y);
		b.push_back(y);
		i++;
	}
	vector<Complex>ya=recursive_FFT(a);
	vector<Complex>yb=recursive_FFT(b);
	vector<Complex>yc=ya*yb;
	vector<Complex>temp=recursive_FFT_opposite(yc);
	return temp;
}
vector<Complex> Polynomial_0(vector<Complex> const&a)
{
   size_t n=a.size();
   if (n==2)
   {
	   Complex y1(1,0),y2(a[1].real+a[0].real,0),y3(a[1].real*a[0].real,0),y4;
	   vector<Complex>yy(4,y4);
	   yy[0]=y1;
	   yy[1]=y2;
	   yy[2]=y3;
	   return yy;
   }
   vector<Complex>a0, a1;
   a0.reserve(n / 2);
   a1.reserve(n / 2);
   for (int i = 0; i<n / 2; i++)
   {
	   a0.push_back(a[i ]);
	   a1.push_back(a[i +n/2]);
   }
   vector<Complex>y0=Polynomial_0(a0);
   vector<Complex>y1=Polynomial_0(a1);
   vector<Complex>y;
   y.resize(n);
   y=Polynomial_multiplication(y0,y1);
   y=y/(2*n);
   return y;
}
void main()
{
	vector<Complex>a;
	cout << "Enter the coefficients of the polynomial (including 0):";
	int  k1 = 0,k2=0;
	Complex i;
	while (k1 != nn&&cin >> i)
	{
		a.push_back(i);
		k1++;
	}
	while (--k1)
	{
		if (a[k1].real!=0||a[k1].imag!=0)
		{
			break;
		}
		k1--;
	}
	vector<Complex>y = Polynomial_0(a);
	for (int t = 0; t<=k1+1; t++)
	{
		printf("%g ", y[t].real);
		if (fabs(y[t].imag) < 0.001)
		{
			cout << endl;
			continue;
		}
		else
		{
			if (y[t].imag<0) printf("%gi", y[t].imag);
			else printf("+%gi", y[t].imag);
		}
		cout << endl;
	}
