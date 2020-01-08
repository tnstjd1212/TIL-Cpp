
#include <iostream>
#include <time.h>

using namespace std;

#define NAME_SIZE 32
#define DESC_LENGTH 512
#define INVENTORY_MAX 20
#define STORE_MAX 3

enum MAIN_MANU {
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_BAG,
	MM_EXIT
};

enum MAP_TYPE {
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum BATTLE {
	B_NONE,
	B_ATTACK,
	//B_ESCAPE,
	//B_DEFEND,
	B_BACK
};
enum JOB {
	J_NONE,
	J_KNIGHT,
	J_ARCHER,
	J_WIZARD,
	J_END   // END값을 코드에 추가함으로써 직업을 나중에 추가 해도 다른 코드를 변경할 필요 없음
};
enum ITEM_TYPE {
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};
enum STORE_MENU {
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_SELL,
	SM_BACK
};

struct _tagMonster
{
	char strName[NAME_SIZE];
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iGetExp;
	int iGetGold;
	int iLevel;
	int iAttackMin;
	int iAttackMax;
	int iArmor;
};

struct _tagItem
{
	char strName[NAME_SIZE];
	char strTypeName[NAME_SIZE];
	char strDesc[DESC_LENGTH]; //아이템 설명
	ITEM_TYPE eType;
	int iPrice;
	int iSell;
	int iStat;
};

struct _tagInventory {
	_tagItem tMyItemArr[INVENTORY_MAX];
	int iItemCount;
	int iGold;
};

struct _tagPlayer {
	int iExp;
	int iLevel;
	char strName[NAME_SIZE];
	JOB eJob;
	char strJob[NAME_SIZE];
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iAttackMin;
	int iAttackMax;
	int iArmor;
	_tagInventory tInventory;
};

//변수 선언
int iMenu;
int iBattleMenu; // 전투할때 iMenu가 사용 중이므로 선택용 변수가 하나 더 필요
int iJob = J_NONE;
int iAttack = 0;
int iDamage = 0;
_tagPlayer tPlayer = {};
_tagMonster tMonsterArr[MT_BACK - 1] = {}; // 맵 단계당 몹 하나 MT_BACK - 1
_tagMonster tBattleMonster = {};
_tagItem tStoreWeaponArr[STORE_MAX] = {};
_tagItem tStoreArmorArr[STORE_MAX] = {};
bool bMonsterAlive;
bool bPlayerAlive;


int main() {

	srand((unsigned int)time(0));

	// 게임시작 시 플레이어 정보 설정
	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.tInventory.iGold = 300000;
	cout << "이름 : ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1);

	while (iJob == J_NONE)
	{
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		cin >> iJob;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iJob <= J_NONE || iJob >= J_END)
			iJob - J_NONE;
	}

	tPlayer.eJob = (JOB)iJob;
	switch (tPlayer.eJob)
	{
	case J_KNIGHT:
		strcpy_s(tPlayer.strJob, "기사");
		tPlayer.iArmor = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iAttackMin = 5;
		tPlayer.iHPMax = 75;
		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMPMax = 25;
		tPlayer.iMP = tPlayer.iMPMax;
		break;
	case J_ARCHER:
		strcpy_s(tPlayer.strJob, "궁수");
		tPlayer.iArmor = 3;
		tPlayer.iAttackMax = 13;
		tPlayer.iAttackMin = 7;
		tPlayer.iHPMax = 60;
		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMPMax = 35;
		tPlayer.iMP = tPlayer.iMPMax;
		break;
	case J_WIZARD:
		strcpy_s(tPlayer.strJob, "마법사");
		tPlayer.iArmor = 1;
		tPlayer.iAttackMax = 17;
		tPlayer.iAttackMin = 7;
		tPlayer.iHPMax = 55;
		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMPMax = 55;
		tPlayer.iMP = tPlayer.iMPMax;
		break;
	}

