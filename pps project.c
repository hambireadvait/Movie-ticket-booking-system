#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 10
#define MAX_BOOKINGS 10
#define HALL_CAPACITY 50

struct Login
{
    char name[50];
    char contact[11];
    int id;
    char password[20];
};

struct Booking
{
    int bookingId;
    int hallNo;
    int showNo;
    int tickets;
    float amount;
};

struct Login users[MAX_USERS];
struct Booking bookings[MAX_USERS][MAX_BOOKINGS];

int bookingCount[MAX_USERS] = {0};

int seats[2][2] =
{
    {HALL_CAPACITY, HALL_CAPACITY},
    {HALL_CAPACITY, HALL_CAPACITY}
};

int bookingIdCounter = 1001;

/* Function to validate 10 digit phone number */
int isValidPhone(char phone[])
{
    int i;

    if(strlen(phone) != 10)
    {
        return 0;
    }

    for(i = 0; i < 10; i++)
    {
        if(!isdigit(phone[i]))
        {
            return 0;
        }
    }

    return 1;
}

/* Function to validate password length */
int isValidPassword(char password[])
{
    if(strlen(password) < 6)
    {
        return 0;
    }

    return 1;
}

int main()
{
    int totalUsers = 0;
    int choice;

    while(1)
    {
        printf("\n====================================");
        printf("\n      MOVIE BOOKING SYSTEM");
        printf("\n====================================\n");

        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        /* REGISTER */
        if(choice == 1)
        {
            if(totalUsers >= MAX_USERS)
            {
                printf("User Limit Reached!\n");
                continue;
            }

            printf("\n========== REGISTER ==========\n");

            printf("Enter Name: ");
            scanf("%s", users[totalUsers].name);

            /* PHONE VALIDATION */
            while(1)
            {
                printf("Enter 10 Digit Phone Number: ");
                scanf("%s", users[totalUsers].contact);

                if(isValidPhone(users[totalUsers].contact))
                {
                    break;
                }
                else
                {
                    printf("Invalid Phone Number!\n");
                }
            }

            printf("Enter ID: ");
            scanf("%d", &users[totalUsers].id);

            /* PASSWORD VALIDATION */
            while(1)
            {
                printf("Enter Password (Minimum 6 Characters): ");
                scanf("%s", users[totalUsers].password);

                if(isValidPassword(users[totalUsers].password))
                {
                    break;
                }
                else
                {
                    printf("Password Must Be 6 Or More Characters!\n");
                }
            }

            printf("Registration Successful!\n");

            totalUsers++;
        }

        /* LOGIN */
        else if(choice == 2)
        {
            int loginId;
            char loginPassword[20];
            int userIndex = -1;
            int i;

            printf("\n========== LOGIN ==========\n");

            printf("Enter ID: ");
            scanf("%d", &loginId);

            printf("Enter Password: ");
            scanf("%s", loginPassword);

            for(i = 0; i < totalUsers; i++)
            {
                if(users[i].id == loginId &&
                   strcmp(users[i].password,
                          loginPassword) == 0)
                {
                    userIndex = i;
                    break;
                }
            }

            if(userIndex == -1)
            {
                printf("Invalid ID Or Password!\n");
                continue;
            }

            printf("Login Successful!\n");

            do
            {
                printf("\n====================================");
                printf("\n            DASHBOARD");
                printf("\n====================================\n");

                printf("1. Book Ticket\n");
                printf("2. Cancel Ticket\n");
                printf("3. View Booking History\n");
                printf("4. Logout\n");

                printf("Enter Choice: ");
                scanf("%d", &choice);

                switch(choice)
                {
                    /* BOOK TICKET */
                    case 1:
                    {
                        int hallNo, showNo, tickets;
                        int hallIndex, showIndex;
                        int confirm;

                        printf("\n========== AVAILABLE SEATS ==========\n");

                        printf("Hall 1 Morning Show : %d Seats\n",
                               seats[0][0]);

                        printf("Hall 1 Evening Show : %d Seats\n",
                               seats[0][1]);

                        printf("Hall 2 Morning Show : %d Seats\n",
                               seats[1][0]);

                        printf("Hall 2 Evening Show : %d Seats\n",
                               seats[1][1]);

                        /* HALL VALIDATION */
                        while(1)
                        {
                            printf("\nEnter Hall Number (1 or 2): ");
                            scanf("%d", &hallNo);

                            if(hallNo == 1 || hallNo == 2)
                            {
                                break;
                            }
                            else
                            {
                                printf("Invalid Hall Number! Please Enter Again.\n");
                            }
                        }

                        printf("\n1. Morning Show\n");
                        printf("2. Evening Show\n");

                        /* SHOW VALIDATION */
                        while(1)
                        {
                            printf("Enter Show Number: ");
                            scanf("%d", &showNo);

                            if(showNo == 1 || showNo == 2)
                            {
                                break;
                            }
                            else
                            {
                                printf("Invalid Show Number! Please Enter Again.\n");
                            }
                        }

                        hallIndex = hallNo - 1;
                        showIndex = showNo - 1;

                        printf("Available Seats: %d\n",
                               seats[hallIndex][showIndex]);

                        printf("Enter Number Of Tickets: ");
                        scanf("%d", &tickets);

                        if(tickets <= 0)
                        {
                            printf("Invalid Ticket Count!\n");
                            break;
                        }

                        if(tickets >
                           seats[hallIndex][showIndex])
                        {
                            printf("Not Enough Seats Available!\n");
                            break;
                        }

                        float totalAmount =
                        tickets * 150;

                        printf("\n========== PAYMENT DETAILS ==========\n");

                        printf("Ticket Price : 150\n");
                        printf("Total Amount : %.2f\n",
                               totalAmount);

                        printf("\n1. Proceed Payment\n");
                        printf("2. Cancel Booking\n");

                        printf("Enter Choice: ");
                        scanf("%d", &confirm);

                        if(confirm == 1)
                        {
                            int b =
                            bookingCount[userIndex];

                            if(b >= MAX_BOOKINGS)
                            {
                                printf("Booking Limit Reached!\n");
                                break;
                            }

                            bookings[userIndex][b]
                            .bookingId = bookingIdCounter++;

                            bookings[userIndex][b]
                            .hallNo = hallNo;

                            bookings[userIndex][b]
                            .showNo = showNo;

                            bookings[userIndex][b]
                            .tickets = tickets;

                            bookings[userIndex][b]
                            .amount = totalAmount;

                            seats[hallIndex][showIndex]
                            -= tickets;

                            bookingCount[userIndex]++;

                            printf("\n===== BOOKING CONFIRMED =====\n");

                            printf("Booking ID : %d\n",
                                   bookings[userIndex][b]
                                   .bookingId);

                            printf("Hall Number : %d\n",
                                   hallNo);

                            printf("Show Number : %d\n",
                                   showNo);

                            printf("Tickets : %d\n",
                                   tickets);

                            printf("Amount Paid : %.2f\n",
                                   totalAmount);
                        }
                        else
                        {
                            printf("Booking Cancelled!\n");
                        }

                        break;
                    }

                    /* CANCEL TICKET */
                    case 2:
                    {
                        int i;
                        int bookingId;
                        int found = 0;
                        int cancelTickets;

                        if(bookingCount[userIndex] == 0)
                        {
                            printf("No Booking Found!\n");
                            break;
                        }

                        printf("\n========== YOUR BOOKINGS ==========\n");

                        for(i = 0;
                            i < bookingCount[userIndex];
                            i++)
                        {
                            printf("\nBooking %d\n", i + 1);

                            printf("Booking ID : %d\n",
                                   bookings[userIndex][i]
                                   .bookingId);

                            printf("Hall No : %d\n",
                                   bookings[userIndex][i]
                                   .hallNo);

                            printf("Show No : %d\n",
                                   bookings[userIndex][i]
                                   .showNo);

                            printf("Tickets : %d\n",
                                   bookings[userIndex][i]
                                   .tickets);

                            printf("Amount : %.2f\n",
                                   bookings[userIndex][i]
                                   .amount);
                        }

                        printf("\nEnter Booking ID To Cancel: ");
                        scanf("%d", &bookingId);

                        for(i = 0;
                            i < bookingCount[userIndex];
                            i++)
                        {
                            if(bookings[userIndex][i]
                               .bookingId == bookingId)
                            {
                                found = 1;

                                printf("Enter Number Of Tickets To Cancel: ");
                                scanf("%d", &cancelTickets);

                                if(cancelTickets <= 0)
                                {
                                    printf("Invalid Ticket Number!\n");
                                    break;
                                }

                                if(cancelTickets >
                                   bookings[userIndex][i].tickets)
                                {
                                    printf("You Cannot Cancel More Than Booked Tickets!\n");
                                    break;
                                }

                                int hallIndex =
                                bookings[userIndex][i]
                                .hallNo - 1;

                                int showIndex =
                                bookings[userIndex][i]
                                .showNo - 1;

                                float refund =
                                cancelTickets * 150;

                                seats[hallIndex][showIndex]
                                += cancelTickets;

                                bookings[userIndex][i]
                                .tickets -= cancelTickets;

                                bookings[userIndex][i]
                                .amount -= refund;

                                printf("\n===== TICKET CANCELLATION DETAILS =====\n");

                                printf("Cancelled Tickets : %d\n",
                                       cancelTickets);

                                printf("Refund Amount : %.2f\n",
                                       refund);

                                printf("Remaining Tickets : %d\n",
                                       bookings[userIndex][i]
                                       .tickets);

                                /* Remove booking if all tickets cancelled */
                                if(bookings[userIndex][i]
                                   .tickets == 0)
                                {
                                    int j;

                                    for(j = i;
                                        j < bookingCount[userIndex] - 1;
                                        j++)
                                    {
                                        bookings[userIndex][j] =
                                        bookings[userIndex][j + 1];
                                    }

                                    bookingCount[userIndex]--;

                                    printf("Complete Booking Cancelled!\n");
                                }

                                printf("Ticket Cancellation Successful!\n");

                                break;
                            }
                        }

                        if(found == 0)
                        {
                            printf("Invalid Booking ID!\n");
                        }

                        break;
                    }

                    /* BOOKING HISTORY */
                    case 3:
                    {
                        int i;

                        if(bookingCount[userIndex] == 0)
                        {
                            printf("No Booking History Found!\n");
                        }
                        else
                        {
                            printf("\n========== BOOKING HISTORY ==========\n");

                            for(i = 0;
                                i < bookingCount[userIndex];
                                i++)
                            {
                                printf("\nBooking %d\n",
                                       i + 1);

                                printf("Booking ID : %d\n",
                                       bookings[userIndex][i]
                                       .bookingId);

                                printf("Hall No : %d\n",
                                       bookings[userIndex][i]
                                       .hallNo);

                                printf("Show No : %d\n",
                                       bookings[userIndex][i]
                                       .showNo);

                                printf("Tickets : %d\n",
                                       bookings[userIndex][i]
                                       .tickets);

                                printf("Amount Paid : %.2f\n",
                                       bookings[userIndex][i]
                                       .amount);
                            }
                        }

                        break;
                    }

                    /* LOGOUT */
                    case 4:
                    {
                        printf("Logged Out Successfully!\n");
                        break;
                    }

                    default:
                    {
                        printf("Invalid Choice!\n");
                    }
                }

            } while(choice != 4);
        }

        /* EXIT */
        else if(choice == 3)
        {
            printf("Thank You For Using Movie Booking System!\n");
            break;
        }

        else
        {
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}