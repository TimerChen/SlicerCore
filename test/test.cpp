//
// Created by timemachine on 18-6-25.
//

#include <stdlib.h>
#include <librarySlicerCore.h>

int main()
{
    //start
    slicer_connect(0, NULL, 0, 0);

    int *data = new int;

    slicer_connect((long long)data, data, 0, 0);

    //test();


}