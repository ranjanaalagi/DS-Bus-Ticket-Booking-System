/*
     BUS TICKET BOOKING SYSTEM
     --------------------------------
     Turbo C++ compatible program.

     Data Structures / Algorithms Used:
     1. Array     - Bus seats and bus information
     2. Linked List - Stores booked passengers
     3. Queue       - Stores waiting passengers
     4. Stack     - Stores cancelled tickets
     5. Linear Search - Searches passenger by ticket number
     6. Bubble Sort - Sorts passengers by seat number

     Input validation:
     - Passenger name accepts only letters and spaces
     - Age accepts 1 to 120
     - Mobile number accepts exactly 10 digits
     - Date accepts DD/MM/YYYY and rejects past/invalid dates
     - Menu and berth choices are validated

     Written for Turbo C++ / college demonstration.
*/

#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <dos.h>

/*
     BUS TICKET BOOKING SYSTEM
     DATA STRUCTURES:
     1. Array
     2. Linked List
     3. Queue
     4. Stack
     5. Linear Search
     6. Bubble Sort

     Turbo C++ version
*/

// Passenger class: stores all details of a booked passenger.
class Passenger
{

public:
  int ticketNo;
  char name[50];
  int age;
  char mobile[11];
  char date[15];
  char route[50];
  char busNo[20];
  char busName[50];
  char busType[15];
  int seatNo;
  char berth[10];
  int price;
  int routeIndex;
  int busIndex;
  Passenger *next;

     Passenger()
     {
       ticketNo=0; age=0; seatNo=0; price=0;
       routeIndex=-1; busIndex=-1;
       name[0]='\0'; mobile[0]='\0'; date[0]='\0';
       route[0]='\0'; busNo[0]='\0'; busName[0]='\0';
       busType[0]='\0'; berth[0]='\0';
       next=NULL;
     }
};

// Bus class: stores bus number, name, prices and seat status.
class Bus
{
public:
   char busNo[20];
   char busName[50];
   int acPrice;
   int nonAcPrice;
   int seats[20];

     Bus()
     {
       int i;
       busNo[0]='\0';
       busName[0]='\0';
       acPrice=0;

         nonAcPrice=0;
         for(i=0;i<20;i++) seats[i]=0;
     }
};

// WaitingPassenger class: stores details of a passenger in the waiting queue.
class WaitingPassenger
{
public:
   char name[50];
   int age;
   char mobile[11];
   char date[15];
   char route[50];
   char busNo[20];
   char busName[50];
   char busType[15];
   char berth[10];
};

Bus buses[8][3];
int busCount[8];

WaitingPassenger *waitingQueue[8][3][20];
int frontQ[8][3];
int rearQ[8][3];
int countQ[8][3];

Passenger cancelledStack[20];
int topStack=-1;

Passenger *head=NULL;
int ticketCounter=1001;

/* Function declaration used before its definition */
void addWaiting(Bus &bus,char route[],int r,int b);


/*--------------------------------------------------
               BASIC NUMBER INPUT
--------------------------------------------------*/
int getNumber()
{
   char x[15];

    int i,value;

    while(1)
    {
      cin >> x;

        if(strlen(x)==0)
        {
            cout<<"Enter numbers only: ";
            continue;
        }

        for(i=0;i<strlen(x);i++)
        {
           if(x[i]<'0' || x[i]>'9')
               break;
        }

        if(i==strlen(x))
        {
            value=0;
            for(i=0;i<strlen(x);i++)
               value=value*10+(x[i]-'0');
            return value;
        }

        cout<<"Invalid input! Enter numbers only: ";
    }
}


/*--------------------------------------------------
                 NAME VALIDATION
--------------------------------------------------*/
// Read and validate passenger name.
   void getName(char name[])
{
   int valid,i;

    cout<<"Enter passenger name: ";
    cin.ignore(100,'\n');

    do
    {

      valid=1;

      cin.getline(name,50);

      if(strlen(name)==0)
          valid=0;

      for(i=0;i<strlen(name);i++)
      {
         if((name[i]>='A' && name[i]<='Z') ||
            (name[i]>='a' && name[i]<='z') ||
            name[i]==' ')
         {
         }
         else
         {
             valid=0;
             break;
         }
      }

      if(valid==0)
          cout<<"Invalid name! Use letters and spaces only.\n";

    }while(valid==0);
}


