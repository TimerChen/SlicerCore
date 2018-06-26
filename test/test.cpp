//
// Created by timemachine on 18-6-25.
//

#include <stdlib.h>
#include <librarySlicerCore.h>

#include <time.h>
#include <zconf.h>
#include <iostream>

int main()
{
    //start
    slicer_connect(0, NULL, 0, 0);

    int *data = new int;



    while(1)
    {
        slicer_connect((long long)data, data, 0, 0);
		std::cerr << "fuck" << std::endl;
        sleep(0.01);
    }

    //test();


}