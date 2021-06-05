#include <fstream.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <process.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>

void line(int);
void Return();
void passwRe();

void inst();

void intro();
void Quiz(char *);

//UNDER "intro()"
void mainmenu();
void about();

//UNDER "mainmenu()"
void newgame();
void stats();
void Deve_sec();

//UNDER "newgame()"
void create_prof();
void load_prof();

//UNDER "Deve_sec()"
void search_re();

//Under "search_re()"
void edit_re();

//Class 1- To Enter Questions!

class Ques
{
	int sno;
	char Que[399];
	char opt1[50], opt2[50], opt3[50], opt4[50];
	char correct_opt;

public:
	int answer_check(int, char);
	void enter_ques();
	void display_ques(int);
	int count();
} v;

//FUNCTION 1A

int Ques::count()
{
	int x = 0;
	ifstream g("ques.dat", ios::binary);
	while (g.read((char *)&v, sizeof(v)))
	{
		x++;
	}
	g.close();
	return x;
}

//FUNCTION 1B

int Ques::answer_check(int sno_check, char opt_check) //Checks Answer
{
	int x;
	ifstream g("ques.dat", ios::binary);
	while (g.read((char *)&v, sizeof(v)))
	{
		if (v.sno == sno_check)
		{
			if (v.correct_opt == opt_check)
			{
				x = 1; //i.e. CORRECT ANSWER
			}
			else
			{
				x = 0; //i.e. WRONG ANSWER
			}
		}
	}
	return x;
}

//FUNCTION 1C

void Ques::enter_ques() //To Enter Ques
{
	clrscr();
	line(18);
	gotoxy(20, 2);
	cout << "## Enter New Question(s) ##" << endl;
	line(18);
	char ch = 'y';
	ofstream f("ques.dat", ios::binary);
	while (ch == 'y' || ch == 'Y')
	{
		cout << ":: Enter Question Number ::- ";
		cin >> v.sno;
		cout << ":: Enter Question ::- ";
		gets(v.Que);
		cout << ":: Enter Option (a) ::- ";
		gets(v.opt1);
		cout << ":: Enter Option (b) ::- ";
		gets(v.opt2);
		cout << ":: Enter Option (c) ::- ";
		gets(v.opt3);
		cout << ":: Enter Option (d) ::- ";
		gets(v.opt4);
		cout << ":: Enter Correct Option ::- ";
		cin >> v.correct_opt;
		f.write((char *)&v, sizeof(v));
		cout << "Do you want to Enter More Questions? ";
		cin >> ch;
	}
	f.close();
	Deve_sec();
}

//FUNCTION 1D

void Ques::display_ques(int n) //To display Question
{

	ifstream g("ques.dat", ios::binary);
	while (g.read((char *)&v, sizeof(v)))
	{
		if (v.sno == n)
		{
			cout << ":: Question " << n << " ::-" << endl;
			cout << v.Que << endl;
			cout << "(a) " << v.opt1 << endl;
			cout << "(b) " << v.opt2 << endl;
			cout << "(c) " << v.opt3 << endl;
			cout << "(d) " << v.opt4 << endl;
		}
	}
	g.close();
}

//CLASS 1 ENDS//

//Class 2- For record Entry of Players

class Re_entry
{
	char name[100];
	int age;
	char gender; //'M' or 'F'
	char alias[25];
	int points;
	int pass_checker(char *);

public:
	Re_entry()
	{
		points = 0;
	}
	void point_incre(int, char *);
	char *Write();
	char *Search();
	void delete_re();
	void change_name(char *);
	void change_age(char *);
	void change_gender(char *);
	void change_points(char *);
	int Display(char *);
	int point_dis(char *);
	void View();
} Z;

//FUNCTION 2A

