
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
	J_END   // END���� �ڵ忡 �߰������ν� ������ ���߿� �߰� �ص� �ٸ� �ڵ带 ������ �ʿ� ����
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
	char strDesc[DESC_LENGTH]; //������ ����
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

//���� ����
int iMenu;
int iBattleMenu; // �����Ҷ� iMenu�� ��� ���̹Ƿ� ���ÿ� ������ �ϳ� �� �ʿ�
int iJob = J_NONE;
int iAttack = 0;
int iDamage = 0;
_tagPlayer tPlayer = {};
_tagMonster tMonsterArr[MT_BACK - 1] = {}; // �� �ܰ�� �� �ϳ� MT_BACK - 1
_tagMonster tBattleMonster = {};
_tagItem tStoreWeaponArr[STORE_MAX] = {};
_tagItem tStoreArmorArr[STORE_MAX] = {};
bool bMonsterAlive;
bool bPlayerAlive;


int main() {

	srand((unsigned int)time(0));

	// ���ӽ��� �� �÷��̾� ���� ����
	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.tInventory.iGold = 300000;
	cout << "�̸� : ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1);

	while (iJob == J_NONE)
	{
		system("cls");
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";
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
		strcpy_s(tPlayer.strJob, "���");
		tPlayer.iArmor = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iAttackMin = 5;
		tPlayer.iHPMax = 75;
		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMPMax = 25;
		tPlayer.iMP = tPlayer.iMPMax;
		break;
	case J_ARCHER:
		strcpy_s(tPlayer.strJob, "�ü�");
		tPlayer.iArmor = 3;
		tPlayer.iAttackMax = 13;
		tPlayer.iAttackMin = 7;
		tPlayer.iHPMax = 60;
		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMPMax = 35;
		tPlayer.iMP = tPlayer.iMPMax;
		break;
	case J_WIZARD:
		strcpy_s(tPlayer.strJob, "������");
		tPlayer.iArmor = 1;
		tPlayer.iAttackMax = 17;
		tPlayer.iAttackMin = 7;
		tPlayer.iHPMax = 55;
		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMPMax = 55;
		tPlayer.iMP = tPlayer.iMPMax;
		break;
	}

	//���� ���� ����
	//easy ���
	strcpy_s(tMonsterArr[0].strName, "���");
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
	
	//normal ��ũ
	strcpy_s(tMonsterArr[1].strName, "��ũ");
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

	//hard �����
	strcpy_s(tMonsterArr[2].strName, "�����");
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

	//�������� �Ǹ��� ������ ���
	strcpy_s(tStoreWeaponArr[0].strName, "���� Į");
	strcpy_s(tStoreWeaponArr[0].strTypeName, "����");
	strcpy_s(tStoreWeaponArr[0].strDesc, "���� ������ Ÿ�ݰ��� ����.");
	tStoreWeaponArr[0].eType = IT_WEAPON;
	tStoreWeaponArr[0].iPrice = 2000;
	tStoreWeaponArr[0].iSell = 1000;
	tStoreWeaponArr[0].iStat = 100;

	strcpy_s(tStoreWeaponArr[1].strName, "Į");
	strcpy_s(tStoreWeaponArr[1].strTypeName, "����");
	strcpy_s(tStoreWeaponArr[1].strDesc, "���� �־ �� �� �ִ�.");
	tStoreWeaponArr[1].eType = IT_WEAPON;
	tStoreWeaponArr[1].iPrice = 10000;
	tStoreWeaponArr[1].iSell = 3000;
	tStoreWeaponArr[1].iStat = 50;

	strcpy_s(tStoreWeaponArr[2].strName, "��ī�ο� Į");
	strcpy_s(tStoreWeaponArr[2].strTypeName, "����");
	strcpy_s(tStoreWeaponArr[2].strDesc, "���� ��ī�Ӵ�.");
	tStoreWeaponArr[2].eType = IT_WEAPON;
	tStoreWeaponArr[2].iPrice = 100000;
	tStoreWeaponArr[2].iSell = 40000;
	tStoreWeaponArr[2].iStat = 200;

	strcpy_s(tStoreArmorArr[0].strName, "������ ����");
	strcpy_s(tStoreArmorArr[0].strTypeName, "��");
	strcpy_s(tStoreArmorArr[0].strDesc, "�����ϴ�.");
	tStoreArmorArr[0].eType = IT_WEAPON;
	tStoreArmorArr[0].iPrice = 1000;
	tStoreArmorArr[0].iSell = 500;
	tStoreArmorArr[0].iStat = 10;

	strcpy_s(tStoreArmorArr[1].strName, "����");
	strcpy_s(tStoreArmorArr[1].strTypeName, "��");
	strcpy_s(tStoreArmorArr[1].strDesc, "�����̴�.");
	tStoreArmorArr[1].eType = IT_WEAPON;
	tStoreArmorArr[1].iPrice = 15000;
	tStoreArmorArr[1].iSell = 5000;
	tStoreArmorArr[1].iStat = 70;

	strcpy_s(tStoreArmorArr[2].strName, "�ܴ��� ����");
	strcpy_s(tStoreArmorArr[2].strTypeName, "��");
	strcpy_s(tStoreArmorArr[2].strDesc, "�ܴ��ϴ�.");
	tStoreArmorArr[2].eType = IT_WEAPON;
	tStoreArmorArr[2].iPrice = 90000;
	tStoreArmorArr[2].iSell = 35000;
	tStoreArmorArr[2].iStat = 130;

	while (true) {
		system("cls");
		cout << "=================���θ޴�==================" << endl;
		cout << "1. ����" << endl;
		cout << "2. ����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ����" << endl;
		cout << "�޴��� ���� �ϼ��� : ";
		cin >> iMenu;

		if (cin.fail()) {
			//�������۸� ����ش�.
			cin.clear();
			//�Է� ���ۿ� \n�� ���� �Ѵ�.
			cin.ignore(1024, '\n'); //�˳��ϰ� 1024 ����Ʈ�� �˻��Ͽ� \n�� �����ش�.
			continue;
		}
		if (iMenu == MM_EXIT)
			break;
		switch (iMenu) {
		case MM_MAP:
			while (true) {
				system("cls");
				cout << "=================�ʸ޴�===================" << endl;
				cout << "1. ����" << endl;
				cout << "2. ����" << endl;
				cout << "3. �����" << endl;
				cout << "4. �ڷ�" << endl;
				cout << "�޴��� ���� �ϼ��� : ";
				cin >> iMenu;

				if (cin.fail()) {
					//�������۸� ����ش�.
					cin.clear();
					//�Է� ���ۿ� \n�� ���� �Ѵ�.
					cin.ignore(1024, '\n'); //�˳��ϰ� 1024 ����Ʈ�� �˻��Ͽ� \n�� �����ش�.
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
					cout << "****************Player****************" << endl;
					cout << "�̸� : " << tPlayer.strName <<
						"\t���� : " << tPlayer.strJob << endl;
					cout << "���� : " << tPlayer.iLevel <<
						"\t����ġ : " << tPlayer.iExp << endl;
					cout << "���ݷ�  : " << tPlayer.iAttackMin <<
						" - " << tPlayer.iAttackMax << "\t���� : " << tPlayer.iArmor << endl;
					cout << "ü�� : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
						"\t���� : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;
					cout << "������� : " << tPlayer.tInventory.iGold << endl << endl;

					// Monster info
					cout << "****************Monster****************" << endl;
					cout << "�̸� : " << tBattleMonster.strName <<
						"\t���� : " << tBattleMonster.iLevel << endl;
					cout << "���ݷ�  : " << tBattleMonster.iAttackMin <<
						" - " << tBattleMonster.iAttackMax << "\t���� : " << tBattleMonster.iArmor << endl;
					cout << "ü�� : " << tBattleMonster.iHP << " / " << tBattleMonster.iHPMax <<
						"\t���� : " << tBattleMonster.iMP << " / " << tBattleMonster.iMPMax << endl;
					cout << "ȹ�� ����ġ : " << tBattleMonster.iGetExp <<
						"\tȹ�� ��� : " << tBattleMonster.iGetGold << endl << endl;

					cout << "1. ����" << endl;
					/*cout << "2. ȸ��" << endl;
					cout << "3. ���" << endl;*/
					cout << "2. ����" << endl;
					cout << "�޴��� ���� �ϼ���." << endl;
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
						cout << tPlayer.strName << " �� " << tBattleMonster.strName << " ���� " << iDamage << "�� ���ظ� �������ϴ�." << endl;

						//���Ͱ� �׾��� ���
						if (tBattleMonster.iHP <= 0)
						{
							bMonsterAlive = 0; // ���͸� ��� ���·� ����

							break;
						}

						//���Ͱ� ��� �ִٸ� �÷��̾ �����Ѵ�.
						iAttack = rand() % (tBattleMonster.iAttackMax - tBattleMonster.iAttackMin + 1) + tBattleMonster.iAttackMin;
						iDamage = iAttack <= tPlayer.iArmor ? 1 : iAttack - tPlayer.iArmor;
						tPlayer.iHP -= iDamage;
						cout << tBattleMonster.strName << " �� " << tPlayer.strName << " ���� " << iDamage << "�� ���ظ� �������ϴ�." << endl;

						//�÷��̾ �׾���	���
						if (tPlayer.iHP <= 0)
						{
							bPlayerAlive = 0; // �÷��̾ ��� ���·� ����
						}
						break;
					/*case B_ESCAPE:
						break;
					case B_DEFEND:
						break;*/
					default:
						cout << "�޴��� �߸� �����ϼ̽��ϴ�." << endl;
						break;
					}
					if (bMonsterAlive == 0) {//���� �����
						cout << tBattleMonster.strName << "�� ����߽��ϴ�." << endl;
						tPlayer.iExp += tBattleMonster.iGetExp;
						tPlayer.tInventory.iGold += tBattleMonster.iGetGold;

						cout << tBattleMonster.iGetExp << "�� ����ġ�� ȹ���߽��ϴ�." << endl;
						cout << tBattleMonster.iGetGold << "�� ��带 ȹ���߽��ϴ�." << endl;

						system("pause");
						break;
					}
					else if (bPlayerAlive == 0) { // �÷��̾� �����
						cout << tPlayer.strName << "�� ����߽��ϴ�." << endl;
						cout << "�������� �й� �߽��ϴ�." << endl;
						cout << (int)(tPlayer.tInventory.iGold * 0.1) << "�� ��带 �Ҿ����ϴ�." << endl;
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
				cout << "=================�����޴�===================\t ������� : " << tPlayer.tInventory.iGold << endl;
				cout << "1. ����" << endl;
				cout << "2. ��" << endl;
				cout << "3. �ȱ�" << endl;
				cout << "4. �ڷ�" << endl;
				cout << "�޴��� ���� �ϼ��� : ";
				cin >> iMenu;

				if (cin.fail()) {
					//�������۸� ����ش�.
					cin.clear();
					//�Է� ���ۿ� \n�� ���� �Ѵ�.
					cin.ignore(1024, '\n'); //�˳��ϰ� 1024 ����Ʈ�� �˻��Ͽ� \n�� �����ش�.
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
						cout << "=================�������===================\t ������� : " << tPlayer.tInventory.iGold << endl;
						// ��� ��� for ������ �ٲ㼭 �������� �߰� �ϸ� �� �� �� �ֵ��� �ٲ۴� (��������) 
						cout << "1. " << tStoreWeaponArr[0].strName << " : " << tStoreWeaponArr[0].strDesc << " ���� : " << tStoreWeaponArr[0].iPrice << endl;
						cout << "2. " << tStoreWeaponArr[1].strName << " : " << tStoreWeaponArr[1].strDesc << " ���� : " << tStoreWeaponArr[1].iPrice << endl;
						cout << "3. " << tStoreWeaponArr[2].strName << " : " << tStoreWeaponArr[2].strDesc << " ���� : " << tStoreWeaponArr[2].iPrice << endl;
						cout << "4. �ڷ�" << endl;
						cout << "������ �������� ���� �ϼ��� : ";
						cin >> iMenu;

						if (cin.fail()) {
							//�������۸� ����ش�.
							cin.clear();
							//�Է� ���ۿ� \n�� ���� �Ѵ�.
							cin.ignore(1024, '\n'); //�˳��ϰ� 1024 ����Ʈ�� �˻��Ͽ� \n�� �����ش�.
							continue;
						}
						if (iMenu <= 0 || iMenu > STORE_MAX + 1)
							continue;
						if (iMenu == STORE_MAX + 1) {
							break;
						}
							if (tStoreWeaponArr[iMenu - 1].iPrice <= tPlayer.tInventory.iGold) {//���� ���� ���� ���ٸ�
								if (tPlayer.tInventory.iItemCount < INVENTORY_MAX) { //�κ��丮�� �� ���� �ʾҴٸ� �����Ѵ�.
									tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount] = tStoreWeaponArr[iMenu - 1];
									strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strName, tStoreWeaponArr[iMenu - 1].strName);
									strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strTypeName, tStoreWeaponArr[iMenu - 1].strTypeName);
									strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strDesc, tStoreWeaponArr[iMenu - 1].strDesc);
									++tPlayer.tInventory.iItemCount;
									tPlayer.tInventory.iGold -= tStoreWeaponArr[iMenu - 1].iPrice;
									cout << tStoreWeaponArr[iMenu - 1].strName << "�� ���� �߽��ϴ�." << endl;
								}
								else
									cout << "������ �� á���ϴ�." << endl;
							}
							else
								cout << "��尡 �����մϴ�." << endl;
						system("pause");
					}
					break;
				case SM_ARMOR:
					while (true) {
						system("cls");
						cout << "=================������===================\t ������� : " << tPlayer.tInventory.iGold << endl;
						cout << "1. " << tStoreArmorArr[0].strName << " : " << tStoreArmorArr[0].strDesc << " ���� : " << tStoreArmorArr[0].iPrice << endl;
						cout << "2. " << tStoreArmorArr[1].strName << " : " << tStoreArmorArr[1].strDesc << " ���� : " << tStoreArmorArr[1].iPrice << endl;
						cout << "3. " << tStoreArmorArr[2].strName << " : " << tStoreArmorArr[2].strDesc << " ���� : " << tStoreArmorArr[2].iPrice << endl;
						cout << "4. �ڷ�" << endl;
						cout << "������ �������� ���� �ϼ��� : ";
						cin >> iMenu;

						if (cin.fail()) {
							//�������۸� ����ش�.
							cin.clear();
							//�Է� ���ۿ� \n�� ���� �Ѵ�.
							cin.ignore(1024, '\n'); //�˳��ϰ� 1024 ����Ʈ�� �˻��Ͽ� \n�� �����ش�.
							continue;
						}
						if (iMenu <= 0 || iMenu > STORE_MAX + 1)
							continue;
						if (iMenu == STORE_MAX + 1) {
							break;
						}
						if (tStoreArmorArr[iMenu - 1].iPrice <= tPlayer.tInventory.iGold) {//���� ���� ���� ���ٸ�
							if (tPlayer.tInventory.iItemCount < INVENTORY_MAX) { //�κ��丮�� �� ���� �ʾҴٸ� �����Ѵ�.
								tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount] = tStoreArmorArr[iMenu - 1];
								strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strName, tStoreArmorArr[iMenu - 1].strName);
								strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strTypeName, tStoreArmorArr[iMenu - 1].strTypeName);
								strcpy_s(tPlayer.tInventory.tMyItemArr[tPlayer.tInventory.iItemCount].strDesc, tStoreArmorArr[iMenu - 1].strDesc);
								++tPlayer.tInventory.iItemCount;
								tPlayer.tInventory.iGold -= tStoreArmorArr[iMenu - 1].iPrice;
								cout << tStoreArmorArr[iMenu - 1].strName << "�� ���� �߽��ϴ�." << endl;
							}
							else
								cout << "������ �� á���ϴ�." << endl;
						}
						else
							cout << "��尡 �����մϴ�." << endl;
						system("pause");
					}
					break;
				case SM_SELL:
					while (true) {
						system("cls");
						cout << "=================�Ǹ�===================\t ������� : " << tPlayer.tInventory.iGold << endl;
						for (int i = 0; i < tPlayer.tInventory.iItemCount; ++i) {
							cout << i + 1 << ". " << "�̸� : " << tPlayer.tInventory.tMyItemArr[i].strName << " : " << tPlayer.tInventory.tMyItemArr[i].strDesc << endl;
							cout << "�з� : " << tPlayer.tInventory.tMyItemArr[i].strTypeName <<
								", ���� : " << tPlayer.tInventory.tMyItemArr[i].iStat << endl << "�Ǹ� ���� : " << tPlayer.tInventory.tMyItemArr[i].iSell << endl << endl << endl;
						}
						cout << tPlayer.tInventory.iItemCount + 1 << ". �ڷ�" << endl;
						cout << "�Ǹ��� �������� ���� �ϼ��� : ";
						cin >> iMenu;
						if (cin.fail()) {
							//�������۸� ����ش�.
							cin.clear();
							//�Է� ���ۿ� \n�� ���� �Ѵ�.
							cin.ignore(1024, '\n'); //�˳��ϰ� 1024 ����Ʈ�� �˻��Ͽ� \n�� �����ش�.
							continue;
						}
						if (iMenu <= 0 || iMenu > tPlayer.tInventory.iItemCount + 1)
							continue;
						if (iMenu == tPlayer.tInventory.iItemCount + 1) {
							break;
						}
						for (int i = iMenu - 1; i < tPlayer.tInventory.iItemCount; ++i) { //�Ǹ��� ������ �ڿ� �ִ� ������ ���� ������ ��ĭ�� �ű��
							if (i == INVENTORY_MAX - 1) // �迭�� �� �� �� ��� �ڿ� �ű� �迭�� ����.
								break;
							tPlayer.tInventory.tMyItemArr[i] = tPlayer.tInventory.tMyItemArr[i + 1];
							strcpy_s(tPlayer.tInventory.tMyItemArr[i].strName, tPlayer.tInventory.tMyItemArr[i + 1].strName);
							strcpy_s(tPlayer.tInventory.tMyItemArr[i].strTypeName, tPlayer.tInventory.tMyItemArr[i + 1].strTypeName);
							strcpy_s(tPlayer.tInventory.tMyItemArr[i].strDesc, tPlayer.tInventory.tMyItemArr[i + 1].strDesc);
						}
						tPlayer.tInventory.iGold += tStoreArmorArr[iMenu - 1].iSell;  //�Ǹ� ������ ���� ��忡 �߰� �Ѵ�.
						cout << tStoreArmorArr[iMenu - 1].strName << "�� �Ǹ� �߽��ϴ�." << endl;
						--tPlayer.tInventory.iItemCount; // ���� ������ ���� ���δ�.
					}
					break;
				}
			}
			break;
		case MM_BAG:
			system("cls");
			cout << "=================����===================" << endl;
			for (int i = 0; i < tPlayer.tInventory.iItemCount; ++i) {
				cout << i + 1 << ". " << "�̸� : " << tPlayer.tInventory.tMyItemArr[i].strName << " : " << tPlayer.tInventory.tMyItemArr[i].strDesc << endl;
				cout << "�з� : " << tPlayer.tInventory.tMyItemArr[i].strTypeName <<
					 ", ���� : " << tPlayer.tInventory.tMyItemArr[i].iStat << endl << "�Ǹ� ���� : " << tPlayer.tInventory.tMyItemArr[i].iSell << endl << endl << endl;
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