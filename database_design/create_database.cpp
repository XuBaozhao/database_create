void create_databases(string dN)//�������ݿ�
{
    bool flag = CreateDirectory(dN.c_str(), NULL);
    if(flag)
    {
        cout<<"Query OK, 1 row affected!"<<endl;
    }
}