void Re_entry::View() //To view Records
{
	clrscr();
	line(18);
	gotoxy(20, 2);
	cout << "## Profile Gallary ##" << endl;
	line(18);
	cout << endl;
	int count = 0, count2 = 0;
	char ch;
	ifstream q("quiz.dat", ios::binary);
	while (q.read((char *)&Z, sizeof(Z)))
	{
		if (count < 3)
		{
			count++;
			count2++;
			cout << ":: Alias :: " << Z.alias << endl;
			cout << ":: Name :: " << Z.name << endl;
			cout << ":: Age :: " << Z.age << endl;
			cout << ":: Gender :: " << Z.gender << endl;
			cout << ":: Points :: " << Z.points << endl
				 << endl;
		}
		else if (count >= 3)
		{
			cout << endl
				 << endl;
			cout << ":: Press 'Y' to View Next Page :: ";
			cin >> ch;
			ch = tolower(ch);
			cout << endl;
			if (ch == 'y')
			{
				count = 0;
				line(18);
				cout << '\t' << '\t' << "   "
					 << "## Profile Gallary ##" << endl;
				line(18);
				cout << endl;
			}
			else
				break;
		}
	}
	q.close();
	cout << endl;
	int ty;
	cout << '\t' << "##::## NO MORE RCORDS TO DISPLAY ##::##" << endl;
	line(18);
	cout << endl;
	cout << "## To Return to previous Menu Press '9' ##";
	cout << endl
		 << "## To Exit the Quiz Press '0' ##" << endl;
	cout << ":: Enter Your Choice(0 or 9) :: ";
	cin >> ty;
	if (ty == 0)
		abort();
	else if (ty == 9)
		Deve_sec();
	else
		Return();
}

//FUNCTION 2B

int Re_entry::point_dis(char *ALIAS) //To display Points
{
	int POINTS;
	ifstream q("quiz.dat", ios::binary);
	while (q.read((char *)&Z, sizeof(Z)))
	{
		if (!strcmp(Z.alias, ALIAS))
			POINTS = Z.points;
	}
	q.close();
	return POINTS;
}

//FUNCTION 2C

int Re_entry::Display(char *ALIAS) //To display Records
{
	int count = 0;
	int x;
	ifstream w("quiz.dat", ios::binary | ios::in);
	while (w.read((char *)&Z, sizeof(Z)))
	{
		if (!strcmp(ALIAS, Z.alias))
		{
			count++;
			cout << "## Profile Found ##" << endl
				 << endl;
			cout << ":: Name ::- " << Z.name << endl;
			cout << ":: Age ::- " << Z.age << endl;
			cout << ":: Gender ::- " << Z.gender << endl;
			cout << ":: Points ::- " << Z.points << endl
				 << endl;
		}
	}
	if (count > 0)
		x = 1;
	else
	{
		cout << "## Profile Not Found ##";
		x = 0;
	}
	w.close();
	return x;
}

//FUNCTION 2D

void Re_entry::change_points(char *ALIAS) //To change Points
{
	char ch;
	cout << "Do you want to change 'Points' ?('Y' or 'N') ";
	cin >> ch;
	ch = tolower(ch);
	if (ch == 'y')
	{
		int points_t;
		cout << ":: Enter Desired Points :: ";
		cin >> points_t;
		fstream q("quiz.dat", ios::binary | ios::in | ios::out);
		while (q.read((char *)&Z, sizeof(Z)))
		{
			if (!strcmp(ALIAS, Z.alias))
			{
				q.seekg(0, ios::cur);
				Z.points = points_t;
				q.seekp(q.tellg() - sizeof(Z));
				q.write((char *)&Z, sizeof(Z));
			}
		}
		q.close();
	}
	else if (ch == 'n')
		cout << ":: No Change in Points ::" << endl;
}

//FUNCTION 2E

void Re_entry::change_gender(char *ALIAS) //To change Gender
{
	char ch;
	cout << "Do you want to change 'Gender' ?('Y' or 'N') ";
	cin >> ch;
	ch = tolower(ch);
	if (ch == 'y')
	{
		fstream q("quiz.dat", ios::binary | ios::in | ios::out);
		while (q.read((char *)&Z, sizeof(Z)))
		{
			if (!strcmp(ALIAS, Z.alias))
			{
				if (Z.gender == 'M' || Z.gender == 'm')
				{
					q.seekg(0, ios::cur);
					Z.gender = 'F';
					q.seekp(q.tellg() - sizeof(Z));
					q.write((char *)&Z, sizeof(Z));
				}
				else
				{
					q.seekg(0, ios::cur);
					Z.gender = 'M';
					q.seekp(q.tellg() - sizeof(Z));
					q.write((char *)&Z, sizeof(Z));
				}
			}
		}
		q.close();
	}
	else
		cout << "::No Change in Gender ::" << endl;
}

