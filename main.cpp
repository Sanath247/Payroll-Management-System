#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>

#include "Company.h"
#include "Branch.h"
#include "Employee.h"
#include "Attendance.h"
#include "Salary.h"

using namespace std;

//To check whether file exist or empty
int FileExistance(string file)
{
	ifstream ifile;
	ifile.open(file);
	if(ifile){
		std::ifstream ifs(file,std::ios::ate);
		if(ifs.tellg() == 0){
			cout<<"File is empty\n";
			return 0;
		}
		else{
			return 1;
		}	
	}
	else{
		cout<<"File doesn't exist\n";
		return 0;
	}
}

//To evaluate user authentication
int owner_authen(int choice) {
	char o_username[20], o_password[20];
	const char *o_user[10] = {"company","branch","employee","attendance","salary"};
	const char *o_pass[10] = {"123","456","789","321","654"};
	cout << endl << endl;
	cout.width(25);
	cout << "Enter Admin ID and Password\n" << "---------------------------------------------------------------------------\n";
	cout << endl << "Admin ID: ";
	cin >> o_username;
	cout << "Password: ";
	cin >> o_password;

	if (strcmp(o_username, o_user[choice-1]) == 0 && strcmp(o_password, o_pass[choice-1]) == 0)
		return 1;
	else{
		cout<<"Invalid Login\n";
		return 0;
	}
}


	int main()
	{
		string compId,brId,emplId,sdate;
		int ch,ch1,ch2,ch3,ch4,ch5,ch6,check;
		cout<<"///////////////////////////////////////////////////////////////////////////\n";
		cout<<"\n";
		cout<<"\t Payroll Record Management Using Variable Length Record\t\n";
		cout<<"\n";
		while(1)
		{
			cout<<"///////////////////////////////////////////////////////////////////////////\n";
			cout<<"1.Company\n2.Branch\n3.Employee\n4.Attendance\n5.Salary\n6.exit"<<endl;
			cout<<"\n";
			cout<<"Enter your choice"<<endl;
			cin>>ch;
			switch(ch)
			{
				case 1:
					if (owner_authen(ch))
					{
						do
						{
							cout<<"\n------------------ Company Details ------------------"<<endl;
							cout<<"1.Input Company Data\n2.Display Company list\n3.Search Record\n4.Modify Record\n5.Logout\n";
							cout<<"\n";
							cout<<"Enter your choice\n";
							cin>>ch2;
							switch(ch2)
							{
								case 1:
									c.read();
									c.pack();
									c.writeFile();
								break;

								case 2:
									if(FileExistance("Company"))
										c.readFile();
									break;
								
								case 3:
									if(FileExistance("Company")){
										cout<<"Enter Company Id to search\n";
										cin>>compId;
										c.search(compId);	
									}
									
								break;
								
								case 4:
									if(FileExistance("Company")){
										cout<<"Enter Company Id to modify\n";
										cin>>compId;
										c.modify(compId);
									}
								break;
								
								default:
									break;
							}
						}while(ch2<5);
					}	
				break;

				case 2:
					if (owner_authen(ch))
					{	do
						{
							cout<<"\n------------------ Branch Details ------------------\n"<<endl;
							cout<<"1.Input Branch Data\n2.Get Branch list\n3.Search Record\n4.Modify Record\n5.Logout\n";

							cout<<"\n";
							cout<<"Enter your choice\n";
							cin>>ch1;
							switch(ch1)
							{
								case 1:
									b.read();
									b.pack();
									b.writeFile();
									break;
								
								case 2:
									if(FileExistance("Branch"))
										b.readFile();
									break;
								
								case 3:
									if(FileExistance("Branch")){
										cout<<"enter Branch Id number to search\n";
										cin>>brId;
										b.search(brId);
									}	
									break;
								
								case 4:
									if(FileExistance("Branch")){
										cout<<"Enter Branch Id to modify\n";
										cin>>brId;
										b.modify(brId);
									}	
									break;
								
								default:
									break;
							}
						}while(ch1<5);
					}
				break;

				
				case 3:
					if (owner_authen(ch))
					{
						do
						{
							cout<<"\n------------------ Employee Details ------------------"<<endl;
							cout<<"1.Add Employee\n2.Show Details\n3.Search Record\n4.Modify Record\n5.Logout\n";

							cout<<"\n";
							cout<<"Enter your choice\n";
							cin>>ch3;
							switch(ch3)
							{
								case 1:
									e.read();
									e.pack();
									e.writeFile();
									break;
								
								case 2:
									if(FileExistance("Employee"))
										e.readFile();
								break;
								
								case 3:
									if(FileExistance("Employee")){
										cout<<"Enter Employee Id to search\n";
										cin>>emplId;
										e.search(emplId);
									}	
									break;
								
								case 4:
									if(FileExistance("Employee")){
										cout<<"Enter Employee Id to modify\n";
										cin>>emplId;
										e.modify(emplId);
									}	
									break;
								
								default:
									break;
							}
						}while(ch3<5);
					}	
				break;

				
				case 4:
					if (owner_authen(ch))
					{
						do
						{
							cout<<"\n------------------ Attendance Status ------------------"<<endl;
							cout<<"1.Mark Attendance\n2.Attendance ledger\n3.Search Attedance status\n4.Logout\n";

							cout<<"\n";
							cout<<"Enter your choice\n";
							cin>>ch4;
							switch(ch4)
							{
								case 1:
									a.read();
									a.pack();
									a.writeFile();
									break;
								
								case 2:
									if(FileExistance("Attendance"))
										a.readFile();
								break;
								
								case 3:
									if(FileExistance("Attendance")){
										cout<<"Enter the date (dd/mm/yyyy)\n";
										cin>>sdate;
										a.search(sdate);
									}	
									break;
								
								default:
									break;
							}
						}while(ch4<4);
					}		
				break;

				case 5:
					if (owner_authen(ch))
					{
						do
						{
							cout<<"\n------------------ Salary Section ------------------"<<endl;
							cout<<"1.Input Salary Details\n2.Generate Payslip\n3.Modify Salary Details\n4.Logout\n";
							cout<<"\n";
							cout<<"Enter your choice\n";
							cin>>ch5;
							switch(ch5)
							{
								case 1:
									s.read();
									s.pack();
									s.writeFile();
									break;
								
								case 2:
									if(FileExistance("Salary"))
										s.readFile();
									break;
								
								case 3:
									if(FileExistance("Salary")){
										cout<<"Enter Employee Id to modify\n";
										cin>>emplId;
										s.modify(emplId);
									}
									break;
								
								default:
									break;
							}
						}while(ch5<4);
					}	
				break;
				
			case 6:cout<<"Thankyou for using this application\n";
					exit(0);	
			
			default:cout<<"Invalid choice...!\n";
					
			}
		}
	}