#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

#define DEBUG 1

#if DEBUG
#define PRINT(x) cerr << x
#elif
#define PRINT(x)
#endif

using namespace std;

vector<vector<pair<int, int>>> found;

int LCS_BruteForce(string A, string B, int i, int j, vector<pair<int, int>> subsequence)
{
	if (i >= A.size() || j >= B.size())
	{
		found.push_back(subsequence);
		
		return subsequence.size();
	}

	if (A[i] == B[j])
	{
		subsequence.push_back({ i, j });

		return LCS_BruteForce(A, B, i + 1, j + 1, subsequence);
	}

	return max(LCS_BruteForce(A, B, i + 1, j, subsequence),
		LCS_BruteForce(A, B, i, j + 1, subsequence));
}

void PrintSubseqnces(string A, string B)
{
	sort(found.begin(), found.end(), [](auto a, auto b)
		{
			if (a.size() != b.size())
			{
				return a.size() < b.size();
			}

			return a < b;
		});

	found.erase(unique(found.begin(), found.end()), found.end());

	int previousSize = 0;

	for (auto subsequence : found)
	{
		if (subsequence.size() != previousSize)
		{
			previousSize = subsequence.size();
			PRINT("SIZE = " << previousSize << endl);
		}

		string a_seq(A.size(), '_');
		string b_seq(B.size(), '_');

		for (auto pair : subsequence)
		{
			a_seq[pair.first] = A[pair.first];
			b_seq[pair.first] = B[pair.first];
		}

		PRINT("\t" << a_seq << " " << b_seq << endl);
	}
}

int main()
{
	string A, B;
	cin >> A >> B;
	
	int LCS = LCS_BruteForce(A, B, 0, 0, {});
	cout << A << "와 " << B << "의 최장 공통 부분 시퀀스 길이: " << LCS << endl;

#if DEBUG
	PrintSubseqnces(A, B);
#endif
}