#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<limits>
using namespace std;
class supermarket {
  public:
	int xz;
	supermarket()
	{xz=0;}
	int itemno;
	string name;
	float price,qty,tax,dis;
	void AddProduct();
	void ShowProduct();
	void InputFile();
	void Display();
	void DisplaySpecific(int n);
	void Update();
	void Delete();
	void menu();
	void AdminMenu();
	void PlaceOrder();
	void intro();
public:
    // Structure to store billing history
    struct BillingHistory {
        int orderNumber;
        string productName;
        int quantity;
        float totalAmount;

        BillingHistory(int _orderNumber, string _productName, int _quantity, float _totalAmount)
            : orderNumber(_orderNumber), productName(_productName), quantity(_quantity), totalAmount(_totalAmount) {}
    };

    // Function to record billing history
    void RecordBillingHistory(const BillingHistory& history) {
        ofstream historyFile("billing_history.txt", ios::out | ios::app);
        if (!historyFile) {
            cout << "Error: Unable to open the billing history file for writing.\n";
            return;
        }
        historyFile << history.orderNumber << "		" << history.productName << "		" << history.quantity << "		" << history.totalAmount << "\n";
        historyFile.close();
    }

    // Function to display billing history
    void DisplayBillingHistory() {
        ifstream historyFile("billing_history.txt");
        if (!historyFile) {
            cout << "No billing history found.\n";
            return;
        }

        int orderNumber;
        string productName;
        int quantity;
        float totalAmount;
		char arr[100];
        cout << "Billing History:\n";
        cout << "Order Number | Product Name | Quantity | Total Amount\n";
//        while (!historyFile.eof()) {
//            cout << orderNumber << " | " << productName << " | " << quantity << " | " << totalAmount << "\n";
//        }
		cout<<historyFile.rdbuf();
		cout<<endl;

        historyFile.close();
    }
};

