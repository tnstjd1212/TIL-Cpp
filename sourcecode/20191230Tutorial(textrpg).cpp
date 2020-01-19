
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
	J_END   // END���� �ڵ忡 �߰������ν� ������ ���߿� �߰� �ص� �ٸ� �ڵ带 ������ �ʿ� ����
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
	char strDesc[DESC_LENGTH]; //������ ����
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
	bool bEquipArmor;   //�������� ������ 0 �����ϸ� 1
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

	//���� ����
	int iMenu;
	_tagPlayer tPlayer = {};
	_tagMonster tMonsterArr[MT_BACK - 1] = {}; // �� �ܰ�� �� �ϳ� MT_BACK - 1
	_tagMonster tBattleMonster = {};
	_tagItem tStoreWeaponArr[STORE_MAX] = {};
	_tagItem tStoreArmorArr[STORE_MAX] = {};
	_tagLevelUpStatus tLvUpTable[J_END - 1] = {};
	const int iLevelUpExp[LEVEL_MAX] = { 40, 100, 200, 500, 900, 1400, 2000, 3000, 4500, 6000 };	//�������� �ʿ��� ����ġ ����



	srand((unsigned int)time(0));



	LevelUPTableSet(tLvUpTable);// �������� �����ϴ� ����

	MonsterSet(tMonsterArr); //���� ����

	StoreItemSet(tStoreWeaponArr, tStoreArmorArr);//�������� �Ǹ��� ������ ���

	PlayerSet(&tPlayer);// ���ӽ��� �� �÷��̾� ���� ����


	while (true) {  //game loop

		iMenu = MainMenu();

		if (iMenu == -1)  // cin.fail
			continue;
		if (iMenu <= MM_NONE || iMenu > MM_EXIT)
			continue;
		if (iMenu == MM_EXIT) //����
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
				//������ ������ ���
				PrintEquipItem(tPlayer.bEquipWeapon, tPlayer.bEquipArmor, tPlayer.tEquipWeapon, tPlayer.tEquipArmor);

				// Inventory ������ ���
				iMenu = EquipMenu(tPlayer.tInventory.iItemCount, tPlayer.tInventory.tMyItemArr);
				if (iMenu <= 0 || iMenu > tPlayer.tInventory.iItemCount + 3)
					continue;
				else if (iMenu == tPlayer.tInventory.iItemCount + 3) 
					break;
				else if (iMenu == tPlayer.tInventory.iItemCount + 1) //��������
					DismountWeapon(&tPlayer);
				else if (iMenu == tPlayer.tInventory.iItemCount + 2) //�� ����
					DismountArmor(&tPlayer);
				else
					EquipItem(iMenu, &tPlayer);				
				system("pause");
			}
			break;
		default:
			cout << "�޴��� �߸� �����߽��ϴ�." << endl;
			break;
		}
				system("pause");
	}

	return 0;
}

//�Լ� ������
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
	cout << "�̸� : " << tPlayer.strName <<
		"\t���� : " << tPlayer.strJob << endl;
	cout << "���� : " << tPlayer.iLevel <<
		"\t����ġ : " << tPlayer.iExp << "/" << iLevelUpExp << endl;
	cout << "���ݷ�  : " << tPlayer.iAttackMin <<
		" - " << tPlayer.iAttackMax << "\t���� : " << tPlayer.iArmor << endl;
	cout << "ü�� : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
		"\t���� : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;
	cout << "������� : " << tPlayer.tInventory.iGold << " ���� ĭ �� : " << tPlayer.tInventory.iItemCount << "/" << INVENTORY_MAX << endl << endl;
}

