#if 0

#include<stdio.h>

#include<math.h>



int queen[16]; //�� ���� ���� ����

int N;

int cnt;



void backtrack(int x);



void main()

{

	int i, j;



	scanf("%d", &N);



	for (i = 0; i<N; i++) //0��° �ٿ� �ϳ��� ���� ���ƺ���

	{
		//dfs
		queen[0] = i;

		backtrack(0);

	}



	printf("%d\n", cnt);





}

//���� ��ġ�� �ε����� ������ ǥ�� queen(row, col) == queen[row] = col;
void backtrack(int x) //�Ķ���ʹ� ���� ���� ��ǥ

{

	int i, j;



	//���ڸ��� ���� ���� �� �ִ°�?
	//x������ ��ȿ��
	for (i = 0; i<x; i++)

	{
		//queen[i] == queen[x] ��ġ�� ���� ��
		//ABS(0-2) == (0-1) //�ٸ� ��
		if ((queen[i] == queen[x]) || (abs(queen[i] - queen[x]) == abs(i - x))) {

			return;

		}

	}



	if (x == N - 1) {

		cnt++; //���� �� ���� ���

		return;

	}



	for (i = 0; i<N; i++) //x+1��° �ٿ� �ϳ��� ���� ���ƺ���

	{

		queen[x + 1] = i;
		//queue[0] = 0, queue[1] = 0
		//queue[0] = 0, queue[1] = 1 -> (0,0) queen, (1,1) queen 
		//queue[0] = 0, queue[1] = 2 -> (0,0) queen, (1,2) queen
		backtrack(x + 1); //backtrack(1)

	}





}

#endif

