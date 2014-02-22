#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <fstream>

using namespace std;

typedef struct{
    string op,disp_address,obcode,loc,label,parameter;
    string n,i,x,b,p,e;
}instruction;

vector<instruction> line;

string optab(string);
bool isop(string);
int loc_leng(string);
int loc_count(int,string);
void pass1();
void pass2();
string ten_to_hex(int);
string hex(int);
string hex_to_binary(string);
string binary_to_hex(string);
int hex_to_ten(string);
void printob();

int main()
{
    pass1();
    pass2();
    printob();
    system("pause");
    return 0;
}

string optab(string mnem)
{
    map<string,string> r;
    r["ADD"]="18";r["ADDF"]="58";r["ADDR"]="90";r["AND"]="40";r["CLEAR"]="B4";
    r["COMP"]="28";r["COMPF"]="88";r["COMPR"]="A0";r["DIV"]="24";r["DIVF"]="64";
    r["DIVR"]="9C";r["FIX"]="C4";r["FLOAT"]="C0";r["HIO"]="F4";r["J"]="3C";
    r["JEQ"]="30";r["JGT"]="34";r["JLT"]="38";r["JSUB"]="48";r["LDA"]="00";
    r["LDB"]="68";r["LDCH"]="50";r["LDF"]="70";r["LDL"]="08";r["LDS"]="6C";
    r["LDT"]="74";r["LDX"]="04";r["LPS"]="D0";r["MUL"]="20";r["MULF"]="60";
    r["MULR"]="98";r["NORM"]="C8";r["OR"]="44";r["RD"]="D8";r["RMO"]="AC";
    r["RSUB"]="4C";r["SHIFTL"]="A4";r["SHIFTR"]="A8";r["SIO"]="F0";r["SSK"]="EC";
    r["STA"]="0C";r["STB"]="78";r["STCH"]="54";r["STF"]="80";r["STI"]="D4";
    r["STL"]="14";r["STS"]="7C";r["STSW"]="E8";r["STT"]="84";r["STX"]="10";
    r["SUB"]="1C";r["SUBF"]="5C";r["SUBR"]="94";r["SVC"]="B0";r["TD"]="E0";
    r["TIO"]="F8";r["TIX"]="2C";r["TIXR"]="B8";r["WD"]="DC";
    string opcode;

    opcode=r[mnem];
    return opcode;
}

bool isop(string lib)
{
    map<string,string> r;
    r["ADD"]="18";r["ADDF"]="58";r["ADDR"]="90";r["AND"]="40";r["CLEAR"]="B4";
    r["COMP"]="28";r["COMPF"]="88";r["COMPR"]="A0";r["DIV"]="24";r["DIVF"]="64";
    r["DIVR"]="9C";r["FIX"]="C4";r["FLOAT"]="C0";r["HIO"]="F4";r["J"]="3C";
    r["JEQ"]="30";r["JGT"]="34";r["JLT"]="38";r["JSUB"]="48";r["LDA"]="00";
    r["LDB"]="68";r["LDCH"]="50";r["LDF"]="70";r["LDL"]="08";r["LDS"]="6C";
    r["LDT"]="74";r["LDX"]="04";r["LPS"]="D0";r["MUL"]="20";r["MULF"]="60";
    r["MULR"]="98";r["NORM"]="C8";r["OR"]="44";r["RD"]="D8";r["RMO"]="AC";
    r["RSUB"]="4C";r["SHIFTL"]="A4";r["SHIFTR"]="A8";r["SIO"]="F0";r["SSK"]="EC";
    r["STA"]="0C";r["STB"]="78";r["STCH"]="54";r["STF"]="80";r["STI"]="D4";
    r["STL"]="14";r["STS"]="7C";r["STSW"]="E8";r["STT"]="84";r["STX"]="10";
    r["SUB"]="1C";r["SUBF"]="5C";r["SUBR"]="94";r["SVC"]="B0";r["TD"]="E0";
    r["TIO"]="F8";r["TIX"]="2C";r["TIXR"]="B8";r["WD"]="DC";
    if(r.find(lib)==r.end())
        return false;
    return true;
}

