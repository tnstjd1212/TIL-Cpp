// 숫자 퍼즐



#include <iostream>
#include <time.h>
#include <conio.h>
//console input output

using namespace std;

int main() {

	srand((unsigned int)time(0));

	int iNum[16] = {};

	for (int i = 0; i < 15; ++i) {
		iNum[i] = i + 1;
	}
	//가장 마지막 칸은 공백
	//(공백은 INT_MAX 라는 특수한 값을 사용)
	//INT_MAX : 이미 정의 되어 있는 값
	//          int의 최댓값
	iNum[15] = INT_MAX;

	/*공백을 제외하고 1~24 까지의 숫자만 
	섞어준다. (인덱스 0~23)
	*/
	int iTemp, idx1, idx2;
	int ientrp = 0;
	do {
		for (int i = 0; i < 100; ++i) { //shuffle
			idx1 = rand() % 15;
			idx2 = rand() % 15;

			iTemp = iNum[idx1];
			iNum[idx1] = iNum[idx2];
			iNum[idx2] = iTemp;
		}
		
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < i; j++) {
				if (iNum[i] < iNum[j])
					++ientrp;
			}
		}
	} while (ientrp % 2); // 무질서도가 짝수일 때 까지 다시 셔플

	char cinput;
	int iStar = 15;// 별의 시작위치

	while (true) {
		system("cls");
		cout << ientrp << endl;
		for (int i = 0; i < 4; ++i) {           // 5*5 행렬 처럼 출력
			for (int j = 0; j < 4; ++j) {
				if (iNum[j + i * 4] == INT_MAX) {
					cout << "*\t";
					iStar = j + i * 4;  //별의 위치 체크
				}
				else {
					cout << iNum[j + i * 4] << "\t";
				}
			}
			cout << endl;
		}


		//퍼즐을 맞추었는지 체크
		bool bWin = true; // 일단 다 맞았다고 가정
		for (int i = 0; i < 15; ++i)
		{
			if (iNum[i] != (i + 1)) { // 하나라도 틀렸다면 false
				bWin = false;
				break;
			}
		}
		if (bWin) { // 모두 맞았다면 실행
			break;
		}


		cout << "w : 위, s :아래, a : 왼쪽, d : 오른쪽, q : 종료"; //key guide
		cinput = _getch();

		if (cinput == 'q' || cinput == 'Q') { 
			break;
		}

		switch (cinput) //* 이동용 switch 문
		{
		case 'w':
		case 'W':
			if (iStar > 3) {
				iNum[iStar] = iNum[iStar - 4]; //*위치에 이동하려는 곳의 값 대입
				iNum[iStar - 4] = INT_MAX; // *의 값은 무조건 정해져 있으므로 따로 저장할 필요 없음
			}
			break;
		case 's':
		case 'S':
			if (iStar < 12) {
				iNum[iStar] = iNum[iStar + 4];
				iNum[iStar + 4] = INT_MAX;
			}
			break; 
		case 'a':
		case 'A':
			if (iStar % 4) {
				iNum[iStar] = iNum[iStar - 1];
				iNum[iStar - 1] = INT_MAX;
			}
			break;
		case 'd':
		case 'D':
			if ((iStar % 4) != 3) {
				iNum[iStar] = iNum[iStar + 1];
				iNum[iStar + 1] = INT_MAX;
			}
			break;
		default:
			break;
		}
	}

	cout << endl << "게임을 종료 합니다." << endl;


	return 0;
}