//FUNCUTION 2F

void Re_entry::change_age(char *ALIAS) //To change Age
{
	char ch;
	cout << "Do you want to change 'Age' ?('Y' or 'N') ";
	cin >> ch;
	ch = tolower(ch);
	if (ch == 'y')
	{
		int age_t;
		cout << ":: Enter New Age :: ";
		cin >> age_t;
		fstream q("quiz.dat", ios::binary | ios::in | ios::out);
		while (q.read((char *)&Z, sizeof(Z)))
		{
			if (!strcmp(ALIAS, Z.alias))
			{
				q.seekg(0, ios::cur);
				Z.age = age_t;
				q.seekp(q.tellg() - sizeof(Z));
				q.write((char *)&Z, sizeof(Z));
			}
		}
		q.close();
	}
	else if (ch == 'n')
		cout << ":: No Change in Age :: " << endl;
}

//FUNCTION 2G

void Re_entry::change_name(char *ALIAS) //To change Name
{
	char ch;
	cout << "Do you want to change 'Name' ?('Y' or 'N') ";
	cin >> ch;
	ch = tolower(ch);
	if (ch == 'y')
	{
		char *nAme;
		cout << ":: Enter New Name :: ";
		gets(nAme);
		fstream q("quiz.dat", ios::binary | ios::in | ios::out);
		while (q.read((char *)&Z, sizeof(Z)))
		{
			if (!strcmp(ALIAS, Z.alias))
			{
				q.seekg(0, ios::cur);
				strcpy(Z.name, nAme);
				q.seekp(q.tellg() - sizeof(Z));
				q.write((char *)&Z, sizeof(Z));
			}
		}
		q.close();
	}
	else if (ch == 'n')
		cout << " ::No Change in Name :: " << endl;
}

//FUNCTION 2H

void Re_entry::delete_re() //To delete Record
{
	clrscr();
	char b[20];
	line(18);
	gotoxy(20, 2);
	cout << "## Delete Profile ##" << endl;
	line(18);
	cout << endl
		 << endl;
	cout << ":: Enter 'Alias' of the Profile ::";
	gets(b);
	int count = 0;
	ifstream q("quiz.dat", ios::binary);
	ofstream w("temp.dat", ios::binary | ios::out);

	while (q.read((char *)&Z, sizeof(Z)))
	{
		if (strcmp(b, Z.alias))
		{
			w.write((char *)&Z, sizeof(Z));
		}
		else
			count++;
	}
	if (count > 0)
	{
		q.close();
		w.close();
		remove("quiz.dat");
		rename("temp.dat", "quiz.dat");
		cout << ":: Profile Deleted :: " << endl
			 << endl;
		char choice1;
		cout << "Do you want to Delete more Profiles ?('Y' or 'N')";
		cin >> choice1;
		choice1 = tolower(choice1);
		if (choice1 == 'y')
			Z.delete_re();
		else if (choice1 == 'n')
			search_re();
	}
	else
	{
		q.close();
		w.close();
		remove("temp.dat");
		char choice1;
		cout << ":: Profile Does Not Exist ::" << endl;
		cout << "Do you want to try again ?('Y' or 'N')";
		cin >> choice1;
		choice1 = tolower(choice1);
		if (choice1 == 'y')
			Z.delete_re();
		else if (choice1 == 'n')
			search_re();
	}
}

//FUNCTION 2I

