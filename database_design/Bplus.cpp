#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>

using namespace std;

// ����B+���Ľ���
#define M 4
// B+����㶨��
struct BPlusNode
{
    int  amount;      // �ý�����ѱ���ļ�ֵ����
    long key[M];      // ��ֵ����
    long children[M]; // �ӽ��λ������
    long father;      // �����λ��
    long left;        // ͬһ���е�����λ��
    long right;       // ͬһ���е��ҽ��λ��
    bool isactive;    // ��Чλ
    bool isleave;     // ��־�ý���Ƿ�Ҷ���
};
// ����ͷ����
bool findkey   (long key, long &position); // ���Ұ���������ֵ�Ľ��λ��
bool insertkey (long key, long position);  // ����һ���¼�ֵ
bool deletekey (long key, long position);  // ɾ�������ļ�ֵ
void printkey  (long mode);                // ���ո���ģʽ���B+��
// ȫ�ֱ���
static long pre;             // ��һ�������ʵĽ��
static long cur;             // ��ǰָ��Ľ��
static long root;            // �����λ��
static long smallest;        // ������С�ؼ�ֵ��Ҷ���
static long nodenewposition; // �²���Ľ��λ��

// ������
int main()
{
    BPlusNode node;
    string    command;
    fstream     iofile;
    long keynumber;
    long position = -1;

    // ��������ļ��Ƿ���ڣ����������򴴽�һ����ʼ���������ļ������а��������λ�ã���С��ֵλ�ú�һ���ս��
    fstream infile ("BPlusTreeData.dat", ios::binary|ios::in);
    if (!infile)
    {
        node.amount = 1;//��������ڣ��򴴽�����㣬�ҽ���M=4
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
        root = 8;//rootΪʲô��8��
        smallest = 8;
        fstream outfile ("BPlusTreeData.dat", ios::binary|ios::out);//����ļ�BPlusTreeData.dat
        outfile.seekp(0, ios::beg);//ָ���Ƶ�begin�����ļ���ͷ
        outfile.write((char *)&root, sizeof(long));//��������
        outfile.write((char *)&smallest, sizeof(long));//�����С�ؼ���
        outfile.write((char *)&node, sizeof(BPlusNode));//���ͷָ�룿
        outfile.close();
    }
    infile.close();
    // ѭ����ȡ�����У�ִ�и���������
    while (true)
    {
        cin >> command >> keynumber;
        // ����һ���µļ�ֵ����ֵ���������йؼ�ֵ�ظ�
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
        if(command=="delete"){  // ɾ�������ļ�ֵ
            if (deletekey(keynumber, position))
                cout << "Successful deleted" << endl;}

        if(command=="show")
            // ����ָ��ģʽ���B+��
            // ģʽ��1������������ṹ
            // ģʽ��2�����մ�С�����˳��������м�ֵ
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




