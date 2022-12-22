#include<fstream.h>
#include<ctype.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();
	void show_account();
	void modify();
	void dep(int);
	void draw(int);
	void report();
	int retacno();
	int retdeposit();
	char rettype();
};
void account::create_account()
{
	cout<<"\nEnter The account No.";
	cin>>acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	gets(name);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter amount : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created...";
}
void account::show_account()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}
void account::modify()
{
	cout<<"\nThe account No."<<acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	gets(name);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The amount : ";
	cin>>deposit;
}
void account::dep(int x)
{
	deposit+=x;
}
void account::draw(int x)
{
	deposit-=x;
}
void account::report()
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" \t "<<"\t "<<type<<" \t "<<setw(6)<<deposit<<endl;
}
int account::retacno()
{
	return acno;
}
int account::retdeposit()
{
	return deposit;
}
char account::rettype()
{
	return type;
}

void createaccount();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int,int);
void loan();
void fixdep();
void main()
{
	char ch,r,c;
	int num;
	clrscr();
	do
	{
		clrscr();
		cout<<"\n\n\n\tBanking Project";
		cout<<"\n\n\t1. Create New Account";
		cout<<"\n\t2. Modify an existing account";
		cout<<"\n\t3. Delete Account";
		cout<<"\n\t4. All account holder list";
		cout<<"\n\t5. Fixed deposit calculator";
		cout<<"\n\t6. Loan calculator";
		cout<<"\n\t7. Exit";
		cout<<"\n\n\tSelect Your Option (1-7) ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
		case '1':createaccount();
			break;
		case '2':do{ cout<<"\n\t1. Balance Check";
			 cout<<"\n\t2. Credit Amount";
			 cout<<"\n\t3. Withdrawl Amount";
			 cout<<"\n\t4. Edit Account ";
			 cout<<"\n\t5. Back to main menu";
			 cout<<"\n\n\tEnter Your Choice:";
			 cin>>c;
			 clrscr();
			 switch(c)
			 {
				case '1': cout<<"\n\n\tEnter The account No. : "; cin>>num;
					  display_sp(num);
					  break;
				case '2':cout<<"\n\n\tEnter The account No. : "; cin>>num;
					 deposit_withdraw(num, 2);
					  break;
				case '3':cout<<"\n\n\tEnter The account No. : "; cin>>num;
					 deposit_withdraw(num, 1);
					  break;
				case '4':cout<<"\n\n\tEnter account no :";cin>>num;
					 modify_account(num);
					  break;


			     }
			}while(c!='5');
			main();
			break;
		case '3':cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		case '4':display_all();
			break;
		case '5':fixdep();
			break;
		case '6':loan();
			break;
		case '7':cout<<"\n\n\t   Thank You";
			cout<<"\n\tSoftware Details";
			cout<<"\n  Made By- Chiranjib Kalita";
			cout<<"\n  Dept-B.Sc IT(3rd Sem)";
			cout<<"\n  Roll no-17";
			break;
		 default :cout<<"\a";
		}
		getch();

	}while(ch!='7');

}


void createaccount()
{
	account a;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	a.create_account();
	outFile.write((char *) &a, sizeof(account));
	outFile.close();
}


void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist";
}


void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Successfully updated ";
			found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write((char *) &ac, sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tAccount Deleted ..";
}


void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME               Type      Balance\n";
	cout<<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

void deposit_withdraw(int n, int option)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	       }
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}

void fixdep()
{
    double A,P,r,t,I;
    float temp;
	cout<<"\n\n\tEnter amount to be Fixed: ";
	cin>>P;
	cout<<"\n\tEnter rate: ";
	cin>>r;
	cout<<"\n\tEnter time(in years): ";
	cin>>t;
	A=0;I=0;
	temp=(1+r/100);
	A=P * pow(temp,t);
	cout<<"\n\tAmount after "<<t<<" years: "<< A;
	I=A-P;
	cout<<"\n\tInterest Earned Amount: "<<I;

}
void loan(){
    double loan_amount,interest_rate,number_of_years,total_amount,monthly_amount;

	cout<<"Enter the loan amount: ";
	cin>>loan_amount;
	cout<<endl;
	cout<<"Enter the interest rate: ";
	cin>>interest_rate;
	cout<<endl;
	cout<<"The number of years: ";
	cin>>number_of_years;
	cout<<endl;

	total_amount=loan_amount+(number_of_years*loan_amount*(interest_rate/100.00));
	monthly_amount=total_amount/(number_of_years*12);

	cout<<"Total amount to be paid: "<<total_amount<<endl;
	cout<<"Total interest: "<<total_amount-loan_amount<<endl;
	cout<<"Monthly amount to be paid: "<<monthly_amount<<endl;

}


