#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void generateBillHeader(char name[500],char date[20])
{
	printf("\n\n");
	printf("\t   ADV.Restaurant");
	printf("\n\t ------------------");
	printf("\nDate:%s",date);
	printf("\nInvoice To: %s",name);
	printf("\n");
	printf("--------------------------------------------\n");
	printf("Items\t\t");
	printf("Qty\t\t");
	printf("Total\t\t");
	printf("\n------------------------------------------");
	printf("\n\n");
}

void generateBillBody(char item[300],int qty,float price)
{
	printf("%s\t\t",item);
	printf("%d\t\t",qty);
	printf("%.2f\t\t",qty*price);
	printf("\n");
}

void generateBillFooter(float total)
{
	printf("\n");
	float dis=0.1*total;
	float netTotal=total - dis;
	float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst;
	printf("------------------------------------------\n");
	printf("Sub Total\t\t\t%.2f",total);
	printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
	printf("\n\t\t\t-------------------");
	printf("\nNet Total\t\t\t%.2f",netTotal);
	printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
	printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
	printf("\n------------------------------------------");
	printf("\nGrand Total\t\t\t%.2f",grandTotal);
	printf("\n------------------------------------------");
}

struct item{
	char item[300];
	float price;
	int qty;
};
struct orders{
	char customer[500];
	char date[50];
	int numofItems;
	struct item itm[500];
};

int main()
{
	int opt;
	int n;
	struct orders ord;
	struct orders order;
	char saveBill='y',countFlag='y';
	FILE *fp;
	char name[50];
	while(countFlag == 'y'){
	int invoiceFound=0;	
	float total=0;
	printf("\t============ADV. RESTAURANT===========");
	printf("\n\n1.Generate Invoices");
	printf("\n2.Show all Invoices");
	printf("\n3.Search Invoices");
	printf("\n4.Exit");
	printf("\n\nYour choice:\t");
	scanf("%d",&opt);
	fgetc(stdin);
	switch(opt)
	{
		case 1:
		//system("clear");
		printf("Please Enter Name of Customer:\t");
		fgets(ord.customer,50,stdin);
		ord.customer[strlen(ord.customer)-1]=0;
		strcpy(ord.date,__DATE__);
		printf("Please Enter the number of Items:\t");
		scanf("%d",&n);
		ord.numofItems=n;
		for(int i=0;i<n;i++)
		{
			fgetc(stdin);
			printf("\n\n");
			printf("Please enter the item %d:\t",i+1);
			fgets(ord.itm[i].item,20,stdin);
			ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
			printf("Please enter the quantity:\t");
			scanf("%d",&ord.itm[i].qty);
			printf("Please enter the unit price:\t");
			scanf("%f",&ord.itm[i].price);
			total+= ord.itm[i].qty * ord.itm[i].price;
		}
		
		generateBillHeader(ord.customer,ord.date);
		for(int i=0;i<ord.numofItems;i++)
		{
			generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
		}
		
		generateBillFooter(total);
		printf("\nDo you want to save the invoice:\t");
		scanf("%s",&saveBill);	
		if(saveBill=='y')
		{
			fp=fopen("RestaurantBill.txt","a+");
			fwrite(&ord,sizeof(struct orders),1,fp);
			if(fwrite!=0)
				printf("\nSuccessfully Saved");
				
			else
				printf("\nError in Saving");
			fclose(fp);
		}		
		break;
		case 2:
			//system("clear");
			fp=fopen("RestaurantBill.txt","r");
			printf("\n***********your invoices*********");
			while(fread(&order,sizeof(struct orders),1,fp))
			{	
				total=0;
				generateBillHeader(order.customer,order.date);			
				for(int i=0;i<order.numofItems;i++)
				{
					generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
					total+= order.itm[i].qty * order.itm[i].price;
				}
				generateBillFooter(total);
			}
			fclose(fp);
		break;
		case 3:	
			
			printf("\nEnter the name of the customer:\t");
			//fgetc(stdin);
			fgets(name,50,stdin);
			name[strlen(name)-1]=0;		
			//system("clear");
			fp=fopen("RestaurantBill.txt","r");
			printf("\n***********your invoices %s*********\n",name);
			while(fread(&order,sizeof(struct orders),1,fp))
			{	
				total=0;
				if(!strcmp(order.customer,name))
				{
					generateBillHeader(order.customer,order.date);			
					for(int i=0;i<order.numofItems;i++)
					{
						generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
						total+= order.itm[i].qty * order.itm[i].price;
					}
					generateBillFooter(total);
					invoiceFound=1;
				}
				
			}
			if(!invoiceFound)
			{
				printf("\nsorry the invoice for %s does not exits",name);
			}
			fclose(fp);
		break;
		case 4:
			printf("\n\t\t Bye Bye :)\n\n");
			exit(0);
		default :
			printf("\nsorry invalid choice\n");
			break;
	}
	printf("\n Do you want to perform another operation [y/n]:");
	scanf("%s",&countFlag);
	
    }
	printf("\n\n");
	
return 0;
}
