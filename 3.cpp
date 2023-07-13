#include <bits/stdc++.h>
#include <chrono>
#include <ctime>

using namespace std;

class spaceTravel;
class date;
class planet;
class ticket;
class traveller;
class passenger;
class astronaut;
class commander;

vector<passenger *> passenger_list;
vector<ticket *> ticket_list;
vector<astronaut *> astronaut_list;
vector<commander *> commander_list;
map<int, int> monthToNumberOfDays = {{1, 31}, {2, 28}, {3, 31}, {4, 30}, {5, 31}, {6, 30}, {7, 31}, {8, 31}, {9, 30}, {10, 31}, {11, 30}, {12, 31}};

class spaceTravel
{
    static int count;

public:
    ::astronaut *astronaut;
    ::commander *commander;
    int spaceTravelId;
    vector<ticket *> tickets;
    vector<ticket *> ticketsReturn;
    void setAstronautId(int);
    void setCommanderId(int);
    void updateAstronaut(::astronaut *);
    void updateCommander(::commander *);

    spaceTravel(::astronaut *, ::commander *);

    // get and print functions:

    ::astronaut *getAstronaut();
    ::commander *getCommander();
    int getSpaceTravelId();
    vector<ticket *> getTickets();
    vector<ticket *> getTicketsReturn();

    void printAstronaut();
    void printCommander();
    void printSpaceTravelId();
    void printTickets();
    void printTicketsReturn();
    void printSpaceTravel();
};
class date
{
public:
    int day;
    int month;
    int year;
    date(int day, int month, int year);

    // get and print functions:

    int getDay();
    int getMonth();
    int getYear();

    void printDay();
    void printMonth();
    void printYear();
    void printDate();
};
class planet
{
public:
    int position_x;
    int position_y;
    int position_z;
    planet(int, int, int);

    // get and print functions:

    int getX();
    int getY();
    int getZ();

    void printX();
    void printY();
    void printZ();
    void printPlanet();
};
class ticket
{
public:
    static int count;
    int id;
    ::spaceTravel *spaceTravel;
    ::spaceTravel *spaceTravelReturn;
    float price;
    ::planet *source_station;
    ::planet *destination_station;
    ::date *date;
    ::passenger *passenger;
    ::date *return_date;
    bool is_return;

    ticket(::passenger *, planet *, planet *, ::date *, bool, ::date *);
    static ticket *bookTicket(::passenger *, planet *, planet *, ::date *, bool, ::date *);
    void cancelTicket();
    void updateTicket(planet *, ::date *, ::date *);

    // get and print functons:
    int getId();
    ::spaceTravel *getSpaceTravel();
    ::spaceTravel *getSpaceTravelReturn();
    float getPrice();
    ::planet *getSource_station();
    ::planet *getDestination_station();
    ::date *getDate();
    ::passenger *getPassenger();
    ::date *getReturn_date();
    bool getIfreturn();

    void printId();
    void printSpaceTravel();
    void printSpaceTravelReturn();
    void printPrice();
    void printSource_station();
    void printDestination_station();
    void printDate();
    void printPassenger();
    void printReturn_date();
    void printIfreturn();
    void printTicket();
};
class traveller
{
    static int count;

public:
    int id;
    int traveller_id;
    string name;

    bool verifyId();
    void updateId(int);
    traveller(string, int);
    traveller();
};
class astronaut : public traveller
{
    static int count;

public:
    int experience;
    int licenseId;
    string flyingLicense;

    astronaut(string, int, int);

    // get and print functions:

    int getExperience();
    int getLicenseId();
    string getFlyingLicense();
    int getId();
    int getTraveller_id();
    string getName();

    void printExperience();
    void printLicenseId();
    void printFlyingLicense();
    void printAstronaut();
    void printTraveller_id();
    void printId();
    void printName();
};
class passenger : public traveller
{
public:
    vector<ticket *> list_of_tickets;
    void addTicket(ticket *);
    passenger(string name, int id);

    // get and print functions:

    vector<ticket *> getList_of_tickets();
    int getId();
    int getTraveller_id();
    string getName();

    void printList_of_tickets();
    void printPassenger();
    void printTraveller_id();
    void printId();
    void printName();
};
class commander : public traveller
{
    static int count;

public:
    string authority;

    commander(string, string, int);
    // get and print functions:

    string getAuthority();
    int getId();
    int getTraveller_id();
    string getName();

    void printAuthority();
    void printCommander();
    void printTraveller_id();
    void printId();
    void printName();
};

int ticket::count = 0;
int traveller::count = 0;
int commander::count = 0;
int astronaut::count = 0;
int spaceTravel::count = 0;

int time_interval(date *d1, date *d2)
{
    int days1 = 365 * d1->year;
    for (int i = 1; i <= 12; i++)
    {
        days1 += (d1->month > i) * monthToNumberOfDays[d1->month];
    }
    days1 += d1->day;

    int days2 = 365 * d2->year;
    for (int i = 1; i <= 12; i++)
    {
        days2 += (d2->month > i) * monthToNumberOfDays[d2->month];
    }
    days2 += d2->day;

    return abs(days1 - days2);
}
float distance(planet *p1, planet *p2)
{
    return sqrt(1.0 * (pow((p1->position_x - p2->position_x), 2) + pow((p1->position_y - p2->position_y), 2) + pow((p1->position_z - p2->position_z), 2)));
}
int is_valid(::passenger *passenger)
{
    for (int i = 0; i < passenger_list.size(); i++)
    {
        if (passenger_list[i] == passenger)
            return 1;
    }
    return 0;
}

date::date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}

planet::planet(int x, int y, int z)
{
    this->position_x = x;
    this->position_y = y;
    this->position_z = z;
}

