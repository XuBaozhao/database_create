void show_values(string name,char words[][21])
{
    // cout<<"------------------------------------------"<<endl;
    FILE *fp ;
    int i,j,k,h;
    const char *p = name.c_str();
    fp=fopen(p, "r");

    if ( fp==NULL )
    {
        printf("读取显示失败\n");
    }
    for( i=0; i<200; i++ ) //循环读取，控制不超过100个
    {
        if ( fscanf(fp, "%20s", words[i] )!= 1 ) //控制每个单词不超过20个
            break;
    }
    fclose(fp);

    int pm=0;
    for(int j=0;j<i;j++)
    {
        string __s(words[j]);
        if(__s!="P")
        {
           pm++;
        }
        else{
            break;
        }
    }
    pm = pm/7;
    for(int w=0;w<pm;w++)
    {
        cout<<"------------";
    }
    cout<<endl;

    int colomn_num = 0;
    for( j=1; j<i; j++ ) //反向输出各单词
    {
        string ss(words[j-1]);
        if((j==1)||(j>=7&&(j-1)%7==0&&ss=="Q"))
        {
            printf( " %-10s|", words[j] ) ;
            colomn_num++;
        }
    }

    cout<<endl;
      for(int w=0;w<pm;w++)
    {
        cout<<"------------";
    }
    cout<<endl;
 //cout<<"------------------------------------------"<<endl;
    for(h=0; h<200; h++)
    {
        string ss1(words[h]);
        if(ss1!="P")
        {
            continue;
        }
        else
        {
            break;
        }
    }
    int u = h/7;
    int op = 0;
    int pp=0;

    int bili = 0;

    for(k=h; k<i; k++)
    {
        pp++;
        string sss(words[k]);
        if(sss=="P")
        {
            continue;
        }

        if((pp==1&&sss!="P")||(pp>=u&&(pp-1)%(u+1)==0&&sss!="P"))
            break;

        printf( " %-10s|", words[k] ) ;
        bili++;

        if(bili==colomn_num)
        {
            cout<<endl;
            bili=0;
        }
//        op++;
//        if(op==u)
//        {
//            op=0;
//            cout<<endl;
//        }
    }
   // cout<<endl;
     for(int w=0;w<pm;w++)
    {
        cout<<"------------";
    }
    cout<<endl;
}
