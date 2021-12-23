create database lab4;
use lab4;

create table customer(
			NAME char(30) primary key not null,
            ADDRESS char(30) not null,
            STATE char(3) not null,
            ZIP int not null,
            PHONE char(15) not null,
            REMARKS char(15) not null );

create table part( 
			partnum int primary key not null,
            description char(30) not null,
            price double not null);
            
create table orders(
			orderedon char(30) not null,
            name char(30) not null,
            partnum int not null,
            quantity int not null,
            remarks char(15) not null,
            primary key (orderedon, name, partnum)
					);

insert into customer values ("TRUE WHEEL","550 HUSKER","NE",58702,"555-4545","NONE");
insert into customer values ("BIKE SPEC","CPT SHRIVE","LA",45678,"555-1234","NONE");
insert into customer values ("LE SHOPPE","HOMETOWN","KS",54678,"555-1278","NONE");
insert into customer values ("AAA BIKE","10 OLDTOWN","NE",56784,"555-3421","JOHN-MGR");
insert into customer values ("JACKS BIKE","24 EGLIN","FL",34567,"555-2314","NONE");

insert into part values (54,"PEDALS", 54.25);
insert into part values (42, "SEATS", 24.50);
insert into part values (46, "TIRES", 15.25);
insert into part values (23, "MOUNTAIN BIKE", 350.45);
insert into part values (76, "ROAD BIKE", 530.00);
insert into part values (10, "TANDEM", 1200.00);

insert into orders values ("15-MAY-1996","TRUE WHEEL",23,6,"PAID");
insert into orders values ("19-MAY-1996","TRUE WHEEL",76,3,"PAID");
insert into orders values ("2-SEP-1996","TRUE WHEEL",10,1,"PAID");
insert into orders values ("30-JUN-1996","TRUE WHEEL",42,8,"PAID");
insert into orders values ("30-JUN-1996","BIKE SPEC",54,10,"PAID");
insert into orders values ("30-MAY-1996","BIKE SPEC",10,2,"PAID");
insert into orders values ("30-MAY-1996","BIKE SPEC",23,8,"PAID");
insert into orders values ("17-JAN-1996","BIKE SPEC",76,11,"PAID");
insert into orders values ("17-JAN-1996","LE SHOPPE",76,5,"PAID");
insert into orders values ("1-JUN-1996","LE SHOPPE",10,3,"PAID");
insert into orders values ("1-JUN-1996","AAA BIKE",10,1,"PAID");
insert into orders values ("1-JUL-1996","AAA BIKE",76,4,"PAID");
insert into orders values ("1-JUL-1996","AAA BIKE",46,14,"PAID");
insert into orders values ("11-JUL-1996","JACKS BIKE",76,14,"PAID");

#1. Write the query that finds the total amount of money earned.
select sum(orders.quantity * part.price) as totalAmount
from part, orders
where part.partnum = orders.partnum;

#2. Write the query that finds the amount of sale to each customer.
select orders.name ,sum(orders.quantity * part.price) as salePerCustomer
from part, orders
where part.partnum = orders.partnum
group by orders.name;

#3. Write the query that finds the number of parts (for each type)
select part.description, sum(orders.quantity) as numOfParts
from part, orders
where part.partnum = orders.partnum
group by part.description;

#4. Write the query that finds how much money has been earned by selling mountain bikes.
select sum(orders.quantity * part.price) as totalMountainBike
from orders, part
where part.partnum = orders.partnum
AND part.description = 'MOUNTAIN BIKE';

#5th question
select customer.name, customer.address, price*quantity as total, part.description
from customer, orders, part
where part.partnum = orders.partnum and customer.name = orders.name
group by total
order by customer.name; 

#6th question
update orders 
set orders.orderedon = '2-SEP-96'
where orders.partnum = 10 and orders.name = 'TRUE WHEEL';

select orders.orderedon, orders.name, part.partnum, orders.quantity
from customer, part, orders
where part.partnum = orders.partnum and orders.orderedon like '%SEP%'
group by orders.orderedon;