void ticket::updateTicket(planet *destination_station, ::date *date, ::date *return_date = NULL)
{
    if ((this->spaceTravel != NULL) && (this->spaceTravel->tickets.size() == 3 && this->spaceTravel->ticketsReturn.size() == 0))
    {
        astronaut *astronaut_temp = this->spaceTravel->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravel->commander;
        commander_list.push_back(commander_temp);
        if (this->spaceTravel->tickets[0] != this)
            this->spaceTravel->tickets[0]->spaceTravel = NULL;
        if (this->spaceTravel->tickets[1] != this)
            this->spaceTravel->tickets[1]->spaceTravel = NULL;
        if (this->spaceTravel->tickets[2] != this)
            this->spaceTravel->tickets[2]->spaceTravel = NULL;

        this->spaceTravel = NULL;
    }
    else if ((this->spaceTravel != NULL) && (this->spaceTravel->tickets.size() == 2 && this->spaceTravel->ticketsReturn.size() == 1))
    {
        astronaut *astronaut_temp = this->spaceTravel->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravel->commander;
        commander_list.push_back(commander_temp);

        this->spaceTravel->ticketsReturn[0]->spaceTravel = NULL;

        if (this->spaceTravel->tickets[0] != this)
            this->spaceTravel->tickets[0]->spaceTravel = NULL;
        else
            this->spaceTravel->tickets[1]->spaceTravel = NULL;

        this->spaceTravel = NULL;
    }
    else if ((this->spaceTravel != NULL) && (this->spaceTravel->tickets.size() == 1 && this->spaceTravel->ticketsReturn.size() == 2))
    {
        astronaut *astronaut_temp = this->spaceTravel->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravel->commander;
        commander_list.push_back(commander_temp);

        this->spaceTravel->ticketsReturn[0]->spaceTravel = NULL;
        this->spaceTravel->ticketsReturn[1]->spaceTravel = NULL;

        this->spaceTravel = NULL;
    }
    else if (this->spaceTravel != NULL)
    {
        for (int i = 0; i < this->spaceTravel->tickets.size(); i++)
        {
            if (this->spaceTravel->tickets[i] == this)
            {
                for (int j = i; j < this->spaceTravel->tickets.size() - 1; j++)
                {
                    this->spaceTravel->tickets[j] = this->spaceTravel->tickets[j + 1];
                }
                this->spaceTravel->tickets.pop_back();
                break;
            }
        }
    }
    if (this->is_return && this->spaceTravelReturn != NULL && (this->spaceTravelReturn->ticketsReturn.size() == 3 && this->spaceTravelReturn->tickets.size() == 0))
    {
        astronaut *astronaut_temp = this->spaceTravelReturn->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravelReturn->commander;
        commander_list.push_back(commander_temp);

        if (this->spaceTravelReturn->ticketsReturn[0] != this)
            this->spaceTravelReturn->ticketsReturn[0]->spaceTravelReturn = NULL;
        else
            this->spaceTravelReturn->ticketsReturn[1]->spaceTravelReturn = NULL;

        this->spaceTravelReturn = NULL;

        if (this->spaceTravelReturn->tickets[0] != this)
            this->spaceTravelReturn->tickets[0]->spaceTravel = NULL;
        if (this->spaceTravelReturn->tickets[1] != this)
            this->spaceTravelReturn->tickets[1]->spaceTravel = NULL;
        if (this->spaceTravelReturn->tickets[2] != this)
            this->spaceTravelReturn->tickets[2]->spaceTravel = NULL;

        this->spaceTravelReturn = NULL;
    }
    else if (this->is_return && this->spaceTravelReturn != NULL && (this->spaceTravelReturn->ticketsReturn.size() == 2 && this->spaceTravelReturn->tickets.size() == 1))
    {
        astronaut *astronaut_temp = this->spaceTravelReturn->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravelReturn->commander;
        commander_list.push_back(commander_temp);

        this->spaceTravelReturn->tickets[0]->spaceTravel = NULL;

        if (this->spaceTravelReturn->ticketsReturn[0] != this)
            this->spaceTravelReturn->ticketsReturn[0]->spaceTravelReturn = NULL;
        else
            this->spaceTravelReturn->ticketsReturn[1]->spaceTravelReturn = NULL;
        this->spaceTravelReturn = NULL;
    }
    else if (this->is_return && this->spaceTravelReturn != NULL && (this->spaceTravelReturn->ticketsReturn.size() == 1 && this->spaceTravelReturn->tickets.size() == 2))
    {
        astronaut *astronaut_temp = this->spaceTravelReturn->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravelReturn->commander;
        commander_list.push_back(commander_temp);

        this->spaceTravelReturn->tickets[0]->spaceTravel = NULL;
        this->spaceTravelReturn->tickets[1]->spaceTravel = NULL;
        this->spaceTravelReturn = NULL;
    }
    else if (this->is_return && this->spaceTravelReturn != NULL)
    {
        for (int i = 0; i < this->spaceTravelReturn->ticketsReturn.size(); i++)
        {
            if (this->spaceTravelReturn->ticketsReturn[i] == this)
            {
                for (int j = i; j < this->spaceTravelReturn->ticketsReturn.size() - 1; j++)
                {
                    this->spaceTravelReturn->ticketsReturn[j] = this->spaceTravelReturn->ticketsReturn[j + 1];
                }
                this->spaceTravelReturn->ticketsReturn.pop_back();
                break;
            }
        }
    }

    this->destination_station = destination_station;
    this->date = date;
    this->return_date = return_date;

    int count=0;
    ticket *ticketnormal1 = NULL;
    ticket *ticketnormal2 = NULL;
    ticket *ticketreturn1 = NULL;
    ticket *ticketreturn2 = NULL;

    for (int i = 0; i < ticket_list.size(); i++)
    {
        if (ticket_list[i]!=this && ticket_list[i]->source_station == source_station && ticket_list[i]->destination_station == destination_station && ticket_list[i]->date == date && (ticket_list[i]->spaceTravel == NULL || ((ticket_list[i]->spaceTravel->tickets.size() + ticket_list[i]->spaceTravel->ticketsReturn.size()) <= 10)))
        {
            count++;
            if (ticketnormal1 == NULL)
                ticketnormal1 = ticket_list[i];
            else
                ticketnormal2 = ticket_list[i];
        }
        if (ticket_list[i]->is_return && ticket_list[i]->spaceTravel != NULL && ticket_list[i]->destination_station == source_station && ticket_list[i]->source_station == destination_station && ticket_list[i]->return_date == date && (ticket_list[i]->spaceTravelReturn == NULL || ((ticket_list[i]->spaceTravelReturn->tickets.size() + ticket_list[i]->spaceTravelReturn->ticketsReturn.size()) <= 10)))
        {
            count++;
            if (ticketreturn1 == NULL)
                ticketreturn1 = ticket_list[i];
            else
                ticketreturn2 = ticket_list[i];
        }
    }
    if (count >= 3)
    {
            
        if (ticketnormal1 != NULL)
        {
            ticketnormal1->spaceTravel->tickets.push_back(this);
            this->spaceTravel = ticketnormal1->spaceTravel;
        }
        else
        {
            ticketreturn1->spaceTravelReturn->tickets.push_back(this);
            this->spaceTravel = ticketreturn1->spaceTravelReturn;
        }
    }
    else if (count == 2)
    {
        astronaut *astronaut_temp = astronaut_list[astronaut_list.size() - 1];
        astronaut_list.pop_back();
        commander *commander_temp = commander_list[commander_list.size() - 1];
        commander_list.pop_back();
        ::spaceTravel *spaceTravelTemp = new ::spaceTravel(astronaut_temp, commander_temp);

        if (ticketnormal1 == NULL)
        {
            spaceTravelTemp->ticketsReturn.push_back(ticketreturn1);
            spaceTravelTemp->ticketsReturn.push_back(ticketreturn2);
            spaceTravelTemp->tickets.push_back(this);

            ticketreturn1->spaceTravelReturn = spaceTravelTemp;
            ticketreturn2->spaceTravelReturn = spaceTravelTemp;
            this->spaceTravel = spaceTravelTemp;
        }
        else if (ticketreturn1 == NULL)
        {
            spaceTravelTemp->tickets.push_back(ticketnormal1);
            spaceTravelTemp->tickets.push_back(ticketnormal2);
            spaceTravelTemp->tickets.push_back(this);

            ticketnormal1->spaceTravel = spaceTravelTemp;
            ticketnormal1->spaceTravel = spaceTravelTemp;
            this->spaceTravel = spaceTravelTemp;
        }
        else
        {
            spaceTravelTemp->tickets.push_back(ticketnormal1);
            spaceTravelTemp->ticketsReturn.push_back(ticketreturn1);
            spaceTravelTemp->tickets.push_back(this);

            ticketnormal1->spaceTravel = spaceTravelTemp;
            ticketreturn1->spaceTravelReturn = spaceTravelTemp;
            this->spaceTravel = spaceTravelTemp;
        }
    }
    if (this->spaceTravel!=NULL && this->is_return)
    {

        int count=0;
        ticket *ticketnormal1 = NULL;
        ticket *ticketnormal2 = NULL;
        ticket *ticketreturn1 = NULL;
        ticket *ticketreturn2 = NULL;

        for (int i = 0; i < ticket_list.size(); i++)
        {
            if ( ticket_list[i]->source_station == destination_station && ticket_list[i]->destination_station == source_station && ticket_list[i]->date == return_date && (ticket_list[i]->spaceTravel == NULL || ((ticket_list[i]->spaceTravel->tickets.size() + ticket_list[i]->spaceTravel->ticketsReturn.size()) <= 10)))
            {
                count++;
                if (ticketnormal1 == NULL)
                    ticketnormal1 = ticket_list[i];
                else
                    ticketnormal2 = ticket_list[i];
            }
            if (ticket_list[i]!=this && ticket_list[i]->is_return && ticket_list[i]->spaceTravel != NULL && ticket_list[i]->source_station == source_station && ticket_list[i]->destination_station == destination_station && ticket_list[i]->return_date == return_date && (ticket_list[i]->spaceTravelReturn == NULL || ((ticket_list[i]->spaceTravelReturn->tickets.size() + ticket_list[i]->spaceTravelReturn->ticketsReturn.size()) <= 10)))
            {
                count++;
                if (ticketreturn1 == NULL)
                    ticketreturn1 = ticket_list[i];
                else
                    ticketreturn1 = ticket_list[i];
            }
        }
        if (count >= 3)
        {
            if (ticketnormal1 != NULL)
            {
                ticketnormal1->spaceTravel->ticketsReturn.push_back(this);
                this->spaceTravelReturn = ticketnormal1->spaceTravel;
            }
            else
            {
                ticketreturn1->spaceTravelReturn->ticketsReturn.push_back(this);
                this->spaceTravelReturn = ticketreturn1->spaceTravelReturn;
            }
        }
        else if (count == 2)
        {
            astronaut *astronaut_temp = astronaut_list[astronaut_list.size() - 1];
            astronaut_list.pop_back();
            commander *commander_temp = commander_list[commander_list.size() - 1];
            commander_list.pop_back();
            ::spaceTravel *spaceTravelTemp = new ::spaceTravel(astronaut_temp, commander_temp);

            if (ticketnormal1 == NULL)
            {
                spaceTravelTemp->ticketsReturn.push_back(ticketreturn1);
                spaceTravelTemp->ticketsReturn.push_back(ticketreturn2);
                spaceTravelTemp->ticketsReturn.push_back(this);

                ticketreturn1->spaceTravelReturn = spaceTravelTemp;
                ticketreturn2->spaceTravelReturn = spaceTravelTemp;
                this->spaceTravelReturn = spaceTravelTemp;
            }
            else if (ticketreturn1 == NULL)
            {
                spaceTravelTemp->tickets.push_back(ticketnormal1);
                spaceTravelTemp->tickets.push_back(ticketnormal2);
                spaceTravelTemp->ticketsReturn.push_back(this);

                ticketnormal1->spaceTravel = spaceTravelTemp;
                ticketnormal2->spaceTravel = spaceTravelTemp;
                this->spaceTravelReturn = spaceTravelTemp;
            }
            else
            {
                spaceTravelTemp->tickets.push_back(ticketnormal1);
                spaceTravelTemp->ticketsReturn.push_back(ticketreturn1);
                spaceTravelTemp->ticketsReturn.push_back(this);

                ticketnormal1->spaceTravel = spaceTravelTemp;
                ticketreturn1->spaceTravelReturn = spaceTravelTemp;
                this->spaceTravelReturn = spaceTravelTemp;

            }
        }
    }

    passenger->addTicket(this);
    ticket_list.push_back(this);


    ::date *curr_date = new ::date(0, 0, 0);

    auto now = std::chrono::system_clock::now();               // get current time
    std::time_t t = std::chrono::system_clock::to_time_t(now); // convert to time_t
    std::tm *cdate = std::localtime(&t);                       // convert to local time

    curr_date->day = cdate->tm_mday;
    curr_date->month = cdate->tm_mon + 1;
    curr_date->year = cdate->tm_year + 1900;

    this->price = (distance(source_station, destination_station)) / (1 + time_interval(date, curr_date));
    if (this->is_return)
        this->price += (distance(source_station, destination_station)) / (1 + time_interval(return_date, curr_date));
}
ticket *ticket::bookTicket(::passenger *passenger, planet *source_station, planet *destination_station, ::date *date, bool return_also, ::date *return_date = NULL)
{

    if (!is_valid(passenger))
    {
        return NULL;
    }
    ::date *curr_date = new ::date(0, 0, 0);

    auto now = std::chrono::system_clock::now();               // get current time
    std::time_t t = std::chrono::system_clock::to_time_t(now); // convert to time_t
    std::tm *cdate = std::localtime(&t);                       // convert to local time

    curr_date->day = cdate->tm_mday;
    curr_date->month = cdate->tm_mon + 1;
    curr_date->year = cdate->tm_year + 1900;

    ticket *ticket_to_be_updated1 = NULL;
    ticket *ticket_to_be_updated2 = NULL;
    if (time_interval(curr_date, date) > 10 * 365)
    {
        return NULL;
    }
    ticket *new_ticket = new ticket(passenger, source_station, destination_station, date, return_also, return_date);
    int count=0;
    ticket *ticketnormal1 = NULL;
    ticket *ticketnormal2 = NULL;
    ticket *ticketreturn1 = NULL;
    ticket *ticketreturn2 = NULL;

    for (int i = 0; i < ticket_list.size(); i++)
    {
        if (ticket_list[i]->source_station == source_station && ticket_list[i]->destination_station == destination_station && ticket_list[i]->date == date && (ticket_list[i]->spaceTravel == NULL || ((ticket_list[i]->spaceTravel->tickets.size() + ticket_list[i]->spaceTravel->ticketsReturn.size()) <= 10)))
        {
            count++;
            if (ticketnormal1 == NULL)
                ticketnormal1 = ticket_list[i];
            else
                ticketnormal2 = ticket_list[i];
        }
        if (ticket_list[i]->is_return && ticket_list[i]->spaceTravel != NULL && ticket_list[i]->destination_station == source_station && ticket_list[i]->source_station == destination_station && ticket_list[i]->return_date == date && (ticket_list[i]->spaceTravelReturn == NULL || ((ticket_list[i]->spaceTravelReturn->tickets.size() + ticket_list[i]->spaceTravelReturn->ticketsReturn.size()) <= 10)))
        {
            count++;
            if (ticketreturn1 == NULL)
                ticketreturn1 = ticket_list[i];
            else
                ticketreturn2 = ticket_list[i];
        }
    }
    if (count >= 3)
    {
        if (ticketnormal1 != NULL)
        {
            ticketnormal1->spaceTravel->tickets.push_back(new_ticket);
            new_ticket->spaceTravel = ticketnormal1->spaceTravel;
        }
        else
        {
            ticketreturn1->spaceTravelReturn->tickets.push_back(new_ticket);
            new_ticket->spaceTravel = ticketreturn1->spaceTravelReturn;
        }
    }
    if (count == 2)
    {
        astronaut *astronaut_temp = astronaut_list[astronaut_list.size() - 1];
        astronaut_list.pop_back();
        commander *commander_temp = commander_list[commander_list.size() - 1];
        commander_list.pop_back();
        ::spaceTravel *spaceTravelTemp = new ::spaceTravel(astronaut_temp, commander_temp);

        if (ticketnormal1 == NULL)
        {
            spaceTravelTemp->ticketsReturn.push_back(ticketreturn1);
            spaceTravelTemp->ticketsReturn.push_back(ticketreturn2);
            spaceTravelTemp->tickets.push_back(new_ticket);

            ticketreturn1->spaceTravelReturn = spaceTravelTemp;
            ticketreturn2->spaceTravelReturn = spaceTravelTemp;
            new_ticket->spaceTravel = spaceTravelTemp;
        }
        else if (ticketreturn1 == NULL)
        {
            spaceTravelTemp->tickets.push_back(ticketnormal1);
            spaceTravelTemp->tickets.push_back(ticketnormal2);
            spaceTravelTemp->tickets.push_back(new_ticket);

            ticketnormal1->spaceTravel = spaceTravelTemp;
            ticketnormal2->spaceTravel = spaceTravelTemp;
            new_ticket->spaceTravel = spaceTravelTemp;
            cout<<"hello"<<endl;
        }
        else
        {
            spaceTravelTemp->tickets.push_back(ticketnormal1);
            spaceTravelTemp->ticketsReturn.push_back(ticketreturn1);
            spaceTravelTemp->tickets.push_back(new_ticket);

            ticketnormal1->spaceTravel = spaceTravelTemp;
            ticketreturn1->spaceTravelReturn = spaceTravelTemp;
            new_ticket->spaceTravel = spaceTravelTemp;
        }
    }
    if (new_ticket->spaceTravel!=NULL && return_also)
    {

        int count=0;
        ticket *ticketnormal1 = NULL;
        ticket *ticketnormal2 = NULL;
        ticket *ticketreturn1 = NULL;
        ticket *ticketreturn2 = NULL;

        for (int i = 0; i < ticket_list.size(); i++)
        {
            if (ticket_list[i]->source_station == destination_station && ticket_list[i]->destination_station == source_station && ticket_list[i]->date == return_date && (ticket_list[i]->spaceTravel == NULL || ((ticket_list[i]->spaceTravel->tickets.size() + ticket_list[i]->spaceTravel->ticketsReturn.size()) <= 10)))
            {
                count++;
                if (ticketnormal1 == NULL)
                    ticketnormal1 = ticket_list[i];
                else
                    ticketnormal2 = ticket_list[i];
            }
            if (ticket_list[i]->is_return && ticket_list[i]->spaceTravel != NULL && ticket_list[i]->source_station == source_station && ticket_list[i]->destination_station == destination_station && ticket_list[i]->return_date == return_date && (ticket_list[i]->spaceTravelReturn == NULL || ((ticket_list[i]->spaceTravelReturn->tickets.size() + ticket_list[i]->spaceTravelReturn->ticketsReturn.size()) <= 10)))
            {
                count++;
                if (ticketreturn1 == NULL)
                    ticketreturn1 = ticket_list[i];
                else
                    ticketreturn1 = ticket_list[i];
            }
        }
        if (count >= 3)
        {
            if (ticketnormal1 != NULL)
            {
                ticketnormal1->spaceTravel->ticketsReturn.push_back(new_ticket);
                new_ticket->spaceTravelReturn = ticketnormal1->spaceTravel;
            }
            else
            {
                ticketreturn1->spaceTravelReturn->ticketsReturn.push_back(new_ticket);
                new_ticket->spaceTravelReturn = ticketreturn1->spaceTravelReturn;
            }
        }
        else if (count == 2)
        {
            astronaut *astronaut_temp = astronaut_list[astronaut_list.size() - 1];
            astronaut_list.pop_back();
            commander *commander_temp = commander_list[commander_list.size() - 1];
            commander_list.pop_back();
            ::spaceTravel *spaceTravelTemp = new ::spaceTravel(astronaut_temp, commander_temp);

            if (ticketnormal1 == NULL)
            {
                spaceTravelTemp->ticketsReturn.push_back(ticketreturn1);
                spaceTravelTemp->ticketsReturn.push_back(ticketreturn2);
                spaceTravelTemp->ticketsReturn.push_back(new_ticket);

                ticketreturn1->spaceTravelReturn = spaceTravelTemp;
                ticketreturn2->spaceTravelReturn = spaceTravelTemp;
                new_ticket->spaceTravelReturn = spaceTravelTemp;
            }
            else if (ticketreturn1 == NULL)
            {
                spaceTravelTemp->tickets.push_back(ticketnormal1);
                spaceTravelTemp->tickets.push_back(ticketnormal2);
                spaceTravelTemp->ticketsReturn.push_back(new_ticket);

                ticketnormal1->spaceTravel = spaceTravelTemp;
                ticketnormal2->spaceTravel = spaceTravelTemp;
                new_ticket->spaceTravelReturn = spaceTravelTemp;
            }
            else
            {
                spaceTravelTemp->tickets.push_back(ticketnormal1);
                spaceTravelTemp->ticketsReturn.push_back(ticketreturn1);
                spaceTravelTemp->ticketsReturn.push_back(new_ticket);

                ticketnormal1->spaceTravel = spaceTravelTemp;
                ticketreturn1->spaceTravelReturn = spaceTravelTemp;
                new_ticket->spaceTravelReturn = spaceTravelTemp;
            }
        }
    }

    passenger->list_of_tickets.push_back(new_ticket);
    ticket_list.push_back(new_ticket);

    for (int i = 0; i < ticket_list.size(); i++)
    {
        if (ticket_list[i]->spaceTravel == NULL)
            ticket_list[i]->spaceTravelReturn = NULL;
    }

    // for (int i = 0; i < ticket_list.size(); i++)
    // {
    //     ticket_list[i]->updateTicket(ticket_list[i]->destination_station, ticket_list[i]->date, ticket_list[i]->return_date);
    // }

    new_ticket->price = (distance(source_station, destination_station)) / (1 + time_interval(date, curr_date));
    if (return_also)
        new_ticket->price += (distance(source_station, destination_station)) / (1 + time_interval(return_date, curr_date));

    return new_ticket;
}
void ticket::cancelTicket()
{
    if ((this->spaceTravel != NULL) && (this->spaceTravel->tickets.size() == 3 && this->spaceTravel->ticketsReturn.size() == 0))
    {
        astronaut *astronaut_temp = this->spaceTravel->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravel->commander;
        commander_list.push_back(commander_temp);
        if (this->spaceTravel->tickets[0] != this)
            this->spaceTravel->tickets[0]->spaceTravel = NULL;
        if (this->spaceTravel->tickets[1] != this)
            this->spaceTravel->tickets[1]->spaceTravel = NULL;
        if (this->spaceTravel->tickets[2] != this)
            this->spaceTravel->tickets[2]->spaceTravel = NULL;

        this->spaceTravel = NULL;
    }
    else if ((this->spaceTravel != NULL) && (this->spaceTravel->tickets.size() == 2 && this->spaceTravel->ticketsReturn.size() == 1))
    {
        astronaut *astronaut_temp = this->spaceTravel->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravel->commander;
        commander_list.push_back(commander_temp);

        this->spaceTravel->ticketsReturn[0]->spaceTravel = NULL;

        if (this->spaceTravel->tickets[0] != this)
            this->spaceTravel->tickets[0]->spaceTravel = NULL;
        else
            this->spaceTravel->tickets[1]->spaceTravel = NULL;

        this->spaceTravel = NULL;
    }
    else if ((this->spaceTravel != NULL) && (this->spaceTravel->tickets.size() == 1 && this->spaceTravel->ticketsReturn.size() == 2))
    {
        astronaut *astronaut_temp = this->spaceTravel->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravel->commander;
        commander_list.push_back(commander_temp);

        this->spaceTravel->ticketsReturn[0]->spaceTravel = NULL;
        this->spaceTravel->ticketsReturn[1]->spaceTravel = NULL;

        this->spaceTravel = NULL;
    }
    else if (this->spaceTravel != NULL)
    {
        for (int i = 0; i < this->spaceTravel->tickets.size(); i++)
        {
            if (this->spaceTravel->tickets[i] == this)
            {
                for (int j = i; j < this->spaceTravel->tickets.size() - 1; j++)
                {
                    this->spaceTravel->tickets[j] = this->spaceTravel->tickets[j + 1];
                }
                this->spaceTravel->tickets.pop_back();
                break;
            }
        }
    }
    if (this->is_return && this->spaceTravelReturn != NULL && (this->spaceTravelReturn->ticketsReturn.size() == 3 && this->spaceTravelReturn->tickets.size() == 0))
    {
        astronaut *astronaut_temp = this->spaceTravelReturn->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravelReturn->commander;
        commander_list.push_back(commander_temp);

        if (this->spaceTravelReturn->ticketsReturn[0] != this)
            this->spaceTravelReturn->ticketsReturn[0]->spaceTravelReturn = NULL;
        else
            this->spaceTravelReturn->ticketsReturn[1]->spaceTravelReturn = NULL;

        this->spaceTravelReturn = NULL;

        if (this->spaceTravelReturn->tickets[0] != this)
            this->spaceTravelReturn->tickets[0]->spaceTravel = NULL;
        if (this->spaceTravelReturn->tickets[1] != this)
            this->spaceTravelReturn->tickets[1]->spaceTravel = NULL;
        if (this->spaceTravelReturn->tickets[2] != this)
            this->spaceTravelReturn->tickets[2]->spaceTravel = NULL;

        this->spaceTravelReturn = NULL;
    }
    else if (this->is_return && this->spaceTravelReturn != NULL && (this->spaceTravelReturn->ticketsReturn.size() == 2 && this->spaceTravelReturn->tickets.size() == 1))
    {
        astronaut *astronaut_temp = this->spaceTravelReturn->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravelReturn->commander;
        commander_list.push_back(commander_temp);

        this->spaceTravelReturn->tickets[0]->spaceTravel = NULL;

        if (this->spaceTravelReturn->ticketsReturn[0] != this)
            this->spaceTravelReturn->ticketsReturn[0]->spaceTravelReturn = NULL;
        else
            this->spaceTravelReturn->ticketsReturn[1]->spaceTravelReturn = NULL;
        this->spaceTravelReturn = NULL;
    }
    else if (this->is_return && this->spaceTravelReturn != NULL && (this->spaceTravelReturn->ticketsReturn.size() == 1 && this->spaceTravelReturn->tickets.size() == 2))
    {
        astronaut *astronaut_temp = this->spaceTravelReturn->astronaut;
        astronaut_list.push_back(astronaut_temp);
        commander *commander_temp = this->spaceTravelReturn->commander;
        commander_list.push_back(commander_temp);

        this->spaceTravelReturn->tickets[0]->spaceTravel = NULL;
        this->spaceTravelReturn->tickets[1]->spaceTravel = NULL;
        this->spaceTravelReturn = NULL;
    }
    else if (this->is_return && this->spaceTravelReturn != NULL)
    {
        for (int i = 0; i < this->spaceTravelReturn->ticketsReturn.size(); i++)
        {
            if (this->spaceTravelReturn->ticketsReturn[i] == this)
            {
                for (int j = i; j < this->spaceTravelReturn->ticketsReturn.size() - 1; j++)
                {
                    this->spaceTravelReturn->ticketsReturn[j] = this->spaceTravelReturn->ticketsReturn[j + 1];
                }
                this->spaceTravelReturn->ticketsReturn.pop_back();
                break;
            }
        }
    }
        cout<<"sid";
    for (int i = 0; i < ticket_list.size(); i++)
    {
        if (ticket_list[i] == this)
        {
            for (int j = i; j < ticket_list.size() - 1; j++)
            {
                ticket_list[j] = ticket_list[j + 1];
            }
            ticket_list.pop_back();
            break;
        }
    }
    for (int i = 0; i < ticket_list.size(); i++)
    {
        if (ticket_list[i]->spaceTravel == NULL)
            ticket_list[i]->spaceTravelReturn = NULL;
    }

    // for (int i = 0; i < ticket_list.size(); i++)
    // {
    //     ticket_list[i]->updateTicket(ticket_list[i]->destination_station, ticket_list[i]->date, ticket_list[i]->return_date);
    // }
}
ticket::ticket(::passenger *passenger, planet *source_station, planet *destination_station, ::date *date, bool return_also, ::date *return_date = NULL)
{
    this->spaceTravel = NULL;
    this->passenger = passenger;
    this->source_station = source_station;
    this->destination_station = destination_station;
    this->date = date;
    this->is_return = return_also;
    this->return_date = return_date;
    this->price = 0;
    this->spaceTravelReturn = NULL;
    this->id = count;
    ticket::count++;
}

