void read_txt(string name,char words[][21],int sum)//��ʾ���ݽṹ��Ϣ
{
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<"|    Field     |    Type     |    Null     |    Key     |    Default     |    Extra     |"<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    FILE *fp ;
    int i,j;
    const char *p = name.c_str();
    fp=fopen(p, "r");
    if ( fp==NULL )
    {
        printf("��ȡ��ʾʧ��\n");
    }
    for( i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
    {
        if ( fscanf(fp, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
            break;
    }
    fclose(fp);
    for( j=0; j<i; j++ ) //�������������
    {
        string ss1(words[j]);
        if((j>=7)&&(j%7==0)&&(ss1!="Q"))
        {
            break;
        }
        if(j==1)
            printf( "| %-13s|", words[j] ) ;
        if(j==2)
            printf( " %-12s|", words[j] ) ;
        if(j==3)
            printf( " %-12s|", words[j] ) ;
        if(j==4)
            printf( " %-11s|", words[j] ) ;
        if(j==5)
            printf( " %-15s|", words[j] ) ;

        if(j>=6&&(j+1)%7==0)
        {
            printf( " %-13s|", words[j] ) ;
            cout<<endl;
        }
        if(j>=6&&(j+1)%7==2)
            printf( "| %-12s |", words[j] ) ;
        if(j>=6&&(j+1)%7==3)
            printf( " %-12s|", words[j] ) ;
        if(j>=6&&(j+1)%7==4)
            printf( " %-12s|", words[j] ) ;
        if(j>=6&&(j+1)%7==5)
            printf( " %-11s|", words[j] ) ;
        if(j>=6&&(j+1)%7==6)
            printf( " %-15s|", words[j] ) ;
    }
    //cout<<endl;
  cout<<"-----------------------------------------------------------------------------------------"<<endl;
}

void read_view(string name,char words[][21])
{

    FILE *fp;
    int i;
    int j;
    const char *p = name.c_str();
    fp=fopen(p, "r");

    if ( fp==NULL )
    {
        printf("��ȡ��ʾʧ��\n");
    }
    for( i=0; i<200; i++ ) //ѭ����ȡ�����Ʋ�����100��
    {
        if ( fscanf(fp, "%20s", words[i] )!= 1 ) //����ÿ�����ʲ�����20��
            break;
    }
    fclose(fp);
    for( j=0; j<i; j++ ) //�������������
    {
        printf( "%s ", words[j] ) ;
    }
    cout<<endl;
}
