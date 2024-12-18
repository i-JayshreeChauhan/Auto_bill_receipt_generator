#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_data(char *mainstr, const char *substring, const char *replstring) ;

int main() {
    FILE *fptr = NULL;

    char prefef_compN[] = "[COMPANY_NAME]";
    char COMPANY_NAME[] = "GRUB GARAGE";

    char prefef_ON[] = "[OUTLET_NAME]";
    char OUTLET_NAME[] = "BARODA OUTLET";

    char prefef_custN[] = "[CUSTOMER_NAME]";
    char customer_name[100];

    char prefef_BA[] = "[BILL_AMOUNT]";
    float BILL_AMOUNT = 0;
    char billAmount[8] = { '0', '0', '0', '0', '0', '0', '0', '\0' };

    char ch;
    int i = 0;
    int data_length = 500;
    int newlength = 0;

    char *file_data = (char *)(calloc(data_length, sizeof(char)));
    if (!file_data) {
        printf("0_Memory allocation failed\n");
        return 1;
    }

    printf("\n----- This program will generate Bill -----\n\n");
    printf("Customer Name: ");
    fgets(customer_name, sizeof(customer_name), stdin);

    // Remove trailing newline from customer_name
    customer_name[strcspn(customer_name, "\n")] = '\0';      //strcspn(customer_name, "\n") --> will return the address of newline char , we will replace it with null char

    printf("Bill amount (1-10000 rs): ");
    scanf("%f", &BILL_AMOUNT);
    snprintf(billAmount, sizeof(billAmount), "%7.1f", BILL_AMOUNT);

   // printf("\n%s",billAmount);


    fptr = fopen("BillTemplate.txt", "r");
    if (!fptr) {
        printf("Error: Could not open BillTemplate.txt\n");
        free(file_data);
        return 1;
    }





    // Read file content
    while ((ch = fgetc(fptr)) != EOF) 
    {
        if (i >= (data_length - 1) )
        { // Ensure space for null terminator
            data_length += 10;
            char *temp = realloc(file_data, data_length);
            if (!temp) 
            {
                free(file_data);
                printf("1_Memory allocation failed\n");
                fclose(fptr);
                return 1;
            }
            file_data = temp;
        }
        file_data[i++] = ch;
    }

    file_data[i] = '\0';


        int original_file_length = strlen(file_data);                // 137 without null , ie 138th = null

        //printf("\n\noriginal length : %d\n\n",original_file_length);
        //printf("\n\n%s\n\n",file_data);

    
        replace_data(file_data,prefef_compN,COMPANY_NAME);
        replace_data(file_data,prefef_ON,OUTLET_NAME);
        replace_data(file_data,prefef_custN,customer_name);
        replace_data(file_data,prefef_BA,billAmount);



    fclose(fptr);


    // Write to bill.txt
    
    
    
    fptr = fopen("bill.txt", "w");
    if (!fptr) {
        printf("Error: Could not open bill.txt for writing\n");
        free(file_data);
        return 1;
    }

    

    fprintf(fptr, "%s", file_data);
    fclose(fptr);

    free(file_data);

    printf("\nBill has been generated successfully.\n");

    return 0;
}

void replace_data(char *mainstr, const char *substring, const char *replstring) 
{
 
 
                char *match=NULL;

                while( (match = strstr(mainstr, substring)) !=NULL)
                {

                    int index1 = match - mainstr; // Start of the match
                    int substring_len = strlen(substring);
                    int replstring_len = strlen(replstring);

                    // Calculate the total length of the new string
                    int total_length = strlen(mainstr) - substring_len + replstring_len + 1;
                    //printf("\n\ntotal length : %d\n\n",total_length);

                    // Create a result buffer to store the new string
                    char *result = (char *)calloc(total_length, sizeof(char));
                    if (!result) 
                    {
                        printf("3_Memory allocation failed\n");
                        
                    }


                    // Copy parts into the result buffer
                    strncpy(result, mainstr, index1);            // Copy up to the match
                    //printf("\n\n%s\n\n",result);
                    strcat(result, replstring);                 // Add the replacement string
                    //printf("\n\n%s\n\n",result);
                    strcat(result, mainstr + index1 + substring_len); // Add the remaining part of the string
                    //printf("\n\n%s\n\n",result);

                    //printf("\n\n%s\n\n",result);

                    mainstr=realloc(mainstr,total_length);
                    strcpy(mainstr,result);

                    //printf("\n\n%s\n\n",mainstr);
                

                    free(result);

                }


    
}
