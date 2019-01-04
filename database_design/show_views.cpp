#include<iomanip>

void   visit1(string path,int layer,char words[][21])//显示数据库信息
{
    struct _finddata_t   filefind;
    string  curr=path+"\\*.*";
    int   done=0,i,handle;
    int put = 0;
    if((handle=_findfirst(curr.c_str(),&filefind))==-1)return;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    cout<<"|   View                                                                       |"<<endl;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    while(!(done=_findnext(handle,&filefind)))
    {
        string file_name = filefind.name;

        file_name = file_name.substr(0,file_name.length()-4);

        cout.setf(ios::left);



        if(put!=0)
        {
            cout<<setw(78)<<file_name<<"↓"<<endl;
         file_name = path+file_name+".txt";
         read_view(file_name,words);
          cout<<"--------------------------------------------------------------------------------"<<endl;
        }
         put++;
    }
 // cout<<endl;
   // cout<<"--------------------------------------------------------------------------------"<<endl;
    _findclose(handle);
}

void   visit5(string path,int layer,char words[][21])//显示数据库信息
{
    struct _finddata_t   filefind;
    string  curr=path+"\\*.*";
    int   done=0,i,handle;
    int put = 0;
    if((handle=_findfirst(curr.c_str(),&filefind))==-1)return;

    while(!(done=_findnext(handle,&filefind)))
    {
        string file_name = filefind.name;

        file_name = file_name.substr(0,file_name.length()-4);

        cout.setf(ios::left);



        if(put!=0)
        {

             string toto = path+file_name+".txt";
            // cout<<"....."<<toto<<"....."<<endl;
            cout<<"Table->"<<file_name<<":"<<endl;
             read_txt(toto,words,1);



        }
         put++;
         cout<<endl;
    }
cout<<endl;
   // cout<<"--------------------------------------------------------------------------------"<<endl;
    _findclose(handle);
}


void show_views(string to,string path,char words[][21])//显示数据表信息
{
    visit1(path,1,words);
    //read_txt(name,words,sum);
    visit5(to,1,words);
}
