void update(string table,string column,string value,string column2,string value2,char words[][21],string cdn)
{
    //update db_1 set name=xiaoming where age=20;

//    cout<<"table........"<<table<<"......"<<endl;
//    cout<<"value........"<<value<<"......"<<endl;
//    cout<<"column........"<<column<<"......"<<endl;
//    cout<<"column2........"<<column2<<"......"<<endl;
//    cout<<"value2........"<<value2<<"......"<<endl;
//    cout<<"cdn........"<<cdn<<"......"<<endl;


    string name=  cdn + table +".txt";
    FILE *fp;
    const char *p = name.c_str();
    fp=fopen(p, "r");
    if ( fp==NULL )
    {
        printf("读取显示失败\n");
    }
    int i;
    for(i=0; i<200; i++ ) //循环读取，控制不超过100个
    {
        if ( fscanf(fp, "%20s", words[i] )!= 1 ) //控制每个单词不超过20个
            break;
    }
    fclose(fp);

    int P=0;
    int column_num=0;
    for(int j=0; j<i; j++)
    {
        string ss(words[j]);
        if(ss=="P")
        {
            P = j;
            column_num = P/7;
            break;
        }
    }

 //  cout<<"P......."<<P<<"....."<<endl;
 // cout<<"column_num....."<<column_num<<"......"<<endl;

    int table_index=0;
    for(int j=0; j<i; j++)
    {
        string ss(words[j]);
        if(ss==column)
        {
            if(j<7)
            {
                table_index = j;
            }
            else
            {
                table_index = (j-1)/7+1;
            }
            break;
        }
    }

//cout<<"table_index..........."<<table_index<<"........"<<endl;

    int table_index2=0;
    for(int j=0; j<i; j++)
    {
        string ss(words[j]);
        if(ss==column2)
        {
            if(j<7)
            {
                table_index2 = j;
            }
            else
            {
                table_index2= (j-1)/7+1;
            }
            break;
        }
    }

//cout<<"table_index2..........."<<table_index2<<"........"<<endl;
    for(int j=P; j<i; j++)
    {
       // cout<<"aaaaaaaaaaaaaaaaaaaaaaaa"<<endl;
        string ss(words[j]);
        if(ss==value2)
        {
            strcpy(words[j+table_index-table_index2],value.c_str());
          //  printf("%s.........",words[j+table_index-table_index2]);
        }

    }



    FILE *FP;
    string instant_name="instant_table";
    instant_name = cdn+instant_name+".txt";
    const char *p_p = instant_name.c_str();
    int now=0;
    int add_test=0;
    if((FP=fopen(p_p,"a"))==NULL)
    {
        cout<<"数据表打开失败！"<<endl;
    }
    else
    {
        for(int j=0; j<i; j++)
        {
            string insert_value(words[j]);
            const char *woo = insert_value.c_str();
            if(j<column_num*7)
            {
                if((j==0)||(j%7==0))
                {
                    if(j==0)
                    {
                        fprintf(FP,"%s",woo);
                    }
                    if(j%7==0&&j!=0)
                    {
                        fputc(10,FP);
                        fprintf(FP,"%s",woo);
                    }
                }
                else
                {
                    fprintf(FP,"%c",' ');
                    fprintf(FP,"%s",woo);
                }
            }
            else
            {
                if(((j-P)==0)||((j-P)%(column_num+1)==0))
                {
                    fputc(10,FP);
                    //fprintf(FP,"%c",' ');
                    fprintf(FP,"%s",woo);
                }
                else
                {
                    fprintf(FP,"%c",' ');
                    fprintf(FP,"%s",woo);
                }
            }
        }

        fclose(FP);

        const char *de = name.c_str();
        if(remove(de))
            printf("更新语句错误！");
        else printf("Query OK, 0 rows affected！ \n");


        int result;
        //const char *oldname = .c_str();
        string nn = cdn+table+".txt";
        const char *newname=nn.c_str();
        // const char *newname=nn.c_str();
        result= rename(p_p , newname );

    }
}
