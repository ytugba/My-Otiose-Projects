#create database
create database lab2;
use lab2;

#create table
create table CHECKS(
					check_id int primary key not null,
                    payee char(30) not null,
                    amount double not null,
                    remarks char(30) not null
					);

#insert values
insert into CHECKS values (1, "Migros", 270.12, "Groceries");
insert into CHECKS values (2, "Petrol Ofisi", 105.00, "Gas (For Car)");
insert into CHECKS values (3, "TCDD", 25.00, "Train to Konya");
insert into CHECKS values (4, "Turkcell", 528.00, "Cellular Phone");
insert into CHECKS values (5, "Baskent Elektrik", 113.78, "Electricity Bill");
insert into CHECKS values (6, "Ayakkabi Dunyasi", 175.00, "Shoes");
insert into CHECKS values (7, "Migros", 315.90, "Groceries");
insert into CHECKS values (8, "Grupama Sigorta", 365.43, "Car Insurance");

#display whole table
select * from CHECKS;

#1. Write a query that returns all checks (CHECK_ID, PAYEE, and AMOUNT)
#in the database in which PAYEE begins with M or P.

select check_id, payee, amount
from CHECKS 
where payee like 'M%' OR payee like 'P%';

#2. Write a query that returns all checks (CHECK_ID, PAYEE, and AMOUNT)
#that is related to Car expenses.#

select check_id, payee, amount
from CHECKS 
where remarks like '%Car%';

#3. Write a query that returns all PAYEEs in which the check AMOUNT is greater
#than 200.00. Only one instance of duplicate data is shown.

select payee 
from CHECKS
where amount > 200.00
group by payee;

#4. Write a query that returns all the checks with the decreasing order of the
#check AMOUNT.

select *
from CHECKS
order by amount desc;

#5. Write a query that returns all the checks (CHECK_ID, PAYEE, and AMOUNT)
#that is related to Shoes or Groceries expenses.

select check_id, payee, amount 
from checks
where remarks like '%Shoes%' or remarks like '%Groceries%';