/*--------------------------------------------------
                  AGE VALIDATION
--------------------------------------------------*/
int getAge()
{
   int age;

    do
    {
      cout<<"Enter age: ";
      age=getNumber();

      if(age<1 || age>120)
          cout<<"Invalid age! Enter age from 1 to 120.\n";

    }while(age<1 || age>120);

    return age;
}


/*--------------------------------------------------
               MOBILE VALIDATION
--------------------------------------------------*/
// Read and validate 10-digit mobile number.
   void getMobile(char mobile[])
{
   int valid,i;

    do
    {
      valid=1;

      cout<<"Enter 10 digit mobile number: ";
      cin>>mobile;

      if(strlen(mobile)!=10)
          valid=0;
      else
      {
          for(i=0;i<10;i++)
          {
             if(mobile[i]<'0' || mobile[i]>'9')
             {
                valid=0;
                break;
             }
          }
      }

      if(valid==1)
      {
          if(mobile[0]<'6' || mobile[0]>'9')
             valid=0;
      }

      if(valid==0)
          cout<<"Invalid mobile number!\n";

    }while(valid==0);

}


/*--------------------------------------------------
             DATE VALIDATION
   Uses computer's current date.
   Past dates are not accepted.
--------------------------------------------------*/
// Read and validate a real current/future date.
   void getDate(char date[])
{
   struct date today;
   int d,m,y,maxDays,valid,i;

    getdate(&today);

    do
    {
      valid=1;

      cout<<"Enter travel date (DD/MM/YYYY): ";
      cin>>date;

      if(strlen(date)!=10)
          valid=0;

      if(valid==1)
      {
          if(date[2]!='/' || date[5]!='/')
              valid=0;
      }

      if(valid==1)
      {
          for(i=0;i<10;i++)
          {
             if(i==2 || i==5)
                 continue;

            if(date[i]<'0' || date[i]>'9')
            {
                valid=0;
                break;
            }

    }
}

if(valid==1)
{
    d=(date[0]-'0')*10+(date[1]-'0');
    m=(date[3]-'0')*10+(date[4]-'0');

    y=(date[6]-'0')*1000+
     (date[7]-'0')*100+
     (date[8]-'0')*10+
     (date[9]-'0');

    if(y<1900 || y>2100)
        valid=0;

    if(m<1 || m>12)
       valid=0;

    if(m==2)
    {
       if((y%400==0) || (y%4==0 && y%100!=0))
           maxDays=29;
       else
           maxDays=28;
    }
    else if(m==4 || m==6 || m==9 || m==11)
       maxDays=30;
    else
       maxDays=31;

    if(d<1 || d>maxDays)
        valid=0;
}

/* Reject dates before today's computer date */
if(valid==1)
{
    if(y<today.da_year)
        valid=0;
    else if(y==today.da_year && m<today.da_mon)
        valid=0;
    else if(y==today.da_year &&
          m==today.da_mon &&

               d<today.da_day)
             valid=0;
      }

      if(valid==0)
      {
          cout<<"Invalid date! Enter today or a future date.\n";
      }

    }while(valid==0);
}


