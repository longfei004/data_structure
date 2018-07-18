#include <iostream>
#include <vector>
using namespace std;


int main()
{
	int n;
	vector<int> a;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		a.push_back(temp);
	}
	bool flag = false;
	int start;
	for (auto it = a.begin() + 1; it != a.end(); it++)
	{
		if (*(it) < *(it - 1) && flag == false)
		{
			start = *(it - 1);
			while (*(it) < *(it - 1))
				it++;
			flag = true;
		}
		if (start > *it)
			flag = false;
		if (*(it) < *(it - 1) && flag == true)
		{
			flag = false;
			break;
		}
	}
	if (flag == true)
		cout << "yes" << endl;
	else
		cout << "no"<< endl;

	return 0;
}