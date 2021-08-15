#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<iomanip>

using namespace std;

//Fourth Class
class Attendance
{
	string empId,empName,branchId,date,attStatus,buffer;
	public:
	void pack();
	void unpack();
	void read();
	void readFile();
	void writeFile();
	void display();
	void search(string);
}a;

void Attendance::read()
{
	cout<<"Enter Employee: ID, Name, Branch Id, Date(dd/mm/yyyy),Attendance Status,\n";
	cin>>empId>>empName>>branchId>>date>>attStatus;
}
void Attendance::pack()
{
	buffer.erase();
	buffer+=empId+"|"+empName+"|"+branchId+"|"+date+"|"+attStatus+"$\n";
}
void Attendance::readFile()
{
	fstream fp;
	fp.open("Attendance",ios::in);
	cout<<"\n\t************************ LEDGER ************************\n";
	cout<<"\nEmployee Id\tEmployee Name\tBranch Id\tDate\t\tAttendance Status"<<"\n"<<endl;
	while(!fp.eof())
	{
		buffer.erase();
		getline(fp,buffer);
		unpack();
		if(!fp.eof())
			display();
	}
	fp.close();
}
void Attendance::unpack()
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
	branchId.erase();
	while(buffer[i]!='|')
		branchId+=buffer[i++];
	i++;
	date.erase();
	while(buffer[i]!='|')
		date+=buffer[i++];
	i++;
	attStatus.erase();
	while(buffer[i]!='$')
		attStatus+=buffer[i++];
	i++;

}
void Attendance::display()
{
	cout<<empId<<setw(24)<<empName<<setw(8)<<branchId<<setw(21)<<date<<setw(13)<<attStatus<<"\n"<<endl;
}

void Attendance::search(string sdate)
{
	fstream fp;
	int flag=0,pos=0;
	fp.open("Attendance",ios::in);
	cout<<"\n\t\tAttendance list of "<<sdate<<"\n\n";
	cout<<"\nEmployee Id\tEmployee Name\tBranch Id\tAttendance Status"<<"\n"<<endl;
	while(!fp.eof())
	{
		buffer.erase();
		getline(fp,buffer);
		unpack();

		if(!fp.eof()){
			if(date==sdate)
			{
				cout<<empId<<setw(24)<<empName<<setw(8)<<branchId<<setw(18)<<attStatus<<"\n"<<endl;
				flag=1;
			}
		}		
	}
	fp.close();
	if(!flag)
		cout<<"Record not found\n";
}

void Attendance::writeFile()
{
	fstream fp;
	fp.open("Attendance",ios::out|ios::app);
	fp<<buffer;
	fp.close();
}