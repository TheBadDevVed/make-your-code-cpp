#include<iostream>
#include<ctype.h>
using namespace std;

struct arrays
{
    int intlength, floatlength, charlength;
    string chararray[100], intarray[100], floatarray[100];

    arrays()
    {
        intlength = floatlength = charlength = 0;
    }

    void addint(string n)
    {
        intarray[intlength] = n;
        intlength++;
    }

    void addfloat(string n)
    {
        floatarray[floatlength] = n;
        floatlength++;
    }

    void addchar(string n)
    {
        chararray[charlength] = n;
        charlength++;
    }
};

class queue
{
    public:

    int count,skipline;
    arrays variables;

    struct node
    {
        string statement;
        node *next;
    }*first,*last;
    
    queue()
    {
        count = skipline = 1;
        first= last = NULL;
    }

    void add(string str) 
    {
        node *temp = new node;
        temp->statement = str;
        temp->next = NULL;

        if(first==NULL)
           first= last =temp;  

        else
        {
            last->next = temp;        
            last=temp;
        }
        

    }

    void display()
    {
        cout<<"\n\n\nYOUR CODE:\n\n";

        cout<<"#include<stdio.h>\nint main()\n{\n";


            if(variables.intlength != 0)
            {
                cout<<"\n    int ";
                for(int i=0;i<variables.intlength;i++)
                    cout<<variables.intarray[i]<<",";

            cout<<"\b;\n";
            }
            

            if(variables.charlength != 0)
            {
                cout<<"\n    char ";
                for(int i=0;i<variables.charlength;i++)
                    cout<<variables.chararray[i]<<",";

            cout<<"\b;\n";
            }
            

            if(variables.floatlength != 0)
            {
                cout<<"\n    float ";
                for(int i=0;i<variables.floatlength;i++)
                    cout<<variables.floatarray[i]<<",";

            cout<<"\b;\n";
            }
            cout<<endl;

        while(first != NULL)
        {
            cout<<first->statement<<endl;
            first = first->next;
        }

        cout<<"}";
    }

    void printing()
    {
        if(skipline)
        add(""); // for cleaner code
        skipline = 0;

        string temp,main = "",tempvar,var = "";
        int flag = 0;

        cout<<"\n\nwhat u want to print\n";
        getline(cin,temp);
        
        for(int i=0;i<temp.length() - 1; i++)
        {
            if(temp[i]=='%' && (temp[i+1] == 'd' || temp[i+1] == 'f' || temp[i+1] == 'c'))
            {
                cout<<"enter variable\n";
                getline(cin,tempvar);
                var = ",";

                for(int j=0;j<tempvar.length();j++)
                {
                    if(isspace(tempvar[j]) && j != tempvar.length()-1)
                    {
                        var += ",";
                        continue;
                    }
                        
                    var += tempvar[j];
                }
                break;
            }
        }

        for(int i=0;i<count*4;i++)
        main += " ";

        main += "printf(\"" + temp + "\"" + var + ");";

        add(main);
    }

    void scanning()
    {
        string main = "",tempvar,var = ",&";
        skipline = 1;

        for(int i=0;i<count*4;i++)
        main += " ";

        main += "scanf(\"";

        cout<<"\n\nenter variable type and the variables\n";
        getline(cin,tempvar);
        
        for(int j=0;j<tempvar.length();j++)
        {
            if(tempvar[j] == 'i' && tempvar[j+1] == 'n'  && tempvar[j+2] == 't' )
            {
                j+=3;
                continue;
            }

            if(tempvar[j] == 'f' && tempvar[j+1] == 'l'  && tempvar[j+2] == 'o' && tempvar[j+3] == 'a'  && tempvar[j+4] == 't')
            {
                j+=5;
                continue;
            }

            if(tempvar[j] == 'c' && tempvar[j+1] == 'h'  && tempvar[j+2] == 'a' && tempvar[j+3] == 'r')
            {
                j+=4;
                continue;
            }

            if((isspace(tempvar[j]) && j != tempvar.length()-1) || tempvar[j] == ',')
            {
                var += ",&";
                continue;
            }
                
            var += tempvar[j];
        }


        //for differentiating char int and float
        int mode =0;
        tempvar += " ";

        for(int i=0;i<tempvar.length();i++)
        {
            string word="";
            for(int j=i;j<tempvar.length();j++)
            {
                if(isspace(tempvar[j]))
                {
                    i = j;
                    break;
                }
                word += tempvar[j];
            }

            if(word == "int")
            {
                mode =1;
                continue;
            }

            if(word == "char")
            {
                mode =2;
                continue;
            }

            if(word == "float")
            {
                mode =3;
                continue;
            }

            if(mode ==1)
            {
                main += "\%d";
            }

            if(mode ==2)
            {
                main += "\%c";
            }

            if(mode ==3)
            {
                main += "\%f";
            }
        }

        main += "\"" + var + ");";

        add(main);
    }