/*--------------------------------------------------
               CREATE BUS DETAILS
--------------------------------------------------*/
void createBuses()
{
   int i,r,b;

    for(r=0;r<8;r++)
    {
       busCount[r]=0;
       for(b=0;b<3;b++)
       {
          frontQ[r][b]=0;
          rearQ[r][b]=-1;
          countQ[r][b]=0;
       }
    }

    /* Route 1 */
    busCount[0]=3;

    strcpy(buses[0][0].busNo,"MH01 101");
    strcpy(buses[0][0].busName,"Neeta Travels");
    buses[0][0].acPrice=650;
    buses[0][0].nonAcPrice=400;

    strcpy(buses[0][1].busNo,"MH01 202");
    strcpy(buses[0][1].busName,"Purple Bus");
    buses[0][1].acPrice=600;
    buses[0][1].nonAcPrice=350;

strcpy(buses[0][2].busNo,"MH01 303");
strcpy(buses[0][2].busName,"Shivneri Bus");
buses[0][2].acPrice=700;
buses[0][2].nonAcPrice=450;

/* Route 2 */
busCount[1]=2;

strcpy(buses[1][0].busNo,"MH12 404");
strcpy(buses[1][0].busName,"Neeta Travels");
buses[1][0].acPrice=650;
buses[1][0].nonAcPrice=400;

strcpy(buses[1][1].busNo,"MH12 505");
strcpy(buses[1][1].busName,"Purple Bus");
buses[1][1].acPrice=600;
buses[1][1].nonAcPrice=350;

/* Route 3 */
busCount[2]=2;

strcpy(buses[2][0].busNo,"MH01 606");
strcpy(buses[2][0].busName,"VRL Travels");
buses[2][0].acPrice=1000;
buses[2][0].nonAcPrice=650;

strcpy(buses[2][1].busNo,"MH01 707");
strcpy(buses[2][1].busName,"SRS Travels");
buses[2][1].acPrice=1100;
buses[2][1].nonAcPrice=700;

/* Route 4 */
busCount[3]=2;

strcpy(buses[3][0].busNo,"KA01 808");
strcpy(buses[3][0].busName,"VRL Travels");
buses[3][0].acPrice=1000;
buses[3][0].nonAcPrice=650;

strcpy(buses[3][1].busNo,"KA01 909");
strcpy(buses[3][1].busName,"SRS Travels");
buses[3][1].acPrice=1100;
buses[3][1].nonAcPrice=700;

/* Route 5 */
busCount[4]=2;

strcpy(buses[4][0].busNo,"MH01 111");
strcpy(buses[4][0].busName,"Paulo Travels");
buses[4][0].acPrice=900;
buses[4][0].nonAcPrice=550;

strcpy(buses[4][1].busNo,"MH01 222");
strcpy(buses[4][1].busName,"Orange Travels");
buses[4][1].acPrice=950;
buses[4][1].nonAcPrice=600;

/* Route 6 */
busCount[5]=1;

strcpy(buses[5][0].busNo,"GA01 333");
strcpy(buses[5][0].busName,"Paulo Travels");
buses[5][0].acPrice=900;
buses[5][0].nonAcPrice=550;

/* Route 7 */
busCount[6]=1;

strcpy(buses[6][0].busNo,"MH01 444");
strcpy(buses[6][0].busName,"Shivneri Bus");
buses[6][0].acPrice=450;
buses[6][0].nonAcPrice=280;

/* Route 8 */
busCount[7]=1;

strcpy(buses[7][0].busNo,"MH15 555");
strcpy(buses[7][0].busName,"Shivneri Bus");
buses[7][0].acPrice=450;
buses[7][0].nonAcPrice=280;

/*
     Demo condition:
     Mumbai -> Pune, Neeta Travels
     Seats 1-19 booked, seat 20 available.
*/
for(i=0;i<19;i++)
   buses[0][0].seats[i]=1;

    buses[0][0].seats[19]=0;
}


/*--------------------------------------------------
                 ROUTES
--------------------------------------------------*/
// Display all available routes.
   void displayRoutes()
{
   cout<<"\n============================================\n";
   cout<<"               AVAILABLE ROUTES\n";
   cout<<"============================================\n";
   cout<<"1. Mumbai -> Pune\n";
   cout<<"2. Pune -> Mumbai\n";
   cout<<"3. Mumbai -> Karnataka\n";
   cout<<"4. Karnataka -> Mumbai\n";
   cout<<"5. Mumbai -> Goa\n";
   cout<<"6. Goa -> Mumbai\n";
   cout<<"7. Mumbai -> Nashik\n";
   cout<<"8. Nashik -> Mumbai\n";
}