void Re_entry::point_incre(int n, char *aliAs) //To increse Point
{
	fstream q("quiz.dat", ios::binary | ios::in | ios::out);
	if (n == 1)
	{
		cout << ":: Correct Answer :: " << endl;
		while (q.read((char *)&Z, sizeof(Z)))
		{
			if (!strcmp(aliAs, Z.alias))
			{
				q.seekg(0, ios::cur);
				++Z.points;
				q.seekp(q.tellg() - sizeof(Z));
				q.write((char *)&Z, sizeof(Z));
			}
		}
	}

	else if (n == 0)
	{
		cout << endl
			 << ":: Incorrect Answer :: " << endl;
	}
	q.close();
}

//FUNCTION 2J

int Re_entry::pass_checker(char a[]) //To check Alias
{
	Re_entry B;
	int count = 0;
	ifstream M("quiz.dat", ios::binary);
	while (M.read((char *)&B, sizeof(B)))
	{
		if (!strcmp(B.alias, a))
			count++;
	}
	if (count == 0)
		return 1;
	else
		return 0;
}

//FUNCTION 2K

char *Re_entry::Write() //To Enter Record
{
	Re_entry A;
	ofstream F("quiz.dat", ios::binary | ios::app);
	cout << ":: Enter your Name ::- ";
	gets(A.name);
	cout << ":: Enter your Age ::- ";
	cin >> A.age;
	cout << ":: Enter your Gender('M' or 'F') ::- ";
	cin >> A.gender;
	cout << ":: Choose an Alias ::- ";
	gets(A.alias);

	while (pass_checker(A.alias) != 1)
	{
		cout << ":: Aready taken! Choose Again ::-";
		gets(A.alias);
	}

	F.write((char *)&A, sizeof(A));
	F.close();
	return A.alias;
}

//FUNCTION 2L

char *Re_entry::Search() //To search record
{
	Re_entry A;
	char b[20];
	int count = 0;
	char pass_match[25];
	cout << ":: Enter Your Alias ::- ";
	gets(pass_match);
	cout << endl
		 << endl
		 << endl;
	ifstream F("quiz.dat", ios::binary);
	while (F.read((char *)&A, sizeof(A)))
	{
		if (!strcmp(pass_match, A.alias))
		{
			count++;
			cout << "## Profile Found ##" << endl
				 << endl;
			cout << ":: Name ::- " << A.name << endl;
			cout << ":: Age ::- " << A.age << endl;
			cout << ":: Gender ::- " << A.gender << endl;
			cout << ":: Points ::- " << A.points << endl
				 << endl;
			strcpy(b, A.alias);
		}
	}
	F.close();
	if (count == 0)
	{
		cout << "## Profile Not Found ##" << endl
			 << endl
			 << endl;
		return "a";
	}
	else
		return b;
}

//CLASS 2 ENDS//

// OTHER FUNCTION DEFINITIONS //

// DEFINITION OF LINE FUNCTION

void line(int n)
{
	for (int i = 0; i < n; i++)
		cout << "*-*";
	cout << endl;
}

// RETURN FUNCTION

void Return()
{
	char choice;
	cout << endl
		 << endl
		 << "To RETURN to 'Intro' press 'R' and then 'Enter'" << endl;
	cout << "To EXIT the Quiz press 'E' and then 'Enter'" << endl;
	cout << "Choice:: ";
	cin >> choice;
	if (choice == 'r' || choice == 'R')
		intro();
	else if (choice == 'e' || choice == 'E')
		abort();
}

//PASSWORD CHECK

void passwRe()
{
	int count = 0;
	char pswrd[] = "pitchers", userentry[20];
	while (count < 3)
	{
		clrscr();
		line(18);
		gotoxy(1, 12);
		line(18);
		gotoxy(5, 4);
		cout << ":: Enter Password(8 characters) ::- ";
		for (int g = 0; g < 8; g++)
		{
			userentry[g] = getch();
			cout << '*';
		}

		if (!strcmp(userentry, pswrd))
		{
			gotoxy(23, 6);
			cout << "CORRECT PASSWORD!";
			delay(1500);
			Deve_sec();
		}
		else
		{
			gotoxy(1, 6);
			if (count != 2)
			{
				cout << "INVALID PASSWORD! PLEASE TRY AGAIN! " << 2 - count << " Attempts left!";
				delay(2500);
			}
			count++;
		}
	}
	gotoxy(15, 8);
	cout << "SORRY! NO ACCESS!";
	delay(1500);
	mainmenu();
}

