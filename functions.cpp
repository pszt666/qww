// Copyright©2023/2/14
// Author:yapeng
// This file is to execute the function and class of function.h
#include "./functions.h"
#include <algorithm>
#include <fstream>

// symbols the num of data we have read and
// according to it we can know when to exit
int CNT = 0;
// record the data we have read
int DATA_NUM = 0;
// save data read from file
vector<double> DATA;

// this function helps to
// sort vectors according to the size
bool cmp(const vector<double> &a, const vector<double> &b) {

    if (a.size() < b.size())
        return true;
    else
        return false;
}

LoserTree::LoserTree() {
}
LoserTree::LoserTree(int merge_current_number,
                     int merge_max_number) {

    merge_current_number_ = merge_current_number;
    merge_max_number_ = merge_max_number;
}
LoserTree::LoserTree(vector<vector<double>> merge_area) {
    merge_area_ = merge_area;
}
void LoserTree::judge_loser_tree(int ls[NUM_MEMORY_SIZE],
                                 LEAFNODE wa[NUM_MEMORY_SIZE],
                                 int q) {
    // father symbols the father of the current node
    //  workarea is the work area the father belongs to
    int work_area, father;
    // find q's father
    for (father = (q + NUM_MEMORY_SIZE) / 2,
        work_area = ls[father];
         father > 0;
         father = father / 2, work_area = ls[father]) {
        // the edge with the less m_num loses
        //  if their m_num equal then compare
        // their nums and the less loses then
        // make the winner q replace this work area
        if (wa[work_area].m_num < wa[q].m_num ||
            (wa[work_area].m_num == wa[q].m_num &&
             wa[work_area].num < wa[q].num)) {
            ls[father] = q;
            q = work_area;
        }
    }
    ls[0] = q;
}
void LoserTree::build_loser_tree(int ls[NUM_MEMORY_SIZE],
                                 LEAFNODE wa[NUM_MEMORY_SIZE]) {
    for (int i = 0; i < NUM_MEMORY_SIZE; i++) {
        // initiate wa and ls
        wa[i].m_num = ls[i] = 0;
    }
    // read data to fill the work area
    for (int i = NUM_MEMORY_SIZE - 1; i >= 0; i--) {
        wa[i].num = DATA[CNT++];
        wa[i].m_num = 1;
        judge_loser_tree(ls, wa, i);
    }
}
void LoserTree::get_run(int ls[NUM_MEMORY_SIZE], LEAFNODE wa[NUM_MEMORY_SIZE],
                        int merge_current_number, int *merge_max_number) {
    // minmax symbols the num which will be got
    double minmax;
    // minmax_area symbols the area which minmax belongs to
    int minmax_area;
    // area symbols a new merge area
    vector<double> area;
    // when m_num>merge_current_number means this area has ended
    while (wa[ls[0]].m_num <= merge_current_number) {
        // record the work area number
        minmax_area = ls[0];
        // renew minmax
        minmax = wa[minmax_area].num;
        // add minmax to area
        area.push_back(minmax);
        // when CNT==DATA_NUM means data has all been handled
        if (CNT == DATA_NUM) {
            wa[minmax_area].m_num = *merge_max_number + 1;

        } else {
            // read a new number from DATA
            wa[minmax_area].num = DATA[CNT++];
            // if this number minus minmax means
            // this number belongs to another area
            if (wa[minmax_area].num < minmax) {
                *merge_max_number = merge_current_number + 1;
                wa[minmax_area].m_num = *merge_max_number;
            } else {
                wa[minmax_area].m_num = merge_current_number;
            }
        }
        judge_loser_tree(ls, wa, minmax_area);
    }
    // this area has been built
    // and merge it to the merge_area_
    merge_area_.push_back(area);
}
void LoserTree::replace_selection() {
    merge_current_number_ = merge_max_number_ = 1;
    // initiate loser tree
    build_loser_tree(loser_tree_, work_area_);
    // while current number means max
    // number means date has all been read
    while (merge_current_number_ <= merge_max_number_) {
        // call build merge area function
        get_run(loser_tree_, work_area_, merge_current_number_,
                &merge_max_number_);
        // renew merge_current number with the m_number of top tree
        merge_current_number_ = work_area_[loser_tree_[0]].m_num;
    }
}
vector<vector<double>> LoserTree::get_merge_area() {
    return merge_area_;
}

