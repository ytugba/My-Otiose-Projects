use lab5;

#No duplicates should be printed in any of the answers.

#1. Find the names of all juniors who are enrolled in a class taught by faculty 
#with the id of 45.

select student.sname
from student, class, enrolled
where student.snum = enrolled.snum and class.fid = 45 and student.level = 'Junior'
group by student.sname;


#2. Find the age of the oldest student who is either a History major or enrolled
# in a course taught by faculty with the id of 45.
select student.sname, MAX(student.age) as MaxAge
from student, class, enrolled
where student.major = 'History' or class.fid = 45 
and enrolled.snum = student.snum and enrolled.cname = class.name;

select max(age)
from student as s
where
(s.snum in (select distinct s1.snum from student as s1 where
major='History'))
OR
(s.snum in (select distinct s2.snum from student as s2, class, enrolled as e2
where s2.snum=e2.snum and cname=name and fid=45));

#3. Find the names of all classes that either meet in room R128 or have three or
# more students enrolled.
select distinct Class.name 
from class, enrolled, student
where room = 'R128' or 
(class.name in (select enrolled.cname 
				from enrolled 
                group by enrolled.cname 
                having count(*)>=3)); 
select distinct c.name
from class as c
where
(c.name in (select distinct c1.name from class as c1 where room='R128'))
OR
(c.name in (select e2.cname from enrolled as e2 group by e2.cname 
having count(*)>=3));

#4. Find the names of all students who are enrolled in two classes that meet at 
#the same time.
select distinct s.sname from class as c, enrolled as e, student as s
where c.name in (select distinct c1.name from class as c1, class as c2
where c1.name!=c2.name and c1.meetsat=c2.meetsat) and
c.name=e.cname and s.snum=e.snum;

#5. Find the names of faculty members who teach in every room in which some class 
#is taught.
select f1.fname 
from faculty as f1 
where not exists (
					select * 
                    from class as c
					where c.room not in (
											select c1.room
                                            from class as c1
                                            where c1.fid=f1.fid));

#6. Find the names of faculty members for whom the combined enrollment of the 
#courses that they teach is less than five.
select f.fname, count(*) 
from faculty as f, class as c, enrolled as e 
where
e.cname=c.name and f.fid=c.fid 
group by f.fname 
having count(*)<5;

#7. For each level, print the level and the average age of students for that level.
select level, avg(age)
from student
group by level;


#8. For all levels except juniors, print the level and the average age of students 
#for that level.
select level, avg(age) 
from student 
where level != 'junior' 
group by level;