bool traveller::verifyId()
{
    return this->name.length() > 0 && this->id >= 0;
}
void traveller::updateId(int newid)
{
    this->id = newid;
}
traveller::traveller(string name, int id)
{
    this->name = name;
    this->traveller_id = count;
    traveller::count++;
    this->id = id;
}
traveller::traveller()
{
    this->traveller_id = count;
    traveller::count++;
}

astronaut::astronaut(string name, int id, int experience)
{
    this->name = name;
    this->id = id;
    this->experience = experience;
    this->licenseId = count;
    astronaut::count++;
    this->flyingLicense = "LicenseId: " + to_string(licenseId);
    astronaut_list.push_back(this);
}

passenger::passenger(string name, int id) : traveller(name, id)
{
    passenger_list.push_back(this);
}
void passenger::addTicket(ticket *ticket)
{
    this->list_of_tickets.push_back(ticket);
}

commander::commander(string name, string authority, int id) : traveller(name, id)
{
    this->authority = authority;
    commander::count++;
    commander_list.push_back(this);
}

spaceTravel::spaceTravel(::astronaut *astronaut, ::commander *commander)
{
    this->astronaut = astronaut;
    this->commander = commander;
    this->spaceTravelId = count;
    this->count++;
}
void spaceTravel::setAstronautId(int idnew)
{
    this->astronaut->id = idnew;
}
void spaceTravel::setCommanderId(int idnew)
{
    this->commander->id = idnew;
}
void spaceTravel::updateAstronaut(::astronaut *astronautnew)
{
    ::astronaut *astronauttemp = this->astronaut;
    for (int i = 0; i < astronaut_list.size(); i++)
    {
        if (astronaut_list[i] == astronautnew)
        {
            astronaut_list[i] = astronauttemp;
        }
    }
    this->astronaut = astronautnew;
}
void spaceTravel::updateCommander(::commander *commandernew)
{
    ::commander *commandertemp = this->commander;
    for (int i = 0; i < commander_list.size(); i++)
    {
        if (commander_list[i] == commandernew)
        {
            commander_list[i] = commandertemp;
        }
    }
    this->commander = commandernew;
}

