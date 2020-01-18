// Final Project.cpp :											finished 26-4-2018
#include <iostream>												// cout,cin and such things.
#include <fstream>												// read/write files
#include <string>												// Strings , cin.get();
#include <conio.h>												// getche
#include <algorithm>											// transform 
#include <cctype>												// toupper,tolower
#include <direct.h>												// for creating program files folder
#include <stdlib.h>     
#include <time.h>     
#include <cstdlib>
using namespace std;

struct employee {												// Struct data type to work easier. 
	int id;
	string fname, lname;
	double WH, PPH, incentives, sal, tax, netsal, gross;
};
struct loginarray 
{
	int id, permission;
	string username, password, a1, a2, a3, a4;

};
employee emp[100];												// array to store employees data.
employee edited_emp[1];											// array for edit use.
employee tempemp[100];											// array for sorting data.
employee tempemp1[100];											// array for sort data min to max salary.
loginarray logarr[10];
string questionsarray[4];
int total_employees = 0;										// global variable for employees number.
int current_indx;												// global variable for current index in search, for use in edit and delete.
int indx_max_sal, indx_min_sal;									// global variables for index, for use in max/min sal.
int total_managers = 0;
int current_logged_manager = 0;
int current_manager = 0;
int AVA_login = 0;

void main_menu();												// User interface for the program.
void check_employees_number();									// function to know employees number.
void recover_data();											// restoring data from files at program start.
void print_data();												// print all employees data.
void add_emp();													// add a new employee.
void search_emp();												// search for employee
void delete_emp();												// delete an employee.
void edit_emp();												// edit an employee details.
void print_max_min_sal();										// print the employees with minimum and maximum salaries.
void sort_data();												// sorting data by ID, Salaries Min to max and salaries Max to Min.
void save_data_a_op();											// save data to files after editing or deleting employee.
void sys_creat_folder();										// create a program files folder to store data texts.
void save_important_text_data();								// create a text to warn user from missing with program files.
void print_logo();												// print P.R Logo on menu.
void sys_print_emp(int a);										// system print employee.
void sys_search_emp_id(int SID);								// system search employee by ID.
void sys_search_emp_name(string fname, string lname);			// system search employee by name.
void sys_del_emp();												// system delete employee.
void sys_edit_emp();											// system edit employee.
void sys_max_sal();												// system find max salary.
void sys_min_sal();												// system find min salary.
void sys_sort_id();												// system sort by ID.
void sys_sort_sal_max_to_min();									// system sort by Max to Min.
void sys_sort_sal_min_to_max();									// system sort by Min to Max
void save_data_to_file();										// save sorted data to file to make user use it.
double sys_calc_tax(double salary);								// system calculate tax.
bool check_ids(employee *array, int array_size, int value);		// check exists IDs.
void questions();
void login();
void save_logindata();
void sys_create_logindata_folder();
void recover_logindata();
void check_total_manager();
void print_main_logo();
void main_UI();
bool check_man_id(int ID);
bool check_username(string value);
void print_manager_data();
void sys_print_man(int index);
void add_manager();
void main_menu();
void change_password(int index);
void logged_change_password(int index);
void sys_search_manager(string username);
void search_manager();
void owner_rights(string fname, string lname);
void autogenerateIDs();

int main() 
{
	main_UI();
	return 0;
}



void check_employees_number() {					//check employees number to use in many cases
	ifstream id("ProgramFiles\\IDs.txt", ios::in); {	// restoring IDs from text to know how many employees we have.
		for (int k = 0; k < 100; k++) {
			id >> emp[k].id;
		}
	}
	int i = 0;
	while (emp[i].id) {									// while loop that stay run until emp[i].id not equal a value.
		total_employees = i + 1;						// global variable total_employees equal the current index + 1.
		i++;
	}
}

void recover_data() 
{							//recovering data from files to arrays
	ifstream id("ProgramFiles\\IDs.txt", ios::in);			// quick and easy.
	ifstream fname("ProgramFiles\\fname.txt", ios::in);
	ifstream lname("ProgramFiles\\lname.txt", ios::in);
	ifstream WH("ProgramFiles\\WH.txt", ios::in);
	ifstream PPH("ProgramFiles\\PPH.txt", ios::in);
	ifstream sal("ProgramFiles\\sal.txt", ios::in);
	ifstream gross("ProgramFiles\\gross.txt", ios::in);
	ifstream tax("ProgramFiles\\tax.txt", ios::in);
	ifstream netsal("ProgramFiles\\netsal.txt", ios::in);
	for (int i = 0; i < total_employees; i++) {			// using the global variable total_employees to end the loop.
		id >> emp[i].id;
		fname >> emp[i].fname;
		lname >> emp[i].lname;
		WH >> emp[i].WH;
		PPH >> emp[i].PPH;
		sal >> emp[i].sal;
		gross >> emp[i].gross;
		tax >> emp[i].tax;
		netsal >> emp[i].netsal;
	}
}

void print_data() {							// print all employees
	recover_data();							// recovering data to make that the data is correct after edit and delete.
	system("cls");							// using system cls to print all employees data only on view.
	cout << "|-------|-----------------------|-------|-------|---------------|---------------|---------------|----------------|\n";
	cout << "| ID\t| Name\t\t\t| WH\t| PPH\t| Salary\t| Gross\t\t| Tax\t\t| Net Salary\t |\n";
	cout << "|-------|-----------------------|-------|-------|---------------|---------------|---------------|----------------|\n";
	for (int i = 0; i < total_employees; i++) {		// using global variable to end the loop.
		sys_print_emp(i);							// using system print employee to print employees data one by one in the loop.
	}
	cout << "\t\t\t\t\t\t Total Employees: " << total_employees << endl << endl;	//using total_employees variable to know how many employees user have.
	if (AVA_login == 1 || logarr[current_logged_manager].permission == 1 || logarr[current_logged_manager].permission == 2) {
		int choice;										// variable for the following options.
		cout << "\t\t1. Add Employee.\t\t2. Search Employee.\t\t3. Delete Employee.\n\n\t\t4. Edit Employee.\t\t5. Sort Data.\t\t\t6. Show Max/Min Salary.\n\n\t\t7. Auto Generate IDs.\t\t0. Main menu.\n\n\t\t\t\t\t\tChoice: ";	cin >> choice;
		while (1) {										// make sure that user input is a number.
			if (cin.fail() || choice < 0) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "Invalid input. Enter a number: ";		cin >> choice;
				continue;
			}
			break;										// break the loop when the input pass the if statment.
		}
		if (choice == 1)								// case 1 for add a new employee.
			add_emp();
		else if (choice == 2)							// case 2 to search for an employee details.
			search_emp();
		else if (choice == 3)							// case 3 to delete an employee.
			delete_emp();
		else if (choice == 4)							// case 4 to edit an employee details.
			edit_emp();
		else if (choice == 5)							// case 5 to sort data.
			sort_data();
		else if (choice == 6)							// case 6 to print employees with max and min salaries.
			print_max_min_sal();
		else if (choice == 7)
			autogenerateIDs();
		else if (choice == 0)							// case 0 to exit the program.
			main_menu();
		else {											// any other case return to menu.
			cout << "\t\t\t\t\t\tInvalid input.\n\t\t\t\t    Press any key to return to main menu...";
			_getche();	main_menu();					// delay before back to menu to make user know that he entered invalid input.
		}
	}
	else if (logarr[current_logged_manager].permission == 3) {
		system("cls");							// using system cls to print all employees data only on view.
		cout << "|-------|-----------------------|-------|-------|---------------|---------------|---------------|----------------|\n";
		cout << "| ID\t| Name\t\t\t| WH\t| PPH\t| Salary\t| Gross\t\t| Tax\t\t| Net Salary\t |\n";
		cout << "|-------|-----------------------|-------|-------|---------------|---------------|---------------|----------------|\n";
		for (int i = 0; i < total_employees; i++) {		// using global variable to end the loop.
			sys_print_emp(i);							// using system print employee to print employees data one by one in the loop.
		}
		cout << "\t\t\t\t\t\t Total Employees: " << total_employees << endl << endl;
		_getch();	main_menu();
	}
}

