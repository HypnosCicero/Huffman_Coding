#include<iostream>
#include<algorithm>
#include<string>
#include<fstream>
#define Maxsize 100000
using namespace std;
int top = 0;//存储顶点
bool cmp(struct stack a, struct stack b);
struct ElemType {
	int weight = -1;//假定权值为整数
	int parent = -1, lchild = -1, rchild = -1;//游标
	char name = '#';
	int flag = 0;
	int is_traversal = 0;
	//int is_name=0;
};
struct stack {//队列
	int value = 0;
	char ch;
}Stack[Maxsize];
stack* place = Stack;//这是为了建树的时候place++;
void HuffmanTree(ElemType huffTree[], struct stack Stack[], int n);
void Select(ElemType huffTree[], int* pi1, int* pi2, int number, int k);
int statistics();
void huffmancoding(ElemType huffTree[], int n);
void huffmandecipher(ElemType huffTree[], int n);
int main() {
	struct ElemType huffTree[1024];
	char ch_name[Maxsize];
	int number = 0;
	int choise = 10;
	number = statistics();//统计
	//cout << number << endl;
	sort(Stack, &Stack[number], cmp);//排序
	HuffmanTree(huffTree, Stack, number);//建树
	while (choise != 0) {
		cout << "文件编码以及译码" << endl;
		cout << "--------------------------" << endl;
		cout << "有以下操作" << endl;
		cout << "1.对某一个文件进行编码" << endl;
		cout << "2.对某一个文件进行译码" << endl;
		cout << "0.退出程序" << endl;
		cout << "--------------------------" << endl;
		cout << "请输入你所要进行操作的编号:" << endl;
		cin >> choise;
		switch (choise) {
		case 1: {

			for (int i = 0; huffTree[i].parent != -1; i++) {
				cout << huffTree[i].name << " " << huffTree[i].weight << " ";
				cout << huffTree[i].parent << " " << huffTree[i].lchild << " ";
				cout << huffTree[i].rchild << endl;
			}
			system("pause");
			huffmancoding(huffTree, number);
			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		case 2: {
			huffmandecipher(huffTree, number);
			system("pause");
			system("cls");
			break;
		}
		case 0: {
			break;
		}
		default: {
			cout << "发生错误";
			break;
		}
		}
	}
	return 0;
}
void HuffmanTree(ElemType huffTree[], struct stack Stack[], int n) {
	int i = 0, k = 0, i1 = 0, i2 = 0;
	for (i = 0; i < 2 * n - 1; i++) {
		huffTree[i].parent = -1;
		huffTree[i].lchild = huffTree[i].rchild = -1;
	}
	for (i = 0; i < n; i++) {//存储叶子结点的权值。
		huffTree[i].weight = Stack[i].value;
		huffTree[i].name = Stack[i].ch;
		//cout << Stack[i].ch << endl;
		//system("pause");
	}
	for (k = n; k < 2 * n - 1; k++) {
		Select(huffTree, &i1, &i2, n, k);//权值最小的根结点下标为i1和i2
		huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
		Stack[k].value = huffTree[k].weight;
		huffTree[i1].parent = k;
		huffTree[i2].parent = k;
		huffTree[k].lchild = i1;
		huffTree[k].rchild = i2;
		place += 2;//奇数则爆炸
	}
	top = k - 1;//编码开始的头结点
	//cout << "顶点的编号" << flag<<endl;//为了编码开始
}
void Select(ElemType huffTree[], int* pi1, int* pi2, int number, int k) {
	for (int i = k - number; i < 2 * number - 1; i++) {
		if (huffTree[i].weight == place->value && huffTree[i].flag == 0) {
			*pi1 = i;
			*pi2 = i + 1;
			//cout << "*pi1=" << *pi1 << " " << "*pi2=" << *pi2 << endl;
			huffTree[i].flag = 1;
			huffTree[i + 1].flag = 1;
			break;
		}
		//cout <<"第"<<i<< "个flag=" << huffTree[i].flag << endl;
	}
}
bool cmp(struct stack a, struct stack b) {
	return a.value < b.value;
}
int statistics() {
	char essay[1024];
	int ch[97] = { 0 };
	int all_of_essay = 0;
	int non_of_essay = 0;
	char* p;
	p = essay;
	memset(essay, 0, 1024);
	fstream myfile("D:\\program for Visual Studio\\Coding\\Huffman\\English_essay.txt");
	if (!myfile) {
		cout << "can not open this file" << endl;
	}
	else {
		while ((*p = myfile.get()) != EOF) {
			if (*p >= ' ' && *p <= '~') {
				ch[*p - ' ']++;
			}
			else if (*p == '\r') {
				ch[95]++;
			}
			else if (*p == '\n') {
				ch[96]++;
			}
			p++;//字符不断往后读.
		}
		int j = 0;//j为Stack的下标;
		for (int i = 0; i < 97; i++) {//应该是95而不是87
			if (ch[i] == 0) {
				non_of_essay++;
			}
			else if (i >= 0 && i <= 94) {
				Stack[j].value = ch[i];//出现的频率
				Stack[j].ch = i + ' ';
				j++;
			}
			else if (i == 95) {
				Stack[j].value = ch[i];
				Stack[j].ch = 14;
				j++;
			}
			else if (i == 96) {
				Stack[j].value = ch[i];
				Stack[j].ch = 10;
				j++;
			}
		}
		all_of_essay = 97 - non_of_essay;
	}
	//cout << "all_of_essay=" << all_of_essay << endl;//all_of_essay是总数
	myfile.close();
	return all_of_essay;
}
void huffmancoding(ElemType huffTree[], int n) {
	char essay[1024];
	int i = 0, j = 0;//i游标
	int stack[1024];//这是栈为了遍历的前后结点而造
	int top_of_stack = 0;
	char show[30];//这是展示的字符串
	//char* new_path = "D:\\program for Visual Studio\\huffman\\Debug";
	char DATA[10240];
	char* data = DATA;
	for (int i = 0; i < 30; i++) {
		show[i] = '#';
	}
	show[29] = '\0';
	char* p;
	p = essay;
	memset(p, 0, 1024);
	fstream myfile("D:\\program for Visual Studio\\Coding\\Huffman\\English_essay.txt");
	fstream Coding("D:\\program for Visual Studio\\Coding\\Huffman\\decrypted.txt");
	if (!myfile) {
		cout << "myfile con not open" << endl;
	}
	else {
		while ((*p = myfile.get()) != EOF) {//最外面的循环是为了将字符全部匹配
			i = top;//因为每次指针往后移动都要从top开始查找。
			top_of_stack = 0;
			stack[top_of_stack] = i;//这里也需要这个
			j = 0;
			while (1) {
				huffTree[stack[top_of_stack]].is_traversal = 1;
				if (*p != huffTree[stack[top_of_stack]].name) {
					if (*p != huffTree[stack[top_of_stack]].name && huffTree[stack[top_of_stack]].lchild == -1 && huffTree[stack[top_of_stack]].rchild == -1 && huffTree[huffTree[stack[top_of_stack - 1]].rchild].is_traversal == 0) {
						stack[top_of_stack] = huffTree[stack[top_of_stack - 1]].rchild;//回溯*1;访问右节点;
						show[j] = '1';//j的0变为1;
						huffTree[stack[top_of_stack]].is_traversal = 1;
					}
					if (*p != huffTree[stack[top_of_stack]].name && huffTree[stack[top_of_stack]].lchild == -1 && huffTree[stack[top_of_stack]].rchild == -1 && huffTree[huffTree[stack[top_of_stack - 1]].rchild].is_traversal == 1) {
						stack[top_of_stack] = 0;
						--top_of_stack;
						show[j] = '#';
						--j;//都只是回溯*1;
						huffTree[stack[top_of_stack]].is_traversal = 1;
					}
					if (*p != huffTree[stack[top_of_stack]].name && huffTree[stack[top_of_stack]].lchild != -1 && huffTree[stack[top_of_stack]].rchild != -1 && huffTree[huffTree[stack[top_of_stack]].lchild].is_traversal == 1 && huffTree[huffTree[stack[top_of_stack]].rchild].is_traversal == 1) {
						if (huffTree[stack[top_of_stack - 1]].rchild == stack[top_of_stack]) {
							stack[top_of_stack] = 0;//只回溯
							--top_of_stack;
							show[j] = '#';
							--j;
							huffTree[stack[top_of_stack]].is_traversal = 1;
						}
						else {
							stack[top_of_stack] = huffTree[stack[top_of_stack - 1]].rchild;//回溯*1;访问右结点
							show[j] = '1';//j的0变为1;
							huffTree[stack[top_of_stack]].is_traversal = 1;
						}
					}
				}
				else {
					break;
				}
				if (huffTree[huffTree[stack[top_of_stack]].lchild].is_traversal == 0) {
					stack[++top_of_stack] = huffTree[stack[top_of_stack - 1]].lchild;
					j++;
					show[j] = '0';
				}
				huffTree[stack[top_of_stack]].is_traversal = 1;
			}
			show[j + 1] = '\0';
			for (i = 1; show[i] != '\0'; i++) {
				*data = show[i];
				cout << show[i];
				data++;
			}
			for (int k = 0; k <= top; k++) {//初始化判断遍历的值
				huffTree[k].is_traversal = 0;
			}
			p++;
		}
	}
	myfile.close();
	cout << endl;
	if (!Coding) {
		cout << "con not open Coding.txt" << endl;
	}
	else {
		*data = '\0';
		for (int d = 0; DATA[d] != '\0'; d++) {
			Coding << DATA[d];
		}
	}
	Coding.close();
}
void huffmandecipher(ElemType huffTree[], int n) {
	char essay[10240];
	char* p;
	p = essay;
	int i = top;
	memset(essay, 0, 1024);
	ifstream cipeher;
	cipeher.open("D:\\program for Visual Studio\\Coding\\Huffman\\decrypted.txt");
	if (!cipeher) {
		cout << "con not open this file" << endl;
	}
	else {
		i = top;
		while ((*p = cipeher.get()) != EOF) {
			if (*p == '0' && huffTree[i].name == '#') {
				i = huffTree[i].lchild;
				//cout << i << endl;
				//system("pause");
			}
			else if (*p == '1' && huffTree[i].name == '#') {
				i = huffTree[i].rchild;
				//cout << i << endl;
				//system("pause");
			}
			else if (huffTree[i].name != '#') {
				cout << huffTree[i].name;
				if (*p == '0') {
					i = huffTree[top].lchild;
					//cout << i << endl;
					//system("pause");
				}
				else {
					i = huffTree[top].rchild;
					//cout << i << endl;
					//system("pause");
				}
			}
			p++;
		}
	}
	cout << endl;
	cipeher.close();
}
