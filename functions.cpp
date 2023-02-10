//
// Created by dell on 2023/2/9.
//
#include "functions.h"
int CNT = 3;
int DATA_NUM = 0;
vector<int> areasize;
vector<double> TT;                                        //将文件中的数据读取到TT中
vector<vector<double>> mergearea;                         //测试用，存储归并段
bool cmp(const vector<double> &a, const vector<double> &b)//设置排序规则，归并段数目少的排在前面，方便之后建立哈弗曼树
{

    if (a.size() < b.size())
        return true;
    else
        return false;
}
void judgetree(int ls[MAX_NUM], LEAFNODE wa[MAX_NUM], int q)//调整败者树结构
{
    int s, t;//t代表q的双亲节点
    for (t = (q + MAX_NUM) / 2, s = ls[t]; t > 0; t = t / 2, s = ls[t]) {
        if (wa[s].rnum < wa[q].rnum || (wa[s].rnum == wa[q].rnum && wa[s].num < wa[q].num)) {
            ls[t] = q;
            q = s;
        }
    }
    ls[0] = q;
}
void get_run(int ls[MAX_NUM], LEAFNODE wa[MAX_NUM], int rc, int *rmax) {
    double minmax;//代表当前取出的最小值
    int q;        //q指示最小值所在哪一块
    vector<double> area;

    while (wa[ls[0]].rnum <= rc)//当前段
    {
        q = ls[0];
        minmax = wa[q].num;
        area.push_back(minmax);//写文件操作！！！！！！！！！！！！！！！
        if (CNT == DATA_NUM)   //读取文件判空操作！！！！！！！！！
        {
            wa[q].rnum = *rmax + 1;

        } else {
            wa[q].num = TT[CNT++];//！！！！！！！！！！！读文件操作
            if (wa[q].num < minmax) {
                *rmax = rc + 1;
                wa[q].rnum = *rmax;
            } else {
                wa[q].rnum = rc;
            }
        }
        judgetree(ls, wa, q);
    }
    mergearea.push_back(area);
    areasize.push_back(area.size());
}
void replace_selection() {
    int rc, rmax;              //rc代表当前处理的第几段，rmax代表所能处理的最大段，该标志来区分什么时候进入下一段的处理。
    int loser_tree[MAX_NUM];   //败者树,由于是完全二叉树，所以使用顺序存储即可。
    LEAFNODE workarea[MAX_NUM];//存储目前正在比较的工作区
    rc = rmax = 1;
    buildtree(loser_tree, workarea);
    while (rc <= rmax) {
        get_run(loser_tree, workarea, rc, &rmax);//建成第一段归并段
        rc = workarea[loser_tree[0]].rnum;       //更新rc的段号
    }
}
void judgetree1(int ls[MERGE_NUM], LEAFNODE wa[MERGE_NUM], int q)//q表示刚刚更改的标志位位置
{
    int s, t;//t代表q的双亲节点
    for (t = (q + MERGE_NUM) / 2, s = ls[t]; t > 0; t = t / 2, s = ls[t]) {
        if (wa[s].num < wa[q].num) {
            ls[t] = q;
            q = s;
        }
    }
    ls[0] = q;
}
void buildtree(int ls[MAX_NUM], LEAFNODE wa[MAX_NUM])//构建败者树函数
{
    for (int i = 0; i < MAX_NUM; i++) {
        wa[i].rnum = ls[i] = 0;//初始化均为0
    }
    for (int i = MAX_NUM - 1; i >= 0; i--) {
        wa[i].num = TT[CNT++];//！！！！！！！！！！！读文件操作
        wa[i].rnum = 1;
        judgetree(ls, wa, i);
    }
}
void buildtree1(int ls[MERGE_NUM], LEAFNODE wa[MERGE_NUM], vector<vector<double>> process)//构建败者树函数
{
    for (int i = 0; i < MERGE_NUM; i++) {
        ls[i] = 0;//初始化均为0
    }
    for (int i = MERGE_NUM - 1; i >= 0; i--) {
        wa[i].num = process[i][0];
        vector<double>::iterator k = process[i].begin();
        process[i].erase(k);
        judgetree1(ls, wa, i);
    }
}
vector<double> get_run1(int ls[MERGE_NUM], LEAFNODE wa[MERGE_NUM], vector<vector<double>> process) {
    double minmax;//代表当前取出的最小值
    int q;        //q指示最小值所在哪一块
    vector<double> res;
    while (wa[ls[0]].num != MAX)//当前段
    {
        q = ls[0];
        minmax = wa[q].num;
        res.push_back(minmax);    //写文件操作！！！！！！！！！！！！！！！
        wa[q].num = process[q][0];//！！！！！！！！！！！读文件操作
        vector<double>::iterator k = process[q].begin();
        process[q].erase(k);//对于每一个归并段都去掉第一个元素
        judgetree1(ls, wa, q);
    }
    return res;
}
vector<double> merge(vector<vector<double>> process)//使用败者树进行段的归并
{
    vector<double> res;
    for (int i = 0; i < MERGE_NUM; i++) process[i].push_back(MAX);//每一个归并段的最后面都加入一个最大值
    int loser_tree[MERGE_NUM];                                    //败者树,由于是完全二叉树，所以使用顺序存储即可。
    LEAFNODE workarea[MERGE_NUM];                                 //存储目前正在比较的工作区
    buildtree1(loser_tree, workarea, process);
    for (int i = 0; i < MERGE_NUM; i++) {
        vector<double>::iterator k = process[i].begin();
        process[i].erase(k);//对于每一个归并段都去掉第一个元素
    }
    res = get_run1(loser_tree, workarea, process);
    return res;
}
void savearea()//保存所有数据分成的归并段数目以及各段数据
{
    ofstream destFile("duan.txt", ios::out);//以文本模式打开out.txt备写
    if (!destFile) {
        //srcFile.close(); 程序结束前不能忘记关闭以前打开过的文件
        cout << "error opening destination file." << endl;
        return;
    }
    //可以像用cin那样用ifstream对象
    for (int i = 0; i < mergearea.size(); i++) {
        destFile << i << ":";
        for (int j = 0; j < mergearea[i].size(); j++)
            destFile << mergearea[i][j] << " ";
        destFile << endl;
    };

    destFile.close();
}
void savefile(vector<double> res) {
    ofstream destFile("out.txt", ios::out);//以文本模式打开out.txt备写
    if (!destFile) {

        cout << "error opening destination file." << endl;
        return;
    }

    destFile.precision(10);
    destFile.setf(ios_base::scientific, ios_base::floatfield);//采用科学计数法
    destFile.setf(ios_base::uppercase);                       //字母大写输出
    for (int i = 0; i < res.size(); i++)
        //可以像 cout 那样使用 ofstream 对象
        destFile << showpos << res[i] << endl;
    destFile.close();
}
void readfile()//读取初始文件的数据
{
    double x;
    ifstream srcFile("text.txt", ios::in);//以文本模式打开in.txt备读
    if (!srcFile) {                       //打开失败
        cout << "error opening source file." << endl;
        return;
    }
    while (srcFile >> x) {
        DATA_NUM++;
        TT.push_back(x);
    }
    srcFile.close();
}
void huffman()//利用huffman树来减小读写外存的次数，k的选值十分重要
{
    int k = MERGE_NUM;
    int size = mergearea.size();
    //priority_queue<vector<double>> q;//优先队列，存储double数组，以每个数组的数目为比较规则
    vector<vector<double>> q;
    for (int i = 0; i < mergearea.size(); i++) {
        q.push_back(mergearea[i]);
    }

    if ((size - 1) % (k - 1) != 0) {
        for (int i = 0; i < k - 1 - (size - 1) % (k - 1); i++) {
            vector<double> obj;

            q.push_back(obj);
        }
    }
    sort(q.begin(), q.end(), cmp);//将所有归并段按照归并段中的数目从小到大排序

    while (q.size() != 1) {
        vector<vector<double>> process;
        for (int i = 0; i < k; i++)//   取出前k个小的数
        {
            process.push_back(q[0]);
            q.erase(q.begin());
        }//弹出顶部数目
        vector<double> res = merge(process);
        q.push_back(res);
        sort(q.begin(), q.end(), cmp);
    }

    savefile(q[0]);//保存结果文件到out.txt中
}