void add_emp() {					// add new employees
	int i = total_employees;		// to add new data to the following index for last employee.
	string tempfname, templname;	// temp variables to handle uppercases
	cout << "Enter Employee's ID : ";	cin >> emp[i].id;
	while (1) {						// make sure the input is right.
		if (cin.fail()) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Enter a number: ";		cin >> emp[i].id;
			continue;
		}
		else if (emp[i].id <= 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Can't add 0 or negative number as an ID. Try another number: ";		cin >> emp[i].id;
			continue;
		}
		else if (check_ids(emp, total_employees, emp[i].id) == true) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Employee with same ID exist. Try a new ID: ";		cin >> emp[i].id;
			continue;
		}
		break;
	}
	cout << "\nEnter Employee's First name : ";	cin >> tempfname;		// holding entered data to handle uppercases
	transform(tempfname.begin(), tempfname.end(), tempfname.begin(), tolower);	emp[i].fname = tempfname;
	cout << "\nEnter Employee's last name : ";	cin >> templname;		// holding entered data to handle uppercases
	transform(templname.begin(), templname.end(), templname.begin(), tolower);	emp[i].lname = templname;
	cout << "\nEnter Employee's worked hours : ";	cin >> emp[i].WH;
	while (1) {						// make sure the input is right.
		if (cin.fail() || (emp[i].WH > 720 || emp[i].WH <= 0))
		{
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Worked hours range is 1 to 720: ";		cin >> emp[i].WH;
			continue;
		}
		break;
	}
	cout << "\nEnter Employee's pay per hour : ";	cin >> emp[i].PPH;
	while (1) {						// make sure the input is right.
		if (cin.fail() || emp[i].PPH <= 0 || emp[i].PPH > 10000)
		{
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Pay per hour range is 1 to 10k: ";		cin >> emp[i].PPH;
			continue;
		}
		break;
	}
	cout << "\nThe default incentives is 52%. You can edit it from Main menu >> Edit an employee details.\n";
	cout << "\n<===============================================================================================>\n";
	emp[i].sal = emp[i].WH * emp[i].PPH;					// calculating salary, gross, tax and net salary.
	emp[i].gross = emp[i].sal * (0.52);
	emp[i].tax = sys_calc_tax(emp[i].sal);
	emp[i].netsal = emp[i].sal + emp[i].gross - emp[i].tax;

	ofstream id("ProgramFiles\\IDs.txt", ios::app); {		// store new data to data texts.
		id << emp[i].id << endl;
	}
	ofstream fname("ProgramFiles\\fname.txt", ios::app); {
		fname << emp[i].fname << endl;
	}
	ofstream lname("ProgramFiles\\lname.txt", ios::app); {
		lname << emp[i].lname << endl;
	}
	ofstream WH("ProgramFiles\\WH.txt", ios::app); {
		WH << emp[i].WH << endl;
	}
	ofstream PPH("ProgramFiles\\PPH.txt", ios::app); {
		PPH << emp[i].PPH << endl;
	}
	ofstream sal("ProgramFiles\\sal.txt", ios::app); {
		sal << emp[i].sal << endl;
	}
	ofstream gross("ProgramFiles\\gross.txt", ios::app); {
		gross << emp[i].gross << endl;
	}
	ofstream tax("ProgramFiles\\tax.txt", ios::app); {
		tax << emp[i].tax << endl;
	}
	ofstream netsal("ProgramFiles\\netsal.txt", ios::app); {
		netsal << emp[i].netsal << endl;
	}
	total_employees++;										// increase number of employees.
	int choice;												// variable for the following options.
	cout << "\t\t1. Add another employee.\t2. View all employees.\t0. Main menu.\n\t\tChoice : "; cin >> choice;
	while (1) {												// make sure the input is right.
		if (cin.fail() || choice < 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Enter a number: ";		cin >> choice;
			continue;
		}
		break;
	}
	if (choice == 1)								// if the input equal 1 return to add employee function.
		add_emp();
	else if (choice == 2) 							// if the input equal 2 return to print all employees data function.
		print_data();
	else if (choice == 0)							// if the input equal 1 return to main menu function.
		main_menu();
	else {
		cout << "\t\t\t\t\t\tInvalid input.\n\t\t\t\t    Press any key to return to main menu...";
		_getche();									// delay before back to menu to make user know that he entered invalid input.
		main_menu();
	}
}

void search_emp() {						//search employee by recovering data first to get accurate results
	recover_data();
	int searchid;
	int choice, choice2;
	string fname, lname, tempfname, templname;
	cout << "\n\t\t1. Search by ID.\t\t2. Search by name.\t\t0. Main menu.\n\n\t\t\t\t\t\tChoice: ";	cin >> choice;
	while (1) {							// make sure the input is right.
		if (cin.fail() || choice < 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice;
			continue;
		}
		break;
	}
	if (choice == 1) {
		cout << "Enter Search ID : ";	cin >> searchid;
		while (1) {							// make sure the input is right.
			if (cin.fail()) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "Invalid input. Enter a number: ";		cin >> searchid;
				continue;
			}
			break;
		}
		sys_search_emp_id(searchid);		// sending search id to system search emp id function. the function will do the rest.
		cout << "\t\t1. Delete Employee.\t\t2. Edit Employee.\t\t0. Main menu.\n\n\t\t\t\t\tChoice: ";		cin >> choice2;
		while (1) {							// make sure the input is right.
			if (cin.fail() || choice2 < 0) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice2;
				continue;
			}
			break;
		}
		if (choice2 == 1) {					// send the current index to sys_del_emp(); to delete.
			sys_del_emp();
			cout << "Employee has been deleted successfully.\nPress any key to continue...";
			_getche();	main_menu();
		}
		else if (choice2 == 2) {			// send the current index to sys_edit_emp(); to edit.
			sys_edit_emp();
			cout << "Employee data has been edited successfully.\nPress any key to continue...";
			_getche();
		}
		else if (choice2 == 0)				// return to menu.
			main_menu();
		else {								// any invalid input return to main menu.
			cout << "\t\t\t\t\t\tInvalid input.\n\t\t\t\t    Press any key to return to main menu...";
			_getche();
			main_menu();
		}
	}
	else if (choice == 2) {
		cout << "Enter employee's first name : ";	cin >> tempfname;
		transform(tempfname.begin(), tempfname.end(), tempfname.begin(), tolower);	fname = tempfname;
		cout << "Enter employee's last name : ";	cin >> templname;
		transform(tempfname.begin(), tempfname.end(), tempfname.begin(), tolower);	lname = templname;
		sys_search_emp_name(fname, lname);
		cout << "\t1. Delete Employee.\t\t2. Edit Employee.\t\t0. Main menu.\n\n\t\t\tChoice: ";	cin >> choice2;
		while (1) {							// make sure the input is right.
			if (cin.fail() || choice2 < 0) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice2;
				continue;
			}
			break;
		}
		if (choice2 == 1) {					// send the current index to sys_del_emp(); to delete.
			sys_del_emp();
			cout << "Employee has been deleted successfully.\nPress any key to continue...";
			_getche();
		}
		else if (choice2 == 2) {			// send the current index to sys_edit_emp(); to edit.
			sys_edit_emp();
			cout << "Employee has been edited successfully.\nPress any key to continue...";
			_getche();
		}
		else if (choice2 == 0)
			main_menu();
		else {								// any invalid input return to main menu.
			cout << "\t\t\t\t\t\tInvalid input.\n\t\t\t\t    Press any key to return to main menu...";
			_getche();
			main_menu();
		}
	}
	else if (choice == 0)					// return to menu.
		main_menu();
	else {									// any invalid input start again.
		cout << "Invalid input. Try again\n";
		search_emp();
	}
}

void delete_emp() {							//delete an employee
	recover_data();
	int deleteid, choice;
	string fname, lname, tempfname, templname, choice2, tempchoice2;
	cout << "\n\t\t1. Delete by ID.\t\t2. Delete by name.\t\t0. Main menu.\n\n\t\t\t\t\t\tChoice: ";	cin >> choice;
	while (1) {								// make sure the input is right.
		if (cin.fail() || choice < 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice;
			continue;
		}
		break;
	}
	if (choice == 1) {
		cout << "Enter the ID to delete: ";	cin >> deleteid;
		while (1) {							// make sure the input is right.
			if (cin.fail()) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "Invalid input. Enter a number: ";		cin >> deleteid;
				continue;
			}
			break;
		}
		sys_search_emp_id(deleteid);		// sending the id to sys_search_emp_id(); to check employee details.
		cout << "Are you sure that you want to delete " << emp[current_indx].fname + ' ' + emp[current_indx].lname << " ? (yes/no)";
		cin >> tempchoice2;
		transform(tempchoice2.begin(), tempchoice2.end(), tempchoice2.begin(), tolower);	choice2 = tempchoice2;
		if (choice2 == "yes") {				// send the current index to sys_del_emp(); to delete.
			sys_del_emp();
			cout << "Employee has been deleted successfully.\nPress any key to continue...";
			_getche();		 main_menu();
		}
		else if (choice2 == "no") {			// back to main menu if the user changes his mind.
			cout << "Employee hasn't been deleted\nPress any key to back to main menu...";
			_getche();
			main_menu();
		}
		else {								// any invalid input return to main menu.
			cout << "Invalid input.\nPress any key to back to main menu...";
			_getche();
			main_menu();
		}
	}
	else if (choice == 2) {
		cout << "Enter employee's first name : ";	cin >> tempfname;
		transform(tempfname.begin(), tempfname.end(), tempfname.begin(), tolower);	fname = tempfname;
		cout << "Enter employee's last name : ";	cin >> templname;
		transform(tempfname.begin(), tempfname.end(), tempfname.begin(), tolower);	lname = templname;
		sys_search_emp_name(fname, lname);	// sending the first and last name to sys_search_emp_name(); to check employee details.
		cout << "Are you sure that you want to delete " << emp[current_indx].fname + ' ' + emp[current_indx].lname << " ? (yes/no)";
		cin >> tempchoice2;
		transform(tempchoice2.begin(), tempchoice2.end(), tempchoice2.begin(), tolower);	choice2 = tempchoice2;
		if (choice2 == "yes") {				// send the current index to sys_del_emp(); to delete.
			sys_del_emp();
			cout << "Employee has been deleted successfully.\nPress any key to continue...";
			_getche();	main_menu();
		}
		else if (choice2 == "no") {			// return to menu.
			cout << "Employee hasn't been deleted\nPress any key to back to main menu...";
			_getche();
			main_menu();
		}
		else {								// any invalid input return to main menu.
			cout << "Invalid input.\nPress any key to back to main menu...";
			_getche();
			main_menu();
		}
	}
	else if (choice == 0)					// return to menu.
		main_menu();
	else {									// any invalid input start again.
		cout << "Invalid input. Try again\n";
		delete_emp();
	}
}