int main()
{
    planet *pl1 = new planet(1, 2, 3);
    planet *pl2 = new planet(4, 5, 6);
    planet *pl3 = new planet(7, 8, 9);

    passenger *p1 = new passenger("sid1", 1001);
    passenger *p2 = new passenger("sid2", 1011);
    passenger *p3 = new passenger("sid3", 1021);
    passenger *p4 = new passenger("sid4", 1031);
    passenger *p5 = new passenger("sid5", 1041);
    passenger *p6 = new passenger("sid6", 1051);
    passenger *p7 = new passenger("sid7", 1061);
    passenger *p8 = new passenger("sid8", 1071);
    passenger *p9 = new passenger("sid9", 1081);
    passenger *p10 = new passenger("sid10", 1091);
    passenger *p11 = new passenger("sid11", 1101);
    commander *c1 = new commander("kalra1", "authority1", 101);
    commander *c2 = new commander("kalra2", "authority1", 111);
    astronaut *a1 = new astronaut("ram1", 10001, 10);
    astronaut *a2 = new astronaut("ramw", 10011, 20);

    date *d1 = new date(21, 3, 2023);
    date *d2 = new date(22, 3, 2023);
    date *d3 = new date(23, 3, 2023);
    date *d4 = new date(21, 3, 2033);
    date *d5 = new date(21, 3, 2043);
    date *d6 = new date(21, 4, 2023);
    date *d7 = new date(24, 3, 2023);
    date *d8 = new date(25, 3, 2023);

    ticket *t1 = ticket::bookTicket(p1, pl1, pl2, d2, 0);//t1 from pl1 to pl2 on date d2
    ticket *t2 = ticket::bookTicket(p2, pl1, pl2, d2, 0);//t2 from pl1 to pl2 on date d2
    ticket *t4 = ticket::bookTicket(p4, pl2, pl1, d1, 0);//t4 from pl2 to pl2 on date d2
    ticket* t3=ticket::bookTicket(p3, pl2, pl3, d1, 1, d2);
    t3->printTicket();
    ticket *t5 = ticket::bookTicket(p5, pl2, pl1, d1, 0);
    t3->printTicket();
    cout<<endl;
    t3->updateTicket( pl1, d1, d2);
    t3->printTicket();
    cout<<endl;
    t1->cancelTicket();
    t3->printTicket();
    return 0;
}

