void create_databases(string dN)//创建数据库
{
    bool flag = CreateDirectory(dN.c_str(), NULL);
    if(flag)
    {
        cout<<"Query OK, 1 row affected!"<<endl;
    }
}