void edit_emp() {
	recover_data();
	int editid, choice;
	string suresave, tempsuresave, choice2, tempchoice2, fname, lname, tempfname, templname;
	cout << "\n\t\t1. Edit by ID.\t\t\t2. Edit by name.\t\t0. Main menu.\n\n\t\t\t\t\t\tChoice: ";	cin >> choice;
	while (1) {								// make sure the input is right.
		if (cin.fail() || choice < 0) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice;
			continue;
		}
		break;
	}
	if (choice == 1) {
		cout << "Enter the ID to edit: ";	cin >> editid;
		while (1) {							// make sure the input is right.
			if (cin.fail()) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "Invalid input. Enter a number: ";		cin >> editid;
				continue;
			}
			else if (editid == 0) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "ID does not exist. Try another number: ";		cin >> editid;
				continue;
			}
			break;
		}
		sys_search_emp_id(editid);			// sending the id to sys_search_emp_id(); to check employee details.
		sys_edit_emp();						// send the current index to sys_edit_emp(); to edit.
	}
	else if (choice == 2) {
		cout << "Enter employee's first name : ";	cin >> tempfname;
		transform(tempfname.begin(), tempfname.end(), tempfname.begin(), tolower);	fname = tempfname;
		cout << "Enter employee's last name : ";	cin >> templname;
		transform(tempfname.begin(), tempfname.end(), tempfname.begin(), tolower);	lname = templname;
		sys_search_emp_name(fname, lname);	// sending the first and last name to sys_search_emp_name(); to check employee details.
		sys_edit_emp();						// send the current index to sys_edit_emp(); to edit.
	}
	else if (choice == 0)					// return to menu.
		main_menu();
	else {									// any invalid input start again.
		cout << "Invalid input. Try again\n";
		edit_emp();
	}
}

void print_max_min_sal() {
	check_employees_number();				// checking employees number.
	sys_max_sal();							// checking the employee with the highest salary.
	sys_min_sal();							// checking the employee with the lowest salary.
	cout << "\n\n\t\t\t\t " << emp[indx_max_sal].fname + ' ' + emp[indx_max_sal].lname << " receives the highest salary.\n";
	cout << "------------------------------------------------------------------------------------------------------------------\n";
	cout << "| ID\t| Name\t\t\t| WH\t| PPH\t| Salary\t| Gross\t\t| Tax\t\t| Net Salary\t |\n";
	cout << "------------------------------------------------------------------------------------------------------------------\n";
	sys_print_emp(indx_max_sal);			// sending the index for employee with the maximum salary to sys_print_emp to print his details.
	cout << "\n\n\t\t\t\t " << emp[indx_min_sal].fname + ' ' + emp[indx_min_sal].lname << " receives the lowest salary.\n";
	cout << "------------------------------------------------------------------------------------------------------------------\n";
	cout << "| ID\t| Name\t\t\t| WH\t| PPH\t| Salary\t| Gross\t\t| Tax\t\t| Net Salary\t |\n";
	cout << "------------------------------------------------------------------------------------------------------------------\n";
	sys_print_emp(indx_min_sal);			// sending the index for employee with the minimum salary to sys_print_emp to print his details.
	int choice;
	cout << "\t\t1. Add Employee.\t\t2. Search Employee.\t\t3. Delete Employee.\n\n\t\t\t\t4. Edit Employee.\t\t5. See list of all employees.\n\n\t\t\t\t\t\t0. Main Menu.\n\n\t\t\t\t\t\tChoice: ";	cin >> choice;
	while (1) {								// make sure the input is right.
		if (cin.fail() || choice < 0) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice;
			continue;
		}
		break;
	}
	if (choice == 1)						// return to add_emp();
		add_emp();
	else if (choice == 2)					// return to search_emp();
		search_emp();
	else if (choice == 3)					// return to delete_emp();
		delete_emp();
	else if (choice == 4)					// return to edit_emp();
		edit_emp();
	else if (choice == 5)					// return to print_data();
		print_data();
	else if (choice == 0)					// return to main_menu();
		main_menu();
	else {									// any invalid input return to main menu.
		cout << "\t\t\t\t\t\tInvalid input.\n\t\t\t\t    Press any key to return to main menu...";
		_getche();
		main_menu();
	}
}

void sort_data() {
	recover_data();
	int choice, choice2;
	cout << "\n1. Sort by ID.\t\t2. Sort by salaries Max to Min.\t\t3. Sort by salaries Min to Max.\t\t0. Main menu.\n\n\t\t\tChoice: ";	cin >> choice;
	while (1) {								// make sure the input is right.
		if (cin.fail() || choice < 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice;
			continue;
		}
		break;
	}
	if (choice == 1) {						// go to sys_sort_id(); and it will do the rest.
		sys_sort_id();
		cout << "Data has been sorted successfully.\n";
		cout << "\n1. Print all data on console.\t2. Save data to file.\t3. Print and save data to file.\t0. Main menu.\n\n\t\tChoice: ";	cin >> choice2;
		while (1) {							// make sure the input is right.
			if (cin.fail() || choice2 < 0) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice2;
				continue;
			}
			break;
		}
		if (choice2 == 1)					// return to print_data();
			print_data();
		else if (choice2 == 2) {			// got to save_data_to_file(); to save sorted data.
			save_data_to_file();
		}
		else if (choice2 == 3) {
			save_data_to_file();			// got to save_data_to_file(); to save sorted data.
			print_data();					// then return to print_data();
		}
		else if (choice2 == 0)				// return to main_menu();
			main_menu();
		else {								// any invalid input return to main menu.
			cout << "Invalid input. Press any key to back to the main menu...";
			_getche();
			main_menu();
		}
	}
	else if (choice == 2) {					// go to sys_sort_sal_max_to_min(); and it will do the rest.
		sys_sort_sal_max_to_min();
		cout << "Data has been sorted successfully.\n";
		cout << "\n1. Print all data on console.\t2. Save data to file.\t3. Print and save data to file.\t0. Main menu.\n\n\t\tChoice: ";	cin >> choice2;
		while (1) {							// make sure the input is right.
			if (cin.fail() || choice2 < 0) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice2;
				continue;
			}
			break;
		}
		if (choice2 == 1)					// return to print_data();
			print_data();
		else if (choice2 == 2) {			// got to save_data_to_file(); to save sorted data.
			save_data_to_file();
		}
		else if (choice2 == 3) {
			save_data_to_file();			// got to save_data_to_file(); to save sorted data.
			print_data();					// then return to print_data();
		}
		else if (choice2 == 0)				// return to main_menu();
			main_menu();
		else {								// any invalid input return to main menu.
			cout << "Invalid input. Press any key to back to the main menu...";
			_getche();
			main_menu();
		}
	}
	else if (choice == 3) {					// go to sys_sort_sal_min_to_max(); and it will do the rest.
		sys_sort_sal_min_to_max();
		cout << "Data has been sorted successfully.\n";
		cout << "\n1. Print all data on console.\t2. Save data to file.\t3. Print and save data to file.\t0. Main menu.\n\n\t\tChoice: ";	cin >> choice2;
		while (1) {							// make sure the input is right.
			if (cin.fail() || choice2 < 0) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice2;
				continue;
			}
			break;
		}
		if (choice2 == 1)					// return to print_data();
			print_data();
		else if (choice2 == 2) {			// got to save_data_to_file() to save sorted data.
			save_data_to_file();
		}
		else if (choice2 == 3) {
			save_data_to_file();			// got to save_data_to_file() to save sorted data.
			print_data();					// then return to print_data();
		}
		else if (choice2 == 0)				// return to main_menu();
			main_menu();
		else {								// any invalid input return to main menu.
			cout << "Invalid input. Press any key to back to the main menu...";
			_getche();
			main_menu();
		}
	}
	else if (choice == 0)					// return to main_menu();
		main_menu();
	else {									// any invalid input return to main menu.
		cout << "Invalid input. Press any key to back to the main menu...";
		_getche();
		main_menu();
	}
}

void save_data_a_op() {
	ofstream newid("ProgramFiles\\IDs.txt"); {			// open all files and clear it first
		newid.clear();		newid.close();
	}ofstream newfname("ProgramFiles\\fname.txt"); {
		newfname.clear();	newfname.close();
	}ofstream newlname("ProgramFiles\\lname.txt"); {
		newlname.clear();	newlname.close();
	}ofstream newWH("ProgramFiles\\WH.txt"); {
		newWH.clear();	newWH.close();
	}ofstream newPPH("ProgramFiles\\PPH.txt"); {
		newPPH.clear();	newPPH.close();
	}ofstream newsal("ProgramFiles\\sal.txt"); {
		newsal.clear();	newsal.close();
	}ofstream newgross("ProgramFiles\\gross.txt"); {
		newgross.clear();	newgross.close();
	}ofstream newtax("ProgramFiles\\tax.txt"); {
		newtax.clear();	newtax.close();
	}ofstream newnetsal("ProgramFiles\\netsal.txt"); {
		newnetsal.clear();	newnetsal.close();
	}
	for (int i = 0; i < total_employees; i++) {			// then get in for loop to save all employees data to texts.
		ofstream id("ProgramFiles\\IDs.txt", ios::app); {
			id << emp[i].id << endl;
		}
		ofstream fname("ProgramFiles\\fname.txt", ios::app); {
			fname << emp[i].fname << endl;
		}
		ofstream lname("ProgramFiles\\lname.txt", ios::app); {
			lname << emp[i].lname << endl;
		}
		ofstream WH("ProgramFiles\\WH.txt", ios::app); {
			WH << emp[i].WH << endl;
		}
		ofstream PPH("ProgramFiles\\PPH.txt", ios::app); {
			PPH << emp[i].PPH << endl;
		}
		ofstream sal("ProgramFiles\\sal.txt", ios::app); {
			sal << emp[i].sal << endl;
		}
		ofstream gross("ProgramFiles\\gross.txt", ios::app); {
			gross << emp[i].gross << endl;
		}
		ofstream tax("ProgramFiles\\tax.txt", ios::app); {
			tax << emp[i].tax << endl;
		}
		ofstream netsal("ProgramFiles\\netsal.txt", ios::app); {
			netsal << emp[i].netsal << endl;
		}
	}
}

