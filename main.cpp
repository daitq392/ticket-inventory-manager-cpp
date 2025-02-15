#include<string.h>
#include<fstream>
#include<conio.h>
#include<iostream>
#include <algorithm>
#include <vector>
#include <shlwapi.h>
#ifdef _MSC_VER
#pragma comment (lib, "Shlwapi.lib")
#endif
#include <string>


#define MaxSize 1000

using namespace std;

class Ticket //Tran Quang Dai
{
    int roll_number = 0;
    char ticket_type = 'g';
    char place_of_departure[50] = "";
    char destination[50] = "";
    int depart_day = 0, depart_month = 0, depart_year = 0, depart_hour = 0, depart_minute = 0;
    long long ticket_price = 0, ticket_commission = 0;
    static vector<vector<int>> sale_record;
public:
    void add_ticket_details(int roll_number, char ticket_type);
    void view_ticket();
    void view_ticket(vector<Ticket*>& vector_ticket, const vector<int>& match_res);
    void modify_ticket();
    void delete_ticket(vector<Ticket*>& vector_ticket, int i);
    void searchforticket(vector<Ticket*>& vector_ticket, int day, int month, int year); //search by time
    void searchforticket(vector<Ticket*>& vector_ticket, char place[50], int typesearch);  //search by date
    long long get_ticket_price() { return ticket_price; }
    long long get_ticket_roll_number() { return roll_number; }
    virtual long long calc_ticket_commission() = 0;
    void set_ticket_commission(long long x) { ticket_commission = x; }
    bool checkDateInPeriod(int day, int month, int year, int StartDay, int StartMonth, int StartYear, int EndDay, int EndMonth, int EndYear);
    int get_ticket_index(vector<Ticket*>& vector_ticket, int roll_number);
    void domes_flight_in_a_period(vector<Ticket*>& vector_ticket, int StartDay, int StartMonth, int StartYear, int EndDay, int EndMonth, int EndYear);
    void get_sale_detail(vector<Ticket*>& vector_ticket, int roll_number, int i);
    long long commission_over_a_period(int startDay, int startMonth, int startYear, int endDay, int endMonth, int endYear);
    void export_file(vector<Ticket*>& vector_ticket);
    void import_file(vector<Ticket*>& vector_ticket);
    virtual ~Ticket() = default;




};

class Domestic_Ticket : public Ticket {   //Tran Quang Dai

public:
    virtual long long calc_ticket_commission() { return (long long)(0.05 * get_ticket_price()); }
    virtual ~Domestic_Ticket() = default;
};

class International_Ticket : public Ticket {    //Tran Quang Dai
public:
    virtual long long calc_ticket_commission() { return (long long)(0.07 * get_ticket_price() + 100000); }
    virtual ~International_Ticket() = default;
};


char fndomesticket[] = "domesticket.txt";
char fninterticket[] = "interticket.txt";
char fnsalerecord[] = "salerecord.txt";

int maxrollnumber(vector<Ticket*>& vector_ticket);
void AddTicket(vector<Ticket*>& vector_ticket);
void ViewTicket(vector<Ticket*>& vector_ticket);
void FormatMoney(long long x);
void DeleteTicket(vector<Ticket*>& vector_ticket);
void ModifyTicket(vector<Ticket*>& vector_ticket);
void SearchTicket(vector<Ticket*>& vector_ticket);
void SearchByPlace(vector<Ticket*>& vector_ticket);
void SearchByTime(vector<Ticket*>& vector_ticket);
void DomesticFlightInAPeriod(vector<Ticket*>& vector_ticket);
void AddSaleRecord(vector<Ticket*>& vector_ticket);
void CommissionOverAPeriod();
void exportfile(vector<Ticket*>& vector_ticket);
void importfile(vector<Ticket*>& vector_ticket);
void printall(vector<Ticket*>& vector_ticket);


vector<vector<int>> Ticket::sale_record{ {0,1,2,3} };

