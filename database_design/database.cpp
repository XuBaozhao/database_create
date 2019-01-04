#include"database.h"
#include"drop_database.cpp"
#include"create_database.cpp"
#include"create_table.cpp"
#include"drop_table.cpp"
#include"show_tables.cpp"
#include"show_databases.cpp"
#include"create_view.cpp"
#include"help_table.cpp"
#include"select_first.cpp"
#include"select_second.cpp"
#include"select_three_four.cpp"
#include"insert_into.cpp"
#include"delete_from_table.cpp"
#include"update.cpp"
#include"show_views.cpp"
#include"delete_view.cpp"


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
bool findkey   (long key, long &position,string ne); // ���Ұ���������ֵ�Ľ��λ��
bool insertkey (long key, long position,string ne);  // ����һ���¼�ֵ
bool deletekey (long key, long position,string ne);  // ɾ�������ļ�ֵ
void printkey  (long mode,string ne);                // ���ո���ģʽ���B+��
// ȫ�ֱ���
static long pre;             // ��һ�������ʵĽ��
static long cur;             // ��ǰָ��Ľ��
static long root;            // �����λ��
static long smallest;        // ������С�ؼ�ֵ��Ҷ���
static long nodenewposition; // �²���Ľ��λ��


BPlusNode node;
string    command;
fstream     iofile;
long keynumber;
long position = -1;

// ��������ļ��Ƿ���ڣ����������򴴽�һ����ʼ���������ļ������а��������λ�ã���С��ֵλ�ú�һ���ս��
fstream infile ("BPlusTreeData.dat", ios::binary|ios::in);


// ���Ұ���������ֵ�Ľ��λ�ã����ҵ��򷵻ء�true��
// ��position�����������ʵĽ��λ��
bool findkey (long key, long &position,string ne)
{
    BPlusNode node;
    long point;
    string we = ne+".dat";
    //const char * filename = ne+".dat";
    const char *p = we.c_str();
    fstream iofile (p, ios::binary|ios::in|ios::out);
    iofile.seekp(0, ios::beg);
    iofile.read((char *)&root, sizeof(long));
    iofile.seekp(root, ios::beg);
    while (true)
    {
        cur = iofile.tellp();
        iofile.read((char *)&node, sizeof(BPlusNode));
        if(!node.isactive)
            continue;

        // B+��ֻ��Ҷ��㱣���¼��Ϣ
        // ���Բ��ұ���ִ�е�Ҷ���
        if(!node.isleave)   // ����ý�㲻��Ҷ��㣬����ݼ�ֵ���������ĸ��ӽ��
        {
            for (int i = 1; i < node.amount; ++i)
            {
                point = -1;
                if (node.key[i] > key)
                {
                    point = node.children[i-1];
                    break;
                }
            }
            if (point == -1)
                point = node.children[node.amount-1];
            iofile.seekp(point, ios::beg);
            pre = cur;
        }
        else     // ����ý����Ҷ��㣬��˳����ʽ���еļ�ֵ
        {
            for (int i = 1; i < node.amount; ++i)
            {
                if (node.key[i] == key)
                {
                    position = cur;
                    iofile.close();
                    return true;
                }
            }
            position = cur;
            iofile.close();
            return false;
        }
    }
}

// ���ո�����ʽ���B+��
void printkey (long mode,string ne)
{
    BPlusNode node;
    int i = 1, k = 1;
    string we = ne+".dat";
    //const char * filename = ne+".dat";
    const char *p = we.c_str();
    fstream iofile(p, ios::binary|ios::in|ios::out);

    // �Ӹ���㿪ʼ��ȱ������������B+���ṹ
    if (mode == 1)
    {
        iofile.seekp(0, ios::beg);
        iofile.read((char *)&root, sizeof(long));
        iofile.seekp(root, ios::beg);
        do
        {
            cur = iofile.tellp();
            cout << "level " << k << ":"<<endl;
            do
            {
                iofile.read((char *)&node, sizeof(BPlusNode));
                cout << "node " << i << ": "<<endl;
                for (int j = 1; j < node.amount; ++j)
                    cout << node.key[j] << " "<<endl;
                if (node.right == 0)
                {
                    i = 1;
                    cout << endl;
                    break;
                }
                iofile.seekp(node.right, ios::beg);
                ++i;
            }
            while(true);
            iofile.seekp(cur, ios::beg);
            iofile.read((char *)&node, sizeof(BPlusNode));
            if (node.children[0] == 0)
                break;
            iofile.seekp(node.children[0], ios::beg);
            ++k;
        }
        while (true);
        iofile.close();
    }
    else if (mode == 2)     // �Ӱ�����С��ֵ��Ҷ��㿪ʼ���մ�С�����˳��������м�ֵ
    {
        iofile.seekp(4, ios::beg);
        iofile.read((char *)&smallest, sizeof(long));
        iofile.seekp(smallest, ios::beg);
        do
        {
            iofile.read((char *)&node, sizeof(BPlusNode));
            for (int l = 1; l < node.amount; ++l)
                cout << node.key[l] << " ";
            cout<<endl;
            if (node.right == 0)
            {
                cout << endl;
                break;
            }
            iofile.seekp(node.right, ios::beg);
        }
        while(true);
        iofile.close();
    }
}

