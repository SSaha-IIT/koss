#include<iostream>
#include<string.h>
#include<fstream>
#include<ncurses.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctime>
#include<stdio.h>

using namespace std;

void page1();

class user
{  
  char fname[20];
  int tickets[5];  
  char pass[20];
  
  public:
  
  char name[20];
  user()
   {
    tickets[0]=0;
    tickets[1]=0;
    tickets[2]=0;
    tickets[3]=0;
    tickets[4]=0;
   };
  void sign();
  void profile();
  void reserve(user);
  void retrieve(char*,char*);
  user ilog();

}temp;

void page2(user);

void user::retrieve(char a[20],char b[20])
{
 strcpy(a,name);
 strcpy(b,pass);
}

class train
{ 
  public:
 
  int no;
  char name[20];
  void status(int);
  struct time
   {
     int hours;
     int minutes;
     int display()
      {
        cout<<hours<<":"<<minutes<<"\n";
      }
   }t;

};

void train::status(int n)                 //train status
{
  train temp2;
  fstream file;
  file.open("trains.txt",ios::in);
  time_t timec;
  struct tm *ltime; 
  while(!file.eof())
   {
     file.read((char*)&temp2,sizeof(temp2));
     if(temp2.no==n)
      { 
        int Hour=5,Min=30; 
        /*time(&timec);                   
        ltime = localtime(&timec); 
        int Hour = ltime->tm_hour;
        int Min  = ltime->tm_min;*/
        if((Hour*60 + Min)>=(temp2.t.hours*60 + temp2.t.minutes))
         cout<<"Train is arriving";
        else
         cout<<"Train has departed";
      }
    }
  file.close();
}

void user::sign()                       //sign up
{ 
  user bot,send;
  char b[20];
  fstream file;
  file.open("/home/saptarshi/GitHub/KOSS/users.txt",ios::in|ios::app);
  system("clear");
  file.seekg(0,ios::beg);
  int c=0;
  cout<<"Enter full name:";
  cin>>send.fname;
  while(c!=1)
   { 
     cout<<"enter username"<<endl;
     cin>>send.name; 
     while(!file.eof())
      { 
       file.read((char*)&bot,sizeof(bot));
       if(strcmp(bot.name,send.name)==1)
        {
         cout<<"user already exists";
         c=0;
        }
       else
         c=1;
      }
   }
  file.close();
  file.open("/home/saptarshi/GitHub/KOSS/users.txt",ios::out|ios::app);
  c=0;
  while(c!=1)
  {
   cout<<"Enter password:";
   cin>>send.pass;
   cout<<"\nRe-enter password:";
   cin>>b;
   if(strcmp(send.pass,b)==0)
     {
       cout<<"Sign up successful\n";
       sleep(1.2);
       c=1;
     }
   else
    cout<<"passwords do not match"<<endl;
   sleep(1.2);
  }
 file.write((char*)&send,sizeof(send));
 file.close();
 page2(send);
}

user ilog()                                    //login
{ 
  user bot;
 	fstream file;
  system("clear");
  char uname[20];
  char pass[20];
  file.open("/home/saptarshi/GitHub/KOSS/users.txt",ios::in|ios::app);
  file.seekg(0,ios::beg);
  int c=1;
  while(c==1)
   {
    cout<<"Enter username:"<<"\t";        
    cin>>uname;
 	  cout<<"Enter password:"<<"\t";
  	cin>>pass;
  	struct retro
   	 {
    	char a[20];
    	char b[20];
   	 }ret;
    while(!file.eof())
     {
      file.read((char*)&bot,sizeof(bot));
      bot.retrieve(ret.a,ret.b);
      if(strcmp(ret.a,uname)==1 && strcmp(ret.b,pass)==1)
       {
        cout<<"Log in successful!!";
        c=0;
        break;
       }
     }
    int g;
    if(c==1)
     {  
      cout<<"Incorrect password or username\n";
      sleep(1);
      cout<<"1.Re-enter username and password\n"; 
      cout<<"2.Back";
      cin>>g;
     }
    if(g!=1 && g!=2)
     cout<<"Enter either 1 or 2\n";
    if(c==1 && g==1)
     ilog();
    else if(c==1 && g==2)
     page1();    
   }
  file.close();
  return bot;
}
   