int main()   //Tran Quang Dai
{
    vector<Ticket*> vector_ticket; //vector to store objects of tickets on sale
    importfile(vector_ticket);

    for (;;)
    {
        system("cls");
        printf("\nNumber of tickets: %zu\n\n", vector_ticket.size());
        cout << "\n\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * *";
        cout << "\n\t\t\t\t*   1. View details of a ticket                   *";
        cout << "\n\t\t\t\t*   2. Add a ticket                               *";
        cout << "\n\t\t\t\t*   3. Delete a ticket                            *";
        cout << "\n\t\t\t\t*   4. Modify a ticket                            *";
        cout << "\n\t\t\t\t*   5. Search for a ticket                        *";
        cout << "\n\t\t\t\t*   6. Show domestic flights in a period          *";
        cout << "\n\t\t\t\t*   7. Calculate commission received in a period  *";
        cout << "\n\t\t\t\t*   8. Add a sale record                          *";
        cout << "\n\t\t\t\t*   9. Export to file                             *";
        cout << "\n\t\t\t\t*   10.Exit                                       *";
        cout << "\n\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * *";

        int option = 0;
        cout << "\n\t\tEnter option: "; cin >> option;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "\a\n\tInvalid option: ";
            cout << "\n\t\tEnter option: "; cin >> option;
        }


        switch (option)
        {
        case 1:
            system("cls");
            ViewTicket(vector_ticket);
            break;
        case 2:
            system("cls");
            AddTicket(vector_ticket);
            break;
        case 3:
            system("cls");
            DeleteTicket(vector_ticket);
            break;
        case 4:
            system("cls");
            ModifyTicket(vector_ticket);
            break;
        case 5:
            system("cls");
            SearchTicket(vector_ticket);
            break;
        case 6:
            system("cls");
            DomesticFlightInAPeriod(vector_ticket);
            break;
        case 7:
            system("cls");
            CommissionOverAPeriod();
            break;
        case 8:
            system("cls");
            AddSaleRecord(vector_ticket);
            break;
        case 9:
            exportfile(vector_ticket);
            break;
        case 10:
            exit(0);
            break;
        default: cout << "\a";

        }
    }

}

int maxrollnumber(vector<Ticket*>& vector_ticket) { //Tran Quang Dai
    int rnummax = 0;
    int n = (int) vector_ticket.size();
    if (n > 0) {
        rnummax = vector_ticket[0]->get_ticket_roll_number();
        for (int i = 0; i < n; i++) {
            if (vector_ticket[i]->get_ticket_roll_number() > rnummax) {
                rnummax = vector_ticket[i]->get_ticket_roll_number();
            }
        }
    }
    return rnummax;
}


void Ticket::add_ticket_details(int roll_number, char ticket_type) //method for getting ticket details from user - Tran Quang Dai
{
    this->roll_number = roll_number;
    this->ticket_type = ticket_type;
    cout << "Enter the place of departure: ";
    cin.ignore();
    cin.getline(place_of_departure, 50);

    cout << "Enter flight date (dd/mm/yyyy): ";
    char sign;
    cin >> depart_day >> sign >> depart_month >> sign >> depart_year;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid format!" << endl;
        cout << "Enter flight date (dd/mm/yyyy): ";
        cin >> depart_day >> sign >> depart_month >> sign >> depart_year;
    }

    cout << "Enter boarding time (hh:mm): ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> depart_hour >> sign >> depart_minute;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid format!" << endl;
        cout << "Enter boarding time (hh:mm): ";
        cin >> depart_hour >> sign >> depart_minute;
    }

    cout << "Enter the destination: ";
    cin.clear();
    cin.ignore(256, '\n');
    cin.getline(destination, 50);


    cout << "Enter the price of the ticket: "; cin >> ticket_price;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid input!" << endl;
        cout << "Re-enter the price of the ticket: ";
        cin >> ticket_price;
    }
    cin.clear();
    cin.ignore(256, '\n');

}

void AddTicket(vector<Ticket*>& vector_ticket) //add ticket to the storing vector - Nguyen Anh Duy
{
    int cont_or_not = 0;
    do
    {
        system("cls");
        cout << "\nEnter details of the ticket\n";
        char ticket_type;
        cout << "Type \"d\" for DOMESTIC and \"i\" for INTERNATIONAL ticket: "; cin >> ticket_type;
        int roll_number = maxrollnumber(vector_ticket) + 1;
        int i = (int)(vector_ticket.size()); //index in the vector
        if (ticket_type == 'd')
            vector_ticket.push_back(new Domestic_Ticket());
        else if (ticket_type == 'i')
            vector_ticket.push_back(new International_Ticket());
        else {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            system("pause");
            return;
        }
        cin.clear();
        cin.ignore(256, '\n');
        vector_ticket[i]->add_ticket_details(roll_number, ticket_type);
        long long x = vector_ticket[i]->calc_ticket_commission(); //Polymorphism
        vector_ticket[i]->set_ticket_commission(x);
        system("cls");
        cout << "\nTicket added succesfully.\n";
        vector_ticket[i]->view_ticket();
        cout << "\n\nEnter 1 to add more tickets.";
        cout << "\nEnter 2 to return to main menu.\n";
        cin >> cont_or_not;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid option!" << endl;
            cout << "\n\nEnter 1 to add more tickets.";
            cout << "\nEnter 2 to return to main menu.\n";
            cin >> cont_or_not;
        }
        cin.clear();
        cin.ignore(256, '\n');
    } while (cont_or_not == 1);
}