void PrintInfo(_tagMonster tMonster)
{
	cout << "****************Monster****************" << endl;
	cout << "�̸� : " << tMonster.strName <<
		"\t���� : " << tMonster.iLevel << endl;
	cout << "���ݷ�  : " << tMonster.iAttackMin <<
		" - " << tMonster.iAttackMax << "\t���� : " << tMonster.iArmor << endl;
	cout << "ü�� : " << tMonster.iHP << " / " << tMonster.iHPMax <<
		"\t���� : " << tMonster.iMP << " / " << tMonster.iMPMax << endl;
	cout << "ȹ�� ����ġ : " << tMonster.iGetExp <<
		"\tȹ�� ��� : " << tMonster.iGetGold << endl << endl;
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

	//�������� ���� �ϴ� ���� ����

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
	//���� ���� ����
	//easy ���
	strcpy_s(ptArray[0].strName, "���");
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

	//normal ��ũ
	strcpy_s(ptArray[1].strName, "��ũ");
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

	//hard �����
	strcpy_s(ptArray[2].strName, "�����");
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
	//�������� �Ǹ��� ������ ���
	strcpy_s(ptWeaponArray[0].strName, "���� Į");
	strcpy_s(ptWeaponArray[0].strTypeName, "����");
	strcpy_s(ptWeaponArray[0].strDesc, "���� ������ Ÿ�ݰ��� ����.");
	ptWeaponArray[0].eType = IT_WEAPON;
	ptWeaponArray[0].iPrice = 2000;
	ptWeaponArray[0].iSell = 1000;
	ptWeaponArray[0].iStat = 100;

	strcpy_s(ptWeaponArray[1].strName, "Į");
	strcpy_s(ptWeaponArray[1].strTypeName, "����");
	strcpy_s(ptWeaponArray[1].strDesc, "���� �־ �� �� �ִ�.");
	ptWeaponArray[1].eType = IT_WEAPON;
	ptWeaponArray[1].iPrice = 10000;
	ptWeaponArray[1].iSell = 3000;
	ptWeaponArray[1].iStat = 50;

	strcpy_s(ptWeaponArray[2].strName, "��ī�ο� Į");
	strcpy_s(ptWeaponArray[2].strTypeName, "����");
	strcpy_s(ptWeaponArray[2].strDesc, "���� ��ī�Ӵ�.");
	ptWeaponArray[2].eType = IT_WEAPON;
	ptWeaponArray[2].iPrice = 100000;
	ptWeaponArray[2].iSell = 40000;
	ptWeaponArray[2].iStat = 200;

	strcpy_s(ptArmorArray[0].strName, "������ ����");
	strcpy_s(ptArmorArray[0].strTypeName, "��");
	strcpy_s(ptArmorArray[0].strDesc, "�����ϴ�.");
	ptArmorArray[0].eType = IT_ARMOR;
	ptArmorArray[0].iPrice = 1000;
	ptArmorArray[0].iSell = 500;
	ptArmorArray[0].iStat = 10;

	strcpy_s(ptArmorArray[1].strName, "����");
	strcpy_s(ptArmorArray[1].strTypeName, "��");
	strcpy_s(ptArmorArray[1].strDesc, "�����̴�.");
	ptArmorArray[1].eType = IT_ARMOR;
	ptArmorArray[1].iPrice = 15000;
	ptArmorArray[1].iSell = 5000;
	ptArmorArray[1].iStat = 70;

	strcpy_s(ptArmorArray[2].strName, "�ܴ��� ����");
	strcpy_s(ptArmorArray[2].strTypeName, "��");
	strcpy_s(ptArmorArray[2].strDesc, "�ܴ��ϴ�.");
	ptArmorArray[2].eType = IT_ARMOR;
	ptArmorArray[2].iPrice = 90000;
	ptArmorArray[2].iSell = 35000;
	ptArmorArray[2].iStat = 130;
}

