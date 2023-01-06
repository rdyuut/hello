#include <iostream>
#include <algorithm>
#include <cstdio>
#define MAX 999
using namespace std;

//求平均寻道长度
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
	cout << endl << "下一个磁道  " << "移动距离" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "FCFS的平均寻道长度:";
	printf("%.2f\n\n", ave(length, n));
}

void SSTF(int* a, int n, int now) {
	int i, min, k = 0;
	int flag;//最短路径的下标
	int t = n;
	int next[MAX], length[MAX];
	int visit[MAX] = { 0 };//访问数组，已经访问过的为1
	//寻道n次
	while (t--) {
		min = 100000;
		//找没有访问过的中最近的
		for (i = 0; i < n; i++) {
			if (visit[i])
				continue;
			if (abs(a[i] - now) < min) {
				flag = i;
				min = abs(a[i] - now);
			}
		}
		length[k] = min;//移动的距离
		next[k++] = a[flag];//下一个被访问的磁道号
		visit[flag] = 1;//访问过的置1
		now = a[flag];//磁道移动到当前位置
	}
	cout << endl << "下一个磁道  " << "移动距离" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "SSTF的平均寻道长度:";
	printf("%.2f\n\n", ave(length, n));
}

void SCAN(int* a, int n, int now) {
	int i, flag = 0, k = 0;
	int next[MAX], length[MAX];
	sort(a, a + n);//从小到大排序
	//寻找开始磁道
	for (i = 0; i < n; i++) {
		if (a[i] >= now) {
			flag = i;
			break;
		}
	}
	//往递增方向访问
	for (i = flag; i < n; i++) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}
	//回来往递减方向访问
	for (i = flag - 1; i >= 0; i--) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}
	cout << endl << "下一个磁道  " << "移动距离" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "SCAN的平均寻道长度:";
	printf("%.2f\n\n", ave(length, n));
}

int main() {
	int a[MAX];//存放要用到的磁道号
	int start;//开始的磁道
	int n, i, flag = 1;
	cout << "一共要用到的磁道数：";
	cin >> n;
	cout << "请输入信道" << endl;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout <<  "输入开始的磁道：";
	cin >> start;
	FCFS(a, n, start);
	SSTF(a, n, start);
	SCAN(a, n, start);
}
//（1）	先来先服务磁盘调度算法（FCFS）
//（2）	最短寻道时间优先磁盘调度算法（SSTF）
//（3）	扫描磁盘调度算法（SCAN）
