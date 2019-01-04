void delete_table(string dN)//É¾³ýÊý¾Ý±í
{
    const char *p = dN.c_str();
    if(remove(p))
        printf("ERROR£¡");
    else printf("Query OK, 0 rows affected£¡ \n");
}
