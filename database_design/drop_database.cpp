int  removeDir(const char *dirPath)//ɾ�����ݿ�
{
    struct _finddata_t fb;   //������ͬ�����ļ��Ĵ洢�ṹ��
    char  path[250];
    long    handle;
    int  resultone;
    int   noFile;            //��ϵͳ�����ļ��Ĵ�����
    noFile = 0;
    handle = 0;
    //����·��
    strcpy(path,dirPath);
    strcat (path,"/*");
    handle = _findfirst(path,&fb);
    //�ҵ���һ��ƥ����ļ�
    if (handle != 0)
    {
        //�����Լ����ҵ�ƥ����ļ�������ִ��
        while (0 == _findnext(handle,&fb))
        {
            //windows�£����и�ϵͳ�ļ�����Ϊ��..��,������������
            noFile = strcmp(fb.name,"..");
            if (0 != noFile)
            {
                //��������·��
                memset(path,0,sizeof(path));
                strcpy(path,dirPath);
                strcat(path,"/");
                strcat (path,fb.name);
                //����ֵΪ16����˵�����ļ��У�����
                if (fb.attrib == 16)
                {
                    removeDir(path);
                }
                //���ļ��е��ļ���ֱ��ɾ�������ļ�����ֵ�����û����ϸ���飬���ܻ������������
                else
                {
                    remove(path);
                }
            }
        }
        //�ر��ļ��У�ֻ�йر��˲���ɾ����������������˺ܾã���׼c���õ���closedir
        //������ܣ�һ�����Handle�ĺ���ִ�к󣬶�Ҫ���йرյĶ�����
        _findclose(handle);
    }
    //�Ƴ��ļ���
    resultone = rmdir(dirPath);
    return  resultone;
}


void drop_database(string name)//ɾ�����ݿ�
{
    const char *p = name.c_str();
    if(removeDir(p))
    {
        cout<<"ERROR��"<<endl;
    }
    else
    {
        cout<<"Query OK, 0 rows affected��"<<endl;
    }
}
