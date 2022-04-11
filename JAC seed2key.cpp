// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <iomanip>

using namespace std;

typedef unsigned int  INT32U;
typedef unsigned char INT8U;

/*江淮解锁算法*/
int main()
{
	INT32U seed[4], Key = 0, Seed = 0, SA[4];
	INT8U securityLevel = 0, i;

	cout << "---------------Welcome JAC Security algorithm------------" << endl << endl;
	cout << "press input seed 4 Bytes[eg 12 34 56 78 By Hex]:";
	cin >> hex >> seed[0] >> seed[1] >> seed[2] >> seed[3] ;
	cout << hex <<  "seed = 0x" << seed[0] << seed[1] << seed[2] << seed[3] << endl;
	cout <<  "press input SA 4 Bytes[eg 12 34 56 78 By Hex]:" ;
	cin >> hex >> SA[0] >> SA[1] >> SA[2] >> SA[3];
	cout << hex << "SA = 0x" << SA[0] << SA[1] << SA[2] << SA[3] << endl;
	cout << "press input securityLevel:";
	cin  >> securityLevel;
	cout << "securityLevel = " << securityLevel << endl;

	Seed = seed[3];
	Seed = Seed | (seed[2] << 8);
	Seed = Seed | (seed[1] << 16);
	Seed = Seed | (seed[0] << 24);

	cout << hex << "Seed = 0x" << Seed << endl;

	if (securityLevel == '1')
	{
		INT32U v0 = Seed, v1 = ~Seed, sum = 0, delta = 0x9E3779B9;
		for (i = 0; i < 2; i++)
		{
			v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + SA[sum & 3]);
			sum += delta;
			v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + SA[(sum >> 11) & 3]);
		}
		Key = v0;
		cout << hex << "securityLevel 1 Key = 0x" << Key << endl;
	}
	else if (securityLevel == '2')
	{
		for (i = 0; i < 3; i++)
		{
			if (SA[0] & 1)  SA[0] = (SA[0] >> 1) + 0x80;
			else SA[0] = SA[0] >> 1;
			//
			if (SA[1] & 1)  SA[1] = (SA[1] >> 1) + 0x80;
			else SA[1] = SA[1] >> 1;
			//
			if (SA[2] & 1)  SA[2] = (SA[2] >> 1) + 0x80;
			else SA[2] = SA[2] >> 1;
			//
			if (SA[3] & 1)  SA[3] = (SA[3] >> 1) + 0x80;
			else SA[3] = SA[3] >> 1;
		}
		INT32U v0 = Seed, v1 = ~Seed, sum = 0, delta = 0x9E3779B9;
		for (i = 0; i < 2; i++)
		{
			v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + SA[sum & 3]);
			sum += delta;
			v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + SA[(sum >> 11) & 3]);
		}
		Key = v0;
		cout << hex << "securityLevel 2 Key = 0x" << Key << endl;
	}
	else
	{
		cout << "securityLevel " << securityLevel << " Invalid" << endl;
	}
	system("pause");
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单