void Ticket::view_ticket() //Tran Quang Dai
{
    cout << "\nTicket number: " << roll_number << endl;
    cout << "Type of ticket: " << +((ticket_type == 'd') ? ("Domestic") : ("International")) << endl;
    cout << "From: " << place_of_departure << endl;
    cout << "To: " << destination << endl;
    printf("Flight date: %02d/%02d/%d\n", depart_day, depart_month, depart_year);
    printf("Boarding time: %02d:%02d\n", depart_hour, depart_minute);
    cout << "Price: "; FormatMoney(ticket_price);
    cout << "Commission: "; FormatMoney(ticket_commission);
}

void Ticket::view_ticket(vector<Ticket*>& vector_ticket, const vector<int>& match_res) //show details of multiple tickets with their roll numbers stored in a vector - Tran Quang Dai
{
    for (size_t i = 0; i < match_res.size(); i++)
    {
        printf("\n*******************");
        int n = match_res[i]; //ticket_roll_number
        int id = get_ticket_index(vector_ticket, n); //index in vector_ticket of vector with roll_number n
        vector_ticket[id]->view_ticket();
    }
}


void ViewTicket(vector<Ticket*>& vector_ticket) // Tran Thi Thuy Linh
{
    int roll_number;
    cout << "\nEnter the roll number of the ticket you want to view: "; cin >> roll_number;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid roll number!" << endl;
        cout << "\nRe-Enter the roll number of the ticket you want to view: "; cin >> roll_number;

    }
    system("cls");
    cin.clear();
    cin.ignore(256, '\n');
    Domestic_Ticket ticket;
    int i = ticket.get_ticket_index(vector_ticket, roll_number);
    if (i == -1)
        cout << "\nThere's no ticket with that roll number" << endl;
    else
        vector_ticket[i]->view_ticket();
    cout << "\n*******************" << endl;
    system("pause");


}

void FormatMoney(long long x) //print 123456 as 123.456 VND - Tran Quang Dai
{
    int fthreeDigit;
    vector <int> res;
    if (x > 1000) {
        while (x != 0)
        {
            fthreeDigit = x % 1000;
            res.push_back(fthreeDigit);
            x = x / 1000;
        }
        std::reverse(res.begin(), res.end());
        cout << res[0] << ".";
        for (size_t i = 1; i < res.size() - 1; ++i)
        {
            if (res[i] == 0)
                cout << "000" << ".";
            else if (res[i] < 100 && res[i] > 9)
                cout << "0" << res[i] << ".";
            else if (res[i] < 10 && res[i] > 0)
                cout << "00" << res[i] << ".";
            else
                cout << res[i] << ".";
        }
        if (res[res.size() - 1] == 0)
            cout << "000 VND" << endl;
        else if (res[res.size() - 1] < 100 && res[res.size() - 1] > 9)
            cout << "0" << res[res.size() - 1] << " VND" << endl;
        else if (res[res.size() - 1] < 10 && res[res.size() - 1] > 0)
            cout << "00" << res[res.size() - 1] << " VND" << endl;
        else
            cout << res[res.size() - 1] << " VND" << endl;
    }
    else cout << x << " VND" << endl;
}

bool Ticket::checkDateInPeriod(int day, int month, int year, int StartDay, int StartMonth, int StartYear, int EndDay, int EndMonth, int EndYear) //Tran Quang Dai
{
    int Date = day + (month * 100) + (year * 10000);
    int StartDate = StartDay + (StartMonth * 100) + (StartYear * 10000);
    int EndDate = EndDay + (EndMonth * 100) + (EndYear * 10000);

    if (Date >= StartDate && Date <= EndDate) {
        return true;
    }
    else {
        return false;
    }
}