void PlayerSet(_tagPlayer* ptPlayer)
{
	// ���ӽ��� �� �÷��̾� ���� ����
	ptPlayer->iLevel = 1;
	ptPlayer->iExp = 0;
	ptPlayer->tInventory.iGold = 300000;
	cout << "�̸� : ";
	cin.getline(ptPlayer->strName, NAME_SIZE - 1);
	int iJob = J_NONE;
	int Fail = 1;
	while (iJob == J_NONE)
	{
		system("cls");
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";
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
		strcpy_s(ptPlayer->strJob, "���");
		ptPlayer->iArmor = 5;
		ptPlayer->iAttackMax = 10;
		ptPlayer->iAttackMin = 5;
		ptPlayer->iHPMax = 75;
		ptPlayer->iHP = ptPlayer->iHPMax;
		ptPlayer->iMPMax = 25;
		ptPlayer->iMP = ptPlayer->iMPMax;
		break;
	case J_ARCHER:
		strcpy_s(ptPlayer->strJob, "�ü�");
		ptPlayer->iArmor = 3;
		ptPlayer->iAttackMax = 13;
		ptPlayer->iAttackMin = 7;
		ptPlayer->iHPMax = 60;
		ptPlayer->iHP = ptPlayer->iHPMax;
		ptPlayer->iMPMax = 35;
		ptPlayer->iMP = ptPlayer->iMPMax;
		break;
	case J_WIZARD:
		strcpy_s(ptPlayer->strJob, "������");
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
	cout << "=================���θ޴�==================" << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "3. ����" << endl;
	cout << "4. ����" << endl;
	cout << "�޴��� ���� �ϼ��� : ";
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
	cout << "=================�����޴�===================" << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "3. �����" << endl;
	cout << "4. �ڷ�" << endl;
	cout << "�޴��� ���� �ϼ��� : ";
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
	cout << "=================�����޴�===================\t ������� : " << iGold << endl;
	cout << "1. ����" << endl;
	cout << "2. ��" << endl;
	cout << "3. �ȱ�" << endl;
	cout << "4. �ڷ�" << endl;
	cout << "�޴��� ���� �ϼ��� : ";
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
		cout << "=================����===================" << endl;
		break;
	case MT_NORMAL:
		cout << "=================����===================" << endl;
		break;
	case MT_HARD:
		cout << "=================�����===================" << endl;
		break;
	}
	// Player info
	PrintInfo(*tPlayer, iLevelUpExp);
	// Monster info
	PrintInfo(*tMonster);

	int iSelMenu = 0;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "�޴��� ���� �ϼ���." << endl;
	cin >> iSelMenu;

	int Fail = 0;
	Fail = CheckCin();
	if (Fail == -1)
		return -1;

	int iDamage = 0;
	switch (iSelMenu) {
	case B_ATTACK:
		iDamage = Attack(tPlayer->iAttackMax, tPlayer->iAttackMin, tMonster->iArmor, &tMonster->iHP);
		cout << tPlayer->strName << " �� " << tMonster->strName << " ���� " << iDamage << "�� ���ظ� �������ϴ�." << endl;

		//���Ͱ� �׾��� ���
		if (tMonster->iHP <= 0)
			return 0;// ����  ���

//���Ͱ� ��� �ִٸ� �÷��̾ �����Ѵ�.
		iDamage = Attack(tMonster->iAttackMax, tMonster->iAttackMin, tPlayer->iArmor, &tPlayer->iHP);
		cout << tMonster->strName << " �� " << tPlayer->strName << " ���� " << iDamage << "�� ���ظ� �������ϴ�." << endl;

		//�÷��̾ �׾���	���
		if (tPlayer->iHP <= 0)
		{
			return 1; // �÷��̾� ���
		}
		system("pause");
		break;
	case B_BACK:
		return iSelMenu;
	default:
		cout << "�޴��� �߸� �����ϼ̽��ϴ�." << endl;
		system("pause");
		return -1;
	}
	return -1;
}

