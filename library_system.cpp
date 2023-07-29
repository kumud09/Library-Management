#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
using namespace std ;

struct Date{
	int d ;
	int m ;
	int y ;
} ;
const int monthDays[12]
    = { 31, 28, 31, 30, 31, 30,
       31, 31, 30, 31, 30, 31 };1

int countLeapYears(Date d)
{
    int years = d.y;
    if (d.m <= 2)
        years--;
    return years / 4
           - years / 100
           + years / 400;
}

int getDifference(Date dt1, Date dt2)
{
    long int n1 = dt1.y * 365 + dt1.d;
 
    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];

    n1 += countLeapYears(dt1);
 
    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    return (n2 - n1);
}



class Book{
public:
	string title ;
	string author ;
	string isbn ;
	string publication ;
	string user_issued ;
	int issue ;
	Date issued ;
	Book(){
		issue=0 ;
		user_issued = "Not issued" ;
	}
	void Show_dueDate(){

	}
} ;

class user{

public:
	string name ;
	string user_id ;
	string password ;
} ;

class Student: public user {
public:
	int fine ;
	Student(){
		fine=0 ;
	}
	vector<Book> booklist;
	void clear_Fine_amount(){
		fine = 0 ;
		cout << "Successful! No dues left now\n" ;
	}


} ;

class Professor: public user {
public:
	int fine ;
	vector<Book> booklist ;
	Professor(){
		fine=0 ;
	}
	void clear_Fine_amount(){
		fine = 0 ;
		cout << "Successful! No dues left now\n" ;
	}

} ;

class Librarian: public user{
public:
	void check_book(vector<Book> b) ;
	void user_books() ;

} ;

void Librarian :: check_book(vector<Book> b){
	if(b.size() == 0) cout << "No books Available\n" ;
	else{
    int i ;
	for(i=0; i<b.size(); i++){
		if(b[i].issue == 1) cout << b[i].title << " : " << b[i].user_issued << '\n' ;
		else cout << b[i].title << " : " << "Book is not issued by any user\n" ;
  }
	}
}



class userDatabase{
public:
	vector<Student> s ;
	vector<Professor> p ;
	int login() ;
	void add_user() ;
	void update_user() ;
	void delete_user() ;
	void calculate_Fine(int i, int c, int max, int &fine) ;

} ;

void userDatabase :: add_user(){
	cout << "Please select category of the user you want to add: \n 1. Student \n 2. Professor \n" ;
	int input ;
	cin >> input ;
	    if(input==1){
			Student s1 ;
			cout << "Enter Student Name: " ;
			cin >> s1.name ;
			cout << "Enter Student username: " ;
			cin >> s1.user_id ;
			cout << "Enter Student password: " ;
			cin >> s1.password ;
			s.push_back(s1) ;
			cout << "User added successfully\n" ;
        }
		else{
			Professor p1 ;
			cout << "Enter Professor Name: " ;
			cin >> p1.name ;
			cout << "Enter Professor username: " ;
			cin >> p1.user_id ;
			cout << "Enter Professor password: " ;
			cin >> p1.password ;
			p.push_back(p1) ;
			cout << "User added successfully...\n" ;
	}
}

void userDatabase :: delete_user(){
			cout << "Please select category of the user you want to delete: \n 1. Student \n 2. Professor \n" ;
			int input ;
			cin >> input ;
			if(input == 1){
				cout << "Enter id of the student: " ;
				string id ;
				cin >> id ;
				int i ;
				for(i=0; i<s.size(); i++){
				if(s[i].user_id == id){
					s.erase(s.begin() + i) ;
					i = -1 ;
					break ;
				}
			}
		    if(i != -1) cout << "Could not find the student !\n" ;
		    else cout << "Student removed Succesfully\n" ;
			}

			else{
				cout << "Enter id of the Professor: " ;
				string id ;
				cin >> id ;
				int i ;
				for(i=0; i<p.size(); i++){
				if(p[i].user_id == id){
					p.erase(p.begin() + i) ;
					break ;
				}
			}
		    if(i == p.size()) cout << "Could not find the professor !\n" ;
		    else cout << "Professor removed Succesfully\n" ;
			}
		}

