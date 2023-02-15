#pragma once
// Copyright©2023/2/14
// Author:yapeng
// Header file
#ifndef EXTERNALSORT_FUNCTONS_H
#define EXTERNALSORT_FUNCTONS_H
#include <stdint.h>
#include <vector>

using std::vector;
extern vector<double> DATA;   // save date from file
extern int CNT;               // symbols t
extern int DATA_NUM;          // symbols the number of data
const int64_t MAX = 100000000;// set the bound of the data
const int NUM_MEMORY_SIZE = 3;// set the memory size
const int NUM_HTREE_SIZE = 2; // Tree Nodes num

// definite LEAFNODE to save the data andthus help
// losertree to produce merge areas.
typedef struct {
    double num;
    int m_num;// symbols the number of this node
} LEAFNODE;
// Use LoserTree to divide data into many merge areas
class LoserTree {
public:
    LoserTree();
    // Construction function 1
    explicit LoserTree(int merge_current_number, int merge_max_number);
    // Construction function 2
    explicit LoserTree(vector<vector<double>> merge_area);
    // Initialize loser tree function
    void build_loser_tree(int ls[NUM_MEMORY_SIZE],
                          LEAFNODE wa[NUM_MEMORY_SIZE]);
    // q symbols the position that changed.
    // This function is to renew loser tree.
    void judge_loser_tree(int ls[NUM_MEMORY_SIZE],
                          LEAFNODE wa[NUM_MEMORY_SIZE], int q);
    // Begin the process of divide data into merge areas
    // and these merge areas are sorted.
    void get_run(int ls[NUM_MEMORY_SIZE], LEAFNODE wa[NUM_MEMORY_SIZE],
                 int merge_current_number, int *merge_max_number);
    // Begin the process of replace selection to get merge areas
    void replace_selection();
    // renew the loser tree
    void judge_loser_tree_a(int ls[NUM_HTREE_SIZE],
                            LEAFNODE wa[NUM_HTREE_SIZE], int q);
    // initiate the loser tree
    void build_loser_tree_a(int ls[NUM_HTREE_SIZE], LEAFNODE wa[NUM_HTREE_SIZE],
                            vector<vector<double>> merge_area);
    // execute the loser tree programe
    vector<double> get_run_a(int *ls, LEAFNODE *wa,
                             vector<vector<double>> merge_area);
    // merge the mergearea into a bigger one
    vector<double> merge(vector<vector<double>> merge_area);
    // get merge area from class
    vector<vector<double>> get_merge_area();
    // use huffman tree to decrease time use when merging these areas
    void huffman();

private:
    // save merge area that produced by loser tree
    vector<vector<double>> merge_area_;
    // merge_current_number symbols the maximum of number of merge area
    int merge_current_number_;
    // merge_max_number symbols the current number of merge area.
    int merge_max_number_;
    // set loser tree work area to save data
    LEAFNODE work_area_[NUM_MEMORY_SIZE];
    // loser tree save construction
    int loser_tree_[NUM_MEMORY_SIZE];
    LEAFNODE work_area_a_[NUM_HTREE_SIZE];
    int loser_tree_a_[NUM_HTREE_SIZE];
};
// definite the rules to compare vector to sort
bool cmp(const vector<double> &a, const vector<double> &b);
// save merge areas to duan.txt
void save_merge_area(vector<vector<double>> mergearea);
// read data file from test.txt
void read_file();
// save result file to out.txt
void savefile(vector<double> res);
#endif