//QUIZ FUNCTION

void Quiz(char *ALias)
{
	clrscr();
	line(18);
	char choice = 'y';
	int i = 0;
	char option;
	gotoxy(20, 2);
	cout << "## QUIZ ##" << endl;
	line(18);
	while (choice == 'y' && i < v.count())
	{
		i++;
		cout << endl;
		v.display_ques(i);
		cout << endl;
		cout << ":: Choose your Option ::- ";
		cin >> option;
		cout << endl;
		int a = v.answer_check(i, option);
		Z.point_incre(a, ALias);
		cout << ":: To continue press 'Y'! To Return press any other KEY! ::- ";
		cin >> choice;
		choice = tolower(choice);
		cout << endl;
	}
	cout << endl
		 << ":: Quiz Ended ::" << endl;
	int chy;
	cout << ":: Your Current Points are :: " << Z.point_dis(ALias) << endl;
	cout << "## To return to Previous Menu Press '9' ##" << endl;
	cout << "## To Exit the Quiz Press '0' ##" << endl;
	cout << ":: Enter Your Choice(0 or 9) ::";
	cin >> chy;
	if (chy == 0)
		abort();
	else if (chy == 9)
		newgame();
	else
		Return();
}

//INSTRUCTIONS

void inst()
{
	clrscr();
	line(18);
	int ch;
	gotoxy(20, 2);
	cout << "## INSTRUCTIONS ##" << endl;
	line(18);
	gotoxy(2, 5);
	cout << "** Kindly Read the following Instructions Carefully Before Proceeding **";
	cout << endl
		 << endl;
	cout << "*1. To Navigate between Menus, TYPE the SERIAL NO. of that MENU (OR as STATED)      and then PRESS 'ENTER KEY'!" << endl
		 << endl;
	cout << "*2. Kindly DO NOT try to be VERY FAST while using the Quiz! Just maintain the       'Normal Pace'!" << endl
		 << endl;
	cout << "*3. Proceed ONLY after you have READ above stated Instructions carefully and you    AGREE to ABIDE by them!" << endl
		 << endl;
	gotoxy(15, 16);
	cout << " ** THANK YOU FOR YOUR PATIENCE ** ";
	gotoxy(18, 18);
	cout << "## To CONTINUE Press '1' ##";
	gotoxy(20, 20);
	cout << "## To QUIT Press '0' ##";
	gotoxy(20, 22);
	cout << ":: Enter Your Choice :: ";
	cin >> ch;
	if (ch == 1)
		intro();
	else if (ch == 0)
		abort();
	else
	{
		gotoxy(14, 24);
		cout << "** INVALID CHOICE (Enter Again) **";
		delay(1500);
		inst();
	}
}

//INTRODUCTION

void intro()
{
	clrscr();
	char choice;
	line(18);
	gotoxy(15, 2);
	cout << "## WELCOME TO THE QUIZ ##" << endl;
	line(18);
	gotoxy(20, 6);
	cout << "1. Main Menu" << endl;
	gotoxy(20, 8);
	cout << "2. About" << endl;
	gotoxy(15, 10);
	cout << "## To Exit the Quiz Press '0' ##";

	gotoxy(10, 12);
	cout << ":: Enter Your Choice and Press 'Enter' ::- ";
	cin >> choice;
	if (choice == '1')
	{
		mainmenu();
	}
	else if (choice == '2')
	{
		about();
	}
	else if (choice == '0')
	{
		abort();
	}
	else
	{
		gotoxy(13, 14);
		cout << "** INVALID CHOICE (Enter Again) **";
		delay(1500);
		intro();
	}
}

//MAINMENU