// ------------------------------------GET AND PRINT FUNCTIONS--------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

::astronaut *spaceTravel::getAstronaut()
{
    return this->astronaut;
}
::commander *spaceTravel::getCommander()
{
    return this->commander;
}
int spaceTravel::getSpaceTravelId()
{
    return this->spaceTravelId;
}
vector<ticket *> spaceTravel::getTickets()
{
    return this->tickets;
}
vector<ticket *> spaceTravel::getTicketsReturn()
{
    return this->ticketsReturn;
}
void spaceTravel::printAstronaut()
{
    this->astronaut->printAstronaut();
}
void spaceTravel::printCommander()
{
    this->commander->printCommander();
}
void spaceTravel::printSpaceTravelId()
{
    cout << this->spaceTravelId << endl;
}
void spaceTravel::printTickets()
{
    for (int i = 0; i < this->tickets.size(); i++)
    {
        this->tickets[i]->printTicket();
    }
}
void spaceTravel::printTicketsReturn()
{
    for (int i = 0; i < this->ticketsReturn.size(); i++)
    {
        this->ticketsReturn[i]->printTicket();
    }
}
void spaceTravel::printSpaceTravel()
{
    cout << "printing space travel class:\n";
    this->printAstronaut();
    this->printCommander();
    this->printSpaceTravelId();
}

