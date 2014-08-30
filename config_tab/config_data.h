#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

struct ConfigData
{
    ConfigData() = default;
    ConfigData(int width, int height, int size, int procent, int iteration, int tabusize, int tabutime)
        :   width(width),
            height(height),
            size(size),
            procent(procent),
            iteration(iteration),
            tabusize(tabusize),
            tabutime(tabutime)
    {

    }

    int width;
    int height;
    int size;
    int procent;
    int iteration;
    int tabusize;
    int tabutime;
};

#endif // CONFIG_DATA_H
