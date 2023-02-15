// Copyright©2023/2/14
// Author:yapeng
// Header file
#include "./functions.h"

int main() {
    read_file();
    LoserTree *losertree = new LoserTree(1, 1);
    losertree->replace_selection();
    save_merge_area(losertree->get_merge_area());
    LoserTree *loserTree_a = new LoserTree(losertree->get_merge_area());
    loserTree_a->huffman();
    return 0;
}
