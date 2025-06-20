#include <vector>
#include <stack>
#include <iostream>

using namespace std;

void FillStack(int node, vector<bool>& visited,
	vector<vector<int>>& adj, stack<int>& stack)
{
	visited[node] = true;

	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			FillStack(next, visited, adj, stack);
		}
	}

	stack.push(node);
}

void CollenctConnectedComponents(int node, vector<bool>& visited,
	vector<vector<int>>& adj, vector<int>& component)
{
	visited[node] = true;
	component.push_back(node);

	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			CollenctConnectedComponents(next, visited, adj, component);
		}
	}
}

vector<vector<int>> Transpose(int V, vector<vector<int>> adj)
{
	vector<vector<int>> transpose(V);

	for (int i = 0; i < V; i++)
	{
		for (auto next : adj[i])
		{
			transpose[next].push_back(i);
		}
	}

	return transpose;
}

vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj)
{
	vector<bool> visited(V, false);
	stack<int> stack;

	for (int i = 0; i < V; i++)
	{
		if (!visited[i])
		{
			FillStack(i, visited, adj, stack);
		}
	}

	vector<vector<int>> transpose = Transpose(V, adj);

	fill(visited.begin(), visited.end(), false);

	vector<vector<int>> connectedComponents;

	while (!stack.empty())
	{
		int node = stack.top();
		stack.pop();

		if (!visited[node])
		{
			vector<int> component;

			CollenctConnectedComponents(node, visited, transpose, component);
			connectedComponents.push_back(component);
		}
	}

	return connectedComponents;
}

int main()
{
	int V = 9;

	vector<vector<int>> adj =
	{
		{1,3},
		{2,4},
		{3,5},
		{7},
		{2},
		{4,6},
		{7,2},
		{8},
		{3}
	};

	vector<vector<int>> connectedComponets = Kosaraju(V, adj);

	cout << "���� ���� ��� ����: " << connectedComponets.size() << endl;

	for (int i = 0; i < connectedComponets.size(); i++)
	{
		cout << "[" << i + 1 << "] ";

		for (auto node : connectedComponets[i])
			cout << node << " ";

		cout << endl;
	}
}