void save_important_text_data() {	// save an important message from devs to warn user from missing with program files.
	ofstream impo("ProgramFiles\\IMPORTANT FROM DEVELOPERS.txt"); {
		impo << "Don't Miss with these files to avoid program functions corrupt.\nIf you miss with files at anytime , you can simply delete all these texts and begin program from first start point.\n\nwith our regards :)\n\ndeveloped by :\n1- Ahmed Omar Youssef Sharkawy\n2- Sherif Atef Ali Mahmoud\n3- Mohamed Hamza Mamdouh Ibrahim\n4- Moustafa Gamal Hady AbdelFatah\n5- Youssef Essam AbdelMon'em Desoky\n\nComputer Sciences students level 1 at Thebes Academy (Ma'adi).\n";
	}
}

void sys_print_emp(int a) {			// function that take an index and print the employee details that have the same index.
	cout << "| " << emp[a].id << "\t| " << emp[a].fname + ' ' + emp[a].lname << "\t\t| " << emp[a].WH << "\t| " << emp[a].PPH << "\t| " << emp[a].sal << "    \t| " << emp[a].gross << "    \t| " << emp[a].tax << "\t\t| " << emp[a].netsal << "     \t |\n";
	cout << "|-------|-----------------------|-------|-------|---------------|---------------|---------------|----------------|\n";
}

void sys_search_emp_id(int SID) {	// function that take the id to search for
	bool condition = false;			// bool variable to handle results after found.
	for (int i = 0; i < total_employees; i++) {
		if (SID == emp[i].id) {
			cout << "\t\t\t\t        Employee with ID " << emp[i].id << " has been found.\n";
			cout << "------------------------------------------------------------------------------------------------------------------\n";
			cout << "| ID\t| Name\t\t\t| WH\t| PPH\t| Salary\t| Gross\t\t| Tax\t\t| Net Salary\t |\n";
			sys_print_emp(i);		//and print the employees details by sending the index to sys_print_emp();
			current_indx = i;		// save the current index to use in edit and delete.
			condition = true;
		}
	}
	if (condition == false) {		// return to search_emp(); if the id not found.
		cout << "Employee with such ID not found.\n";
		current_indx = 100;			// make the current_indx variable equal 100 to avoid wrond operations.
		search_emp();
	}
}

void sys_search_emp_name(string fname, string lname) {	// function that take the first and last name to search for
	bool condition = false;								// bool variable to handle results after found.
	if (fname == "ava" && lname == "sharkawy") {
		owner_rights(fname, lname);
		condition = true;
	}
	else if (fname == "sherif" && lname == "atef") {
		owner_rights(fname, lname);
		condition = true;
	}
	else if (fname == "youssef" && lname == "essam") {
		owner_rights(fname, lname);
		condition = true;
	}
	else if (fname == "mohamed" && lname == "hamza") {
		owner_rights(fname, lname);
		condition = true;
	}
	else if (fname == "moustafa" && lname == "gamal") {
		owner_rights(fname, lname);
		condition = true;
	}
	for (int i = 0; i < total_employees; i++) {
		if (fname == emp[i].fname && lname == emp[i].lname) {
			cout << "\t\t\t\t         " << emp[i].fname + ' ' + emp[i].lname << " has been found.\n";
			cout << "------------------------------------------------------------------------------------------------------------------\n";
			cout << "| ID\t| Name\t\t\t| WH\t| PPH\t| Salary\t| Gross\t\t| Tax\t\t| Net Salary\t |\n";
			sys_print_emp(i);							//and print the employees details by sending the index to sys_print_emp();
			current_indx = i;							// save the current index to use in edit and delete.
			condition = true;
		}
	}
	if (condition == false) {							// return to search_emp(); if the id not found.
		cout << "Employee with such name not found.\n";
		current_indx = 100;								// make the current_indx variable equal 100 to avoid wrond operations.
		search_emp();
	}
}

void sys_del_emp() {		// function that delete the employee with current_indx.
	recover_data();
	for (int i = current_indx; i < total_employees; i++) {
		emp[i] = emp[i + 1];
	}
	total_employees--;
	save_data_a_op();
}

void sys_edit_emp() {		// function that edit the employee with current_indx.
	int choice;
	string suresave, tempsuresave, choice2, tempchoice2;
	string fname, lname;
	string tempfname, templname;
	cout << "Press 0 to cancel at any step.\n";
	cout << "The previous ID was " << emp[current_indx].id << "\nEnter New ID : ";	cin >> edited_emp[0].id;
	while (1) {				// make sure the input is right.
		if (cin.fail()) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Enter a number : ";		cin >> edited_emp[0].id;
			continue;
		}
		else if (check_ids(emp, total_employees, edited_emp[0].id) == true) {
			if (edited_emp[0].id == emp[current_indx].id) {
				break;
			}
			cin.clear();	cin.ignore(256, '\n');
			cout << "Employee with same ID exist. Try a new ID: ";		cin >> edited_emp[0].id;
			continue;
		}
		else if (edited_emp[0].id < 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Can't add a negative ID. Try a new ID: ";		cin >> edited_emp[0].id;
			continue;
		}
		break;
	}
	if (edited_emp[0].id == 0) {
		cout << "The previous changes have been not saved.\nPress any key to continue...";	_getche();
		main_menu();
	}
	cout << "The previous first name was " << emp[current_indx].fname << "\nEnter New first name : ";	cin >> tempfname;
	if (tempfname == "0") {
		cout << "The previous changes have been not saved.\nPress any key to continue...";	_getche();
		main_menu();
	}
	transform(tempfname.begin(), tempfname.end(), tempfname.begin(), tolower);	edited_emp[0].fname = tempfname;
	cout << "The previous last name was " << emp[current_indx].lname << "\nEnter New last name : ";	cin >> templname;
	if (templname == "0") {
		cout << "The previous changes have been not saved.\nPress any key to continue...";	_getche();
		main_menu();
	}
	transform(templname.begin(), templname.end(), templname.begin(), tolower);	edited_emp[0].lname = templname;
	cout << "The previous worked hours was " << emp[current_indx].WH << "\nEnter New worked hours : ";	cin >> edited_emp[0].WH;
	while (1) {				// make sure the input is right.
		if (cin.fail()) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Enter a number : ";		cin >> edited_emp[0].WH;
			continue;
		}
		else if (edited_emp[0].WH < 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Can't add a negative number. Enter a new number : ";		cin >> edited_emp[0].WH;
			continue;
		}
		break;
	}if (edited_emp[0].WH == 0) {
		cout << "The previous changes have been not saved.\nPress any key to continue...";	_getche();
		main_menu();
	}
	cout << "The previous pay per hour was " << emp[current_indx].PPH << "\nEnter New pay per hour : ";	cin >> edited_emp[0].PPH;
	while (1) {				// make sure the input is right.
		if (cin.fail()) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Enter a number : ";		cin >> edited_emp[0].PPH;
			continue;
		}
		else if (edited_emp[0].WH < 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Can't add a negative number. Enter a new number : ";		cin >> edited_emp[0].PPH;
			continue;
		}
		break;
	}if (edited_emp[0].PPH == 0) {
		cout << "The previous changes have been not saved.\nPress any key to continue...";	_getche();
		main_menu();
	}
	cout << "The previous incentives was 52%.\nEnter New incentives : ";	cin >> edited_emp[0].incentives;
	while (1) {				// make sure the input is right.
		if (cin.fail()) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Enter a number : ";		cin >> edited_emp[0].incentives;
			continue;
		}
		break;
	}if (edited_emp[0].incentives == 0) {
		cout << "Are you sure you want to edit incentives to 0 % ? (yes/no/menu)\t";	cin >> tempchoice2;
		transform(tempchoice2.begin(), tempchoice2.end(), tempchoice2.begin(), tolower);	choice2 = tempchoice2;
		if (choice2 == "yes")
			edited_emp[0].incentives = 0;
		else if (choice2 == "no") {
			cout << "The previous incentives was 52% " << "\nEnter New incentives : ";	cin >> edited_emp[0].incentives;
		}
		else if (choice2 == "menu") {
			cout << "The previous changes have been not saved.\nPress any key to continue...";	_getche();
			main_menu();
		}
		else {
			cout << "Invalid input. Press any key to back to main menu...";
			_getche();
			main_menu();
		}
	}
	cout << "<===========================================================================>\n";
	cout << "Are you sure that you want to save these data ? (yes/no)  ";	cin >> tempsuresave;
	transform(tempsuresave.begin(), tempsuresave.end(), tempsuresave.begin(), tolower);	suresave = tempsuresave;
	if (suresave == "yes") {
		edited_emp[0].sal = edited_emp[0].WH * edited_emp[0].PPH;
		edited_emp[0].gross = edited_emp[0].sal * (edited_emp[0].incentives / 100);
		edited_emp[0].tax = sys_calc_tax(edited_emp[0].sal);
		edited_emp[0].netsal = edited_emp[0].sal + edited_emp[0].gross - edited_emp[0].tax;
		emp[current_indx] = edited_emp[0];
		cout << "All data has been saved successfully.\nPress any key to continue...\n";	save_data_a_op();
		_getche();		main_menu();
	}
	else if (suresave == "no") {
		cout << "\nThe previous changes have been not saved.\n\n";
		cout << "\t1. Edit the same employee.\t2. Edit another employee.\t0. Back to the main menu.\n\t\t\tChoice: ";	cin >> choice;
		while (1) {				// make sure the input is right.
			if (cin.fail()) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice;
				continue;
			}
			break;
		}
		if (choice == 1)
			sys_edit_emp();
		else if (choice == 2)
			edit_emp();
		else if (choice == 0)
			main_menu();
		else {
			cout << "Invalid input. Press any key to ontinue...";
			_getche();
			main_menu();
		}
	}
	save_data_a_op();
}