void BattleResult(int iResult, _tagPlayer* ptPlayer, int iLevelUpExp, _tagLevelUpStatus tLevelUpStatus, _tagMonster tMonster)
{
	if (iResult == 0) {//���� �����
		cout << tMonster.strName << "�� ����߽��ϴ�." << endl;
		ptPlayer->iExp += tMonster.iGetExp;
		ptPlayer->tInventory.iGold += tMonster.iGetGold;

		cout << tMonster.iGetExp << "�� ����ġ�� ȹ���߽��ϴ�." << endl;
		cout << tMonster.iGetGold << "�� ��带 ȹ���߽��ϴ�." << endl;

		if (ptPlayer->iExp >= iLevelUpExp) {
			//�ʿ��� ����ġ ��ŭ ����ġ�� �����Ѵ�.
			ptPlayer->iExp -= iLevelUpExp;
			//������ ������Ų��.
			++ptPlayer->iLevel;
			cout << "������ �Ͽ����ϴ�." << endl;

			//������ ������ �÷��ش�.
			ptPlayer->iAttackMax += tLevelUpStatus.iAttackUp;
			ptPlayer->iAttackMin += tLevelUpStatus.iAttackUp;
			ptPlayer->iArmor += tLevelUpStatus.iArmorUp;
			ptPlayer->iHPMax += tLevelUpStatus.iHPUp;
			ptPlayer->iMPMax += tLevelUpStatus.iMPUp;

			cout << "������ " << tLevelUpStatus.iAttackUp << " �ö����ϴ�." << endl;
			cout << "�� " << tLevelUpStatus.iArmorUp << " �ö����ϴ�." << endl;
			cout << "ü���� " << tLevelUpStatus.iHPUp << " �ö����ϴ�." << endl;
			cout << "������ " << tLevelUpStatus.iMPUp << " �ö����ϴ�." << endl;
		}

		system("pause");
	}
	else if (iResult == 1) { // �÷��̾� �����
		cout << ptPlayer->strName << "�� ����߽��ϴ�." << endl;
		cout << "�������� �й� �߽��ϴ�." << endl;
		cout << (int)(ptPlayer->tInventory.iGold * 0.1) << "�� ��带 �Ҿ����ϴ�." << endl;
		ptPlayer->tInventory.iGold -= (int)(ptPlayer->tInventory.iGold * 0.1);
		system("pause");
	}
}

int BuyMenu(int iGold, int iItemCount, _tagItem* ptStoreItemArr)
{
	int iSelMenu = 0;
	int Fail = 0;
	system("cls");
	cout << "=================" << ptStoreItemArr[0].strTypeName << "����===================\t ������� : " << iGold <<
		"���� ĭ �� : " << iItemCount << "/" << INVENTORY_MAX << endl;
	for (int i = 0; i < STORE_MAX; ++i) {
		cout << i + 1 << ". " << ptStoreItemArr[i].strName << " : " << ptStoreItemArr[i].strDesc << endl <<
			"���� : " << ptStoreItemArr[i].iPrice << endl << endl;
	}
	cout << STORE_MAX + 1 << ". �ڷ�" << endl;
	cout << "������ �������� ���� �ϼ��� : ";
	cin >> iSelMenu;

	Fail = CheckCin();
	if (Fail == -1)
		iSelMenu = -1;
	return iSelMenu;
}

void Buy(int* iGold, int* iItemCount, int iMenu, _tagItem* ptStoreItemArr, _tagItem* ptPlayreItemArr)
{
	if (ptStoreItemArr[iMenu - 1].iPrice <= *iGold) {//���� ���� ���� ���ٸ�
		if (*iItemCount < INVENTORY_MAX) { //�κ��丮�� �� ���� �ʾҴٸ� �����Ѵ�.
			ptPlayreItemArr[*iItemCount] = ptStoreItemArr[iMenu - 1];
			strcpy_s(ptPlayreItemArr[*iItemCount].strName, ptStoreItemArr[iMenu - 1].strName);
			strcpy_s(ptPlayreItemArr[*iItemCount].strTypeName, ptStoreItemArr[iMenu - 1].strTypeName);
			strcpy_s(ptPlayreItemArr[*iItemCount].strDesc, ptStoreItemArr[iMenu - 1].strDesc);
			++* iItemCount;
			*iGold -= ptStoreItemArr[iMenu - 1].iPrice;
			cout << ptStoreItemArr[iMenu - 1].strName << "�� ���� �߽��ϴ�." << endl;
		}
		else
			cout << "������ �� á���ϴ�." << endl;
	}
	else
		cout << "��尡 �����մϴ�." << endl;
}