void mainmenu()
{
	clrscr();
	int choice;
	line(18);
	gotoxy(20, 2);
	cout << "## Main Menu ##" << endl;
	line(18);
	gotoxy(20, 6);
	cout << "1. New Game";
	gotoxy(20, 8);
	cout << "2. Statistics";
	gotoxy(20, 10);
	cout << "3. Developer's Section";
	gotoxy(13, 12);
	cout << "## To Return to Previous Menu Press '9' ##";
	gotoxy(15, 14);
	cout << "## To Exit the Quiz Press '0' ##";

	gotoxy(13, 16);
	cout << ":: Enter Your Choice and press 'Enter'::- ";
	cin >> choice;
	if (choice == 1)
	{
		newgame();
	}
	else if (choice == 2)
	{
		stats();
	}
	else if (choice == 3)
	{
		passwRe();
	}
	else if (choice == 9)
	{
		intro();
	}
	else if (choice == 0)
	{
		abort();
	}
	else
	{
		gotoxy(13, 18);
		cout << "** INVALID CHOICE (Enter Again) **";
		delay(1500);
		mainmenu();
	}
}

//ABOUT US

void about()
{
	clrscr();
	line(18);
	gotoxy(20, 2);
	cout << "## About Us ##" << endl;
	line(18);
	gotoxy(17, 6);
	cout << "#::# GROUP MEMBERS #::#";
	gotoxy(20, 8);
	cout << "* Hrishabh Rai *";
	gotoxy(17, 10);
	cout << "* Kshitiz Srivastava *";
	gotoxy(20, 12);
	cout << "* Prakhar Gupta *";
	gotoxy(16, 14);
	int ch;
	cout << "* Ravi Prakash Tripathi *" << endl
		 << endl;
	line(18);
	cout << endl
		 << endl
		 << endl;
	cout << "        ## To Return to Previous Menu Press '9' ## " << endl;
	cout << "            ## To Exit the Quiz Press '0' ## " << endl;
	cout << "            :: Enter Your Choice (0 or 9) :: ";
	cin >> ch;

	if (ch == 9)
		intro();
	else if (ch == 0)
		abort();
	else
	{
		gotoxy(13, 23);
		cout << "** INVALID CHOICE (Enter Again) **";
		delay(1500);
		about();
	}
}

//NEW GAME

void newgame()
{
	clrscr();
	char choice;
	line(18);
	gotoxy(20, 2);
	cout << "## New Game ##" << endl;
	line(18);
	gotoxy(20, 6);
	cout << "1. Create Profile";
	gotoxy(20, 8);
	cout << "2. Load Profile";
	gotoxy(13, 10);
	cout << "## To Return to Previous Menu Press '9' ##";
	gotoxy(15, 12);
	cout << "## To Exit the Quiz Press '0' ##";
	gotoxy(13, 14);
	cout << ":: Enter Your Choice and Press 'Enter' ::- ";
	cin >> choice;
	if (choice == '1')
		create_prof();
	else if (choice == '2')
		load_prof();
	else if (choice == '0')
		abort();
	else if (choice == '9')
		mainmenu();
	else
	{
		gotoxy(13, 16);
		cout << "** INVALID CHOICE (Enter Again) **";
		delay(1500);
		newgame();
	}
}

//STATISTICS

void stats()
{
	clrscr();
	cout << "stats(UNDER CONSTRUCTION)";
	Return();
}

//DEVELEPOR'S SECTION

void Deve_sec()
{
	clrscr();
	char choice;
	line(18);
	gotoxy(17, 2);
	cout << "## Developer's Section ##" << endl;
	line(18);
	gotoxy(20, 6);
	cout << "1. Search/Edit Profile";
	gotoxy(20, 8);
	cout << "2. Enter New Question(s)";
	gotoxy(20, 10);
	cout << "3. View All Profile(s)";
	gotoxy(13, 12);
	cout << "## To Return to Previous Menu Press '9' ##";
	gotoxy(15, 14);
	cout << "## To Exit the Quiz Press '0' ##";
	gotoxy(16, 16);
	cout << ":: Enter Your Choice and Press 'Enter' ::- ";
	cin >> choice;
	if (choice == '1')
		search_re();
	else if (choice == '2')
		v.enter_ques();
	else if (choice == '3')
		Z.View();
	else if (choice == '0')
		abort();
	else if (choice == '9')
		mainmenu();
	else
	{
		gotoxy(13, 16);
		cout << "** INVALID CHOICE (Enter Again) **";
		delay(1500);
		Deve_sec();
	}
}

