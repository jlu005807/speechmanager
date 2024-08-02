#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include"speechmanager.h"

using namespace std;

void speechmanager::showmenu()
{
    cout << "***************************************" << endl;
    cout << "**********�ݽ��������̹���ϵͳ*********" << endl;
    cout << "*************1-��ʼ�ݽ�����************" << endl;
    cout << "*************2-�鿴�����¼************" << endl;
    cout << "*************3-��ձ�����¼************" << endl;
    cout << "*************0-�˳���������************" << endl;
    cout << "***************************************" << endl;
    return;
}


void speechmanager::exitspeechmanager()
{
    cout << "���Ƿ�ȷ���˳�ϵͳ��" << endl;
    cout << "       1-ȷ��       " << endl;
    cout << "       0-����       " << endl;
    cout << "����������ѡ��";

    int choice;
    cin >> choice;
    while (choice < 0 || choice>1 || cin.fail())
    {
        cin.ignore();
        if (cin.fail()) {
            char cl;
            while ((cl = getchar()) != '\n');
            cin.clear();
        }
        cout << "����������������룺";
        cin >> choice;
    }
    if (choice == 1) {
        cout << "  �˳��ɹ�" << endl;
        cout << "��ӭ�´�ʹ��" << endl;
        system("pause");
        system("cls");
        exit(0);
    }
    else {
        cout << "���سɹ�" << endl;
        system("pause");
        system("cls");
    }

}

void speechmanager::initspeech()
{
    this->v1.clear();
    this->v2.clear();
    this->victory.clear();
    this->m_speaker.clear();

    this->m_index = 1;

    this->m_record.clear();
}

void speechmanager::createspeaker()
{
    string nameseed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameseed.size(); i++)
    {
        string name="ѡ��";
        name += nameseed[i];

        speaker sp(name, 0, 0);
        this->v1.push_back(i + 10001);

        this->m_speaker.insert(make_pair(i + 10001, sp));
    }
}

void speechmanager::startspeech()
{
    //��һ�ֿ�ʼ����
    cout << "��һ�ֱ���������ʼ��" << endl;

    //1.��ǩ
    this->speechdraw();

    //2.��������֣�
    this->speechcontest();

    //3.��ʾ�������
    this->showscore();

    //�ڶ��ֿ�ʼ����
    this->m_index++;
    cout << "�ڶ��ֱ���������ʼ��" << endl;

    //1.��ǩ
    this->speechdraw();

    //2.����
    this->speechcontest();

    //3.��ʾ���ս��
    this->showscore();
    
    //4.����������ļ���
    this->saverecord();

    cout << "�����ݽ�����������" << endl;
    system("pause");
    system("cls");

    //���ñ���
    this->initspeech();
    this->createspeaker();
    this->loadrecord();
}

void speechmanager::speechdraw()
{
    cout << "��(" << this->m_index << ")�ֱ���ѡ�����ڳ�ǩ��" << endl;
    cout << "--------------------------------------" << endl;
    cout << "��ǩ����ݽ�˳�����£�" << endl;

    if (this->m_index == 1) {

        random_shuffle(v1.begin(), v1.end());

        for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    else {

        random_shuffle(v2.begin(), v2.end());

        for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
        {
            cout << *it << " ";
        }

        cout << endl;
    }
    cout << "---------------------------------------------------------------------------" << endl;
    system("pause");
    cout << endl;
}

void speechmanager::speechcontest()
{
    cout << "-------------------��(" << this->m_index << ")�ֱ�����ʽ��ʼ-----------------" << endl;

    multimap<double, int, greater<double>>groupscore;

    int num = 0;

    vector<int>v_src;//ѡ��

    if (this->m_index == 1)
    {
        v_src = v1;
    }
    else {
        v_src = v2;
    }

    for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
    {
        num++;

        deque<double>d;

        for (int i = 0; i < 10; i++)
        {
            double score = (rand() % 401 + 600) / 10.f;

            d.push_back(score);
        }

        sort(d.begin(), d.end(), greater<double>());

        d.pop_back();
        d.pop_front();

        double sum = accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum / (double)d.size();

        this->m_speaker[*it].m_score[this->m_index-1] = avg;

        groupscore.insert(make_pair(avg, *it));

        if (num % 6 == 0)
        {
            cout << "��" << num / 6 << "С��������Σ�" << endl;

            for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end(); it++)
            {
                cout << "��ţ�" << it->second << "   ������ " << this->m_speaker[it->second].m_name << "   �ɼ���" << this->m_speaker[it->second].m_score[this->m_index - 1] << endl;

            }

            int count = 0;
            for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end()&&count<3; it++,count++)
            {
                if (this->m_index == 1)
                {
                    v2.push_back((*it).second);
                }
                else
                {
                    victory.push_back((*it).second);
                }
            }
            groupscore.clear();
            cout << endl;
        }
    }
    cout << "-------------------��(" << this->m_index << ")�ֱ�������---------------------" << endl;
    system("pause");
}