int SellMenu(int iGold, int iItemCount, _tagItem* ptPlayreItemArr)
{
	int iSelMenu = 0;
	int Fail = 0;
	system("cls");
	cout << "=================�Ǹ�===================\t ������� : " << iGold <<
		"���� ĭ �� : " << iItemCount << "/" << INVENTORY_MAX << endl;
	for (int i = 0; i < iItemCount; ++i) {
		cout << i + 1 << ". �̸� : " << ptPlayreItemArr[i].strName << " : " << ptPlayreItemArr[i].strDesc << endl;
		cout << "�з� : " << ptPlayreItemArr[i].strTypeName <<
			", ���� : " << ptPlayreItemArr[i].iStat << endl << "�Ǹ� ���� : " << ptPlayreItemArr[i].iSell << endl << endl << endl;
	}
	cout << iItemCount + 1 << ". �ڷ�" << endl;
	cout << "�Ǹ��� �������� ���� �ϼ��� : ";
	cin >> iSelMenu;

	Fail = CheckCin();
	if (Fail == -1)
		iSelMenu = -1;
	return iSelMenu;
}

void Sell(int* iGold, int* iItemCount, int iMenu, _tagItem* ptPlayreItemArr)
{
	*iGold += ptPlayreItemArr[iMenu - 1].iSell;  //�Ǹ� ������ ���� ��忡 �߰� �Ѵ�.
	cout << ptPlayreItemArr[iMenu - 1].strName << "�� �Ǹ� �߽��ϴ�." << endl;
	for (int i = iMenu - 1; i < *iItemCount; ++i) { //�Ǹ��� ������ �ڿ� �ִ� ������ ���� ������ ��ĭ�� �ű��
		if (i == INVENTORY_MAX - 1) // �迭�� �� �� �� ��� �ڿ� �ű� �迭�� ����.
			break;
		ptPlayreItemArr[i] = ptPlayreItemArr[i + 1];
		strcpy_s(ptPlayreItemArr[i].strName, ptPlayreItemArr[i + 1].strName);
		strcpy_s(ptPlayreItemArr[i].strTypeName, ptPlayreItemArr[i + 1].strTypeName);
		strcpy_s(ptPlayreItemArr[i].strDesc, ptPlayreItemArr[i + 1].strDesc);
	}
	--* iItemCount; // ���� ������ ���� ���δ�.
}

void PrintEquipItem(bool bEqWeapon, bool bEqArmor, _tagItem tEqWeapon, _tagItem tEqArmor)
{
	if (bEqWeapon) {
		cout << "���� ���� ���� : " << "�̸� : " << tEqWeapon.strName << " : " << tEqWeapon.strDesc << endl;
		cout << "�з� : " << tEqWeapon.strTypeName << ", ���� : " << tEqWeapon.iStat << endl;
	}
	if (bEqArmor) {
		cout << "���� ���� �� : " << "�̸� : " << tEqArmor.strName << " : " << tEqArmor.strDesc << endl;
		cout << "�з� : " << tEqArmor.strTypeName << ", ���� : " << tEqArmor.iStat << endl << endl;
	}

}

int EquipMenu(int iItemCount, _tagItem* ptItemArr)
{
	int iSelMenu = 0;
	int Fail = 0;
	cout << "=================����===================" << endl;
	for (int i = 0; i < iItemCount; ++i) {
		cout << i + 1 << ". " << "�̸� : " << ptItemArr[i].strName << " : " << ptItemArr[i].strDesc << endl;
		cout << "�з� : " << ptItemArr[i].strTypeName <<
			", ���� : " << ptItemArr[i].iStat << endl << "�Ǹ� ���� : " << ptItemArr[i].iSell << endl << endl << endl;
	}
	cout << iItemCount + 1 << ". ������ ���� ����" << endl;
	cout << iItemCount + 2 << ". ������ �� ����" << endl;
	cout << iItemCount + 3 << ". �ڷ�" << endl;
	cout << "������ �������� ���� �ϼ��� : ";
	cin >> iSelMenu;
	Fail = CheckCin();
	if (Fail == -1)
		iSelMenu = Fail;
	return iSelMenu;
}

