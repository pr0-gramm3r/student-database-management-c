#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int selection();                //  Just Selects option EndUser Accordingly
void create(char[]);            //  char: file_name 
void write(char[],int);         //  Char: file_name & int: amount 
void view(char[]);              //  Char: file_name
void edit(char[],int);          //  Char: file_name & int: roll no.
void datadelete(char[],int);    //  Char: file_name & int: roll no.
void Tabledelete(char[]);       //  Char: file_name
void Tableview();               //  Just View the table created Using a Master file
void removeFromMaster(char[]);  //  char: file_name //  Deletes deleted table from master
void waitForEnter();            //  Used in return


// Database carry actual data Of Students
struct DATABASE
{
    int Roll_no ;
    char Name[20] ;

    // Marks carry all sub_marks and total
    struct MARKS
    {
        float C,Fit,Eng,Prac;
    }M;
    
};

int main()
{
    int status;
    printf("You Entered Into A DataBase\n");
    printf("\nYou have Got Admin Powers Of Database Management\n");
    // Fuction Calling
    while (1)
    {  
         status = selection();

        if (status == 0)
        {
            printf("Exiting program...\n");
            break;
        }
    }
    
    return 0;
}

int selection()
{
    int Amount, Roll, option;
    char TableName[20], exitDatabase;

    printf("Do You wish to:\n");
    printf("1.  Create new Table\n");
    printf("2.  View Data of Specific Table\n");
    printf("3.  Write Data into the Specific Table\n");
    printf("4.  Edit Data of Specific Table\n");
    printf("5.  Delete Data of Specific Table\n");
    printf("6.  Delete Specific Table\n");
    printf("7.  View All Table\n");
    printf("8.  Exit Database \n");

    printf("\n\nChoose The Given Optional Number And press Enter to select \nHere : ");
    scanf("%d",&option);

    switch (option)
    {
    case 1:
        {      
            printf("Enter Name For Table (Without .txt/.dat and space) : ");
            scanf("%19s",TableName);    
                                        
            strcat(TableName,".dat");   //Added this So no issue in File making

            create(TableName);
            break;
        }
    case 2:
        {
            printf("Enter Name For Table (Without .txt/.dat) : ");
            scanf("%19s",TableName);

            strcat(TableName,".dat");   //Added this So no issue in File making
            
            view(TableName);
            break;
        }
    case 3:
        {
            printf("Enter Name For Table (Without .txt/.dat) : ");
            scanf("%19s",TableName);

            strcat(TableName,".dat");   //Added this So no issue in File making
            
            printf("Enter The Numbers of Student You wan't to add : ");
            scanf("%d",&Amount);
            
            write(TableName,Amount);
            break;
        }
    case 4:
        {
            printf("Enter Name For Table (Without .txt/.dat) : ");
            scanf("%19s",TableName);

            strcat(TableName,".dat");   //Added this So no issue in File making
            
            printf("Enter The Roll No. Student : ");
            scanf("%d",&Roll);
            
            edit(TableName,Roll);
            break;
        }
    case 5:
        {
            printf("Enter Name For Table (Without .txt/.dat) : ");
            scanf("%19s",TableName);

            strcat(TableName,".dat");   //Added this So no issue in File making
            
            printf("Enter The Roll No. Student : ");
            scanf("%d",&Roll);
            
            datadelete(TableName,Roll);
            break;
        }
    case 6:
        {
           
            printf("Enter Name For Table (Without .txt/.dat) : ");
            scanf("%19s",TableName);

            strcat(TableName,".dat");   //Added this So no issue in File making
            
            Tabledelete(TableName);
            break;
        }        
    case 7:
    {
        Tableview();
        break;
    }

    case 8:
    {
        printf("Are you sure to Exit!!, press Y to Exit : ");
        scanf(" %c",&exitDatabase);

        if (exitDatabase == 'y' || exitDatabase == 'Y')
        {
            return 0;
        }
        return 1;
        break;
        
    }
    
    default:
        printf("Invalid Option");
        return 1;
        break;
    }
    return 1;

}

