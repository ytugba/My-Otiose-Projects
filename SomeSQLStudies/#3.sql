create database lab3;
use lab3;

create table CLASS(
				sid int primary key not null,
                sname char(30) not null,
                gpa double not null,
                age int not null
				);

insert into CLASS values (17, "Ali K.", 3.56, 21);
insert into CLASS values (11, "Mehmet S.", 2.12, 18);
insert into CLASS values (25, "Ayhan D.", 1.78, 17);
insert into CLASS values (27, "Fatma B.", 2.45, 17);
insert into CLASS values (68, "Fulya K", 2.67, 19);
insert into CLASS values (62, "Ahmet T.", 3.03, 20);
insert into CLASS values (42, "Yasemin K.", 3.48, 22);
insert into CLASS values (45, "Nilufer C.", 3.12, 18);
insert into CLASS values (28, "Mehmet R.", 2.89, 23);
insert into CLASS values (36, "Mustafa D.", 1.56, 18);

select * from CLASS;

#Find the names and ages of all the students.
select sname, age from CLASS;

#Find the students (names and ids) who have GPA above 3.00.
select sname, sid 
from CLASS 
where gpa > 3.00;

#Find the average of GPAs of students who have GPA above 2.50.
select avg(gpa) as AverageGPA
from CLASS
where gpa > 2.50;

#Find the maximum age.
select max(age) as maxAge 
from CLASS;

#Find the average of student’s ages whose name start with the letter ‘M’.
select avg(age) as avgAge
from CLASS
where sname like 'M%';

#Display all the information sorted on age with descending order.
select * 
from CLASS 
order by age desc;

#Turn all letters of name Mustafa D. into uppercase letters.
#only on display screen
select upper(sname)
from CLASS
where sname = 'Mustafa D.';

#Turn all letters of name Yasemin K. into lowercase letters.
#only on display screen
select lower(sname)
from CLASS
where sname = 'Yasemin K.';

#Find average of ages and average of GPAs.
select avg(age) as avgAge, avg(gpa) as avgGpa
from CLASS;

#Replace Mehmet R. with M. R.
update CLASS
set sname = 'M. R.'
where sid = 28;

select * from CLASS;

#update
UPDATE CLASS
SET sname = 'MUSTAFA D.'
WHERE sid = 36;

select * from CLASS;