void LoserTree::judge_loser_tree_a(int *ls, LEAFNODE *wa, int q) {
    int work_area, father;
    for (father = (q + NUM_HTREE_SIZE) / 2, work_area = ls[father];
         father > 0; father = father / 2, work_area = ls[father]) {
        if (wa[work_area].num < wa[q].num) {
            ls[father] = q;
            q = work_area;
        }
    }
    ls[0] = q;
}
void LoserTree::build_loser_tree_a(int *ls, LEAFNODE *wa,
                                   vector<vector<double>> merge_area) {
    for (int i = 0; i < NUM_HTREE_SIZE; i++) {// initiate loser tree
        ls[i] = 0;
        wa[i].num = -MAX;
    }
    for (int i = NUM_HTREE_SIZE - 1; i >= 0; i--) {
        wa[i].num = merge_area[i][0];
        // delete the factor that has been addend to
        vector<double>::iterator k = merge_area[i].begin();
        merge_area[i].erase(k);
        judge_loser_tree_a(ls, wa, i);
    }
}
vector<double> LoserTree::get_run_a(int *ls, LEAFNODE *wa,
                                    vector<vector<double>> merge_area) {
    double minmax;
    int q;
    vector<double> merge_res;
    // when num equals MAX means
    // this area has reached to the end
    while (wa[ls[0]].num != MAX) {
        q = ls[0];
        minmax = wa[q].num;
        merge_res.push_back(minmax);
        wa[q].num = merge_area[q][0];
        vector<double>::iterator k = merge_area[q].begin();
        merge_area[q].erase(k);
        judge_loser_tree_a(ls, wa, q);
    }
    return merge_res;
}
vector<double> LoserTree::merge(vector<vector<double>> merge_area) {
    vector<double> sort_res;
    // every area has added MAX so we can
    // judge whether has reached to the end
    for (int i = 0; i < NUM_HTREE_SIZE; i++)
        merge_area[i].push_back(MAX);
    // initiate the loser tree
    build_loser_tree_a(loser_tree_a_, work_area_a_, merge_area);
    // get the merge area
    sort_res = get_run_a(loser_tree_a_, work_area_a_, merge_area);
    return sort_res;
}
void savefile(vector<double> res) {
    std::ofstream destFile("out.txt", std::ios::out);
    if (!destFile) {

        printf("error opening destination file.");
        return;
    }
    destFile.precision(10);
    // use scientific to output
    destFile.setf(std::ios_base::scientific, std::ios_base::floatfield);
    // make words output as the form of uppercase
    destFile.setf(std::ios_base::uppercase);
    for (int i = 0; i < res.size(); i++)
        destFile << std::showpos << res[i] << std::endl;
    destFile.close();
}
// read data from file
void read_file() {
    double file_read_data;
    std::ifstream srcFile("test.txt", std::ios::in);
    // open failure
    if (!srcFile) {
        printf("error opening source file.");
        return;
    }
    while (srcFile >> file_read_data) {
        // DATA_NUM symbols the number of the data
        DATA_NUM++;
        // read date from file to DATA
        DATA.push_back(file_read_data);
    }
    // close this file
    srcFile.close();
}
void save_merge_area(vector<vector<double>> mergearea) {
    std::ofstream destFile("duan.txt", std::ios::out);
    if (!destFile) {
        printf("error opening destination file.");
        return;
    }
    for (int i = 0; i < mergearea.size(); i++) {
        destFile << i << ":";
        for (int j = 0; j < mergearea[i].size(); j++)
            destFile << mergearea[i][j] << " ";
        destFile << std::endl;
    }

    destFile.close();
}
void LoserTree::huffman() {
    // we can create k nodes
    int k = NUM_HTREE_SIZE;
    int size = merge_area_.size();
    // add empty merge area to make
    // the sum can be divided by k
    if ((size - 1) % (k - 1) != 0) {
        for (int i = 0; i < k - 1 - (size - 1) % (k - 1); i++) {
            vector<double> obj;
            merge_area_.push_back(obj);
        }
    }
    // sort merge_area_ according to the size
    sort(merge_area_.begin(), merge_area_.end(), cmp);
    // when merge_area_ has only one factor
    // it means the huffman has been built
    while (merge_area_.size() != 1) {
        vector<vector<double>> process;
        // select top k min area to merge
        for (int i = 0; i < k; i++) {
            process.push_back(merge_area_[0]);
            merge_area_.erase(merge_area_.begin());
        }
        // res used to save these k areas
        vector<double> res = merge(process);
        merge_area_.push_back(res);
        sort(merge_area_.begin(), merge_area_.end(), cmp);
    }
    // output these result data to out.txt
    savefile(merge_area_[0]);
}