// ��λ�ڡ�position���Ľ���в���һ���¼�ֵ��key��
// ����B+���Ĺ��򣬸���������ѽ��
bool insertkey (long key, long position,string ne)
{
    //  cout<<"-----------------------------"<<endl;
    fstream iofile;
    string we = ne+".dat";
    //const char * filename = ne+".dat";
    const char *p = we.c_str();
    iofile.open(p, ios::binary|ios::in|ios::out);
    BPlusNode node;
    BPlusNode nodenew;
    BPlusNode nodetemp1, nodetemp2;
    long keytemp[M];
    long childrentemp[M+1];
    iofile.seekp(0, ios::end);
    long posEnd = iofile.tellp();
    //���ڵ����֮���½����ڵ�
    if (position == 0)
    {
        iofile.seekp(0, ios::beg);
        iofile.read((char *)&root, sizeof(long));
        iofile.seekp(root, ios::beg);
        iofile.read((char *)&node, sizeof(BPlusNode));
        nodenew.amount = 2;
        nodenew.key[1] = key;
        nodenew.children[0] = root;
        nodenew.children[1] = nodenewposition;
        nodenew.father = 0;
        nodenew.left = 0;
        nodenew.right = 0;
        nodenew.isactive = true;
        nodenew.isleave = false;
        iofile.seekp(8, ios::beg);
        do
        {
            cur = iofile.tellp();
            iofile.read((char *)&nodetemp2, sizeof(BPlusNode));
        }
        while(nodetemp2.isactive && iofile.tellp() < posEnd);
        if (nodetemp2.isactive)
        {
            nodenewposition = iofile.tellp();
            iofile.write((char *)&nodenew, sizeof(BPlusNode));
        }
        else
        {
            iofile.seekp(cur, ios::beg);
            nodenewposition = cur;
            iofile.write((char *)&nodenew, sizeof(BPlusNode));
        }
        root = nodenewposition;
        iofile.seekp(0, ios::beg);
        iofile.write((char *)&root, sizeof(long));
        for (int i = 0; i <= 1; ++i)
        {
            iofile.seekp(nodenew.children[i], ios::beg);
            iofile.read((char *)&nodetemp1, sizeof(BPlusNode));
            nodetemp1.father = nodenewposition;
            iofile.seekp(nodenew.children[i], ios::beg);
            iofile.write((char *)&nodetemp1, sizeof(BPlusNode));
        }
        iofile.close();
        return true;
    }
    else     // û�з��ѵ������
    {
        int insertposition = 0;
        iofile.seekp(position, ios::beg);
        iofile.read((char *)&node, sizeof(BPlusNode));
        if (node.amount < M)   // ����л��п�λ�����²���ļ�ֵ������Ҫ����
        {
            // ���մ�С�����˳����������ԭ�м�ֵ���²���ļ�ֵ
            bool issort1 = false;
            for (int i = 1; i < node.amount; ++i)
            {
                if (node.key[i] > key)
                {
                    for (int j = node.amount - i, k = 0; j > 0; --j, ++k)
                        node.key[node.amount-k] = node.key[node.amount-k-1];
                    node.key[i] = key;
                    insertposition = i;
                    issort1 = true;
                    break;
                }
            }
            if (!issort1)
            {
                node.key[node.amount] = key;
                insertposition = node.amount;
            }
            node.amount++;
            if (!node.isleave)
            {
                for (int p = node.amount-1; p > insertposition; --p)
                    node.children[p] = node.children[p-1];
                node.children[insertposition] = nodenewposition;
            }
            iofile.seekp(position, ios::beg);
            iofile.write((char *)&node, sizeof(BPlusNode));
            iofile.close();
            return true;
        }
        else     // �����û�п�λ�����²���ļ�ֵ��������ѳ��������
        {
            long nextinsertkey = 0;
            // ���մ�С�����˳����������ԭ�м�ֵ���²���ļ�ֵ
            // ���Ұ��ռ�ֵ��˳���������б����ӽ��λ�õ�����
            bool issort2 = false;
            for (int m = 1, n = 0, o = 0; m < M; ++m, ++o)
            {
                if (node.key[m] < key || issort2)
                {
                    keytemp[m-1+n] = node.key[m];
                    childrentemp[o+n] = node.children[o];
                }
                else
                {
                    keytemp[m-1] = key;
                    childrentemp[o] = node.children[o];
                    childrentemp[o+1] = nodenewposition;
                    n = 1;
                    --m;
                    issort2 = true;
                }
            }
            if (!issort2)
            {
                keytemp[M-1] = key;
                childrentemp[M-1] = node.children[M-1];
                childrentemp[M] = nodenewposition;
            }
            node.amount = M/2+1;
            if (!node.isleave)   // �����ڲ����ķ�ʽ�����½��
            {
                nodenew.amount = M/2;
                for (int i = 0, j = 1; i <= M; ++i)
                {
                    if (i < M/2)
                    {
                        node.key[i+1] = keytemp[i];
                        node.children[i] = childrentemp[i];
                    }
                    else if (i == M/2)
                    {
                        nextinsertkey = keytemp[i];
                        node.children[i] = childrentemp[i];
                    }
                    else if (i < M)
                    {
                        nodenew.key[j] = keytemp[i];
                        nodenew.children[j-1] = childrentemp[i];
                        node.key[i] = 0;
                        ++j;
                    }
                    else if (i == M)
                    {
                        nodenew.children[j-1] = childrentemp[i];
                    }
                }
                nodenew.isleave = false;
            }
            else     // ����Ҷ���ķ�ʽ�����½��
            {
                nodenew.amount = M/2+1;
                for (int i = 0, j = 1; i < M; ++i)
                {
                    if (i < M/2)
                    {
                        node.key[i+1] = keytemp[i];
                    }
                    else
                    {
                        nodenew.key[j] = keytemp[i];
                        if (i < M-1)
                            node.key[i+1] = 0;
                        ++j;
                    }
                }
                nextinsertkey = nodenew.key[1];
                nodenew.isleave = true;
                for (int n = 0; n < M; ++n)
                    nodenew.children[n] = 0;
            }
            nodenew.key[0] = 0;
            nodenew.father = node.father;
            nodenew.left = position;
            nodenew.right = node.right;
            nodenew.isactive = true;
            // �����½��Ĳ���λ��
            // �������ļ��д���һ��������ɾ���Ľ�㣬�����½�㸲�ǵ�������
            // �������������Ľ�㣬���½����ӵ������ļ�β��
            iofile.seekp(8, ios::beg);
            do
            {
                cur = iofile.tellp();
                iofile.read((char *)&nodetemp2, sizeof(BPlusNode));
            }
            while(nodetemp2.isactive && iofile.tellp() < posEnd);
            if (nodetemp2.isactive)
            {
                nodenewposition = iofile.tellp();
                iofile.write((char *)&nodenew, sizeof(BPlusNode));
            }
            else
            {
                iofile.seekp(cur, ios::beg);
                nodenewposition = cur;
                iofile.write((char *)&nodenew, sizeof(BPlusNode));
            }
            node.right = nodenewposition;
            iofile.seekp(position, ios::beg);
            iofile.write((char *)&node, sizeof(BPlusNode));
            iofile.close();
            if (insertkey(nextinsertkey, nodenew.father,ne))  // �ݹ���ò����㷨�����Ѻ���Ҫ���뵽�����ļ�ֵ���뵽�������
                return true;
            else
                return false;
        }
    }
}

// ɾ�������ļ�ֵ
// ���㷨������B+����ɾ������
// ֻ�Ǽ򵥵ؽ�����ɾ����ֵ���������ֵ���²���һ��
bool deletekey (long key, long position,string ne)
{
    fstream iofile;
    string we = ne+".dat";
    //const char * filename = ne+".dat";
    const char *p = we.c_str();
    iofile.open(p, ios::binary|ios::in|ios::out);
    BPlusNode node;
    long *keynumbertemp = new long[1000];
    long number = 0;
    long posEnd;
    iofile.seekp(0, ios::end);
    posEnd = iofile.tellp();
    iofile.seekp(4, ios::beg);
    iofile.read((char *)&smallest, sizeof(long));
    iofile.seekp(smallest, ios::beg);
    do
    {
        iofile.read((char *)&node, sizeof(BPlusNode));
        for (int i = 1; i < node.amount; ++i)
        {
            keynumbertemp[number] = node.key[i];
            ++number;
        }
        if (node.right == 0)
        {
            --number;
            break;
        }
        iofile.seekp(node.right, ios::beg);
    }
    while(true);
    node.amount = 1;
    for (int j = 0; j < M; ++j)
    {
        node.key[j] = 0;
        node.children[j] = 0;
    }
    node.father = 0;
    node.left = 0;
    node.right = 0;
    node.isactive = true;
    node.isleave = true;
    root = 8;
    smallest = 8;
    iofile.seekp(0, ios::beg);
    iofile.write((char *)&root, sizeof(long));
    iofile.write((char *)&smallest, sizeof(long));
    iofile.write((char *)&node, sizeof(BPlusNode));
    for (; iofile.tellp() < posEnd;)
    {
        iofile.read((char *)&node, sizeof(BPlusNode));
        node.isactive = false;
        iofile.seekp(-long(sizeof(BPlusNode)), ios::cur);
        iofile.write((char *)&node, sizeof(BPlusNode));
    }
    iofile.close();
    for (int k = 0; k <= number; ++k)
    {
        if (keynumbertemp[k] == key)
            continue;
        findkey(keynumbertemp[k], position,ne);
        insertkey(keynumbertemp[k], position,ne);
    }
    return true;
}