int Ticket::get_ticket_index(vector<Ticket*>& vector_ticket, int roll_number) //return the index in the storing vector of a ticket from its roll number - Tran Quang Dai
{
    for (size_t i = 0; i < vector_ticket.size(); i++)
        if (vector_ticket[i]->roll_number == roll_number)
            return (int)i;
    return -1;
}

void Ticket::delete_ticket(vector<Ticket*>& vector_ticket, int i) //Tran Quang Dai
{
    delete vector_ticket[i];
    vector_ticket.erase(vector_ticket.begin() + i - 1);
}


void DeleteTicket(vector<Ticket*>& vector_ticket) //Nguyen Anh Duy
{
    int roll_number;
    cout << "Enter the roll number of the ticket you want to delete: "; cin >> roll_number;
    Domestic_Ticket ticket;
    int i = ticket.get_ticket_index(vector_ticket, roll_number);
    if (i == -1)
        cout << "\nThere's no ticket with that roll number" << endl;
    else
    {
        vector_ticket[i]->delete_ticket(vector_ticket, i);
        cout << "\nTicket deleted." << endl;
    }

    system("pause");
}



void Ticket::modify_ticket() //Tran Quang Dai
{
    cout << "\n\nModify: \n";
    int option = 0;
    while (option != 6)
    {
        system("cls");
        view_ticket();
        cout << "\n\t1. Edit PLACE OF DEPARTURE of ticket";
        cout << "\n\t2. Edit DESTINATION of ticket";
        cout << "\n\t3. Edit FLIGHT DATE of ticket";
        cout << "\n\t4. Edit BOARDING TIME of ticket";
        cout << "\n\t5. Edit PRICE of ticket";
        cout << "\n\t6. SAVE changes.";

        cout << "\n\t\tEnter option: "; cin >> option;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            continue;

        }
        switch (option)
        {
        case 1:
            cout << "Enter new place of departure: ";
            cin.ignore();
            cin.getline(place_of_departure, 50);
            system("cls");
            break;
        case 2:
            cout << "Enter new destination: ";
            cin.ignore();
            cin.getline(destination, 50);
            system("cls");
            break;
        case 3:
            cout << "Enter new flight date (dd/mm/yyyy): ";
            char sign;
            cin >> depart_day >> sign >> depart_month >> sign >> depart_year;
            while (cin.fail())
            {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Invalid format!" << endl;
                cout << "Enter new flight date (dd/mm/yyyy): ";
                cin >> depart_day >> sign >> depart_month >> sign >> depart_year;
            }
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");
            break;
        case 4:
            cout << "Enter new boarding time (hh:mm): ";
            cin >> depart_hour >> sign >> depart_minute;
            while (cin.fail())
            {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Invalid format!" << endl;
                cout << "Enter new flight date (dd/mm/yyyy): ";
                cin >> depart_day >> sign >> depart_month >> sign >> depart_year;
            }
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");
            break;
        case 5:
            cout << "Enter new price of the ticket: "; cin >> ticket_price;
            while (cin.fail())
            {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Invalid input!" << endl;
                cout << "Enter new price of the ticket: ";
                cin >> ticket_price;
            }
            cin.clear();
            cin.ignore(256, '\n');
            ticket_commission = calc_ticket_commission(); //recalculate ticket commission
            system("cls");
            break;
        default: cout << "\a Invalid option!";
        }
    }

    system("cls");
    cout << "\nTicket modified! New details:\n";
    view_ticket();
    cout << "\n*******************" << endl;
    system("pause");
}

void ModifyTicket(vector<Ticket*>& vector_ticket) //Nguyen Anh Duy
{
    int roll_number;
    cout << "Enter the roll number of the ticket you want to modify: "; cin >> roll_number;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid roll number!" << endl;
        cout << "\nRe-Enter the roll number of the ticket you want to modify: "; cin >> roll_number;

    }
    system("cls");
    cin.clear();
    cin.ignore(256, '\n');
    Domestic_Ticket ticket;
    int i = ticket.get_ticket_index(vector_ticket, roll_number);
    if (i == -1)
    {
        cout << "\nThere's no ticket with that roll number" << endl;
        system("pause");
    }
    else
        vector_ticket[i]->modify_ticket();
}