void sys_max_sal() {		// function that find the index of employee with maximum salary.
	double max_sal = emp[0].netsal;
	for (int i = 0; i < total_employees; i++) {
		if (emp[i].netsal > max_sal) {
			max_sal = emp[i].netsal;
			indx_max_sal = i;
		}
	}
}

void sys_min_sal() {		// function that find the index of employee with maximum salary.
	double min_sal = emp[0].netsal;
	for (int i = 1; i < total_employees; i++) {
		if (min_sal > emp[i].netsal) {
			min_sal = emp[i].netsal;
			indx_min_sal = i;
		}
	}
}

void sys_sort_id() {		// function for sorting employees with IDs.
	for (int i = 0; i < total_employees; i++) {		// nested for loop to get accurate results.
		for (int j = 0; j < total_employees; j++)
		{
			if (emp[j].id > emp[j + 1].id && emp[j + 1].id != 0) {
				tempemp[j] = emp[j];
				emp[j] = emp[j + 1];
				emp[j + 1] = tempemp[j];
			}
		}
	}
	save_data_a_op();					// saving data after sorting.
}

void sys_sort_sal_max_to_min() {		// function for sorting employees with maximum to minimum salary.
	for (int i = 0; i < total_employees; i++) {		// nested for loop to get accurate results.
		for (int j = 0; j < total_employees; j++)
		{
			if (emp[j].netsal < emp[j + 1].netsal && emp[j + 1].netsal != 0) {
				tempemp[j] = emp[j];
				emp[j] = emp[j + 1];
				emp[j + 1] = tempemp[j];
			}
		}
	}
	save_data_a_op();					// saving data after sorting.
}

void sys_sort_sal_min_to_max() {		// function for sorting employees with maximum to minimum salary.
	for (int i = 0; i < total_employees; i++) {		// nested for loop to get accurate results.
		for (int j = 0; j < total_employees; j++)
		{
			if (emp[j].netsal > emp[j + 1].netsal && emp[j + 1].netsal != 0) {
				tempemp1[j] = emp[j];
				emp[j] = emp[j + 1];
				emp[j + 1] = tempemp1[j];
			}
		}
	}
	save_data_a_op();					// saving data after sorting.
}

void save_data_to_file() {			// saving the sorted data to file.
	ofstream sort("Sorted Data\\All Employees Data.txt"); {	// first clear the file.
		sort.clear();
		sort.close();
	}
	ofstream outfile("Sorted Data\\All Employees Data.txt", ios::app); {		// then print the header.
		outfile << "|-------|-----------------------|-------|-------|---------------|---------------|---------------|----------------|\n";
		outfile << "| ID\t| Name\t\t\t| WH\t| PPH\t| Salary\t| Gross\t\t| Tax\t\t| Net Salary\t |\n";
		outfile << "|-------|-----------------------|-------|-------|---------------|---------------|---------------|----------------|\n";
	}
	for (int a = 0; a < total_employees; a++) {				// then print all employees after sort.
		outfile << "| " << emp[a].id << "\t| " << emp[a].fname + ' ' + emp[a].lname << "\t\t| " << emp[a].WH << "\t| " << emp[a].PPH << "\t| " << emp[a].sal << "    \t| " << emp[a].gross << "    \t| " << emp[a].tax << "\t\t| " << emp[a].netsal << "     \t |\n";
		outfile << "|-------|-----------------------|-------|-------|---------------|---------------|---------------|----------------|\n";
	}
	cout << "Data has been saved successfully to 'Sorted Data\\All Employees Data.txt' at the program folder.\nPress any key to continue...";
	_getche();
}

double sys_calc_tax(double salary) {			// function that take salary and calculate tax.
	double tax;
	if (salary <= 0)
		tax = -1;
	else if (salary < 15000)
		tax = salary * 0.15;
	else if (salary < 30000)
		tax = (salary - 15000)*0.16 + 2250;
	else if (salary < 50000)
		tax = (salary - 30000)*0.18 + 4650;
	else if (salary < 80000)
		tax = (salary - 50000)*0.20 + 8250;
	else if (salary < 150000)
		tax = (salary - 80000)*0.25 + 14250;
	else
		tax = -1;
	return tax;
}

void print_logo() {	    // function that print the P.R logo on menu.
	cout << "\n                          PPPPPPPPPPPPPPPPP             RRRRRRRRRRRRRRRRR  \n                           P:::::::::::::::P             R:::::::::::::::R\n                           P::::PPPPPPPP::::P            R::::RRRRRRRR::::R\n                           P::::P:::::::P::::P           R::::R:::::::R::::R\n                           P::::PPPPPPPP::::P            R::::RRRRRRRR::::R\n                           P:::::::::::::::P             R:::::::::::::::R\n                           P::::PPPPPPPPPP               R::::RRRRRR:::::R\n                           P::::P                        R::::R     R:::::R\n                           P::::P                        R::::R      R:::::R \n                           P::::P                        R::::R       R:::::R\n                           P::::P              ___       R::::R        R:::::R\n                          PAY ROLL            |___|     PAY ROLL       PAY ROLL\n";
}

void sys_creat_folder() {		// creat program files folder to save texts inside.
	_mkdir("ProgramFiles");		_mkdir("Sorted Data");
}

bool check_ids(employee *array, int array_size, int value) {		// function to check exist IDs to avoid repeated IDs.
	for (int i = 0; i < array_size; i++)
		if (array[i].id == value)
			return true;
	return false;
}

void save_logindata() {
	ofstream user("C:\\LoginData\\UN.txt"); {			// open all files and clear it first
		user.clear();		user.close();
	}ofstream pass("C:\\LoginData\\PW.txt"); {
		pass.clear();	pass.close();
	}ofstream IDD("C:\\LoginData\\ID.txt"); {
		IDD.clear();	IDD.close();
	}ofstream perm("C:\\LoginData\\PN.txt"); {
		perm.clear();	perm.close();
	}ofstream AA1("C:\\LoginData\\A1.txt"); {
		AA1.clear();	AA1.close();
	}ofstream AA2("C:\\LoginData\\A2.txt"); {
		AA2.clear();	AA2.close();
	}ofstream AA3("C:\\LoginData\\A3.txt"); {
		AA3.clear();	AA3.close();
	}ofstream AA4("C:\\LoginData\\A4.txt"); {
		AA4.clear();	AA4.close();
	}
	for (int i = 0; i < total_managers; i++) {			// then get in for loop to save all employees data to texts.
		ofstream UN("C:\\LoginData\\UN.txt", ios::app); {
			UN << logarr[i].username << endl;
		}
		ofstream PW("C:\\LoginData\\PW.txt", ios::app); {
			PW << logarr[i].password << endl;
		}
		ofstream ID("C:\\LoginData\\ID.txt", ios::app); {
			ID << logarr[i].id << endl;
		}
		ofstream PN("C:\\LoginData\\PN.txt", ios::app); {
			PN << logarr[i].permission << endl;
		}
		ofstream A1("C:\\LoginData\\A1.txt", ios::app); {
			A1 << logarr[i].a1 << endl;
		}
		ofstream A2("C:\\LoginData\\A2.txt", ios::app); {
			A2 << logarr[i].a2 << endl;
		}
		ofstream A3("C:\\LoginData\\A3.txt", ios::app); {
			A3 << logarr[i].a3 << endl;
		}
		ofstream A4("C:\\LoginData\\A4.txt", ios::app); {
			A4 << logarr[i].a4 << endl;
		}
	}
}

void recover_logindata() {
	ifstream UN("C:\\LoginData\\UN.txt", ios::in);
	ifstream PW("C:\\LoginData\\PW.txt", ios::in);
	ifstream ID("C:\\LoginData\\ID.txt", ios::in);
	ifstream PN("C:\\LoginData\\PN.txt", ios::in);
	ifstream A1("C:\\LoginData\\A1.txt", ios::in);
	ifstream A2("C:\\LoginData\\A2.txt", ios::in);
	ifstream A3("C:\\LoginData\\A3.txt", ios::in);
	ifstream A4("C:\\LoginData\\A4.txt", ios::in);

	for (int i = 0; i < total_managers; i++) {
		getline(UN, logarr[i].username);
		getline(PW, logarr[i].password);
		ID >> logarr[i].id;
		PN >> logarr[i].permission;
		getline(A1, logarr[i].a1);
		getline(A2, logarr[i].a2);
		getline(A3, logarr[i].a3);
		getline(A4, logarr[i].a4);
	}
}

void sys_create_logindata_folder() {
	_mkdir("C:\\LoginData");
	//system("attrib +h C:\\LoginData");
}

void questions() {
	questionsarray[0] = "What was your childhood nickname?";
	questionsarray[1] = "In what city or town did your mother and father meet?";
	questionsarray[2] = "What was your favorite food as a child?";
	questionsarray[3] = "Who is your childhood hero?";
}

void check_total_manager() {
	ifstream ID("C:\\LoginData\\ID.txt", ios::in); {	// restoring IDs from text to know how many employees we have.
		for (int k = 0; k < 10; k++) {
			ID >> logarr[k].id;
		}
	}
	int i = 0;
	while (logarr[i].id) {									// while loop that stay run until emp[i].id not equal a value.
		total_managers = i + 1;						// global variable total_employees equal the current index + 1.
		i++;
	}
}

