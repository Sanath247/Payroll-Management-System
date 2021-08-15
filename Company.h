#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>

using namespace std;


//First Class
class Company
{
	string companyId,companyName,companyState,companyCity,buffer;
	public:
	void pack();	
	void unpack();
	void read();
	void readFile();
	void writeFile();
	void display();
	int deleteRecord(string);
	int search(string);
	void modify(string);
	//int owner_authen();
}c;

void Company::read()
{
	cout<<"Enter Company: ID, Name, State, City\n";
	cin>>companyId>>companyName>>companyState>>companyCity;
}

void Company::pack()
{
	buffer.erase();
	buffer+=companyId+"|"+companyName+"|"+companyState+"|"+companyCity+"$\n";
}

void Company::readFile()
{
		fstream fp;
		fp.open("Company",ios::in);
		while(!fp.eof())
		{
			buffer.erase();
			getline(fp,buffer);
			unpack();
			if(!fp.eof()&&buffer[0]!='*')
				display();
		}
		fp.close();	
}

void Company::unpack()
{
	int i=0;
	companyId.erase();
	while(buffer[i]!='|')
		companyId+=buffer[i++];
	i++;
	companyName.erase();
	while(buffer[i]!='|')
		companyName+=buffer[i++];
	i++;
	companyState.erase();
	while(buffer[i]!='|')
		companyState+=buffer[i++];
	i++;
	companyCity.erase();
	while(buffer[i]!='$')
		companyCity+=buffer[i++];
	i++;
}

void Company::display()
{
	
	cout<<"Company ID:"<<companyId<<"\n"<<"Company Name: "<<companyName<<"\n"<<"Company State: "<<companyState<<"\n"<<"Company City: "<<companyCity<<"\n"<<endl;
}

int Company::search(string compId)
{
		fstream fp;
		int number=0,flag=0,pos=0;
		fp.open("Company",ios::in);
		while(!fp.eof())
		{
			buffer.erase();
			getline(fp,buffer);
			number++;
			unpack();
			if(companyId==compId)
			{
				cout<<"\nRecord is "<<buffer;
				cout<<"\nRecord found at position "<<number<<"\n";
				pos=fp.tellg();
				flag=1;
				return pos;
			}
		}
		fp.close();
		if(!flag)
			cout<<"Record not found\n";
		return pos;
}

int Company::deleteRecord(string compId)
{
	fstream fp;
	char mark='*',t;
	int pos,flag=0;
	pos=search(compId);
	if(pos)
	{
		fp.open("Company",ios::in|ios::out);
		pos-=2;
		t=fp.get();
		while(t!='$'&&pos!=0)
		{
			pos--;
			fp.seekp(pos,ios::beg);
			t=fp.get();
		}
		if(pos!=0)
			fp.seekp(pos+2,ios::beg);
		else
			fp.seekp(pos,ios::beg);
		fp.put(mark);
		flag=1;
	}
	fp.close();
	if(!flag)
		return 0;
	else
		return 1;
}

void Company::modify(string compId)
{
		if(deleteRecord(compId))
		{
			cout<<"Enter Company: ID, Name, State, City\n";
			cin>>companyId>>companyName>>companyState>>companyCity;
			buffer.erase();
			pack();
			writeFile();
		}
}

void Company::writeFile()
{
	fstream fp;
	fp.open("Company",ios::out|ios::app);
	fp<<buffer;
	fp.close();
}