void speechmanager::showscore()
{
    cout << "-------------------��(" << this->m_index << ")�ֽ���ѡ����Ϣ����-------------" << endl;
    
    vector<int> v;
    if (this->m_index == 1) {
        v = v2;
    }
    else {
        v = victory;
    }

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "��ţ�" << *it << "   ������ " << this->m_speaker[*it].m_name << "   �ɼ���" << this->m_speaker[*it].m_score[this->m_index - 1] << endl;

    }
    cout << endl;

    system("pause");
    system("cls");
}

void speechmanager::saverecord()
{
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);

    for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++)
    {
        ofs << *it << "," << this->m_speaker[*it].m_score[1] << ",";

    }
    ofs << endl;

    ofs.close();
    cout << "��¼�Ѿ����棡" << endl;
    this->fileempty = false;
}

void speechmanager::loadrecord()
{
    ifstream ifs("speech.csv",ios::in);
    if (!ifs.is_open())
    {
        this->fileempty = true;
        ifs.close();
        return;
    }
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        this->fileempty = true;
        ifs.close();
        return;
    }

    this->fileempty = false;

    ifs.putback(ch);

    string data;

    int index = 0;
    
    while (ifs >> data)
    {

        vector<string>v;

        int pos = -1;
        int start = 0;

        while (true)
        {
            pos = data.find(",", start);

            if (pos == -1)
            {
                //û���ҵ������
                break;
            }

            string temp = data.substr(start, pos - start);

            v.push_back(temp);

            start = pos + 1;

        }
        this->m_record.insert(make_pair(index, v));
        index++;

    }
    ifs.close();
}

void speechmanager::showrecord()
{

    if (this->fileempty) {
        cout << "�ļ������ڻ��¼Ϊ��" << endl;
    }
    for (int i = 0; i < this->m_record.size(); i++)
    {
        cout << "��" << i + 1 << "�죺" << endl;
        cout << "�ھ���ţ�" << this->m_record[i][0] << "  �ɼ���" << this->m_record[i][1] << endl;
        cout << "�Ǿ���ţ�" << this->m_record[i][2] << "  �ɼ���" << this->m_record[i][3] << endl;
        cout << "������ţ�" << this->m_record[i][4] << "  �ɼ���" << this->m_record[i][5] << endl;    
    }
    system("pause");
    system("cls");
}

void speechmanager::clearrecord()
{

    cout << "�Ƿ�ȷ����ռ�¼��" << endl;
    cout << "    1-ȷ��" << endl;
    cout << "    0-����" << endl;
    cout << "����������ѡ��";

    int select = 0;

    cin >> select;
    while ( select > 1 || select < 0||cin.fail() )
    {
        
        cout << "����������������룺";
        cin.clear();
        if (cin.fail()) {
            char c;
            while (c=getchar()!= '\n'&&c!=EOF);
        }
     
        cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
        
        cin >> select;
    }

    if (select == 1)
    {
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();

        this->initspeech();
        this->createspeaker();
        this->loadrecord();

        cout << "��ճɹ�" << endl;
    }
    system("pause");
    system("cls");
}
speechmanager::speechmanager() {
    this->initspeech();

    this->createspeaker();

    this->loadrecord();

};

speechmanager::~speechmanager() {

};