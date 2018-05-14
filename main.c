#define SIZE 50
#include<stdio.h>
#include<iostream>
#include <ctype.h>
#include<math.h>
#include<string.h>
#include<fstream>
using namespace std;

char s[SIZE];
int top = -1;



int count0( char * infx ,int i)           // Function To Check uniqueness of variables in an expression
{
 for (int p=0;p<i;p++)
 {
  if(infx[i]==infx[p])
  return 0;

 }

 return 1;
}
int varvalcal(char * infx,char * vararray)        // Function counts the number of unique variables and assigns them as elements of array vararray
{ int i,count=0;
 for(i=0;infx[i]!='\0';i++)
 {
  if((((infx[i]>='A'&& infx[i]<='Z')||(infx[i]>='a'&& infx[i]<='z'))&&(count0(infx,i))))
  {
   vararray[count]=infx[i];
   count++;
  }
 }
 vararray[count]='\0';
 return count;
}
char var[50][50];
char fx[20];
char infx[50], pofx[50],vararray[10];
char meaning[20][30];
char fxmean[20];

void push(char elem) {             // Push int  stack function
 s[++top] = elem;
}

char pop() {               // Pop from stack
 if(top!=-1)
 {
  char temp;
  temp=s[top];
  top--; return (temp);
 }
}

int pr(char elem)               // function that returns the priority of the operators
{
  switch (elem) {
   case '#':
      return 0;
   case '(':
      return 1;
   case '+':
      return 2;
   case '*':
      return 3;
    case '\'':
      return 4;
 }
}
void meanset(char * vararray)
{
 for(int i=0;vararray[i]!='\0';i++)
 {
  fflush(stdin);
  cout<<"\nEnter the meaning of "<<vararray[i]<<":  ";
  gets(meaning[i]);

 } cout<<"\nEnter meaning of F(x): ";
 gets(fxmean);
 cout<<endl;

}
void con(char * infx, char * pofx )         // Function  that converts infix to postfix
{
 char tempinfx[50];

 char ch,c,elem;
 int i = 0, k = 0;
  printf("\n\nEnter your boolean Expression to be evaluated ( in  terms of variables , Os and 1s ) :    ");
  scanf("%s", infx);
  push('#');
  strcpy(tempinfx,infx);
 while ((ch = infx[i++]) != '\0')
 {
    if (ch == '(')
      push(ch);
    else if (isalnum(ch))
      {
       pofx[k] = ch;
       k++;
      }
    else if (ch == ')')
  {
      while (s[top] != '(')
       { pofx[k] = pop();
        k++;
       }

      elem = pop();
     }
  else
  {
      while (pr(s[top]) >= pr(ch))
        {
      pofx[k] = pop();
         k++;
     }
   push(ch);
  }
  }
 while (s[top] != '#')
    pofx[k++] = pop();
  pofx[k] = '\0';
  strcpy(infx,tempinfx);
}

int eval(char * pofx,int variables,char * vararray)       // Evaluates the expression pofx and stores results in Fx array
{
 char ch;
 int c,l,j,a,b,i=0,k=0;
 char temparray[50],op1,op2;
 for(c=0;c<pow(2,variables);c++) {
  strcpy(temparray,pofx);
  for(a=0;a<variables;a++)
 {
  for(b=0;temparray[b]!='\0';b++)
  {
   if(vararray[a]==temparray[b])
   {
    temparray[b]=var[a][c];
   }
  }
 }

 for(l=1;temparray[l]!='\0';l++)
 {
  if(temparray[l]=='\'')
   if(temparray[l-1]=='0')
    temparray[l-1]='1';
   else
    temparray[l-1]='0';
 }
 i=0;
 while( (ch=temparray[i++]) != '\0')
  {
   if(ch=='0'||ch=='1')
  { push(ch);
  }
  else if(ch=='\'')
   continue;
   else
    {
      op2=pop();
      op1=pop();
       switch(ch)
       {
        case '+':
        if(op1=='1' || op2=='1' ) push('1');
        else push('0');
        break;
        case '*':
        if( op1=='0' || op2=='0' ) push('0');
        else push('1');
        break;
     case '\'':
      break;

       }
    }
  }
  fx[c] =  s[top];
 }
}