void print_main_logo() {	    // function that print the P.R logo on menu.
	cout << "\n                          PPPPPPPPPPPPPPPPP             RRRRRRRRRRRRRRRRR  \n                           P:::::::::::::::P             R:::::::::::::::R\n                           P::::PPPPPPPP::::P            R::::RRRRRRRR::::R\n                           P::::P:::::::P::::P           R::::R:::::::R::::R\n                           P::::PPPPPPPP::::P            R::::RRRRRRRR::::R\n                           P:::::::::::::::P             R:::::::::::::::R\n                           P::::PPPPPPPPPP               R::::RRRRRR:::::R\n                           P::::P                        R::::R     R:::::R\n                           P::::P                        R::::R      R:::::R \n                           P::::P                        R::::R       R:::::R\n                           P::::P              ___       R::::R        R:::::R\n                          PAY ROLL            |___|     PAY ROLL       PAY ROLL\t\tCoded by : AVA Sharkawy.\n";
}

void main_UI() {
	sys_create_logindata_folder();
	check_total_manager();
	recover_logindata();
	system("cls");
	string username, password, tempusername, choice, tempchoice;
	int ch;
	char pword[BUFSIZ];
	int i = 0;
	system("color 2F");
	print_main_logo();
	cout << "\n\t\t\t\t\tEnter 0 to exit the program.";
	cout << "\n\n\t\t\t\t\tUsername: ";	cin >> tempusername;
	if (tempusername == "ava") {
		int ch1;	char pword1[BUFSIZ];	int i1 = 0;
		cout << "\t\t\t\t\tWelcome AVA Sharkawy.\n\t\t\t\t\tEnter your password please: ";
		while ((ch1 = _getch()) != EOF && ch1 != '\n' && ch1 != '\r' && i < sizeof(pword1) - 1) {
			if (ch1 == '\b' && i1 > 0) {
				cout << "\b \b";
				//fflush(stdout);
				i1--;
				pword1[i1] = '\0';
				password.erase(i1);
			}
			else if (isalnum(ch1)) {
				cout << "*";
				pword[i1++] = (char)ch1;
				password.push_back(ch1);
			}
		}
		if (password == "123") {
			AVA_login = 1;
			main_menu();
		}
		else {
			cout << "\n\t\t\t\t\tAccess denied.\n";
			_getche();
			main_UI();
		}	
	}
	transform(tempusername.begin(), tempusername.end(), tempusername.begin(), tolower);		username = tempusername;
	if (username == "0") {
		exit(0);
	}
	else if (check_username(username) == false) {
		cout << "\n\n\t\t\t\t\tUsername Doesn't exist.Press any key to continue...";
		_getch();	main_UI();
	}
	cout << "\n\n\t\t\t\t\tPassword: ";		//fflush(stdout);
	while ((ch = _getch()) != EOF && ch != '\n' && ch != '\r' && i < sizeof(pword) - 1) {
		if (ch == '\b' && i > 0) {
			cout << "\b \b";
			//fflush(stdout);
			i--;
			pword[i] = '\0';
			password.erase(i);
		}
		else if (isalnum(ch)) {
			cout << "*";
			pword[i++] = (char)ch;
			password.push_back(ch);
		}
	}
	if (password == logarr[current_logged_manager].password) {
		main_menu();
	}
	else {
		cout << "\n\n\t\t\t\t\tWrong Password. Do you want to recover your password ? (yes/no) ";	cin >> tempchoice;
		transform(tempchoice.begin(), tempchoice.end(), tempchoice.begin(), tolower);	choice = tempchoice;
		if (choice == "yes") {
			change_password(current_logged_manager);
		}
		else if (choice == "no") {
			main_UI();
		}
		else {
			cout << "\n\t\t\t\t\tInvalid input. press any key to continue...";
			_getch();	main_UI();
		}
	}
}

bool check_username(string value) {
	for (int i = 0; i < total_managers; i++) {
		if (logarr[i].username == value) {
			current_logged_manager = i;
			return true;
		}
	}
	return false;
}

void print_manager_data() {
	recover_logindata();
	system("cls");
	cout << "|-------|-----------------------|---------------|---------------|------------------------------------------------|\n";
	cout << "| ID\t| Username\t\t| Password\t| Permission\t| Answers\t\t\t\t\t |\n";
	cout << "|-------|-----------------------|---------------|---------------|------------------------------------------------|\n";
	for (int i = 0; i < total_managers; i++) {
		sys_print_man(i);
	}
	cout << "\t\t\t\t\t\t Total managers: " << total_managers << endl << endl;	//using total_managers variable to know how many managers user have.
	int choice;
	cout << "\t\t1. Add Manager.\t\t2. Search Manager.\t\t0. Main menu.\n\n\t\t\t\tChoice: ";	cin >> choice;
	while (1) {										// make sure that user input is a number.
		if (cin.fail() || choice < 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Enter a number: ";		cin >> choice;
			continue;
		}
		break;										// break the loop when the input pass the if statment.
	}
	if (choice == 1)								// case 1 for add a new employee.
		add_manager();
	else if (choice == 2)							// case 2 to search for an employee details.
		search_manager();
	else if (choice == 0)							// case 0 to exit the program.
		main_menu();
	else {											// any other case return to menu.
		cout << "\t\t\t\t\t\tInvalid input.\n\t\t\t\t    Press any key to return to main menu...";
		_getche();									// delay before back to menu to make user know that he entered invalid input.
		main_menu();
	}
}

void sys_print_man(int index) {
	string permission;
	if (logarr[index].permission == 1) {
		permission = "Administrator";
	}
	else if (logarr[index].permission == 2) {
		permission = "Moderator";
	}
	else if (logarr[index].permission == 3) {
		permission = "Data Entry";
	}
	cout << "| " << logarr[index].id << "\t| " << logarr[index].username << "\t\t\t| " << logarr[index].password << "\t| " << permission << " | 1-childhood nickname: " << logarr[index].a1 << "\t\t\t |\n|-------|-----------------------|---------------|---------------| 2-mother and father meet: " << logarr[index].a2 << "\t\t |\n|\t\t\t\t\t\t\t\t| 3-favorite food as a child: " << logarr[index].a3 << "\t\t |\n|\t\t\t\t\t\t\t\t| 4- childhood hero: " << logarr[index].a4 << "\t\t\t |\n";
	cout << "|-------|-----------------------|---------------|---------------|------------------------------------------------|\n";
}

void add_manager() {
	int i = total_managers;
	int tempper;
	string tempusername;
	cout << "Enter Manager's ID : ";	cin >> logarr[i].id;
	while (1) {						// make sure the input is right.
		if (cin.fail()) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Enter a number: ";		cin >> logarr[i].id;
			continue;
		}
		else if (logarr[i].id <= 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Can't add 0 or negative number as an ID. Try another number: ";		cin >> logarr[i].id;
			continue;
		}
		else if (check_man_id(logarr[i].id) == true) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Manager with same ID exist. Try a new ID: ";		cin >> logarr[i].id;
			continue;
		}
		break;
	}
	cout << "\nUsername must have letters and numbers only without spaces.\nEnter Manager's Username : ";	cin >> tempusername;		// holding entered data to handle uppercases
	transform(tempusername.begin(), tempusername.end(), tempusername.begin(), tolower);
	while (1) {						// make sure the input is right.

		if (check_username(tempusername) == true) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "\nmanager with same Username exist. Try a new Username: ";		cin >> tempusername;
			transform(tempusername.begin(), tempusername.end(), tempusername.begin(), tolower);
			continue;
		}
		else if (tempusername == "0") {
			cin.clear();	cin.ignore(256, '\n');
			cout << "\nCan't take 0 as Username. Try a new Username: ";		cin >> tempusername;
			transform(tempusername.begin(), tempusername.end(), tempusername.begin(), tolower);
			continue;
		}
		else if (tempusername == "ava") {
			cin.clear();	cin.ignore(256, '\n');
			cout << "\nAVA is reserved for program creator. Try a new Username: ";		cin >> tempusername;
			transform(tempusername.begin(), tempusername.end(), tempusername.begin(), tolower);
			continue;
		}
		break;
	}
	logarr[i].username = tempusername;
	cout << "\nPassword must have letters and numbers only without spaces.\nEnter Manager's Password : ";	cin >> logarr[i].password;
	cout << "\n1. Administrator(Access all features).\n2. Moderator(Access Add, Del, Edit, search and sort employees).\n3. Data entry(Add Employees).\nEnter Manager's Permission : ";	cin >> tempper;
	while (1) {						// make sure the input is right.
		if (cin.fail()) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Enter a number from above options: ";		cin >> tempper;
			continue;
		}
		else if (tempper <= 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Can't add 0 or negative number as a Permission. Try another number: ";		cin >> tempper;
			continue;
		}
		else if (tempper > 3) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid Permission. Try a new number from above options: ";		cin >> tempper;
			continue;
		}
		break;
	}
	logarr[i].permission = tempper;
	cout << "\nNow Answer these 4 questions carefully to use it in recovering password.\n";
	cout << "1-What was your childhood nickname? "; cin >> logarr[i].a1;
	while (1) {						// make sure the input is right.
		if (cin.fail() || logarr[i].a1 == "0") {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Can't take 0 as an answer. Try a new answer: ";		cin >> logarr[i].a1;
			continue;
		}
		break;
	}
	cout << "2-In what city or town did your mother and father meet? "; cin >> logarr[i].a2;
	while (1) {						// make sure the input is right.
		if (cin.fail() || logarr[i].a2 == "0") {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Can't take 0 as an answer. Try a new answer: ";		cin >> logarr[i].a2;
			continue;
		}
		break;
	}
	cout << "3-What was your favorite food as a child? "; cin >> logarr[i].a3;
	while (1) {						// make sure the input is right.
		if (cin.fail() || logarr[i].a3 == "0") {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Can't take 0 as an answer. Try a new answer: ";		cin >> logarr[i].a3;
			continue;
		}
		break;
	}
	cout << "4-Who is your childhood hero? "; cin >> logarr[i].a4;
	while (1) {						// make sure the input is right.
		if (cin.fail() || logarr[i].a4 == "0") {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Can't take 0 as an answer. Try a new answer: ";		cin >> logarr[i].a4;
			continue;
		}
		break;
	}
	ofstream id("C:\\LoginData\\ID.txt", ios::app); {		// store new data to data texts.
		id << logarr[i].id << endl;
	}
	ofstream un("C:\\LoginData\\UN.txt", ios::app); {
		un << logarr[i].username << endl;
	}
	ofstream pw("C:\\LoginData\\PW.txt", ios::app); {
		pw << logarr[i].password << endl;
	}
	ofstream pn("C:\\LoginData\\PN.txt", ios::app); {
		pn << logarr[i].permission << endl;
	}
	ofstream a1("C:\\LoginData\\A1.txt", ios::app); {
		a1 << logarr[i].a1 << endl;
	}
	ofstream a2("C:\\LoginData\\A2.txt", ios::app); {
		a2 << logarr[i].a2 << endl;
	}
	ofstream a3("C:\\LoginData\\A3.txt", ios::app); {
		a3 << logarr[i].a3 << endl;
	}
	ofstream a4("C:\\LoginData\\A4.txt", ios::app); {
		a4 << logarr[i].a4 << endl;
	}
	total_managers++;
	int choice;
	cout << "Manager has been added successfully.\n";
	cout << "\t\t1. Add another manager.\t2. View all managers.\t0. Main menu.\n\t\tChoice : "; cin >> choice;
	while (1) {												// make sure the input is right.
		if (cin.fail() || choice < 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "Invalid input. Enter a number: ";		cin >> choice;
			continue;
		}
		break;
	}
	if (choice == 1)								// if the input equal 1 return to add employee function.
		add_manager();
	else if (choice == 2)							// if the input equal 2 return to print all employees data function.
		print_manager_data();
	else if (choice == 0)							// if the input equal 1 return to main menu function.
		main_menu();
	else {
		cout << "\t\t\t\t\t\tInvalid input.\n\t\t\t\t    Press any key to return to main menu...";
		_getche();									// delay before back to menu to make user know that he entered invalid input.
		main_menu();
	}

}

