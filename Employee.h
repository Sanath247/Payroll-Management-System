#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>

using namespace std;

//Third Class
class Employee
{
	string empId,empName,empPhone,empMail,branchId,buffer;
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
}e;

void Employee::read()
{
	cout<<"Enter Employee: ID, Name, Phone No., Email, Branch Id\n";
	cin>>empId>>empName>>empPhone>>empMail>>branchId;
}
void Employee::pack()
{
	buffer.erase();
	buffer+=empId+"|"+empName+"|"+empPhone+"|"+empMail+"|"+branchId+"$\n";
}
void Employee::readFile()
{
	fstream fp;
	fp.open("Employee",ios::in);
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
void Employee::unpack()
{
	int i=0;
	empId.erase();
	while(buffer[i]!='|')
		empId+=buffer[i++];
	i++;
	empName.erase();
	while(buffer[i]!='|')
		empName+=buffer[i++];
	i++;
	empPhone.erase();
	while(buffer[i]!='|')
		empPhone+=buffer[i++];
	i++;
	empMail.erase();
	while(buffer[i]!='|')
		empMail+=buffer[i++];
	i++;
	branchId.erase();
	while(buffer[i]!='$')
		branchId+=buffer[i++];
	i++;
}
void Employee::display()
{
	cout<<"Employee Id:"<<empId<<"\n"<<"Employee Name:"<<empName<<"\n"<<"Employee Phone:"<<empPhone<<"\n"<<"Employee Mail:"<<empMail<<"\n"<<"branch Id:"<<branchId<<"\n"<<endl;
}
int Employee::search(string emplId)
{
	fstream fp;
	int number=0,flag=0,pos=0;
	fp.open("Employee",ios::in);
	while(!fp.eof())
	{
		buffer.erase();
		getline(fp,buffer);
		number++;
		unpack();
		if(empId==emplId)
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
int Employee::deleteRecord(string emplId)
{
	fstream fp;
	char mark='*',t;
	int pos,flag=0;
	pos=search(emplId);
	if(pos)
	{
		fp.open("Employee",ios::in|ios::out);
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
void Employee::modify(string emplId)
{
	if(deleteRecord(emplId))
	{
		cout<<"Enter Employee: ID, Name, Phone No., Emai, Branch Id\n";
		cin>>empId>>empName>>empPhone>>empMail>>branchId;
		buffer.erase();
		pack();
		writeFile();
	}
}
void Employee::writeFile()
{
	fstream fp;
	fp.open("Employee",ios::out|ios::app);
	fp<<buffer;
	fp.close();
}