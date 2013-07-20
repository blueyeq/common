#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

int main(int argc, char **argv){

    fstream fin(argv[1], ios::in);
    fstream fout1(argv[2], ios::out);
    fstream fout2(argv[3], ios::out);
    
    char line[9096];
    int lineCnt(0);
    while(fin.getline(line, 2096)){
        istringstream in(line);
        int len = strlen(line);
        if(lineCnt++ % 100 != 0)  continue;
//        cout<<line<<endl;
        for(int i = len - 1; i >= 0; --i){
            if(line[i]  == '[' && line[i - 1] == '\t'){
                line[i] = line[len - 1] = 0;
                //cout<<line<<endl<<(line + i + 1)<<endl;
                fout1<<line<<endl;
                fout2<<(line + i + 1)<<endl;
                break;
            }
        }
       
    }
    fin.close();
    fout1.close();
    fout2.close();

    return 0;
}