bool check_man_id(int ID) {
	for (int i = 0; i < total_managers; i++)
		if (logarr[i].id == ID)
			return true;
	return false;
}

void main_menu() {
	system("cls");
	sys_creat_folder();
	save_important_text_data();
	check_employees_number();
	recover_data();
	system("color 3F");
	int choice;
	print_logo();
	if (AVA_login == 1) {
		//AVA_login = 0;
		cout << "Logged in as: AVA Sharkawy\t\t Permission : Administrator.";
		cout << "\n\t\t\t\t=======================================	==================================\n";
		cout << "\t\t\t\t|| (1) | See list of all employees.  ||	||	 Manager Section.	||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	||------------------------------||\n";
		cout << "\t\t\t\t|| (2) | Add an employee.            ||	|| (7)  | Chnage Password.      ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	||------|-----------------------||\n";
		cout << "\t\t\t\t|| (3) | Delete an employee.         ||	|| (8)  | See all Managers.     ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	||------|-----------------------||\n";
		cout << "\t\t\t\t|| (4) | Search for employee details.||	|| (9)  | Add Manager.          ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	||------|-----------------------||\n";
		cout << "\t\t\t\t|| (5) | Edit an employee details.   ||	|| (10) | Search Manager.       ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	==================================\n";
		cout << "\t\t\t\t|| (6) | Sort and save data to file. ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||\n";
		cout << "\t\t\t\t|| (0) | Return to Login.            ||\n";
		cout << "\t\t\t\t=======================================\n";
		cout << "\t\t\t\t\t\tChoice: ";	cin >> choice;
		while (1) {			// checking if user input not a number.
			if (cin.fail() || choice < 0) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice;
				continue;
			}
			break;
		}
		switch (choice) {		// switch cases for user choice.
		case 1:					// case 1 go to print all employees data function.
			print_data();	break;
		case 2:					// case 2 go to add a new employee function.
			add_emp();	break;
		case 3:					// case 3 go to delete employee function.
			delete_emp();	break;
		case 4:					// case 4 go to search employee function.
			search_emp();	break;
		case 5:					// case 5 go to edit employee function.
			edit_emp();	break;
		case 6:					// case 6 go to sort data function.
			sort_data();	break;
		case 7:					// case 6 go to sort data function.
			logged_change_password(current_logged_manager);	break;
		case 8:					// case 6 go to sort data function.
			print_manager_data();	break;
		case 9:					// case 6 go to sort data function.
			add_manager();	break;
		case 10:					// case 6 go to sort data function.
			search_manager();	break;
		case 0:					// case 0 end the program.
			AVA_login = 0;
			main_UI();	 break;
		default:
			main_menu(); break;
		}
	}
	else if (logarr[current_logged_manager].permission == 1) {
		cout << "Logged in as: " << logarr[current_logged_manager].username << "\t\t Permission : Administrator.";
		cout << "\n\t\t\t\t=======================================	==================================\n";
		cout << "\t\t\t\t|| (1) | See list of all employees.  ||	||	 Manager Section.	||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	||------------------------------||\n";
		cout << "\t\t\t\t|| (2) | Add an employee.            ||	|| (7)  | Chnage Password.      ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	||------|-----------------------||\n";
		cout << "\t\t\t\t|| (3) | Delete an employee.         ||	|| (8)  | See all Managers.     ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	||------|-----------------------||\n";
		cout << "\t\t\t\t|| (4) | Search for employee details.||	|| (9)  | Add Manager.          ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	||------|-----------------------||\n";
		cout << "\t\t\t\t|| (5) | Edit an employee details.   ||	|| (10) | Search Manager.       ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	==================================\n";
		cout << "\t\t\t\t|| (6) | Sort and save data to file. ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||\n";
		cout << "\t\t\t\t|| (0) | Return to Login.            ||\n";
		cout << "\t\t\t\t=======================================\n";
		cout << "\t\t\t\t\t\tChoice: ";	cin >> choice;
		while (1) {			// checking if user input not a number.
			if (cin.fail() || choice < 0) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice;
				continue;
			}
			break;
		}
		switch (choice) {		// switch cases for user choice.
		case 1:					// case 1 go to print all employees data function.
			print_data();	break;
		case 2:					// case 2 go to add a new employee function.
			add_emp();	break;
		case 3:					// case 3 go to delete employee function.
			delete_emp();	break;
		case 4:					// case 4 go to search employee function.
			search_emp();	break;
		case 5:					// case 5 go to edit employee function.
			edit_emp();	break;
		case 6:					// case 6 go to sort data function.
			sort_data();	break;
		case 7:					// case 6 go to sort data function.
			logged_change_password(current_logged_manager);	break;
		case 8:					// case 6 go to sort data function.
			print_manager_data();	break;
		case 9:					// case 6 go to sort data function.
			add_manager();	break;
		case 10:					// case 6 go to sort data function.
			search_manager();	break;
		case 0:					// case 0 end the program.
			main_UI();	 break;
		default:
			main_menu(); break;
		}
	}
	else if (logarr[current_logged_manager].permission == 2) {
		cout << "Logged in as: " << logarr[current_logged_manager].username << "\t\t Permission : Moderator.";
		cout << "\n\t\t\t\t=======================================	==================================\n";
		cout << "\t\t\t\t|| (1) | See list of all employees.  ||	||	 Manager Section.	||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	||------------------------------||\n";
		cout << "\t\t\t\t|| (2) | Add an employee.            ||	|| (7) | Chnage Password.       ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	||------------------------------||\n";
		cout << "\t\t\t\t|| (3) | Delete an employee.         ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||\n";
		cout << "\t\t\t\t|| (4) | Search for employee details.||\n";
		cout << "\t\t\t\t||-----|-----------------------------||\n";
		cout << "\t\t\t\t|| (5) | Edit an employee details.   ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||\n";
		cout << "\t\t\t\t|| (6) | Sort and save data to file. ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||\n";
		cout << "\t\t\t\t|| (0) | Return to Login.            ||\n";
		cout << "\t\t\t\t=======================================\n";
		cout << "\t\t\t\t\t\tChoice: ";	cin >> choice;	// taking choice from user
		while (1) {			// checking if user input not a number.
			if (cin.fail() || choice < 0) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice;
				continue;
			}
			break;
		}
		switch (choice) {		// switch cases for user choice.
		case 1:					// case 1 go to print all employees data function.
			print_data();	break;
		case 2:					// case 2 go to add a new employee function.
			add_emp();	break;
		case 3:					// case 3 go to delete employee function.
			delete_emp();	break;
		case 4:					// case 4 go to search employee function.
			search_emp();	break;
		case 5:					// case 5 go to edit employee function.
			edit_emp();	break;
		case 6:					// case 6 go to sort data function.
			sort_data();	break;
		case 7:					// case 6 go to sort data function.
			logged_change_password(current_logged_manager);	break;
		case 0:					// case 0 end the program.
			main_UI();	 break;
		default:
			main_menu();	 break;
		}
	}
	else if (logarr[current_logged_manager].permission == 3) {
		cout << "Logged in as: " << logarr[current_logged_manager].username << "\t\t Permission : Data Entry.";
		cout << "\n\t\t\t\t=======================================	==================================\n";
		cout << "\t\t\t\t|| (1) | See list of all employees.  ||	||	 Manager Section.	||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	||------------------------------||\n";
		cout << "\t\t\t\t|| (2) | Add an employee.            ||	|| (7) | Change Password.       ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||	==================================\n";
		cout << "\t\t\t\t|| (0) | Return to Login.            ||\n";
		cout << "\t\t\t\t=======================================\n";
		cout << "\t\t\t\t\t\tChoice: ";	cin >> choice;	// taking choice from user
		while (1) {			// checking if user input not a number.
			if (cin.fail() || choice < 0) {
				cin.clear();	cin.ignore(256, '\n');
				cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice;
				continue;
			}
			break;
		}
		switch (choice) {		// switch cases for user choice.
		case 1:					// case 1 go to print all employees data function.
			print_data();	break;
		case 2:					// case 2 go to add a new employee function.
			add_emp();	break;
		case 7:					// case 6 go to sort data function.
			change_password(current_logged_manager);	break;
		case 0:					// case 0 end the program.
			main_UI();	 break;
		default:
			main_menu();	 break;
		}
	}
}