    void equations()
    {
        string temp,main;
        char ch;
        
        if(skipline)
        add("");
        skipline = 0;

        do
        {
            temp = "",main ="";
            ch='n';

            for(int i=0;i<count*4;i++)
                main += " ";
            
            cout<<"\n\nenter equation\n";
            getline(cin,temp);

            main += temp + ";";
            add(main);

            cout<<"continue (y/n)\n";
            cin>>ch;
            cin.ignore();
        }while(ch == 'y');
    }

    void conditions() 
    {
        add(""); //for cleaner code
        skipline = 0;

        string temp,allconditions="",main = "",temp2="";
        char ch = 'n';

        for(int i=0;i<count*4;i++)
            main += " ";

        main += "if(";

        cout<<"\n\nenter the condition\n";
        getline(cin,temp);

        allconditions += temp;
        

        main += allconditions + ")";

        add(main);

        for(int i=0;i<count*4;i++)
            temp2 += " ";
        temp2 += "{";

        add(temp2);
        temp2 = "";

        count++;
        menu("if(" + allconditions + ")");
        count--;

        for(int i=0;i<count*4;i++)
            temp2 += " ";
        temp2 += "}";
        add(temp2);

        cout<<"want else condition? (y/n)";
        cin>>ch;

        if(ch=='y')
        {
            main = temp2 = "";

            for(int i=0;i<count*4;i++)
                main += " ";

            main += "else";
            add(main);

            for(int i=0;i<count*4;i++)
                temp2 += " ";

            temp2 += "{";

            add(temp2);
            temp2 = "";

            count++;
            menu("else of (" + allconditions + ")");
            count--;

            for(int i=0;i<count*4;i++)
                temp2 += " ";
            temp2 += "}";
            add(temp2);
        }

        skipline =1;
    }

    void loops()
    {
        string main="",temp;

        add("");
        skipline = 0;

        for(int i=0;i<count*4;i++)
            main += " ";

        main += "for(";

        cout<<"\n\nfor loop condition\n";
        getline(cin,temp);

        main += temp + ")";

        add(main);

        main = "";

        for(int i=0;i<count*4;i++)
            main += " ";

        main +="{";

        add(main);

        count++;
        menu("for(" + temp + ")");
        count--;

        main = "";

        for(int i=0;i<count*4;i++)
            main += " ";

        main +="}";
        add(main);
    }

    void switchcase()
    {
        string enteredCase,vartype,temp="",main="",spaces ="";

        if(skipline)
            add("");

        skipline = 0;

        for(int i=0;i<count*4;i++)
        spaces += " ";

        cout<<"\n\nenter variable and variable type(int/char)\n";
        cin>>temp>>vartype;
        cin.ignore();

        main += spaces + "switch(" + temp +")";
        add(main);
        add(spaces + "{");
        main = spaces = "";

        count++;
        do
        {
            cout<<"enter case (to exit switch enter \"EXIT\")\n";
            cin>>enteredCase;

            main = spaces = "";
            for(int i=0;i<count*4;i++)
                spaces += " ";

            if(enteredCase =="EXIT")
            break;

            if(vartype == "char")
                enteredCase = "\'" + enteredCase + "\'";

            main += spaces + "case " + enteredCase +":";
                add(main);

                count++;
                menu("case " + enteredCase + ":");
                count--;

                add(spaces + "break;");
                add("");
            


        } while (enteredCase !="EXIT");

        count--;
        spaces ="";

        for(int i=0;i<count*4;i++)
        spaces += " ";
        add(spaces + "}");
        

        
    }

    void declaration()
    {
        string temp,main,word="";
        int mode=0;

        cout<<"\n\ndeclare the type and enter the variables\n";
        getline(cin,temp);

        temp += " ";

        for(int i=0; i<temp.length();i++)
        {
            word = "";
            for(int j=i;j<temp.length();j++)
            {
                if(isspace(temp[j]))
                {
                    i=j;
                    break;
                }
                word += temp[j];
            }

            if(word == "int")
            {
                mode=1;
                continue;
            }

            if(word == "float")
            {
                mode=2;
                continue;
            }

            if(word == "char")
            {
                mode=3;
                continue;
            }

            if(mode ==1)
            {
                variables.addint(word);
            }

            if(mode ==2)
            {
                variables.addfloat(word);
            }
            if(mode ==3)
            {
                variables.addchar(word);
            }
        }
    }

    void menu(string text = "(int main)")
    {
        int n;

        do{
        cout<<"\n\nselect     " << text;
        cout<<"\n0: declare variables\n1: printing\n2: scanning\n3: equation\n4: if conditions\n5: for loop\n6: switch case\n9: exit\nenter: ";
        cin>>n;
        cin.ignore();

        switch(n)
        {    
            case 0:
                declaration();
            break;

            case 1:
               printing();
            break;

            case 2:
                scanning();
            break;

            case 3:
                equations();
            break;

            case 4:
                conditions();
            break;

            case 5:
                loops();
            break;

            case 6:
                switchcase();
            break;

        }
        }while(n!=9);
    }

};

int main()
{
    class queue code;

    code.menu();
    code.display();
}