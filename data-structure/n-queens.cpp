#if 0

#include<stdio.h>

#include<math.h>



int queen[16]; //각 줄의 퀸을 저장

int N;

int cnt;



void backtrack(int x);



void main()

{

	int i, j;



	scanf("%d", &N);



	for (i = 0; i<N; i++) //0번째 줄에 하나씩 퀸을 놓아본다

	{
		//dfs
		queen[0] = i;

		backtrack(0);

	}



	printf("%d\n", cnt);





}

//퀸의 위치를 인덱스와 값으로 표현 queen(row, col) == queen[row] = col;
void backtrack(int x) //파라매터는 퀸을 놓을 좌표

{

	int i, j;



	//이자리에 퀸을 놓을 수 있는가?
	//x까지만 유효함
	for (i = 0; i<x; i++)

	{
		//queen[i] == queen[x] 겹치면 같은 열
		//ABS(0-2) == (0-1) //다른 열
		if ((queen[i] == queen[x]) || (abs(queen[i] - queen[x]) == abs(i - x))) {

			return;

		}

	}



	if (x == N - 1) {

		cnt++; //퀸을 다 놓은 경우

		return;

	}



	for (i = 0; i<N; i++) //x+1번째 줄에 하나씩 퀸을 놓아본다

	{

		queen[x + 1] = i;
		//queue[0] = 0, queue[1] = 0
		//queue[0] = 0, queue[1] = 1 -> (0,0) queen, (1,1) queen 
		//queue[0] = 0, queue[1] = 2 -> (0,0) queen, (1,2) queen
		backtrack(x + 1); //backtrack(1)

	}





}

#endif