/*--------------------------------------------------
              ROUTE NAME
--------------------------------------------------*/
void getRouteName(int choice,char route[])
{
   if(choice==1) strcpy(route,"Mumbai -> Pune");
   else if(choice==2) strcpy(route,"Pune -> Mumbai");
   else if(choice==3) strcpy(route,"Mumbai -> Karnataka");
   else if(choice==4) strcpy(route,"Karnataka -> Mumbai");
   else if(choice==5) strcpy(route,"Mumbai -> Goa");
   else if(choice==6) strcpy(route,"Goa -> Mumbai");
   else if(choice==7) strcpy(route,"Mumbai -> Nashik");
   else strcpy(route,"Nashik -> Mumbai");
}


/*--------------------------------------------------
             AVAILABLE SEATS
--------------------------------------------------*/

// Count seats whose value is 0 (available).
   int availableSeats(Bus &bus)
{
   int i,count=0;

    for(i=0;i<20;i++)
       if(bus.seats[i]==0)
           count++;

    return count;
}


/*--------------------------------------------------
               DISPLAY SEATS
--------------------------------------------------*/
// Display booked/available status of all 20 seats.
   void displaySeats(Bus &bus)
{
   int i;

    cout<<"\n========== SEAT STATUS ==========\n";

    for(i=0;i<20;i++)
    {
       cout<<"Seat "<<i+1<<" : ";

        if(bus.seats[i]==0)
            cout<<"Available";
        else
            cout<<"Booked";

        cout<<"\n";
    }
}


/*--------------------------------------------------
             LINKED LIST INSERT
--------------------------------------------------*/
// Add a passenger node at the end of the linked list.
   void addPassenger(Passenger *p)
{
   Passenger *temp;

    if(head==NULL)
        head=p;
    else
    {
        temp=head;

        while(temp->next!=NULL)
          temp=temp->next;

        temp->next=p;
    }
}


/*--------------------------------------------------
            SET PASSENGER DETAILS
--------------------------------------------------*/
void setPassenger(
   Passenger *p,
   int ticketNo,
   char name[],
   int age,
   char mobile[],
   char date[],
   char route[],
   Bus &bus,
   char busType[],
   int seatNo,
   char berth[],
   int price,
   int r,
   int b)
{
   p->ticketNo=ticketNo;
   strcpy(p->name,name);
   p->age=age;
   strcpy(p->mobile,mobile);
   strcpy(p->date,date);
   strcpy(p->route,route);
   strcpy(p->busNo,bus.busNo);
   strcpy(p->busName,bus.busName);
   strcpy(p->busType,busType);
   p->seatNo=seatNo;

    strcpy(p->berth,berth);
    p->price=price;
    p->routeIndex=r;
    p->busIndex=b;
    p->next=NULL;
}


/*--------------------------------------------------
                 PRINT TICKET
--------------------------------------------------*/
void printTicket(Passenger *p)
{
   cout<<"\n============================================\n";
   cout<<"             TICKET BOOKED SUCCESSFULLY\n";
   cout<<"============================================\n";
   cout<<"*** TICKET NUMBER : "<<p->ticketNo<<" ***\n";
   cout<<"============================================\n";
   cout<<"Date             : "<<p->date<<"\n";
   cout<<"Route             : "<<p->route<<"\n";
   cout<<"Bus No.            : "<<p->busNo<<"\n";
   cout<<"Bus Name : "<<p->busName<<"\n";
   cout<<"Passenger : "<<p->name<<"\n";
   cout<<"Age              : "<<p->age<<"\n";
   cout<<"Mobile            : "<<p->mobile<<"\n";
   cout<<"Bus Type : "<<p->busType<<"\n";
   cout<<"Seat No. : "<<p->seatNo<<"\n";
   cout<<"Berth            : "<<p->berth<<"\n";
   cout<<"Ticket Price : Rs. "<<p->price<<"\n";
   cout<<"============================================\n";
cout<<"----------------------------------------------------\n";
cout<<"          THANK YOU FOR BOOKING WITH US!\n";
cout<<"            HAVE A SAFE & HAPPY JOURNEY!\n";
cout<<"----------------------------------------------------\n";

cout << "\nPress any key to continue...";
getch();
}


