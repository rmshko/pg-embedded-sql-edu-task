/* Processed by ecpg (10.10 (Ubuntu 10.10-0ubuntu0.18.04.1)) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "main.pgc"
#include <iostream>
#include <pgtypes_date.h>

#line 1 "/usr/include/postgresql/sqlca.h"
#ifndef POSTGRES_SQLCA_H
#define POSTGRES_SQLCA_H

#ifndef PGDLLIMPORT
#if  defined(WIN32) || defined(__CYGWIN__)
#define PGDLLIMPORT __declspec (dllimport)
#else
#define PGDLLIMPORT
#endif							/* __CYGWIN__ */
#endif							/* PGDLLIMPORT */

#define SQLERRMC_LEN	150

#ifdef __cplusplus
extern "C"
{
#endif

struct sqlca_t
{
	char		sqlcaid[8];
	long		sqlabc;
	long		sqlcode;
	struct
	{
		int			sqlerrml;
		char		sqlerrmc[SQLERRMC_LEN];
	}			sqlerrm;
	char		sqlerrp[8];
	long		sqlerrd[6];
	/* Element 0: empty						*/
	/* 1: OID of processed tuple if applicable			*/
	/* 2: number of rows processed				*/
	/* after an INSERT, UPDATE or				*/
	/* DELETE statement					*/
	/* 3: empty						*/
	/* 4: empty						*/
	/* 5: empty						*/
	char		sqlwarn[8];
	/* Element 0: set to 'W' if at least one other is 'W'	*/
	/* 1: if 'W' at least one character string		*/
	/* value was truncated when it was			*/
	/* stored into a host variable.             */

	/*
	 * 2: if 'W' a (hopefully) non-fatal notice occurred
	 */	/* 3: empty */
	/* 4: empty						*/
	/* 5: empty						*/
	/* 6: empty						*/
	/* 7: empty						*/

	char		sqlstate[5];
};

struct sqlca_t *ECPGget_sqlca(void);

#ifndef POSTGRES_ECPG_INTERNAL
#define sqlca (*ECPGget_sqlca())
#endif

#ifdef __cplusplus
}
#endif

#endif

#line 3 "main.pgc"

using namespace std;

/* exec sql whenever sqlerror  sqlprint ; */
#line 6 "main.pgc"


