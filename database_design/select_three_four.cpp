#include<iomanip>

void select_column2(string xing,string name,string select_name,string value,char words[][21])
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


    //int if_have_column_name = 0;   select xing from name where select_name=value;
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

   // cout<<"column_num........"<<column_num<<endl;
    //cout<<"xing...."<<xing<<"/////"<<endl;

    int search_column_num = 0;
    if(xing=="*")
    {

        for(int w=0;w<column_num;w++)
        {
            cout<<"----------";
        }
        cout<<endl;

        for(int j=1; j<column_num*7; j=j+7)
        {
            string ss(words[j]);
            if(ss==select_name)
            {
                search_column_num = (j-1)/7+1;
            }
           // cout<<"| "<<words[j];
            printf("%-9s|",words[j]);
        }
        //cout<<"|";
        cout<<endl;

       for(int w=0;w<column_num;w++)
        {
            cout<<"----------";
        }
        cout<<endl;

        for(int j=column_num*7; j<i; j++)
        {
            string s(words[j]);
            if(s==value)
            {
                for(int w=j-search_column_num+1; w<j-search_column_num+1+column_num; w++)
                {
                    string sss(words[w]);
                    //cout<<"| ";
                    //cout<<sss;
                    printf("%-9s|",words[w]);
                }
               cout<<endl;
                for(int w=0;w<column_num;w++)
        {
            cout<<"----------";
        }
        cout<<endl;
                //cout<<"| "<<;
            }
        }
    }
    else
    {
        cout<<"----------"<<endl;
        //cout<<"| "<<xing<<" |"<<endl;
        cout.setf(ios::left);
        cout<<setw(9)<<xing<<"|"<<endl;
        cout<<"----------"<<endl;
        int column_index,sea;
        for(int j=0;j<i;j++)
        {
            string s(words[j]);
            if(s==select_name)
            {
                column_index = j/7+1;
                break;
            }
        }
          for(int j=0;j<i;j++)
        {
            string s(words[j]);
            if(s==xing)
            {
                sea = j/7+1;
                break;
            }
        }

        for(int j=column_num*7; j<i; j++)
        {
            string _s(words[j]);
          if(_s==value)
          {
              string s(words[j+sea-column_index]);
             // cout<<"| "<<s<<" |"<<endl;
             printf("%-9s|\n",words[j+sea-column_index]);
              cout<<"----------"<<endl;
          }

        }
    }


}
