#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//int Knapsack_01(int items, int capacity, vector<int> values,
//	vector<int> weight)
//{
//	vector<vector<int>> DP(items + 1, vector<int>(capacity + 1, 0));
//
//	for (int i = 1; i <= items; i++)
//	{
//		int currentWeight = weight[i - 1];
//		int currentValues = values[i - 1];
//
//		for (int totalWeight = 1; totalWeight <= capacity; totalWeight++)
//		{
//			if (totalWeight < currentWeight)
//			{
//				DP[i][totalWeight] = DP[i - 1][totalWeight];
//			}
//			else
//			{
//				DP[i][totalWeight] = max(DP[i - 1][totalWeight],
//					DP[i - 1][totalWeight - currentWeight] + currentValues);
//			}
//		}
//	}
//
//	return DP[items][capacity];
//}

int UnboundedKnapsack(int items, int cpapcity, vector<int> values,
	vector<int> weight)
{
	vector<int> DP(cpapcity + 1, 0);

	for (int w = 0; w <= cpapcity; w++)
	{
		for (int i = 0; i < items; i++)
		{
			if (weight[i] <= w)
			{
				DP[w] = max(DP[w], DP[w - weight[i]] + values[i]);
			}
		}
	}

	return DP[cpapcity];
}

int main()
{
	int items, capacity;
	cin >> items >> capacity;

	vector<int> values(items), weight(items);

	for (auto& v : values) cin >> v;
	for (auto& w : weight) cin >> w;

//	int result = Knapsack_01(items, capacity, values, weight);

	int result = UnboundedKnapsack(items, capacity, values, weight);

	cout << "배낭에 채울 수 있는 물건들의 최고 가격: " << result << endl;
}