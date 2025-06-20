#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

const int UNKNOWN = 1e9;

int V, E;
vector<vector<int>> adj;
vector<vector<int>> weight;

map<pair<int, int>, int> memo;

int ShortestPath_Memoization(int depth, int node, vector<vector<int>>
	& adj, vector<vector<int>>& weight)
{
	if (memo.find({ node, depth }) != memo.end())
	{
		return memo[{node, depth}];
	}

	memo[{node, depth}] = UNKNOWN;

	for (auto next : adj[node])
	{
		int w = weight[node][next];
		int dist = ShortestPath_Memoization(depth - 1, next, adj, weight) + w;

		memo[{node, depth}] = min(memo[{node, depth}], dist);
	}

	return memo[{node, depth}];
}

vector<int> SingleSourecShortestPaths(int source)
{
	vector<vector<int>> adj_t(V);
	vector<vector<int>> weight_t(V, vector<int>(V, UNKNOWN));

	memo.clear();

	for (int i = 0; i < V; i++)
	{
		for (auto j : adj[i])
		{
			adj_t[j].push_back(i);
			weight_t[j][i] = weight[i][j];
		}

		memo[{source, i }] = 0;

		if (i != source)
		{
			memo[{i, 0}] = UNKNOWN;
		}
	}

	vector<int> distance(V);

	for (int i = 0; i < V; i++)
	{
		distance[i] = ShortestPath_Memoization(V - 1, i, adj_t, weight_t);
	}

	return distance;
}

int main()
{
	cin >> V >> E;

	weight.resize(V, vector<int>(V, UNKNOWN));
	adj.resize(V);

	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;

		adj[u].push_back(v);
		weight[u][v] = w;
	}

	vector<vector<int>> paths(V);

	for (int i = 0; i < V; i++)
	{
		paths[i] = SingleSourecShortestPaths(i);
	}

	cout << "각 정점 사이의 최단 거리: " << endl;
	
	for (int i = 0; i < V; i++)
	{
		cout << i << ": ";

		for (int j = 0; j < V; j++)
		{
			(paths[i][j] == UNKNOWN) ? cout << "- "
				: cout << paths[i][j] << " ";
		}

		cout << endl;
	}
}