int loc_leng(string opcode)
{
    map<string,int> l;
    l["18"]=3;l["58"]=3;l["90"]=2;l["40"]=3;l["B4"]=2;
    l["28"]=3;l["88"]=3;l["A0"]=2;l["24"]=3;l["64"]=3;
    l["9C"]=2;l["C4"]=1;l["C0"]=1;l["F4"]=1;l["3C"]=3;
    l["30"]=3;l["34"]=3;l["38"]=3;l["48"]=3;l["00"]=3;
    l["68"]=3;l["50"]=3;l["70"]=3;l["08"]=3;l["6C"]=3;
    l["74"]=3;l["04"]=3;l["D0"]=3;l["20"]=3;l["60"]=3;
    l["98"]=2;l["C8"]=1;l["44"]=3;l["D8"]=3;l["AC"]=2;
    l["4C"]=3;l["A4"]=2;l["A8"]=2;l["F0"]=1;l["EC"]=3;
    l["0C"]=3;l["78"]=3;l["54"]=3;l["80"]=3;l["D4"]=3;
    l["14"]=3;l["7C"]=3;l["E8"]=3;l["84"]=3;l["10"]=3;
    l["1C"]=3;l["5C"]=3;l["94"]=2;l["B0"]=2;l["E0"]=3;
    l["F8"]=1;l["2C"]=3;l["B8"]=2;l["DC"]=3;
    int leng;

    leng=l[opcode];
    return leng;

}

int loc_count(int pc,string op)
{
    int loc;

    loc=pc+loc_leng(op);
    return loc;
}

void pass1()
{
    ifstream file;
    instruction temp;
    string lip;
    int loc_num=0,end_count=0;
    file.open("test.txt",ios::in);

    file>>lip;
    while(end_count!=1)
    {
        if(lip=="END")//if read is END read next parameter and stop pass one
        {
            temp.op="END";
            file>>lip;
            temp.parameter=lip;
            end_count++;
            line.push_back(temp);
        }
        else if(lip=="BASE")//if instruction is BASE
        {
            temp.op="BASE";
            file>>lip;
            temp.parameter=lip;
            line.push_back(temp);
        }
        else if(isop(lip)||lip[0]=='+')//if is format 4 or is op
        {
            if(lip[0]=='+')//check if format 4 and cut first char '+'
            {
                lip=lip.substr(0,lip.length()-1);//store op and parameter
                temp.op=optab(lip);
                loc_num+=4;
                temp.loc=ten_to_hex(loc_num);
                file>>lip;
                temp.parameter=lip;
                temp.e="1";
            }
            else//is op but not format 4
            {
                temp.op=optab(lip);//store op
                if(loc_leng(temp.op)!=1)//if is not format 1
                {
                    loc_num=loc_count(loc_num,temp.op);
                    temp.loc=ten_to_hex(loc_num);//calculate loc
                    if(lip!="RSUB")//if op is RSUB, there is no parameter
                    {
                        file>>lip;
                        temp.parameter=lip;
                    }
                }
                else//if is format 1
                {
                    loc_num+=1;//loc +=1
                    temp.loc=ten_to_hex(loc_num);
                }
                line.push_back(temp);//store in line
            }
        }
        else//if lip is label
        {
            temp.label=lip;
            file>>lip;
            if(lip=="START")//if lip is START
            {
                temp.op="START";
                file>>lip;
                temp.loc=lip;
                temp.parameter=lip;
                line.push_back(temp);//store in line
            }
            else if(lip=="BYTE"||lip=="RESW"||lip=="RESB")//instruction is byte resw resb
            {
                temp.op=lip;
                if(lip=="BYTE")
                {
                    loc_num+=1;
                    temp.loc=ten_to_hex(loc_num);
                    file>>lip;
                    temp.parameter=lip;
                }
                else if(lip=="RESW")
                {
                    loc_num+=3;
                    temp.loc=ten_to_hex(loc_num);
                    file>>lip;
                    temp.parameter=lip;
                }
                if(lip=="RESB")
                {
                    int x;
                    file>>x;
                    loc_num+=x;
                    temp.loc=ten_to_hex(loc_num);
                }
            }
            else
            {
                if(lip[0]=='+')//if is format 4
                {
                    lip=lip.substr(0,lip.length()-1);//cut the char '+'
                    temp.op=optab(lip);
                    loc_num+=4;
                    temp.loc=ten_to_hex(loc_num);
                    file>>lip;
                    temp.parameter=lip;
                    temp.e="1";
                }
                else
                {
                    temp.op=optab(lip);
                    if(loc_leng(temp.op)!=1)//if is not format 1
                    {
                        loc_num=loc_count(loc_num,temp.op);
                        temp.loc=ten_to_hex(loc_num);
                        if(lip!="RSUB")//ignore the parameter if lip is RSUB
                        {
                            file>>lip;
                            temp.parameter=lip;
                        }
                    }
                    else//if is format 1 calculate loc and ignore
                    {
                        loc_num+=1;
                        temp.loc=ten_to_hex(loc_num);
                    }
                }
                line.push_back(temp);//store in line
            }
        }
    }
    file.close();
}

