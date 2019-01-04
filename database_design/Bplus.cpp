#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>

using namespace std;

// 定义B+树的阶数
#define M 4
// B+树结点定义
struct BPlusNode
{
    int  amount;      // 该结点中已保存的键值个数
    long key[M];      // 键值数组
    long children[M]; // 子结点位置数组
    long father;      // 父结点位置
    long left;        // 同一层中的左结点位置
    long right;       // 同一层中的右结点位置
    bool isactive;    // 有效位
    bool isleave;     // 标志该结点是否叶结点
};
// 函数头定义
bool findkey   (long key, long &position); // 查找包含给定键值的结点位置
bool insertkey (long key, long position);  // 插入一个新键值
bool deletekey (long key, long position);  // 删除给定的键值
void printkey  (long mode);                // 按照给定模式输出B+树
// 全局变量
static long pre;             // 上一个被访问的结点
static long cur;             // 当前指向的结点
static long root;            // 根结点位置
static long smallest;        // 保存最小关键值的叶结点
static long nodenewposition; // 新插入的结点位置

// 主函数
int main()
{
    BPlusNode node;
    string    command;
    fstream     iofile;
    long keynumber;
    long position = -1;

    // 检测索引文件是否存在，若不存在则创建一个初始化的索引文件，其中包含根结点位置，最小键值位置和一个空结点
    fstream infile ("BPlusTreeData.dat", ios::binary|ios::in);
    if (!infile)
    {
        node.amount = 1;//如果不存在，则创建根结点，且阶数M=4
        for (int i = 0; i < M; ++i)
        {
            node.key[i] = 0;
            node.children[i] = 0;
        }
        node.father = 0;
        node.left = 0;
        node.right = 0;
        node.isactive = true;
        node.isleave = true;
        root = 8;//root为什么＝8？
        smallest = 8;
        fstream outfile ("BPlusTreeData.dat", ios::binary|ios::out);//输出文件BPlusTreeData.dat
        outfile.seekp(0, ios::beg);//指针移到begin处，文件开头
        outfile.write((char *)&root, sizeof(long));//输出根结点
        outfile.write((char *)&smallest, sizeof(long));//输出最小关键字
        outfile.write((char *)&node, sizeof(BPlusNode));//输出头指针？
        outfile.close();
    }
    infile.close();
    // 循环获取命令行，执行给定的命令
    while (true)
    {
        cin >> command >> keynumber;
        // 插入一个新的键值，该值不能与已有关键值重复
      if(command=="insert")
            {
                if (findkey(keynumber, position))
            {
                cout << keynumber << " is already in this B+ tree" << endl;
            }
            else if (insertkey(keynumber, position))
            {
                cout << "Successful inserted in ms" << endl;
            }
            else
                cout << "Action falled" << endl;
            }
        if(command=="delete"){  // 删除给定的键值
            if (deletekey(keynumber, position))
                cout << "Successful deleted" << endl;}

        if(command=="show")
            // 按照指定模式输出B+数
            // 模式“1”输出整棵树结构
            // 模式“2”按照从小到大的顺序输出所有键值
            {printkey(keynumber);}

//        case 't':
//            testBtree(keynumber);
//            break;
        if(command=="exit")
            {return 0;}
        else
            cout << "Please make sure the command is correct" << endl;
            //continue;
        }
    }