int *  ttable(int varc)               // initialises ttable array
{
     int t=pow(2,varc);
     char bit='1';               // Number of packets in the ith column is 2^i+1
   for(int j=0;j<pow(2,varc);j++)           // Width of a packet in the ith column is (2^n)/(2^(i+1))  = 2^(n-i-1)
     for(int i=0;i<varc;i++)
     {
             for (int j=0;j<t;j++)
             {
                 if(j%(int)pow(2,varc-i-1)==0)
                 {
                     bit=(bit=='1'?bit='0':bit='1');
                 }
                 var[i][j]=bit;
             }
     }
}
int *  ttabledisplay(int varc)            // Displays the truthtable
{
     int t=pow(2,varc);              // Number of packets in the ith column is 2^i+1
   for(int j=0;j<pow(2,varc);j++)           // Width of a packet in the ith column is (2^n)/(2^(i+1))  = 2^(n-i-1)
     {
              for (int i=0;i<varc;i++)
              {
                       cout<<var[i][j]<<"\t";
              }
     cout<<"\t"<<fx[j];   cout<<endl;
     }
    cout<<endl<<endl;
}

int pos(char item)
{
 for(int t=0;t<10;t++)
 {
  if(item==vararray[t])
  return t;
 }
}

void statement()
{
 cout<<fxmean<<" if ";
 for(int p=0;infx[p]!='\0';p++)
 {
  if(infx[p+1]=='\'')
  {
   cout<<" does not "<<meaning[pos(infx[p])]<<" ";
   p=p+1;
  }
  else if (infx[p]=='*')
  cout<<" and ";
  else if (infx[p]=='+')
  cout<<" or ";
  else
  cout<<meaning[pos(infx[p])]<<" ";

 }

 cout<<endl<<endl;

}


void graphdisplay(int varc,char * vararray)        // Displays the simulation graph
{
 int cycles,time;
 cout<<"Enter Clock Time for Simuation Graph (in multiples of 50 ms)  :  " ;
 cin>> time;
 cout<<"Enter the number of cycles :  ";
 cin>>cycles;

 int t=pow(2,varc);
    cout<<endl;
 for (int i=0;i<varc;i++)
    {

    cout<<vararray[i]<<"\t";

 for(int t=0;t<cycles;t++)
 {

    for(int j=0;j<pow(2,varc);j++)  {
                       for(int o=0;o<time/50;o++)
                        {
                         if(var[i][j]=='1')
                          printf("-");
       else
            printf("_");
                        }
            }
      }
 cout<<endl<<endl;
 }
    cout<<"Fx\t";
 for(int t=0;t<cycles;t++)
 {

    for(int j=0;j<pow(2,varc);j++)
    {
   for(int n=0;n<time/50;n++)
     {
          if(fx[j]=='1')
           printf("-");
    else
        printf("_");
     }
    }
 }

 cout<<"\n\n"<<"Time"<<"\t";
 for(int d=0;d<=time*cycles*pow(2,varc);d=d+time*cycles)
 {
  cout<<d<<"\t";
 }

 ofstream fout;
 fout.open("Graph.txt",ios::in);

 for (int i=0;i<varc;i++)
    {

    fout<<vararray[i]<<"\t";

 for(int t=0;t<cycles;t++)
 {

    for(int j=0;j<pow(2,varc);j++)
    {
                       for(int o=0;o<time/50;o++)
                        {
                         if(var[i][j]=='1')
                          fout<<("-");
       else
            fout<<("_");
                        }

            }
      }
 fout<<endl<<endl; }
    fout<<"Fx\t";
 for(int t=0;t<cycles;t++)
 {

    for(int j=0;j<pow(2,varc);j++)
    {
   for(int n=0;n<time/50;n++)
     {
          if(fx[j]=='1')
           fout<<("-");
    else
        fout<<("_");
     }
    }
 }
 fout.close();


 fout<<"\n\n"<<"Time"<<"\t";
 for(int d=0;d<=time*cycles*pow(2,varc);d=d+time*cycles)
 {
  fout<<d<<"\t";

 }

}
int main()                    // Main fruntion
{
con(infx, pofx);                // convert infix to postfix expression
int variables=varvalcal(infx,vararray);           // count number of variables in the expression
printf("\n\nGiven Infix Expn: %s  Postfix Expn: %s\n\n", infx, pofx);
ttable(variables);                // Initialises the truthtable with values
eval(pofx,variables,vararray);             // evaluates the logig expression

meanset(vararray);
for(int i=0;i<=variables;i++)
{
 printf("%c\t",vararray[i]);
}
printf("Fx");



printf("\n");

ttabledisplay(variables);
cout<<endl;
statement();              // display truthtable
cout<<endl;
graphdisplay(variables,vararray);            // display simulation graph
}