int date::getDay()
{
    return this->day;
}
int date::getMonth()
{
    return this->month;
}
int date::getYear()
{
    return this->year;
}
void date::printDay()
{
    cout << this->day << endl;
}
void date::printMonth()
{
    cout << this->month << endl;
}
void date::printYear()
{
    cout << this->year << endl;
}
void date::printDate()
{
    cout << "Date: " << this->day << "-" << this->month << "-" << this->year << endl;
}

int planet::getX()
{
    return this->position_x;
}
int planet::getY()
{
    return this->position_y;
}
int planet::getZ()
{
    return this->position_z;
}
void planet::printX()
{
    cout << this->position_x << endl;
}
void planet::printY()
{
    cout << this->position_y << endl;
}
void planet::printZ()
{
    cout << this->position_z << endl;
}
void planet::printPlanet()
{
    cout << "(" << this->position_x << ", " << this->position_y << ", " << this->position_z << ")" << endl;
}

int ticket::getId()
{
    return this->id;
}
::spaceTravel *ticket::getSpaceTravel()
{
    return this->spaceTravel;
}
::spaceTravel *ticket::getSpaceTravelReturn()
{
    return this->spaceTravelReturn;
}
float ticket::getPrice()
{
    return this->price;
}
::planet *ticket::getSource_station()
{
    return this->source_station;
}
::planet *ticket::getDestination_station()
{
    return this->destination_station;
}
::date *ticket::getDate()
{
    return this->date;
}
::passenger *ticket::getPassenger()
{
    return this->passenger;
}
::date *ticket::getReturn_date()
{
    return this->return_date;
}
bool ticket::getIfreturn()
{
    return this->is_return;
}
void ticket::printId()
{
    cout << "ticket id: " << this->id << endl;
}
void ticket::printSpaceTravel()
{
    this->spaceTravel->printSpaceTravel();
}
void ticket::printSpaceTravelReturn()
{
    this->spaceTravelReturn->printSpaceTravel();
}
void ticket::printPrice()
{
    cout << "ticket price: " << this->price << endl;
}
void ticket::printSource_station()
{
    cout << "from: ";
    this->source_station->printPlanet();
}
void ticket::printDestination_station()
{
    cout << "to: ";
    this->destination_station->printPlanet();
}
void ticket::printDate()
{
    this->date->printDate();
}
void ticket::printPassenger()
{
    this->passenger->printPassenger();
}
void ticket::printReturn_date()
{
    if (this->is_return)
        this->return_date->printDate();
}
void ticket::printIfreturn()
{
    cout << "return type: ";
    this->is_return ? cout << "return" : cout << "no return";
    cout << endl;
}
void ticket::printTicket()
{
    cout << "printing ticket: \n";
    cout << "Start ";
    this->printDate();
    this->printIfreturn();
    if (this->is_return)
        cout << "Return: ";
    this->printReturn_date();
    this->printSource_station();
    this->printDestination_station();
    this->printId();
    this->printPassenger();
    this->printPrice();
    cout << "space travel details: ";
    if (this->spaceTravel == NULL)
        cout << "no space travel formed, passenger cannot travel" << endl;
    else if (this->is_return && this->spaceTravelReturn == NULL)
        cout << "space travel formed for forward travel, but not for return , passenger cannot return" << endl;
    else if (!this->is_return && this->spaceTravel != NULL)
        cout << "space travelled formed successfully for one way travel" << endl;
    else if (this->is_return && this->spaceTravelReturn != NULL)
        cout << "space travel formed successfully for both way travel" << endl;
}

