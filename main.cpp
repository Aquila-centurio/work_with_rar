
#include <iostream>
#include <fstream>

using namespace std;



struct TITLE
{
    char size[4];
    char unusable[15];
    char name[2];
    char unsable2[4];
};

struct RAR_FILE
{
    char un_use[2];
    char type;
    char un_use2[2];
    unsigned char header_size[2];
};

void read_header(ifstream &file, RAR_FILE* Title,TITLE* Head_type, int current_loc);
void printer(int lenght_of_name,ifstream &file);


int main(){
    char filePath[] = {"/home/aquila/Учёба/CLionProjects/arc/Example.rar"};
    RAR_FILE* Title = new RAR_FILE;
    TITLE* Head_type = new TITLE;

    ifstream file;
    file.open(filePath, ios::binary);

    char symb;

    if(file.is_open()) {

        file.seekg(0, ios::end);
        int length = file.tellg(), current_loc = 0, num = 0;
        file.seekg(0, ios::beg);
        read_header(file, Title, Head_type, current_loc);
        file.close();
    }


    return 0;
}


void read_header(ifstream &file, RAR_FILE* Title,TITLE* Head_type, int current_loc )
{



        for(int i = 0; i<3;i++)
        {
            file.seekg(current_loc, ios::beg);
            file.read((char*)Title, 7);

            int len=int((*Title).header_size[0]+(*Title).header_size[1]);

            if ((*Title).type==0x74)
            {
                int position = current_loc + 7;
                file.seekg(position);
                file.read((char*)Head_type, 25);
                int compress_size=int(((*Head_type).size[0])+((*Head_type).size[1])+((*Head_type).size[2])+((*Head_type).size[3]));
                int lenght_of_name = int((*Head_type).name[0]+(*Head_type).name[1]);
                current_loc=current_loc+len+compress_size;
                printer(lenght_of_name,file);

            }
            else {
                current_loc = current_loc + len;
                i--;
            }


        };
}

void printer(int lenght_of_name,ifstream &file){
    for (int i=0; i<lenght_of_name; i++)
    {
        char a;
        file.read(&a,1);
        cout << a;
    };
    cout << endl;
}