/*--------------------------------------------------
                 BOOK TICKET
--------------------------------------------------*/
// Book an available seat or add the passenger to the waiting queue.

    void bookTicket()
{
    int routeChoice,busChoice,typeChoice;
    int seatNo,berthChoice,age,price;
    int r,b,ticketNo;

    char route[50];
    char busType[15];
    char berth[10];
    char name[50];
    char mobile[11];
    char date[15];

    Passenger *p;
    Bus *bus;

    displayRoutes();

    do
    {
      cout<<"Enter route choice: ";
      routeChoice=getNumber();

        if(routeChoice<1 || routeChoice>8)
            cout<<"Invalid route choice!\n";

    }while(routeChoice<1 || routeChoice>8);

    r=routeChoice-1;
    getRouteName(routeChoice,route);

    cout<<"\n========== AVAILABLE BUSES ==========\n";

    for(b=0;b<busCount[r];b++)
    {
       cout<<"\n"<<b+1<<". "<<buses[r][b].busNo
         <<" - "<<buses[r][b].busName<<"\n";

        cout<<"AC Price : Rs. "<<buses[r][b].acPrice<<"\n";
        cout<<"Non-AC Price : Rs. "<<buses[r][b].nonAcPrice<<"\n";
        cout<<"Available Seats : "<<availableSeats(buses[r][b])<<"\n";
    }

    do

{
    cout<<"\nSelect bus: ";
    busChoice=getNumber();

    if(busChoice<1 || busChoice>busCount[r])
        cout<<"Invalid bus choice!\n";

}while(busChoice<1 || busChoice>busCount[r]);

b=busChoice-1;
bus=&buses[r][b];

/* Full bus */
if(availableSeats(*bus)==0)
{
    cout<<"\nALL SEATS BOOKED.\n";
    addWaiting(*bus,route,r,b);
    return;
}

cout<<"\n========== BUS TYPE ==========\n";
cout<<"1. AC   - Rs. "<<bus->acPrice<<"\n";
cout<<"2. Non-AC - Rs. "<<bus->nonAcPrice<<"\n";

do
{
  cout<<"Select bus type: ";
  typeChoice=getNumber();

    if(typeChoice!=1 && typeChoice!=2)
        cout<<"Invalid choice!\n";

}while(typeChoice!=1 && typeChoice!=2);

if(typeChoice==1)
{
    strcpy(busType,"AC");
    price=bus->acPrice;
}
else
{
    strcpy(busType,"Non-AC");
    price=bus->nonAcPrice;
}

displaySeats(*bus);

while(1)
{
  cout<<"\nEnter seat number: ";
  seatNo=getNumber();

    if(seatNo<1 || seatNo>20)
        cout<<"Seat number must be 1 to 20.\n";
    else if(bus->seats[seatNo-1]==1)
        cout<<"This seat is already booked!\n";
    else
        break;
}

cout<<"\n========== PASSENGER DETAILS ==========\n";

getName(name);
age=getAge();
getMobile(mobile);
getDate(date);

cout<<"\n========== BERTH ==========\n";
cout<<"1. Upper\n";
cout<<"2. Lower\n";

do
{
  cout<<"Select berth: ";
  berthChoice=getNumber();

    if(berthChoice!=1 && berthChoice!=2)
        cout<<"Invalid choice!\n";

}while(berthChoice!=1 && berthChoice!=2);

if(berthChoice==1)
    strcpy(berth,"Upper");
else
    strcpy(berth,"Lower");

ticketNo=ticketCounter++;

    bus->seats[seatNo-1]=1;

    p=new Passenger;

    setPassenger(p,ticketNo,name,age,mobile,date,route,
           *bus,busType,seatNo,berth,price,r,b);

    addPassenger(p);

    printTicket(p);
}


