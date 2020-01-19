
#include <iostream>

#include <time.h>

using namespace std;

#define NAME_SIZE 32
#define DESC_LENGTH 512
#define INVENTORY_MAX 20
#define STORE_MAX 3
#define LEVEL_MAX 10

enum MAIN_MANU
{
	MM_NONE,
	MM_BATTLE,
	MM_STORE,
	MM_BAG,
	MM_EXIT
};

enum MAP_TYPE
{
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum BATTLE
{
	B_NONE,
	B_ATTACK,
	B_BACK
};
enum JOB
{
	J_NONE,
	J_KNIGHT,
	J_ARCHER,
	J_WIZARD,
	J_END   // END값을 코드에 추가함으로써 직업을 나중에 추가 해도 다른 코드를 변경할 필요 없음
};
enum ITEM_TYPE
{
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};
enum STORE_MENU
{
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

struct _tagInventory
{
	_tagItem tMyItemArr[INVENTORY_MAX];
	int iItemCount;
	int iGold;
};

struct _tagPlayer
{
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
	bool bEquipWeapon;
	bool bEquipArmor;   //장착하지 않으면 0 장착하면 1
	_tagItem tEquipWeapon;
	_tagItem tEquipArmor;
	_tagInventory tInventory;
};

struct _tagLevelUpStatus
{
	int iAttackUp;
	int iArmorUp;
	int iHPUp;
	int iMPUp;
};

int CheckCin();
void PrintInfo(_tagPlayer, int);
void PrintInfo(_tagMonster);
int Attack(int, int, int, int*);
void LevelUPTableSet(_tagLevelUpStatus*);
void MonsterSet(_tagMonster*);
void StoreItemSet(_tagItem*, _tagItem*);
void PlayerSet(_tagPlayer*);
int MainMenu();
int BattleMenu();
int StoreMenu(int);
void BattleSet(int, _tagMonster*, _tagMonster*);
int Battle(_tagPlayer*, _tagMonster*, int, int);
void BattleResult(int, _tagPlayer*, int, _tagLevelUpStatus, _tagMonster);
int BuyMenu(int, int, _tagItem*);
void Buy(int*, int*, int, _tagItem*, _tagItem*);
int SellMenu(int, int, _tagItem*);
void Sell(int*, int*, int, _tagItem*);
void PrintEquipItem(bool, bool, _tagItem, _tagItem);
int EquipMenu(int, _tagItem*);
void DismountWeapon(_tagPlayer*);
void DismountArmor(_tagPlayer*);
void EquipItem(int ,_tagPlayer*);








int main() {

	//변수 선언
	int iMenu;
	_tagPlayer tPlayer = {};
	_tagMonster tMonsterArr[MT_BACK - 1] = {}; // 맵 단계당 몹 하나 MT_BACK - 1
	_tagMonster tBattleMonster = {};
	_tagItem tStoreWeaponArr[STORE_MAX] = {};
	_tagItem tStoreArmorArr[STORE_MAX] = {};
	_tagLevelUpStatus tLvUpTable[J_END - 1] = {};
	const int iLevelUpExp[LEVEL_MAX] = { 40, 100, 200, 500, 900, 1400, 2000, 3000, 4500, 6000 };	//레벨업에 필요한 경험치 설정



	srand((unsigned int)time(0));



	LevelUPTableSet(tLvUpTable);// 레벨업시 증가하는 스탯

	MonsterSet(tMonsterArr); //몬스터 정보

	StoreItemSet(tStoreWeaponArr, tStoreArmorArr);//상점에서 판매할 아이템 목록

	PlayerSet(&tPlayer);// 게임시작 시 플레이어 정보 설정


	while (true) {  //game loop

		iMenu = MainMenu();

		if (iMenu == -1)  // cin.fail
			continue;
		if (iMenu <= MM_NONE || iMenu > MM_EXIT)
			continue;
		if (iMenu == MM_EXIT) //종료
			break;
		switch (iMenu)
		{
		case MM_BATTLE:
			while (true)
			{
				iMenu = BattleMenu();
				if (iMenu == -1)  // cin.fail
					continue;
				if (iMenu <= MT_NONE || iMenu > MT_BACK)
					continue;
				if (iMenu == MT_BACK) {
					break;
				}

				BattleSet(iMenu, &tBattleMonster, tMonsterArr);
				tPlayer.iHP = tPlayer.iHPMax;
				tPlayer.iMP = tPlayer.iMPMax;
				int iResult = 3;
				while (true)
				{
					iResult = Battle(&tPlayer, &tBattleMonster, iLevelUpExp[tPlayer.iLevel - 1], iMenu);

					if (iResult == B_BACK)
						break;
					if (iResult == -1)
						continue;
					BattleResult(iResult, &tPlayer, iLevelUpExp[tPlayer.iLevel - 1], tLvUpTable[tPlayer.eJob - 1], tBattleMonster);
					break;
				}

			}

			break;
		case MM_STORE:
			while (true) {
				iMenu = StoreMenu(tPlayer.tInventory.iGold);
				if (iMenu == -1)  // cin.fail
					continue;
				if (iMenu <= SM_NONE || iMenu > SM_BACK)
					continue;
				if (iMenu == SM_BACK) {
					break;
				}
				switch (iMenu) {
				case SM_WEAPON:
					while (true) {
						iMenu = BuyMenu(tPlayer.tInventory.iGold, tPlayer.tInventory.iItemCount, tStoreWeaponArr);
						if (iMenu == -1)  // cin.fail
							continue;
						if (iMenu <= 0 || iMenu > STORE_MAX + 1)
							continue;
						if (iMenu == STORE_MAX + 1) {
							break;
						}
						Buy(&tPlayer.tInventory.iGold, &tPlayer.tInventory.iItemCount, iMenu, tStoreWeaponArr, tPlayer.tInventory.tMyItemArr);
						system("pause");
					}
					break;
				case SM_ARMOR:
					while (true) {
						iMenu = BuyMenu(tPlayer.tInventory.iGold, tPlayer.tInventory.iItemCount, tStoreArmorArr);
						if (iMenu == -1)  // cin.fail
							continue;
						if (iMenu <= 0 || iMenu > STORE_MAX + 1)
							continue;
						if (iMenu == STORE_MAX + 1) {
							break;
						}
						Buy(&tPlayer.tInventory.iGold, &tPlayer.tInventory.iItemCount, iMenu, tStoreArmorArr, tPlayer.tInventory.tMyItemArr);
						system("pause");
					}
					break;
				case SM_SELL:
					while (true) {
						iMenu = SellMenu(tPlayer.tInventory.iGold, tPlayer.tInventory.iItemCount, tPlayer.tInventory.tMyItemArr);
						if (iMenu == -1)  // cin.fail
							continue;
						if (iMenu <= 0 || iMenu > tPlayer.tInventory.iItemCount + 1)
							continue;
						if (iMenu == tPlayer.tInventory.iItemCount + 1) {
							break;
						}
						Sell(&tPlayer.tInventory.iGold, &tPlayer.tInventory.iItemCount, iMenu, tPlayer.tInventory.tMyItemArr);
						system("pause");
					}
					break;
				}
			}
			break;
		case MM_BAG:
			while (true) {
				system("cls");
				// Player info
				PrintInfo(tPlayer, iLevelUpExp[tPlayer.iLevel - 1]);
				//장착한 아이템 출력
				PrintEquipItem(tPlayer.bEquipWeapon, tPlayer.bEquipArmor, tPlayer.tEquipWeapon, tPlayer.tEquipArmor);

				// Inventory 아이템 출력
				iMenu = EquipMenu(tPlayer.tInventory.iItemCount, tPlayer.tInventory.tMyItemArr);
				if (iMenu <= 0 || iMenu > tPlayer.tInventory.iItemCount + 3)
					continue;
				else if (iMenu == tPlayer.tInventory.iItemCount + 3) 
					break;
				else if (iMenu == tPlayer.tInventory.iItemCount + 1) //무기해제
					DismountWeapon(&tPlayer);
				else if (iMenu == tPlayer.tInventory.iItemCount + 2) //방어구 해제
					DismountArmor(&tPlayer);
				else
					EquipItem(iMenu, &tPlayer);				
				system("pause");
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

//함수 구현부
int CheckCin()
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return -1;
	}
	return 0;
}

void PrintInfo(_tagPlayer tPlayer, int iLevelUpExp)
{
	cout << "****************Player****************" << endl;
	cout << "이름 : " << tPlayer.strName <<
		"\t직업 : " << tPlayer.strJob << endl;
	cout << "레벨 : " << tPlayer.iLevel <<
		"\t경험치 : " << tPlayer.iExp << "/" << iLevelUpExp << endl;
	cout << "공격력  : " << tPlayer.iAttackMin <<
		" - " << tPlayer.iAttackMax << "\t방어력 : " << tPlayer.iArmor << endl;
	cout << "체력 : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
		"\t마나 : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;
	cout << "보유골드 : " << tPlayer.tInventory.iGold << " 가방 칸 수 : " << tPlayer.tInventory.iItemCount << "/" << INVENTORY_MAX << endl << endl;
}

void PrintInfo(_tagMonster tMonster)
{
	cout << "****************Monster****************" << endl;
	cout << "이름 : " << tMonster.strName <<
		"\t레벨 : " << tMonster.iLevel << endl;
	cout << "공격력  : " << tMonster.iAttackMin <<
		" - " << tMonster.iAttackMax << "\t방어력 : " << tMonster.iArmor << endl;
	cout << "체력 : " << tMonster.iHP << " / " << tMonster.iHPMax <<
		"\t마나 : " << tMonster.iMP << " / " << tMonster.iMPMax << endl;
	cout << "획득 경험치 : " << tMonster.iGetExp <<
		"\t획득 골드 : " << tMonster.iGetGold << endl << endl;
}

int Attack(int iAttackMax, int iAttackMin, int iArmor, int* iHP)
{
	int iAttack = 0;
	int iDamage = 0;
	iAttack = rand() % (iAttackMax - iAttackMin + 1) + iAttackMin;
	iDamage = iAttack <= iArmor ? 1 : iAttack - iArmor;
	*iHP -= iDamage;
	return iDamage;
}

void LevelUPTableSet(_tagLevelUpStatus* ptArray)
{

	//레벨업시 증가 하는 스탯 선언

	ptArray[J_KNIGHT - 1].iAttackUp = 5;
	ptArray[J_KNIGHT - 1].iArmorUp = 10;
	ptArray[J_KNIGHT - 1].iHPUp = 55;
	ptArray[J_KNIGHT - 1].iMPUp = 10;

	ptArray[J_ARCHER - 1].iAttackUp = 8;
	ptArray[J_ARCHER - 1].iArmorUp = 5;
	ptArray[J_ARCHER - 1].iHPUp = 30;
	ptArray[J_ARCHER - 1].iMPUp = 30;

	ptArray[J_WIZARD - 1].iAttackUp = 11;
	ptArray[J_WIZARD - 1].iArmorUp = 3;
	ptArray[J_WIZARD - 1].iHPUp = 15;
	ptArray[J_WIZARD - 1].iMPUp = 50;

}

void MonsterSet(_tagMonster* ptArray)
{
	//몬스터 스탯 설정
	//easy 고블린
	strcpy_s(ptArray[0].strName, "고블린");
	ptArray[0].iArmor = 2;
	ptArray[0].iAttackMax = 5;
	ptArray[0].iAttackMin = 10;
	ptArray[0].iGetExp = 10;
	ptArray[0].iGetGold = 500;
	ptArray[0].iHPMax = 45;
	ptArray[0].iHP = ptArray[0].iHPMax;
	ptArray[0].iLevel = 1;
	ptArray[0].iMPMax = 10;
	ptArray[0].iMP = ptArray[0].iMPMax;

	//normal 오크
	strcpy_s(ptArray[1].strName, "오크");
	ptArray[1].iArmor = 30;
	ptArray[1].iAttackMax = 40;
	ptArray[1].iAttackMin = 30;
	ptArray[1].iGetExp = 100;
	ptArray[1].iGetGold = 4000;
	ptArray[1].iHPMax = 400;
	ptArray[1].iHP = ptArray[1].iHPMax;
	ptArray[1].iLevel = 10;
	ptArray[1].iMPMax = 30;
	ptArray[1].iMP = ptArray[1].iMPMax;

	//hard 오우거
	strcpy_s(ptArray[2].strName, "오우거");
	ptArray[2].iArmor = 100;
	ptArray[2].iAttackMax = 160;
	ptArray[2].iAttackMin = 150;
	ptArray[2].iGetExp = 1000;
	ptArray[2].iGetGold = 30000;
	ptArray[2].iHPMax = 2000;
	ptArray[2].iHP = ptArray[2].iHPMax;
	ptArray[2].iLevel = 80;
	ptArray[2].iMPMax = 100;
	ptArray[2].iMP = ptArray[2].iMPMax;
}

void StoreItemSet(_tagItem* ptWeaponArray, _tagItem* ptArmorArray)
{
	//상점에서 판매할 아이템 목록
	strcpy_s(ptWeaponArray[0].strName, "무딘 칼");
	strcpy_s(ptWeaponArray[0].strTypeName, "무기");
	strcpy_s(ptWeaponArray[0].strDesc, "날은 없지만 타격감이 좋다.");
	ptWeaponArray[0].eType = IT_WEAPON;
	ptWeaponArray[0].iPrice = 2000;
	ptWeaponArray[0].iSell = 1000;
	ptWeaponArray[0].iStat = 100;

	strcpy_s(ptWeaponArray[1].strName, "칼");
	strcpy_s(ptWeaponArray[1].strTypeName, "무기");
	strcpy_s(ptWeaponArray[1].strDesc, "날이 있어서 벨 수 있다.");
	ptWeaponArray[1].eType = IT_WEAPON;
	ptWeaponArray[1].iPrice = 10000;
	ptWeaponArray[1].iSell = 3000;
	ptWeaponArray[1].iStat = 50;

	strcpy_s(ptWeaponArray[2].strName, "날카로운 칼");
	strcpy_s(ptWeaponArray[2].strTypeName, "무기");
	strcpy_s(ptWeaponArray[2].strDesc, "날이 날카롭다.");
	ptWeaponArray[2].eType = IT_WEAPON;
	ptWeaponArray[2].iPrice = 100000;
	ptWeaponArray[2].iSell = 40000;
	ptWeaponArray[2].iStat = 200;

	strcpy_s(ptArmorArray[0].strName, "말랑한 갑옷");
	strcpy_s(ptArmorArray[0].strTypeName, "방어구");
	strcpy_s(ptArmorArray[0].strDesc, "말랑하다.");
	ptArmorArray[0].eType = IT_ARMOR;
	ptArmorArray[0].iPrice = 1000;
	ptArmorArray[0].iSell = 500;
	ptArmorArray[0].iStat = 10;

	strcpy_s(ptArmorArray[1].strName, "갑옷");
	strcpy_s(ptArmorArray[1].strTypeName, "방어구");
	strcpy_s(ptArmorArray[1].strDesc, "갑옷이다.");
	ptArmorArray[1].eType = IT_ARMOR;
	ptArmorArray[1].iPrice = 15000;
	ptArmorArray[1].iSell = 5000;
	ptArmorArray[1].iStat = 70;

	strcpy_s(ptArmorArray[2].strName, "단단한 갑옷");
	strcpy_s(ptArmorArray[2].strTypeName, "방어구");
	strcpy_s(ptArmorArray[2].strDesc, "단단하다.");
	ptArmorArray[2].eType = IT_ARMOR;
	ptArmorArray[2].iPrice = 90000;
	ptArmorArray[2].iSell = 35000;
	ptArmorArray[2].iStat = 130;
}

void PlayerSet(_tagPlayer* ptPlayer)
{
	// 게임시작 시 플레이어 정보 설정
	ptPlayer->iLevel = 1;
	ptPlayer->iExp = 0;
	ptPlayer->tInventory.iGold = 300000;
	cout << "이름 : ";
	cin.getline(ptPlayer->strName, NAME_SIZE - 1);
	int iJob = J_NONE;
	int Fail = 1;
	while (iJob == J_NONE)
	{
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		cin >> iJob;

		Fail = CheckCin();
		if (Fail == -1)
			continue;
		else if (iJob <= J_NONE || iJob >= J_END)
			iJob = J_NONE;
	}

	ptPlayer->eJob = (JOB)iJob;
	switch (ptPlayer->eJob)
	{
	case J_KNIGHT:
		strcpy_s(ptPlayer->strJob, "기사");
		ptPlayer->iArmor = 5;
		ptPlayer->iAttackMax = 10;
		ptPlayer->iAttackMin = 5;
		ptPlayer->iHPMax = 75;
		ptPlayer->iHP = ptPlayer->iHPMax;
		ptPlayer->iMPMax = 25;
		ptPlayer->iMP = ptPlayer->iMPMax;
		break;
	case J_ARCHER:
		strcpy_s(ptPlayer->strJob, "궁수");
		ptPlayer->iArmor = 3;
		ptPlayer->iAttackMax = 13;
		ptPlayer->iAttackMin = 7;
		ptPlayer->iHPMax = 60;
		ptPlayer->iHP = ptPlayer->iHPMax;
		ptPlayer->iMPMax = 35;
		ptPlayer->iMP = ptPlayer->iMPMax;
		break;
	case J_WIZARD:
		strcpy_s(ptPlayer->strJob, "마법사");
		ptPlayer->iArmor = 1;
		ptPlayer->iAttackMax = 17;
		ptPlayer->iAttackMin = 7;
		ptPlayer->iHPMax = 55;
		ptPlayer->iHP = ptPlayer->iHPMax;
		ptPlayer->iMPMax = 55;
		ptPlayer->iMP = ptPlayer->iMPMax;
		break;
	}
}

int MainMenu()
{
	int iSelMenu = 0;
	int Fail = 0;
	system("cls");
	cout << "=================메인메뉴==================" << endl;
	cout << "1. 전투" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 가방" << endl;
	cout << "4. 종료" << endl;
	cout << "메뉴를 선택 하세요 : ";
	cin >> iSelMenu;

	Fail = CheckCin();
	if (Fail == -1)
		iSelMenu = -1;
	return iSelMenu;
}

int BattleMenu()
{
	int iSelMenu = 0;
	int Fail = 0;
	system("cls");
	cout << "=================전투메뉴===================" << endl;
	cout << "1. 쉬움" << endl;
	cout << "2. 보통" << endl;
	cout << "3. 어려움" << endl;
	cout << "4. 뒤로" << endl;
	cout << "메뉴를 선택 하세요 : ";
	cin >> iSelMenu;

	Fail = CheckCin();
	if (Fail == -1)
		iSelMenu = -1;
	return iSelMenu;
}

int StoreMenu(int iGold)
{
	int iSelMenu = 0;
	int Fail = 0;
	system("cls");
	cout << "=================상점메뉴===================\t 보유골드 : " << iGold << endl;
	cout << "1. 무기" << endl;
	cout << "2. 방어구" << endl;
	cout << "3. 팔기" << endl;
	cout << "4. 뒤로" << endl;
	cout << "메뉴를 선택 하세요 : ";
	cin >> iSelMenu;

	Fail = CheckCin();
	if (Fail == -1)
		iSelMenu = -1;
	return iSelMenu;
}

void BattleSet(int iMenu, _tagMonster* ptBattleMonster, _tagMonster* ptMonsterArray)
{
	*ptBattleMonster = ptMonsterArray[iMenu - 1];
	strcpy_s(ptBattleMonster->strName, ptMonsterArray[iMenu - 1].strName);
}

int Battle(_tagPlayer* tPlayer, _tagMonster* tMonster, int iLevelUpExp, int iDifficulty)
{
	system("cls");
	switch (iDifficulty) {
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
	PrintInfo(*tPlayer, iLevelUpExp);
	// Monster info
	PrintInfo(*tMonster);

	int iSelMenu = 0;
	cout << "1. 공격" << endl;
	cout << "2. 도망" << endl;
	cout << "메뉴를 선택 하세요." << endl;
	cin >> iSelMenu;

	int Fail = 0;
	Fail = CheckCin();
	if (Fail == -1)
		return -1;

	int iDamage = 0;
	switch (iSelMenu) {
	case B_ATTACK:
		iDamage = Attack(tPlayer->iAttackMax, tPlayer->iAttackMin, tMonster->iArmor, &tMonster->iHP);
		cout << tPlayer->strName << " 이 " << tMonster->strName << " 에게 " << iDamage << "의 피해를 입혔습니다." << endl;

		//몬스터가 죽었을 경우
		if (tMonster->iHP <= 0)
			return 0;// 몬스터  사망

//몬스터가 살아 있다면 플레이어를 공격한다.
		iDamage = Attack(tMonster->iAttackMax, tMonster->iAttackMin, tPlayer->iArmor, &tPlayer->iHP);
		cout << tMonster->strName << " 이 " << tPlayer->strName << " 에게 " << iDamage << "의 피해를 입혔습니다." << endl;

		//플레이어가 죽었을	경우
		if (tPlayer->iHP <= 0)
		{
			return 1; // 플레이어 사망
		}
		system("pause");
		break;
	case B_BACK:
		return iSelMenu;
	default:
		cout << "메뉴를 잘못 선택하셨습니다." << endl;
		system("pause");
		return -1;
	}
	return -1;
}

void BattleResult(int iResult, _tagPlayer* ptPlayer, int iLevelUpExp, _tagLevelUpStatus tLevelUpStatus, _tagMonster tMonster)
{
	if (iResult == 0) {//몬스터 사망시
		cout << tMonster.strName << "이 사망했습니다." << endl;
		ptPlayer->iExp += tMonster.iGetExp;
		ptPlayer->tInventory.iGold += tMonster.iGetGold;

		cout << tMonster.iGetExp << "의 경험치를 획득했습니다." << endl;
		cout << tMonster.iGetGold << "의 골드를 획득했습니다." << endl;

		if (ptPlayer->iExp >= iLevelUpExp) {
			//필요한 경험치 만큼 경험치를 차감한다.
			ptPlayer->iExp -= iLevelUpExp;
			//레벨을 증가시킨다.
			++ptPlayer->iLevel;
			cout << "레벨업 하였습니다." << endl;

			//레벨업 스탯을 올려준다.
			ptPlayer->iAttackMax += tLevelUpStatus.iAttackUp;
			ptPlayer->iAttackMin += tLevelUpStatus.iAttackUp;
			ptPlayer->iArmor += tLevelUpStatus.iArmorUp;
			ptPlayer->iHPMax += tLevelUpStatus.iHPUp;
			ptPlayer->iMPMax += tLevelUpStatus.iMPUp;

			cout << "공격이 " << tLevelUpStatus.iAttackUp << " 올랐습니다." << endl;
			cout << "방어가 " << tLevelUpStatus.iArmorUp << " 올랐습니다." << endl;
			cout << "체력이 " << tLevelUpStatus.iHPUp << " 올랐습니다." << endl;
			cout << "마나가 " << tLevelUpStatus.iMPUp << " 올랐습니다." << endl;
		}

		system("pause");
	}
	else if (iResult == 1) { // 플레이어 사망시
		cout << ptPlayer->strName << "이 사망했습니다." << endl;
		cout << "전투에서 패배 했습니다." << endl;
		cout << (int)(ptPlayer->tInventory.iGold * 0.1) << "의 골드를 잃었습니다." << endl;
		ptPlayer->tInventory.iGold -= (int)(ptPlayer->tInventory.iGold * 0.1);
		system("pause");
	}
}

int BuyMenu(int iGold, int iItemCount, _tagItem* ptStoreItemArr)
{
	int iSelMenu = 0;
	int Fail = 0;
	system("cls");
	cout << "=================" << ptStoreItemArr[0].strTypeName << "상점===================\t 보유골드 : " << iGold <<
		"가방 칸 수 : " << iItemCount << "/" << INVENTORY_MAX << endl;
	for (int i = 0; i < STORE_MAX; ++i) {
		cout << i + 1 << ". " << ptStoreItemArr[i].strName << " : " << ptStoreItemArr[i].strDesc << endl <<
			"가격 : " << ptStoreItemArr[i].iPrice << endl << endl;
	}
	cout << STORE_MAX + 1 << ". 뒤로" << endl;
	cout << "구매할 아이템을 선택 하세요 : ";
	cin >> iSelMenu;

	Fail = CheckCin();
	if (Fail == -1)
		iSelMenu = -1;
	return iSelMenu;
}

void Buy(int* iGold, int* iItemCount, int iMenu, _tagItem* ptStoreItemArr, _tagItem* ptPlayreItemArr)
{
	if (ptStoreItemArr[iMenu - 1].iPrice <= *iGold) {//돈이 가격 보다 많다면
		if (*iItemCount < INVENTORY_MAX) { //인벤토리가 꽉 차지 않았다면 구매한다.
			ptPlayreItemArr[*iItemCount] = ptStoreItemArr[iMenu - 1];
			strcpy_s(ptPlayreItemArr[*iItemCount].strName, ptStoreItemArr[iMenu - 1].strName);
			strcpy_s(ptPlayreItemArr[*iItemCount].strTypeName, ptStoreItemArr[iMenu - 1].strTypeName);
			strcpy_s(ptPlayreItemArr[*iItemCount].strDesc, ptStoreItemArr[iMenu - 1].strDesc);
			++* iItemCount;
			*iGold -= ptStoreItemArr[iMenu - 1].iPrice;
			cout << ptStoreItemArr[iMenu - 1].strName << "을 구매 했습니다." << endl;
		}
		else
			cout << "가방이 꽉 찼습니다." << endl;
	}
	else
		cout << "골드가 부족합니다." << endl;
}

int SellMenu(int iGold, int iItemCount, _tagItem* ptPlayreItemArr)
{
	int iSelMenu = 0;
	int Fail = 0;
	system("cls");
	cout << "=================판매===================\t 보유골드 : " << iGold <<
		"가방 칸 수 : " << iItemCount << "/" << INVENTORY_MAX << endl;
	for (int i = 0; i < iItemCount; ++i) {
		cout << i + 1 << ". 이름 : " << ptPlayreItemArr[i].strName << " : " << ptPlayreItemArr[i].strDesc << endl;
		cout << "분류 : " << ptPlayreItemArr[i].strTypeName <<
			", 성능 : " << ptPlayreItemArr[i].iStat << endl << "판매 가격 : " << ptPlayreItemArr[i].iSell << endl << endl << endl;
	}
	cout << iItemCount + 1 << ". 뒤로" << endl;
	cout << "판매할 아이템을 선택 하세요 : ";
	cin >> iSelMenu;

	Fail = CheckCin();
	if (Fail == -1)
		iSelMenu = -1;
	return iSelMenu;
}

void Sell(int* iGold, int* iItemCount, int iMenu, _tagItem* ptPlayreItemArr)
{
	*iGold += ptPlayreItemArr[iMenu - 1].iSell;  //판매 가격을 보유 골드에 추가 한다.
	cout << ptPlayreItemArr[iMenu - 1].strName << "을 판매 했습니다." << endl;
	for (int i = iMenu - 1; i < *iItemCount; ++i) { //판매한 아이템 뒤에 있는 아이템 들을 앞으로 한칸씩 옮긴다
		if (i == INVENTORY_MAX - 1) // 배열의 맨 끝 일 경우 뒤에 옮길 배열이 없다.
			break;
		ptPlayreItemArr[i] = ptPlayreItemArr[i + 1];
		strcpy_s(ptPlayreItemArr[i].strName, ptPlayreItemArr[i + 1].strName);
		strcpy_s(ptPlayreItemArr[i].strTypeName, ptPlayreItemArr[i + 1].strTypeName);
		strcpy_s(ptPlayreItemArr[i].strDesc, ptPlayreItemArr[i + 1].strDesc);
	}
	--* iItemCount; // 소지 아이템 수를 줄인다.
}

void PrintEquipItem(bool bEqWeapon, bool bEqArmor, _tagItem tEqWeapon, _tagItem tEqArmor)
{
	if (bEqWeapon) {
		cout << "착용 중인 무기 : " << "이름 : " << tEqWeapon.strName << " : " << tEqWeapon.strDesc << endl;
		cout << "분류 : " << tEqWeapon.strTypeName << ", 성능 : " << tEqWeapon.iStat << endl;
	}
	if (bEqArmor) {
		cout << "착용 중인 방어구 : " << "이름 : " << tEqArmor.strName << " : " << tEqArmor.strDesc << endl;
		cout << "분류 : " << tEqArmor.strTypeName << ", 성능 : " << tEqArmor.iStat << endl << endl;
	}

}

int EquipMenu(int iItemCount, _tagItem* ptItemArr)
{
	int iSelMenu = 0;
	int Fail = 0;
	cout << "=================가방===================" << endl;
	for (int i = 0; i < iItemCount; ++i) {
		cout << i + 1 << ". " << "이름 : " << ptItemArr[i].strName << " : " << ptItemArr[i].strDesc << endl;
		cout << "분류 : " << ptItemArr[i].strTypeName <<
			", 성능 : " << ptItemArr[i].iStat << endl << "판매 가격 : " << ptItemArr[i].iSell << endl << endl << endl;
	}
	cout << iItemCount + 1 << ". 장착된 무기 해제" << endl;
	cout << iItemCount + 2 << ". 장착된 방어구 해제" << endl;
	cout << iItemCount + 3 << ". 뒤로" << endl;
	cout << "장착할 아이템을 선택 하세요 : ";
	cin >> iSelMenu;
	Fail = CheckCin();
	if (Fail == -1)
		iSelMenu = Fail;
	return iSelMenu;
}

void DismountWeapon(_tagPlayer* ptPlayer)
{
	//착용된 무기가 있는지 확인한다.
	if (ptPlayer->bEquipWeapon) {
		if (ptPlayer->tInventory.iItemCount < INVENTORY_MAX) {
			//장착된 무기를 해제한다.  공격력을 낮춘다.
			ptPlayer->bEquipWeapon = 0;
			ptPlayer->iAttackMax -= ptPlayer->tEquipWeapon.iStat;
			ptPlayer->iAttackMin -= ptPlayer->tEquipWeapon.iStat;
			//해제한 아이템을 내 인벤토리에 넣는다
			ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount] = ptPlayer->tEquipWeapon;
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strName, ptPlayer->tEquipWeapon.strName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strTypeName, ptPlayer->tEquipWeapon.strTypeName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strDesc, ptPlayer->tEquipWeapon.strDesc);
			++ptPlayer->tInventory.iItemCount;
			cout << ptPlayer->tEquipWeapon.strName << "을 해제 했습니다." << endl;
		}
		else
			cout << "가방이 꽉 찼습니다." << endl;
	}
	else
		cout << "장착된 무기가 없습니다." << endl;
}

void DismountArmor(_tagPlayer* ptPlayer)
{
	//착용된 아이템이 있는지 확인한다.
	if (ptPlayer->bEquipArmor) {
		if (ptPlayer->tInventory.iItemCount < INVENTORY_MAX) {
			//장착된 아이템을 해제한다.  방어력을 낮춘다.
			ptPlayer->bEquipArmor = 0;
			ptPlayer->iArmor -= ptPlayer->tEquipArmor.iStat;
			//해제한 아이템을 내 인벤토리에 넣는다
			ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount] = ptPlayer->tEquipArmor;
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strName, ptPlayer->tEquipArmor.strName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strTypeName, ptPlayer->tEquipArmor.strTypeName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strDesc, ptPlayer->tEquipArmor.strDesc);
			++ptPlayer->tInventory.iItemCount;
			cout << ptPlayer->tEquipArmor.strName << "을 해제 했습니다." << endl;
		}
		else
			cout << "가방이 꽉 찼습니다." << endl;
	}
	else
		cout << "장착된 방어구가 없습니다." << endl;

}

void EquipItem(int iMenu ,_tagPlayer* ptPlayer)
{
	_tagItem tItemSwap = {};
	if(ptPlayer->tInventory.tMyItemArr[iMenu - 1].eType == IT_WEAPON) {
		if (ptPlayer->bEquipWeapon)					//만약있다면 swap알고리즘으로 교체한다.
		{
			cout << "무기를 장착하고 있습니다. 장착 중인 무기와 선택한 무기를 교체 합니다." << endl;
			system("pause");
			ptPlayer->iAttackMax -= ptPlayer->tEquipWeapon.iStat; //해제할 무기의 공격력을 낮춘다.
			ptPlayer->iAttackMin -= ptPlayer->tEquipWeapon.iStat;

			tItemSwap = ptPlayer->tEquipWeapon;      //해제할 아이템 swap용 변수에 저장
			strcpy_s(tItemSwap.strName, ptPlayer->tEquipWeapon.strName);
			strcpy_s(tItemSwap.strTypeName, ptPlayer->tEquipWeapon.strTypeName);
			strcpy_s(tItemSwap.strDesc, ptPlayer->tEquipWeapon.strDesc);

			ptPlayer->tEquipWeapon = ptPlayer->tInventory.tMyItemArr[iMenu - 1];
			strcpy_s(ptPlayer->tEquipWeapon.strName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName);
			strcpy_s(ptPlayer->tEquipWeapon.strTypeName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strTypeName);
			strcpy_s(ptPlayer->tEquipWeapon.strDesc, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strDesc);

			ptPlayer->tInventory.tMyItemArr[iMenu - 1] = tItemSwap;
			strcpy_s(ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName, tItemSwap.strName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[iMenu - 1].strTypeName, tItemSwap.strTypeName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[iMenu - 1].strDesc, tItemSwap.strDesc);

			ptPlayer->iAttackMax += ptPlayer->tEquipWeapon.iStat; //장착한 무기의 공격력을 높인다.
			ptPlayer->iAttackMin += ptPlayer->tEquipWeapon.iStat;

			cout << ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName << "을 해제하고, " << ptPlayer->tEquipWeapon.strName << "을 장착했습니다." << endl;
		}
		else //장착하고 있는 아이템이 없을 경우 선택한 아이템을 장착 한다.
		{
			//장착하고, 공격력을 올린다.
			ptPlayer->bEquipWeapon = 1;
			ptPlayer->tEquipWeapon = ptPlayer->tInventory.tMyItemArr[iMenu - 1];
			strcpy_s(ptPlayer->tEquipWeapon.strName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName);
			strcpy_s(ptPlayer->tEquipWeapon.strTypeName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strTypeName);
			strcpy_s(ptPlayer->tEquipWeapon.strDesc, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strDesc);
			ptPlayer->iAttackMax += ptPlayer->tEquipWeapon.iStat;
			ptPlayer->iAttackMin += ptPlayer->tEquipWeapon.iStat;

			for (int i = iMenu - 1; i < ptPlayer->tInventory.iItemCount; ++i) { //장착한 아이템 뒤에 있는 아이템 들을 앞으로 한칸씩 옮긴다
				if (i == INVENTORY_MAX - 1) // 배열의 맨 끝 일 경우 뒤에 옮길 배열이 없다.
					break;
				ptPlayer->tInventory.tMyItemArr[i] = ptPlayer->tInventory.tMyItemArr[i + 1];
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strName, ptPlayer->tInventory.tMyItemArr[i + 1].strName);
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strTypeName, ptPlayer->tInventory.tMyItemArr[i + 1].strTypeName);
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strDesc, ptPlayer->tInventory.tMyItemArr[i + 1].strDesc);
			}
			--ptPlayer->tInventory.iItemCount; // 소지 아이템 수를 줄인다.
			cout << ptPlayer->tEquipWeapon.strName << "을 장착 했습니다." << endl;


		}
	}// 무기 장착 끝
	else if (ptPlayer->tInventory.tMyItemArr[iMenu - 1].eType == IT_ARMOR) {
		if (ptPlayer->bEquipArmor)					//만약있다면 swap알고리즘으로 교체한다.
		{
			cout << "방어구를 장착하고 있습니다. 장착 중인 방어구와 선택한 방어구를 교체 합니다." << endl;
			system("pause");
			ptPlayer->iArmor -= ptPlayer->tEquipArmor.iStat; //해제할 방어구의 방어력을 낮춘다.

			tItemSwap = ptPlayer->tEquipArmor;      //해제할 아이템 swap용 변수에 저장
			strcpy_s(tItemSwap.strName, ptPlayer->tEquipArmor.strName);
			strcpy_s(tItemSwap.strTypeName, ptPlayer->tEquipArmor.strTypeName);
			strcpy_s(tItemSwap.strDesc, ptPlayer->tEquipArmor.strDesc);

			ptPlayer->tEquipArmor = ptPlayer->tInventory.tMyItemArr[iMenu - 1];
			strcpy_s(ptPlayer->tEquipArmor.strName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName);
			strcpy_s(ptPlayer->tEquipArmor.strTypeName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strTypeName);
			strcpy_s(ptPlayer->tEquipArmor.strDesc, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strDesc);

			ptPlayer->tInventory.tMyItemArr[iMenu - 1] = tItemSwap;
			strcpy_s(ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName, tItemSwap.strName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[iMenu - 1].strTypeName, tItemSwap.strTypeName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[iMenu - 1].strDesc, tItemSwap.strDesc);

			ptPlayer->iArmor += ptPlayer->tEquipArmor.iStat; //장착한 무기의 공격력을 높인다.

			cout << ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName << "을 해제하고, " << ptPlayer->tEquipArmor.strName << "을 장착했습니다." << endl;
		}
		else					//장착하고 있는 아이템이 없을 경우 선택한 아이템을 장착 한다.
		{
			//장착하고, 방어력을 올린다.
			ptPlayer->bEquipArmor = 1;
			ptPlayer->tEquipArmor = ptPlayer->tInventory.tMyItemArr[iMenu - 1];
			strcpy_s(ptPlayer->tEquipArmor.strName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName);
			strcpy_s(ptPlayer->tEquipArmor.strTypeName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strTypeName);
			strcpy_s(ptPlayer->tEquipArmor.strDesc, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strDesc);
			ptPlayer->iArmor += ptPlayer->tEquipArmor.iStat;

			for (int i = iMenu - 1; i < ptPlayer->tInventory.iItemCount; ++i) { //장착한 아이템 뒤에 있는 아이템 들을 앞으로 한칸씩 옮긴다
				if (i == INVENTORY_MAX - 1) // 배열의 맨 끝 일 경우 뒤에 옮길 배열이 없다.
					break;
				ptPlayer->tInventory.tMyItemArr[i] = ptPlayer->tInventory.tMyItemArr[i + 1];
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strName, ptPlayer->tInventory.tMyItemArr[i + 1].strName);
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strTypeName, ptPlayer->tInventory.tMyItemArr[i + 1].strTypeName);
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strDesc, ptPlayer->tInventory.tMyItemArr[i + 1].strDesc);
			}
			--ptPlayer->tInventory.iItemCount; // 소지 아이템 수를 줄인다.
			cout << ptPlayer->tEquipArmor.strName << "을 장착 했습니다." << endl;
		}
	}
}