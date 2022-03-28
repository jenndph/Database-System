#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysql.h"


#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "user";
const char* pw = "6843";
const char* db = "project";

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}

		printf("********************************************\n");
		printf("******** 20181614 김주연 DBProject2 ********\n");
		printf("********************************************\n\n");

		const char* query;
		int state = 0;

		int type;
		int type_one = 1, truck_num = 1;
		char year[5], month[3], name[18];
		char *str, *tmp;
		FILE* fp = fopen("20181614_1.txt", "r");// 20181614_1.txt에는 table create, update 코드가 있음
		while (!feof(fp)) {						// 파일에서 한 줄씩 읽어와서 데이터베이스 초기화 수행 
			str = (char*)malloc(500 * sizeof(char));
			fgets(str, 500, fp);
			
			state = mysql_query(connection, str);
			if (state != 0) continue;
			sql_result = mysql_store_result(connection);
			mysql_free_result(sql_result);
			free(str);
		}
		fclose(fp);
		while (1) {								// 입력으로 0을 받기 전까지 while loop 수행
			printf("\n------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE I\n");
			printf("\t2. TYPE II\n");
			printf("\t3. TYPE III\n");
			printf("\t4. TYPE IV\n");
			printf("\t5. TYPE V\n");
			printf("\t0. QUIT\n\n");
			printf("Which type of query? ");
			scanf("%d", &type);
			printf("\n\n");

			if(type==1){
				printf("---- TYPE I ----\n\n");		//  Assume truck 1721 is destroyed in a crash. 
				while(truck_num!=0){
					printf("Input the number of truck : ");
					scanf("%d", &truck_num);
					if (truck_num == 0) break;		// truck number 0이면 back, 1721이 아니면 재입력 받음
					else if (truck_num != 1721) printf("Truck %d is not destroyed.\n\n", truck_num);
					else {							// truck number 1721인 경우 type 1-1, 1-2, 1-3 수행
						while (1) {
							printf("\n------- Subtypes in TYPE I -------\n\n");
							printf("\t1. TYPE I-1\n");
							printf("\t2. TYPE I-2\n");
							printf("\t3. TYPE I-3\n");
							printf("\t0. QUIT\n");
							printf("Which type of query? ");
							scanf("%d", &type_one);
							if (type_one == 0) break;
							if (type_one == 1) {
								printf("\n---- TYPE I-1 ----\n\n");
								printf("** Find all customers who had a package on the truck at the time of the crash. **\n");
								fp = fopen("20181614_2.txt", "r");		// txt 파일에 저장된 query 읽어옴
								while (!feof(fp)) {
									str = (char*)malloc(500 * sizeof(char));
									fgets(str, 500, fp);
									printf("Customer name : ");
									state = mysql_query(connection, str);
									if (state != 0) continue;
									sql_result = mysql_store_result(connection);
									while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
									{
										printf("%s %s  ", sql_row[0], sql_row[1]);	// customer는 name, phone_number로 구분되므로 둘 다 표시
									}
									printf("\n\n");
									mysql_free_result(sql_result);
									free(str);
								}
								fclose(fp);
							}
							else if (type_one == 2) {
								printf("\n---- TYPE I-2 ----\n\n");
								printf("** Find all recipients who had a package on that truck at the time of the crash. **\n");
								fp = fopen("20181614_3.txt", "r");		// txt 파일에 저장된 query 읽어옴
								while (!feof(fp)) {
									str = (char*)malloc(500 * sizeof(char));
									fgets(str, 500, fp);
									printf("Recipient name : ");
									state = mysql_query(connection, str);
									if (state != 0) continue;
									sql_result = mysql_store_result(connection);
									while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
									{
										printf("%s %s  ", sql_row[0], sql_row[1]);	// recipient는 name, phone_number로 구분되므로 둘 다 표시
									}
									printf("\n\n");
									mysql_free_result(sql_result);
									free(str);
								}
								fclose(fp);
							}
							else if (type_one == 3) {
								printf("\n---- TYPE I-3 ----\n\n");
								printf("** Find the last successful delivery by that truck prior to the crash. **\n");
								fp = fopen("20181614_4.txt", "r");		// txt 파일에 저장된 query 읽어옴
								while (!feof(fp)) {
									str = (char*)malloc(500 * sizeof(char));
									fgets(str, 500, fp);
									printf("Delivery ID : ");
									state = mysql_query(connection, str);
									if (state != 0) continue;
									sql_result = mysql_store_result(connection);
									while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
									{
										printf("%s  ", sql_row[0]);	// package는 package_id로 구분되므로 package_id만 표시
									}
									printf("\n\n");
									mysql_free_result(sql_result);
									free(str);
								}
								fclose(fp);
							}
							else continue;
						}
						if (type_one == 0) break;
					}
				}
			}
			else if (type==2) {
				printf("---- TYPE II ----\n\n");
				while (1) {
					printf("** Find the customer who has shipped the most packages in certain year **\n");
					printf(" Which Year? : ");
					scanf("%s", year);						// stdin으로 연도 입력받음
					if (!strcmp(year,"0")) break;
					else {
						fp = fopen("20181614_5.txt", "r");		// txt 파일에 저장된 query 읽어옴
						str = (char*)malloc(500 * sizeof(char));
						tmp = (char*)malloc(100 * sizeof(char));
						fgets(str, 500, fp);				// 입력받은 연도를 query에 넣어주는 과정
						strcat(str, year);
						fgets(tmp, 500, fp);
						strcat(str, tmp);
						printf("Customer name : ");
						state = mysql_query(connection, str);
						if (state != 0) continue;
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("%s %s  ", sql_row[0], sql_row[1]);	// customer는 name, phone_number로 구분되므로 둘 다 표시
						}
						printf("\n\n");
						mysql_free_result(sql_result);
						free(str);
						fclose(fp);
					}
				}
			}
			else if (type == 3) {
				printf("---- TYPE III ----\n\n");
				while (1) {
					printf("** Find the customer who has spent the most money on shipping in the past certain year **\n");
					printf(" Which Year? : ");
					scanf("%s", year);						// stdin으로 연도 입력받음
					if (!strcmp(year, "0")) break;
					else {
						fp = fopen("20181614_6.txt", "r");		// txt 파일에 저장된 query 읽어옴
						str = (char*)malloc(500 * sizeof(char));
						tmp = (char*)malloc(100 * sizeof(char));
						fgets(str, 500, fp);				// 입력받은 연도를 query에 넣어주는 과정
						strcat(str, year);
						fgets(tmp, 500, fp);
						strcat(str, tmp);
						printf("Customer name : ");
						state = mysql_query(connection, str);
						if (state != 0) continue;
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("%s %s  ", sql_row[0], sql_row[1]);	// customer는 name, phone_number로 구분되므로 둘 다 표시
						}
						printf("\n\n");
						mysql_free_result(sql_result);
						free(str);
						fclose(fp);
					}
				}
			}
			else if (type == 4) {
				printf("---- TYPE IV ----\n\n");
				printf("** Find those packages that were not delivered within the promised time **\n");
				fp = fopen("20181614_7.txt", "r");		// txt 파일에 저장된 query 읽어옴
				while (!feof(fp)) {
					str = (char*)malloc(1400 * sizeof(char));
					fgets(str, 1400, fp);
					state = mysql_query(connection, str);
					if (state != 0) continue;
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s  ", sql_row[0]);	// package는 package_id로 구분되므로 package_id만 표시
					}
					printf("\n\n");
					mysql_free_result(sql_result);
					free(str);
				}
				fclose(fp);
			}
			else if (type == 5) {
				char day[8];
				char* y, * m;
				y = (char*)calloc(5, sizeof(char));
				m = (char*)calloc(3, sizeof(char));
				char* number = (char*)calloc(12, sizeof(char));
				char* fname = (char*)calloc(40, sizeof(char));
				printf("---- TYPE V ----\n\n");
				printf("** Generate the bill for each customer for the past certain month **\n");
				printf("Customer name : ");
				scanf("%s", name);					// stdin으로 customer 이름 입력받음
				printf("Customer number : ");
				scanf("%s", number);				// stdin으로 customer phone_number 입력받음 ( customer는 name, phone_number로 구분되므로 둘 다 입력)
				printf("Which month(YYYY-MM)? : ");
				scanf("%s", day);					// stdin으로 날짜 입력받음
				strncpy(y, day, 4);
				strncpy(m, day + 5, 2);
				printf("Generating Bill...\n\n");
				
				strcat(fname, "bill_");				// output file 이름 생성 ("bill_YYYYMM_customer-name_customer-phone-number.txt")
				strcat(fname, y);
				strcat(fname, m);
				strcat(fname, "_");
				strcat(fname, name);
				strcat(fname, "_");
				strcat(fname, number);
				strcat(fname, ".txt");
				FILE* f_out = fopen(fname, "w");

				fp = fopen("20181614_8.txt", "r");		// txt 파일에 저장된 query 읽어옴. type5-1.txt는 V의 첫 번째 항목에 해당하는 bill 생성
				str = (char*)malloc(500 * sizeof(char));
				tmp = (char*)malloc(200 * sizeof(char));
				fgets(str, 500, fp);				// 입력받은 customer name, phone_number, 날짜를 query에 넣어주는 과정
				strcat(str, "\"");
				strcat(str, name);
				strcat(str, "\"");
				fgets(tmp, 200, fp);
				strcat(str, tmp);
				strcat(str, "\"");
				strcat(str, number);
				strcat(str, "\"");
				fgets(tmp, 200, fp);
				strcat(str, tmp);
				strncat(str, y, 4);
				fgets(tmp, 200, fp);
				strcat(str, tmp);
				strncat(str, m, 2);
				state = mysql_query(connection, str);
				if (state != 0) continue;
				sql_result = mysql_store_result(connection);
				fprintf(f_out, "Customer\tPhone_number\tAddress\tAmount\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
				{
					fprintf(f_out, "%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]); 	
					// customer는 name, phone_number로 구분되므로 파일에 둘 다 표시
					//  A simple bill: customer, address, and amount owed  항목 포함
				}
				fprintf(f_out, "\n");
				mysql_free_result(sql_result);
				free(str);
				fclose(fp);

				fprintf(f_out, "------------------------------\n");
				fprintf(f_out, "Itemized Billing List\n");
				fp = fopen("20181614_9.txt", "r");		// txt 파일에 저장된 query 읽어옴. type5-2.txt는 V의 두 번째, 세 번째 항목에 해당하는 bill 생성
				str = (char*)malloc(500 * sizeof(char));
				tmp = (char*)malloc(200 * sizeof(char));
				fgets(str, 500, fp);				// 입력받은 customer name, phone_number, 날짜를 query에 넣어주는 과정
				strcat(str, "\"");
				strcat(str, name);
				strcat(str, "\"");
				fgets(tmp, 200, fp);
				strcat(str, tmp);
				strcat(str, "\"");
				strcat(str, number);
				strcat(str, "\"");
				fgets(tmp, 100, fp);
				strcat(str, tmp);
				strncat(str, y, 4);
				fgets(tmp, 100, fp);
				strcat(str, tmp);
				strncat(str, m, 2);
				fgets(tmp, 200, fp);
				strcat(str, tmp);

				state = mysql_query(connection, str);
				if (state != 0) continue;
				sql_result = mysql_store_result(connection);
				fprintf(f_out, "| Package Number | Amount | Serivce Type | Payment Type | Timeliness of Delivery|\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
				{
					fprintf(f_out, "%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
					// A bill listing charges by type of service  항목 포함
					// An itemize billing listing each individual shipment and the charges for it  항목 포함
				}
				fprintf(f_out, "\n");
				mysql_free_result(sql_result);
				free(str);
				fclose(fp);
				fclose(f_out);
				printf("Generation Completed\n\n");
			}
			else if (type == 0) break;
			else continue;
		}
		
		fp = fopen("20181614_10.txt", "r");// 20181614_10.txt에는 table delete, drop 코드가 있음
		while (!feof(fp)) {				// 한 줄 씩 읽어 와서 database 삭제 수행
			str = (char*)malloc(500 * sizeof(char));
			fgets(str, 500, fp);

			state = mysql_query(connection, str);
			if (state != 0) continue;
			sql_result = mysql_store_result(connection);
			mysql_free_result(sql_result);
			free(str);
		}
		fclose(fp);

		mysql_close(connection);
	}
	return 0;
}