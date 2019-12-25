
/*
야구게임 :
1~9 사이의 랜덤한 3개의 숫자를 얻어온다. 
단, 숫자는 중복되어서는 안된다.
player는 이 3개의 숫자를 맞춰야 하며 3개씩 숫자를 입력한다.
만약 1개의 숫자의 위치와 숫자를 모두 맞췄다면, 1strike,
위치는 맞추지 못했지만, 숫자가 입력한 3개의 숫자에 들어있다면,
1ball 증가하며,
입력한 3개의 숫자에 맞출 숫자가 아무 것도 없다면 out 이다.
 얻어온 3개의 숫자와 자리를 모두 일치하게 입력하면 게임이 종료된다.
 단, 입력한 숫자 중에 0이 하나라도 있을경우 종료된다.
*/



#include<iostream>
#include<time.h>

using namespace std;


int main() {
	//랜덤으로 3개의 숫자를 얻어오는 코드
	srand((unsigned int)time(0));
	int iNum[9] = {}; //1~9의 숫자를 넣을 배열 선언

	for (int i = 0; i < 9; ++i) { // 배열에 1~9 까지의 숫자를 넣는 코드
		iNum[i] = i + 1;
	}

	int iSwap, idx1, idx2;
	for (int i = 0; i < 50; ++i) { //shuffle
		idx1 = rand() % 9;
		idx2 = rand() % 9;

		iSwap = iNum[idx1];
		iNum[idx1] = iNum[idx2];
		iNum[idx2] = iSwap;
	}

	int iRnum[3];
	for (int i = 0; i < 3; ++i) { //섞은 숫자 배열의 맨 앞의 3자리를 랜덤 숫자로 뽑아옴
		iRnum[i] = iNum[i];
	}

	int iCount = 0;
	int iPlayer[3];
	int iball = 0, istrike = 0;
	//game start
	while (true) {
		//Player의 입력을 받아오는 코드
		cout << endl << "1에서 9사이의 서로 다른 정수 3개를 입력해 주세요. (0이 입력되면 게임 종료)" << endl;
		cin >> iPlayer[0] >> iPlayer[1] >> iPlayer[2];


		//Player의 입력에 0이 있는지 확인 하는 코드
		if ((iPlayer[0] == 0) || (iPlayer[1] == 0) || (iPlayer[2] == 0)) {
			break;
		}
		else if ((iPlayer[0] < 1) || (iPlayer[0] > 9) || (iPlayer[1] < 1) || (iPlayer[1] > 9) || (iPlayer[2] < 1) || (iPlayer[2] > 9)) {
			// 1~9사이의 숫자가 아닐 경우
			cout << "범위 내의 숫자가 아닙니다." << endl;
			continue;
		}
		else if (iPlayer[0] == iPlayer[1] || iPlayer[1] == iPlayer[2] || iPlayer[2] == iPlayer[0]) {
			cout << "숫자가 중복 되었습니다." << endl;
			continue;
		}


		//Player의 입력과 얻어온 3개의 숫자를 비교하는 코드
		else {
			++iCount;
			iball = istrike = 0;
			for (int p = 0; p < 3; ++p) {
				for (int r = 0; r < 3; ++r) {
					if (iPlayer[p] == iRnum[r]) {
						if (p == r) {
							++istrike;
						}
						else {
							++iball;
						}
					}
				}
			}
		}


		// 적절한 출력을 출력하는 코드
		if ((iball == 0) && (istrike == 0)) {
			cout << "Out!" << endl;
		}
		else if (istrike == 3) {
			cout << "Game Clear!!  시도 횟수 : " << iCount << endl;
			break;
		}
		else {
			cout << istrike << " strike, " << iball << " ball" << endl;
		}
	}

	return 0;
}