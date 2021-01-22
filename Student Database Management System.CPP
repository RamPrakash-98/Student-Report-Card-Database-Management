#include<fstream.h>
#include<conio.h>
#include<iomanip.h>
#include<stdio.h>
#include<process.h>
#include<dos.h>
void create();
void edit();
void display();
void del();
class student
{
 char name[30],sec;
 int Class,rno;
 float marks[5];

 public:

//Function to enter details of Student

 void getdata()
 {
  cout<<"\n Enter Name of student : ";
  gets(name);
  cout<<" Enter class and section of the student :\n Class :";
  cin>>Class;
  cout<<" Section :";
  cin>>sec;
  cout<<" Enter roll no. of student : ";
  cin>>rno;
  cout<<'\n';
  entermarks();
 }

  // Function to show details of the student

 void showdata()
 {
  cout<<"\n Name:        \t";puts(name);
  cout<<"\n Class:       \t"<<Class<<' '<<sec;
  cout<<"\n Roll No.:    \t"<<rno;
 }

 //Function to return roll number

 int getrno()
 {
  return rno;
 }

  //Function to enter marks of student

 void entermarks()
 {
  cout<<"\n Enter Marks out of 100\n";

  cout<<"   English:           ";   cin>>marks[0];
  cout<<"   Mathematics:       ";   cin>>marks[1];
  cout<<"   Physics:           ";   cin>>marks[2];
  cout<<"   Chemistry:         ";   cin>>marks[3];
  cout<<"   Computer Science   ";   cin>>marks[4];
 }

 //Function to display marks

 void displaymarks()
 {
  cout<<"\t English:        \t"<<marks[0]<<'\n';
  cout<<"\t Mathematics:    \t"<<marks[1]<<'\n';
  cout<<"\t Physics:        \t"<<marks[2]<<'\n';
  cout<<"\t Chemistry:      \t"<<marks[3]<<'\n';
  cout<<"\t Computerscience:\t"<<marks[4]<<'\n';
 }

  //Function to Display Result
 void displayresult()
 {
  showdata();
  cout<<"\n\t***********************************************************\n";
  displaymarks();
  float avg,sum=0;
  for(int i=0;i<5;i++)
  sum+=marks[i];
  avg=sum/5;
  char grade;

	 if(avg>=90)              grade='A1';
   else  if(avg>=80 && avg<90)    grade='A2';
   else  if(avg>=70 && avg<80)    grade='B1';
   else  if(avg>=60 && avg<70)    grade='B2';
   else  if(avg>=50 && avg<60)    grade='C1';
   else  if(avg>=40 && avg<50)    grade='C2';
   else  if(avg>=33 && avg<40)    grade='D';
   else  if(avg<33)               grade='F';


   cout<<"\n\n\t Total Marks:"<<sum<<"/500";
   cout<<"\n\t Percentage:"<<setprecision(3)<<avg<<'%';
   cout<<"\n\t Grade:"<<grade;

 }
}S;

 //End of Class

 void main()
 {
  clrscr();
  cout<<"\n\n                              WELCOME: ";
  int choice;
  cout<<"\n\n\n\t\t          STUDENT REPORT CARD\n";
  cout<<"\n\t          *************************************** \n";
  cout<<"\n\t\t    1.CREATE NEW RECORD";
  cout<<"\n\t\t    2.EDIT EXISTING RECORD";
  cout<<"\n\t\t    3.DISPLAY RECORD";
  cout<<"\n\t\t    4.DELETE RECORD";
  cout<<"\n\t\t    5.EXIT";
  cout<<"\n\n\t\t    Enter your choice: ";
  cin>>choice;

       if(choice==1)
       create();
  else if(choice==2)
       edit();
  else if(choice==3)
       display();
  else if(choice==4)
       del();
  else if(choice==5)
	{
	  clrscr();
	  cout<<" \n\n\n \t\tTHANK YOU ";

	  delay(500);
	  exit(0);
	}

   getch();
 }

  //Function to create Records

  void create()
  {
   ofstream fil("student.dat",ios::app);
   char ch='y';
   clrscr();
   do
   {
    S.getdata();
    fil.write((char*)&S,sizeof(S));
    cout<<"Do you want to enter more records ?(y/n) ";
    cin>>ch;
   }while(ch=='y'||ch=='Y');
   fil.close();
   main();
  }

 //Function to edit Records

 void edit()
 {
  clrscr();
  fstream file("student.dat",ios::in|ios::out);
  student S;
  int found=-1,rn,pos;
  cout<<"Enter the roll no. to be edited:";
  cin>>rn;
  file.seekg(0);
  while(!file.eof())
  {
   pos=file.tellg();
   file.read((char*)&S,sizeof(S));
   if(rn==S.getrno())
   { cout<<"\nExisting Record: ";
     S.displayresult();
     found=1;
     break;
   }
  }
  if (found==1)
  {
   cout<<"\n Enter new record: ";
   S.getdata();
   file.seekg(pos,ios::beg);
   file.write((char*)&S,sizeof(S));
  }
  else
  {
   cout<<"Record does not exist ";
   delay(2000);
  }
  file.close();
  getch();
  main();
 }

 // Function to display Record

 void display()
 {
  clrscr();
  ifstream file("student.dat",ios::in);
  int r,flag=-1;
  cout<<"Enter the roll no. whose record is to be  displayed: ";
  cin>>r;
  file.seekg(0);
  file.read((char*)&S,sizeof(S));
  while(!file.eof())
  {
   if(r==S.getrno())
   {
    cout<<"\nRecord Found\n";
    S.displayresult();
    flag=1;
    break;
   }
   file.read((char*)&S,sizeof(S));

  }

  file.close();
  if(flag!=1)
  cout<<"\nRecord Doesn't Exist \nPress Enter to continue..... ";
  else
  cout<<"\n Press Enter to continue.... ";
  getch();
  main();
 }

 //Function to delete Record

 void del()
 {
  clrscr();
  ifstream file("student.dat",ios::in);
  ofstream newfile("newstudent.dat",ios::out);
  int r,found=0;
  cout<<"Enter the roll no of the record to be deleted:";
  cin>>r;
  file.read((char*)&S,sizeof(S));
  while(!file.eof() && found==0)
  {
   if(r!=S.getrno())
   newfile.write((char*)&S,sizeof(S));
   else
   found=1;
   file.read((char*)&S,sizeof(S));
  }
  if(found==0)
  {
   cout<<"\nRecord does not exist";
   delay(1000);
  }
  else
  cout<<"\n Record Successfully Deleted";
  delay(1000);
  file.close();
  newfile.close();
  remove("student.dat");
  rename("newstudent.dat","student.dat");
  main();
 }

  //                      End of Program



