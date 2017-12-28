

#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<math.h>
#include<windows.h>
using namespace std;

//定义磁盘号的范围（0 <= 磁盘号 < MAX_DISK_NUMBER)
const int MAX_DISK = 200;
//定义一个数组存储要访问的磁盘的序列号
int Disk[MAX_DISK + 1];
int Disk_non[MAX_DISK + 1];
//DISK_NUMBER要访问的磁道的数量，
int DISK_NUMBER = 0;
//保存磁道的访问方向 DIRECTION 为 1 时从小到大， 为 0 时 从大到小；
int DIRECTION = 1;
//定义当前磁道号
int CURRENT_DISK;
#define random(a,b) (rand()%(b-a+1)+a);

//比较大小的方法，用于对 Disk[] 的排序
int compare(int a, int b) {
	return a > b;
}

//（FCFS）
//将当前的磁道号放入要访问的磁道号 Disk[0] 中，可轻易找到其右的要访问的磁道号
void FCFS() {
	//定义变量
	//next 标记 当前磁道 disk[]第一个未调度的磁道号在数组中的序号
	//now 当前磁道；
	int now = 0;
	now = DISK_NUMBER;
	int next = 0;
	//定义寻道长度和平均寻道长度
	double length = 0, avg_length = 0;
	length += fabs(Disk_non[now] - Disk_non[next]);
	cout << Disk_non[0] << "->";
	Sleep(500);
	now = next;
	next++;
		//i++顺序输出
			for (int i=1; i < DISK_NUMBER; i++)
			{
				length += fabs(Disk_non[now] - Disk_non[next]);
				cout<<Disk_non[i]<<"->";
				Sleep(500);
				now = next;
				next++;
			}
	//计算平均寻道时间
	avg_length = length / DISK_NUMBER;
	cout << "平均寻道时间为：" << avg_length << endl;;
}


//最短寻道时间优先（SSTF）
//将当前的磁道号放入要访问的磁道号 Disk[] 中，排序后便可轻易找到其左右的要访问的磁道号
void SSTF() {
	//定义三个变量，left标记 当前磁道 左边第一个微调度的磁道号在数组中的序号
	//right 标记 当前磁道 右边第一个未调度的磁道号在数组中的序号
	//now 当前磁道；
	int left, right, now;
	//定义寻道长度和平均寻道长度
	double length = 0, avg_length = 0;
	//根据磁道移动的方向不同对磁道号进行排序
	if (DIRECTION == 1)
		sort(Disk, Disk + DISK_NUMBER + 1);
	else
		sort(Disk, Disk + DISK_NUMBER + 1, compare);

	//    //输出排序后的Disk[]
	//    for(int i = 0; i < DISK_NUMBER; i++)
	//        printf("%d ",Disk[i]);
	for (int i = 0; i <= DISK_NUMBER; i++)
	{
		//找到当前磁道 左右边第一个未调度的磁道号在数组中的序号
		if (Disk[i] == CURRENT_DISK)
		{
			now = i;
			left = i - 1;
			right = i + 1;
		}
	}
	//不断寻找距离 now 进的并输出，相应改变 now left right
	while (!(left == -1 && right == DISK_NUMBER + 1))
	{
		//如果左侧到了 Disk[] 外则把右边的顺序输出
		if (left <= -1)
		{
			length += fabs(Disk[right] - Disk[now]);
			for (int i = right; i <= DISK_NUMBER; i++)
			{
				if (i > right)
					length += fabs(Disk[i] - Disk[i - 1]);
				cout<<Disk[i]<<"->";
				Sleep(500);
			}
			break;
		}
		//如果右侧到了 Disk[] 外则把左边的顺序输出
		if (right == DISK_NUMBER + 1)
		{
			length += fabs(Disk[now] - Disk[left]);
			for (int i = left; i >= 0; i--)
			{
				if (i < left)
					length += fabs(Disk[i] - Disk[i + 1]);
				cout<<Disk[i]<<"->";
				Sleep(500);
			}
			break;
		}
		//right 距离 <= left 向右走（不管方向为什么，都是往右走，因为方向不同时的排序方法不同，
		//根据方向区分左右距离相等时向左还是向右的话，效果与排序叠加，恰好得到了错误的序列）
		if (fabs(Disk[right] - Disk[now]) <= fabs(Disk[now] - Disk[left]))
		{
			length += fabs(Disk[right] - Disk[now]);
			cout<< Disk[right]<<"->";
			Sleep(500);
			now = right;
			right++;
		}
		else if (fabs(Disk[right] - Disk[now]) > fabs(Disk[now] - Disk[left]))
		{
			length += fabs(Disk[now] - Disk[left]);
			cout<< Disk[left]<<"->";
			Sleep(500);
			now = left;
			left--;
		}
	}
	//计算平均寻道时间
	avg_length = length / DISK_NUMBER;
	cout<<"平均寻道时间为："<< avg_length;
}

//FSCAN
//将当前的磁道号放入要访问的磁道号 Disk[] 中，排序后便可轻易找到其左右的要访问的磁道号
void FSCAN() {   //电梯调度算法  
	int left, right, now;
	//定义寻道长度和平均寻道长度
	double length = 0, avg_length = 0;
	//根据磁道移动的方向不同对磁道号进行排序
	if (DIRECTION == 1)
		sort(Disk, Disk + DISK_NUMBER + 1);
	else
		sort(Disk, Disk + DISK_NUMBER + 1, compare);

	for (int i = 0; i <= DISK_NUMBER; i++)
	{
		//找到当前磁道 左右边第一个未调度的磁道号在数组中的序号
		if (Disk[i] == CURRENT_DISK)
		{
			now = i;
			left = i - 1;
			right = i+1;
		}
	}

	while (left >= 0) {
		length += abs(Disk[now] - Disk[left]);
		Sleep(500);
		cout << Disk[left] <<"->";
		now = left;
		left--;
	}
	while (right <= DISK_NUMBER) {
		length += abs(Disk[now] - Disk[right]);
		Sleep(500);
		cout << Disk[right] << "->";
		now = right;
		right++;
	}
	//计算平均寻道时间
	avg_length = length / DISK_NUMBER;
	cout << "平均寻道时间为：" << avg_length<<endl;
}

int main()
{
	cout<<"input the number of the disk\n";
	cin>>DISK_NUMBER;
	cout << endl;
	cout<<"the Disk[] is \n";
	for (int i = 0; i < DISK_NUMBER; i++) {
		Disk[i] = random(0, 200);
		Disk_non[i] = Disk[i];
		cout << Disk[i]<<"->";
	}
	cout << endl;
	cout<<"input the direction of the disk , right = 1 and left = 0\n";
	cin>>DIRECTION;
	cout << endl;
	cout<<"input the current disk\n";
	cin>>CURRENT_DISK;
	//把CURRENT_DISK加入Disk[]
	Disk[DISK_NUMBER] = CURRENT_DISK;
	Disk_non[DISK_NUMBER] = CURRENT_DISK;
	cout<<"the answer of the SSTF is:\n";
	SSTF();
	cout << endl;
	cout << endl;
	cout << "the answer of the FCFS is:\n";
	FCFS();
	cout << endl;
	cout << "the answer of the FCFS is:\n";
	FSCAN();
	system("pause");
	return 0;
}


