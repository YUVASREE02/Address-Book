/* NAME: D.Yuvasree
DATE:5/12/25
DESCRIPTION: This Address Book project allows users to efficiently store and manage contact information using multiple operations such as create, list, edit, search, delete, and save.
Each function includes detailed input validations to ensure the accuracy and consistency of the stored data.
*/
#include <stdio.h>
#include "contact.h"
#include <string.h>
#include <ctype.h>

/* Function definitions */
// void init_intitalization(AddressBook *addressbook)
// {
// }

       
int create_contact(AddressBook *addressbook)
{
    int choice;

    /*---------------- NAME VALIDATION ----------------*/
    printf("Enter the Name: ");
    while(1)
    {
        int flag = 0;
        scanf(" %[^\n]", addressbook->contact_details[addressbook->contact_count].Name);

        // Check each character of name
        int i = 0;
        while(addressbook->contact_details[addressbook->contact_count].Name[i] != '\0')
        {
            char ch = addressbook->contact_details[addressbook->contact_count].Name[i];

            // Only alphabets and spaces allowed
            if(!((isalpha(ch)) || (ch == ' ')))
            {
                flag = 1;
                break;
            }
            i++;
        }

        // If valid name
        if(flag == 0)
        {
            printf("Name accepted successfully!\n");
            break;
        }
        else
        {
            printf("Name should contain only alphabets and space! Try again\n");
        }
    }

    /*---------------- MOBILE NUMBER VALIDATION ----------------*/
    printf("Enter the phone no: ");
    scanf(" %[^\n]", addressbook->contact_details[addressbook->contact_count].Mobile_number);

    while (1)
    {
        int flag = 0;
        int len = 0;
        int duplicate = 0;

        char *mob = addressbook->contact_details[addressbook->contact_count].Mobile_number;

        // Check each character is digit
        for (int i = 0; mob[i] != '\0'; i++)
        {
            if (!isdigit(mob[i]))
            {
                printf("Mobile number must contain only digits! Try again:\n");
                flag = 1;
                break;
            }
            len++;
        }
        if (flag)
        {
            scanf(" %[^\n]", mob);
            continue;
        }

        // Must start with 6-9
        if (mob[0] < '6' || mob[0] > '9')
        {
            printf("Mobile number must start with 6! Try again:\n");
            scanf(" %[^\n]", mob);
            continue;
        }

        // Must be exactly 10 digits
        if (len != 10)
        {
            printf("Mobile number must be exactly 10 digits! Try again:\n");
            scanf(" %[^\n]", mob);
            continue;
        }

        // Check duplicate mobile number
        for (int i = 0; i < addressbook->contact_count; i++)
        {
            if (strcmp(addressbook->contact_details[i].Mobile_number, mob) == 0)
            {
                duplicate = 1;
                break;
            }
        }
        if (duplicate)
        {
            printf("This mobile number already exists! Enter a different number:\n");
            scanf(" %[^\n]", mob);
            continue;
        }

        printf("Mobile number accepted successfully!\n");
        break;
    }

    /*---------------- MAIL ID VALIDATION ----------------*/
    printf("Enter the mail id: ");
    scanf(" %[^\n]", addressbook->contact_details[addressbook->contact_count].Mail_ID);

    while(1)
    {
        int at_count = 0, alpha = 0, dot = 0;
        int duplicate = 0;
        int at_pos = -1, dot_pos = -1;

        char *mail = addressbook->contact_details[addressbook->contact_count].Mail_ID;

        int lowercase_error = 0;
        int space_error = 0;

        // Check lowercase + no spaces
        for(int i = 0; mail[i] != '\0'; i++)
        {
            if (isupper(mail[i]))
            {
                lowercase_error = 1;
                break;
            }
            if(mail[i] == ' ')
            {
                space_error = 1;
                break;
            }
        }

        if (lowercase_error)
        {
            printf("Error! Email must contain only lowercase letters. Try again:\n");
            scanf(" %[^\n]", mail);
            continue;
        }

        if (space_error)
        {
            printf("Error! Email should not contain any spaces. Try again:\n");
            scanf(" %[^\n]", mail);
            continue;
        }

        // Count '@', '.', alphabets and digits
        for(int i=0; mail[i] != '\0'; i++)
        {
            char ch = mail[i];

            if(ch == '@')
            {
                at_count++;
                at_pos = i;
            }
            else if (ch == '.')
            {
                dot++;
                dot_pos = i;
            }
            else if(isalpha(ch) || isdigit(ch))
            {
                alpha = 1;
            }
        }

        // Check duplicate email ID
        for (int i = 0; i < addressbook->contact_count; i++)
        {
            if (strcmp(addressbook->contact_details[i].Mail_ID, mail) == 0)
            {
                duplicate = 1;
                break;
            }
        }

        if(duplicate)
        {
            printf("This Mail Id already exists! Enter unique ID.\n");
            scanf(" %[^\n]", mail);
            continue;
        }

        // Email should not start with digit
        if(isdigit(mail[0]))
        {
            printf("Mail should not start with a number.\n");
            scanf(" %[^\n]", mail);
            continue;
        }

        // Must end with .com or .in
        if(!(strcmp(mail + dot_pos, ".com") == 0 || strcmp(mail + dot_pos, ".in") == 0))
        {
            printf("Only .com or .in allowed.\n");
            scanf(" %[^\n]", mail);
            continue;
        }

        // Must contain exactly one @
        if(at_count != 1)
        {
            printf("Email must contain exactly one '@'.\n");
            scanf(" %[^\n]", mail);
            continue;
        }

        // Must contain one dot
        if(dot != 1)
        {
            printf("Email must contain exactly one dot.\n");
            scanf(" %[^\n]", mail);
            continue;
        }

        // Dot should come after '@'
        if(at_pos > dot_pos)
        {
            printf("'.' must come after '@'.\n");
            scanf(" %[^\n]", mail);
            continue;
        }

        // At least one character between @ and .
        if(dot_pos - at_pos <= 1)
        {
            printf("Domain missing between '@' and '.'.\n");
            scanf(" %[^\n]", mail);
            continue;
        }

        // @ cannot be first
        if(at_pos == 0)
        {
            printf("'@' cannot be first.\n");
            scanf(" %[^\n]", mail);
            continue;
        }

        // Email should not end with dot
        if(dot_pos == strlen(mail)-1)
        {
            printf("Email must not end with '.'.\n");
            scanf(" %[^\n]", mail);
            continue;
        }

        break;
    }

    // Increment count and return
    printf("Mail ID created successfully!\n");
    addressbook->contact_count++;
    printf("contact created successfully!\n");

    // Ask user whether to add more contacts
    printf("Do you want to add another contact? (y-1/n-0): ");
    scanf("%d", &choice);
    if(choice == 1)
    {
        create_contact(addressbook);
    }
    else
    {
        printf("Returning to main menu...\n");
    }
}
void list_contacts(AddressBook *addressbook)
{
    /*------------------Displaying Contacts-----------------------*/
    if(addressbook->contact_count == 0)
    {
        printf("No contact to show\n");
    }
    for(int i=0;i<addressbook->contact_count;i++)
    {
        printf("-----------------------------------------\n");
        printf("Name: %s\n",addressbook->contact_details[i].Name);
        printf("Mobile no: %s\n",addressbook->contact_details[i].Mobile_number);
        printf("Mail ID: %s\n",addressbook->contact_details[i].Mail_ID);
        printf("-------------------------------------------\n");
    }
}

