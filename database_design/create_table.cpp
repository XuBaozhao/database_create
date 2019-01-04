void create_table(FILE *fp,string tn)//�������ݱ�
{
    const char *p = tn.c_str();
    fp= fopen(p,"w");
    fclose(fp);
    cout<<"Query OK, 0 rows affected��"<<endl;
}

void create_table_step(int next,int num,string name,string str)
{
    FILE *FP;
    const char *p = name.c_str();
    if((FP=fopen(p,"a"))==NULL)
    {
        cout<<"���ݱ��ʧ�ܣ�"<<endl;
    }
    else
    {
        // cout<<"���ݱ�򿪳ɹ���"<<endl;
        // cout<<"������Ϣ��"<<endl;
        string f="";
        string t="";
        string n="NO";
        string k="NO";
        string d="NULL";
        string e="NULL";
        string value="";
        char o=' ';
        char gg='Q';

        if(next==0)
        {
            if(num==1)
            {
                fprintf(FP,"%c",gg);
                fprintf(FP,"%c",o);
                // cout<<"������Filed��Ϣ��"<<endl;
                //cin>>f;
                f=str;
                const char *ff = f.c_str();

                fprintf(FP,"%s",ff);
                fprintf(FP,"%c",o);
            }
            if(num==2)
            {
                // cout<<"������Type��Ϣ��"<<endl;
                //cin>>t;
                t = str;
                const char *tt = t.c_str();
                fprintf(FP,"%s",tt);
                fprintf(FP,"%c",o);
            }
            if(num==3)
            {
                //cout<<"������Null��Ϣ��(YES/NO)"<<endl;
                //cin>>n;
                n = str;
                const char *nn = n.c_str();
                fprintf(FP,"%s",nn);
                fprintf(FP,"%c",o);
            }
            if(num==4)
            {
                // cout<<"������Key��Ϣ��(YES/NO)"<<endl;
                //cin>>k;
                k = str;
                const char *kk = k.c_str();
                fprintf(FP,"%s",kk);
                fprintf(FP,"%c",o);
            }
            if(num==5)
            {
                //  cout<<"������Default��Ϣ��"<<endl;
                //cin>>d;
                d= str;
                const char *dd = d.c_str();
                fprintf(FP,"%s",dd);
                fprintf(FP,"%c",o);
            }
            if(num==6)
            {
                //  cout<<"������Extra��Ϣ��"<<endl;
                //cin>>e;
                e = str;
                const char *ee = e.c_str();
                fprintf(FP,"%s",ee);
                fprintf(FP,"%c",o);
                fputc(10,FP);
            }
            fclose(FP);
            //   cout<<"�ɹ��洢��"<<endl;
        }
        else
        {
            if(num==2)
            {
                //   cout<<"������Null��Ϣ��(YES/NO)"<<endl;
                //cin>>n;
                // n = str;
                const char *nn = n.c_str();
                fprintf(FP,"%s",nn);
                fprintf(FP,"%c",o);
                //  cout<<"������Key��Ϣ��(YES/NO)"<<endl;
                //cin>>k;
                // k = str;
                const char *kk = k.c_str();
                fprintf(FP,"%s",kk);
                fprintf(FP,"%c",o);
                // cout<<"������Default��Ϣ��"<<endl;
                //cin>>d;
                //d= str;
                const char *dd = d.c_str();
                fprintf(FP,"%s",dd);
                fprintf(FP,"%c",o);
                // cout<<"������Extra��Ϣ��"<<endl;
                //cin>>e;
                //e = str;
                const char *ee = e.c_str();
                fprintf(FP,"%s",ee);
                fprintf(FP,"%c",o);
                fputc(10,FP);
            }
            if(num==3)
            {
                //  cout<<"������Key��Ϣ��(YES/NO)"<<endl;
                //cin>>k;
                // k = str;
                const char *kk = k.c_str();
                fprintf(FP,"%s",kk);
                fprintf(FP,"%c",o);
                //  cout<<"������Default��Ϣ��"<<endl;
                //cin>>d;
                //d= str;
                const char *dd = d.c_str();
                fprintf(FP,"%s",dd);
                fprintf(FP,"%c",o);
                // cout<<"������Extra��Ϣ��"<<endl;
                //cin>>e;
                //e = str;
                const char *ee = e.c_str();
                fprintf(FP,"%s",ee);
                fprintf(FP,"%c",o);
                fputc(10,FP);
            }
            if(num==4)
            {
                //  cout<<"������Default��Ϣ��"<<endl;
                //cin>>d;
                //d= str;
                const char *dd = d.c_str();
                fprintf(FP,"%s",dd);
                fprintf(FP,"%c",o);
                //cout<<"������Extra��Ϣ��"<<endl;
                //cin>>e;
                //e = str;
                const char *ee = e.c_str();
                fprintf(FP,"%s",ee);
                fprintf(FP,"%c",o);
                fputc(10,FP);
            }
            if(num==5)
            {
                //  cout<<"������Extra��Ϣ��"<<endl;
                //cin>>e;
                //e = str;
                const char *ee = e.c_str();
                fprintf(FP,"%s",ee);
                fprintf(FP,"%c",o);
                fputc(10,FP);
            }
            fclose(FP);
            //  cout<<"�ɹ��洢��"<<endl;
        }
    }
}


void insert_value(string name,char words[][21],string kk,int num)
{
    FILE *FP,*fp;

    const char *p = name.c_str();
    int i;

    if((FP=fopen(p,"a"))==NULL)
    {
        cout<<"���ݱ��ʧ�ܣ�"<<endl;
    }
    else
    {
        //cout<<"���ݱ�򿪳ɹ���"<<endl;
        char o=' ';
        char gg='P';

        if(num==1)
        {
            // fputc(10,FP);
            fprintf(FP,"%c",gg);
            fprintf(FP,"%c",o);

            const char *ff = kk.c_str();
            fprintf(FP,"%s",ff);
            fprintf(FP,"%c",o);
        }
        else
        {
            const char *ff = kk.c_str();
            fprintf(FP,"%s",ff);
            fprintf(FP,"%c",o);
        }
        fclose(FP);
       // cout<<"�ɹ��洢��"<<endl;
    }
}


