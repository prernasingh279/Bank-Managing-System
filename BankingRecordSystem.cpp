#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

class account{
    char acc_no[20];
    char fname[10];
    char lname[10];
    float total_bal;
public:
    void read_data();
    void show_data();
    void write_record();
    void read_record();
    void search_record();
    void edit_record();
    void delete_record();
};

void account::read_data()
{
    cout<<"\nEnter account number: ";
    cin>>acc_no;
    cout<<"\nEnter First name: ";
    cin>>fname;
    cout<<"\nEnter last name: ";
    cin>>lname;
    cout<<"\nEnter the balance: ";
    cin>>total_bal;
    cout<<endl;
}

void account::show_data()
{
    cout<<"Account Number: "<<acc_no<<endl;
    cout<<"First Name: "<<fname<<endl;
    cout<<"Last Name: "<<lname<<endl;
    cout<<"Current Balance: "<<total_bal<<endl;
    cout<<"----------------------------"<<endl;
}

void account::write_record()
{
    ofstream outfile;
    outfile.open("record.bank",ios::binary|ios::app);
    read_data();
    outfile.write(reinterpret_cast<char *>(this),sizeof(*this));
    outfile.close();
}

void account::read_record()
{
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n***Data from file***"<<endl;
     while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            show_data();
        }
    }
    infile.close();
}

void account::search_record()
{
    int n;
    ifstream infile;
    infile.open("record.bank",ios::binary);
    if(!infile)
    {
       cout<<"Error in Opening! File Not Found!!"<<endl;
       return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter record no to search: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this),sizeof(*this));
    show_data();
}

void account::edit_record()
{
    int n;
    fstream iofile;
    iofile.open("record.bank",ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0,ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter record number to edit: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this),sizeof(*this));
    cout<<"Record "<<n<<" has following data"<<endl;
    show_data();
    iofile.close();
    iofile.open("record.bank",ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\n Enter data to modify "<<endl;
    read_data();
    iofile.write(reinterpret_cast<char*>(this),sizeof(*this));
}

void account::delete_record()
{
    int n;
    ifstream infile;
    infile.open("record.bank",ios::binary);
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter record number to delete: "<<endl;
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank",ios::out|ios::binary);
    infile.seekg(0);
    for(int i=0;i<count;i++)
    {
        infile.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(i==(n-1))
        {
            continue;
            tmpfile.write(reinterpret_cast<char*>(this),sizeof(*this));
        }
        infile.close();
        tmpfile.close();
        remove("record.bank");
        rename("tmpfile.bank","record.bank");
    }
}
int main()
    {
        account obj;
        int choice;
        cout<<"------Account Information--------"<<endl;
        while(true)
        {
            cout<<"Select one option below"<<endl;
            cout<<"\n\t1--> Add record to file";
            cout<<"\n\t2--> Show record to file";
            cout<<"\n\t3--> Search record from file";
            cout<<"\n\t4--> Update record";
            cout<<"\n\t5--> Delete record";
            cout<<"\n\t6--> Quit";
            cout<<"\nEnter your choice: ";
            cin>>choice;
            switch(choice)
            {
            case 1:
                obj.write_record();
                break;

            case 2:
                obj.read_record();
                break;

            case 3:
                obj.search_record();
                break;

            case 4:
                obj.edit_record();
                break;

            case 5:
                obj.delete_record();
                break;

            case 6:
                exit(0);
                break;

            default:
                cout<<"\nEnter correct choice";
                exit(0);
            }
        }
        system("pause");
        return 0;
    }