int search_contacts(AddressBook *addressbook)
{
    int cont = 1; // Flag to continue searching

    while(cont == 1)
    {
        int opt;
        //printf("=----choose  the menu----\n");
        //printf("1.search by name\n2.search by mobile number\n3.search by mail id\n4.exit\n");
        scanf("%d", &opt);

        switch(opt)
        {
            /*-----------------SEARCH BY NAME----------------*/
        case 1:

            char name[32];
            printf("Enter the name: ");
            scanf(" %[^\n]", name);

            int indices[100];     // To store all matched indices
            int found_count = 0;  // Count of matches

            // Find all contacts with matching name
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Name, name) == 0)
                {
                    indices[found_count] = i; // store index
                    found_count++;
                }
            }

            // No match found
            if (found_count == 0)
            {
                printf("Details not found\n");
                break;
            }

            // Print all matched contacts
            printf("------Matching Contacts------\n");
            for (int i = 0; i < found_count; i++)
            {
                int idx = indices[i];
                printf("%d. %s %s %s\n",
                       i + 1,
                       addressbook->contact_details[idx].Name,
                       addressbook->contact_details[idx].Mobile_number,
                       addressbook->contact_details[idx].Mail_ID);
            }

            // If multiple matches → ask user to choose one
            if (found_count > 1)
            {
                int choice;
                printf("Multiple contacts found. Select the index number: ");
                scanf("%d", &choice);

                if (choice >= 1 && choice <= found_count)
                {
                    int selected = indices[choice - 1]; // chosen contact index
                    printf("You selected:\n%s %s %s\n",
                           addressbook->contact_details[selected].Name,
                           addressbook->contact_details[selected].Mobile_number,
                           addressbook->contact_details[selected].Mail_ID);
                }
                else
                {
                    printf("Invalid selection.\n");
                }
            }

            break;

            /*--------------SEARCH BY MOBILE NUMBER---------------*/
        case 2:

            char mobile_number[11];
            int flag = 0;

            printf("Enter the mobile number:");
            scanf(" %[^\n]", mobile_number);

            // Search by mobile number
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Mobile_number, mobile_number) == 0)
                {
                    // Match found → print details
                    printf("-------Details found------\n");
                    printf("%s %s %s\n",
                           addressbook->contact_details[i].Name,
                           addressbook->contact_details[i].Mobile_number,
                           addressbook->contact_details[i].Mail_ID);
                    flag = 1;
                    break;
                }
            }

            if (flag == 0) // No match
            {
                printf("Details not found\n");
            }

            break;

            /*------------------SEARCH BY MAIL ID-----------------*/
        case 3:

            char mail_id[35];
            int found = 0;

            printf("Enter the mail id:");
            scanf(" %[^\n]", mail_id);

            // Search by mail ID
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Mail_ID, mail_id) == 0)
                {
                    // Match found → print details
                    printf("-------Details found------\n");
                    printf("%s %s %s\n",
                           addressbook->contact_details[i].Name,
                           addressbook->contact_details[i].Mobile_number,
                           addressbook->contact_details[i].Mail_ID);

                    found = 1;
                    break;
                }
            }

            if (found == 0) // No match
            {
                printf("Details not found\n");
            }

            break;

        case 4:
            printf("GO back to main menu\n");
            return 0; // Exit search function

        default:
            printf("Choose the correct option from the Menu\n");
            break;
        }

        // Ask user whether to continue searching
        printf("Do you want to continue searching? (1->Yes / 0->No): ");
        scanf("%d", &cont);
    }

    return 0; // End of search function
}