fstream f;
supermarket s;
void supermarket::PlaceOrder() {
	
    int order[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    static int orderNumber = 1; // Initialize the order number

    do {
        int productNumber;
        bool validProduct = false;
        while (!validProduct) {
            cout << "\n\nEnter The Product No. Of The Product : ";
            cin >> productNumber;
            if (cin.fail() || productNumber < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid numeric product number.\n";
            } else {
                validProduct = true;
            }
        }
        bool productFound = false;
        f.open("Store_Info.txt", ios::in|ios::out);
        while (f.read((char*)&s, sizeof(supermarket))) {
            if (s.itemno == productNumber) {
                productFound = true;
                cout << "\nProduct Name: " << s.name << "\n";
                cout << "Price: " << s.price << "\n";
                cout << "Available Quantity: " << s.qty << "\n";
                int quantity;
                bool validQuantity = false;
                while (!validQuantity) {
                    cout << "Enter Quantity: ";
                    cin >> quantity;
                    if (cin.fail() || quantity < 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid numeric quantity.\n";
                    } else {
                        validQuantity = true;
                    }
                }
                if (quantity <= s.qty) {
                    order[c] = productNumber;
                    quan[c] = quantity;
                    c++;
                    amt = s.price * quantity;
                    damt = amt - (amt * s.dis / 100);
                    total += damt;
                    BillingHistory history(orderNumber, s.name, quantity, damt);
                    RecordBillingHistory(history);
                    orderNumber++; // Increment order number for the next order
                    s.qty -= quantity;
					int pos = static_cast<int>(f.tellg()) - sizeof(supermarket);
					f.seekp(pos, ios::beg);
						f.write((char*)&s, sizeof(supermarket));
                    cout << "\nOrder Added: " << s.name << " (Quantity: " << quantity << ")";
                } else {
                    cout << "\nInsufficient quantity in stock for: " << s.name;
                }
                break; // No need to continue searching
            }
        }
        f.close();
        if (!productFound) {
            cout << "\nProduct with item number " << productNumber << " not found in inventory.";
        }
        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order";
    system("cls");
    cout << "\n\n********************************VOUCHER************************\n";
    cout << "\nItem No.\tItem Name\tQuantity \tPrice \t\tAmount \t  Amount after discount\n";
    for (int x = 0; x < c; x++) {
        f.open("Store_Info.txt", ios::in);
        while (f.read((char*)&s, sizeof(supermarket))) {
            if (s.itemno == order[x]) {
                amt = s.price * quan[x];
                damt = amt - (amt * s.dis / 100);
                cout << "\n " << order[x] << "\t \t" << s.name << "\t\t" << quan[x] << "\t\t" << s.price << "\t\t" << amt << "\t\t\t" << damt;
                f.close();
                break; // No need to continue searching
            }
        }
    }

    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
}
/*void supermarket:: PlaceOrder() {
        int order[50], quan[50], c = 0;
        float amt, damt, total = 0;
        char ch = 'Y';
        menu();
        cout << "\n============================";
        cout << "\n PLACE YOUR ORDER";
        cout << "\n============================\n";
        int orderNumber = 1; // Initialize the order number
        do {
            cout << "\n\nEnter The Product No. Of The Product : ";
            cin >> order[c];
            cout << "\nQuantity in number : ";
            cin >> quan[c];
            c++;
            cout << "\nDo You Want To Order Another Product ? (y/n)";
            cin >> ch;
        } while (ch == 'y' || ch == 'Y');

        cout << "\n\nThank You For Placing The Order";
        system("cls");
        cout << "\n\n********************************INVOICE************************\n";
        cout << "\nItem No.\tItem Name\tQuantity \tPrice \t\tAmount \t  Amount after discount\n";
        for (int x = 0; x < c; x++) {
            f.open("Store_Info.txt", ios::in);
            f.read((char*)&s, sizeof(supermarket));
            while (!f.eof()) {
                if (itemno == order[x]) {
                    amt = s.price * quan[x];
                    damt = amt - (amt * s.dis / 100);
                    cout << "\n " << order[x] << "\t \t" << s.name << "\t\t" << quan[x] << "\t\t" << s.price << "\t\t" << amt << "\t\t\t" << damt;
                    total += damt;

                    // Record billing history for this order
                    BillingHistory history(orderNumber, s.name, quan[x], damt);
                    RecordBillingHistory(history);
                    orderNumber++; // Increment order number for the next order
                }
                f.read((char*)&s, sizeof(supermarket));
            }
            f.close();
        }
        cout << "\n\n\t\t\t\t\tTOTAL = " << total;
    }
*/
void supermarket::AddProduct()
{
cout << "\nEnter the Item no. of the Product: ";
    
    // Validate and set item number
    while (true) {
    	//bool productFound=false;
        if (!(cin >> itemno) || itemno <= 0) {
            cout << "\nInvalid item number. Please enter a positive numeric item number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }              
    cout << "Enter the Name of the Product: ";
    cin.ignore(); 
    getline(cin, name); 
    // Validate and set price
    while (true) {
        cout << "Enter the Price of the Product: ";
        if (!(cin >> price) || price < 0) {
            cout << "Invalid price. Please enter a non-negative numeric price: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    // Validate and set discount
    while (true) {
        cout << "Enter the Discount (%) of the Product: ";
        if (!(cin >> dis) || dis < 0 || dis > 100) {
            cout << "Invalid discount. Please enter a numeric discount between 0 and 100: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    // Validate and set quantity
    while (true) {
        cout << "Enter the Quantity of the Product: ";
        if (!(cin >> qty) || qty < 0) {
            cout << "Invalid quantity. Please enter a non-negative numeric quantity: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    xz = xz + 1;
}

void supermarket::ShowProduct()
{
cout<<"\nThe Item no. of The Product : "<<itemno;
cout<<"\nThe Name of The Product : ";
cout<<name;
cout<<"\nThe Price of The Product : "<<price;
cout<<"\nDiscount : "<<dis;
cout<<"\nQuantity: "<<qty;
}

void supermarket::InputFile()
{
f.open("Store_Info.txt",ios::out|ios::app);
s.AddProduct();
f.write((char*)&s,sizeof(supermarket));
f.close();
cout<<"\n\nThe Product Has Been Created \n";
}

void supermarket::Display()
{
system("cls");
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
f.open("Store_Info.txt",ios::in);
int flag;
flag=0;
while(flag==0)
{
if(!f.eof())
{
flag==0;
f.read((char*)&s,sizeof(supermarket));
s.ShowProduct();
cout<<"\n\n====================================\n";
}
else 
flag==1;
}
f.close();
}

void supermarket::DisplaySpecific(int n)
{
int flag=0;
f.open("Store_Info.txt",ios::in);
while(f.read((char*)&s,sizeof(supermarket)))
{
if(s.itemno==n)
{
system("cls");
s.ShowProduct();
flag=1;
}
}
f.close();
if(flag==0)
cout<<"\n\nrecord not exist";
}

void supermarket::Update()
{
int no,found;
found=0;
system("cls");
cout<<"\n\n\tTo Modify ";
cout<<"\n\n\tEnter The Item No. of The Product";
while(true){
        if (!(cin >> no) || no <= 0) {
            cout << "\nInvalid item number. Please enter a positive numeric item number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
f.open("Store_Info.txt",ios::in|ios::out);
while(f.read((char*)&s,sizeof(supermarket)) && found==0)
{
if(s.itemno==no)
{
s.ShowProduct();
cout<<"\nEnter The New Details of Product"<<endl;
s.AddProduct();
int pos=(-1)*static_cast<int>(sizeof(supermarket));
f.seekp(pos,ios::cur);
f.write((char*)&s,sizeof(supermarket));
cout<<"\n\n\t Record Updated";
found=1;
}
}
f.close();
if(found==0)
cout<<"\n\n Record Not Found ";
}

void supermarket::Delete()
{
int no;
system("cls");
cout<<"\n\n\n\tDelete Record";
cout<<"\n\nEnter The Item no of The Product You Want To Delete";
while(true){
        
        if (!(cin >> no) || no <= 0) {
            cout << "\nInvalid item number. Please enter a positive numeric item number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
f.open("Store_Info.txt",ios::in|ios::out);
fstream f2;
f2.open("Temp.txt",ios::out);
f.seekg(0,ios::beg);
while(f.read((char*)&s,sizeof(supermarket)))
{
if(s.itemno!=no)
{
f2.write((char*)&s,sizeof(supermarket));
}
}
f2.close();
f.close();
remove("Store_Info.txt");
rename("Temp.txt","Store_Info.txt");
cout<<"\n\n\tRecord Deleted ..";
}

void supermarket::menu()
{
system("cls");
f.open("Store_Info.txt",ios::in);
if(!f)
{
cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
cout<<"\n\n\n Program is closing ....";
exit(0);
}
cout<<"\n\n\t\tProduct MENU\n\n";
cout<<"====================================================\n";
cout<<"ITEM.NO.\tNAME\t\tPRICE\n";
cout<<"====================================================\n";
while(f.read((char*)&s,sizeof(supermarket)))
{
cout<<s.itemno<<"\t\t"<<s.name<<"\t\t"<<s.price<<endl;
}
f.close();
}
void supermarket::intro()
{
system("cls");
cout<<"\t\t\t\t";
cout<<"SUPERMARKET";
cout<<"\t\t\t\t";
cout<<"BILLING";
cout<<"\t\t\t\t";
cout<<"PROJECT";

}

void supermarket::AdminMenu()
{
system("cls");
char ch2;
cout<<"\n\n\n\tADMIN MENU";
cout<<"\n\n\t1.CREATE PRODUCT";
cout<<"\n\n\t2.MODIFY PRODUCT";
cout<<"\n\n\t3.DELETE PRODUCT";
cout<<"\n\n\t4.VIEW PRODUCT MENU";
cout<<"\n\n\t5.VIEW Billing History";
cout<<"\n\n\t6.BACK TO MAIN MENU";
cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
cin>>ch2;
switch(ch2)
{
case '1': system("cls");
		InputFile();
		break;
case '2': Update();break;
case '3': Delete();break;
case '4': menu();break;
case '5': DisplayBillingHistory();
case '6': break;
default:AdminMenu();;
AdminMenu();
}
}
int main() {
char ch;
//s.intro();
    do {
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. CUSTOMER";
        cout << "\n\n\t02. ADMINISTRATOR";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        cin >> ch;
        switch (ch) {
            case '1':
                system("cls");
                s.PlaceOrder();
                break;
            case '2':
                s.AdminMenu();
                break;
            case '3':
                exit(0);
            default:
                cout << "\a";
        }
    } while (ch != '4');

    return 0;
}
