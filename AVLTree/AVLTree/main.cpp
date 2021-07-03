#include <iostream>
#include <list>
#include <string>
#include "AVLTree.h"

using namespace std;

int main()
{
	AVLTree<int> t;
	int ch;
	int* ptemp;
	int temp;

	do
	{
		cout << "(1) 삽입 (2) 삭제 (3) 검색 (4) 출력 : ";
		cin >> ch;

		switch (ch)
		{
		case 1:
			cout << "정수 입력 : ";
			cin >> temp;
			t.insert(temp);
			break;

		case 2:
			cout << "삭제할 정수 입력 : ";
			cin >> temp;
			if (t.remove(temp))
				cout << temp << " 를 삭제했습니다.\n";
			else
				cout << "탐색에 실패했습니다.\n";
			break;

		case 3:
			cout << "검색할 정수 입력 : ";
			cin >> temp;
			ptemp = t.find(temp);
			if (ptemp != NULL)
				cout << *ptemp << " 를 찾았습니다.\n";
			else
				cout << "탐색에 실패했습니다.\n";
			break;

		case 4:
			t.print();
			break;
		case 5:
			t.printTree();
			break;

		}
		cout << endl << endl;

	} while (ch >= 1 && ch <= 5);

	return 0;
}