void user::reserve(user type)                     //reserve
{ 
  train temp2;
  user send;
  system("clear");
  int a;
  for(a=0;temp.tickets[a]!=0;a++);
  if(a==5)
   {
    cout<<"Cannot reserve anymore tickets";
    page2(type);
   }
  else
   {
    cout<<"Enter train number of the train which you wish to book";
    fstream file;
    file.open("trains.txt",ios::in);
    while(!file.eof())
     {
      file.read((char*)&temp2,sizeof(temp2));
      cout<<"Train number:"<<temp2.no;
      cout<<"\t"<<"Train name:";
      puts(temp2.name);
     }
    int i,c=0;
    cin>>i;
    file.seekg(0,ios::beg);
    while(c!=1)
    {
     while(!file.eof())
      {
       file.read((char*)&temp2,sizeof(temp2));
       if(i==temp2.no)
        {
         cout<<"Ticket has been booked";
         send.tickets[a]=i; 
         c=1;
         break;
        }
      }
     if(c!=1)
     {
       cout<<"Invalid train number\n";
       cout<<"Please re-eneter train number";
       cin>>i;
     }
    }
   sleep(.5);
   page2(type);
  }
}
       
void user::profile()                 //profile 
{
  train temp2;
  system("clear");
  fstream file;
  file.open("trains.txt",ios::in);
  cout<<"\t\t"<<"Profile"<<"\n";
  cout<<"Username:"<<name<<"\n";
  cout<<"Tickets Booked:"<<"\n";
  int i;
  for(i=0;tickets[i]!=0;i++)
   {
    while(!file.eof())
     {
      file.read((char*)&temp2,sizeof(temp2));
      if(temp2.no==tickets[i])
       {
         cout<<i<<" Train number : "<<temp2.no<<"\t Name:";
         puts(temp2.name);
         break;
       }
     }
   }   
  file.close();
  cout<<"1.Back"<<"\t2.Exit\n";
  while(1)
   { 
    cin>>i;
    if(i==1)
     page2(temp);
    else if(i==2)
     exit(0);
    else
     cout<<"Invalid command\nRe-enter\n";
   }
}
  
void status()                             //status 
{ 
  train temp2;
  system("clear");
  cout<<"\t\tTrain status\n";
  cout<<"Enter train number\n";
  int no;
  cin>>no;
  fstream file;
  file.open("trains.txt",ios::in);
  int c=0,i=0;
  while(c!=1)
  {
   while(!file.eof())
    {
     file.read((char*)&temp2,sizeof(temp2));
     if(temp2.no==no)
      {
        i++;
        cout<<i<<" Train number : "<<temp2.no<<"\n Name:";
        puts(temp2.name);
        cout<<"\nTrain status :";
        temp2.status(temp2.no);
        c=1;
        break;
      }  
    }
   if(c==0)
    {
     cout<<"Re-enter train number";
     cin>>temp2.no;
    }
   } 
  file.close();
}

void trains()                               //train schedule
{ 
  train temp2;
  system("clear");
  fstream file;
  cout<<"Train name\tTrain number\tDeparture time\n";
  file.open("trains.txt",ios::in);
  while(!file.eof())
   {
    file.read((char*)&temp2,sizeof(temp2));
    //file>>temp2.name>>temp2.no;
    cout<<temp2.name<<"\t"<<temp2.no<<"\t"<<temp2.t.display()<<"\n";
   }
  file.close();
  int i;
  cout<<"1.Back"<<"\t2.Exit\n";
  while(1)
   { 
    cin>>i;
    if(i==1)
     page1();
    else if(i==2)
     exit(0);
    else
     cout<<"Invalid command\nRe-enter\n";
   } 
}

void olog()                                //logout
{
  system("clear");
  page1();
}

void page1()                               //page 1
{ 
  system("clear");
  user perm;
  fstream file;
  cout<<"\t \t"<<"WEST BENGAL RAILWAY NETWORK"<<"\n";
  cout<<"1.Log In"<<"\n"<<"2.Sign up"<<"\n";
  cout<<"3.Check Train Schedules"<<"\n"<<"4.Exit\n";
  int n;
  int m=1;
  while(m==1)
 {
  cin>>n;
  switch (n)
  { 
    case 1: m=0;                                      //done
            perm=ilog();
            page2(perm);
            break;
    case 2: m=0;                                      //done
	          temp.sign();
            break;
    case 3: m=0;
            trains();                                 //done  
            break;
    case 4: exit(0);                                 //done-works
            break;

    default: cout<<"Enter a number between 1 & 4"<<"\n";
             m=1;;
  }
 }
}

void page2(user perm)                               //page 2
{
  system("clear");
  
  cout<<"\t\t"<<"Welcome\t"<<perm.name;
  cout<<"\n1.Check Train Status"<<endl;
  cout<<"2.Reserve tickets"<<endl;
  cout<<"3.View profile"<<endl;
  cout<<"4.Log out"<<endl;
  int n;
  cin>>n;
  switch(n)
  { 
   case 1: status();          //done
           break;
   case 2: perm.reserve(perm);         //done
           break;
   case 3: perm.profile();         //done - works
           break;
   case 4: olog();            //done -works
           break;
   
   default: cout<<"Enter a number between 1 & 4"<<"\n";
  }
}

int main()
{
  system("clear");
  page1();
  getch();
}



             