void userDatabase :: update_user(){
			cout << "Enter id of the user to be updated: " ;
			string id ;
            cin >> id ;
			int i,j ;
			for(i=0; i<s.size(); i++){
				if(s[i].user_id == id){
					break ;
				}
			}
			if(i != s.size()){
				cout << "Update the details as follows: \n" ;
		    	cout << "Enter name of the user: " ;
				cin >> s[i].name ;
				cout << "Enter user id of the user: " ;
				cin >> s[i].user_id ;
				cout << "Enter password: " ;
				cin >> s[i].password ;
				cout << "User updated\n" ;
			}
			else{
			for(j=0; j<p.size(); j++){
				if(p[j].user_id == id){
					break ;
				}
			}
			if(j != p.size()){
				cout << "Update the details as follows: \n" ;
		    	cout << "Enter name of the user: " ;
				cin >> p[i].name ;
				cout << "Enter user id of the user: " ;
				cin >> p[i].user_id ;
				cout << "Enter password: " ;
				cin >> p[i].password ;
				cout << "User updated\n" ;
			}
			else cout << "Couldn't find the user\n" ;
		}		    
}

void userDatabase :: calculate_Fine(int i, int c, int max, int &fine){
	Date fineCheck ;
	cout << "Enter today's in dd mm yy format: \n" ;
	cout << "Day: \n" ;
	cin >> fineCheck.d ;
	cout << "Month: \n" ;
	cin >> fineCheck.m ;
	cout << "Year: \n" ;
	cin >> fineCheck.y ;
	int j,sum=0 ;
	for(j=0; j<s[i].booklist.size(); j++){
		if(getDifference(s[i].booklist[j].issued, fineCheck) > max)
		sum = sum + c*(getDifference(s[i].booklist[j].issued, fineCheck) - max) ;
	}
	fine = sum ;
	cout << "Your current Fine is: " << fine << '\n' ;
}


class bookDatabase{
public:
	vector<Book> b ;
	void add_book() ;
	void update_book() ;
	void delete_book() ;
	void book_request(vector<Book> &booklist) ;
	void return_book(int &f, int c, int max, vector<Book> &booklist) ;
	int fine(int f) ;
	void search_book() ;

} ;


void bookDatabase :: add_book(){
			Book b1 ;
			cout << "Enter name of the Book: " ;
			cin >> b1.title ;
			cout << "Enter name of the author: " ;
			cin >> b1.author ;
			cout << "Enter ISBN of the Book: " ;
			cin >> b1.isbn ;
			cout << "Enter publication of the Book: " ;
			cin >> b1.publication ;

			b.push_back(b1) ;
			cout << "Book added successfully\n" ;
}

void bookDatabase :: delete_book(){
			cout << "Enter ISBN of the Book to be deleted: " ;
			string isbn ;
			cin >> isbn ;
			int i ;
			for(i=0; i<b.size(); i++){
				if(b[i].isbn == isbn){
					b.erase(b.begin() + i) ;
					i = -1 ;
					break ;
				}
			}
		    if(i == -1) cout << "Could not find the book !\n" ;
		    else cout << "Book deleted Succesfully\n" ;
}

void bookDatabase :: update_book(){
			cout << "Enter ISBN of the Book to be updated: " ;
			string isbn ;
            cin >> isbn ;
			int i ;
			for(i=0; i<b.size(); i++){
				if(b[i].isbn == isbn){
					break ;
				}
			}
		    if(i == b.size()) cout << "Could not find the book !\n" ;
		    else{
		    	cout << "Update the details as follows: \n" ;
		    	cout << "Enter name of the Book: " ;
				cin >> b[i].title ;
				cout << "Enter name of the author: " ;
				cin >> b[i].author ;
				cout << "Enter ISBN of the Book: " ;
				cin >> b[i].isbn ;
				cout << "Enter publication of the Book: " ;
				cin >> b[i].publication ;
				cout << "Book updated Successfully\n" ;
		    }
}

void bookDatabase :: book_request(vector<Book> &booklist){
	cout << "--------------------------------------------------Book Issue Portal--------------------------------------------------------\n" ;
	cout << "Enter the ISBN of book: " ;
	string id ;
	cin >> id ;
    int i ;
	for(i=0; i<b.size(); i++){
		if(b[i].isbn == id){
			if(b[i].issue == 0){ 
				cout << "Yes it is available for issue.. \n Press 1 to issue this book\n"; 
				int input ;
				cin >> input ;
				if(input == 1){
					Date issue_d ;
					cout << "Enter the issue Date in dd mm yy format: \n" ;
					cout << "Day: \n" ;
					cin >> issue_d.d ;
					cout << "Month: \n" ;
					cin >> issue_d.m ;
					cout << "Year: " ;
					cin >> issue_d.y ;
					b[i].issued = issue_d ;
					cout << "Confirm details: " ;
					cout << "Enter user id: " ;
					string uid ;
					cin >> uid ;
					b[i].issue = 1 ;
					b[i].user_issued = uid ;
					booklist.push_back(b[i]) ;
					cout << "Book issued succesfully\n" ;
				}
				else{
					return ;
				}
			}
			else cout << "This book is already issued\n" ;
			break ;
		}
	}
	if(i == b.size()) cout << "Book Not found\n" ;
}

