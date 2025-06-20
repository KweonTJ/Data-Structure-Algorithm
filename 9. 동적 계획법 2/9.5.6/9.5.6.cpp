#include <vector>
#include <iostream>

using namespace std;

const int UNKNOWN = 1e9;



vector<vector<int>> FloydWarshall(int V, vector<vector<int>> weight)
{
	vector<vector<int>> distance(V, vector<int>(V, UNKNOWN));

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			distance[i][j] = weight[i][j];
		}

		distance[i][i] = 0;
	}
	
	for (int mid = 0; mid < V; mid++)
	{
		for (int start = 0; start < V; start++)
		{
			for (int end = 0; end < V; end++)
			{
				if (distance[start][mid] + distance[mid][end] < distance[start][end])
				{
					distance[start][end] = distance[start][mid] + distance[mid][end];
				}
			}
		}
	}

	for (int i = 0; i < V; i++)
	{
		if (distance[i][i] < 0)
			return {};
	}

	return distance;
}

int main()
{
	int V, E;
	cin >> V >> E;

	vector<vector<int>> weight(V, vector<int>(V, UNKNOWN));

	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;

		weight[u][v] = w;
	}

	vector<vector<int>> distance = FloydWarshall(V, weight);

	if (distance.empty())
	{
		cout << "음수 가중치 사이클이 있습니다." << endl;
		return 0;
	}

	for (int i = 0; i < V; i++)
	{
		cout << i << endl;

		for (int j = 0; j < V; j++)
		{
			cout << "\t" << j << ": ";

			(distance[i][j] == UNKNOWN) ? cout << "_" << endl
				: cout << distance[i][j] << endl;
		}
	}

	return 0;
}