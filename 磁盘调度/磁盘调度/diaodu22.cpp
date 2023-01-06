#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MAX 1111
#define INF 0x3f3f3f3f         //���������
using namespace std;
typedef struct Disk_Scheduling
{
	int Trackhao;
	int Trackshu;
}DKSG;

int track[MAX];
int mark[MAX];
double t;            //��λѰ��ʱ��
int n;
int now;             //��ǰ�ŵ�
int flag = 1;          //��������ɨ��
//����
int input(int& n, int& now)
{
	int im = 0;
	int Min = INF;
	cout << "����������ŵ��Ÿ�������ʼ�ŵ��ţ���λѰ��ʱ���Լ���ͷ����(0-����  1-����):" << endl;
	cin >> n >> now >> t >> flag;
	cout << "������" << n << "���ŵ���:" << endl;
	for (int i = 0; i < n; i++) {
		cin >> track[i];
		int temp = fabs(track[i] - now);
		if (temp < Min) {
			Min = temp;                               //������ʼ�ŵ�����Ĵŵ���
			im = i;
		}
	}
	return im;
}
//���
void output(int n, DKSG ds[MAX])
{
	int sum = 0;
	cout << "�����ʵ���һ���ŵ���         ���ŵ���" << endl;
	for (int i = 0; i < n; i++) {
		cout << "       " << ds[i].Trackhao << "                     " << ds[i].Trackshu << endl;
		sum += ds[i].Trackshu;
	}
	cout << "���ŵ�������" << sum << endl;                         //������ŵ�����
	cout << "ƽ��Ѱ��ʱ�䣺" << (sum * t) / n << endl;              //���ƽ��Ѱ��ʱ��
}
//�����ȷ���
void FCFS(int now)
{
	DKSG ds[MAX];
	for (int i = 0; i < n; i++) {
		ds[i].Trackhao = track[i];
		ds[i].Trackshu = fabs(track[i] - now);
		now = track[i];
	}
	cout << "�����ȷ���:" << endl;
	output(n, ds);
}
//���·��
void SSTF(int now, int im)
{
	DKSG ds[MAX];
	memset(mark, 0, sizeof(mark));
	for (int i = 0; i < n; i++) {
		int Min = INF;
		ds[i].Trackhao = track[im];
		ds[i].Trackshu = fabs(track[im] - now);
		now = track[im];
		mark[im] = 1;                                 //��Ǵ�λ�Ƿ����
		for (int j = 0; j < n; j++) {
			if (!mark[j]) {
				double temp = fabs(track[j] - now);
				if (temp < Min) {
					Min = temp;
					im = j;                           //ÿ��ѭ��ѡ����С��
				}
			}
		}
	}
	cout << "���Ѱ��ʱ������:" << endl;
	output(n, ds);
}
//ɨ��
void SCAN(int now)
{
	DKSG ds[MAX];
	double retrack[MAX];
	if (flag)                                                        //����ɨ��
	{
		sort(track, track + n);                                           //��С��������
		int locate = upper_bound(track, track + n, now) - track;         //���ֲ��ҵ�һ������now������
		int t = locate;                                            //��¼������
		int k, r;
		for (k = 0; k < n - locate; k++) {
			retrack[k] = track[k + locate];
		}
		for (r = k; r < n; r++) {
			retrack[r] = track[--t];
		}
		for (int i = 0; i < n; i++) {
			ds[i].Trackhao = retrack[i];                               //�����ս������ds������
			ds[i].Trackshu = fabs(retrack[i] - now);
			now = retrack[i];
		}
	}
	else
	{                                                            //����ɨ��
		sort(track, track + n, greater<int>());                  //�Ӵ���С����       
		int locate = upper_bound(track, track + n, now, greater<int>()) - track;     //���ֲ��ҵ�һ������now������         
		int t = locate;                                      //��¼������
		int k, r;
		for (k = 0; k < n - locate; k++) {
			retrack[k] = track[k + locate];
		}
		for (r = k; r < n; r++) {
			retrack[r] = track[--t];
		}                                                         //��retrack�����м�¼ɨ����
		for (int i = 0; i < n; i++) {
			ds[i].Trackhao = retrack[i];
			ds[i].Trackshu = fabs(retrack[i] - now);                 //�����ս������ds������
			now = retrack[i];
		}
	}
	printf("\nɨ������㷨:\n");
	output(n, ds);
}

//ѭ��ɨ��
void C_SCAN(int now)
{
	DKSG ds[MAX];
	double retrack[MAX];
	if (flag)                                                     //����ɨ��
	{
		sort(track, track + n);                                    //��С��������
		int locate = upper_bound(track, track + n, now) - track;
		int im;
		for (int i = 0; i < n; i++) {
			im = (i + locate) % n;
			ds[i].Trackhao = track[im];
			ds[i].Trackshu = fabs(track[im] - now);                       //�����ս������ds������
			now = track[im];
		}
	}
	else                                                                  //����ɨ��
	{
		sort(track, track + n, greater<int>());                             //�Ӵ���С����  
		int locate = upper_bound(track, track + n, now, greater<int>()) - track;       //���ֲ��ҵ�һ������now������ 
		int t = locate;                                                     //��¼������
		int k, r, l = 0;
		for (k = 0; k < n - locate; k++) {
			retrack[k] = track[k + locate];
		}
		for (r = k; r < n; r++) {
			retrack[r] = track[l++];                                            //��retrack�����м�¼ɨ����
		}
		for (int i = 0; i < n; i++) {
			ds[i].Trackhao = retrack[i];
			ds[i].Trackshu = fabs(retrack[i] - now);
			now = retrack[i];                                        //�����ս������ds������
		}
	}
	printf("\nѭ��ɨ������㷨:\n");
	output(n, ds);                                               //������մ�
}
int main()
{
	char ch;
	do {
		int i = input(n, now);
		FCFS(now);
		SSTF(now, i);
		SCAN(now);
		C_SCAN(now);
		cout << "�Ƿ����:";
		cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	return 0;
}