	//몬스터 스탯 설정
	//easy 고블린
	strcpy_s(tMonsterArr[0].strName, "고블린");
	tMonsterArr[0].iArmor = 2;
	tMonsterArr[0].iAttackMax = 5;
	tMonsterArr[0].iAttackMin = 10;
	tMonsterArr[0].iGetExp = 10;
	tMonsterArr[0].iGetGold = 100;
	tMonsterArr[0].iHPMax = 45;
	tMonsterArr[0].iHP = tMonsterArr[0].iHPMax;
	tMonsterArr[0].iLevel = 1;
	tMonsterArr[0].iMPMax = 10;
	tMonsterArr[0].iMP = tMonsterArr[0].iMPMax;
	
	//normal 오크
	strcpy_s(tMonsterArr[1].strName, "오크");
	tMonsterArr[1].iArmor = 30;
	tMonsterArr[1].iAttackMax = 40;
	tMonsterArr[1].iAttackMin = 30;
	tMonsterArr[1].iGetExp = 100;
	tMonsterArr[1].iGetGold = 700;
	tMonsterArr[1].iHPMax = 400;
	tMonsterArr[1].iHP = tMonsterArr[1].iHPMax;
	tMonsterArr[1].iLevel = 10;
	tMonsterArr[1].iMPMax = 30;
	tMonsterArr[1].iMP = tMonsterArr[1].iMPMax;

	//hard 오우거
	strcpy_s(tMonsterArr[2].strName, "오우거");
	tMonsterArr[2].iArmor = 100;
	tMonsterArr[2].iAttackMax = 160;
	tMonsterArr[2].iAttackMin = 150;
	tMonsterArr[2].iGetExp = 10000;
	tMonsterArr[2].iGetGold = 30000;
	tMonsterArr[2].iHPMax = 2000;
	tMonsterArr[2].iHP = tMonsterArr[2].iHPMax;
	tMonsterArr[2].iLevel = 80;
	tMonsterArr[2].iMPMax = 100;
	tMonsterArr[2].iMP = tMonsterArr[2].iMPMax;

	//상점에서 판매할 아이템 목록
	strcpy_s(tStoreWeaponArr[0].strName, "무딘 칼");
	strcpy_s(tStoreWeaponArr[0].strTypeName, "무기");
	strcpy_s(tStoreWeaponArr[0].strDesc, "날은 없지만 타격감이 좋다.");
	tStoreWeaponArr[0].eType = IT_WEAPON;
	tStoreWeaponArr[0].iPrice = 2000;
	tStoreWeaponArr[0].iSell = 1000;
	tStoreWeaponArr[0].iStat = 100;

	strcpy_s(tStoreWeaponArr[1].strName, "칼");
	strcpy_s(tStoreWeaponArr[1].strTypeName, "무기");
	strcpy_s(tStoreWeaponArr[1].strDesc, "날이 있어서 벨 수 있다.");
	tStoreWeaponArr[1].eType = IT_WEAPON;
	tStoreWeaponArr[1].iPrice = 10000;
	tStoreWeaponArr[1].iSell = 3000;
	tStoreWeaponArr[1].iStat = 50;

	strcpy_s(tStoreWeaponArr[2].strName, "날카로운 칼");
	strcpy_s(tStoreWeaponArr[2].strTypeName, "무기");
	strcpy_s(tStoreWeaponArr[2].strDesc, "날이 날카롭다.");
	tStoreWeaponArr[2].eType = IT_WEAPON;
	tStoreWeaponArr[2].iPrice = 100000;
	tStoreWeaponArr[2].iSell = 40000;
	tStoreWeaponArr[2].iStat = 200;

	strcpy_s(tStoreArmorArr[0].strName, "말랑한 갑옷");
	strcpy_s(tStoreArmorArr[0].strTypeName, "방어구");
	strcpy_s(tStoreArmorArr[0].strDesc, "말랑하다.");
	tStoreArmorArr[0].eType = IT_WEAPON;
	tStoreArmorArr[0].iPrice = 1000;
	tStoreArmorArr[0].iSell = 500;
	tStoreArmorArr[0].iStat = 10;

	strcpy_s(tStoreArmorArr[1].strName, "갑옷");
	strcpy_s(tStoreArmorArr[1].strTypeName, "방어구");
	strcpy_s(tStoreArmorArr[1].strDesc, "갑옷이다.");
	tStoreArmorArr[1].eType = IT_WEAPON;
	tStoreArmorArr[1].iPrice = 15000;
	tStoreArmorArr[1].iSell = 5000;
	tStoreArmorArr[1].iStat = 70;

	strcpy_s(tStoreArmorArr[2].strName, "단단한 갑옷");
	strcpy_s(tStoreArmorArr[2].strTypeName, "방어구");
	strcpy_s(tStoreArmorArr[2].strDesc, "단단하다.");
	tStoreArmorArr[2].eType = IT_WEAPON;
	tStoreArmorArr[2].iPrice = 90000;
	tStoreArmorArr[2].iSell = 35000;
	tStoreArmorArr[2].iStat = 130;

	while (true) {
		system("cls");
		cout << "=================메인메뉴==================" << endl;
		cout << "1. 지도" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 가방" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택 하세요 : ";
		cin >> iMenu;

		if (cin.fail()) {
			//에러버퍼를 비워준다.
			cin.clear();
			//입력 버퍼에 \n을 삭제 한다.
			cin.ignore(1024, '\n'); //넉넉하게 1024 바이트를 검사하여 \n을 지워준다.
			continue;
		}
		if (iMenu == MM_EXIT)
			break;
		switch (iMenu) {
		case MM_MAP:
			while (true) {
				system("cls");
				cout << "=================맵메뉴===================" << endl;
				cout << "1. 쉬움" << endl;
				cout << "2. 보통" << endl;
				cout << "3. 어려움" << endl;
				cout << "4. 뒤로" << endl;
				cout << "메뉴를 선택 하세요 : ";
				cin >> iMenu;

				if (cin.fail()) {
					//에러버퍼를 비워준다.
					cin.clear();
					//입력 버퍼에 \n을 삭제 한다.
					cin.ignore(1024, '\n'); //넉넉하게 1024 바이트를 검사하여 \n을 지워준다.
					continue;
				}
				if (iMenu <= MT_NONE || iMenu > MT_BACK)
					continue;
				if (iMenu == MT_BACK) {
					break;
				}

				tBattleMonster = tMonsterArr[iMenu - 1];
				strcpy_s(tBattleMonster.strName,  tMonsterArr[iMenu - 1].strName);
				tPlayer.iHP = tPlayer.iHPMax;
				tPlayer.iMP = tPlayer.iMPMax;
				bMonsterAlive = 1;
				bPlayerAlive = 1;
				while (true)
				{
					system("cls");
					switch (iMenu) {
					case MT_EASY:
						cout << "=================쉬움===================" << endl;
						break;
					case MT_NORMAL:
						cout << "=================보통===================" << endl;
						break;
					case MT_HARD:
						cout << "=================어려움===================" << endl;
						break;
					}
					// Player info
					cout << "****************Player****************" << endl;
					cout << "이름 : " << tPlayer.strName <<
						"\t직업 : " << tPlayer.strJob << endl;
					cout << "레벨 : " << tPlayer.iLevel <<
						"\t경험치 : " << tPlayer.iExp << endl;
					cout << "공격력  : " << tPlayer.iAttackMin <<
						" - " << tPlayer.iAttackMax << "\t방어력 : " << tPlayer.iArmor << endl;
					cout << "체력 : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
						"\t마나 : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;
					cout << "보유골드 : " << tPlayer.tInventory.iGold << endl << endl;

					// Monster info
					cout << "****************Monster****************" << endl;
					cout << "이름 : " << tBattleMonster.strName <<
						"\t레벨 : " << tBattleMonster.iLevel << endl;
					cout << "공격력  : " << tBattleMonster.iAttackMin <<
						" - " << tBattleMonster.iAttackMax << "\t방어력 : " << tBattleMonster.iArmor << endl;
					cout << "체력 : " << tBattleMonster.iHP << " / " << tBattleMonster.iHPMax <<
						"\t마나 : " << tBattleMonster.iMP << " / " << tBattleMonster.iMPMax << endl;
					cout << "획득 경험치 : " << tBattleMonster.iGetExp <<
						"\t획득 골드 : " << tBattleMonster.iGetGold << endl << endl;

					cout << "1. 공격" << endl;
					/*cout << "2. 회피" << endl;
					cout << "3. 방어" << endl;*/
					cout << "2. 도망" << endl;
					cout << "메뉴를 선택 하세요." << endl;
					cin >> iBattleMenu;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}
					if (iBattleMenu == B_BACK)
						break;
					switch (iBattleMenu) {
					case B_ATTACK:
						iAttack = rand() % (tPlayer.iAttackMax - tPlayer.iAttackMin + 1) + tPlayer.iAttackMin;
						iDamage = iAttack <= tBattleMonster.iArmor ? 1 : iAttack - tBattleMonster.iArmor;
						tBattleMonster.iHP -= iDamage;
						cout << tPlayer.strName << " 이 " << tBattleMonster.strName << " 에게 " << iDamage << "의 피해를 입혔습니다." << endl;

						//몬스터가 죽었을 경우
						if (tBattleMonster.iHP <= 0)
						{
							bMonsterAlive = 0; // 몬스터를 사망 상태로 변경

							break;
						}

						//몬스터가 살아 있다면 플레이어를 공격한다.
						iAttack = rand() % (tBattleMonster.iAttackMax - tBattleMonster.iAttackMin + 1) + tBattleMonster.iAttackMin;
						iDamage = iAttack <= tPlayer.iArmor ? 1 : iAttack - tPlayer.iArmor;
						tPlayer.iHP -= iDamage;
						cout << tBattleMonster.strName << " 이 " << tPlayer.strName << " 에게 " << iDamage << "의 피해를 입혔습니다." << endl;

						//플레이어가 죽었을	경우
						if (tPlayer.iHP <= 0)
						{
							bPlayerAlive = 0; // 플레이어를 사망 상태로 변경
						}
						break;
					/*case B_ESCAPE:
						break;
					case B_DEFEND:
						break;*/
					default:
						cout << "메뉴를 잘못 선택하셨습니다." << endl;
						break;
					}
					if (bMonsterAlive == 0) {//몬스터 사망시
						cout << tBattleMonster.strName << "이 사망했습니다." << endl;
						tPlayer.iExp += tBattleMonster.iGetExp;
						tPlayer.tInventory.iGold += tBattleMonster.iGetGold;

						cout << tBattleMonster.iGetExp << "의 경험치를 획득했습니다." << endl;
						cout << tBattleMonster.iGetGold << "의 골드를 획득했습니다." << endl;

						system("pause");
						break;
					}
					else if (bPlayerAlive == 0) { // 플레이어 사망시
						cout << tPlayer.strName << "이 사망했습니다." << endl;
						cout << "전투에서 패배 했습니다." << endl;
						cout << (int)(tPlayer.tInventory.iGold * 0.1) << "의 골드를 잃었습니다." << endl;
						tPlayer.tInventory.iGold -= (int)(tPlayer.tInventory.iGold * 0.1);
						cout << tPlayer.tInventory.iGold << endl;
						system("pause");
						break;
					}
					system("pause");
				}
			
			}

			break;
		case MM_STORE:
			while (true) {
				system("cls");
				cout << "=================상점메뉴===================\t 보유골드 : " << tPlayer.tInventory.iGold << endl;
				cout << "1. 무기" << endl;
				cout << "2. 방어구" << endl;
				cout << "3. 팔기" << endl;
				cout << "4. 뒤로" << endl;
				cout << "메뉴를 선택 하세요 : ";
				cin >> iMenu;

				if (cin.fail()) {
					//에러버퍼를 비워준다.
					cin.clear();
					//입력 버퍼에 \n을 삭제 한다.
					cin.ignore(1024, '\n'); //넉넉하게 1024 바이트를 검사하여 \n을 지워준다.
					continue;
				}
				if (iMenu <= SM_NONE || iMenu > SM_BACK)
					continue;
				if (iMenu == SM_BACK) {
					break;
				}
				switch (iMenu) {
				case SM_WEAPON:
					while (true) {
						system("cls");
						cout << "=================무기상점===================\t 보유골드 : " << tPlayer.tInventory.iGold << endl;
						// 출력 방식 for 문으로 바꿔서 아이템을 추가 하면 더 팔 수 있도록 바꾼다 (개선사항) 
						cout << "1. " << tStoreWeaponArr[0].strName << " : " << tStoreWeaponArr[0].strDesc << " 가격 : " << tStoreWeaponArr[0].iPrice << endl;
						cout << "2. " << tStoreWeaponArr[1].strName << " : " << tStoreWeaponArr[1].strDesc << " 가격 : " << tStoreWeaponArr[1].iPrice << endl;
						cout << "3. " << tStoreWeaponArr[2].strName << " : " << tStoreWeaponArr[2].strDesc << " 가격 : " << tStoreWeaponArr[2].iPrice << endl;
						cout << "4. 뒤로" << endl;
						cout << "구매할 아이템을 선택 하세요 : ";
						cin >> iMenu;

						if (cin.fail()) {
							//에러버퍼를 비워준다.
							cin.clear();
							//입력 버퍼에 \n을 삭제 한다.
							cin.ignore(1024, '\n'); //넉넉하게 1024 바이트를 검사하여 \n을 지워준다.
							continue;
						}
						if (iMenu <= 0 || iMenu > STORE_MAX + 1)
							continue;
						if (iMenu == STORE_MAX + 1) {
							break;
						}
							if (tStoreWeaponArr[iMenu - 1].iPrice <= tPlayer.tInventory.iGold) {//돈이 가격 보다 많다면
								if (tPlayer.tInventory.iItemCount < INVENTORY_MAX) { //인벤토리가 꽉 차지 않았다면 구매한다.
									tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount] = tStoreWeaponArr[iMenu - 1];
									strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strName, tStoreWeaponArr[iMenu - 1].strName);
									strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strTypeName, tStoreWeaponArr[iMenu - 1].strTypeName);
									strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strDesc, tStoreWeaponArr[iMenu - 1].strDesc);
									++tPlayer.tInventory.iItemCount;
									tPlayer.tInventory.iGold -= tStoreWeaponArr[iMenu - 1].iPrice;
									cout << tStoreWeaponArr[iMenu - 1].strName << "을 구매 했습니다." << endl;
								}
								else
									cout << "가방이 꽉 찼습니다." << endl;
							}
							else
								cout << "골드가 부족합니다." << endl;
						system("pause");
					}
					break;
				case SM_ARMOR:
					while (true) {
						system("cls");
						cout << "=================방어구상점===================\t 보유골드 : " << tPlayer.tInventory.iGold << endl;
						cout << "1. " << tStoreArmorArr[0].strName << " : " << tStoreArmorArr[0].strDesc << " 가격 : " << tStoreArmorArr[0].iPrice << endl;
						cout << "2. " << tStoreArmorArr[1].strName << " : " << tStoreArmorArr[1].strDesc << " 가격 : " << tStoreArmorArr[1].iPrice << endl;
						cout << "3. " << tStoreArmorArr[2].strName << " : " << tStoreArmorArr[2].strDesc << " 가격 : " << tStoreArmorArr[2].iPrice << endl;
						cout << "4. 뒤로" << endl;
						cout << "구매할 아이템을 선택 하세요 : ";
						cin >> iMenu;

						if (cin.fail()) {
							//에러버퍼를 비워준다.
							cin.clear();
							//입력 버퍼에 \n을 삭제 한다.
							cin.ignore(1024, '\n'); //넉넉하게 1024 바이트를 검사하여 \n을 지워준다.
							continue;
						}
						if (iMenu <= 0 || iMenu > STORE_MAX + 1)
							continue;
						if (iMenu == STORE_MAX + 1) {
							break;
						}
						if (tStoreArmorArr[iMenu - 1].iPrice <= tPlayer.tInventory.iGold) {//돈이 가격 보다 많다면
							if (tPlayer.tInventory.iItemCount < INVENTORY_MAX) { //인벤토리가 꽉 차지 않았다면 구매한다.
								tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount] = tStoreArmorArr[iMenu - 1];
								strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strName, tStoreArmorArr[iMenu - 1].strName);
								strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strTypeName, tStoreArmorArr[iMenu - 1].strTypeName);
								strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strDesc, tStoreArmorArr[iMenu - 1].strDesc);
								++tPlayer.tInventory.iItemCount;
								tPlayer.tInventory.iGold -= tStoreArmorArr[iMenu - 1].iPrice;
								cout << tStoreArmorArr[iMenu - 1].strName << "을 구매 했습니다." << endl;
							}
							else
								cout << "가방이 꽉 찼습니다." << endl;
						}
						else
							cout << "골드가 부족합니다." << endl;
						system("pause");
					}
					break;
				case SM_SELL:
					while (true) {
						system("cls");
						cout << "=================판매===================\t 보유골드 : " << tPlayer.tInventory.iGold << endl;
						for (int i = 0; i < tPlayer.tInventory.iItemCount; ++i) {
							cout << i + 1 << ". " << "이름 : " << tPlayer.tInventory.tMyItemArr[i].strName << " : " << tPlayer.tInventory.tMyItemArr[i].strDesc << endl;
							cout << "분류 : " << tPlayer.tInventory.tMyItemArr[i].strTypeName <<
								", 성능 : " << tPlayer.tInventory.tMyItemArr[i].iStat << endl << "판매 가격 : " << tPlayer.tInventory.tMyItemArr[i].iSell << endl << endl << endl;
						}
						cout << tPlayer.tInventory.iItemCount + 1 << ". 뒤로" << endl;
						cout << "판매할 아이템을 선택 하세요 : ";
						cin >> iMenu;
						if (cin.fail()) {
							//에러버퍼를 비워준다.
							cin.clear();
							//입력 버퍼에 \n을 삭제 한다.
							cin.ignore(1024, '\n'); //넉넉하게 1024 바이트를 검사하여 \n을 지워준다.
							continue;
						}
						if (iMenu <= 0 || iMenu > tPlayer.tInventory.iItemCount + 1)
							continue;
						if (iMenu == tPlayer.tInventory.iItemCount + 1) {
							break;
						}
						for (int i = iMenu - 1; i < tPlayer.tInventory.iItemCount; ++i) { //판매한 아이템 뒤에 있는 아이템 들을 앞으로 한칸씩 옮긴다
							if (i == INVENTORY_MAX - 1) // 배열의 맨 끝 일 경우 뒤에 옮길 배열이 없다.
								break;
							tPlayer.tInventory.tMyItemArr[i] = tPlayer.tInventory.tMyItemArr[i + 1];
							strcpy_s(tPlayer.tInventory.tMyItemArr[i].strName, tPlayer.tInventory.tMyItemArr[i + 1].strName);
							strcpy_s(tPlayer.tInventory.tMyItemArr[i].strTypeName, tPlayer.tInventory.tMyItemArr[i + 1].strTypeName);
							strcpy_s(tPlayer.tInventory.tMyItemArr[i].strDesc, tPlayer.tInventory.tMyItemArr[i + 1].strDesc);
						}
						tPlayer.tInventory.iGold += tStoreArmorArr[iMenu - 1].iSell;  //판매 가격을 보유 골드에 추가 한다.
						cout << tStoreArmorArr[iMenu - 1].strName << "을 판매 했습니다." << endl;
						--tPlayer.tInventory.iItemCount; // 소지 아이템 수를 줄인다.
					}
					break;
				}
			}
			break;
		case MM_BAG:
			system("cls");
			cout << "=================가방===================" << endl;
			for (int i = 0; i < tPlayer.tInventory.iItemCount; ++i) {
				cout << i + 1 << ". " << "이름 : " << tPlayer.tInventory.tMyItemArr[i].strName << " : " << tPlayer.tInventory.tMyItemArr[i].strDesc << endl;
				cout << "분류 : " << tPlayer.tInventory.tMyItemArr[i].strTypeName <<
					 ", 성능 : " << tPlayer.tInventory.tMyItemArr[i].iStat << endl << "판매 가격 : " << tPlayer.tInventory.tMyItemArr[i].iSell << endl << endl << endl;
			}
			break;
		default:
			cout << "메뉴를 잘못 선택했습니다." << endl;
			break;
		}
		
		system("pause");
	}

	return 0;
}