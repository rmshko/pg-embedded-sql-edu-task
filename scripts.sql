CREATE DOMAIN num_type smallint CHECK (VALUE > 0);
CREATE DOMAIN form_number_type char(4) NOT NULL;
CREATE DOMAIN avg_mark_type numeric(3, 2) CHECK (VALUE >= 2 AND VALUE <= 5);
CREATE TYPE event_type AS ENUM('olympiad', 'club', 'disco');
CREATE TYPE subject_type AS ENUM('humanitarian', 'technical');

CREATE TABLE school(
	num num_type,
	address varchar(100) NOT NULL,
	PRIMARY KEY(num)
);

CREATE TABLE form(
	num form_number_type,
	school_number num_type,
	number_of_students num_type NOT NULL,
	form_master_name varchar(60) NOT NULL,
	PRIMARY KEY (num, school_num),
	FOREIGN KEY (school_number) REFERENCES school(num)	
);

CREATE TABLE student(
	name varchar(60),
	address varchar(100) NOT NULL,
	birth_date date NOT NULL,
	school_num num_type,
	form_num form_number_type,
	PRIMARY KEY (name),
	FOREIGN KEY (school_num, form_num) REFERENCES form(school_num, num)
);

CREATE TABLE event(
	name varchar(30),
	type_of_event event_type NOT NULL,
	description varchar(500),
	PRIMARY KEY (name)
);

CREATE TABLE participation(
	student_name varchar(60),
	event_name varchar(30),
	participation_info varchar(500),
	PRIMARY KEY (student_name, event_name),
	FOREIGN KEY (student_name) REFERENCES student(name),
	FOREIGN KEY (event_name) REFERENCES event(name)
);

CREATE TABLE subject(
	name varchar(30),
	description varchar(500),
	type_of_subject subject_type,
	PRIMARY KEY(name)
);

CREATE TABLE student_performance (
	student_name varchar(60),
	subject_name varchar(30),
	average_mark avg_mark_type,
	PRIMARY KEY (student_name, subject_name),
	FOREIGN KEY (student_name) REFERENCES student(name),
	FOREIGN KEY (subject_name) REFERENCES subject(name)
);

INSERT INTO school(num, address) 
	VALUES (10, 'City, street_1, 1'), (12, 'City, another street, 5'), (20, 'City, streetN, 14');

INSERT INTO form(num, school_num, number_of_students, form_master_name)
	VALUES ('10-1', 10, 20, 'Smirnov A.B.'), ('11-3', 10, 25, 'Ivanov A.A.'), ('9-2', 20, 17, 'Borisov D.S.');

INSERT INTO student(name, address, birth_date, school_num, form_num)
	VALUES ('Andreev U.N.', 'unknown street1, house1, 5', '2002-01-01', 10, '11-3'), 
		('Nikolaev A.S.', 'unknown street2, house2, 10', '2004-10-10', 20, '9-2');

INSERT INTO event(name, type_of_event, description) 
	VALUES ('Mudrenok', 'olympiad', 'Mathematical olympiad');

INSERT INTO participation(student_name, event_name, participation_info)
	VALUES ('Andreev U.N.', 'Mudrenok', 'Won the olympiad');

INSERT INTO subject(name, description, type_of_subject)
	VALUES ('Math', 'Math description', 'technical');

INSERT INTO student_performance(student_name, subject_name, average_mark)
	VALUES ('Andreev U.N.', 'Math', 4.75);