void bookDatabase :: return_book(int &f, int c, int max, vector<Book> &booklist){
	cout << "Enter the isbn of the book: " ;
	int i ;
	string isbn ;
	cin >> isbn ;
	for(i=0; i<b.size(); i++){
		if(b[i].isbn == isbn){
			int j ;
			for(j=0; j<booklist.size(); j++){
				if(booklist[j].isbn == isbn) break ;
			}
			booklist.erase(booklist.begin() + j) ;
			b[i].issue = 0 ;
			cout << "Enter today's date in dd mm yy: " ;
			Date issue_d ;
			cout << "Day: \n" ;
			cin >> issue_d.d ;
			cout << "Month: \n" ;
			cin >> issue_d.m ;
			cout << "Year: " ;
			cin >> issue_d.y ;
			if(getDifference(b[i].issued, issue_d) > max){
			cout << "Your fine for this book: " << c*(getDifference(b[i].issued, issue_d) - max) << '\n' ;
			}
			else {
				cout << "No fine for this book" << '\n' ;
			}
			break ;
		}
	}
	if(i == b.size()) cout << "Book not Found \n" ;
}

void bookDatabase :: search_book(){
	cout << "--------------------------------------------------------------------Search------------------------------------------------------------------------------" ;
	cout << "\nEnter name of the Book: " ;
	string book ;
	cin >> book ;
	int i,j, check=1 ;
			for(i=0; i<b.size(); i++){
				if(b[i].title == book){
					check = 0 ;
					cout << b[i].title << '\n' ;
					cout << b[i].author << '\n' ;
					cout << "Issued by: " << b[i].user_issued << '\n' ;
				}
			}
			if(check) cout << "Couldn't find the Book\n" ;
}




