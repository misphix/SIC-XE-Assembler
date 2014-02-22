void pass2()
{ 
    int size;
    size=line.back;
    string loclabel;
    int loclabel1;
    int locpara;
    int opcode;
    string a="";
    string b="@#,x";
    for(int i=0;i<=size;i++)
    {  
        for(int counter=0;counter<(line[i].parameter).length;counter++)
        {
            if(line[i].parameter[counter]==',')
            x=1;
            else if{line[i].parameter[counter]=='@')
            n=1;
            else if{line[i].parameter[counter]=='#')
            i=1;
            
        }
        a=line[i].parameter
        split(a,a,b);
        for(int j=0;j<=size;j++)
        {
            if(line[i].parameter==line[j].label)
               loclabel=line[j].loc;
        }
        
        loclabel1=hex_to_ten(loclabel);/*記得打*/ 
        locpara=hex_to_ten(line[i+1].loc);
        newloc=loclabel1-locpara;
        
        if(n==1)
        {
           opcode=(hex_to_ten(line[i].op))+2;
        }
        if(i==1)
        {
           opcode=(hex_to_ten(line[i].op))+1;
        }
        
        if(newloc<2048)
        {
           p=1;
        }
        else if(newloc>2048)
        {
           b=1;
           for(int j=0;j<=size;j++)
           {
               if(line[j].op="BASE")
               {
                  for(int k=0;k<=size;k++)
                  { 
                     if(line[k].label==line[j].parameter)
                        loclabel=line[k].loc;
                  }
                }
           }
           loclabel1=hex_to_ten(loclabel);/*記得打*/ 
           locpara=hex_to_ten(line[i+1].loc);
        
           newloc=loclabel1-locpara;
        }
        
        if(e==1)
        {
           newloc=loclabel;
        }
        
        
        if(e==1)
        {
           line[i].op=ten_to_hex(opcode);
           line[i].loc=ten_to_hex(newloc);
           line[i].obcode=line[i].op+"10"+line[i].loc;
        }
        else if(e==0)
        {
            if(b==0&&p==1&&x==0)
            {
              line[i].op=ten_to_hex(opcode);
              line[i].loc=ten_to_hex(newloc);
              line[i].obcode=line[i].op+"2"+line[i].loc;
            }
            else if(b==0&&p==1&&x==1)
            {
                    line[i].op=ten_to_hex(opcode);
                    line[i].loc=ten_to_hex(newloc);
                    line[i].obcode=line[i].op+"A"+line[i].loc;
            }
            else if(b==1&&p==1&&x==1)
            {      
                   line[i].op=ten_to_hex(opcode);
                   line[i].loc=ten_to_hex(newloc);
                   line[i].obcode=line[i].op+"E"+line[i].loc;
            }
            else if(b==1&&p==1&&x==0)
            {    
                   line[i].op=ten_to_hex(opcode);
                   line[i].loc=ten_to_hex(newloc);
                   line[i].obcode=line[i].op+"6"+line[i].loc;
            }
            else if(b==1&&p==0&&x==1)
            {      
                   line[i].op=ten_to_hex(opcode);
                   line[i].loc=ten_to_hex(newloc);
                   line[i].obcode=line[i].op+"C"+line[i].loc;
            }
            else if(b==1&&p==0&&x==0)
            {    
                   line[i].op=ten_to_hex(opcode);
                   line[i].loc=ten_to_hex(newloc);
                   line[i].obcode=line[i].op+"4"+line[i].loc;
            }
            
        }

                 
     }
}
                 
                 
