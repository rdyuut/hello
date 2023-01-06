#include <iostream>
#include <algorithm>
#include <cstdio>
#define MAX 999
using namespace std;

//��ƽ��Ѱ������
double ave(int* length, int n) {
	double sum = 0;
	int i;
	for (i = 0; i < n; i++)
		sum += length[i];
	return sum / n;
}

void FCFS(int* a, int n, int now) {
	int i, k = 0;
	int t = n;
	int next[MAX], length[MAX];
	int visit[MAX] = { 0 };
	while (t--)
	{
		for (i = 0; i < n; i++) {
			if (visit[i])
				continue;
			else {
				length[k] = abs(a[i] - now);
				next[k++] = a[i];
				visit[i] = 1;
				now = a[i];
			}
		}
	}
	cout << endl << "��һ���ŵ�  " << "�ƶ�����" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "FCFS��ƽ��Ѱ������:";
	printf("%.2f\n\n", ave(length, n));
}

void SSTF(int* a, int n, int now) {
	int i, min, k = 0;
	int flag;//���·�����±�
	int t = n;
	int next[MAX], length[MAX];
	int visit[MAX] = { 0 };//�������飬�Ѿ����ʹ���Ϊ1
	//Ѱ��n��
	while (t--) {
		min = 100000;
		//��û�з��ʹ����������
		for (i = 0; i < n; i++) {
			if (visit[i])
				continue;
			if (abs(a[i] - now) < min) {
				flag = i;
				min = abs(a[i] - now);
			}
		}
		length[k] = min;//�ƶ��ľ���
		next[k++] = a[flag];//��һ�������ʵĴŵ���
		visit[flag] = 1;//���ʹ�����1
		now = a[flag];//�ŵ��ƶ�����ǰλ��
	}
	cout << endl << "��һ���ŵ�  " << "�ƶ�����" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "SSTF��ƽ��Ѱ������:";
	printf("%.2f\n\n", ave(length, n));
}

void SCAN(int* a, int n, int now) {
	int i, flag = 0, k = 0;
	int next[MAX], length[MAX];
	sort(a, a + n);//��С��������
	//Ѱ�ҿ�ʼ�ŵ�
	for (i = 0; i < n; i++) {
		if (a[i] >= now) {
			flag = i;
			break;
		}
	}
	//�������������
	for (i = flag; i < n; i++) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}
	//�������ݼ��������
	for (i = flag - 1; i >= 0; i--) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}
	cout << endl << "��һ���ŵ�  " << "�ƶ�����" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "SCAN��ƽ��Ѱ������:";
	printf("%.2f\n\n", ave(length, n));
}

int main() {
	int a[MAX];//���Ҫ�õ��Ĵŵ���
	int start;//��ʼ�Ĵŵ�
	int n, i, flag = 1;
	cout << "һ��Ҫ�õ��Ĵŵ�����";
	cin >> n;
	cout << "�������ŵ�" << endl;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout <<  "���뿪ʼ�Ĵŵ���";
	cin >> start;
	FCFS(a, n, start);
	SSTF(a, n, start);
	SCAN(a, n, start);
}
//��1��	�����ȷ�����̵����㷨��FCFS��
//��2��	���Ѱ��ʱ�����ȴ��̵����㷨��SSTF��
//��3��	ɨ����̵����㷨��SCAN��
