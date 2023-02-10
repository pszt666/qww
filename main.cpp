#include "functions.h"
int main() {
    readfile();         //读取文件
    replace_selection();//归并选择挑选分成几段归并段，以及每段的数目
    savearea();         //保存归并段数目和种类
    huffman();          //使用哈夫曼树来减少归并过程中需要比较的次数
    system("pause");
    return 0;
}
