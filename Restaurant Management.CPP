#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<process.h>

class restra
{	int dno;
	char dname[20];
	float price;
	public:
	void getdata();
	void display();
	void modify();
	int get_dno();
	char * get_dname();
	float get_price();
};

void restra::getdata()
{	cout<<"\nEnter dish no., name, amount";
	cin>>dno;
	gets(dname);
	cin>>price;
}

void restra::display()
{	cout<<dno<<"\t";
	cout<<dname<<"     \t";
	cout<<price<<"                    \n";
}

void restra::modify()
{	char newname[20],p;
	display();
	cout<<"\nEnter new name: (press ' . ' to retain old one)\n";
	gets(newname);
	if(strcmp(newname,".")==0)
		strcpy(newname,dname);
	if(strcmp(dname,newname)!=0)
		strcpy(dname,newname);
	cout<<"\nEnter modified price:";
	cin>>price;
}

int restra::get_dno()
{	return dno;}
float restra::get_price()
{	return price;}
char * restra::get_dname()
{	return dname;}
fstream finout;
ifstream fin;
ofstream fout;
restra s1,s2;

void show()
{	fin.open("dishes.dat",ios::in|ios::binary);
	if(fin.eof()==1)
	{	cout<<"\nNo record found";
		return;
	}
	else
	{	cout<<"Dish no."<<"Dish name\t"<<"Price\n";
		while(fin.eof()!=1)
		{	fin.read((char*)&s2, sizeof(s2));
			if(fin.eof()!=1)
				s2.display();
		}
	}
	fin.close();
}

void main()
{	char dnam[80], last='y', a;
	int dn;
	restra s[2];
	clrscr();
	int ch, f=0, amt=0;
	do
	{	cout<<"\nEnter your choice:";
		cout<<"\n1. To add a new dish in menu";
		cout<<"\n2. View menu";
		cout<<"\n3. To insert a new dish";
		cout<<"\n4. Delete a dish from menu";
		cout<<"\n5. Modify an existing record";
		cout<<"\n6. Place order";
		cout<<"\n7. Exit \n";
		fflush(stdin);
		cin>>ch;
		if(ch==1)
		{	fout.open("dishes.dat", ios::out|ios::binary);
			for(int i=0;i<5;i++)
			{	s[i].getdata();
				fout.write((char *)&s[i], sizeof(s[i]));
			}
			fout.close();
		}

		if(ch==2)
			show();

		if(ch==3)
		{	fin.open("dishes.dat", ios::in|ios::binary);	
			fout.open("temp.dat", ios::out|ios::binary);
			cout<<"\nEnter data for new dish";
			s1.getdata();
			while(fin.eof()!=1)
			{	fin.read((char*)&s2, sizeof(s2));
				if(fin.eof()==1)
					break;
				if(s1.get_dno()<=s2.get_dno())
				{	fout.write((char*)&s1, sizeof(s1));
					last='n';
					break;
				}
				else
					fout.write((char*)&s2, sizeof(s2));
			}
			if(last=='y')
				fout.write((char*)&s1, sizeof(s1));
			else if(!fin.eof())
			{	while(fin.eof()!=1)
				{	fout.write((char*)&s2, sizeof(s2));
					fin.read((char*)&s2, sizeof(s2));
				}
			}
			fin.close();
			fout.close();
			remove("dishes.dat");
			rename("temp.dat" , "dishes.dat");
			cout<<"\nRecord inserted successfully\n";
			show();
		}

		if(ch==4)
		{	fin.open("dishes.dat", ios::in|ios::binary);
			fout.open("temp.dat", ios::out|ios::binary);
			cout<<"\nEnter dish no. to be deleted:";
			cin>>dn;
			while(fin.eof()!=1)
			{	fin.read((char*)&s2, sizeof(s2));
				if(fin.eof()==1)
					break;
				if(s2.get_dno()==dn)
				{	s2.display();
					f=1;
					cout<<"\nConfirm deletion: (y/n)";
					cin>>a;
					if(a=='n')
						fout .write((char*)&s2, sizeof(s2));
				}
				else
					fout.write((char*)&s2, sizeof(s2));
			}
			if(f==0)
			{	cout<<"\nRecord not found\n";
				getch();
				exit(0);
			}
			fin.close();
			fout.close();
			remove("dishes.dat");
			rename("temp.dat" , "dishes.dat");
			cout<<"\nRecord inserted successfully\n";
			show();
		}

		if(ch==5)
		{	long pos=0;f=0;
			finout.open("dishes.dat", ios::in|ios::out|ios::binary);
			cout<<"\nEnter dish no. which has to be modified:";
			cin>>dn;
			while(fin.eof()!=1)
			{	pos=finout.tellg();
				finout.read((char*)&s2, sizeof(s2));
				if(finout.eof()==1)
					break;
				if(s2.get_dno()==dn)
				{	s2.modify();
					finout.seekg(pos);
					finout.write((char*)&s2, sizeof(s2));
					f=1;
					cout<<"\nRecord modified successfully\n";
					break;
				}
			}
			if(f==0)
			{	cout<<"\nRecord not found";
				getch();
			}
			finout.close();
			show();
		}

		if(ch==6)
		{	int ic,qty,hw;
			int adno[5], aqty[5];
			char adname[5][15];
			float aprice[5];
			char ans='y';
			show();
			int i=0;
			cout<<"\nHow many orders do you want?";
			cin>>hw;
			while(ans=='y')
			{	cout<<"\nPlease enter an item code and its quantity";
				cin>>ic>>qty;
				fin.open("dishes.dat", ios::in|ios::binary);
				while(fin.eof()!=1)
				{	fin.read((char*)&s2, sizeof(s2));
					if(fin.eof()==1)
						break;
					if(s2.get_dno()==ic)
					{       amt=amt+ (s2.get_price()*qty));
						adno[i]=s2.get_dno();
						aqty[i]=qty;
						strcpy(adname[i], s2.get_dname());
						aprice[i]=s2.get_price();
						i++;
						fin.close();
						break;
					}
				}
				cout<<"\nDo you want to order more? (y/n)";
				cin>>ans;
			}
			cout<<"\nTotal amount="<<amt;
			cout<<"\nOrder details are as under:";
			cout<<"\nItem code   Item name   Item price   Quantity   Amount\n";
			for(int j=0;j<5;j++)
			{       int z=0;
				while(z<hw)
				{cout<<adno[j]<<"\t"<<adname[j]<<"\t"<<aprice[j]<<"\t"<<aqty[j]<<"\t"<<aqty[j]*aprice[j]<<"\n";
					hw--;j++;}}
					getch();
		}
		if(ch==7)
			exit(0);
	}while(1);
}
