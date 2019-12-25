
#include <iostream>
#include <time.h>


using namespace std;

int main() {
	/*
	do {}while(조건식)
	do while문은 처음 한 번은 무조건 동작하고, 그 뒤에는 조건식을
	체크해서 동작하는 반복문 이다.
	*/

	/*
	배열 : 여러개의 변수를 한 번에 선언 할 수 있는 기능 이다,
	변수타입 배열명[개수]
	특징 : 연속된 메모리 공간에 생성된다.
	*/


	srand((unsigned int)time(0));
	//lotto Program
	int iLOTTO[45] = {};

	for (int i = 0; i < 45; ++i) { //베열에 1부터 45까지 차례대로 넣음
		iLOTTO[i] = i + 1;
	}

	//shuffle :Swap algorithm 활용
	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i) { //임의의 두 인덱스를 100번 swap한다
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		iTemp = iLOTTO[idx1];
		iLOTTO[idx1] = iLOTTO[idx2];
		iLOTTO[idx2] = iTemp;
	}
	for (int i = 0; i < 6; ++i) {
		cout << iLOTTO[i] << "\t";
	}
	cout << "Bonus number :" << iLOTTO[6] << endl;


	return 0;
}