#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
//#include <math.h>
#include <cmath>
#include <string>
#include <sstream>

std::vector<bool> duglas_peker(std::vector<std::pair<double, double>>, double);

int main(int argc, char *argv[])
{
    std::vector<std::pair<double, double>> values;// {{1,5},{2,3},{5,1},{6,4},{9,6},{11,4},{13,3},{14,2},{18,5}};
    std::vector<bool> values_of_return;
    int i = 0;
    std::string str;
    std::ifstream file("./Data.txt");
    double str1;
    std::stringstream ss;
    int a;

    while(getline(file, str))
    {
        a = str.find(',', 0);

        if(a>=0)
            str[a] = '.';

        str = str.substr(str.find('\t'));
        str1 = 0;
        str1 = atof(str.c_str());
        //ss << str;
        //ss >> str1;
        //ss.str(std::string());
        //std::cout << i << std::endl;
        //std::cout << str << ' ' << str1 << std::endl;

        values.push_back({i, str1});
        ++i;
    }

    file.close();

    /*for(i = 0; i < values.size(); ++i)
    {
        //std::cout << values[i].second << std::endl;
    }*/

    values_of_return = duglas_peker(values, 0.05);

    for(i = 0; i < values_of_return.size(); ++i)
    {
        if(values_of_return[i])
        {
            std::cout << values[i].first << ' ' << values[i].second << std::endl;
        }
        else
            values[i].second = 0;
    }

    std::ofstream file1("./data_qt_data1.txt");

    for(i = 0; i < values.size(); ++i)
    {
        file1 << values[i].second << std::endl;
    }

    file1.close();
    
    return 0;
}

std::vector<bool> duglas_peker(std::vector<std::pair<double, double>> values, double e)
{
    std::stack<std::pair<int, int>> index_of_value;
    std::vector<bool> values_for_return;

    for(int i = 0; i < values.size(); ++i)
    {
        values_for_return.push_back(true);
    }

    //index_of_value.push({values.begin(), values.end()});
    index_of_value.push({0, values.size()-1});
    while(!index_of_value.empty())
    {
        int startIndex = index_of_value.top().first;
        int endIndex = index_of_value.top().second;

        index_of_value.pop();

        double dMax = 0;
        int index = startIndex;
        double d = 0, length_of_line = 0, length_of_line1 = 0, length_of_line2 = 0, p = 0;

        for(int i = startIndex + 1; i < endIndex; ++i)
        {
            if(values_for_return[i])
            {
                length_of_line = std::sqrt(std::pow(values[startIndex].first - values[endIndex].first, 2) + std::pow(values[startIndex].second - values[endIndex].second, 2));
                length_of_line1 = std::sqrt(std::pow(values[i].first - values[endIndex].first, 2) + std::pow(values[i].second - values[endIndex].second, 2));
                length_of_line2 = std::sqrt(std::pow(values[startIndex].first - values[i].first, 2) + std::pow(values[startIndex].second - values[i].second, 2));
                p = (length_of_line + length_of_line1 + length_of_line2) / 2;
                d = std::sqrt(p * (p - length_of_line) * (p - length_of_line1) * (p - length_of_line2)) * 2 / length_of_line;
//std::cout << d << ' ' << length_of_line << ' ' << length_of_line1 << ' ' << length_of_line2 << ' ' << p << ' ' << i << std::endl;
                if(d > dMax)
                {
                    index = i;
                    dMax = d;
                }
            }
        }

        if(dMax >= e)
        {
            index_of_value.push({startIndex, index});
            index_of_value.push({index, endIndex});
        }
        else
        {
            for(int j = startIndex + 1; j < endIndex; ++j)
                values_for_return[j] = false;
        }
    }

    return values_for_return;
}