void create_index(string name,char words[][21],string ne)
{

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
        string we = ne+".dat";
        //const char * filename = ne+".dat";
        const char *p = we.c_str();
        fstream outfile (p, ios::binary|ios::out);//����ļ�BPlusTreeData.dat
        outfile.seekp(0, ios::beg);//ָ���Ƶ�begin�����ļ���ͷ
        outfile.write((char *)&root, sizeof(long));//��������
        outfile.write((char *)&smallest, sizeof(long));//�����С�ؼ���
        outfile.write((char *)&node, sizeof(BPlusNode));//���ͷָ�룿
        outfile.close();
    }
    infile.close();


    long position = -1;
    // cout<<"---------------------------"<<endl;
    FILE *fp ;
    int i,j,k,h;
    const char *p = name.c_str();
    fp=fopen(p, "r");

    if ( fp==NULL )
    {
        printf("��ȡ��ʾʧ��\n");
    }
    for( i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
    {
        if ( fscanf(fp, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
            break;
    }
    fclose(fp);

    int pm=0;
    for(int j=0; j<i; j++)
    {
        string __s(words[j]);
        if(__s!="P")
        {
            pm++;
        }
        else
        {
            break;
        }
    }

    int column= pm/7;
    pm = pm+1;

    //  cout<<"column---"<<column<<"-----pm"<<pm<<endl;
    for(int j=pm; j<i; j++)
    {
        if((j-pm)%(column+1)==0)
        {
            string s(words[j]);
            stringstream ss;
            int cp;
            ss<<s;
            ss>>cp;
            // cp = (long)cp;
            //   cout<<"....."<<cp<<"....."<<endl;
            findkey(cp, position,ne);
            insertkey(cp, position,ne);
        }
    }
    // printkey(1);
}


void insert_index_name(string index_name,string a)
{
    string name="index_name.txt";
    FILE *FP;
    const char *p = name.c_str();
    if((FP=fopen(p,"a"))==NULL)
    {
        cout<<"���ݱ��ʧ�ܣ�"<<endl;
    }
    else
    {
        cout<<"���ݱ�򿪳ɹ���"<<endl;
        const char *ff = index_name.c_str();
        const char *gg = a.c_str();
        fprintf(FP,"%s",ff);
        fprintf(FP,"%c",' ');
        fprintf(FP,"%s",gg);
        fputc(10,FP);
        fclose(FP);
    }
}

void read_index(string name,char words[][21])
{
    FILE *fp ;
    int i,j,k,h;
    const char *p = name.c_str();
    fp=fopen(p, "r");

    if ( fp==NULL )
    {
        printf("��ȡ��ʾʧ��\n");
    }
    for( i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
    {
        if ( fscanf(fp, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
            break;
    }
    fclose(fp);

    cout<<"................����������Ϣչʾ��"<<endl;
    for(int j=0; j<i; j++)
    {

        if(j%2==0&&j!=1)

        {

            string __s(words[j]);
            string __s1(words[j+1]);
            cout<<"................������"<<__s<<endl;
            cout<<"................����"<<__s1<<endl;
            printkey(2,__s);
            printkey(1,__s);

        }
    }
}


void select_and(string xing,string name,string cmf,string cms,string first,string second,char words[][21])
{
    FILE *fp ;
    int i,j,k,h;
    const char *p = name.c_str();
    fp=fopen(p, "r");

    if ( fp==NULL )
    {
        printf("��ȡ��ʾʧ��\n");
    }

    for( i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
    {
        if ( fscanf(fp, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
            break;
    }
    fclose(fp);

    int pm=0;
    for(int j=0; j<i; j++)
    {
        string __s(words[j]);
        if(__s!="P")
        {
            pm++;
        }
        else
        {
            break;
        }
    }
    pm = pm/7;
//cout<<"pm...."<<pm<<endl;

    if(xing=="*")
    {
        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;

        int colomn_num = 0;
        for( j=1; j<i; j++ ) //�������������
        {
            string ss(words[j-1]);
            if((j==1)||(j>=7&&(j-1)%7==0&&ss=="Q"))
            {
                printf( " %-10s|", words[j] ) ;
                colomn_num++;
            }

        }

        cout<<endl;
        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;
    }


    int cmf_index=0;
    int cms_index=0;
    int xing_index =0;

    for(int j=0; j<i; j++)
    {
        string s(words[j]);
        if(s==cmf)
        {
            cmf_index=(j-1)/7+1;
        }
        if(s==cms)
        {
            cms_index=(j-1)/7+1;
        }
        if(xing!="*")
        {
            if(s==xing)
                xing_index=(j-1)/7+1;
        }
    }


    int bigo=cmf_index-xing_index;
    int kula=0;
    int cha = cmf_index - cms_index;
    int you = 0;

    for(int j=0; j<i; j++)
    {
        string s(words[j]);
        string _s(words[j-cha]);
        if(s==first&&_s==second)
        {
            you = 1;
            // cout<<"wwwww"<<endl;
            if(xing=="*")
            {
                for(int k=1; k<=pm; k++)
                {
                    printf( " %-10s|", words[j-cmf_index+k]) ;

                }
                cout<<endl;
            }
            else
            {
                if(kula==0)
                {
                    cout<<"------------"<<endl;
                    //cout<<"| "<<table<<" |"<<endl;
                    cout<<"   "<<xing<<endl;
                    cout<<"------------"<<endl;
                    kula=1;
                }
                printf( " %-10s|\n",words[j-bigo] );
                cout<<"------------";
                cout<<endl;
            }
        }

    }

    if(you==0)
    {
        cout<<"�����ҵļ�¼�����ڣ�"<<endl;
    }
//cout<<cmf_index<<"...."<<cms_index<<endl;
    if(xing=="*")
    {
        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;
    }

}

void select_or(string xing,string name,string cmf,string cms,string first,string second,char words[][21])
{
    FILE *fp ;
    int i,j,k,h;
    const char *p = name.c_str();
    fp=fopen(p, "r");

    if ( fp==NULL )
    {
        printf("��ȡ��ʾʧ��\n");
    }

    for( i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
    {
        if ( fscanf(fp, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
            break;
    }
    fclose(fp);

    int pm=0;
    for(int j=0; j<i; j++)
    {
        string __s(words[j]);
        if(__s!="P")
        {
            pm++;
        }
        else
        {
            break;
        }
    }
    pm = pm/7;
//cout<<"pm...."<<pm<<endl;

    if(xing=="*")
    {
        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;

        int colomn_num = 0;
        for( j=1; j<i; j++ ) //�������������
        {
            string ss(words[j-1]);
            if((j==1)||(j>=7&&(j-1)%7==0&&ss=="Q"))
            {
                printf( " %-10s|", words[j] ) ;
                colomn_num++;
            }

        }

        cout<<endl;
        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;
    }


    int cmf_index=0;
    int cms_index=0;
    int xing_index =0;

    for(int j=0; j<i; j++)
    {
        string s(words[j]);
        if(s==cmf)
        {
            cmf_index=(j-1)/7+1;
        }
        if(s==cms)
        {
            cms_index=(j-1)/7+1;
        }
        if(xing!="*")
        {
            if(s==xing)
                xing_index=(j-1)/7+1;
        }
    }


    int bigo=cmf_index-xing_index;
    int kula=0;
    int cha = cmf_index - cms_index;
    int you = 0;

    for(int j=0; j<i; j++)
    {
        string s(words[j]);
        string _s(words[j-cha]);
        if(s==first||_s==second)
        {
            you = 1;
            // cout<<"wwwww"<<endl;
            if(xing=="*")
            {
                for(int k=1; k<=pm; k++)
                {
                    printf( " %-10s|", words[j-cmf_index+k]) ;

                }
                cout<<endl;
            }
            else
            {
                if(kula==0)
                {
                    cout<<"------------"<<endl;
                    //cout<<"| "<<table<<" |"<<endl;
                    cout<<"   "<<xing<<endl;
                    cout<<"------------"<<endl;
                    kula=1;
                }
                printf( " %-10s|\n",words[j-bigo] );
                cout<<"------------";
                cout<<endl;
            }
        }

    }

    if(you==0)
    {
        cout<<"�����ҵļ�¼�����ڣ�"<<endl;
    }
//cout<<cmf_index<<"...."<<cms_index<<endl;
    if(xing=="*")
    {
        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;
    }

}

void in_select(string in[20],string name,string name2,char words[][21])
{

    FILE *fp ;
    int i,j,k,h;
    const char *p = name.c_str();
    fp=fopen(p, "r");

    if ( fp==NULL )
    {
        printf("��ȡ��ʾʧ��\n");
    }

    for( i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
    {
        if ( fscanf(fp, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
            break;
    }
    fclose(fp);


    int pm=0;
    for(int j=0; j<i; j++)
    {
        string __s(words[j]);
        if(__s!="P")
        {
            pm++;
        }
        else
        {
            break;
        }
    }
    pm = pm/7;



    int name2_index=0;
    for(int j=0; j<i; j++)
    {
        string s(words[j]);
        if(s==name2)
        {
            name2_index = j;
            break;
        }
    }
    if(name2_index==0)
    {
        cout<<"�������ݱ����ڣ�"<<endl;
    }
    else
    {
        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;

        int colomn_num = 0;
        for( j=1; j<i; j++ ) //�������������
        {
            string ss(words[j-1]);
            if((j==1)||(j>=7&&(j-1)%7==0&&ss=="Q"))
            {
                printf( " %-10s|", words[j] ) ;
                colomn_num++;
            }
        }

        cout<<endl;
        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;
        name2_index = (name2_index-1)/7+1;


        for(int j=0; j<20; j++)
        {
            if(in[j]=="")
            {
                break;
            }
            for(int k=0; k<i; k++)
            {
                string _s(words[k]);
                if(in[j]==_s)
                {
                    for(int p=1; p<=pm; p++)
                    {
                        printf( " %-10s|",words[k-name2_index+p]);
                    }
                    cout<<endl;
                }
            }
        }
        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;
    }
}


void between_select(string xing,string name,string name2,string sf,string ss,char words[][21])
{

    FILE *fp ;
    int i,j,k,h;
    const char *p = name.c_str();
    fp=fopen(p, "r");

    if ( fp==NULL )
    {
        printf("��ȡ��ʾʧ��\n");
    }

    for( i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
    {
        if ( fscanf(fp, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
            break;
    }
    fclose(fp);

    int pm=0;
    for(int j=0; j<i; j++)
    {
        string __s(words[j]);
        if(__s!="P")
        {
            pm++;
        }
        else
        {
            break;
        }
    }
    pm = pm/7;


    int p_index=0;
    for(int j=0; j<i; j++)
    {
        string _s(words[j]);
        if(_s=="P")
        {
            p_index = j;
            break;
        }
    }



    int index=0;
    for(int j=0; j<i; j++)
    {
        string s(words[j]);
        if(s==name2)
        {
            index = (j-1)/7+1;
        }
    }
    if(index==0)
    {
        cout<<"���ҵ����ݱ����ڣ�"<<endl;
    }

    //cout<<"index....."<<index<<endl;

    if(xing=="*")
    {

        int have=0;

        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;

        int colomn_num = 0;
        for( int j=1; j<i; j++ ) //�������������
        {
            string ss(words[j-1]);
            if((j==1)||(j>=7&&(j-1)%7==0&&ss=="Q"))
            {
                printf( " %-10s|", words[j] ) ;
                colomn_num++;
            }
        }

        cout<<endl;
        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;



        for(int j=p_index-1; j<i; j=j+index+1)
        {

            string ___s(words[j]);
            //cout<<"......"<<j<<"......."<<___s<<endl;
            stringstream ss_1,ss_2,ss_3;
            int cp_1,cp_2,cp_3;
            ss_1<<___s;
            ss_1>>cp_1;
            ss_2<<sf;
            ss_2>>cp_2;
            ss_3<<ss;
            ss_3>>cp_3;
            if(cp_1>=cp_2&&cp_1<=cp_3)
            {
                have = 1;
                for(int q=1; q<=pm; q++)
                {
                    printf(" %-10s|",words[j-index+q]);
                }
                cout<<endl;
            }
            j=j+pm-index;
        }

        if(have==0)
        {
            cout<<"���ݱ����ڣ�"<<endl;
        }

        for(int w=0; w<pm; w++)
        {
            cout<<"------------";
        }
        cout<<endl;



    }
    else
    {
        int zhaojun_index=0;
        int cha;
        int have2=0;
        for(int j=0; j<i; j++)
        {
            string zhaojun(words[j]);

            if(zhaojun==xing)
            {
                zhaojun_index = (j-1)/7+1;
                cout<<"------------"<<endl;
                //cout<<"| "<<table<<" |"<<endl;
                printf(" %-10s|\n",words[j]);
                cout<<"------------"<<endl;
                break;
            }
        }
        if(zhaojun_index==0)
        {
            cout<<"�������ҵ����ݱ����ڣ�"<<endl;
        }
        else
        {
            cha =zhaojun_index-index;
        }

        for(int j=p_index-1; j<i; j=j+index+1)
        {
            if(j==p_index-1) continue;
            string zhuge(words[j]);
            //cout<<"zhuge...."<<zhuge<<"jj......"<<j<<"......"<<sf<<"......."<<ss<<endl;

            stringstream ss_1,ss_2,ss_3;
            int cp_1,cp_2,cp_3;
            ss_1<<zhuge;
            ss_1>>cp_1;
            ss_2<<sf;
            ss_2>>cp_2;
            ss_3<<ss;
            ss_3>>cp_3;

            //cout<<"cp_1...."<<cp_1<<"cp_2...."<<cp_2<<"cp_3...."<<cp_3<<endl;

            if(cp_1>=cp_2&&cp_1<=cp_3)
            {
                have2 = 1;
                printf("% -10s|\n",words[j+cha]);
            }
            j=j+pm-index;
        }
        if(have2==0)
        {
            cout<<"�������ҵ����ݲ����ڣ�"<<endl;
        }
        cout<<"------------"<<endl;
    }


}

void select_tao(string Sno,string name,string Cgrade,string la,string polo,string nb,string nbc,char words[][21])
{//select * from Stu where Sno in(select Cno from Course where Cgrade=90);
    FILE *fp;
    const char *p = name.c_str();
    fp=fopen(p, "r");
    if ( fp==NULL )
    {
        printf("��ȡ��ʾʧ��\n");
    }
    int i;
    for(i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
    {
        if ( fscanf(fp, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
            break;
    }
    fclose(fp);
char word[100][21];

string in[20];
int in_num = 0;

    int Sno_index=0;
    int Sno_have = 0;
    for(int j=0; j<i; j++)
    {
        string _Sno(words[j]);
        if(_Sno==Sno)
        {
            Sno_have = 1;
            Sno_index = (j-1)/7+1;
            break;
        }
    }
//cout<<"Sno...have"<<Sno_have<<"  Sno_index...."<<Sno_index<<endl;

    int Cgrade_index=0;
    int Cgrade_have = 0;
    for(int j=0; j<i; j++)
    {
        string _Cgrade(words[j]);
        if(_Cgrade==Cgrade)
        {
            Cgrade_have = 1;
            Cgrade_index = (j-1)/7+1;
            break;
        }
    }
//cout<<"Cgrade...have"<<Cgrade_have<<"  Cgrade_index...."<<Cgrade_index<<endl;


    int p_index;
    int _num;
    for(int j=0;j<i;j++)
    {
        string ps(words[j]);
        if(ps=="P")
        {
           p_index = j;
           break;
        }
    }

    _num = p_index/7;
    p_index = p_index-1;

//cout<<"p_index...."<<p_index<<endl;

    if(Sno_have==0||Cgrade_have==0)
    {
        cout<<"��ѯ���Բ����ڣ�"<<endl;
    }
    else
    {
        int cha = Sno_index - Cgrade_index;

            if(la=="=")
            {
                in_num = 0;
                for(int j=p_index;j<i;j=j+Sno_index+1)
                {
                 //   cout<<"j....."<<j<<endl;
                    string ps_sno(words[j]);
                    if(ps_sno==polo)
                    {
                        string psps(words[j+cha]);
                      //  cout<<"psps....."<<psps<<endl;
                        in[in_num] = psps;
                        in_num ++;
                    }
                    j = j +_num - Cgrade_index;
                }
                in_select(in,nb,nbc,word);
            }
            if(la==">")
            {
                in_num = 0;
                for(int j=p_index;j<i;j=j+Sno_index+1)
                {
                  //  cout<<"j....."<<j<<endl;
                    string ps_sno(words[j]);
                    stringstream ss_1,ss_2;
            int cp_1,cp_2;
            ss_1<<ps_sno;
            ss_1>>cp_1;
            ss_2<<polo;
            ss_2>>cp_2;


                    if(cp_1>cp_2)
                    {
                        string psps(words[j+cha]);
                       // cout<<"psps....."<<psps<<endl;
                        in[in_num] = psps;
                        in_num ++;
                    }
                    j = j +_num - Sno_index;
                }
                in_select(in,nb,nbc,word);
            }
            if(la=="<")
            {
                in_num = 0;
for(int j=p_index;j<i;j=j+Sno_index+1)
                {
                  //  cout<<"j....."<<j<<endl;
                    string ps_sno(words[j]);
                    stringstream ss_1,ss_2;
            int cp_1,cp_2;
            ss_1<<ps_sno;
            ss_1>>cp_1;
            ss_2<<polo;
            ss_2>>cp_2;


                    if(cp_1<cp_2)
                    {
                        string psps(words[j+cha]);
                     //   cout<<"psps....."<<psps<<endl;
                        if(psps!="NO"&&psps!="NULL")
                        {
                            in[in_num] = psps;
                        in_num ++;}

                    }
                    j = j +_num - Sno_index;
                }
                in_select(in,nb,nbc,word);
            }

    }


}


int main()
{
    //system("color 00");
    int key = 0;
    int _use = 0;
    int A_or_V = 0;

    int insert_ok = 1;
    int delete_ok = 1;
    int update_ok = 1;
    int create_ok = 1;

    char words[500][21];
    while(key==0)
    {
        cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"-----------------------------------���ݿ����ϵͳ��DATABASE MANAGEMENT SYSTEM��------------------------------------------"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"                                   1.����Ա��¼(�鿴�Ͳ���Ȩ��)            2.�ο͵�¼���鿴Ȩ�ޣ�"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"                                   ��ѡ����뷽ʽ��Input:1(����Ա):/Input:2(�ο�))"<<endl;
        cout<<"                                   ";
        string nn;
        cin>>nn;
        if(nn=="2")
        {
           insert_ok = 0;
    delete_ok = 0;
    update_ok = 0;
     create_ok = 0;
            _use = 1;
            key = 1;
            cout<<"                                   Welcome!"<<endl;
            cout<<"                                   Visitor!"<<endl;
        }
        if(nn=="1")
        {
            cout<<"                  Enter manager_name:(Don't have manager_name?  Press H to apply one)"<<endl;
            string admin;
            cout<<"                  ";
            cin>>admin;

            if(admin=="H")
            {
                cout<<"                                   Enter the manager_name:"<<endl;
                cout<<"                                   ";
                string m_name;
                cin>>m_name;
                cout<<"                                   Enter the manager_password:"<<endl;
                cout<<"                                   ";
                string m_pwd;
                cin>>m_pwd;
                string m_pname = "super_name.txt";
                FILE * ffp;
                const char *ffpp = m_pname.c_str();
                ffp=fopen(ffpp, "r");
                if ( ffpp==NULL )
                {
                    printf("��ȡ��ʾʧ��\n");
                }
                int i;
                for( i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
                {
                    if ( fscanf(ffp, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
                        break;
                }
                fclose(ffp);
                int mmd = 0;
                for(mmd=0; mmd<i; mmd++)
                {
                    string meme(words[mmd]);
                    if(meme==m_name)
                    {
                        cout<<"                                   �û����Ѵ��ڣ�"<<endl;
                        break;
                    }
                }
                if(mmd==i)
                {
                    FILE * fp;
                    const char *pp = m_pname.c_str();
                    if((fp=fopen(pp,"a"))==NULL)
                    {
                        cout<<"APPLY ERROR��"<<endl;
                    }
                    else
                    {
                        const char *ff = m_name.c_str();
                        const char *gg = m_pwd.c_str();
                        fprintf(fp,"%s",ff);
                        fprintf(fp,"%c",' ');
                        fprintf(fp,"%s",gg);
                        fputc(10,fp);
                        cout<<"APPLY SUCCESS��"<<endl<<endl;
                    }
                    fclose(fp);
                    cout<<"Enter manager_name:"<<endl;
                    cin>>admin;
                    cout<<"Enter password:"<<endl;
                    string pwd;
                    cin>>pwd;
                    FILE * FP;
                    FP=fopen(pp, "r");
                    if ( FP==NULL )
                    {
                        printf("ERROR\n");
                    }
                    int i;
                    for(i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
                    {
                        if ( fscanf(FP, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
                            break;
                    }
                    fclose(FP);
                    int j;
                    int sec = 0;
                    for(j=0; j<i; j++)
                    {
                        string kkkk(words[j]);
                        if(kkkk==admin)
                        {
                            string v(words[j+1]);
                            if(v!=pwd)
                            {
                                cout<<"�������!"<<endl;
                                int in_key = 0;
                                cout<<"�Ƿ񷵻��ϼ�����1.�����ϼ�/2.������"<<endl;
                                cin>>in_key;
                                if(in_key==1)
                                {
                                    key = 0;
                                }
                                else
                                {
                                    return 0;
                                }
                            }
                            else
                            {
                                key=1;
                                _use = 1;
                                A_or_V = 1;
                                system("cls");
                                cout<<endl;
                                cout<<"                                   Welcome!         "<<endl;
                                cout<<"                                   Administrator!"<<endl;
                                cout<<endl;
                            }
                        }
                        else
                        {
                            j++;
                            if(j==i-1)
                            {
                                cout<<"�û��������ڣ�"<<endl<<endl;
                                int in_key = 0;
                                cout<<"�Ƿ񷵻��ϼ�����1.�����ϼ�/2.������"<<endl;
                                cin>>in_key;
                                if(in_key==1)
                                {
                                    key = 0;
                                }
                                else
                                {
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                cout<<"                  ";
                cout<<"Enter the manager_password:"<<endl;
                string pwd;
                cout<<"                  ";
                cin>>pwd;
                FILE * FP;
                string m_pname = "super_name.txt";
                const char *pp = m_pname.c_str();
                FP=fopen(pp, "r");

                if ( FP==NULL )
                {
                    printf("ERROR\n");
                }
                int i;
                for(i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
                {

                    if ( fscanf(FP, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
                        break;
                }
                fclose(FP);
                int j;
                for(j=0; j<i; j++)
                {
                    string kkkk(words[j]);
                    if(kkkk==admin)
                    {
                        string v(words[j+1]);
                        if(v!=pwd)
                        {
                            cout<<"������� !"<<endl<<endl;
                            int in_key = 0;
                            cout<<"�Ƿ񷵻��ϼ�����1.�����ϼ�/2.������"<<endl;
                            cin>>in_key;
                            if(in_key==1)
                            {
                                key = 0;
                            }
                            else
                            {
                                return 0;
                            }
                        }
                        else
                        {
                            key=1;
                            _use = 1;
                            A_or_V = 1;
                            system("cls");
                            cout<<endl;
                            cout<<"                                   Welcome!         "<<endl;
                            cout<<"                                   Administrator!"<<endl;
                            cout<<endl;
                        }
                    }
                    else
                    {
                        j++;
                        if(j==i-1)
                        {
                            cout<<"�û��������ڣ�"<<endl<<endl;
                            int in_key = 0;
                            cout<<"�Ƿ񷵻��ϼ�����1.�����ϼ�/2.������"<<endl;
                            cin>>in_key;
                            if(in_key==1)
                            {
                                key = 0;
                            }
                            else
                            {
                                return 0;
                            }
                        }
                    }
                }
            }
        }

        if(_use==1)
        {
            int n;
            string dn = "database\\";
            string cdn = "database\\";
            string nb = "database\\";
            string DB="";
            int sum=0;
            while(true)
            {
                cout<<"Super_sql> ";
                FILE *fp;
                string use;
                cin>>use;

                if(use=="add")
                {
                    FILE * fpg = fopen("database\\db\\db.txt", "r+");
                    if (fpg == NULL)
                    {
                        printf("file error\n");
                        exit(1);
                    }
                    fseek(fpg, 122, SEEK_SET);//����Ƶ��ļ���ʼ��ڶ����ֽڴ���
                    fprintf(fpg,"%c",' ');
                    fwrite("yun", 1, 3, fpg); //�ļ���д������yun
                    fclose(fpg);
                }
                if(use=="clear;")
                {
                    system("cls");
                }
                if(use=="use")
                {
                    string database,margin;
                    cin>>database;
                    int len = database.length()-1;
                    margin = database[len];
                    DB = database.substr(0,database.length()-1);
                    if(margin==";"&&use=="use")
                    {
                        cdn = "database\\";
                        cdn = cdn + DB + "\\";
                        cout<<"Database changed��"<<endl;
                    }
                    else
                    {
                        cout<<"INPUTE ERROR��"<<endl;
                    }
                }
                if(use=="create")
                {
                    string dN,create,database,margin;
                    cin>>database;
                    if(database=="database")
                    {
                        cin>>dN;
                        int len = dN.length()-1;
                        margin = dN[len];
                        dN = dN.substr(0,dN.length()-1);
                        if(create_ok == 1)
                        {
                            if(margin==";")
                            {
                                dN = dn + dN;
                                create_databases(dN);
                            }
                            else
                            {
                                cout<<"create����������!"<<endl;
                            }
                        }
                        else
                        {
                            cout<<"�Բ�����û��CreateȨ�ޣ�"<<endl;
                        }
                    }
                    else
                    {
                        if(database=="index")
                        {
                            string index_name,on,table_column;
                            //create index aa on db_1(Sno);

                            cin>>index_name>>on>>table_column;

                            string a="";
                            for(int i=0; i<table_column.length()-1; i++)
                            {
                                if(table_column[i]!='(')
                                {
                                    a+=table_column[i];
                                }
                                else
                                {
                                    break;
                                }
                            }
                            insert_index_name(index_name,a);
                            string ne = a;
                            a = cdn+a+".txt";
                            create_index(a,words,index_name);
                            cout<<"create index success!"<<endl;
                        }
                        else
                        {
                            if(database=="table")
                            {
                                string table_name="";
                                string str = "";
                                int num = 0;
                                int sum=0;
                                int next = 0;
                                while(true)
                                {
                                    cin>>dN;
                                    //ȡ���һ���ַ�
                                    int len = dN.length()-1;
                                    margin = dN[len];
                                    //����;�ţ����һ��
                                    if(margin==";")
                                    {
                                        int pie = 0;
                                        int na = 0;
                                        for(int gg=0; gg<dN.length(); gg++)
                                        {
                                            char com = dN[gg];
                                            if(com!=')')
                                            {
                                                pie++;
                                            }
                                            else
                                            {
                                                break;
                                            }
                                        }
                                        str = dN.substr(0,pie);
                                        num++;
                                        next = 0;
                                        if(A_or_V ==1)
                                        {
                                            create_table_step(0,num,table_name,str);
                                            create_table_step(1,num,table_name,str);
                                        }
                                        char cn = ' ';
                                        int j;
                                        for(j=0; j<dN.length(); j++)
                                        {
                                            cn = dN[j];
                                            if(cn!='(')
                                            {
                                                na++;
                                            }
                                            else
                                            {
                                                break;
                                            }
                                        }
                                        int bingo = 0;
                                        int cctv = 0;
                                        int mumu=0;
                                        for(int i=0; i<dN.length(); i++)
                                        {
                                            cn = dN[i];
                                            if(cn==';')
                                            {
                                                str=dN.substr(na+mumu+1,i-na-2-mumu);
                                                if(A_or_V ==1)
                                                {
                                                    insert_value(table_name,words,str,0);
                                                }
                                            }
                                            if(cn!=',')
                                            {
                                                bingo++;
                                            }
                                            else
                                            {
                                                cctv++;
                                                if(cctv==1)
                                                {
                                                    str = dN.substr(na+1,bingo-na-1);
                                                    na = bingo;
                                                    if(A_or_V ==1)
                                                    {
                                                        insert_value(table_name,words,str,1);
                                                    }
                                                }
                                                else
                                                {
                                                    mumu++;
                                                    str = dN.substr(na+mumu,bingo-na);
                                                    na = bingo;
                                                    if(A_or_V ==1)
                                                    {
                                                        insert_value(table_name,words,str,0);
                                                    }
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else//�����Ƿֺ�
                                    {
                                        sum++;
                                        if(num==0&&sum==1)
                                        {
                                            num++;
                                            int pie = 0;
                                            for(int gg=0; gg<dN.length(); gg++)
                                            {
                                                char com = dN[gg];
                                                if(com!='(')
                                                {
                                                    pie++;
                                                }
                                                else
                                                {
                                                    break;
                                                }
                                            }
                                            //������
                                            table_name = dN;
                                            if(A_or_V ==1)
                                            {
                                                table_name = table_name.substr(0,pie);
                                                table_name = cdn+table_name+".txt";
                                                create_table(fp,table_name);
                                                str = dN.substr(pie+1,dN.length()-pie);
                                                create_table_step(next,num,table_name,str);
                                            }
                                        }
                                        else
                                        {
                                            int pie = 0;
                                            for(int gg=0; gg<dN.length(); gg++)
                                            {
                                                char com = dN[gg];
                                                if(com!=',')
                                                {
                                                    pie++;
                                                }
                                                else
                                                {
                                                    break;
                                                }
                                            }
                                            if(pie==dN.length())
                                            {
                                                next = 0;
                                                num++;
                                                if(A_or_V ==1)
                                                {
                                                    create_table_step(next,num,table_name,dN);
                                                }
                                            }
                                            else
                                            {
                                                if(A_or_V ==1)
                                                {
                                                    next = 0;
                                                    str = dN.substr(0,pie);
                                                    num++;
                                                    create_table_step(next,num,table_name,str);
                                                    next = 1;
                                                    create_table_step(next,num,table_name,str);
                                                    next = 0;
                                                    num=1;
                                                    str = dN.substr(pie+1,dN.length()-pie);
                                                    create_table_step(next,num,table_name,str);
                                                }
                                            }
                                        }
                                    }
                                }
                                if(create_ok ==0)
                                {
                                    cout<<"�Բ�����û��CreateȨ�ޣ�"<<endl;
                                }
                            }
                            else
                            {
                                int y;
                                int yy = 0;
                                if(database=="view")
                                {
                                    string name;
                                    cin>>name;
                                    int len = name.length()-1;
                                    margin = name[len];
                                    string kkk = name;
                                    int jj = name.length();
                                    if(create_ok == 1)
                                    {
                                        for(y = 0; y<name.length(); y++)
                                        {
                                            string nex;
                                            nex = name[y];
                                            if(nex!="(")
                                            {
                                                yy++;
                                            }
                                            else
                                            {
                                                break;
                                            }
                                        }
                                        name = name.substr(0,yy);
                                        name = "views\\"+name+".txt";
                                        create_view(fp,name);
                                        insert_view(fp,name,use);
                                        insert_view(fp,name,database);
                                        insert_view(fp,name,kkk);
                                        while(margin!=";")
                                        {
                                            cin>>kkk;
                                            int len = kkk.length()-1;
                                            margin = kkk[len];
                                            insert_view(fp,name,kkk);
                                        }
                                    }
                                    else
                                    {
                                        cout<<"�Բ�����û��CreateȨ�ޣ�"<<endl;
                                    }
                                }
                                else
                                {
                                    cout<<"create����������!"<<endl;
                                }
                            }
                        }
                    }
                }
                if(use=="drop")
                {
                    string dN,drop,database,margin;
                    cin>>database>>dN;
                    int len = dN.length()-1;
                    margin = dN[len];
                    dN = dN.substr(0,dN.length()-1);
                    if(A_or_V == 1)
                    {
                        if(database=="database"&&margin==";")
                        {
                            dN = dn + dN;
                            drop_database(dN);
                        }
                        else
                        {
                            if(database=="table"&&margin==";")
                            {
                                dN = cdn+dN+".txt";
                                delete_table(dN);
                            }
                            if(database=="view"&&margin==";")
                            {
                                string lk="views\\"+dN+".txt";
                                delete_view(lk);
                            }

                        }
                    }
                    else
                    {
                        cout<<"�Բ�����û��DropȨ�ޣ�"<<endl;
                    }
                }
                if(use=="show")
                {
                    string databases;
                    cin>>databases;
                    if(databases=="index")
                    {
                        string name;
                        cin>>name;
                        int len3 = name.length()-1;
                        //string margin = name[len3];
                        name = name.substr(0,len3);
                        cout<<endl;
                        cout<<"INDEX_NAME: "<<name<<endl;
                        printkey(2,name);
                        printkey(1,name);
                    }
                    else
                    {
                        if(databases=="databases;")
                        {
                            show_databases();
                        }
                        else
                        {
                            if(databases=="tables;")
                            {
                                string path = cdn ;
                                show_tables(path);
                            }
                            else
                            {
                                cout<<"show����������"<<endl;
                            }
                        }
                    }
                }
                if(use=="help")
                {
                    string table,name,margin;
                    cin>>table;
                    int len3 = table.length()-1;
                    margin = table[len3];
                    string ddb = table.substr(0,table.length()-1);
//                    if(table=="indexs;")
//                    {
//                        string index_n="index_name.txt";
//                        read_index(index_n,words);
//                    }
                    if(margin==";"&&table!="index;")
                    {

                        string to = nb + ddb + "\\";
                        show_tables(to);
                        string to2 = "views\\";
                        show_views(to,to2,words);

                        string index_n="index_name.txt";
                        read_index(index_n,words);
                    }
                    else
                    {
                        cin>>name;
                        string kkk;
                        kkk = name;
                        int len = name.length()-1;
                        margin = name[len];
                        name = name.substr(0,name.length()-1);
                        if(margin==";"&&table=="table")
                        {
                            name = cdn + name + ".txt";
                            read_txt(name,words,sum);


                        }
                        else
                        {
                            if(table=="view"&&margin==";")
                            {
                                name = "views\\"+ name + ".txt";
                                read_view(name,words);
                            }
                            else
                            {


                                cout<<"ERROR��"<<endl;

                            }
                        }
                    }
                }
                if(use=="select")
                {

                    string xing,from,name,margin;
                    cin>>xing>>from>>name;
                    string namename;

                    string link_name = name;
                    link_name = cdn + link_name + ".txt";

                    int len = name.length()-1;
                    margin = name[len];
                    namename = name.substr(0,name.length()-1);
                    namename = cdn + namename + ".txt";
                    if(xing=="*"&&from=="from"&&margin==";")
                    {
                        show_values(namename,words);
                    }
                    else
                    {
                        if(xing!="*"&&from=="from"&&margin==";")
                        {
                            select_column(xing,namename,words);
                        }
                        else
                        {
                            string where,name2;
                            cin>>where>>name2;

                            string link_where = where;
                            string link_first = name2;

                            len = name2.length()-1;
                            margin = name2[len];


                            if(from=="from"&&margin==";")
                            {
                                int column_name=0;
                                for(int i=0; i<name2.length(); i++)
                                {
                                    if(name2[i]!='=')
                                    {
                                        column_name++;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                                string select_name,value;
                                select_name = name2.substr(0,column_name);
                                value = name2.substr(column_name+1,len-column_name-1);
                                name = cdn + name + ".txt";
                                select_column2(xing,name,select_name,value,words);
                            }



                            if(link_where=="where"&&margin!=";")
                            {
                                string link_and;
                                cin>>link_and;
                                string in_l = link_and;
                                if(link_and=="between")
                                {
                                    string sf,ss,sand,ss_fog;
                                    cin>>sf>>sand>>ss_fog;

                                    for(int i=0; i<ss_fog.length()-1; i++)
                                    {
                                        ss+=ss_fog[i];
                                    }
                                    between_select(xing,link_name,name2,sf,ss,words);
                                }
                                if(link_and=="and")
                                {
                                    string link_second;
                                    cin>>link_second;

                                    string margin3="";
                                    int len3 = link_second.length()-1;
                                    margin3 = link_second[len3];

                                    if(margin3==";")
                                    {
                                        int link_end=0;
                                        string select_first;
                                        string select_second;
                                        string link_cmf;
                                        string link_cms;
                                        int link_len = link_first.length();

                                        for(int l=0; l<link_len; l++)
                                        {
                                            if(link_end==1)
                                            {
                                                select_first+=link_first[l];
                                            }
                                            if(link_first[l]=='=')
                                            {
                                                link_end = 1;
                                            }
                                            if(link_end==0)
                                            {
                                                link_cmf+=link_first[l];
                                            }

                                        }

                                        link_end = 0;

                                        link_len = link_second.length();
                                        for(int l=0; l<link_len; l++)
                                        {
                                            if(l==link_len-1)
                                            {
                                                continue;
                                            }

                                            if(link_end==1)
                                            {
                                                select_second+=link_second[l];
                                            }
                                            if(link_second[l]=='=')
                                            {
                                                link_end = 1;
                                            }

                                            if(link_end==0)
                                            {
                                                link_cms+=link_second[l];
                                            }
                                        }

                                        select_and(xing,link_name,link_cmf,link_cms,select_first,select_second,words);

                                    }
                                    else
                                    {
                                        cout<<"And Wrong!"<<endl;
                                    }

                                }
                                if(link_and=="or")
                                {
                                    string link_second;
                                    cin>>link_second;

                                    string margin3="";
                                    int len3 = link_second.length()-1;
                                    margin3 = link_second[len3];

                                    if(margin3==";")
                                    {
                                        int link_end2=0;
                                        string select_first;
                                        string select_second;
                                        string link_cmf;
                                        string link_cms;
                                        int link_len = link_first.length();

                                        for(int l=0; l<link_len; l++)
                                        {
                                            if(link_end2==1)
                                            {
                                                select_first+=link_first[l];
                                            }
                                            if(link_first[l]=='=')
                                            {
                                                link_end2 = 1;
                                            }
                                            if(link_end2==0)
                                            {
                                                link_cmf+=link_first[l];
                                            }

                                        }

                                        link_end2 = 0;

                                        link_len = link_second.length();
                                        for(int l=0; l<link_len; l++)
                                        {
                                            if(l==link_len-1)
                                            {
                                                continue;
                                            }

                                            if(link_end2==1)
                                            {
                                                select_second+=link_second[l];
                                            }
                                            if(link_second[l]=='=')
                                            {
                                                link_end2 = 1;
                                            }

                                            if(link_end2==0)
                                            {
                                                link_cms+=link_second[l];
                                            }
                                        }

                                        select_or(xing,link_name,link_cmf,link_cms,select_first,select_second,words);
                                    }
                                    else
                                    {
                                        cout<<"Or Wrong!"<<endl;
                                    }
                                }
                                else //select * from table where name in(aa,bb,cc);
                                {
                                    string margin2="";
                                    int len2 = link_and.length()-1;
                                    margin2 = link_and[len2];
                                    if(margin2==";")
                                    {
                                        // cout<<"asdasd"<<endl;
                                        string in[20];
                                        int in_len = link_and.length();
                                        int begin_in=0;
                                        int nexx=0;
                                        for(int i=0; i<in_len; i++)
                                        {
                                            if(link_and[i]==')')
                                            {
                                                break;
                                            }
                                            if(link_and[i]==',')
                                            {
                                                nexx++;
                                                continue;
                                            }
                                            if(begin_in==1)
                                            {
                                                in[nexx]+=link_and[i];
                                            }
                                            if(link_and[i]=='(')
                                            {
                                                begin_in=1;
                                            }
                                        }
                                        in_select(in,link_name,name2,words);

                                    }
                                    else    //select * from Stu where Sno in(select Cno from Course where Cgrade=90);
                                    {
                                        //select * from Stu where Sno in(select Sno from Course where Cgrade>80);
                                        string m_sno,m_from,m_course,m_where,m_last;
                                        string m_type;
                                        int m_num=0;
                                        string m_la="",m_mid="",m_polo="";
                                        int m_polo_have = 0;

                                        while(1)
                                        {
                                            cin>>m_type;
                                            m_num++;

                                            int m_len=m_type.length()-1;
                                            string m_mar;
                                            m_mar = m_type[m_len];
                                            if(m_mar==";")
                                            {
                                                if(m_num!=5)
                                                {
                                                    cout<<"��ѯ��䴦����"<<endl;
                                                    break;
                                                }
                                                else
                                                {
                                                    for(int mm_i=0; mm_i<=m_len; mm_i++)
                                                    {
                                                     //   cout<<"mm_i....."<<mm_i<<endl;
                                                        if(m_type[mm_i]!='='&&m_type[mm_i]!='>'&&m_type[mm_i]!='<')
                                                        {
                                                            if(m_polo_have==0){
                                                            m_la+=m_type[mm_i];
                                                            //cout<<"m_la...."<<m_la<<endl;
                                                            }
                                                            if(m_polo_have==1)
                                                            {
                                                                if(m_type[mm_i]==')')
                                                                {
                                                                    break;
                                                                }
                                                                else
                                                                {
                                                                    m_polo+=m_type[mm_i];
                                                                }

                                                            }
                                                        }
                                                        else
                                                        {
                                                            if(m_polo_have==0)
                                                            {
                                                                m_mid+=m_type[mm_i];
                                                                m_polo_have = 1;
                                                              //  cout<<"m_mid...."<<m_mid<<endl;
                                                            }



                                                        }
                                                    }
                                                  //  cout<<"Stu.."<<name<<"   Sno..   "<<name2<<"   Sno.."<<m_sno<<"  Course..."<<m_course<<"   Cgrade.."<<m_la<<"   =><.."<<m_mid<<endl;
                                                  //  cout<<"m_polo.."<<m_polo<<endl;
                                                    m_course = cdn + m_course + ".txt";
                                                    string xu_name = cdn+name+".txt";
                                                    select_tao(m_sno,m_course,m_la,m_mid,m_polo,xu_name,name2,words);

                                                    break;
                                                }
                                            }
                                            else
                                            {

                                                if(m_num==1)
                                                {
                                                    m_sno=m_type;
                                                }
                                                if(m_num==3)
                                                {
                                                    m_course=m_type;
                                                }








                                            }







                                        }

                                    }

                                }
                            }




                        }
                    }
                }
                if(use=="insert")
                {
                    string into,table,values,margin;
                    cin>>into;
                    if(into=="into")
                    {
                        cin>>table>>values;
                        int cash=0;
                        int enen  =0;
                        table =  cdn + table +".txt";
                        int len = values.length();
                        int num_add = 0;
                        int begin_add = 0;
                        int is_first = 0;
                        string insert_string="";
                        if(insert_ok==1)
                        {
                            for(int i=0; i<len; i++)
                            {
                                if(values[i]==')')
                                {
                                    insert_table(3,table,insert_string);
                                    insert_string="";
                                    break;
                                }
                                if(values[i]=='(')
                                {
                                    begin_add = 1;
                                }
                                else
                                {
                                    //  if(cash==1){
                                    if(values[i]==',')
                                    {
                                        is_first++;
                                        if(is_first==1)
                                        {


                                            insert_table(1,table,insert_string);
                                            insert_string="";

                                        }
                                        else
                                        {
                                            insert_table(2,table,insert_string);
                                            insert_string="";
                                        }
                                        enen++;
                                        if(enen==1)
                                        {
                                            cout<<"Insert success!"<<endl;
                                        }
                                    }
                                    // }
                                    if(begin_add==1&&values[i]!=',')
                                    {
                                        insert_string+=values[i];
                                    }
                                    //  cout<<"insert_string...."<<insert_string<<endl;
                                    if(insert_string=="null")
                                    {
                                        cout<<"The primary_key can't be null!"<<endl;
                                        // cash = -1;
                                        //  enen =1;
                                        break;
                                    }
                                    num_add++;
                                }
                            }

                        }
                        else
                        {
                            cout<<"�Բ�����û��InsertȨ�ޣ�"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"insert����������!"<<endl;
                    }
                }
                if(use=="grante")
                {
                    //grante select on table ...;
                    int ltb;
                    string type;
                    string mar;
                    string mmm;
                    int nhk=0;

                    while(1)
                    {
                        cin>>type;
                        nhk++;
                        if(nhk==1)
                        {
                            mmm = type;
                        }
                        ltb = type.length()-1;
                        mar = type[ltb];
                        if(mar==";")
                        {
                            if(nhk!=4)
                            {
                                cout<<"��Ȩ������"<<endl;
                                break;
                            }
                            else
                            {

                                if(mmm=="create")
                                {
                                    cout<<endl;
                                    cout<<"����createȨ�ޣ�"<<endl;
                                    create_ok = 1;
                                }
                                if(mmm=="delete")
                                {
                                    cout<<endl;
                                    cout<<"����deleteȨ�ޣ�"<<endl;
                                    delete_ok = 1;
                                }
                                if(mmm=="update")
                                {
                                    cout<<endl;
                                    cout<<"����updateȨ�ޣ�"<<endl;
                                    update_ok = 1;
                                }
                                if(mmm=="insert")
                                {
                                    cout<<endl;
                                    cout<<"����insertȨ�ޣ�"<<endl;
                                    insert_ok = 1;
                                }
                                break;
                            }
                        }
                    }



                    cout<<endl;
                }
                if(use=="revoke")
                {
                    int ltb;
                    string type;
                    string mar;
                    int nhk=0;
                    string mmm;

                    while(1)
                    {
                        cin>>type;

                        nhk++;
                        if(nhk==1)
                        {
                            mmm = type;
                        }
                        ltb = type.length()-1;

                        mar = type[ltb];

                        //cout<<"mar..."<<mar<<"type..."<<type<<endl;
                        if(mar==";")
                        {
                            if(nhk!=4)
                            {
                                cout<<"��Ȩ������"<<endl;
                                break;
                            }
                            else
                            {
                                if(mmm=="create")
                                {
                                    cout<<endl;
                                    cout<<"�ջ�createȨ�ޣ�"<<endl;
                                    create_ok = 0;
                                }
                                if(mmm=="delete")
                                {
                                    cout<<endl;
                                    cout<<"�ջ�deleteȨ�ޣ�"<<endl;
                                    delete_ok = 0;
                                }
                                if(mmm=="update")
                                {
                                    cout<<endl;
                                    cout<<"�ջ�updateȨ�ޣ�"<<endl;
                                    update_ok = 0;
                                }
                                if(mmm=="insert")
                                {
                                    cout<<endl;
                                    cout<<"�ջ�insertȨ�ޣ�"<<endl;
                                    insert_ok = 0;
                                }
                                break;
                            }
                        }
                    }



                    cout<<endl;

                }
                if(use=="delete")
                {
                    string from,name,where,la,margin;
                    cin>>from>>name>>where>>la;
                    if(delete_ok == 1)
                    {
                        string tra = name;
                        int len = la.length()-1;
                        margin = la[len];
                        if(from=="from"&&where=="where"&&margin==";")
                        {
                            name = cdn+name+".txt";
                            delete_table_value(la,name,words,cdn,tra);
                        }
                        else
                        {
                            cout<<"delete����������!"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"�Բ�����û��DeleteȨ�ޣ�"<<endl;
                    }
                }
                if(use=="update")
                {
                    //update db_1 set name=xiaoming where age=20;
                    string table,sett,column_name,where,last,margin;
                    cin>>table>>sett>>column_name>>where>>last;

                    int len = last.length()-1;
                    margin = last[len];
                    int ulen=0,wlen=0,test_wlen=0;
                    string value;
                    if(update_ok == 1)
                    {
                        if(sett=="set"&&where=="where"&&margin==";")
                        {
                            for(int i=0; i<column_name.length(); i++)
                            {
                                if(column_name[i]!='=')
                                {
                                    ulen++;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for(int i=0; i<column_name.length(); i++)
                            {
                                if(test_wlen==1)
                                {
                                    wlen++;
                                }
                                if(column_name[i]=='\'')
                                {
                                    wlen++;
                                    test_wlen = 1;
                                }
                            }
                            wlen = wlen-2;
                            value = column_name.substr(ulen+1,wlen);
                            column_name = column_name.substr(0,ulen);
                            string column_name2,value2;
                            wlen = last.length();
                            ulen = 0;
                            for(int i=0; i<last.length(); i++)
                            {
                                if(last[i]!='=')
                                {
                                    ulen++;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            wlen=wlen-ulen-2;
                            column_name2 = last.substr(0,ulen);
                            value2 = last.substr(ulen+1,wlen);
                            update(table,column_name,value,column_name2,value2,words,cdn);
                        }
                        else
                        {
                            cout<<"����������!"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"�Բ�����û��UpdateȨ�ޣ�"<<endl;
                    }
                }
            }
        }
    }

}