void Ticket::searchforticket(vector<Ticket*>& vector_ticket, char place[50], int typesearch) //search by place - Tran Quang Dai
{
    int res = 0; //variable to count number of matching tickets
    vector<int> match_res; //vector to store roll numbers of matching tickets
    for (int i = 0; i < (int)vector_ticket.size(); i++) {
        if ((typesearch == 1) ? ((StrStrIA(vector_ticket[i]->place_of_departure, place))) : ((StrStrIA(vector_ticket[i]->destination, place))))
        {
            match_res.push_back(vector_ticket[i]->roll_number); //store their roll numbers in vector
            res++;
        }
    }
    if (res == 0)
        cout << "\nNo matching ticket";
    else
    {
        printf("\n%d matching ticket%s:", res, (res == 1) ? ("") : ("s"));
        Domestic_Ticket ticket;
        ticket.view_ticket(vector_ticket, match_res);
    }
}

void Ticket::searchforticket(vector<Ticket*>& vector_ticket, int day, int month, int year) //search by time - //Tran Quang Dai
{
    int res = 0; //variable to count number of matching tickets
    vector<int> match_res; //vector to store index of matching tickets
    for (int i = 0; i < (int)vector_ticket.size(); i++) {
        if (vector_ticket[i]->depart_day == day && vector_ticket[i]->depart_month == month && vector_ticket[i]->depart_year == year)
        {
            match_res.push_back(vector_ticket[i]->roll_number);
            res++;
        }
    }
    if (res == 0)
        cout << "\nNo matching ticket";
    else
    {
        printf("\n%d matching ticket%s:", res, (res == 1) ? ("") : ("s"));
        Domestic_Ticket ticket;
        ticket.view_ticket(vector_ticket, match_res);
    }
}

void SearchTicket(vector<Ticket*>& vector_ticket) //Tran Quang Dai
{
    int cont_or_not = 0;
    do {
        int searchopt;
        system("cls");
        cout << "Enter 1 to search by time, 2 to search by location: ";
        cin >> searchopt;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid option!" << endl;
            cout << "Enter 1 to search by time, 2 to search by location: ";
            cin >> searchopt;
        }
        system("cls");
        cin.clear();
        cin.ignore(256, '\n');
        if (searchopt == 1)
            SearchByTime(vector_ticket);
        else if (searchopt == 2)
            SearchByPlace(vector_ticket);
        else cout << "\a";
        cout << "\n\nEnter 1 to continue searching.";
        cout << "\nEnter 2 to return to main menu.\n";
        cin >> cont_or_not;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid option!" << endl;
            cout << "\n\nEnter 1 to continue searching.";
            cout << "\nEnter 2 to return to main menu.\n";
            cin >> cont_or_not;
        }
    } while (cont_or_not == 1);
}

void SearchByPlace(vector<Ticket*>& vector_ticket) // Tran Thi Thuy Linh
{
    int typesearch;
    cout << "Enter 1 to search by place of departure, 2 to search by destination: ";
    cin >> typesearch;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid option!" << endl;
        cout << "Enter 1 to search by place of departure, 2 to search by destination: ";
        cin >> typesearch;
    }
    system("cls");
    cin.clear();
    cin.ignore(256, '\n');
    char place[50] = "";
    system("cls");
    if (typesearch == 1)
    {
        cout << "Enter the place of departure to search: ";
    }
    else if (typesearch == 2)
    {
        cout << "Enter the destination to search: ";
    }
    else cout << "\a";
    cin.getline(place, 50);
    Domestic_Ticket ticket;
    ticket.searchforticket(vector_ticket, place, typesearch);
}

void SearchByTime(vector<Ticket*>& vector_ticket) // Tran Thi Thuy Linh
{
    cout << "Enter the flight date you want to search (dd/mm/yyyy): ";
    int day, month, year;
    char sign;
    cin >> day >> sign >> month >> sign >> year;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid format!" << endl;
        cout << "Enter the flight date you want to search (dd/mm/yyyy): ";
        cin >> day >> sign >> month >> sign >> year;
    }
    system("cls");
    cin.clear();
    cin.ignore(256, '\n');
    Domestic_Ticket ticket;
    ticket.searchforticket(vector_ticket, day, month, year);
}


