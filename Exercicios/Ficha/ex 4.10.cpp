#include <iostream>
#include <vector>
using namespace std;

void removeDuplicates(vector<int> &v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		int number = v[i];
		int counter = 0;

		for (size_t a = 0; a < v.size(); a++)
		{
			if (v.at(a) == number)
				counter++;

			if (v.at(a) == number && counter > 1)
			{
				if (a + 1 >= v.size())
					v.resize(v.size() - 1);
				else
				{
					for (size_t b = a; b < v.size() - 1; b++)
					{
						v.at(b) = v.at(b + 1);
					}
					v.resize(v.size() - 1);
				}
				counter = 1;
			}
		}
	}
}

int main()
{
	vector<int> vec = { 1,2,2,2,2,1,3,2,5,5,5,5,4,3,1,8,7,9,5 };

	removeDuplicates(vec);

	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << ",";

	}
	cout << endl;

}