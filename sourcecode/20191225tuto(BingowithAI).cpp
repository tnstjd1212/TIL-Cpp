//빙고 게임 만들기 : 6개 빙고가 먼저 되면 승리

#include <iostream>

#include <time.h>

using namespace std;



//변수선언
int iBingo[25] = {};
int iAIBingo[25] = {};//빙고판
int iTemp, idx1, idx2; // 셔플용 변수
int iComplete = 0, iAIComplete = 0; // 완성된 빙고 라인의 개수를 저장 한다.
int iAIMode = 0; //AI난이도 선택용 변수
int iInput; // Player input과 AI input 을 저장하는 변수
bool bAcc = true; //중복 확인 용 변수
int iNonSelect[25] = {}; // AI가 선택할 수를 저장하는 배열
int iNonSelectCount = 0; // AI가 선택할 수의 개수를 카운팅 하는 변수
int iLine = 0;
int iStarCount = 0;
int iSaveCount = 0; // AI hard 모드에서 가장 성공할 확률이 높은 라인을 찾기 위한 변수 


enum AI_MODE {
	AM_EASY = 1,
	AM_HARD
};
enum LINE_NUMBER {
	LN_R1,
	LN_R2,
	LN_R3,
	LN_R4,
	LN_R5,
	LN_C1,
	LN_C2,
	LN_C3,
	LN_C4,
	LN_C5,
	LN_LT,
	LN_RT
};

