#include <iostream>
#include <fstream>
#include <string>
#include<conio.h>
using namespace std;

class Product {
private:
    char name[30], category[30], id[30], brand[30], description[30];

public:
    void createProduct() {
        cout << "Name: ";
        cin>> name;

        cout << "Brand: ";
       cin>> brand;

        cout << "Description: ";
        cin>>description;

        cout << "ID: ";
        cin>>id;

        cout << "Category: ";
        cin>>category;
    }

    void showProductInfo() {
        cout << "Name: " << name << endl;
        cout << "Brand: " << brand << endl;
        cout << "Category: " << category << endl;
        cout << "Description: " << description << endl;
        cout << "ID: " << id << endl;
    }
void writeOnFile() {
		char ch;
		ofstream f1;
		f1.open("f.dat",ios::binary|ios::app);

		do {
			createProduct();
			f1.write(reinterpret_cast<char*>(this),sizeof(*this));
			cout<<"Do you have next data?(y/n)";
			cin>>ch;
		}while(ch=='y');

		cout<<"Product has been Sucessfully Created...";
		f1.close();
	}



void readFromFile() {
		ifstream f2;
		f2.open("f.dat",ios::binary);

		cout<<"\n================================\n";
		cout<<"LIST OF ProductS";
		cout<<"\n================================\n";

		while(!f2.eof()) {
			if(f2.read(reinterpret_cast<char*>(this),sizeof(*this)))
			{
				showProductInfo();
				cout<<"\n================================\n";
			}
		}
		f2.close();
	}
   void searchOnFile() {
		ifstream f3;
		string searchid;
		cout<<"Enter id no.: ";
		cin>>searchid;
		f3.open("f.dat",ios::binary);

		while(!f3.eof()) {
			if(f3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (id==searchid) {
					showProductInfo();
					return;
				}
			}
		}
		cout<<"\n\n No record not found";
		f3.close();
	}
	void deleteFromFile() {
		string searchid;
		int flag = 0;
		ofstream f4;
		ifstream f5;

		f5.open("f.dat",ios::binary);
		f4.open("temp.dat",ios::binary);

		cout<<"Enter id no. to delete: ";
		cin>> searchid;

		while(!f5.eof()) {
			if(f5.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if( searchid!=id) {
					f4.write(reinterpret_cast<char*>(this),sizeof(*this));
				}
				else
					flag = 1;
			}
		}
		f5.close();
		f4.close();
		remove("f.dat");
		rename("temp.dat","f.dat");

		flag==1?
		cout<<endl<<endl<<"\tProduct Deleted...":
		cout<<endl<<endl<<"\tProduct Not Found...";
	}

	void editProduct() {
		string searchid;
		fstream f6;

		cout<<"Edit Product";
		cout<<"\n===============================\n\n";
		cout<<"Enter the product id to be edit: ";
		cin>> searchid;

		f6.open("f.dat",ios::binary|ios::out|ios::in);

		while(!f6.eof()) {
			if(f6.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if (id==searchid) {
					cout<<"Enter new record\n";
					createProduct();
					int pos=-1*sizeof(*this);
					f6.seekp(pos,ios::cur);
					f6.write(reinterpret_cast<char*>(this),sizeof(*this));
					cout<<endl<<endl<<"\t Product Successfully Updated...";
					return;
				}
			}
		}
		cout<<"\n\n No record not found";
		f6.close();
	}
};

int main() {
	system("cls");

	cout<<"\n\n\n\n\n\n\n\n\t\t\t * WELCOME TO Product MANAGEMENT SYSTEM *";
	getch();

	while(1) {
		Product c1;
		int choice;

		system("cls");


		cout<<"\nProduct MANAGEMENT SYSTEM";
        cout<<"\n\nMAIN MENU";
		cout<<"\n=====================\n";
        cout<<"[1] Add a new Product\n";
        cout<<"[2] List all Products\n";
        cout<<"[3] Search for Product\n";
        cout<<"[4] Delete a product\n";
        cout<<"[5] Edit a Product\n";
        cout<<"[0] Exit";
		cout<<"\n=====================\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice) {
        	case 1:
        		system("cls");
        		c1.writeOnFile();
        		break;

        	case 2:
				system("cls");
        		c1.readFromFile();
        		break;

			case 3:
        		system("cls");
        		c1.searchOnFile();
        		break;

        	case 4:
				system("cls");
        		c1.deleteFromFile();
        		break;

        	case 5:
			    system("cls");
        		c1.editProduct();
        		break;

        	case 0:
        		system("cls");
        		cout<<"\n\n\n\t\t\tThank you for using PMS."<<endl<<endl;
        		exit(0);
        		break;

        	default:
				continue;
		}

		int opt;
		cout<<"\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
		cin>>opt;

		switch (opt) {
			case 0:
        		system("cls");
        		cout<<"\n\n\n\t\t\tThank you for using PMS."<<endl<<endl;
        		exit(0);
        		break;

			default:
				continue;
		}
	}
 return 0;
}