/*--------------------------------------------------
               ADD TO WAITING QUEUE
--------------------------------------------------*/
void addWaiting(Bus &bus,char route[],int r,int b)
{
   WaitingPassenger p;
   int typeChoice,berthChoice;

    if(countQ[r][b]>=20)
    {
        cout<<"Waiting queue is full!\n";
        return;
    }

    cout<<"\n========== WAITING TICKET ==========\n";

    getName(p.name);
    p.age=getAge();
    getMobile(p.mobile);
    getDate(p.date);

    cout<<"\n1. AC\n";
    cout<<"2. Non-AC\n";

    do
    {
      cout<<"Select bus type: ";
      typeChoice=getNumber();

      if(typeChoice!=1 && typeChoice!=2)
          cout<<"Invalid choice!\n";

    }while(typeChoice!=1 && typeChoice!=2);

    if(typeChoice==1)
        strcpy(p.busType,"AC");
    else
        strcpy(p.busType,"Non-AC");

    cout<<"\n1. Upper\n";
    cout<<"2. Lower\n";

    do
    {
      cout<<"Select berth: ";
      berthChoice=getNumber();

      if(berthChoice!=1 && berthChoice!=2)
          cout<<"Invalid choice!\n";

    }while(berthChoice!=1 && berthChoice!=2);

    if(berthChoice==1)
        strcpy(p.berth,"Upper");
    else
        strcpy(p.berth,"Lower");

    strcpy(p.route,route);
    strcpy(p.busNo,bus.busNo);
    strcpy(p.busName,bus.busName);

    rearQ[r][b]++;

    waitingQueue[r][b][rearQ[r][b]]=new WaitingPassenger;
    *waitingQueue[r][b][rearQ[r][b]]=p;
    countQ[r][b]++;

    cout<<"\nWaiting passenger added successfully.\n";
    cout<<"Waiting Number : "<<countQ[r][b]<<"\n";
}


/*--------------------------------------------------
        GIVE FREED SEAT TO WAITING PASSENGER
--------------------------------------------------*/

void giveSeatToWaiting(int r,int b,int seatNo)
{
  WaitingPassenger p;
  Passenger *newP;
  Bus &bus=buses[r][b];
  int price,ticketNo,i;

  if(countQ[r][b]==0)
      return;

  cout<<"\nA passenger is waiting for this bus.\n";
  cout<<"Giving freed Seat "<<seatNo
    <<" to first waiting passenger.\n";

  p=*waitingQueue[r][b][frontQ[r][b]];

  delete waitingQueue[r][b][frontQ[r][b]];

  /* Shift the remaining queue elements forward. */
  for(i=frontQ[r][b]; i<rearQ[r][b]; i++)
  {
     waitingQueue[r][b][i]=waitingQueue[r][b][i+1];
  }

  waitingQueue[r][b][rearQ[r][b]]=NULL;
  rearQ[r][b]--;
  countQ[r][b]--;

  if(countQ[r][b]==0)
  {
      frontQ[r][b]=0;
      rearQ[r][b]=-1;
  }

  if(strcmp(p.busType,"AC")==0)
      price=bus.acPrice;
  else
      price=bus.nonAcPrice;

  ticketNo=ticketCounter++;
  bus.seats[seatNo-1]=1;

  newP=new Passenger;

    setPassenger(newP,ticketNo,p.name,p.age,p.mobile,p.date,
           p.route,bus,p.busType,seatNo,p.berth,
           price,r,b);

    addPassenger(newP);

    cout<<"\nWaiting passenger is now BOOKED.\n";
    printTicket(newP);
}

