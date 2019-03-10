#include <iostream>

using namespace std;


char str[10];


void func(int x)
{
	int i = 0;
	int l = -90;
	int r = 90;
	int m = 0;
    char c;

	for(i = 0; i < 6; ++i){
		if(x >= m){
		    c = '1';
			l = m;
		}else{
		    c = '0';
			r = m;
		}

		str[i] = c;
		m = ( l + r ) / 2;
	}

	str[6] = '\0';
}


int main()
{
	int a;
	cin >> a;
	func(a);
	cout << str <<endl;

	return 0;
}