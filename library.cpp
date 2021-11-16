#include<fstream>
#include<iostream>
using namespace std;
#include<conio.h>
#include<string.h>
class library
{
	public:
	int shelf;
	char Book_name[40];
	int Book_ID;
	char author[20];
	char type[10];
	int copies;
		void get();
		void disp();
		void wtf();
		void rff();
		void search();
		void erase();
		void mod();
		void idgen();
}l1;
class issuer
{
	char name[20];
	char phone_no[10];
	char ID_no[10];
	char Bookissue_name[100];
	int avail,checkdisp;
	int bookid;
	int issue_date;
	int issue_month;
	int issue_year;
	int due_date;
	int due_month;
	int due_year;
	int return_date,return_month,return_year;
	float fine;
	public:
		void wtf();
		int check;
		void rff();
		void search();
		void erase();
		void mod();
		void finecalc();
		void duedatecalc();
		void get();
		void disp();
		int bookavail();
		int copiescheck(int check,char bname[100]);
		void breturn();
}i1;
void issuer::get()
{
	int copy;
	cout<<"\nEnter book name to be issued:";
	cin>>Bookissue_name;
	avail=bookavail();
	copy=i1.copiescheck(1,Bookissue_name);
	if ((avail==1)&&(copy>=0))
	{
	cout<<"\nYour name:";
	cin>>name;
	cout<<"\nYour Phone number:";
	cin>>phone_no;
	cout<<"\nYour ID number:";
	cin>>ID_no;
	cout<<"\nEnter issue date(DD/MM/YY)";
	cin>>issue_date>>issue_month>>issue_year;
	checkdisp=1;
	duedatecalc();
    }
    else
    {
	    cout<<"Sorry book is not available";
	    checkdisp=0;
    }
}
int issuer::bookavail()
{
	ifstream ifile;
	int flag=0;
	ifile.open("library.dat");
	ifile.read((char *)&l1, sizeof l1);
	while(ifile)
	{
		if (strcmpi(Bookissue_name,l1.Book_name)==0)
		{
		    strcpy(Bookissue_name,l1.Book_name);
		    bookid=l1.Book_ID;
		    flag=1;
	    }
		ifile.read((char *)&l1, sizeof l1);
	}
	if (flag)
	return 1;
	else 
	return 0;
}
void issuer::disp()
{
	cout<<"\nIssuer name: "<<name;
	cout<<"\nBook name: "<<Bookissue_name;
	cout<<"\nBook ID number: "<<bookid;
	cout<<"\nIssue date: "<<issue_date<<"/"<<issue_month<<"/"<<issue_year;
	cout<<"\nDue date: "<<due_date<<"/"<<due_month<<"/"<<due_year;
	cout<<"\nFine: "<<fine;
}
void issuer::wtf()
{
	ofstream ofile;
	ofile.open("issuer.dat",ios::app);
	get();
	if (checkdisp)
	{
	ofile.write((char *)&i1,sizeof i1);
	ofile.close();
    }
}
void issuer::rff()
{
	ifstream ifile;
	ifile.open("issuer.dat");
	ifile.seekg(0,ios::beg);
	ifile.read((char *)&i1, sizeof i1);
	while (ifile)
	{
		disp();
		ifile.read((char *)&i1, sizeof i1);
	}
	ifile.close();
}
void issuer::search()
{
	ifstream ifile;
	int flag=0;
	char booksearch[40];
	ifile.open("issuer.dat");
	cout<<"Enter book name to be searched";
	cin>>booksearch;
	ifile.read((char *)&i1, sizeof i1);
	while (ifile)
	{
	     if (strcmpi(booksearch,i1.Bookissue_name)==0)
	        {
			  flag=1;
			  disp();
		    }
		ifile.read((char *)&i1, sizeof i1);
    }
    if (!flag)
    cout<<"Sorry book not found";
    ifile.close();
}
void issuer::erase()
{
	ifstream ifile;
	ofstream ofile;
	char bookerase[40];
	ifile.open("issuer.dat");
	ofile.open("tempo.dat",ios::app);
	cout<<"Enter book name to be deleted";
	cin>>bookerase;
	ifile.read((char *)&i1, sizeof i1);
	while (ifile)
	{
		
		if (strcmpi(bookerase,i1.Bookissue_name)!=0)
		 {
		
		   ofile.write((char *)&i1, sizeof i1);
	     }
	     ifile.read((char *)&i1, sizeof i1);
	}
	ifile.close();
	ofile.close();
	remove("issuer.dat");
	rename("tempo.dat","issuer.dat");
}
void issuer::mod()
{
	fstream f;
	f.open("issuer.dat",ios::in|ios::out);
    f.seekg(0,ios::beg);
	int x,y;
	char record[40];
	cout<<"Enter Book name record to be modified";
	cin>>record;
	f.read((char *)&i1,sizeof i1);
	int a=f.tellg();
	while (f)
	{
		if (strcmpi(record,i1.Bookissue_name)==0)
		{
		
		    cout<<"Select the record that needs to be modified.\nPress 1 to change book name\nPress 2 to change issuer's name\nPress 3 to change Book ID\nPress 4 to change Issue date\nPress 5 to change whole record";		
		    cin>>x;
		    switch(x)
		  {
		    	case 1:
		    		cout<<"Enter new Book name";
		    		cin>>i1.Bookissue_name;
		    		break;
		    	case 2:
		    		cout<<"Enter new issuer name";
		    		cin>>i1.name;
		    		break;
		    	case 3:
		    		cout<<"Enter new Book ID";
		    		cin>>i1.ID_no;
		    		break;
		    	case 4:	
				    cout<<"Enter new issue date";
		    		cin>>i1.issue_date;
		    		break;
		    	case 5:
		    		i1.wtf();
		    		break;
		    	default:cout<<"Option does not exist";
		  }
		  f.seekg(a-sizeof i1,ios::beg);
		  f.write((char *)&i1,sizeof i1);
    	}
	    f.read((char *)&i1,sizeof i1);
	    a=f.tellg();   
	}
	f.close();
}
void issuer::duedatecalc()
{
	due_month=issue_month;
	due_year=issue_year;
	due_date=issue_date+14;
	if (due_date>30)
	  {
		  due_month++;
	      due_date=due_date-30;
      }
    if (due_month>12)
     {
     	due_year++;
     	due_month=1;
	 }
}
void issuer::breturn()
{
	char record[100],namep[20];
	cout<<"\nEnter Book name:";
	cin>>record;
	cout<<"\nEnter your name:";
	cin>>namep;
	ifstream ifile;
	int flag=0;
	ifile.open("issuer.dat");
	ifile.read((char *)&i1, sizeof i1);
	while(ifile)
	{
		if ((strcmpi(Bookissue_name,record)==0)&&(strcmpi(name,namep)==0))
		{
		    flag=1;
	    }
		ifile.read((char *)&l1, sizeof l1);
	}
	ifile.close();
	if (flag)
	{
	cout<<"Enter book return date(DD/MM/YY):";
	cin>>return_date>>return_month>>return_year;
	i1.copiescheck(2,record);
	fine=(return_date-due_date);
	if (fine<0)
	  fine=fine+30;
	if ((return_date>=due_date)&&(return_month>due_month))
	     fine=fine+((return_month-due_month)*30);
	else if ((return_date>=due_date)&&(return_month<due_month)&&(return_year>due_year))
	     {
	     	return_month=(return_month-due_month)+12;
	     	fine=fine+(return_month*30);
		 }
	if ((return_month>=due_month)&&(return_year>due_year))
	  fine=fine+((return_year-due_year)*365);
	disp();
	cout<<"\nAccount deleted successfully!";
	ifstream ifile;
	ofstream ofile;
	ifile.open("issuer.dat");
	ofile.open("tempo.dat",ios::app);
	ifile.read((char *)&i1, sizeof i1);
	while (ifile)
	{
		
		if (strcmpi(namep,i1.name)!=0)
		 {
		
		   ofile.write((char *)&i1, sizeof i1);
	     }
	     ifile.read((char *)&i1, sizeof i1);
	}
	ifile.close();
	ofile.close();
	remove("issuer.dat");
	rename("tempo.dat","issuer.dat");
   }
   else 
   cout<<"Book is not issued";
}
void library::get()
{
	cout<<"\n Enter type";
	cin>>type;
	cout<<"\n Enter Book name";
	cin>>Book_name;
	cout<<"\n Enter Author name";
	cin>>author;
	cout<<"\n Enter Shelf number";
	cin>>shelf;
	cout<<"Enter copies";
	cin>>copies;
	idgen();
}
void library::idgen()
{
	ifstream ifile;
	ifile.open("library.dat");
	ifile.seekg(-sizeof l1,ios::end);
	ifile.read((char *)&l1, sizeof l1);
	Book_ID=l1.Book_ID+1;
	ifile.close();
}
void library::disp()
{
	cout<<"\n Type-\t";
	cout<<type;
	cout<<"\n Book name :\t";
	cout<<Book_name;
    cout<<"\n Author name :\t";
	cout<<author;
	cout<<"\n Book ID :\t";
	cout<<Book_ID;
	cout<<"\n Shelf number : \t";
	cout<<shelf;
	cout<<"\n Copies :  \t";
	cout<<copies;
}
int issuer::copiescheck(int check,char bname[100])
{
	fstream f;
	f.open("library.dat",ios::in|ios::out);
	f.seekg(0,ios::beg);
	f.read((char *)&l1, sizeof l1);
	int a=f.tellg();
	while (f)
	{
		if (strcmpi(bname,l1.Book_name)==0)
		{
         	if (check==1)
         	  l1.copies--;
        	else if (check==2)
        	  l1.copies++;
          f.seekg(a-sizeof l1,ios::beg);
		  f.write((char *)&l1,sizeof l1);
        }
        f.read((char *)&l1,sizeof l1);
	    a=f.tellg();   
    }
    f.close();
	return l1.copies;
}
void library::wtf()
{
	ofstream ofile;
	ofile.open("library.dat",ios::app);
	get();
	ofile.write((char *)&l1,sizeof l1);
	ofile.close();
}
void library::rff()
{
	ifstream ifile;
	ifile.open("library.dat");
	ifile.seekg(0,ios::beg);
	ifile.read((char *)&l1, sizeof l1);
	while (ifile)
	{
		disp();
		ifile.read((char *)&l1, sizeof l1);
	}
	ifile.close();
}