int main() {

	srand((unsigned int)time(0));


	//1~25 까지 숫자를 넣어준다.
	for (int i = 0; i < 25; ++i) {
		iBingo[i] = i + 1;
		iAIBingo[i] = i + 1;
	}

	//number shuffle
	for (int i = 0; i < 100; ++i) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iBingo[idx1];
		iBingo[idx1] = iBingo[idx2];
		iBingo[idx2] = iTemp;

		//AI 숫자도 섞는다.
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iAIBingo[idx1];
		iAIBingo[idx1] = iAIBingo[idx2];
		iAIBingo[idx2] = iTemp;
	}

	

	//AI 난이도 선택
	while (true) {
		system("cls");
		cout << " 1. Easy" << endl;
		cout << " 2. Hard" << endl;
		cout << "AI 모드를 선택하세요 : ";
		cin >> iAIMode;

		if (iAIMode == AM_EASY || iAIMode == AM_HARD)
			break;
	}

	while (true) {
		system("cls");
		//숫자를 5X5로 출력한다.
		cout << "=================Player================" << endl;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (iBingo[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else {
					cout << iBingo[5 * i + j] << "\t";
				}
			}
			cout << endl;
		}
		cout << "Player 빙고 완성 개수 : " << iComplete << endl << endl;

		cout << "=================AI====================" << endl;

		switch (iAIMode) {
		case AM_EASY:
			cout << "AI easy mode" << endl;
			break;
		case AM_HARD:
			cout << "AI hard mode" << endl;
			break;
		}
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (iAIBingo[i * 5 + j] == INT_MAX) {
					cout << "*\t";
				}
				else
					cout << iAIBingo[i * 5 + j] << "\t";
			}
			cout << endl;
		}
		cout << "AI 빙고 완성 개수 : " << iAIComplete << endl << endl;
		if (iComplete >= 6) {  // 동시에 성공했을 경우 Player 승리
			cout << "Player 승리" << endl;
			break;
		}
		else if (iAIComplete >= 6) {
			cout << "AI 승리" << endl;
			break;
		}

		cout << "숫자를 입력하세요.(0을 누르면 종료됩니다) : ";
			cin >> iInput;

		if (iInput == 0)
			break;
		else if (iInput < 1 || iInput > 25) {
			cout << "범위 내의 숫자가 아닙니다.숫자를 다시 입력하세요." << endl;
			system("pause");
			continue;
		}
		
		//중복되었다고 가정 후 숫자를 찾으면 중복 되지 않았다로 변경
		bAcc = true;
		for (int i = 0; i < 25; ++i) {
			if (iInput == iBingo[i]) {
				bAcc = false;
				iBingo[i] = INT_MAX;
				//더 이상 숫자를 찾아 볼 필요가 없으므로 for문을 빠져나간다.
				break;
			}
		}
		if (bAcc) { //true 일 경우 중복된 숫자를 입력한 것이므로 다시 입력하게 한다.
			cout << "중복된 숫자입니다.숫자를 다시 입력하세요." << endl;
			system("pause");
			continue;
		}

		//AI 숫자를 별로 변환
		for (int i = 0; i < 25; ++i) {
			if (iInput == iAIBingo[i]) {
				iAIBingo[i] = INT_MAX;
				break;
			}
		}

		//AI가 선택을 한다. AI모드에 따라 달라진다.
		// AI Easy 모드 : 중복되지 않은 수 중에 하나를 랜덤하게 선택

		// AI Hard 모드 : 라인들 중에서 빙고가 될 확률이 가장 높은 라인의 숫자 중 하나를 선택
		iNonSelectCount = 0;
		iSaveCount = 0;
		iLine = 0;
		iNonSelect[25] = {};
		switch (iAIMode) {
		case AM_EASY:
			for (int i = 0; i < 25; ++i) {
				if (iAIBingo[i] != INT_MAX) {
					iNonSelect[iNonSelectCount] = iAIBingo[i];
					++iNonSelectCount;
				}
			}
			if (iNonSelectCount != 0) {
				iInput = iNonSelect[rand() % iNonSelectCount];
			}
			else
				cout << "선택할 수 있는 수가 없습니다.";
			
			break;
		case AM_HARD:
			for (int i = 0; i < 5; ++i) {

				//Row 별 개수 검사
				iStarCount = 0;
				for (int j = 0; j < 5; ++j) {
					if (iAIBingo[5 * i + j] == INT_MAX) {
						++iStarCount;
					}
				}
				if (iStarCount >= iSaveCount && iStarCount < 5) {
					iSaveCount = iStarCount;
					iLine = i; // Row 0~4
				}
				//column 별 개수 검사
				iStarCount = 0;
				for (int j = 0; j < 5; ++j) {
					if (iAIBingo[i + j * 5] == INT_MAX) {
						++iStarCount;
					}
				}
				if (iStarCount >= iSaveCount && iStarCount < 5) {
					iSaveCount = iStarCount;
					iLine = i + 5; //column 5~9
				}
			}

			iStarCount = 0;
			for (int i = 0; i < 5; ++i) {
				if (iAIBingo[i * 6] == INT_MAX) {
					++iStarCount;
				}
			}
			if (iStarCount >= iSaveCount && iStarCount < 5) {
				iSaveCount = iStarCount;
				iLine = LN_LT;
			}

			iStarCount = 0;
			for (int i = 0; i < 5; ++i) {
				if (iAIBingo[4 + i * 4] == INT_MAX) {
					++iStarCount;
				}
			}
			if (iStarCount >= iSaveCount && iStarCount < 5) {
				iSaveCount = iStarCount;
				iLine = LN_RT;
			}

			switch (iLine) {
			case LN_R1:
			case LN_R2:
			case LN_R3:
			case LN_R4:
			case LN_R5:// 가로 줄 일 경우
				for (int i = 0; i < 5; ++i) {
					if (iAIBingo[iLine * 5 + i] != INT_MAX) {
						iNonSelect[iNonSelectCount] = iAIBingo[iLine * 5 + i];
						++iNonSelectCount;
					}
				}
				if (iNonSelectCount != 0) {
					iInput = iNonSelect[rand() % iNonSelectCount];
				}
				else
					cout << "선택할 수 있는 수가 없습니다.";

				break;
			case LN_C1:
			case LN_C2:
			case LN_C3:
			case LN_C4:
			case LN_C5://세로 줄 일 경우
				for (int i = 0; i < 5; ++i) {
					if (iAIBingo[(iLine - 5) + 5 * i] != INT_MAX) {
						iNonSelect[iNonSelectCount] = iAIBingo[(iLine - 5) + 5 * i];
						++iNonSelectCount;
					}
				}
				if (iNonSelectCount != 0) {
					iInput = iNonSelect[rand() % iNonSelectCount];
				}
				else
					cout << "선택할 수 있는 수가 없습니다.";

				break;
			case LN_LT:
				for (int i = 0; i < 5; ++i)
				{
					if (iAIBingo[6 * i] != INT_MAX) {
						iNonSelect[iNonSelectCount] = iAIBingo[6 * i];
						++iNonSelectCount;
					}
				}
				if (iNonSelectCount != 0) {
					iInput = iNonSelect[rand() % iNonSelectCount];
				}
				else
					cout << "선택할 수 있는 수가 없습니다.";

				break;
			case LN_RT:
				for (int i = 0; i < 5; ++i)
				{
					if (iAIBingo[4 * i + 4] != INT_MAX) {
						iNonSelect[iNonSelectCount] = iAIBingo[4 * i + 4];
						++iNonSelectCount;
					}
				}
				if (iNonSelectCount != 0) {
					iInput = iNonSelect[rand() % iNonSelectCount];
				}
				else
					cout << "선택할 수 있는 수가 없습니다.";

				break;// line switch
			}
			break; //AImode switch
		}

		cout << "AI가 선택한 수는 " << iInput << "입니다." << endl;
		system("pause");


		//AI가 선택한 수를 *로 변환
		for (int i = 0; i < 25; ++i) {
			if (iInput == iBingo[i]) {
				iBingo[i] = INT_MAX;
				break;
			}
		}


		for (int i = 0; i < 25; ++i) {
			if (iInput == iAIBingo[i]) {
				iAIBingo[i] = INT_MAX;
				break;
			}
		}




		//빙고가 완성 되었는지 체크
		iComplete = 0;
		iAIComplete = 0;
		for (int i = 0; i < 5; ++i) {
			//Player 가로 세로 체크
			//가로 5줄 체크
			int icheck = 0;
			for (int j = 0; j < 5; ++j) {
				if (iBingo[i * 5 + j] == INT_MAX)
					++icheck;
				else //하나라도 아닐 경우 빙고가 아니므로 더 비교할 필요 없으므로 탈출 
					break;
			}
			if (icheck == 5) { //5개가 모두 체크 됬으면 1Bingo
				++iComplete;
			}

			// 세로 5줄 체크
			icheck = 0; //세로를 체크하기 위해 다시 초기화
			for (int j = 0; j < 5; ++j) {
				if (iBingo[j * 5 + i] == INT_MAX)
					++icheck;
				else
					break;
			}
			if (icheck == 5) {
				++iComplete;
			}

			//AI  가로 세로 체크
			//가로 5줄 체크
			int iAIcheck = 0;
			for (int j = 0; j < 5; ++j) {
				if (iAIBingo[i * 5 + j] == INT_MAX)
					++iAIcheck;
				else //하나라도 아닐 경우 빙고가 아니므로 더 비교할 필요 없으므로 탈출 
					break;
			}
			if (iAIcheck == 5) { //5개가 모두 체크 됬으면 1Bingo
				++iAIComplete;
			}

			// 세로 5줄 체크
			iAIcheck = 0; //세로를 체크하기 위해 다시 초기화
			for (int j = 0; j < 5; ++j) {
				if (iAIBingo[j * 5 + i] == INT_MAX)
					++iAIcheck;
				else
					break;
			}
			if (iAIcheck == 5) {
				++iAIComplete;
			}
		}

		//Player 대각선 체크
		//오른쪽 대각선 체크
		int icheck = 0;
		for (int i = 0; i < 5; ++i) {
			if (iBingo[6 * i] == INT_MAX)
				++icheck;
			else
				break;
		}
		if (icheck == 5) {
			++iComplete;
		}

		//왼쪽 대각선 체크
		icheck = 0;
		for (int i = 0; i < 5; ++i) {
			if (iBingo[4 + i * 4] == INT_MAX) {
				++icheck;
			}
			else {
				break;
			}
		}

		if (icheck == 5) {
			++iComplete;
		}


		//AI 대각선 체크
		//오른쪽 대각선 체크
		int iAIcheck = 0;
		for (int i = 0; i < 5; ++i) {
			if (iAIBingo[6 * i] == INT_MAX)
				++iAIcheck;
			else
				break;
		}
		if (iAIcheck == 5) {
			++iAIComplete;
		}

		//왼쪽 대각선 체크
		iAIcheck = 0;
		for (int i = 0; i < 5; ++i) {
			if (iAIBingo[4 + i * 4] == INT_MAX) {
				++iAIcheck;
			}
			else {
				break;
			}
		}

		if (iAIcheck == 5) {
			++iAIComplete;
		}

	}

	return 0;
}