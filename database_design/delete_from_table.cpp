void delete_table_value(string la,string name,char words[][21],string cdn,string tn)
{
    string table_name="";
    int begin_add = 0;
    string value="";
    //int value_add = 0;
    for(int i=0; i<la.length(); i++)
    {
        if(la[i]==';')
        {
            break;
        }
        if(begin_add==1)
        {
            value+=la[i];
        }
        if(la[i]!='=')
        {
            if(begin_add==0)
            {
                table_name+=la[i];
            }
        }
        else
        {
            begin_add = 1;
        }
    }



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

    int P;
    int column_num;
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
   // cout<<"P....."<<P<<endl;


    int table_index;
    for(int j=0; j<i; j++)
    {
        string ss(words[j]);
        if(ss==table_name)
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
  //  cout<<"table_index....."<<table_index<<endl;
  //  cout<<"column_num....."<<column_num<<endl;
   // cout<<value<<" and "<<table_name<<endl;








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
            const char *ff = insert_value.c_str();
            if((j==P+table_index)||((j>P+table_index)&&(j-P-table_index)%(column_num+1)==0))
            {
               // cout<<"j------"<<j<<endl;
                string ss(words[j]);
                if(ss==value)
                {
                    now = j;
                   // cout<<"now...."<<now<<endl;
                }
                if(((j-column_num*7+1)%(column_num+1)==0)&&(j>=column_num*7)&&(now==0))
                {
                    //  cout<<"emmmmmmmmmmmmmmmmmmmmmmmmmm"<<endl;
                    for(int k=j-column_num; k<=j; k++)
                    {
                     //   cout<<"kkkkk......"<<k<<endl;
                        string wow(words[k]);
                        const char *woo = wow.c_str();
                        if(wow=="P")
                        {
                            fputc(10,FP);
                            fprintf(FP,"%s",woo);
                        }
                        else
                        {
                            fprintf(FP,"%c",' ');
                            fprintf(FP,"%s",woo);
                        }
                    }
                }

            }
            else
            {
                if(now!=0)
                {
                    j=now-table_index+column_num+1;
                    //cout<<"JJ....."<<endl;
                    now=0;
                }
                if(j<column_num*7)
                {
                    if(j==0)
                    {
                        fprintf(FP,"%s",ff);
                    }
                    else
                    {
                        if(insert_value=="Q"||insert_value=="P")
                        {
                            fputc(10,FP);
                            fprintf(FP,"%s",ff);
                        }
                        else
                        {
                            fprintf(FP,"%c",' ');
                            fprintf(FP,"%s",ff);
                        }
                    }
                }
                if(((j-column_num*7+1)%(column_num+1)==0)&&(j>=column_num*7)&&(now==0))
                {
                    // cout<<"emmmmmmmmmmmmmmmmmmmmmmmmmm"<<endl;
                    for(int k=j-column_num; k<=j; k++)
                    {
                       // cout<<"kkkkk......"<<k<<endl;
                        string wow(words[k]);
                        const char *woo = wow.c_str();
                        if(wow=="P")
                        {
                            fputc(10,FP);
                            fprintf(FP,"%s",woo);
                        }
                        else
                        {
                            fprintf(FP,"%c",' ');
                            fprintf(FP,"%s",woo);
                        }
                    }
                }
            }
        }
    }
    fclose(FP);


    const char *de = name.c_str();
    if(remove(de))
        printf("ERROR！");
    else printf("Query OK, 0 rows affected！ \n");


    int result;
    //const char *oldname = .c_str();
    string nn = cdn+tn+".txt";
    const char *newname=nn.c_str();
    result= rename( p_p , newname );
//    if ( result == 0 )
//        puts ( "File successfully renamed" );
//    else
//        perror( "Error renaming file" );


















}
