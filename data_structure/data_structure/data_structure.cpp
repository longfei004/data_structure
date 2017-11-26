#include "LinkQueue.h"	// ��������

int main(void)
{
	char c = '1';
	CLinkQueue<int> qa;
	int x;

	while (c != '0')
	{
		cout << endl << "1. ���ɶ���.";
		cout << endl << "2. ��ʾ����.";
		cout << endl << "3. �����.";
		cout << endl << "4. ������.";
		cout << endl << "5. ȡ����ͷ.";
		cout << endl << "0. �˳�";
		cout << endl << "ѡ����(0~5):";
		cin >> c;
		switch (c) 
		{
			case '1':
				qa.Clear();
				cout << endl << "����e(e = 0ʱ�˳�)";
				cin >> x;
				while (x != 0) {
					qa.EnQueue(x);
					cin >> x;
				}
				break;
			case '2':
				cout << endl;
				qa.Traverse(Write<int>);			
				break;
			case '3':
				cout << endl << "����Ԫ��ֵ:";
				cin >> x;
				qa.EnQueue(x);
				break;
			case '4':
				if(qa.DelQueue(x) == SUCCESS)
					cout << endl << "��ͷԪ��ֵΪ: " << x << endl;
				break;
			case '5':
				if(qa.GetHead(x) == SUCCESS)
					cout << endl << "��ͷԪ��ֵΪ: " << x << endl;
				break;
		}
		cout << endl;
	}
	
	return 0;
}


