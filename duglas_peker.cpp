#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
//#include <math.h>
#include <cmath>
#include <string>
#include <sys/time.h>

std::vector<int> duglas_peker(std::vector<std::pair<int, double>>, double, int);

int main(int argc, char *argv[])
{
    struct timeval tv;
    std::vector<std::pair<int, double>> values;// {{1,5},{2,3},{5,1},{6,4},{9,6},{11,4},{13,3},{14,2},{18,5}};
    std::vector<int> values_of_return;
    unsigned i = 0;
    //std::string str;
    std::ifstream file("/home/l/code/cpp/data_qt_data_input.txt");
    //double str1;
    //std::stringstream ss;
    int a;
    int x, values_count;
    double y;

    while(!file.eof())//getline(file, str))
    {
        /*a = str.find(',', 0);

        if(a>=0)
            str[a] = '.';

        str = str.substr(str.find('\t'));
        str1 = 0;
        str1 = atof(str.c_str());*/
        //ss << str;
        //ss >> str1;
        //ss.str(std::string());
        //std::cout << i << std::endl;
        //std::cout << str << ' ' << str1 << std::endl;
        file >> x >> y;
        values.push_back({x, y});
        //values.push_back({i, str1});
        //++i;
    }

    values_count = x;
    file.close();

    /*for(i = 0; i < values.size(); ++i)
    {
        //std::cout << values[i].second << std::endl;
    }*/

    gettimeofday(&tv, NULL);
    
    double time_begin = ((double)tv.tv_sec) * 1000 + ((double)tv.tv_usec) / 1000;

    values_of_return = duglas_peker(values, 10, values_count);

    gettimeofday(&tv, NULL);
    
    double time_end = ((double)tv.tv_sec) * 1000 + ((double)tv.tv_usec) / 1000;

    /*for(i = 0; i < values_of_return.size(); ++i)
    {
        if(values_of_return[i])
        {
            std::cout << values[i].first << ' ' << values[i].second << std::endl;
        }
        else
            values[i].second = 0;
    }*/

    std::ofstream file1("/home/l/code/cpp/data_qt_data_output.txt");

    values_count = values_of_return.size();

    for(i = 0; i < values_count; ++i)
        file1 << values[values_of_return[i]].first << ' ' << values[values_of_return[i]].second << std::endl;

    file1.close();
    
    double total_time_ms = time_end - time_begin;

    std::cout << total_time_ms << std::endl;

    std::system("~/code/python/plot.py");

    return 0;
}

std::vector<int> duglas_peker(std::vector<std::pair<int, double>> values, double e, int values_count)
{
    std::stack<std::pair<int, int>> index_of_value;
    std::vector<int> values_for_return;
    unsigned i = 0;
    int startIndex = 0;
    int endIndex = 0;
    double dMax = 0;
    int index = 0;
    double d = 0, p = 0;
    double length_of_line = 0, length_of_line1 = 0, length_of_line2 = 0;
    double a_hight = 0, b_hight = 0;

    index_of_value.push({0, values_count - 1});

    while(!index_of_value.empty())
    {
        startIndex = index_of_value.top().first;
        endIndex = index_of_value.top().second;

        index_of_value.pop();

        dMax = 0;

        //length_of_line = std::sqrt((values[startIndex].first - values[endIndex].first) * (values[startIndex].first - values[endIndex].first) + (values[startIndex].second - values[endIndex].second) * (values[startIndex].second - values[endIndex].second));
        //a_hight = values[startIndex].first - values[endIndex].first;
        //b_hight = values[startIndex].second - values[endIndex].second;
        a_hight = values[endIndex].first - values[startIndex].first;
        b_hight = values[endIndex].second - values[startIndex].second;
        length_of_line = std::sqrt(a_hight * a_hight + b_hight * b_hight);
        //length_of_line = std::sqrt(std::pow(values[startIndex].first - values[endIndex].first, 2) + std::pow(values[startIndex].second - values[endIndex].second, 2));

        for(i = startIndex + 1; i < endIndex; ++i)
        {
            //length_of_line1 = std::sqrt(std::pow(values[i].first - values[endIndex].first, 2) + std::pow(values[i].second - values[endIndex].second, 2));
            //length_of_line2 = std::sqrt(std::pow(values[startIndex].first - values[i].first, 2) + std::pow(values[startIndex].second - values[i].second, 2));
            /*a_hight = values[i].first - values[endIndex].first;
            b_hight = values[i].second - values[endIndex].second;

            length_of_line1 = std::sqrt(a_hight * a_hight + b_hight * b_hight);

            a_hight = values[startIndex].first - values[i].first;
            b_hight = values[startIndex].second - values[i].second;

            length_of_line2 = std::sqrt(a_hight * a_hight + b_hight * b_hight);

            p = (length_of_line + length_of_line1 + length_of_line2) / 2;
            d = std::sqrt(p * (p - length_of_line) * (p - length_of_line1) * (p - length_of_line2)) * 2 / length_of_line;*/
            d = std::abs(b_hight * values[i].first - a_hight * values[i].second + values[endIndex].first * values[startIndex].second - values[endIndex].second * values[startIndex].first) / length_of_line;

            if(d > dMax)
            {
                index = i;
                dMax = d;
            }
        }

        if(dMax >= e)
        {
            index_of_value.push({index, endIndex});
            index_of_value.push({startIndex, index});
        }
        else
            values_for_return.push_back(startIndex);
    }

    values_for_return.push_back(values_count - 1);

    return values_for_return;
}