int edit_contact(AddressBook *addressbook)
{
    if (addressbook->contact_count == 0)  // check if list is empty
    {
        printf("No contacts found!\n");
        return 1;
    }

    int cont = 1; // repeat edit option

    while (cont == 1) // loop for editing again
    {
        char key[50];
        int matched[100], mcount = 0, opt;
        printf("\nEnter the name/mobile/email to edit: ");
        scanf(" %[^\n]", key);

        // ------------------- FIND MATCHING CONTACTS -------------------
        for (int i = 0; i < addressbook->contact_count; i++)
        {
            if (strcmp(key, addressbook->contact_details[i].Name) == 0 ||
                strcmp(key, addressbook->contact_details[i].Mobile_number) == 0 ||
                strcmp(key, addressbook->contact_details[i].Mail_ID) == 0)
            {
                matched[mcount] = i;   // store index of matched contact
                mcount++;
            }
        }

        if (mcount == 0)   // no match found
        {
            printf("No contact found!\n");
            return 1;
        }

        int index;

        // ------------ ONLY ONE MATCH FOUND -------------
        if (mcount == 1)
        {
            index = matched[0]; // choose the only match
            printf("Match found. Proceeding to edit...\n");
        }
        // ------------ MULTIPLE MATCHES FOUND -------------
        else
        {
            printf("\nMultiple contacts found:\n");
            for (int i = 0; i < mcount; i++)
            {
                int idx = matched[i];
                printf("%d) %s - %s - %s\n",
                       i,
                       addressbook->contact_details[idx].Name,
                       addressbook->contact_details[idx].Mobile_number,
                       addressbook->contact_details[idx].Mail_ID);
            }

            printf("Choose contact (0-%d): ", mcount - 1); // user chooses index
            scanf("%d", &index);

            if (index < 0 || index >= mcount) // invalid selection
            {
                printf("Invalid selection!\n");
                return 1;
            }

            index = matched[index]; // pick selected contact
        }

        // ----------------- EDIT OPTIONS -----------------
        printf("\nWhat do you want to edit:\n");
        printf("1. Name\n");
        printf("2. Mobile\n");
        printf("3. Mail ID\n");
        printf("4. Back\n");
        printf("Enter the option:\n");
        scanf("%d", &opt);

        switch (opt)
        {
        /*------------------- EDIT NAME ------------------------*/
        case 1:
        {
            while (1)
            {
                int valid = 1;
                printf("Enter new name: ");
                scanf(" %[^\n]", addressbook->contact_details[index].Name);

                char *nm = addressbook->contact_details[index].Name;

                // name validation
                for (int i = 0; nm[i] != '\0'; i++)
                {
                    if (!(isalpha(nm[i]) || nm[i] == ' ')) // only letters + space
                    {
                        valid = 0;
                        break;
                    }
                }

                if (valid) // accept valid name
                {
                    printf("Name updated successfully!\n");
                    break;
                }
                else
                {
                    printf("Invalid! Name can contain only alphabets and spaces.\n");
                }
            }
            break;
        }

        /*-------------------- EDIT MOBILE NUMBER ----------------------*/
        case 2:
        {
            while (1)
            {
                int valid = 1;
                printf("Enter new mobile number: ");
                scanf(" %[^\n]", addressbook->contact_details[index].Mobile_number);

                char *mob = addressbook->contact_details[index].Mobile_number;
                int len = strlen(mob);

                if (len != 10) valid = 0; // must be 10 digits

                for (int i = 0; mob[i] != '\0'; i++)
                {
                    if (!isdigit(mob[i])) // only digits allowed
                    {
                        valid = 0;
                        break;
                    }
                }

                // duplicate mobile check
                for (int i = 0; i < addressbook->contact_count; i++)
                {
                    if (i != index && strcmp(addressbook->contact_details[i].Mobile_number, mob) == 0)
                    {
                        printf("Mobile number already exists! Try again.\n");
                        valid = 0;
                    }
                }

                if (valid)
                {
                    printf("Mobile number updated successfully!\n");
                    break;
                }
                else
                {
                    printf("Invalid! Mobile must be 10 digits and unique.\n");
                }
            }
        }
        break;

        /*-------------- EDIT MAIL ID ------------------*/
        case 3:
        {
            char mail[100];
            int duplicate;

            while (1)
            {
                int at_count = 0, dot_count = 0;
                int at_pos = -1, dot_pos = -1;
                int invalid = 0;

                printf("Enter new mail id: ");
                scanf(" %[^\n]", mail);

                // check each character
                for (int i = 0; mail[i] != '\0'; i++)
                {
                    char ch = mail[i];

                    if (ch == '@') { at_count++; at_pos = i; }
                    else if (ch == '.') { dot_count++; dot_pos = i; }
                    else if (ch == ' ') { invalid = 1; break; }
                    else if (isupper(ch)) { invalid = 1; break; }
                }

                if (invalid)
                {
                    printf("Invalid characters found in mail\n");
                    continue;
                }

                if (isdigit(mail[0]))
                {
                     printf("mail cannot start with number\n");
                     continue;
                }
                if (at_count != 1)
                {
                     printf("exactly one @ required\n");
                      continue; 
                }
                if (dot_count != 1)
                {
                     printf("exactly one dot required\n");
                    continue;
                }
                if (at_pos > dot_pos)
                {
                     printf("dot must come after @\n");
                    continue; 
                }
                if (dot_pos - at_pos <= 1)
                { 
                    printf("missing domain between @ and dot\n");
                     continue;
                }
                if (dot_pos == strlen(mail)-1)
                {
                     printf("mail cannot end with dot\n");
                      continue; 
                }
                if (!(strcmp(mail + dot_pos, ".com") == 0 || strcmp(mail + dot_pos, ".in") == 0))
                {
                    printf("only .com or .in allowed\n");
                    continue;
                }

                // check duplicate mail
                duplicate = 0;
                for (int i = 0; i < addressbook->contact_count; i++)
                {
                    if (i != index && strcmp(addressbook->contact_details[i].Mail_ID, mail) == 0)
                    {
                        duplicate = 1;
                        break;
                    }
                }

                if (duplicate)
                {
                    printf("mail already exists\n");
                    continue;
                }

                strcpy(addressbook->contact_details[index].Mail_ID, mail); // update mail
                printf("mail updated successfully\n");
                break;
            }
            break;
        }

        case 4: // go back
            printf("Returning to menu.\n");
            break;

        default: // invalid menu option
            printf("Invalid option!\n");
        }

        printf("Do you want to edit again(1/0): "); // repeat edit
        scanf("%d", &cont);
    }

    return 0;
}
int delete_contact(AddressBook *addressbook)
{
    if (addressbook->contact_count == 0) // no contacts available
    {
        printf("No contacts to delete!\n");
        return 0;
    }

    int opt, choose = 1;

    while (choose == 1) // repeat deletion
    {
        //printf("\nChoose option to delete:\n");
        //printf("1. Name\n2. Mobile Number\n3. Mail ID\n");
        //printf("Enter option: ");
        scanf("%d", &opt);

        switch (opt)
        {

        /* ------------------ DELETE BY NAME ------------------ */
        case 1:
        {
            char key[100];
            printf("Enter the Name to Delete: ");
            scanf(" %[^\n]", key);

            int match_index[100];
            int match_count = 0;

            // search for matching names
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Name, key) == 0)
                {
                    match_index[match_count++] = i; // store matched indices
                }
            }

            if (match_count == 0) // no matching name
            {
                printf("No matching contacts found.\n");
                break;
            }

            // display all matches
            printf("\nMatching contacts:\n");
            for (int m = 0; m < match_count; m++)
            {
                int idx = match_index[m];
                printf("%d. %s - %s - %s\n",
                    m + 1,
                    addressbook->contact_details[idx].Name,
                    addressbook->contact_details[idx].Mobile_number,
                    addressbook->contact_details[idx].Mail_ID);
            }

            // ask user to choose which to delete
            int serial;
            printf("\nEnter the serial number to delete: ");
            scanf("%d", &serial);

            if (serial < 1 || serial > match_count) // invalid option
            {
                printf("Invalid serial number!\n");
                break;
            }

            int real_index = match_index[serial - 1]; // actual index in array

            // confirm deletion
            char confirm;
            printf("Are you sure you want to delete this? (Y/N): ");
            scanf(" %c", &confirm);

            if (confirm != 'Y' && confirm != 'y') // if user cancels
            {
                printf("Delete cancelled.\n");
                break;
            }

            // delete by shifting elements
            for (int i = real_index; i < addressbook->contact_count - 1; i++)
            {
                addressbook->contact_details[i] = addressbook->contact_details[i + 1];
            }

            addressbook->contact_count--; // decrease count
            printf("Contact deleted successfully!\n");

            save_contacts(addressbook); // update file
            printf("File updated successfully.\n");

            break;
        }

        /* ------------------ DELETE BY MOBILE NUMBER ------------------ */
        case 2:
        {
            char mob[11];
            printf("Enter the mobile number: ");
            scanf(" %[^\n]", mob);

            int found = 0;

            // search by mobile number
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Mobile_number, mob) == 0)
                {
                    char confirm;

                    // ask user before deleting
                    printf("Are you sure you want to delete this contact? (Y/N): ");
                    scanf(" %c", &confirm);

                    if (confirm == 'Y' || confirm == 'y') // proceed
                    {
                        for (int j = i; j < addressbook->contact_count - 1; j++)
                        {
                            addressbook->contact_details[j] = addressbook->contact_details[j + 1];
                        }

                        addressbook->contact_count--; // reduce count
                        printf("Contact deleted successfully!\n");
                    }
                    else
                    {
                        printf("Deletion cancelled.\n");
                    }

                    found = 1;
                    break;
                }
            }

            if (!found) // no match found
            {
                printf("Contact not found\n");
            }

            break;
        }

        /* ------------------ DELETE BY EMAIL ID ------------------ */
        case 3:
        {
            char mail[35];
            printf("Enter the mail id to delete: ");
            scanf(" %[^\n]", mail);

            int found = 0;

            // search by mail ID
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Mail_ID, mail) == 0)
                {
                    char confirm;

                    // confirm deletion
                    printf("Are you sure you want to delete this contact? (Y/N): ");
                    scanf(" %c", &confirm);

                    if (confirm == 'Y' || confirm == 'y') // yes -> delete
                    {
                        for (int j = i; j < addressbook->contact_count - 1; j++)
                        {
                            addressbook->contact_details[j] = addressbook->contact_details[j + 1];
                        }

                        addressbook->contact_count--;
                        printf("Contact deleted successfully!\n");
                    }
                    else
                    {
                        printf("Deletion cancelled.\n");
                    }

                    found = 1;
                    break;
                }
            }

            if (!found) // nothing matched
            {
                printf("Contact not found\n");
            }

            break;
        }

        default:
            printf("Invalid option!\n"); // wrong menu input
            break;
        }

        // repeat delete process?
        printf("\nDo you want to continue deleting? (1-Yes / 0-No): ");
        scanf("%d", &choose);
    }

    return 0;
}


int save_contacts(AddressBook *addressbook)
{// ----------save contacts in file---------------------------
    FILE*  fptr =fopen("data.txt","w");//intialize file pointer
    if(fptr==NULL)//check the file
    {
        printf("file not found\n");
        return 0;
    }
    fprintf(fptr,"#%d\n",addressbook->contact_count);//print contact count in file
    for(int i=0;i<addressbook->contact_count;i++)
    {
        //print contact count in file
    fprintf(fptr,"%s,%s,%s\n", addressbook->contact_details[i].Name,
         addressbook->contact_details[i].Mobile_number,
         addressbook->contact_details[i].Mail_ID);
    }
   fclose(fptr);//close file
    return 1;
}
int load_contacts(AddressBook *addressbook)
  {//------------ Load contacts from file--------------------
    FILE *fptr = fopen("data.txt", "r");//read the data from file
    if (fptr == NULL)
    {
    printf("No saved data found!\n");
    return 0; // failure
    }


    // Read contact count
    fscanf(fptr, "#%d\n", &addressbook->contact_count);
    return 0;
}