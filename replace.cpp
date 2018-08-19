#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class ReplaceList
{
public:
    string strFrom;
    string strTo;
};

int main(int argc,char* argv[])
{
    ifstream fileList("/home/bill/.config/replacelist");

    //count the number of items in list
    int listlength=(std::count(std::istreambuf_iterator<char>(fileList),
                       std::istreambuf_iterator<char>(), '\n')+1)/2;
    fileList.clear();
    fileList.seekg(0,ios::beg);
    vector<ReplaceList> list(listlength);
    for(int i=0; i<listlength; i++)
    {
        getline(fileList,list[i].strFrom);
        getline(fileList,list[i].strTo);
    }

    ifstream inFile(argv[1]);
    ofstream outFile(strcat(argv[1],".new"));
    while( !inFile.eof())
    {
        string str;
        getline(inFile,str);
        std::size_t position;
        int find_position=0;
        for(int item=0; item<listlength; item++)
        {
            position = str.find(list[item].strFrom,find_position);
            if (position!=std::string::npos)
            {
                str.replace(position,list[item].strFrom.length(),list[item].strTo);
                //set find_position to avoid replacing already replaced strings
                find_position=position+list[item].strTo.length();
                item--;
            }
            else{
                find_position=0;
            }
        }
        outFile<<str<<endl;
    }
    inFile.close();
    outFile.close();
    return 0;
}