int main(){
	userDatabase u ;
	cout << "--------------------------------------------------Library Management System---------------------------------------------\n" ;
	bookDatabase book ;
	string userid ;
	string pass ;
	int exit = 1 ;
	while(exit != 0){
	int input=-1, i=0, option=100, t, ret, logout = 0 ;
		cout << "Please select your category: \n 1. Student\n 2. Professor\n 3. Librarian \n" ;
		cin >> input ;
		switch(input){
			case 1:			
				cout << "------------------------------------------------Login------------------------------------------------\n" ;
				t = 0 ;
				while(t < 3){
				cout << "Username:" << " " ;
				cin >> userid ;
				cout << "Password:" << " " ;
				cin >> pass ;
				for(i=0; i<u.s.size(); i++){
					if(u.s[i].user_id == userid && u.s[i].password == pass) {t = 4;break ;}
				}
				if(i == u.s.size()){cout << "Wrong details..\n" ; t++ ;}
				}
				if(t == 3) cout << "You have entered incorrect details for 3 times..\n Run the program again..\n " ;
				if(t != 3){
					cout << "Hello " << u.s[i].name << ", " ;
					option = 100 ;
					while(option != 0){
					cout << "What do you want to do ?" << '\n' ;
					cout << "1. See list of books\n2. List of books issued by you\n3. Books available for issue\n4. Issue a book\n5. Return Book\n6. Calculate Fine\n7. Clear Fine\n" ;
					cin >> option ;
					switch(option){
						case 0:
							cout << "Logged out Successfully" ;
							break ;
						case 1:
							for(auto it: book.b) cout << it.title << '\n' ;
							break ;
						case 2:
							for(auto it: u.s[i].booklist) cout << it.title << '\n' ;
							break ;
						case 3:
							for(i=0; i<book.b.size(); i++){
								if(book.b[i].issue == 0) 
									cout << book.b[i].title << '\n' ;
							}
							break ;
						case 4:
							if(u.s[i].booklist.size() < 5){
								book.book_request(u.s[i].booklist) ;
							}
							break ;
						case 5: 
							book.return_book(u.s[i].fine, 2, 30, u.s[i].booklist) ;
							break ;
						
						case 6:
							u.calculate_Fine(i,2,30, u.s[i].fine) ;
							break ;
						case 7: 
							u.s[i].clear_Fine_amount() ;
							break ;

					}
					cout << "1. Do you want to perform any further action ?\n2. Logout\n" ;
					int l ;
					cin >> l ;
					if(l == 2) option =  0 ;
					else continue ;
				  }
				}
				break ;

			case 2:
				cout << "-----------------------------------------------------Login------------------------------------------------------\n" ;
				t = 0 ;
				while(t < 3){
				cout << "Username:" << " " ;
				cin >> userid ;
				cout << "Password:" << " " ;
				cin >> pass ;
				for(i=0; i<u.p.size(); i++){
					if(u.p[i].user_id == userid && u.p[i].password == pass) {t = 4;break ;}
				}
				if(i == u.p.size()){cout << "Wrong details..\n" ; t++ ;}
				}
				if(t == 3) cout << "You have entered incorrect details for 3 times..\n Run the program again.. " ;
				if(t != 3){
					cout << "Hello " << u.p[i].name ;
					while(option != 0){
					cout << "What do you want to do ?" << '\n' ;
					cout << "0. Exit/Logout\n 1. See list of books\n2. List of books issued by you\n3. Books available for issue\n4. Issue a book\n5. Return a book\n6. Calculate Fine\n7. Clear Fine\n" ;
					cin >> option ;
					switch(option){
						case 0:
							cout << "Logged out Successfully" ;
							break ;
						case 1:
							for(auto it: book.b) cout << it.title << '\n' ;
                            break ;
						case 2:
							int i ;
							for(auto it: u.p[i].booklist) cout << it.title << '\n' ;
                            break ;
						case 3:
							for(i=0; i<book.b.size(); i++){
								if(book.b[i].issue == 0) 
									cout << book.b[i].title << '\n' ;
							}
							break ;
						case 4:
							book.book_request(u.p[i].booklist) ;
							break ;
						case 5: 
							book.return_book(u.p[i].fine, 5, 60, u.p[i].booklist) ;
							break ;
						case 6:
							u.calculate_Fine(i,5,60, u.p[i].fine) ;
							break ;
						case 7: 
							u.p[i].clear_Fine_amount() ;
							break ;
					}
					cout << "1. Do you want to perform any further action ?\n2. Logout\n" ;
					int l ;
					cin >> l ;
					if(l == 2) option =  0 ;
					else continue ;
					}
				}
				break ;


			case 3:
				string username ;
				string password ;
				cout << "Enter username: " ;
				cin >> username ;
				cout << "Enter Password: " ;
				cin >> password ;
				if(username == "Lib@svnit.ac.in" && password == "Lib@123"){
				Librarian lib ;
				option = 100 ;
				while(option != 0){
				cout << "Please select the action you want to perform:\n 0. Exit/Logout\n 1. Add a user\n 2. Add a book\n 3. Update book details\n 4. Delete a book\n 5. Update User\n 6. Delete user\n 7. See list of all books\n 8. See the list of users\n 9. Check which user has a particular book\n10. Search\n" ;
				cin >> option ;
				switch(option){
					case 0:
						cout << "Logged out Successfully\n" ;
						break ;
					case 1:
						u.add_user() ;
                        break ;
					case 2:
						book.add_book() ;
                        break ;
					case 3:
						book.update_book(); 
                        break ;
					case 4:
						book.delete_book() ;
                        break ;
					case 5:
						u.update_user() ;
                        break ;
					case 6:
						u.delete_user() ;
                        break ;
					case 7:
						for(auto it: book.b) cout << it.title << '\n' ;
                        break ;
					case 8:
						for(auto it: u.s) cout << it.name << '\n' ;
						for(auto it: u.p) cout << it.name << '\n' ;
                        break ;
					case 9:
						lib.check_book(book.b) ;
                        break ;
					case 10:
						book.search_book() ;

						
				}
				cout << "1. Do you want to perform any further action ?\n2. Logout\n" ;
				int l ;
				cin >> l ;
				if(l == 2) option =  0 ;
				else continue ;
			}
				}
				else cout << "Invalid Details..." ;
		 		break ;

		}
	cout << "Enter 0 to exit..\nPress 1 to continue to Homepage of LMS\n" ;
	cin >> exit ;
	}
	cout << "Exited from the system ...\n" ;
}