void DismountWeapon(_tagPlayer* ptPlayer)
{
	//����� ���Ⱑ �ִ��� Ȯ���Ѵ�.
	if (ptPlayer->bEquipWeapon) {
		if (ptPlayer->tInventory.iItemCount < INVENTORY_MAX) {
			//������ ���⸦ �����Ѵ�.  ���ݷ��� �����.
			ptPlayer->bEquipWeapon = 0;
			ptPlayer->iAttackMax -= ptPlayer->tEquipWeapon.iStat;
			ptPlayer->iAttackMin -= ptPlayer->tEquipWeapon.iStat;
			//������ �������� �� �κ��丮�� �ִ´�
			ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount] = ptPlayer->tEquipWeapon;
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strName, ptPlayer->tEquipWeapon.strName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strTypeName, ptPlayer->tEquipWeapon.strTypeName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strDesc, ptPlayer->tEquipWeapon.strDesc);
			++ptPlayer->tInventory.iItemCount;
			cout << ptPlayer->tEquipWeapon.strName << "�� ���� �߽��ϴ�." << endl;
		}
		else
			cout << "������ �� á���ϴ�." << endl;
	}
	else
		cout << "������ ���Ⱑ �����ϴ�." << endl;
}

void DismountArmor(_tagPlayer* ptPlayer)
{
	//����� �������� �ִ��� Ȯ���Ѵ�.
	if (ptPlayer->bEquipArmor) {
		if (ptPlayer->tInventory.iItemCount < INVENTORY_MAX) {
			//������ �������� �����Ѵ�.  ������ �����.
			ptPlayer->bEquipArmor = 0;
			ptPlayer->iArmor -= ptPlayer->tEquipArmor.iStat;
			//������ �������� �� �κ��丮�� �ִ´�
			ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount] = ptPlayer->tEquipArmor;
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strName, ptPlayer->tEquipArmor.strName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strTypeName, ptPlayer->tEquipArmor.strTypeName);
			strcpy_s(ptPlayer->tInventory.tMyItemArr[ptPlayer->tInventory.iItemCount].strDesc, ptPlayer->tEquipArmor.strDesc);
			++ptPlayer->tInventory.iItemCount;
			cout << ptPlayer->tEquipArmor.strName << "�� ���� �߽��ϴ�." << endl;
		}
		else
			cout << "������ �� á���ϴ�." << endl;
	}
	else
		cout << "������ ���� �����ϴ�." << endl;

}

