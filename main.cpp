#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <string.h>
#include <sstream>


using namespace std;

class Student{
    public:
        int id;
        string name;
        string add;
        int age;

        Student(int id,string name,string add,int age){
            this->id=id;
            this->name=name;
            this->add=add;
            this->age=age;
        }
};

MYSQL* initConnection(){
    MYSQL* conn;
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn,"localhost","root","root","cplus",0,NULL,0) !=0){
        cout << "Succesfully  Connected to MySQL database" << endl;
    }else{
        cout << "Failed to Connect to MySQL database" << endl;
    }
    //mysql_close(conn);
    return conn;
}

void insert(MYSQL* conn,Student s){
    stringstream query;
    query<<"insert into students values("<<s.id<<",\""<<s.name<<"\",\" "<<s.add<<"\","<<s.age<<")";
    cout<<query.str()<<endl;

    string q=query.str();
    const char* cstr = q.c_str();
    int qstate=mysql_query(conn,cstr);

    if(!qstate)
        cout<<"record inserted successfully..."<<endl;
    else
        cout<<"query problem: "<<mysql_error(conn)<<endl;
}

void search(MYSQL* conn){
    MYSQL_RES * res;
    MYSQL_ROW row;

    string query="select * from students";
    const char* cstr = query.c_str();

    int qstate=mysql_query(conn,cstr);

    res = mysql_store_result(conn);
    if(!qstate)
        {
            while(row=mysql_fetch_row(res))
            {
                cout<<"id: "<<row[0]<< " "<<" - name: "<<row[1]<< " "<<" - add: "<<row[2]<<" - age: "<<row[3]<<endl;
            }
        }else
        {
            cout<<"query error: "<<mysql_error(conn)<<endl;
        }
}

void searchByID(MYSQL* conn,int id){
    MYSQL_RES * res;
    MYSQL_ROW row;

    stringstream querystream;
    querystream<<"select * from students where id = "<<id;
    cout<<querystream.str()<<endl;

    string query=querystream.str();
    const char* cstr = query.c_str();
    int qstate=mysql_query(conn,cstr);

    res = mysql_store_result(conn);
    if(!qstate)
        {
            while(row=mysql_fetch_row(res))
            {
                cout<<"id: "<<row[0]<< " "<<" - name: "<<row[1]<< " "<<" - add: "<<row[2]<<" - age: "<<row[3]<<endl;
            }
        }else
        {
            cout<<"query error: "<<mysql_error(conn)<<endl;
        }
}

int main()
{
    MYSQL* conn=initConnection();
    //----------------------------
    int op;
    cout<<"Enter Operation ? 1- Insert New  2- Display All  3- Search By ID "<<endl;
    cin>>op;

    switch(op){
    case 1:{
        //-----------------------------
        int id;
        string name;
        string add;
        int age;

        cout<<"Enter Your ID : ";
        cin>>id;

        cout<<"Enter Your Name : ";
        cin>>name;

        cout<<"Enter Your Add : ";
        cin>>add;

        cout<<"Enter Your Age : ";
        cin>>age;

        Student s(id,name,add,age);
        insert(conn,s);
        break;
        }
    case 2:{
        //-----------------------------
        search(conn);
        break;
        }
    case 3:{
        //-----------------------------
        int idSearch;
        cout<<"Enter Your ID ? ";
        cin>>idSearch;
        searchByID(idSearch);
        break;
        }
    default:
        cout<<"Wrong Operation";
    }
}