int astronaut::getExperience()
{
    return this->experience;
}
int astronaut::getLicenseId()
{
    return this->licenseId;
}
string astronaut::getFlyingLicense()
{
    return this->flyingLicense;
}
int astronaut::getId()
{
    return this->id;
}
int astronaut::getTraveller_id()
{
    return this->traveller_id;
}
string astronaut::getName()
{
    return this->name;
}
void astronaut::printExperience()
{
    cout << this->experience;
}
void astronaut::printLicenseId()
{
    cout << this->licenseId << endl;
}
void astronaut::printFlyingLicense()
{
    cout << this->flyingLicense << endl;
}
void astronaut::printTraveller_id()
{
    cout << this->traveller_id << endl;
}
void astronaut::printId()
{
    cout << this->id << endl;
}
void astronaut::printName()
{
    cout << this->name << endl;
}
void astronaut::printAstronaut()
{
    cout << "printing astronaut:\n";
    this->printExperience();
    this->printLicenseId();
    this->printFlyingLicense();
    this->printTraveller_id();
    this->printId();
    this->printName();
}

int passenger::getId()
{
    return this->id;
}
int passenger::getTraveller_id()
{
    return this->traveller_id;
}
string passenger::getName()
{
    return this->name;
}
vector<ticket *> passenger::getList_of_tickets()
{
    return this->list_of_tickets;
}
void passenger::printList_of_tickets()
{
    for (int i = 0; i < this->list_of_tickets.size(); i++)
    {
        this->list_of_tickets[i]->printTicket();
    }
}
void passenger::printTraveller_id()
{
    cout << "passenger traveller id: " << this->traveller_id << endl;
}
void passenger::printId()
{
    cout << "passenger id: " << this->id << endl;
}
void passenger::printName()
{
    cout << "passenger name: " << this->name << endl;
}
void passenger::printPassenger()
{
    cout << "printing passenger:\n";
    this->printId();
    this->printName();
    this->printTraveller_id();
}

string commander::getAuthority()
{
    return this->authority;
}
int commander::getId()
{
    return this->id;
}
int commander::getTraveller_id()
{
    return this->traveller_id;
}
string commander::getName()
{
    return this->name;
}
void commander::printAuthority()
{
    cout << this->authority;
}
void commander::printTraveller_id()
{
    cout << this->traveller_id << endl;
}
void commander::printId()
{
    cout << this->id << endl;
}
void commander::printName()
{
    cout << this->name << endl;
}
void commander::printCommander()
{
    cout << "printing commander\n";
    this->printAuthority();
    this->printId();
    this->printName();
    this->printTraveller_id();
}