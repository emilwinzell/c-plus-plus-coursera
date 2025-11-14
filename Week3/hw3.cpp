#include "prim.h"
using namespace std;

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

int main() {
    string path = "sample_data";
    Graph gr{path};
    gr.print();

    PrimsMST pmst{gr};
    pmst.find_mst(0);
}