void EquipItem(int iMenu ,_tagPlayer* ptPlayer)
{
	_tagItem tItemSwap = {};
	if(ptPlayer->tInventory.tMyItemArr[iMenu - 1].eType == IT_WEAPON) {
		if (ptPlayer->bEquipWeapon)					//�����ִٸ� swap�˰������� ��ü�Ѵ�.
		{
			cout << "���⸦ �����ϰ� �ֽ��ϴ�. ���� ���� ����� ������ ���⸦ ��ü �մϴ�." << endl;
			system("pause");
			ptPlayer->iAttackMax -= ptPlayer->tEquipWeapon.iStat; //������ ������ ���ݷ��� �����.
			ptPlayer->iAttackMin -= ptPlayer->tEquipWeapon.iStat;

			tItemSwap = ptPlayer->tEquipWeapon;      //������ ������ swap�� ������ ����
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

			ptPlayer->iAttackMax += ptPlayer->tEquipWeapon.iStat; //������ ������ ���ݷ��� ���δ�.
			ptPlayer->iAttackMin += ptPlayer->tEquipWeapon.iStat;

			cout << ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName << "�� �����ϰ�, " << ptPlayer->tEquipWeapon.strName << "�� �����߽��ϴ�." << endl;
		}
		else //�����ϰ� �ִ� �������� ���� ��� ������ �������� ���� �Ѵ�.
		{
			//�����ϰ�, ���ݷ��� �ø���.
			ptPlayer->bEquipWeapon = 1;
			ptPlayer->tEquipWeapon = ptPlayer->tInventory.tMyItemArr[iMenu - 1];
			strcpy_s(ptPlayer->tEquipWeapon.strName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName);
			strcpy_s(ptPlayer->tEquipWeapon.strTypeName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strTypeName);
			strcpy_s(ptPlayer->tEquipWeapon.strDesc, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strDesc);
			ptPlayer->iAttackMax += ptPlayer->tEquipWeapon.iStat;
			ptPlayer->iAttackMin += ptPlayer->tEquipWeapon.iStat;

			for (int i = iMenu - 1; i < ptPlayer->tInventory.iItemCount; ++i) { //������ ������ �ڿ� �ִ� ������ ���� ������ ��ĭ�� �ű��
				if (i == INVENTORY_MAX - 1) // �迭�� �� �� �� ��� �ڿ� �ű� �迭�� ����.
					break;
				ptPlayer->tInventory.tMyItemArr[i] = ptPlayer->tInventory.tMyItemArr[i + 1];
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strName, ptPlayer->tInventory.tMyItemArr[i + 1].strName);
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strTypeName, ptPlayer->tInventory.tMyItemArr[i + 1].strTypeName);
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strDesc, ptPlayer->tInventory.tMyItemArr[i + 1].strDesc);
			}
			--ptPlayer->tInventory.iItemCount; // ���� ������ ���� ���δ�.
			cout << ptPlayer->tEquipWeapon.strName << "�� ���� �߽��ϴ�." << endl;


		}
	}// ���� ���� ��
	else if (ptPlayer->tInventory.tMyItemArr[iMenu - 1].eType == IT_ARMOR) {
		if (ptPlayer->bEquipArmor)					//�����ִٸ� swap�˰������� ��ü�Ѵ�.
		{
			cout << "���� �����ϰ� �ֽ��ϴ�. ���� ���� ���� ������ ���� ��ü �մϴ�." << endl;
			system("pause");
			ptPlayer->iArmor -= ptPlayer->tEquipArmor.iStat; //������ ���� ������ �����.

			tItemSwap = ptPlayer->tEquipArmor;      //������ ������ swap�� ������ ����
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

			ptPlayer->iArmor += ptPlayer->tEquipArmor.iStat; //������ ������ ���ݷ��� ���δ�.

			cout << ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName << "�� �����ϰ�, " << ptPlayer->tEquipArmor.strName << "�� �����߽��ϴ�." << endl;
		}
		else					//�����ϰ� �ִ� �������� ���� ��� ������ �������� ���� �Ѵ�.
		{
			//�����ϰ�, ������ �ø���.
			ptPlayer->bEquipArmor = 1;
			ptPlayer->tEquipArmor = ptPlayer->tInventory.tMyItemArr[iMenu - 1];
			strcpy_s(ptPlayer->tEquipArmor.strName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strName);
			strcpy_s(ptPlayer->tEquipArmor.strTypeName, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strTypeName);
			strcpy_s(ptPlayer->tEquipArmor.strDesc, ptPlayer->tInventory.tMyItemArr[iMenu - 1].strDesc);
			ptPlayer->iArmor += ptPlayer->tEquipArmor.iStat;

			for (int i = iMenu - 1; i < ptPlayer->tInventory.iItemCount; ++i) { //������ ������ �ڿ� �ִ� ������ ���� ������ ��ĭ�� �ű��
				if (i == INVENTORY_MAX - 1) // �迭�� �� �� �� ��� �ڿ� �ű� �迭�� ����.
					break;
				ptPlayer->tInventory.tMyItemArr[i] = ptPlayer->tInventory.tMyItemArr[i + 1];
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strName, ptPlayer->tInventory.tMyItemArr[i + 1].strName);
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strTypeName, ptPlayer->tInventory.tMyItemArr[i + 1].strTypeName);
				strcpy_s(ptPlayer->tInventory.tMyItemArr[i].strDesc, ptPlayer->tInventory.tMyItemArr[i + 1].strDesc);
			}
			--ptPlayer->tInventory.iItemCount; // ���� ������ ���� ���δ�.
			cout << ptPlayer->tEquipArmor.strName << "�� ���� �߽��ϴ�." << endl;
		}
	}
}