void create(char TableName[])
{
    FILE *fp,*master;

    fp = fopen(TableName, "wb");
    if (fp == NULL)
    {
        printf("Error creating file\n");
        return;
    }

    fclose(fp);

    // Open master file
    master = fopen("tables.dat", "a");
    
    if (master == NULL)
    {
        printf("\nSomething Went Wrong !!, Try creating Again \n");
        remove(TableName);
        return;
    }
    
    fprintf(master, "%s\n", TableName);
    fclose(master);

    printf("\nTable Created Successfully\n");

    printf("\nPress Enter to Return...");
    waitForEnter();
    return;
    
}

void write(char TableName[],int Amount)
{
    FILE *fp;
    int i,opt,option,Roll;
    struct DATABASE *D;
    D = (struct DATABASE*)malloc(sizeof(struct DATABASE)*Amount);        

    if (D == NULL)
    {
        printf("\nMemory Allocation Failed");
        return;
    }
    
    for (i = 0; i < Amount; i++)
    {            
        printf("Enter Roll No. : ");
        scanf("%d",&D[i].Roll_no);
        
        printf("Enter Name : ");
        scanf(" %19[^\n]",D[i].Name);
        
        printf("Enter Marks of C : ");
        scanf("%f",&D[i].M.C);
        
        printf("Enter Marks of Fit : ");
        scanf("%f",&D[i].M.Fit);
        
        printf("Enter Marks of Eng : ");
        scanf("%f",&D[i].M.Eng);
        
        printf("Enter Marks of Practical : ");
        scanf("%f",&D[i].M.Prac);

    }
    
    fp = fopen(TableName,"ab");

    if (fp == NULL)
    {
        printf("\nFile Not Found!!\n");
        printf("\nPress Enter To Return\n");
        waitForEnter();
        return;
    }
    

    fwrite(D,sizeof(struct DATABASE),Amount,fp);
    free(D);
    printf("\nData Written Successfully\n");
    fclose(fp);

    printf("\nPress Enter to Return...");
    waitForEnter();
    return;
 
     
}

void view(char TableName[])
{

    FILE *fp;
    struct DATABASE D;

    fp = fopen(TableName, "rb");   

    if (fp == NULL)
    {
        printf("File not found!\n");
        printf("Try Again !!");
        return;
    }

    printf("\n---- Student Data ----\n");

    // Read one struct at a time
    while (fread(&D, sizeof(struct DATABASE), 1, fp) == 1)
    {
        printf("\n\nRoll No : %d", D.Roll_no);
        printf("\nName    : %s", D.Name);
        printf("\nNow Marks Part\n");
        printf("\nC       : %.2f", D.M.C);
        printf("\nFit     : %.2f", D.M.Fit);
        printf("\nEng     : %.2f", D.M.Eng);
        printf("\nPrac    : %.2f\n\n", D.M.Prac);
    }

    fclose(fp);   
    printf("\nPress Enter to Return...");
    waitForEnter();
    return;
}

void edit(char TableName[], int Roll)
{
    FILE *fp;
    struct DATABASE D;
    int found = 0, option, chances = 0;

    fp = fopen(TableName, "rb+");

    if (fp == NULL)
    {
        printf("\nFile Not Found\n");
        return;
    }

    while (fread(&D, sizeof(struct DATABASE), 1, fp) == 1)
    {
        if (D.Roll_no == Roll)
        {
            found = 1;
            printf("\nData Found\n");

            // 🔁 Retry loop instead of recursion
            while (chances < 3)
            {
                printf("\nYou Wish to change : \n");
                printf("1. Name\n2. Marks of C\n3. Marks of Fit\n");
                printf("4. Marks of Eng\n5. Marks of Practical\n6. All\n");
                printf("Enter choice: ");
                scanf("%d", &option);

                if (option >= 1 && option <= 6)
                {
                    break; // valid input
                }
                else
                {
                    printf("Invalid input, try again\n");
                    chances++;
                }
            }

            if (chances == 3)
            {
                printf("Too many invalid attempts\n");
                fclose(fp);
                return;
            }

            switch (option)
            {
                case 1:
                {
                    printf("Enter Name: ");
                    scanf(" %19[^\n]", D.Name);
                    break;
                }    

                case 2:
                {
                    printf("Enter Marks of C: ");
                    scanf("%f", &D.M.C);
                    break;
                }

                case 3:
                {
                    printf("Enter Marks of Fit: ");
                    scanf("%f", &D.M.Fit);
                    break;
                }

                case 4:
                {
                    printf("Enter Marks of Eng: ");
                    scanf("%f", &D.M.Eng);
                    break;
                }

                case 5:
                {
                    printf("Enter Marks of Practical: ");
                    scanf("%f", &D.M.Prac);
                    break;
                }

                case 6:
                {
                    printf("Enter Name: ");
                    scanf("%19s", D.Name);
                    printf("Enter Marks of C: ");
                    scanf("%f", &D.M.C);
                    printf("Enter Marks of Fit: ");
                    scanf("%f", &D.M.Fit);
                    printf("Enter Marks of Eng: ");
                    scanf("%f", &D.M.Eng);
                    printf("Enter Marks of Practical: ");
                    scanf("%f", &D.M.Prac);
                    break;
                }
            }

            // Move back and overwrite
            fseek(fp, -sizeof(struct DATABASE), SEEK_CUR);
            fwrite(&D, sizeof(struct DATABASE), 1, fp);

            printf("\nRecord Updated Successfully!\n");

            fclose(fp);
            return; // stop after update
        }
    }

    if (!found)
    {
        printf("\nData Not Found With this Roll No.\n");
    }

    fclose(fp);
    return;
}