//CREATE PROFILE

void create_prof()
{
	clrscr();
	line(18);
	char choice;
	char S[20];
	gotoxy(20, 2);
	cout << "## Create Profile ##" << endl;
	line(18);
	strcpy(S, Z.Write());
	cout << ":: Press '1' to CONTINUE to QUIZ ::" << endl;
	cout << ":: Press '9' to Return to Previous menu ::" << endl;
	cout << ":: Press '0' to Exit the quiz ::";
	choice = tolower(choice);
	cin >> choice;
	if (choice == '1')
		Quiz(S);
	else if (choice == '0')
		abort();
	else if (choice == '9')
		newgame();
	else
		Return();
}

//LOAD PROFILE

void load_prof()
{
	clrscr();
	line(18);
	char Q[20];
	char choice;
	gotoxy(20, 2);
	cout << "## Load Profile ##" << endl;
	line(18);
	strcpy(Q, Z.Search());
	if (!strcmp(Q, "a"))
	{
		char choice2;
		cout << ":: To Search Again Press 'Y':: " << endl;
		cout << ":: To Return to Previous Menu press '9':: ";
		cin >> choice2;
		choice2 = tolower(choice2);
		if (choice2 == 'y')
			load_prof();
		else if (choice2 == '9')
			newgame();
	}
	cout << ":: Press '1' to CONTINUE to QUIZ :: " << endl;
	cout << ":: To Return to Previous Menu Press '9' ::" << endl;
	cout << ":: To Exit the Quiz Press '0' ::";
	cin >> choice;
	choice = tolower(choice);
	if (choice == '1')
		Quiz(Q);
	else if (choice == '0')
		abort();
	else if (choice == '9')
		newgame();
	else
		Return();
}

//SEARCH PROFILE

void search_re()
{
	clrscr();
	line(18);
	int choice;
	gotoxy(17, 2);
	cout << "## Edit Profile ##" << endl;
	line(18);
	gotoxy(17, 6);
	cout << "1. Delete Profile ";
	gotoxy(17, 8);
	cout << "2. Edit Profile ";
	gotoxy(13, 10);
	cout << "## To Return to Previous menu Press '9'##";
	gotoxy(15, 12);
	cout << "## To Exit the Quiz Press '0'##";
	gotoxy(13, 14);
	cout << ":: Enter your choice and Press 'Enter'::- ";
	cin >> choice;
	if (choice == 1)
		Z.delete_re();
	else if (choice == 2)
		edit_re();
	else if (choice == 0)
		abort();
	else if (choice == 9)
		Deve_sec();
	else
	{
		gotoxy(13, 16);
		cout << "##INVALID CHOICE (Enter Again) ##";
		delay(1500);
		search_re();
	}
}

//EDIT PROFILE

void edit_re()
{
	clrscr();
	line(18);
	char b[20];
	gotoxy(20, 2);
	cout << "## Edit Profile ##" << endl;
	line(18);
	cout << endl
		 << endl;
	cout << ":: Enter 'Alias' of the Profile :: ";
	gets(b);
	int a = Z.Display(b);
	if (a == 1)
	{
		Z.change_name(b);
		Z.change_age(b);
		Z.change_gender(b);
		Z.change_points(b);
		cout << endl;
		cout << "::Work Done ::" << endl;
	}
	else if (a == 0)
		cout << endl
			 << " ::ERROR:: " << endl;

	char ch2;
	cout << " Do you Want to Edit more Profiles ?('Y' or 'N') ";
	cin >> ch2;
	ch2 = tolower(ch2);
	if (ch2 == 'y')
		edit_re();
	else if (ch2 == 'n')
		search_re();
}

void main()
{
	inst();
	getch();
}
