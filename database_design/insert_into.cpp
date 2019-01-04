void insert_table(int is_first,string name,string insert_value)
{
    FILE *FP;
    const char *p = name.c_str();
    if((FP=fopen(p,"a"))==NULL)
    {
        cout<<"数据表打开失败！"<<endl;
    }
    else
    {
        const char *ff = insert_value.c_str();
        //fprintf(FP,"%s",ff);
       // cout<<"数据表打开成功！"<<endl;
        if(is_first==1)
        {
            fputc(10,FP);
            fprintf(FP,"%c",'P');
            fprintf(FP,"%c",' ');

            fprintf(FP,"%s",ff);  //fprintf(FP,"%c",'1');
            //   cout<<"num1"<<endl;
        }
        if(is_first==2)
        {
            fprintf(FP,"%c",' ');
            fprintf(FP,"%s",ff);  //fprintf(FP,"%c",'2');
            //   cout<<"num2"<<endl;
        }
        if(is_first==3)
        {
            fprintf(FP,"%c",' ');
            fprintf(FP,"%s",ff);  //fprintf(FP,"%c",'3');
            //  cout<<"num3"<<endl;
        }
    }
    fclose(FP);
}