void Ticket::domes_flight_in_a_period(vector<Ticket*>& vector_ticket, int StartDay, int StartMonth, int StartYear, int EndDay, int EndMonth, int EndYear) //Tran Quang Dai
{
    int res = 0;
    vector<int> match_res;
    for (int i = 0; i < (int)vector_ticket.size(); i++) {
        if (checkDateInPeriod(vector_ticket[i]->depart_day, vector_ticket[i]->depart_month, vector_ticket[i]->depart_year, StartDay, StartMonth, StartYear, EndDay, EndMonth, EndYear) &&
            (vector_ticket[i]->ticket_type == 'd'))
        {
            match_res.push_back(i + 1);
            res++;
        }
    }
    if (res == 0)
        cout << "\nThere is no domestic flight during that period." << endl;
    else if (res == 1)
    {
        cout << "\nThere is 1 domestic flight during that period." << endl;
        Domestic_Ticket ticket;
        ticket.view_ticket(vector_ticket, match_res);
    }

    else
    {
        cout << "\nThere are " << res << " domestic flights during that period." << endl;
        Domestic_Ticket ticket;
        ticket.view_ticket(vector_ticket, match_res);
    }
    system("pause");
}

void DomesticFlightInAPeriod(vector<Ticket*>& vector_ticket) // Tran Thi Thuy Linh
{
    cout << "Enter the period you want to search." << endl;
    cout << "Enter the start date (dd/mm/yyyy): ";
    int StartDay, StartMonth, StartYear;
    char sign;
    cin >> StartDay >> sign >> StartMonth >> sign >> StartYear;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid format!" << endl;
        cout << "Enter the start date(dd/mm/yyyy): ";
        cin >> StartDay >> sign >> StartMonth >> sign >> StartYear;
    }
    cin.clear();
    cin.ignore(256, '\n');
    cout << "Enter the end date (dd/mm/yyyy): ";
    int EndDay, EndMonth, EndYear;
    cin >> EndDay >> sign >> EndMonth >> sign >> EndYear;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid format!" << endl;
        cout << "Enter the end date (dd/mm/yyyy): ";
        cin >> EndDay >> sign >> EndMonth >> sign >> EndYear;
    }
    system("cls");
    cin.clear();
    cin.ignore(256, '\n');
    Domestic_Ticket ticket;
    ticket.domes_flight_in_a_period(vector_ticket, StartDay, StartMonth, StartYear, EndDay, EndMonth, EndYear);
}

void Ticket::get_sale_detail(vector<Ticket*>& vector_ticket, int roll_number, int i) //Tran Quang Dai
{
    int ticket_sale;
    cout << "Enter the amount sold: ";  cin >> ticket_sale;
    long long total_commission = vector_ticket[i]->ticket_commission * ticket_sale;
    cout << "Enter selling date (dd/mm/yyyy): ";
    int sell_day, sell_month, sell_year;
    char sign;
    cin >> sell_day >> sign >> sell_month >> sign >> sell_year;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid format!" << endl;
        cout << "Enter the selling date(dd/mm/yyyy): ";
        cin >> sell_day >> sign >> sell_month >> sign >> sell_year;
    }
    cin.clear();
    cin.ignore(256, '\n');
    vector<int> one_record;
    one_record.push_back(sell_day);
    one_record.push_back(sell_month);
    one_record.push_back(sell_year);
    one_record.push_back(total_commission);
    sale_record.push_back(one_record);
}


void AddSaleRecord(vector<Ticket*>& vector_ticket) // Tran Quang Dai
{
    int cont_or_not = 0;
    do
    {
        cout << "\nDetails of the ticket sold:" << endl;
        int roll_number;
        cout << "Enter the roll number of the ticket: "; cin >> roll_number;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid roll number!" << endl;
            cout << "\nRe-Enter the roll number of the ticket sold: "; cin >> roll_number;

        }
        system("cls");
        cin.clear();
        cin.ignore(256, '\n');
        Domestic_Ticket ticket;
        int i = ticket.get_ticket_index(vector_ticket, roll_number);
        if (i == -1)
        {
            cout << "\nThere's no ticket with that roll number" << endl;
            system("pause");
            continue;
        }
        else
            vector_ticket[i]->view_ticket();
        cout << "\n*******************" << endl;
        ticket.get_sale_detail(vector_ticket, roll_number, i);
        cout << "\nSale record added successfully.\n";
        cout << "\n\nEnter 1 to add more sale records.";
        cout << "\nEnter 2 to return to main menu.\n";
        cin >> cont_or_not;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid option!" << endl;
            cout << "\n\nEnter 1 to add more sale records.";
            cout << "\nEnter 2 to return to main menu.\n";
            cin >> cont_or_not;
        }
        cin.clear();
        cin.ignore(256, '\n');
        system("cls");
    } while (cont_or_not == 1);

}