void datadelete(char TableName[],int Roll)
{
    FILE *fp, *temp;
    struct DATABASE D;
    int found = 0;
    fp = fopen(TableName,"rb");
    temp = fopen("temp_delete.dat","wb");

    if (fp == NULL || temp == NULL)
    {
        printf("\nFile error\nTrying Again!!\n");
        if(fp) fclose(fp);
        if(temp) fclose(temp);
        return;
    }

    while (fread(&D,sizeof(struct DATABASE),1,fp) == 1)
    {
        if (D.Roll_no == Roll)
        {
            found = 1;
            continue; 
        }       

        fwrite(&D, sizeof(struct DATABASE), 1, temp); 
    }

    fclose(fp);
    fclose(temp);

    if(!found)  
    {
        printf("\nRecord Not Found\nTry Again !!");
        remove("temp_delete.dat");
    }
    else
    {
            // Old Data Removed
            remove(TableName);

            // Rename Temp file to original file
            rename("temp_delete.dat",TableName);

        printf("\nData Deleted Successfully");
    }

    printf("\nPress Enter to Return...");
    waitForEnter();
    return;
}

void Tabledelete(char TableName[])
{
    char Confirmation;
    
    printf("Are You Sure You Wish to Delete %s\n",TableName);
    printf("Press Y For yes or N for no : ");
    scanf(" %c",&Confirmation);
    
        if (Confirmation == 'Y' || Confirmation == 'y')
        {
            if (remove(TableName) == 0)
            {            
                printf("\nTable Deleted Successfully \n");
                removeFromMaster(TableName);
            }
            else
            {
                printf("\nError Deleting Table\n");
            }
                
        }
        else if (Confirmation == 'N' || Confirmation == 'n')
        {
            printf("\nOperation Cancelled");
        }
        else
        {
            printf("\nInvalid Input ,Try Again ");
        }
    
    printf("\nPress Enter to return...");
    waitForEnter();
    return;
    
}

void Tableview()
{
    FILE *master;
    char name[50];

    master = fopen("tables.dat","r");

    if (master == NULL)
    {
        printf("No Tables Found \nReturning\n");
        printf("\nPress Enter to return...");
        return;  
    }
    
    printf("\n--- All Tables ---\n");
    
    while (fscanf(master, "%s", name) != EOF)
    {
        printf("%s\n", name);
    }

    fclose(master);
    printf("\nPress Enter to return...");
    waitForEnter();
    return;

}

void removeFromMaster(char TableName[])
{
    FILE *master, *temp;
    char name[50];
    int found = 0;

    master = fopen("tables.dat", "r");
    temp = fopen("temp_master.dat", "w");

    if (master == NULL || temp == NULL)
    {
        printf("\nInternal Error\n Returning\n");
        return;
    }

    while (fscanf(master, "%s", name) != EOF)
    {
        if (strcmp(name, TableName) == 0)
        {
            found = 1;
            continue; // skip this one
        }

        fprintf(temp, "%s\n", name);
    }

    fclose(master);
    fclose(temp);

    remove("tables.dat");
    rename("temp_master.dat", "tables.dat");
    return;
 
}

void waitForEnter()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // clear buffer
    getchar(); // wait for user
}