string hex_to_binary(const string hexnum)
{
    string binnum="";

    for(int i=0;hexnum[i]!='\0';i++)
    {
        switch(hexnum[i])
        {
            case '0':
                binnum+="0000";
                break;
            case '1':
                binnum+="0001";
                break;
            case '2':
                binnum+="0010";
                break;
            case '3':
                binnum+="0011";
                break;
            case '4':
                binnum+="0100";
                break;
            case '5':
                binnum+="0101";
                break;
            case '6':
                binnum+="0110";
                break;
            case '7':
                binnum+="0111";
                break;
            case '8':
                binnum+="1000";
                break;
            case '9':
                binnum+="1001";
                break;
            case 'A':
                binnum+="1010";
                break;
            case 'B':
                binnum+="1011";
                break;
            case 'C':
                binnum+="1100";
                break;
            case 'D':
                binnum+="1101";
                break;
            case 'E':
                binnum+="1110";
                break;
            case 'F':
                binnum+="1111";
                break;
        }
    }
    return binnum;
}

string binary_to_hex(const string binnum)
{
    string hexnum="",temp="",fixbinnum=binnum;

    for(int i=0;i<(binnum.length()%4);i++)//fill 0 before binary number into 4n
        fixbinnum="0"+fixbinnum;
    for(int j=0;j+3<fixbinnum.length()-1;j+=4)
    {
        temp=fixbinnum[j]+fixbinnum[j+1]+fixbinnum[j+2]+fixbinnum[j+3];
        if(temp=="0000")
            hexnum+="0";
        else if(temp=="0001")
            hexnum+="1";
        else if(temp=="0010")
            hexnum+="2";
        else if(temp=="0011")
            hexnum+="3";
        else if(temp=="0100")
            hexnum+="4";
        else if(temp=="0101")
            hexnum+="5";
        else if(temp=="0110")
            hexnum+="6";
        else if(temp=="0111")
            hexnum+="7";
        else if(temp=="1000")
            hexnum+="8";
        else if(temp=="1001")
            hexnum+="9";
        else if(temp=="1010")
            hexnum+="A";
        else if(temp=="1011")
            hexnum+="B";
        else if(temp=="1100")
            hexnum+="C";
        else if(temp=="1101")
            hexnum+="D";
        else if(temp=="1110")
            hexnum+="E";
        else if(temp=="1111")
            hexnum+="F";
    }
}

string ten_to_hex(int number)
{
    string a[100];
    int remainder;
    int counter=0;
    string hex1="";
    if(15>number)
    {
       hex1=hex(number);
    }
    else
    {
        while(number>15)
        {
              number=number/16;
              remainder=number%16;
              a[counter]=hex(remainder);
               counter++;
        }
        for(int i=counter;i>=0;i--)
        {
             hex1=hex1+a[counter];
        }
    }
    return hex1;
}

string hex(int remainder1)
{
     string char1;
     if(remainder1==0)
     {
       char1="0";
       return char1;
     }
     else if(remainder1==1)
     {
       char1="1";
       return char1;
     }
     else if(remainder1==2)
     {
       char1="2";
       return char1;
     }
     else if(remainder1==3)
     {
       char1="3";
       return char1;
     }
     else if(remainder1==4)
     {
       char1="4";
       return char1;
     }
     else if(remainder1==5)
     {
       char1="5";
       return char1;
     }
     else if(remainder1==6)
     {
       char1="6";
       return char1;
     }
     else if(remainder1==7)
     {
       char1="7";
       return char1;
     }
     else if(remainder1==8)
     {
       char1="8";
       return char1;
     }
     else if(remainder1==9)
     {
       char1="9";
       return char1;
     }
     else if(remainder1==10)
     {
       char1="A";
       return char1;
     }
     else if(remainder1==11)
     {
       char1="B";
       return char1;
     }
     else if(remainder1==12)
     {
        char1="C";
        return char1;
     }
     else if(remainder1==13)
     {
        char1="D";
        return char1;
     }
     else if(remainder1==14)
     {
        char1="E";
        return char1;
     }
     else if(remainder1==15)
     {
        char1="F";
        return char1;
     }
}

