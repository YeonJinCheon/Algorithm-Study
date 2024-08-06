#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

int T;
int N;
int max_sum;

struct Balloon
{
	int prev;
	int pres;
	int next;
};

Balloon arr[1001] = { 0 };
vector<Balloon> v;
int visited[1001] = { 0 };

void init()
{
	for (int i = 0; i < 11; i++)
	{
		memset(arr, 0, sizeof(arr));
	}
	for (int i = 0; i < 11; i++)
	{
		memset(visited, 0, sizeof(visited));
	}
	max_sum = 0;
}

void input()
{
	int a;
	int b = -1;
	int prev, pres; // , next;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> a;
		
		pres = a;
		prev = b;
		arr[a] = { prev, pres, -1 };  // 양 끝을 -1로 채움
		arr[b].next = pres;

		/*
		pres = a;
		prev = b;
		v.push_back({ prev, pres, -1 });
		b = a;
		*/
	}
}

void process(int lev, int sum)
{
	int calc;
	int temp_prev, temp_next;
	for (int i = 0; i < N; i++)
	{
		if (visited[i])
			return;
		visited[i] = 1;

		if (v[i].prev != -1 || v[i].next != -1)
		{
			calc = v[i].prev * v[i].next;
		}
		if (v[i].prev == -1)
		{
			calc = v[i].pres;
			temp_prev = v[i + 1].prev;
			v[i + 1].prev = -1;
		}
		if (v[i].next == -1)
		{
			calc = v[i].pres;
			temp_next = v[i - 1].next;
			v[i - 1].next = -1;
		}

		process(lev + 1, sum + calc);
		visited[i] = 0;
		if (v[i].prev == -1)
		{
			v[i + 1].prev = temp_prev;
		}
		if (v[i].next == -1)
		{
			v[i - 1].next = temp_next;
		}
	}
}

void output(int t)
{
	cout << "#" << t << " " << max_sum << "\n";
}

int main()
{
	cin >> T;

	for (int t = 0; t < T; t++)
	{
		init();
		input();
		process(0, 0);
		output(t + 1);
	}

	return 0;
}