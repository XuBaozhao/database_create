#include<iomanip>

void   visit1(string path,int layer)//显示数据库信息
{
    struct _finddata_t   filefind;
    string  curr=path+"\\*.*";
    int   done=0,i,handle;
    if((handle=_findfirst(curr.c_str(),&filefind))==-1)return;
    cout<<"--------------------"<<endl;
    cout<<"|  Table           |"<<endl;
    cout<<"--------------------"<<endl;
    int to=0;
    while(!(done=_findnext(handle,&filefind)))
    {
        if(to!=0){
        string file_name = filefind.name;
        file_name = file_name.substr(0,file_name.length()-4);
        cout.setf(ios::left);
        cout<<setw(19)<<file_name<<"|"<<endl;
        }
        to++;
    }
    cout<<"--------------------"<<endl;
    _findclose(handle);
}

void show_tables(string path)//显示数据表信息
{
    visit1(path,1);
}
