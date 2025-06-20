#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define DEBUG 1
#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

void GetAllSubsets(vector<int> set, vector<int> subset, int index,
	vector<vector<vector<int>>>& allSubsets)
{
	if (index == set.size())
	{
		allSubsets[subset.size()].push_back(subset);
		return;
	}

	GetAllSubsets(set, subset, index + 1, allSubsets);

	subset.push_back(set[index]);
	GetAllSubsets(set, subset, index + 1, allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set, int target)
{
	vector<vector<vector<int>>> allSubsets(set.size() + 1);

	GetAllSubsets(set, {}, 0, allSubsets);

	for (int size = 0; size <= set.size(); size++)
	{
		PRINT("부분집합의 원소 개수: " << size << endl);

		for (auto subset : allSubsets[size])
		{
			PRINT("\t{ ");

			int sum = 0;
			for (auto number : subset)
			{
				sum += number;
				PRINT(number << " ");
			}

			PRINT("} = " << sum << endl);

			if (sum == target)
				return true;
		}
	}

	return false;
}

int main()
{
	vector<int> set = { 13, 79, 45, 29 };
	int target = 100000;

	bool found = SubsetSum_BruteForce(set, target);

	if (found)
	{
		cout << "원소 합이 " << target << "인 부분집합이 있습니다." << endl;
	}
	else
	{
		cout << "원소 합이" << target << "인 부분집합이 없습니다." << endl;
	}
}