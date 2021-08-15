#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>

using namespace std;

//Fifth class0
class Salary
{
	string emplId,empId,empName,buffer,hr,med,pf,basicSal,grossSal,tax;
	int hr1,med1,pf1,basicSal1;
	double grossSal1 = 0, tax1 = 0;

	public:
	void pack();
	void unpack();
	void read();
	void readFile();
	void writeFile();
	void display(string);
	int deleteRecord(string);
	int search(string);
	void modify(string);
	void paySlip();
}s;

void Salary::read()
{
	cout<<"Enter Employee: ID, Name, H.R, ME.D, P.F, Basic Salary\n";
	cin>>empId>>empName>>hr>>med>>pf>>basicSal;
	paySlip();
	cout<<"\n"<<"Gross slary: "<<grossSal<<"\n"<<"Tax: "<<tax<<"\n"<<endl;
}
void Salary::pack()
{
	buffer.erase();
	buffer+=empId+"|"+empName+"|"+hr+"|"+med+"|"+pf+"|"+basicSal+"|"+grossSal+"|"+tax+"$\n";
}
void Salary::readFile()
{
	cout<<"\nEnter Employee Id: ";
	cin>>emplId;

	fstream fp;
	int flag = 0;
	fp.open("Salary",ios::in);
	while(!fp.eof())
	{
		buffer.erase();
		getline(fp,buffer);
		unpack();
		if(empId==emplId)
		{
			display(emplId);
			flag = 1;
		}	
	}
	fp.close();
	if(!flag)
		cout<<"Record not found\n";
}
void Salary::unpack()
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
	hr.erase();
	while(buffer[i]!='|')
		hr+=buffer[i++];
	i++;
	med.erase();
	while(buffer[i]!='|')
		med+=buffer[i++];
	i++;
	pf.erase();
	while(buffer[i]!='|')
		pf+=buffer[i++];
	i++;
	basicSal.erase();
	while(buffer[i]!='|')
		basicSal+=buffer[i++];
	i++;
	grossSal.erase();
	while(buffer[i]!='|')
		grossSal+=buffer[i++];
	i++;
	tax.erase();
	while(buffer[i]!='$')
		tax+=buffer[i++];
	i++;
}
void Salary::display(string emplId)
{
	if(empId==emplId)
	{
		cout<<"\n\t--------------- PAYSLIP ---------------\n"<<endl;
		
		cout<<"\t\tEmployee ID:"<<empId<<"\n\n"<<"\t\tEmployee Name:"<<empName<<"\n"<<endl;

		cout<<"\t----------------------------------------\n"<<endl;

		cout<<"\t\tHRA: "<<hr<<"\n"<<"\t\tMED: "<<med<<"\n"<<"\t\tPF: "<<pf<<"\n"<<"\t\tBASIC SALARY: "<<basicSal<<"\n\n"<<endl;
		cout<<"\t\tGROSS SALARY: "<<grossSal<<"\n"<<"\t\tTAX (2.1 % of gross): "<<tax<<"\n"<<endl;

		cout<<"\n\t--------------- ******** ---------------\n"<<endl;
	}
}

int Salary::search(string emplId)
{
	fstream fp;
	int number=0,flag=0,pos=0;
	fp.open("Salary",ios::in);
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
int Salary::deleteRecord(string emplId)
{
	fstream fp;
	char mark='*',t;
	int pos,flag=0;
	pos=search(emplId);
	if(pos)
	{
		fp.open("Salary",ios::in|ios::out);
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

void Salary::modify(string emplId)
{
	if(deleteRecord(emplId))
	{
		cout<<"Enter Employee: ID, Name, H.R, ME.D, P.F, Basic Salary\n";
		cin>>empId>>empName>>hr>>med>>pf>>basicSal;
		paySlip();
		cout<<"\n"<<"Gross slary: "<<grossSal<<"\n"<<"Tax: "<<tax<<"\n"<<endl;
		buffer.erase();
		pack();
		writeFile();
	}
}
void Salary::writeFile()
{
	fstream fp;
	fp.open("Salary",ios::out|ios::app);
	fp<<buffer;
	fp.close();
}

void Salary::paySlip()
{
	hr1 = stoi(hr);
	med1 = stoi(med);
	pf1 = stoi(pf);
	basicSal1 = stoi(basicSal);

	grossSal1 = hr1+med1+pf1+basicSal1;
	tax1 = (grossSal1*2.1)/100;

	grossSal = to_string(grossSal1);
	tax = to_string(tax1);
}