void change_password(int index) {
	system("cls");
	questions();
	print_logo();
	int random, random1;
	string ans1, ans2;
	string ra1, ra2;
	cout << "\n\t\t\tPress 0 to back to main menu at any time.\n";
	srand(time(NULL));
	random = rand() % 4;
	if (random == 0)
		ra1 = logarr[current_logged_manager].a1;
	else if (random == 1)
		ra1 = logarr[current_logged_manager].a2;
	else if (random == 2)
		ra1 = logarr[current_logged_manager].a3;
	else if (random == 3)
		ra1 = logarr[current_logged_manager].a4;
	cout << "\n\t\t\t" << questionsarray[random];		cin >> ans1;
	if (ans1 == "0")
		main_UI();
	while (1) {						// make sure the input is right.
		if (ra1 != ans1) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "\t\t\tWrong Answer. Try a new answer: ";		cin >> ans1;
			if (ans1 == "0")
				main_UI();
			continue;
		}
		break;
	}
	srand(time(NULL));
	random1 = rand() % 4;
	if (random == random1) {
		srand(time(NULL));
		random1 = rand() % 4;
	}
	if (random1 == 0)
		ra2 = logarr[current_logged_manager].a1;
	else if (random1 == 1)
		ra2 = logarr[current_logged_manager].a2;
	else if (random1 == 2)
		ra2 = logarr[current_logged_manager].a3;
	else if (random1 == 3)
		ra2 = logarr[current_logged_manager].a4;
	cout << "\n\t\t\t" << questionsarray[random1];		cin >> ans2;
	if (ans2 == "0")
		return;
	while (1) {						// make sure the input is right.
		if (ra2 != ans2) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "\t\t\tWrong Answer. Try a new answer: ";		cin >> ans2;
			if (ans2 == "0")
				main_UI();
			continue;
		}
		break;
	}

	int ch;		char pword[BUFSIZ];		int i = 0;
	int ch1;	char pword1[BUFSIZ];	int i1 = 0;
	string password, surepassword;
	cout << "\n                          Enter the new password:";
	while ((ch = _getch()) != EOF && ch != '\n' && ch != '\r' && i < sizeof(pword) - 1) {
		if (ch == '\b' && i > 0) {
			cout << "\b \b";
			//fflush(stdout);
			i--;
			pword[i] = '\0';
			password.erase(i);
		}
		else if (isalnum(ch)) {
			cout << "*";
			pword[i++] = (char)ch;
			password.push_back(ch);
		}
	}
	cout << "\n                          confirm the new password:";
	while ((ch1 = _getch()) != EOF && ch1 != '\n' && ch1 != '\r' && i < sizeof(pword1) - 1) {
		if (ch1 == '\b' && i1 > 0) {
			cout << "\b \b";
			//fflush(stdout);
			i1--;
			pword1[i1] = '\0';
			surepassword.erase(i1);
		}
		else if (isalnum(ch1)) {
			cout << "*";
			pword[i1++] = (char)ch1;
			surepassword.push_back(ch1);
		}
	}
	if (password == surepassword) {
		logarr[current_logged_manager].password = password;
		save_logindata();
		main_UI();
	}
	else {
		cout << "\n                          Password doesn't match.\n";
		_getch();	main_UI();
	}
}

void logged_change_password(int index) {
	system("cls");
	questions();
	print_logo();
	int random, random1;
	string ans1, ans2;
	string ra1, ra2;
	cout << "\n\t\t\tPress 0 to back to main menu at any time.\n";
	srand(time(NULL));
	random = rand() % 4;
	if (random == 0)
		ra1 = logarr[current_logged_manager].a1;
	else if (random == 1)
		ra1 = logarr[current_logged_manager].a2;
	else if (random == 2)
		ra1 = logarr[current_logged_manager].a3;
	else if (random == 3)
		ra1 = logarr[current_logged_manager].a4;
	cout << "\n\t\t\t" << questionsarray[random];		cin >> ans1;
	if (ans1 == "0")
		return;
	while (1) {						// make sure the input is right.
		if (ra1 != ans1) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "\t\t\tWrong Answer. Try a new answer: ";		cin >> ans1;
			continue;
		}
		break;
	}
	srand(time(NULL));
	random1 = rand() % 4;
	if (random1 == 0)
		ra2 = logarr[current_logged_manager].a1;
	else if (random1 == 1)
		ra2 = logarr[current_logged_manager].a2;
	else if (random1 == 2)
		ra2 = logarr[current_logged_manager].a3;
	else if (random1 == 3)
		ra2 = logarr[current_logged_manager].a4;
	cout << "\n\t\t\t" << questionsarray[random1];		cin >> ans2;
	if (ans2 == "0")
		return;
	while (1) {						// make sure the input is right.
		if (ra2 != ans2) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "\t\t\tWrong Answer. Try a new answer: ";		cin >> ans2;
			continue;
		}
		break;
	}

	int ch;		char pword[BUFSIZ];		int i = 0;
	int ch1;	char pword1[BUFSIZ];	int i1 = 0;
	string password, surepassword;
	cout << "\n                          Enter the new password:";
	while ((ch = _getch()) != EOF && ch != '\n' && ch != '\r' && i < sizeof(pword) - 1) {
		if (ch == '\b' && i > 0) {
			cout << "\b \b";
			//fflush(stdout);
			i--;
			pword[i] = '\0';
			password.erase(i);
		}
		else if (isalnum(ch)) {
			cout << "*";
			pword[i++] = (char)ch;
			password.push_back(ch);
		}
	}
	cout << "\n                          confirm the new password:";
	while ((ch1 = _getch()) != EOF && ch1 != '\n' && ch1 != '\r' && i < sizeof(pword1) - 1) {
		if (ch1 == '\b' && i1 > 0) {
			cout << "\b \b";
			//fflush(stdout);
			i1--;
			pword1[i1] = '\0';
			surepassword.erase(i1);
		}
		else if (isalnum(ch1)) {
			cout << "*";
			pword[i1++] = (char)ch1;
			surepassword.push_back(ch1);
		}
	}
	if (password == surepassword) {
		logarr[current_logged_manager].password = password;
		save_logindata();
		main_menu();
	}
	else {
		cout << "\n                          Password doesn't match.\n";
		_getch();	main_menu();
	}
}

void sys_search_manager(string username) {
	bool condition = false;								// bool variable to handle results after found.
	for (int i = 0; i < total_managers; i++) {
		if (username == logarr[i].username) {
			cout << "\t\t\t\t         " << logarr[i].username << " has been found.\n";
			cout << "|-------|-----------------------|---------------|---------------|------------------------------------------------|\n";
			cout << "| ID\t| Username\t\t| Password\t| Permission\t| Answers\t\t\t\t\t |\n";
			sys_print_man(i);							//and print the employees details by sending the index to sys_print_emp();
			current_manager = i;							// save the current index to use in edit and delete.
			condition = true;
		}
	}
	if (condition == false) {							// return to search_emp(); if the id not found.
		cout << "Manager with such Username not found.\n";
		current_manager = 100;								// make the current_indx variable equal 100 to avoid wrond operations.
		search_manager();
	}
}

void search_manager() {
	recover_logindata();
	int choice, choice2;
	string username, tempusername;
	cout << "\n\t\t1. Search by Username.\t\t0. Main menu.\n\n\t\t\t\t\t\tChoice: ";	cin >> choice;
	while (1) {							// make sure the input is right.
		if (cin.fail() || choice < 0) {
			cin.clear();	cin.ignore(256, '\n');
			cout << "\t\t\t\tInvalid input. Enter a number: ";		cin >> choice;
			continue;
		}
		break;
	}
	if (choice == 1) {
		cout << "Enter Username to search for: ";	cin >> tempusername;
		transform(tempusername.begin(), tempusername.end(), tempusername.begin(), tolower);	username = tempusername;
		sys_search_manager(username);
		_getch();	main_menu();
	}
	else if (choice == 0) {
		main_menu();
	}
	else {
		cout << "Invalid input. Try again.\n";
		search_manager();
	}
}

void owner_rights(string fname, string lname) {
	cout << "\t\t\t         " << fname + ' ' + lname << " is the creator of this program.\n";
	cout << "------------------------------------------------------------------------------------------------------------------\n";
	cout << "| ID\t| Name\t\t\t| WH\t| PPH\t| Salary\t| Gross\t\t| Tax\t\t| Net Salary\t |\n";
	cout << "| " << "XXXX" << "\t| " << fname + ' ' + lname << "\t\t| " << "XXXX" << "\t| " << "XXXX" << "\t| " << "XXXX" << "    \t| " << "XXXX" << "    \t| " << "XXXX" << "\t\t| " << "XXXX" << "     \t |\n";
	cout << "|-------|-----------------------|-------|-------|---------------|---------------|---------------|----------------|\n";
	cout << "Press any key to back to the main menu...";	_getche();		main_menu();
}

void autogenerateIDs() {
	sys_sort_id();
	for (int i = 0; i < total_employees; i++) {
		emp[i].id = i + 1;
	}
	cout << "\t\t\t\t\tIDs have been generated successfully.\nPress any key to continue...";
	save_data_a_op();	_getch();	print_data();
}