long long Ticket::commission_over_a_period(int startDay, int startMonth, int startYear, int endDay, int endMonth, int endYear) //Tran Quang Dai
{
    long long total_commission = 0;
    for (size_t i = 1; i < sale_record.size(); i++) {
        if (checkDateInPeriod(sale_record[i][0], sale_record[i][1], sale_record[i][2], startDay, startMonth, startYear, endDay, endMonth, endYear))
            total_commission += sale_record[i][3];
        //cout << sale_record[1][1];
        //total_commission = 1;
    }
    return total_commission;
}

void CommissionOverAPeriod() // Tran Thi Thuy Linh
{
    cout << "Enter the period you want to calculate. \n";
    cout << "\nEnter the start date(dd/mm/yyyy): ";
    int startDay, startMonth, startYear;
    char sign;
    cin >> startDay >> sign >> startMonth >> sign >> startYear;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid format!" << endl;
        cout << "\nEnter the start date(dd/mm/yyyy): ";
        cin >> startDay >> sign >> startMonth >> sign >> startYear;
    }
    cin.clear();
    cin.ignore(256, '\n');
    cout << "\nEnter the end date(dd/mm/yyyy): ";
    int endDay, endMonth, endYear;
    cin >> endDay >> sign >> endMonth >> sign >> endYear;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid format!" << endl;
        cout << "\nEnter the end date(dd/mm/yyyy): ";
        cin >> endDay >> sign >> endMonth >> sign >> endYear;
    }
    cin.clear();
    cin.ignore(256, '\n');
    Domestic_Ticket ticket;
    long long total_commission = ticket.commission_over_a_period(startDay, startMonth, startYear, endDay, endMonth, endYear);
    system("cls");
    printf("\nTotal commission received from %02d/%02d/%04d to %02d/%02d/%04d: ", startDay, startMonth, startYear, endDay, endMonth, endYear);
    FormatMoney(total_commission);
    system("pause");
}

void Ticket::export_file(vector<Ticket*>& vector_ticket) //Tran Quang Dai
{
    FILE* stream1 = NULL;
    errno_t err;
    err = fopen_s(&stream1, fndomesticket, "w");

    if (err == 0)
    {
        for (size_t i = 0; i < vector_ticket.size(); i++)
        {
            if (vector_ticket[i]->ticket_type == 'd')
            {
                fprintf_s(stream1, "%04d,%s,%s,%02d,%02d,%4d,%02d,%02d,%012lld,%012lld\n",
                    vector_ticket[i]->roll_number,
                    vector_ticket[i]->place_of_departure,
                    vector_ticket[i]->destination,
                    vector_ticket[i]->depart_day,
                    vector_ticket[i]->depart_month,
                    vector_ticket[i]->depart_year,
                    vector_ticket[i]->depart_hour,
                    vector_ticket[i]->depart_minute,
                    vector_ticket[i]->ticket_price,
                    vector_ticket[i]->ticket_commission
                );
            }
        }
        fclose(stream1);
    }
    else
    {
        printf("The file was not opened\n");
    }

    FILE* stream2 = NULL;
    err = fopen_s(&stream2, fninterticket, "w");

    if (err == 0)
    {
        for (size_t i = 0; i < vector_ticket.size(); i++)
        {

            if (vector_ticket[i]->ticket_type == 'i')
            {
                fprintf_s(stream2, "%04d,%s,%s,%02d,%02d,%4d,%02d,%02d,%012lld,%012lld\n",
                    vector_ticket[i]->roll_number,
                    vector_ticket[i]->place_of_departure,
                    vector_ticket[i]->destination,
                    vector_ticket[i]->depart_day,
                    vector_ticket[i]->depart_month,
                    vector_ticket[i]->depart_year,
                    vector_ticket[i]->depart_hour,
                    vector_ticket[i]->depart_minute,
                    vector_ticket[i]->ticket_price,
                    vector_ticket[i]->ticket_commission
                );
            }
        }
        fclose(stream2);
    }
    else
    {
        printf("The file was not opened\n");
    }


    FILE* stream3 = NULL;
    err = fopen_s(&stream3, fnsalerecord, "w");

    if (err == 0)
    {
        for (size_t i = 1; i < sale_record.size(); i++)
        {
            fprintf_s(stream1, "%02d,%02d,%04d,%012lld\n",
                sale_record[i][0],
                sale_record[i][1],
                sale_record[i][2],
                sale_record[i][3]
            );

        }
        fclose(stream3);
    }
    else
    {
        printf("The file %s was not opened\n", fnsalerecord);
    }
}

