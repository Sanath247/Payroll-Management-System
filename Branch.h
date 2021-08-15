#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>

using namespace std;

//Second Class
class Branch
{
	string branchId,branchName,branchState,branchCity,companyId,buffer;
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
}b;

void Branch::read()
{
	cout<<"Enter Branch: ID, Name, State, City and Company ID\n";
	cin>>branchId>>branchName>>branchState>>branchCity>>companyId;
}

void Branch::pack()
{
	buffer.erase();
	buffer+=branchId+"|"+branchName+"|"+branchState+"|"+branchCity+"|"+companyId+"$\n";
}

void Branch::readFile()
{
	fstream fp;
	fp.open("Branch",ios::in);
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

void Branch::unpack()
{
	int i=0;
	branchId.erase();
	while(buffer[i]!='|')
		branchId+=buffer[i++];
	i++;
	branchName.erase();
	while(buffer[i]!='|')
		branchName+=buffer[i++];
	i++;
	branchState.erase();
	while(buffer[i]!='|')
		branchState+=buffer[i++];
	i++;
	branchCity.erase();
	while(buffer[i]!='|')
		branchCity+=buffer[i++];
	i++;
	companyId.erase();
	while(buffer[i]!='$')
		companyId+=buffer[i++];
	i++;
}

void Branch::display()
{
	
	cout<<"Branch ID: "<<branchId<<"\n"<<"Branch Name: "<<branchName<<"\n"<<"Branch State: "<<branchState<<"\n"<<"Branch City: "<<branchCity<<"\n"<<"Company ID: "<<companyId<<"\n"<<endl;
}

int Branch::search(string brId)
{
	fstream fp;
	int number=0,flag=0,pos=0;
	fp.open("Branch",ios::in);
	while(!fp.eof())
	{
		buffer.erase();
		getline(fp,buffer);
		number++;
		unpack();
		if(branchId==brId)
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

int Branch::deleteRecord(string brId)
{
	fstream fp;
	char mark='*',t;
	int pos,flag=0;
	pos=search(brId);
	if(pos)
	{
		fp.open("Branch",ios::in|ios::out);
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

void Branch::modify(string brId)
{
	if(deleteRecord(brId))
	{
		cout<<"Enter Branch: ID, Name, State, City and CompanyId\n";
		cin>>branchId>>branchName>>branchState>>branchCity>>companyId;
		buffer.erase();
		pack();
		writeFile();
	}
}

void Branch::writeFile()
{
	fstream fp;
	fp.open("Branch",ios::out|ios::app);
	fp<<buffer;
	fp.close();
}