void delete_view(string dN)//ɾ�����ݱ�
{
    const char *p = dN.c_str();
    if(remove(p))
        printf("ERROR��");
    else printf("Query OK, 0 rows affected�� \n");
}