void library::search()
{
	ifstream ifile;
	int flag=0;
	char booksearch[40];
	ifile.open("library.dat");
	cout<<"Enter book name to be searched";
	cin>>booksearch;
	ifile.read((char *)&l1, sizeof l1);
	while (ifile)
	{
	     if (strcmpi(booksearch,l1.Book_name)==0)
	        {
			  flag=1;
			  disp();
		    }
		ifile.read((char *)&l1, sizeof l1);
    }
    if (!flag)
    cout<<"Sorry book not found";
    ifile.close();
}
void library::erase()
{
	ifstream ifile;
	ofstream ofile;
	char bookerase[40];
	ifile.open("library.dat");
	ofile.open("temp.dat",ios::app);
	cout<<"Enter book name to be deleted";
	cin>>bookerase;
	ifile.read((char *)&l1, sizeof l1);
	while (ifile)
	{
		
		if (strcmpi(bookerase,l1.Book_name)!=0)
		 {
		
		   ofile.write((char *)&l1, sizeof l1);
	     }
	     ifile.read((char *)&l1, sizeof l1);
	}
	ifile.close();
	ofile.close();
	remove("library.dat");
	rename("temp.dat","library.dat");
}
void library::mod()
{
	fstream f;
	f.open("library.dat",ios::in|ios::out);
	int x,y;
	char record[40];
	cout<<"Enter Book name record to be modified";
	cin>>record;
	f.read((char *)&l1,sizeof l1);
	int a=f.tellg();
	while (f)
	{
		if (strcmpi(record,l1.Book_name)==0)
		{
		
		    cout<<"Select the record that needs to be modified.\nPress 1 to change book name\nPress 2 to change author name\nPress 3 to change Book ID\nPress 4 to change Shelf number\nPress 5 to change Type\n Press 6 to change the Copies\n Press 7 to change the whole record";		
		    cin>>x;
		    switch(x)
		  {
		    	case 1:
		    		cout<<"Enter new Book name";
		    		cin>>l1.Book_name;
		    		break;
		    	case 2:
		    		cout<<"Enter new author name";
		    		cin>>l1.author;
		    		break;
		    	case 3:
		    		cout<<"Enter new Book ID";
		    		cin>>l1.Book_ID;
		    		break;
		    	case 4:	
				    cout<<"Enter new shelf number";
		    		cin>>l1.shelf;
		    		break;
		    	case 5:
		    		cout<<"Enter new type";
		    		cin>>l1.type;
		    		break;
		    	case 6:
		    		cout<<"Enter new copies";
		    		cin>>l1.copies;
		    		break;
		    	case 7:
		    		l1.wtf();
		  }
		  f.seekg(a-sizeof l1,ios::beg);
		  f.write((char *)&l1,sizeof l1);
	    }
	    f.read((char *)&l1,sizeof l1);
	    a=f.tellg();
	    f.close();
	}
}
int main()
{
	int x,y,choice;
	char record='y';
	cout<<"\t\t\t****WELCOME TO KITAAB AND KOFFEE****";
	do 
	{cout<<"\n 1. Library records\t\t2. Issuer records ";
	cin>>choice;
	if (choice==1)
	{
	do
	{
		
		cout<<"\nMain menu \n1. Press 1 to Write \n2. Press 2 to Read \n3. Press 3 to Search \n4. Press 4 to Delete \n5. Press 5 to modify ";
		cin>>x;
		switch(x)
		{
			case 1:
				l1.wtf();
				break;
			case 2:
				l1.rff();
				break;
			case 3:
				l1.search();
				break;
			case 4:
				l1.erase();
				break;
			case 5:
				l1.mod();
				break;
			default: cout<<"Option does not exist";
		}
		cout<<"\nDo you want to continue? Press 1 for yes and 2 for no";
		cin>>y;		
	}while(y==1);
   }
   else
   {
   	do
	{
		
		cout<<"\nMain menu \n1. Press 1 to Write \n2. Press 2 to Read \n3. Press 3 to Search \n4. Press 4 to delete \n5. Press 5 to modify \n6. Press 6 to return the book";
		cin>>x;
		switch(x)
		{
			case 1:
				i1.wtf();
				break;
			case 2:
				i1.rff();
				break;
			case 3:
				i1.search();
				break;
			case 4:
				i1.erase();
				break;
			case 5:
				i1.mod();
				break;
			case 6:
				i1.breturn();
				break;
			default: cout<<"Option does not exist";
		}
		cout<<"\nDo you want to continue? Press 1 for yes and 2 for no";
		cin>>y;		
	}while(y==1);
   }
   cout<<"\nChange record? Press y to continue";
   cin>>record;
}while(record=='y'||record=='Y');
	return 0;
}