int hex_to_ten(string hexnum)
{
    int digit=hexnum.length(),tennum=0;

    for(int i=0;digit>0;digit--,i++)
    {
        switch(hexnum[i])
        {

            case '1':
                tennum+=1*pow(16.0,digit-1);
                break;
            case '2':
                tennum+=2*pow(16.0,digit-1);
                break;
            case '3':
                tennum+=3*pow(16.0,digit-1);
                break;
            case '4':
                tennum+=4*pow(16.0,digit-1);
                break;
            case '5':
                tennum+=5*pow(16.0,digit-1);
                break;
            case '6':
                tennum+=6*pow(16.0,digit-1);
                break;
            case '7':
                tennum+=7*pow(16.0,digit-1);
                break;
            case '8':
                tennum+=8*pow(16.0,digit-1);
                break;
            case '9':
                tennum+=9*pow(16.0,digit-1);
                break;
            case 'A':
                tennum+=10*pow(16.0,digit-1);
                break;
            case 'B':
                tennum+=11*pow(16.0,digit-1);
                break;
            case 'C':
                tennum+=12*pow(16.0,digit-1);
                break;
            case 'D':
                tennum+=13*pow(16.0,digit-1);
                break;
            case 'E':
                tennum+=14*pow(16.0,digit-1);
                break;
            case 'F':
                tennum+=15*pow(16.0,digit-1);
                break;
        }
    }

    return tennum;
}

void pass2()
{
    string loclabel;
    int loclabel1;
    int locpara;
    int opcode;
    int x;
    int p;
    int b;
    int n;
    int i;
    int newloc;

    for(int i1=0;i1<=line.size();i1++)
    {
        for(int counter=0;counter<((line[i1].parameter).size());counter++)
        {
            if(line[i1].parameter[counter]==',')
            x=1;
            else if(line[i1].parameter[counter]=='@')
            n=1;
            else if(line[i1].parameter[counter]=='#')
            i=1;

        }
        int z=line[i1].parameter.find('@#,x');
        line[i1].parameter=line[i1].parameter.substr(0,z);
        for(int j=0;j<=line.size();j++)
        {
            if(line[i1].parameter==line[j].label)
               loclabel=line[j].loc;
        }

        loclabel1=hex_to_ten(loclabel);/*記得打*/
        locpara=hex_to_ten(line[i1+1].loc);
        newloc=loclabel1-locpara;

        if(n==1)
        {
           opcode=(hex_to_ten(line[i1].op))+2;
        }
        if(i==1)
        {
           opcode=(hex_to_ten(line[i1].op))+1;
        }

        if(newloc<2048)
        {
           p=1;
        }
        else if(newloc>2048)
        {
           b=1;
           for(int j=0;j<=line.size();j++)
           {
               if(line[j].op=="BASE")
               {
                  for(int k=0;k<=line.size();k++)
                  {
                     if(line[k].label==line[j].parameter)
                        loclabel=line[k].loc;
                  }
                }
           }
           loclabel1=hex_to_ten(loclabel);/*記得打*/
           locpara=hex_to_ten(line[i1+1].loc);

           newloc=loclabel1-locpara;
        }

        if(line[i1].e=="1")
        {
           newloc=hex_to_ten(loclabel);
        }


        if(line[i1].e=="1")
        {
           line[i1].op=ten_to_hex(opcode);
           line[i1].loc=ten_to_hex(newloc);
           line[i1].obcode=line[i1].op+"10"+line[i1].loc;
        }
        else if(line[i1].e=="0")
        {
            if(b==0&&p==1&&x==0)
            {
              line[i1].op=ten_to_hex(opcode);
              line[i1].loc=ten_to_hex(newloc);
              line[i1].obcode=line[i1].op+"2"+line[i1].loc;
            }
            else if(b==0&&p==1&&x==1)
            {
                    line[i1].op=ten_to_hex(opcode);
                    line[i1].loc=ten_to_hex(newloc);
                    line[i1].obcode=line[i1].op+"A"+line[i1].loc;
            }
            else if(b==1&&p==1&&x==1)
            {
                   line[i1].op=ten_to_hex(opcode);
                   line[i1].loc=ten_to_hex(newloc);
                   line[i1].obcode=line[i1].op+"E"+line[i1].loc;
            }
            else if(b==1&&p==1&&x==0)
            {
                   line[i1].op=ten_to_hex(opcode);
                   line[i1].loc=ten_to_hex(newloc);
                   line[i1].obcode=line[i1].op+"6"+line[i1].loc;
            }
            else if(b==1&&p==0&&x==1)
            {
                   line[i1].op=ten_to_hex(opcode);
                   line[i1].loc=ten_to_hex(newloc);
                   line[i1].obcode=line[i1].op+"C"+line[i1].loc;
            }
            else if(b==1&&p==0&&x==0)
            {
                   line[i1].op=ten_to_hex(opcode);
                   line[i1].loc=ten_to_hex(newloc);
                   line[i1].obcode=line[i1].op+"4"+line[i1].loc;
            }

        }


     }

}

void printob()
{
    for(int i=0;i<line.size();i++)
    {
        if(line[i].obcode=="")
            cout<<endl;
        else
            cout<<line[i].obcode<<endl;
    }
}
