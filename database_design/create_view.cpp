void create_view(FILE *fp,string tn)
{
    const char *p = tn.c_str();
    fp= fopen(p,"w");
    fclose(fp);


    cout<<"Query OK, 0 rows affected!;"<<endl;
}

void insert_view(FILE *fp,string tn,string kkk)
{
    const char *p = tn.c_str();
    char o = ' ';
    FILE * FP;
    if((FP=fopen(p,"a"))==NULL)
    {
        cout<<"数据表打开失败！"<<endl;
    }
    else
    {
        // cout<<"数据表打开成功！"<<endl;
        const char *ff = kkk.c_str();
        fprintf(FP,"%s",ff);
        fprintf(FP,"%c",o);
    }
    fclose(FP);
   // cout<<"Query OK, 0 rows affected！"<<endl;
}
