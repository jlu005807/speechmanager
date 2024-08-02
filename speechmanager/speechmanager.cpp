#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include"speechmanager.h"

using namespace std;

void speechmanager::showmenu()
{
    cout << "***************************************" << endl;
    cout << "**********演讲比赛流程管理系统*********" << endl;
    cout << "*************1-开始演讲比赛************" << endl;
    cout << "*************2-查看往届记录************" << endl;
    cout << "*************3-清空比赛记录************" << endl;
    cout << "*************0-退出比赛程序************" << endl;
    cout << "***************************************" << endl;
    return;
}


void speechmanager::exitspeechmanager()
{
    cout << "你是否确定退出系统？" << endl;
    cout << "       1-确定       " << endl;
    cout << "       0-返回       " << endl;
    cout << "请输入您的选择：";

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
        cout << "输入错误，请重新输入：";
        cin >> choice;
    }
    if (choice == 1) {
        cout << "  退出成功" << endl;
        cout << "欢迎下次使用" << endl;
        system("pause");
        system("cls");
        exit(0);
    }
    else {
        cout << "返回成功" << endl;
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
        string name="选手";
        name += nameseed[i];

        speaker sp(name, 0, 0);
        this->v1.push_back(i + 10001);

        this->m_speaker.insert(make_pair(i + 10001, sp));
    }
}

void speechmanager::startspeech()
{
    //第一轮开始比赛
    cout << "第一轮比赛即将开始！" << endl;

    //1.抽签
    this->speechdraw();

    //2.比赛（打分）
    this->speechcontest();

    //3.显示晋级结果
    this->showscore();

    //第二轮开始比赛
    this->m_index++;
    cout << "第二轮比赛即将开始！" << endl;

    //1.抽签
    this->speechdraw();

    //2.比赛
    this->speechcontest();

    //3.显示最终结果
    this->showscore();
    
    //4.保存分数到文件里
    this->saverecord();

    cout << "本届演讲比赛结束！" << endl;
    system("pause");
    system("cls");

    //重置比赛
    this->initspeech();
    this->createspeaker();
    this->loadrecord();
}

void speechmanager::speechdraw()
{
    cout << "第(" << this->m_index << ")轮比赛选手正在抽签！" << endl;
    cout << "--------------------------------------" << endl;
    cout << "抽签后的演讲顺序如下：" << endl;

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
    cout << "-------------------第(" << this->m_index << ")轮比赛正式开始-----------------" << endl;

    multimap<double, int, greater<double>>groupscore;

    int num = 0;

    vector<int>v_src;//选手

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
            cout << "第" << num / 6 << "小组比赛名次：" << endl;

            for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end(); it++)
            {
                cout << "编号：" << it->second << "   姓名： " << this->m_speaker[it->second].m_name << "   成绩：" << this->m_speaker[it->second].m_score[this->m_index - 1] << endl;

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
    cout << "-------------------第(" << this->m_index << ")轮比赛结束---------------------" << endl;
    system("pause");
}

void speechmanager::showscore()
{
    cout << "-------------------第(" << this->m_index << ")轮晋级选手信息如下-------------" << endl;
    
    vector<int> v;
    if (this->m_index == 1) {
        v = v2;
    }
    else {
        v = victory;
    }

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "编号：" << *it << "   姓名： " << this->m_speaker[*it].m_name << "   成绩：" << this->m_speaker[*it].m_score[this->m_index - 1] << endl;

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
    cout << "记录已经保存！" << endl;
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
                //没有找到的情况
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
        cout << "文件不存在或记录为空" << endl;
    }
    for (int i = 0; i < this->m_record.size(); i++)
    {
        cout << "第" << i + 1 << "届：" << endl;
        cout << "冠军编号：" << this->m_record[i][0] << "  成绩：" << this->m_record[i][1] << endl;
        cout << "亚军编号：" << this->m_record[i][2] << "  成绩：" << this->m_record[i][3] << endl;
        cout << "季军编号：" << this->m_record[i][4] << "  成绩：" << this->m_record[i][5] << endl;    
    }
    system("pause");
    system("cls");
}

void speechmanager::clearrecord()
{

    cout << "是否确定清空记录？" << endl;
    cout << "    1-确定" << endl;
    cout << "    0-返回" << endl;
    cout << "请输入您的选择：";

    int select = 0;

    cin >> select;
    while ( select > 1 || select < 0||cin.fail() )
    {
        
        cout << "输入错误，请重新输入：";
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

        cout << "清空成功" << endl;
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