void connectToDatabase(const char* host, const char* dbname, const char* user, const char* pass) {
	/* exec sql begin declare section */
		 
		    
		    
		    
	
#line 10 "main.pgc"
 char target [ 256 ] ;
 
#line 11 "main.pgc"
 const char * db = dbname ;
 
#line 12 "main.pgc"
 const char * u = user ;
 
#line 13 "main.pgc"
 const char * p = pass ;
/* exec sql end declare section */
#line 14 "main.pgc"


	strcpy(target, db);
	strcat(target, "@");
	strcat(target, host);

	cout << "target: " << target << endl;

	{ ECPGconnect(__LINE__, 0, target , u , p , NULL, 0); 
#line 22 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 22 "main.pgc"

}

/* SCHOOLS INTERFACE */

void getAllSchools() {
	/* exec sql begin declare section */
	 
	 

	
#line 29 "main.pgc"
 unsigned int num ;
 
#line 30 "main.pgc"
 char address [ 100 ] ;
/* exec sql end declare section */
#line 32 "main.pgc"


	/* declare cursor_school cursor for select num , address from school order by num */
#line 35 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare cursor_school cursor for select num , address from school order by num", ECPGt_EOIT, ECPGt_EORT);
#line 37 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 37 "main.pgc"


	while (true) {
		{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch cursor_school", ECPGt_EOIT, 
	ECPGt_unsigned_int,&(num),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(address),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 40 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 40 "main.pgc"


		if (sqlca.sqlcode == ECPG_NOT_FOUND) {
			break;
		}

		cout << endl;
		cout << "School num: " << num << endl;
		cout << "School address: " << address << endl;
		cout << endl;
	}

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close cursor_school", ECPGt_EOIT, ECPGt_EORT);
#line 52 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 52 "main.pgc"


	return;
}

void getSchoolByNum() {
	cout << "Enter school number: " << endl;
	unsigned schoolNum;
	cin >> schoolNum;

	/* exec sql begin declare section */
	    
	 
	
#line 63 "main.pgc"
 const unsigned int num = schoolNum ;
 
#line 64 "main.pgc"
 char address [ 100 ] ;
/* exec sql end declare section */
#line 65 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select num , address from school where num = $1 ", 
	ECPGt_unsigned_int,&(num),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_unsigned_int,&(num),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(address),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 67 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 67 "main.pgc"

	if (sqlca.sqlcode == ECPG_NOT_FOUND || strncmp(sqlca.sqlstate, "00", 2))
	{
		cout << "Not found" << endl;
		return;
	}
	cout << endl;
	cout << "School number: " << num << endl;
	cout << "School address: " << address << endl;
	cout << endl;

	return;
}

void addSchool() {
	cout << "Enter school number:" << endl;
	unsigned schoolNumber;
	cin >> schoolNumber;

	cout << "Enter school address:" << endl;
	string schoolAddressTmp;
	cin.ignore();
	getline(cin, schoolAddressTmp, '\n');
    const char* schoolAddress = schoolAddressTmp.c_str();
	
	/* exec sql begin declare section */
	    
	    

	
#line 93 "main.pgc"
 const unsigned int num = schoolNumber ;
 
#line 94 "main.pgc"
 const char * address = schoolAddress ;
/* exec sql end declare section */
#line 96 "main.pgc"

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into school values ( $1  , $2  )", 
	ECPGt_unsigned_int,&(num),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(address),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 97 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 97 "main.pgc"

	{ ECPGtrans(__LINE__, NULL, "commit");
#line 98 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 98 "main.pgc"


	return;
}

void updateSchool() {
	cout << "Enter school number:" << endl;
	unsigned schoolNumber;
	cin >> schoolNumber;

	cout << "Enter school address:" << endl;
	string schoolAddressTmp;
	cin.ignore();
	getline(cin, schoolAddressTmp, '\n');
    const char* schoolAddress = schoolAddressTmp.c_str();

	/* exec sql begin declare section */
	    
	    

	
#line 115 "main.pgc"
 const unsigned int num = schoolNumber ;
 
#line 116 "main.pgc"
 const char * address = schoolAddress ;
/* exec sql end declare section */
#line 118 "main.pgc"

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update school set address = $1  where num = $2 ", 
	ECPGt_char,&(address),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(num),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 119 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 119 "main.pgc"


	{ ECPGtrans(__LINE__, NULL, "commit");
#line 121 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 121 "main.pgc"


	return;
}

void deleteSchool() {
    cout << "Enter school number:" << endl;
    unsigned schoolNumber;
    cin >> schoolNumber;

    /* exec sql begin declare section */
        
    
#line 132 "main.pgc"
 const unsigned int num = schoolNumber ;
/* exec sql end declare section */
#line 133 "main.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "delete from school where num = $1 ", 
	ECPGt_unsigned_int,&(num),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 135 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 135 "main.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 137 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 137 "main.pgc"


    return;
}

void schoolMenu() {
	while (true) {
		cout << "School menu:" << endl;
		cout << "1. Add school" << endl;
		cout << "2. Get school info" << endl;
		cout << "3. Update school" << endl;
		cout << "4. Delete school" << endl;
		cout << "5. Show all schools" << endl;
		cout << "0. Exit" << endl;
		int number;
		cin >> number;
		switch (number) {
			case 1: {
				addSchool();
				break;
			}
			case 2: {
				getSchoolByNum();
				break;
			}
			case 3: {
				updateSchool();
				break;
			}
			case 4: {
				deleteSchool();
				break;
			}
			case 5: {
				getAllSchools();
				break;
			}
			case 0: {
				return;
			}
			default: {
				cout << "Wrong number. Enter again" << endl;
				break;
			}
		}
	}
}

/* FORMS INTERFACE */

void getAllForms() {
	/* exec sql begin declare section */

	 
	 	
	 
	 	

	
#line 190 "main.pgc"
 char formMasterName [ 60 ] ;
 
#line 191 "main.pgc"
 char formNum [ 4 ] ;
 
#line 192 "main.pgc"
 unsigned int schoolNum ;
 
#line 193 "main.pgc"
 unsigned int studentsNum ;
/* exec sql end declare section */
#line 195 "main.pgc"


	/* declare cursor_form cursor for select num , school_number , form_master_name , ( select count ( * ) from student where form_num = num ) as number_of_students from form order by num */
#line 200 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare cursor_form cursor for select num , school_number , form_master_name , ( select count ( * ) from student where form_num = num ) as number_of_students from form order by num", ECPGt_EOIT, ECPGt_EORT);
#line 202 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 202 "main.pgc"


	while (true) {
		{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch cursor_form", ECPGt_EOIT, 
	ECPGt_char,(formNum),(long)4,(long)1,(4)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(schoolNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(formMasterName),(long)60,(long)1,(60)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(studentsNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 206 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 206 "main.pgc"


		if (sqlca.sqlcode == ECPG_NOT_FOUND) {
			break;
		}

		cout << endl;
		cout << "Form number: " << formNum << endl;
		cout << "School number: " << schoolNum << endl;
		cout << "Name of form master: " << formMasterName << endl;
		cout << "Number of students: " << studentsNum << endl;
		cout << endl;
	}

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close cursor_form", ECPGt_EOIT, ECPGt_EORT);
#line 220 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 220 "main.pgc"


	return;
}

void getFormByNumAndSchoolNum() {
	cout << "Enter form number: " << endl;
	string formNumberTmp;
	cin.ignore();
	getline(cin, formNumberTmp, '\n');
    const char* formNumber = formNumberTmp.c_str();

	cout << "Enter school number: " << endl;
	unsigned schoolNumber;
	cin >> schoolNumber;

	/* exec sql begin declare section */
	    
	    
	 
	 

	
#line 237 "main.pgc"
 const char * formNum = formNumber ;
 
#line 238 "main.pgc"
 const unsigned int schoolNum = schoolNumber ;
 
#line 239 "main.pgc"
 unsigned int studentsNum ;
 
#line 240 "main.pgc"
 char formMasterName [ 100 ] ;
/* exec sql end declare section */
#line 242 "main.pgc"


	cout << formNum << ' ' << schoolNum << endl;

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select num , school_number , form_master_name , ( select count ( * ) from student where form_num = $1  ) as number_of_students from form where num = $2  and school_number = $3 ", 
	ECPGt_char,&(formNum),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(formNum),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(schoolNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,&(formNum),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(schoolNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(formMasterName),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(studentsNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 250 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 250 "main.pgc"


	if (sqlca.sqlcode == ECPG_NOT_FOUND || strncmp(sqlca.sqlstate, "00", 2))
	{
		cout << "Not found" << endl;
		return;
	}
	cout << endl;
	cout << "Form number: " << formNum << endl;
	cout << "School number: " << schoolNum << endl;
	cout << "Name of form master: " << formMasterName << endl;
	cout << "Number of students: " << studentsNum << endl;
	cout << endl;

	return;
}

void addForm() {
	cout << "Enter form number: " << endl;
	string formNumberTmp;
	cin.ignore();
	getline(cin, formNumberTmp, '\n');
    const char* formNumber = formNumberTmp.c_str();

	cout << "Enter school number: " << endl;
	unsigned schoolNumber;
	cin >> schoolNumber;

	cout << "Enter name of form master:" << endl;
	string masterNameTmp;
	cin.ignore();
	getline(cin, masterNameTmp, '\n');
	const char* masterName = masterNameTmp.c_str();
	
	/* exec sql begin declare section */
	    
	    
	    

	
#line 285 "main.pgc"
 const char * formNum = formNumber ;
 
#line 286 "main.pgc"
 const unsigned int schoolNum = schoolNumber ;
 
#line 287 "main.pgc"
 const char * formMasterName = masterName ;
/* exec sql end declare section */
#line 289 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into form values ( $1  , $2  , $3  )", 
	ECPGt_char,&(formNum),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(schoolNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(formMasterName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 292 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 292 "main.pgc"

	{ ECPGtrans(__LINE__, NULL, "commit");
#line 293 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 293 "main.pgc"


	return;
}

void updateForm() {
	cout << "Enter form number: " << endl;
	string formNumberTmp;
	cin.ignore();
	getline(cin, formNumberTmp, '\n');
    const char* formNumber = formNumberTmp.c_str();

	cout << "Enter school number:" << endl;
	unsigned schoolNumber;
	cin >> schoolNumber;

	cout << "Enter name of form master:" << endl;
	string masterNameTmp;
	cin.ignore();
	getline(cin, masterNameTmp, '\n');
	const char* masterName = masterNameTmp.c_str();

	/* exec sql begin declare section */
	    
	    
	    

	
#line 316 "main.pgc"
 const char * formNum = formNumber ;
 
#line 317 "main.pgc"
 const unsigned int schoolNum = schoolNumber ;
 
#line 318 "main.pgc"
 const char * formMasterName = masterName ;
/* exec sql end declare section */
#line 320 "main.pgc"

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update form set form_master_name = $1  where num = $2  and school_number = $3 ", 
	ECPGt_char,&(formMasterName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(formNum),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(schoolNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 323 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 323 "main.pgc"


	{ ECPGtrans(__LINE__, NULL, "commit");
#line 325 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 325 "main.pgc"


	return;
}

void deleteForm() {
	cout << "Enter form number: " << endl;
	string formNumberTmp;
	cin.ignore();
	getline(cin, formNumberTmp, '\n');
    const char* formNumber = formNumberTmp.c_str();

	cout << "Enter school number:" << endl;
    unsigned schoolNumber;
    cin >> schoolNumber;

    /* exec sql begin declare section */
	    
        
    
#line 342 "main.pgc"
 const char * formNum = formNumber ;
 
#line 343 "main.pgc"
 const unsigned int schoolNum = schoolNumber ;
/* exec sql end declare section */
#line 344 "main.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "delete from form where num = $1  and school_number = $2 ", 
	ECPGt_char,&(formNum),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(schoolNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 346 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 346 "main.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 348 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 348 "main.pgc"


    return;
}

void formMenu() {
	while (true) {
		cout << "Form menu:" << endl;
		cout << "1. Add form" << endl;
		cout << "2. Get form info" << endl;
		cout << "3. Update form" << endl;
		cout << "4. Delete form" << endl;
		cout << "5. Show all forms" << endl;
		cout << "0. Exit" << endl;
		int number;
		cin >> number;
		switch (number) {
			case 1: {
				addForm();
				break;
			}
			case 2: {
				getFormByNumAndSchoolNum();
				break;
			}
			case 3: {
				updateForm();
				break;
			}
			case 4: {
				deleteForm();
				break;
			}
			case 5: {
				getAllForms();
				break;
			}
			case 0: {
				return;
			}
			default: {
				cout << "Wrong number. Enter again" << endl;
				break;
			}
		}
	}
}

/* STUDENTS INTERFACE */

void getAllStudents() {
	/* exec sql begin declare section */

	 
	 	
	 
	 	
	 

	
#line 401 "main.pgc"
 char name [ 60 ] ;
 
#line 402 "main.pgc"
 char address [ 100 ] ;
 
#line 403 "main.pgc"
 date birthDate ;
 
#line 404 "main.pgc"
 unsigned int schoolNum ;
 
#line 405 "main.pgc"
 char formNum [ 4 ] ;
/* exec sql end declare section */
#line 407 "main.pgc"


	/* declare cursor_student cursor for select name , address , birth_date , school_num , form_num from student order by name */
#line 411 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare cursor_student cursor for select name , address , birth_date , school_num , form_num from student order by name", ECPGt_EOIT, ECPGt_EORT);
#line 413 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 413 "main.pgc"


	while (true) {
		{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch cursor_student", ECPGt_EOIT, 
	ECPGt_char,(name),(long)60,(long)1,(60)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(address),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_date,&(birthDate),(long)1,(long)1,sizeof(date), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(schoolNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(formNum),(long)4,(long)1,(4)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 417 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 417 "main.pgc"

		
		if (sqlca.sqlcode == ECPG_NOT_FOUND) {
			break;
		}

		cout << endl;
		cout << "Name: " << name << endl;
		cout << "Address: " << address << endl;
		cout << "Birth date: " << PGTYPESdate_to_asc(birthDate) << endl;
		cout << "School number: " << schoolNum << endl;
		cout << "Form number: " << formNum << endl;
		cout << endl;
	}

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close cursor_student", ECPGt_EOIT, ECPGt_EORT);
#line 432 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 432 "main.pgc"


	return;
}

void getStudentByName() {
	cout << "Enter student name: " << endl;
	string studentNameTmp;
	cin.ignore();
	getline(cin, studentNameTmp, '\n');
    const char* studentName = studentNameTmp.c_str();

	/* exec sql begin declare section */

	    
	 
	 
	 
	 

	
#line 446 "main.pgc"
 const char * name = studentName ;
 
#line 447 "main.pgc"
 char address [ 100 ] ;
 
#line 448 "main.pgc"
 date birthDate ;
 
#line 449 "main.pgc"
 unsigned int schoolNum ;
 
#line 450 "main.pgc"
 char formNum [ 4 ] ;
/* exec sql end declare section */
#line 452 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select name , address , birth_date , school_num , form_num from student where name = $1 ", 
	ECPGt_char,&(name),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,&(name),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(address),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_date,&(birthDate),(long)1,(long)1,sizeof(date), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(schoolNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(formNum),(long)4,(long)1,(4)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 457 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 457 "main.pgc"


	if (sqlca.sqlcode == ECPG_NOT_FOUND || strncmp(sqlca.sqlstate, "00", 2))
	{
		cout << "Not found" << endl;
		return;
	}
	cout << endl;
	cout << "Name: " << name << endl;
	cout << "Address: " << address << endl;
	cout << "Birth date: " << PGTYPESdate_to_asc(birthDate) << endl;
	cout << "School number: " << schoolNum << endl;
	cout << "Form number: " << formNum << endl;
	cout << endl;

	return;
}

void addStudent() {
	cout << "Enter student name: " << endl;
	string studentNameTmp;
	cin.ignore();
	getline(cin, studentNameTmp, '\n');
    const char* studentName = studentNameTmp.c_str();

	cout << "Enter student address: " << endl;
	string studentAddrTmp;
	cin.ignore();
	getline(cin, studentAddrTmp, '\n');
    const char* studentAddr = studentAddrTmp.c_str();

	cout << "Enter student birth date:" << endl;
	string studentBirthDateTmp;
	cin >> studentBirthDateTmp;
    const char* studentBirthDate = studentBirthDateTmp.c_str();

	cout << "Enter school number:" << endl;
	unsigned schoolNumber;
	cin >> schoolNumber;

	cout << "Enter form number:" << endl;
	string formNumberTmp;
	cin.ignore();
	getline(cin, formNumberTmp, '\n');
    const char* formNumber = formNumberTmp.c_str();
	
	/* exec sql begin declare section */

	    
	    
	    
	    
	    
	
	
#line 505 "main.pgc"
 const char * name = studentName ;
 
#line 506 "main.pgc"
 const char * address = studentAddr ;
 
#line 507 "main.pgc"
 const char * birthDate = studentBirthDate ;
 
#line 508 "main.pgc"
 const unsigned int schoolNum = schoolNumber ;
 
#line 509 "main.pgc"
 const char * formNum = formNumber ;
/* exec sql end declare section */
#line 511 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into student values ( $1  , $2  , $3  , $4  , $5  )", 
	ECPGt_char,&(name),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(address),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(birthDate),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(schoolNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(formNum),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 514 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 514 "main.pgc"

	{ ECPGtrans(__LINE__, NULL, "commit");
#line 515 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 515 "main.pgc"


	return;
}

void updateStudent() {
	cout << "Enter student name: " << endl;
	string studentNameTmp;
	cin.ignore();
	getline(cin, studentNameTmp, '\n');
    const char* studentName = studentNameTmp.c_str();

	cout << "Enter student address: " << endl;
	string studentAddrTmp;
	cin.ignore();
	getline(cin, studentAddrTmp, '\n');
    const char* studentAddr = studentAddrTmp.c_str();

	cout << "Enter student birth date:" << endl;
	string studentBirthDateTmp;
	cin.ignore();
	getline(cin, studentBirthDateTmp, '\n');
    const char* studentBirthDate = studentBirthDateTmp.c_str();

	cout << "Enter school number:" << endl;
	unsigned schoolNumber;
	cin >> schoolNumber;

	cout << "Enter form number:" << endl;
	string formNumberTmp;
	cin.ignore();
	getline(cin, formNumberTmp, '\n');
    const char* formNumber = formNumberTmp.c_str();

	/* exec sql begin declare section */
	    
	    
	    
	    
	    

	
#line 550 "main.pgc"
 const char * name = studentName ;
 
#line 551 "main.pgc"
 const char * address = studentAddr ;
 
#line 552 "main.pgc"
 const char * birthDate = studentBirthDate ;
 
#line 553 "main.pgc"
 const unsigned int schoolNum = schoolNumber ;
 
#line 554 "main.pgc"
 const char * formNum = formNumber ;
/* exec sql end declare section */
#line 556 "main.pgc"

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update student set address = $1  , birth_date = $2  , school_num = $3  , form_num = $4  where name = $5 ", 
	ECPGt_char,&(address),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(birthDate),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_unsigned_int,&(schoolNum),(long)1,(long)1,sizeof(unsigned int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(formNum),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(name),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 562 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 562 "main.pgc"


	{ ECPGtrans(__LINE__, NULL, "commit");
#line 564 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 564 "main.pgc"


	return;
}

void deleteStudent() {
	cout << "Enter student name: " << endl;
	string studentNameTmp;
	cin.ignore();
	getline(cin, studentNameTmp, '\n');
    const char* studentName = studentNameTmp.c_str();

    /* exec sql begin declare section */

	    

    
#line 578 "main.pgc"
 const char * name = studentName ;
/* exec sql end declare section */
#line 580 "main.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "delete from student where name = $1 ", 
	ECPGt_char,&(name),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 582 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 582 "main.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 584 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 584 "main.pgc"


    return;
}

void studentMenu() {
	while (true) {
		cout << "Student menu:" << endl;
		cout << "1. Add student" << endl;
		cout << "2. Get student info" << endl;
		cout << "3. Update student" << endl;
		cout << "4. Delete student" << endl;
		cout << "5. Show all students" << endl;
		cout << "0. Exit" << endl;
		int number;
		cin >> number;
		switch (number) {
			case 1: {
				addStudent();
				break;
			}
			case 2: {
				getStudentByName();
				break;
			}
			case 3: {
				updateStudent();
				break;
			}
			case 4: {
				deleteStudent();
				break;
			}
			case 5: {
				getAllStudents();
				break;
			}
			case 0: {
				return;
			}
			default: {
				cout << "Wrong number. Enter again" << endl;
				break;
			}
		}
	}
}

/* SUBJECTS MENU */

void getAllSubjects() {
	/* exec sql begin declare section */

	 
	 	
	 

	
#line 637 "main.pgc"
 char name [ 30 ] ;
 
#line 638 "main.pgc"
 char description [ 500 ] ;
 
#line 639 "main.pgc"
 char type [ 20 ] ;
/* exec sql end declare section */
#line 641 "main.pgc"


	/* declare cursor_subject cursor for select name , description , type_of_subject from subject order by name */
#line 645 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare cursor_subject cursor for select name , description , type_of_subject from subject order by name", ECPGt_EOIT, ECPGt_EORT);
#line 647 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 647 "main.pgc"


	while (true) {
		{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch cursor_subject", ECPGt_EOIT, 
	ECPGt_char,(name),(long)30,(long)1,(30)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(description),(long)500,(long)1,(500)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(type),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 651 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 651 "main.pgc"


		if (sqlca.sqlcode == ECPG_NOT_FOUND) {
			break;
		}

		cout << endl;
		cout << "Name: " << name << endl;
		cout << "Type of subject: " << type << endl;
		cout << "Description: " << description << endl;
		cout << endl;
	}

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close cursor_subject", ECPGt_EOIT, ECPGt_EORT);
#line 664 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 664 "main.pgc"


	return;
}

void getSubjectByName() {
	cout << "Enter subject name: " << endl;
	string subjectNameTmp;
	cin.ignore();
	getline(cin, subjectNameTmp, '\n');
    const char* subjectName = subjectNameTmp.c_str();

	/* exec sql begin declare section */

	    
	 
	 

	
#line 678 "main.pgc"
 const char * name = subjectName ;
 
#line 679 "main.pgc"
 char description [ 500 ] ;
 
#line 680 "main.pgc"
 char type [ 20 ] ;
/* exec sql end declare section */
#line 682 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select name , description , type_of_subject from subject where name = $1 ", 
	ECPGt_char,&(name),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,&(name),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(description),(long)500,(long)1,(500)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(type),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 687 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 687 "main.pgc"


	if (sqlca.sqlcode == ECPG_NOT_FOUND || strncmp(sqlca.sqlstate, "00", 2))
	{
		cout << "Not found" << endl;
		return;
	}
	cout << endl;
	cout << "Name: " << name << endl;
	cout << "Type of subject: " << type << endl;
	cout << "Description: " << description << endl;
	cout << endl;

	return;
}

string chooseSubjectType() {
	while (true) {
		cout << "Choose subject type: " << endl;
		cout << "1. Technical" << endl;
		cout << "2. Humanitarian" << endl;

		unsigned subjectTypeNum;
		cin >> subjectTypeNum;

		if (subjectTypeNum == 1) { return "technical"; }
		else if (subjectTypeNum == 2) {	return "humanitarian"; }
		else { 
			cout << "Wrong type: Choose again" << endl;
			continue;
	    }
	}	
}

void addSubject() {
	cout << "Enter subject name: " << endl;
	string subjectNameTmp;
	cin.ignore();
	getline(cin, subjectNameTmp, '\n');
    const char* subjectName = subjectNameTmp.c_str();
	
	const char* subjectType = chooseSubjectType().c_str();	

	cout << "Enter subject description:" << endl;
	string subjectDescriptionTmp;
	cin.ignore();
	getline(cin, subjectDescriptionTmp, '\n');
    const char* subjectDescription = subjectDescriptionTmp.c_str();
	
	/* exec sql begin declare section */

	    
	    
	    
	
	
#line 738 "main.pgc"
 const char * name = subjectName ;
 
#line 739 "main.pgc"
 const char * type = subjectType ;
 
#line 740 "main.pgc"
 const char * description = subjectDescription ;
/* exec sql end declare section */
#line 742 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into subject values ( $1  , $2  , $3  )", 
	ECPGt_char,&(name),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(description),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(type),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 745 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 745 "main.pgc"

	{ ECPGtrans(__LINE__, NULL, "commit");
#line 746 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 746 "main.pgc"


	return;
}

void updateSubject() {
	cout << "Enter subject name: " << endl;
	string subjectNameTmp;
	cin.ignore();
	getline(cin, subjectNameTmp, '\n');
    const char* subjectName = subjectNameTmp.c_str();
	
	const char* subjectType = chooseSubjectType().c_str();	

	cout << "Enter subject description:" << endl;
	string subjectDescriptionTmp;
	cin.ignore();
	getline(cin, subjectDescriptionTmp, '\n');
    const char* subjectDescription = subjectDescriptionTmp.c_str();

	/* exec sql begin declare section */

	    
	    
	    

	
#line 768 "main.pgc"
 const char * name = subjectName ;
 
#line 769 "main.pgc"
 const char * type = subjectType ;
 
#line 770 "main.pgc"
 const char * description = subjectDescription ;
/* exec sql end declare section */
#line 772 "main.pgc"


	cout << name << type << description << endl;

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update subject set type_of_subject = $1  , description = $2  where name = $3 ", 
	ECPGt_char,&(type),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(description),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(name),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 779 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 779 "main.pgc"

	
	{ ECPGtrans(__LINE__, NULL, "commit");
#line 781 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 781 "main.pgc"


	return;
}

void deleteSubject() {
	cout << "Enter subject name: " << endl;
	string subjectNameTmp;
	cin.ignore();
	getline(cin, subjectNameTmp, '\n');
    const char* subjectName = subjectNameTmp.c_str();

    /* exec sql begin declare section */

	    

    
#line 795 "main.pgc"
 const char * name = subjectName ;
/* exec sql end declare section */
#line 797 "main.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "delete from subject where name = $1 ", 
	ECPGt_char,&(name),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 799 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 799 "main.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 801 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 801 "main.pgc"


    return;
}

void subjectMenu() {
	while (true) {
		cout << "Subject menu:" << endl;
		cout << "1. Add subject" << endl;
		cout << "2. Get subject info" << endl;
		cout << "3. Update subject" << endl;
		cout << "4. Delete subject" << endl;
		cout << "5. Show all subjects" << endl;
		cout << "0. Exit" << endl;
		int number;
		cin >> number;
		switch (number) {
			case 1: {
				addSubject();
				break;
			}
			case 2: {
				getSubjectByName();
				break;
			}
			case 3: {
				updateSubject();
				break;
			}
			case 4: {
				deleteSubject();
				break;
			}
			case 5: {
				getAllSubjects();
				break;
			}
			case 0: {
				return;
			}
			default: {
				cout << "Wrong number. Enter again" << endl;
				break;
			}
		}
	}
}

/* PERFORMANCE INTERFACE */

void getAllPerformances() {
	/* exec sql begin declare section */

	 
	 
	 

	
#line 854 "main.pgc"
 char studentName [ 60 ] ;
 
#line 855 "main.pgc"
 char subjectName [ 30 ] ;
 
#line 856 "main.pgc"
 float avgMark ;
/* exec sql end declare section */
#line 858 "main.pgc"


	/* declare cursor_performance cursor for select student_name , subject_name , average_mark from student_performance order by student_name */
#line 862 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare cursor_performance cursor for select student_name , subject_name , average_mark from student_performance order by student_name", ECPGt_EOIT, ECPGt_EORT);
#line 864 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 864 "main.pgc"


	while (true) {
		{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch cursor_performance", ECPGt_EOIT, 
	ECPGt_char,(studentName),(long)60,(long)1,(60)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(subjectName),(long)30,(long)1,(30)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_float,&(avgMark),(long)1,(long)1,sizeof(float), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 868 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 868 "main.pgc"


		if (sqlca.sqlcode == ECPG_NOT_FOUND) {
			break;
		}

		cout << endl;
		cout << "Student name: " << studentName << endl;
		cout << "Subject name: " << subjectName << endl;
		cout << "Average mark: " << avgMark << endl;
		cout << endl;
	}

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close cursor_performance", ECPGt_EOIT, ECPGt_EORT);
#line 881 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 881 "main.pgc"


	return;
}

void getStudentPerformance() {
	cout << "Enter student name:" << endl;
	string nameTmp;
	cin.ignore();
	getline(cin, nameTmp, '\n');
    const char* name = nameTmp.c_str();

	/* exec sql begin declare section */

	    
	 
	 

	
#line 895 "main.pgc"
 const char * studentName = name ;
 
#line 896 "main.pgc"
 char subjectName [ 30 ] ;
 
#line 897 "main.pgc"
 float avgMark ;
/* exec sql end declare section */
#line 899 "main.pgc"


	ECPGset_var( 0, &( studentName ), __LINE__);\
 /* declare cursor_performance_of_student cursor for select subject_name , average_mark from student_performance where student_name = $1  order by subject_name */
#line 905 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare cursor_performance_of_student cursor for select subject_name , average_mark from student_performance where student_name = $1  order by subject_name", 
	ECPGt_char,&(studentName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 907 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 907 "main.pgc"

	
	cout << "Performance for student " << studentName << ":" << endl;
	while (true) {
		{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch cursor_performance_of_student", ECPGt_EOIT, 
	ECPGt_char,(subjectName),(long)30,(long)1,(30)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_float,&(avgMark),(long)1,(long)1,sizeof(float), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 912 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 912 "main.pgc"


		if (sqlca.sqlcode == ECPG_NOT_FOUND) {
			break;
		}

		cout << endl;
		cout << "Subject name: " << subjectName << endl;
		cout << "Average mark: " << avgMark << endl;
		cout << endl;
	}

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close cursor_performance_of_student", ECPGt_EOIT, ECPGt_EORT);
#line 924 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 924 "main.pgc"


	return;
}

void getSubjectPerformance() {
	cout << "Enter subject name:" << endl;
	string nameTmp;
	cin.ignore();
	getline(cin, nameTmp, '\n');
    const char* name = nameTmp.c_str();

	/* exec sql begin declare section */

	    
	 
	 

	
#line 938 "main.pgc"
 const char * subjectName = name ;
 
#line 939 "main.pgc"
 char studentName [ 30 ] ;
 
#line 940 "main.pgc"
 float avgMark ;
/* exec sql end declare section */
#line 942 "main.pgc"


	ECPGset_var( 1, &( subjectName ), __LINE__);\
 /* declare cursor_performance_for_subject cursor for select student_name , average_mark from student_performance where subject_name = $1  order by student_name */
#line 948 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare cursor_performance_for_subject cursor for select student_name , average_mark from student_performance where subject_name = $1  order by student_name", 
	ECPGt_char,&(subjectName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 950 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 950 "main.pgc"

	
	cout << "Performance for subject " << subjectName << ":" << endl;
	while (true) {
		{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch cursor_performance_for_subject", ECPGt_EOIT, 
	ECPGt_char,(studentName),(long)30,(long)1,(30)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_float,&(avgMark),(long)1,(long)1,sizeof(float), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 955 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 955 "main.pgc"


		if (sqlca.sqlcode == ECPG_NOT_FOUND) {
			break;
		}

		cout << endl;
		cout << "Student name: " << studentName << endl;
		cout << "Average mark: " << avgMark << endl;
		cout << endl;
	}

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close cursor_performance_for_subject", ECPGt_EOIT, ECPGt_EORT);
#line 967 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 967 "main.pgc"


	return;
}

void getStudentPerformanceForSubject() {
	cout << "Enter student name:" << endl;
	string studNameTmp;
	cin.ignore();
	getline(cin, studNameTmp, '\n');
    const char* studName = studNameTmp.c_str();

	cout << "Enter subject name:" << endl;
	string subjNameTmp;
	cin.ignore();
	getline(cin, subjNameTmp, '\n');
    const char* subjName = subjNameTmp.c_str();

	/* exec sql begin declare section */

	    
	    
	 

	
#line 987 "main.pgc"
 const char * studentName = studName ;
 
#line 988 "main.pgc"
 const char * subjectName = subjName ;
 
#line 989 "main.pgc"
 float avgMark ;
/* exec sql end declare section */
#line 991 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select student_name , subject_name , average_mark from student_performance where student_name = $1  and subject_name = $2 ", 
	ECPGt_char,&(studentName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(subjectName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,&(studentName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(subjectName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_float,&(avgMark),(long)1,(long)1,sizeof(float), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 996 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 996 "main.pgc"


	if (sqlca.sqlcode == ECPG_NOT_FOUND || strncmp(sqlca.sqlstate, "00", 2))
	{
		cout << "Not found" << endl;
		return;
	}
	cout << endl;
	cout << "Student name: " << studentName << endl;
	cout << "Subject name: " << subjectName << endl;
	cout << "Average mark: " << avgMark << endl;
	cout << endl;

	return;
}

void addPerformance() {
	cout << "Enter student name:" << endl;
	string studNameTmp;
	cin.ignore();
	getline(cin, studNameTmp, '\n');
    const char* studName = studNameTmp.c_str();

	cout << "Enter subject name:" << endl;
	string subjNameTmp;
	getline(cin, subjNameTmp, '\n');
    const char* subjName = subjNameTmp.c_str();

	cout << "Enter average mark:";
	float mark;
	cin >> mark;

	cout << studName << ' ' << subjName << ' ' << endl;
	
	/* exec sql begin declare section */

	    
	    
	    
	
	
#line 1032 "main.pgc"
 const char * studentName = studName ;
 
#line 1033 "main.pgc"
 const char * subjectName = subjName ;
 
#line 1034 "main.pgc"
 const float avgMark = mark ;
/* exec sql end declare section */
#line 1036 "main.pgc"


	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into student_performance values ( $1  , $2  , $3  )", 
	ECPGt_char,&(studentName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(subjectName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_float,&(avgMark),(long)1,(long)1,sizeof(float), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 1039 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 1039 "main.pgc"

	{ ECPGtrans(__LINE__, NULL, "commit");
#line 1040 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 1040 "main.pgc"


	return;
}

void updatePerformance() {
	cout << "Enter student name:" << endl;
	string studNameTmp;
	cin.ignore();
	getline(cin, studNameTmp, '\n');
    const char* studName = studNameTmp.c_str();

	cout << "Enter subject name:" << endl;
	string subjNameTmp;
	getline(cin, subjNameTmp, '\n');
    const char* subjName = subjNameTmp.c_str();

	cout << "Enter average mark:";
	float mark;
	cin >> mark;
	
	/* exec sql begin declare section */

	    
	    
	    
	
	
#line 1063 "main.pgc"
 const char * studentName = studName ;
 
#line 1064 "main.pgc"
 const char * subjectName = subjName ;
 
#line 1065 "main.pgc"
 const float avgMark = mark ;
/* exec sql end declare section */
#line 1067 "main.pgc"

	{ ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update student_performance set average_mark = $1  where student_name = $2  and subject_name = $3 ", 
	ECPGt_float,&(avgMark),(long)1,(long)1,sizeof(float), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(studentName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(subjectName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 1070 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 1070 "main.pgc"

	
	{ ECPGtrans(__LINE__, NULL, "commit");
#line 1072 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 1072 "main.pgc"


	return;
}

void deletePerformance() {
	cout << "Enter student name:" << endl;
	string studNameTmp;
	cin.ignore();
	getline(cin, studNameTmp, '\n');
    const char* studName = studNameTmp.c_str();

	cout << "Enter subject name:" << endl;
	string subjNameTmp;
	getline(cin, subjNameTmp, '\n');
    const char* subjName = subjNameTmp.c_str();

	/* exec sql begin declare section */

	    
	    

    
#line 1091 "main.pgc"
 const char * studentName = studName ;
 
#line 1092 "main.pgc"
 const char * subjectName = subjName ;
/* exec sql end declare section */
#line 1094 "main.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "delete from student_performance where student_name = $1  and subject_name = $2 ", 
	ECPGt_char,&(studentName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(subjectName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 1097 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 1097 "main.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 1099 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 1099 "main.pgc"


    return;
}

void deleteStudentPerformance () {
	cout << "Enter student name:" << endl;
	string studNameTmp;
	cin.ignore();
	getline(cin, studNameTmp, '\n');
    const char* studName = studNameTmp.c_str();

	/* exec sql begin declare section */

	    

    
#line 1113 "main.pgc"
 const char * studentName = studName ;
/* exec sql end declare section */
#line 1115 "main.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "delete from student_performance where student_name = $1 ", 
	ECPGt_char,&(studentName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 1118 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 1118 "main.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 1120 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 1120 "main.pgc"


    return;
}

void deleteSubjectPerformance () {
	cout << "Enter subject name:" << endl;
	string subjNameTmp;
	cin.ignore();
	getline(cin, subjNameTmp, '\n');
    const char* subjName = subjNameTmp.c_str();

	/* exec sql begin declare section */

	    

    
#line 1134 "main.pgc"
 const char * subjectName = subjName ;
/* exec sql end declare section */
#line 1136 "main.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "delete from student_performance where subject_name = $1 ", 
	ECPGt_char,&(subjectName),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 1139 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 1139 "main.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 1141 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 1141 "main.pgc"


    return;
}

void performanceMenu() {
	while (true) {
		cout << "Performance menu:" << endl;
		cout << "1. Add performance" << endl;
		cout << "2. Get performance info for student" << endl;
		cout << "3. Get performance info for subject" << endl;
		cout << "4. Get performance info for subject and student" << endl;
		cout << "5. Update performance" << endl;
		cout << "6. Delete performance for student" << endl;
		cout << "7. Delete performance for subject" << endl;
		cout << "8. Delete performance for subject and student" << endl;
		cout << "9. Show all performances" << endl;
		cout << "0. Exit" << endl;
		int number;
		cin >> number;
		switch (number) {
			case 1: {
				addPerformance();
				break;
			}
			case 2: {
				getStudentPerformance();
				break;
			}
			case 3: {
				getSubjectPerformance();
				break;
			}
			case 4: {
				getStudentPerformanceForSubject();
				break;
			}
			case 5: {
				updatePerformance();
				break;
			}
			case 6: {
				deleteStudentPerformance();
				break;
			}
			case 7: {
				deleteSubjectPerformance();
				break;
			}
			case 8: {
				deletePerformance();
				break;
			}
			case 9: {
				getAllPerformances();
				break;
			}
			case 0: {
				return;
			}
			default: {
				cout << "Wrong number. Enter again" << endl;
				break;
			}
		}
	}
}

/* MAIN MENU */

void menu() {
	while (true) {
		cout << "Menu:" << endl;
		cout << "1. Schools" << endl;
		cout << "2. Forms" << endl;
		cout << "3. Students" << endl;
		cout << "4. Subjects" << endl;
		cout << "5. Performance" << endl;
        cout << "6. Events (CRUD-interface is not implemented)" << endl;
        cout << "7. Participation (CRUD-interface is not implemented)" << endl;
		cout << "0. Exit" << endl;
		int number;
		cin >> number;
		switch (number) {
			case 1: {
				schoolMenu();
				break;
			}
			case 2: {
				formMenu();
				break;
			}
			case 3: {
				studentMenu();
				break;
			}
			case 4: {
				subjectMenu();
				break;
			}
		    case 5: {
				performanceMenu();
				break;
			}
			case 0: {
				return;
			}
			default: {
				cout << "Wrong number. Enter again" << endl;
				break;
			}
		}
	}
	return;
}

int main() {
    connectToDatabase("localhost:5432", "postgres", "postgres", "superuser");

    menu();

    return 0;
}