/*--------------------------------------------------
                 CANCEL TICKET
--------------------------------------------------*/
// Cancel a ticket, push it to the stack and assign the seat to the queue.
   void cancelTicket()
{
   int ticketNo,r,b,seatNo;
   Passenger *temp,*prev;

    cout<<"\n========== CANCEL TICKET ==========\n";
    cout<<"Enter Ticket Number: ";
    ticketNo=getNumber();

    temp=head;
    prev=NULL;

    while(temp!=NULL)
    {
      if(temp->ticketNo==ticketNo)
          break;

        prev=temp;
        temp=temp->next;
    }

    if(temp==NULL)
    {
        cout<<"Ticket not found!\n";
        return;
    }

    r=temp->routeIndex;
    b=temp->busIndex;
    seatNo=temp->seatNo;

    /* Remove from linked list */
    if(prev==NULL)
        head=temp->next;
    else
        prev->next=temp->next;

    /* Push cancelled ticket into stack */
    if(topStack<19)
    {
        topStack++;
        cancelledStack[topStack]=*temp;
        cancelledStack[topStack].next=NULL;
    }

    /* Free seat */
    buses[r][b].seats[seatNo-1]=0;

    delete temp;

    cout<<"Ticket cancelled successfully!\n";
    cout<<"Seat "<<seatNo<<" is now available.\n";

    /* Queue */
    giveSeatToWaiting(r,b,seatNo);
}


/*--------------------------------------------------
                 SEARCH TICKET
--------------------------------------------------*/
// Linear search: find a passenger by ticket number.
   void searchTicket()
{
   int ticketNo;
   Passenger *temp;

    cout<<"\n========== LINEAR SEARCH ==========\n";
    cout<<"Enter Ticket Number: ";
    ticketNo=getNumber();

    temp=head;

    while(temp!=NULL)

    {
        if(temp->ticketNo==ticketNo)
        {
            printTicket(temp);
            return;
        }

        temp=temp->next;
    }

    cout<<"Ticket not found!\n";
}


/*--------------------------------------------------
             DISPLAY PASSENGERS
--------------------------------------------------*/
// Display all booked passengers in compact table form.
   void displayPassengers()
{
   Passenger *temp;

    if(head==NULL)
    {
        cout<<"No passengers booked.\n";
        return;
    }

    cout<<"\n============================================================\n";
    cout<<"              ALL BOOKED TICKETS\n";
    cout<<"============================================================\n";
    cout<<"Ticket No. Name                       Seat Date\n";
    cout<<"------------------------------------------------------------\n";

    temp=head;

    while(temp!=NULL)
    {
      cout<<temp->ticketNo<<"           ";
      cout<<temp->name<<"               ";
      cout<<temp->seatNo<<"        ";
      cout<<temp->date<<"\n";

        temp=temp->next;

    }

    cout<<"============================================================\n";
    cout<<"Total booked tickets are shown above.\n";
}


/*--------------------------------------------------
               DISPLAY WAITING LIST
--------------------------------------------------*/
// Display all waiting passengers in compact table form.
   void displayWaiting()
{
   int r,b,i,index,total=0;

    cout<<"\n============================================================\n";
    cout<<"                 WAITING LIST\n";
    cout<<"============================================================\n";
    cout<<"Waiting No. Name                        Bus                Date\n";
    cout<<"------------------------------------------------------------\n";

    for(r=0;r<8;r++)
    {
       for(b=0;b<busCount[r];b++)
       {
          for(i=0;i<countQ[r][b];i++)
          {
             index=frontQ[r][b]+i;
             total++;

                cout<<total<<"       ";
                cout<<waitingQueue[r][b][index]->name;
                cout<<"        ";
                cout<<waitingQueue[r][b][index]->busName;
                cout<<"     ";
                cout<<waitingQueue[r][b][index]->date;
                cout<<"\n";
            }
        }
    }

    cout<<"============================================================\n";

    if(total==0)

       cout<<"Waiting list is empty.\n";
    else
       cout<<"Total waiting passengers: "<<total<<"\n";
}