void exportfile(vector<Ticket*>& vector_ticket) //Nguyen Anh Duy
{
    Domestic_Ticket ticket;
    ticket.export_file(vector_ticket);
    cout << "\nExported file successfully!" << endl;
    system("pause");
}

vector<string> parse(string& str, char delimiter) //function to separate piece of information in a line from input file - Tran Quang Dai
{
    vector<string> res;
    string tmp;

    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == delimiter) {
            res.push_back(tmp);
            tmp.clear();
        }
        else tmp += str[i];
    }

    if (tmp.size() > 0)
        res.push_back(tmp);

    return res;
}


void Ticket::import_file(vector<Ticket*>& vector_ticket)  //Tran Quang Dai
{
    string line;
    ifstream inputFile1;
    inputFile1.open(fndomesticket, fstream::in);
    if (inputFile1.fail())
    {
        cout << "input failed" << endl;
        exit(1);
    }
    size_t i = 0;
    while (getline(inputFile1, line))
    {
        vector<string> data = parse(line, ',');
        vector_ticket.push_back(new Domestic_Ticket());
        vector_ticket[i]->roll_number = stoi(data[0]);
        vector_ticket[i]->ticket_type = 'd';
        strcpy_s(vector_ticket[i]->place_of_departure, 50, data[1].c_str());
        strcpy_s(vector_ticket[i]->destination, 50, data[2].c_str());
        vector_ticket[i]->depart_day = stoi(data[3]);
        vector_ticket[i]->depart_month = stoi(data[4]);
        vector_ticket[i]->depart_year = stoi(data[5]);
        vector_ticket[i]->depart_hour = stoi(data[6]);
        vector_ticket[i]->depart_minute = stoi(data[7]);
        vector_ticket[i]->ticket_price = stoi(data[8]);
        vector_ticket[i]->ticket_commission = stoi(data[9]);
        i++;
    }
    inputFile1.close();

    ifstream inputFile2;
    inputFile2.open(fninterticket, fstream::in);
    if (inputFile2.fail())
    {
        cout << "input failed" << endl;
        exit(1);
    }
    i = vector_ticket.size();
    while (getline(inputFile2, line))
    {
        vector<string> data = parse(line, ',');
        vector_ticket.push_back(new International_Ticket());
        vector_ticket[i]->roll_number = stoi(data[0]);
        vector_ticket[i]->ticket_type = 'i';
        strcpy_s(vector_ticket[i]->place_of_departure, 50, data[1].c_str());
        strcpy_s(vector_ticket[i]->destination, 50, data[2].c_str());
        vector_ticket[i]->depart_day = stoi(data[3]);
        vector_ticket[i]->depart_month = stoi(data[4]);
        vector_ticket[i]->depart_year = stoi(data[5]);
        vector_ticket[i]->depart_hour = stoi(data[6]);
        vector_ticket[i]->depart_minute = stoi(data[7]);
        vector_ticket[i]->ticket_price = stoi(data[8]);
        vector_ticket[i]->ticket_commission = stoi(data[9]);
        i++;
    }
    inputFile2.close();

    ifstream inputFile3;
    inputFile3.open(fnsalerecord, fstream::in);
    if (inputFile3.fail())
    {
        cout << "input failed" << endl;
        exit(1);
    }
    while (getline(inputFile3, line))
    {
        vector<string> data = parse(line, ',');
        vector<int> one_record;
        one_record.push_back(stoi(data[0]));
        one_record.push_back(stoi(data[1]));
        one_record.push_back(stoi(data[2]));
        one_record.push_back(stoi(data[3]));
        sale_record.push_back(one_record);
    }
    inputFile3.close();
}




void importfile(vector<Ticket*>& vector_ticket) //Nguyen Anh Duy
{
    Domestic_Ticket ticket;
    ticket.import_file(vector_ticket);
}


