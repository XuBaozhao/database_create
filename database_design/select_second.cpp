void select_column(string table,string name,char words[][21])
{
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


    //int if_have_column_name = 0;
    int column_num = 0;
    for(int k=0; k<i; k++)
    {
        string ss(words[k]);
        if(ss=="P")
        {
            column_num = k/7;
            break;
        }
    }

    int search_column_num = 0;
    for(int h=0; h<i; h++)
    {
        string ss1(words[h]);
        if(ss1==table)
        {
            search_column_num = (h-1)/7+1;
            cout<<"------------"<<endl;
            //cout<<"| "<<table<<" |"<<endl;
            printf(" %-10s|\n",words[h]);
            cout<<"------------"<<endl;
            break;
        }
    }
    if(search_column_num==0)
    {
        cout<<"NOT EXIST!"<<endl;
    }
    else
    {
        for(int w=column_num*7; w<i; w++)
        {
            string ss(words[w]);

            if(ss=="P")
            {
                //string s_s(words[w+search_column_num]);
                // cout<<"--------"<<endl;
                //cout<<"| "<<s_s<<" |"<<endl;
                printf(" %-10s|\n",words[w+search_column_num]);
            }
        }
    }
    cout<<"------------"<<endl;

}
