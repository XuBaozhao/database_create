void   visit(string path,int layer)//��ʾ���ݿ���Ϣ
{
    struct _finddata_t   filefind;
    string  curr=path+"\\*.*";
    int   done=0,i,handle;
    if((handle=_findfirst(curr.c_str(),&filefind))==-1)return;
    cout<<"----------------------"<<endl;
    cout<<"|  Database          |"<<endl;
    cout<<"----------------------"<<endl;
    int to=0;
    while(!(done=_findnext(handle,&filefind)))
    {

        if(to){
        printf("|%-20s|\n",filefind.name);}
          to++;
    }
    cout<<"----------------------"<<endl;
    _findclose(handle);
}



void show_databases()//��ʾ���ݿ���Ϣ
{
    string path;
    path="database\\";
    visit(path,1);
}