/*--------------------------------------------------
             DISPLAY CANCELLED STACK
--------------------------------------------------*/
// Display cancelled tickets from top of stack (LIFO).
   void displayCancelled()
{
   int i;

    cout<<"\n============================================================\n";
    cout<<"               CANCELLED TICKETS\n";
    cout<<"============================================================\n";
    cout<<"Ticket No. Name                       Seat Date\n";
    cout<<"------------------------------------------------------------\n";

    if(topStack==-1)
    {
        cout<<"No cancelled tickets.\n";
    }
    else
    {
        for(i=topStack;i>=0;i--)
        {
           cout<<cancelledStack[i].ticketNo<<"         ";
           cout<<cancelledStack[i].name<<"        ";
           cout<<cancelledStack[i].seatNo<<"     ";
           cout<<cancelledStack[i].date<<"\n";
        }
    }

    cout<<"============================================================\n";
}

/*--------------------------------------------------
            SWAP FOR BUBBLE SORT
--------------------------------------------------*/
void swapPassenger(Passenger *a,Passenger *b)
{
   Passenger temp;

    /*
         Only data is swapped.
         next pointers are NOT swapped.
    */
    temp=*a;

    a->next=NULL;
    b->next=NULL;

    *a=*b;
    *b=temp;

    /*
         Restore original links.
         This keeps the linked list connected.
    */
}


/*--------------------------------------------------
                 BUBBLE SORT
--------------------------------------------------*/
// Bubble sort: arrange booked passengers by seat number.
   void sortPassengers()
{
   Passenger *a,*b;
   Passenger temp;
   Passenger *nextNode;
   int swapped;

    if(head==NULL)
    {
        cout<<"No passengers to sort.\n";
        return;
    }

    do
    {
      swapped=0;
      a=head;

         while(a->next!=NULL)
         {
           b=a->next;

          if(a->seatNo>b->seatNo)
          {
              /* Save the link after the two nodes. */
              nextNode=b->next;

              /* Swap complete passenger data. */
              temp=*a;
              *a=*b;
              *b=temp;

              /* Restore linked-list connections. */
              a->next=b;
              b->next=nextNode;

              swapped=1;
          }

          a=a->next;
      }

    }while(swapped==1);

    cout<<"\nPassengers sorted by seat number.\n";

    cout<<"\n============================================================\n";
    cout<<"              SORTED PASSENGERS\n";
    cout<<"============================================================\n";
    cout<<"Ticket No. Name                       Seat Date\n";
    cout<<"------------------------------------------------------------\n";

    a=head;
    while(a!=NULL)
    {
      cout<<a->ticketNo<<"              ";
      cout<<a->name<<"             ";
      cout<<a->seatNo<<"          ";
      cout<<a->date<<"\n";
      a=a->next;
    }

    cout<<"============================================================\n";
}

/*--------------------------------------------------
                  MAIN MENU
--------------------------------------------------*/
// Main menu: calls the required operation based on user choice.
   void menu()
{
   int choice;

  do
  {
    cout<<"\n\n============================================\n";
    cout<<"       BUS TICKET BOOKING SYSTEM\n";
    cout<<"============================================\n";
    cout<<"1. Book Ticket\n";
    cout<<"2. Display Booked Passengers\n";
    cout<<"3. Search Passenger by Ticket No.\n";
    cout<<"4. Cancel Ticket\n";
    cout<<"5. Display Waiting List\n";
    cout<<"6. Display Cancelled Tickets\n";
    cout<<"7. Sort Passengers by Seat No.\n";
    cout<<"8. Exit\n";
    cout<<"============================================\n";

    cout<<"Enter your choice: ";
    choice=getNumber();

    switch(choice)
    {
      case 1:
         bookTicket();
         break;

       case 2:
         displayPassengers();
         break;

       case 3:
         searchTicket();
         break;

       case 4:
         cancelTicket();
         break;

          case 5:
            displayWaiting();
            break;

          case 6:
            displayCancelled();
            break;

          case 7:
            sortPassengers();
            break;

          case 8:
            cout<<"Thank you for using the system!\n";
            break;

          default:
            cout<<"Invalid choice!\n";
      }

    }while(choice!=8);
}


/*--------------------------------------------------
                   MAIN
--------------------------------------------------*/
void main()
{
   clrscr();

    createBuses();

    menu();

    getch();
}

