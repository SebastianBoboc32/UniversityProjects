
create table Sports(
	sportId INT PRIMARY KEY,
	SportName VARCHAR(20),
	
);

create table Teams(
	teamId INT PRIMARY KEY,
	teamName VARCHAR(100),
	sportId INT references Sports(sportId),
);

create table Users(
	userId INT PRIMARY KEY,
	username VARCHAR(50),
	email VARCHAR(100),
	balance INT
);


create table Transactions(
	transactionId INT PRIMARY KEY,
	userId INT references Users(userId)
	ON DELETE SET NULL,
	amount int,
	transactionType VARCHAR(10),
	transactionTime date
);

create table Evenimente(
	eventId INT PRIMARY KEY,
	eventName VARCHAR(100),
	dateandtime date,
	sportId INT references Sports(sportId)
	
);

create table BetTypes(
	betTypeId INT PRIMARY KEY,
	betTypeName VARCHAR(100),
);


create table UserActivities(
	activityId INT PRIMARY KEY,
	userId INT references Users(userId)
	ON DELETE SET NULL,
	activityType varchar(100),
	activityTime DATE,
);


create table Bets(
	betId INT PRIMARY KEY,
	eventId INT references Evenimente(eventId),
	betTypeId INT references BetTypes(betTypeId),
	dateandtime DATE,
);

create table BetSelections(
	userIdbetId INT PRIMARY KEY,
	betId INT references Bets(betId)
	ON DELETE CASCADE,
	userId INT references Users(userId)
	ON DELETE CASCADE,
	outcome varchar(5),
	amount INT,
);

create table BetPreferences(
	userIdbetTypeId INT NOT null,
	userId INT references Users(userId),
	betTypeId INT,
	betTypeName VARCHAR(100),
	username VARCHAR(50),
);


create table Results(
	resultId INT PRIMARY KEY,
	eventId INT references Evenimente(eventId),
	teamId INT references Teams(teamId),
	dateAndTime DATE,
);



INSERT INTO Sports(sportId,SportName) VALUES (1,'football');
INSERT INTO Sports(sportId,SportName) VALUES (2,'basketball');
INSERT INTO Sports(sportId,SportName) VALUES (3,'e-sports');
INSERT INTO Sports(sportId,SportName) VALUES (4,'formula 1');
INSERT INTO Sports(sportId, SportName) VALUES (5, 'tennis');
INSERT INTO Sports(sportId, SportName) VALUES (6, 'cricket');
INSERT INTO Sports(sportId, SportName) VALUES (7, 'volleyball');


INSERT INTO Teams(teamId,teamName,sportId) VALUES (3,'real madrid',1);
INSERT INTO Teams(teamId,teamName,sportId) VALUES (17,'ac milan',1);
INSERT INTO Teams(teamId,teamName,sportId) VALUES (44,'LA Lakers',2);
INSERT INTO Teams(teamId,teamName,sportId) VALUES (23,'chicago bulls',2);
INSERT INTO Teams(teamId,teamName,sportId) VALUES (12,'G2 Esports',3);
INSERT INTO Teams(teamId,teamName,sportId) VALUES (33,'Furia Gaming',3);
INSERT INTO Teams(teamId,teamName,sportId) VALUES (91,'Red Bull',4);
INSERT INTO Teams(teamId,teamName,sportId) VALUES (88,'Ferrari',4);
INSERT INTO Teams(teamId, teamName, sportId) VALUES (77, 'Wimbledon Winners', 5);
iNSERT INTO Teams(teamId, teamName, sportId) VALUES (12, 'Mumbai Indians', 6);
INSERT INTO Teams(teamId, teamName, sportId) VALUES (22, 'Brazil National Team', 7);
INSERT INTO Teams(teamId, teamName, sportId) VALUES (13, 'Mumbai Indians', 2);
INSERT INTO Teams(teamId, teamName, sportId) VALUES (14, 'Brazil National Team', 3);
INSERT INTO Teams(teamId, teamName, sportId) VALUES (62, 'Mumbai Indians', 1);
INSERT INTO Teams(teamId, teamName, sportId) VALUES (92, 'Brazil National Team', 4);
INSERT INTO Teams(teamId, teamName, sportId) VALUES (10, 'Mumbai Indians', 3);
INSERT INTO Teams(teamId, teamName, sportId) VALUES (222, 'Brazil National Team', 1);



INSERT INTO Transactions(transactionId,userId,amount,transactionType,transactionTime) VALUES (44,756,1000,'withdrawal','2023-09-26');
INSERT INTO Transactions(transactionId,userId,amount,transactionType,transactionTime) VALUES (46,333,200,'deposit','2023-10-04');
INSERT INTO Transactions(transactionId,userId,amount,transactionType,transactionTime) VALUES (31,404,150,'withdrawal','2023-08-31');
INSERT INTO Transactions(transactionId,userId,amount,transactionType,transactionTime) VALUES (90,901,300,'withdrawal','2023-10-01');
INSERT INTO Transactions(transactionId,userId,amount,transactionType,transactionTime) VALUES (2,731,2000,'deposit','2023-09-22');
INSERT INTO Transactions(transactionId, userId, amount, transactionType, transactionTime) VALUES (75, 731, 500, 'deposit', '2023-10-15');
INSERT INTO Transactions(transactionId, userId, amount, transactionType, transactionTime) VALUES (103, 404, 300, 'withdrawal', '2023-10-20');
INSERT INTO Transactions(transactionId, userId, amount, transactionType, transactionTime) VALUES (120, 756, 800, 'deposit', '2023-10-25');
INSERT INTO Transactions(transactionId, userId, amount, transactionType, transactionTime) VALUES (50, 901, 150, 'withdrawal', '2023-10-28');
INSERT INTO Transactions(transactionId, userId, amount, transactionType, transactionTime) VALUES (88, 731, 1000, 'deposit', '2023-11-02');


UPDATE Transactions
SET amount = 0,transactionType = 'expired'
WHERE transactionTime < GETDATE()



INSERT INTO Evenimente(eventId,eventName,dateandtime,sportId) VALUES (616,'Real Madrid vs Ac Milan','2023-10-11',1);
INSERT INTO Evenimente(eventId,eventName,dateandtime,sportId) VALUES (646,'LA Lakers vs Chicago Bulls','2023-10-07',2);
INSERT INTO Evenimente(eventId,eventName,dateandtime,sportId) VALUES (700,'Furia Gaming vs G2 Esports','2023-10-30',3);
INSERT INTO Evenimente(eventId,eventName,dateandtime,sportId) VALUES (84,'Hunagaroring','2023-10-01',4);
INSERT INTO Evenimente(eventId,eventName,dateandtime,sportId) VALUES (655,'Ac Milan  vs Real Madrid','2023-12-14',1);
INSERT INTO Evenimente(eventId,eventName,dateandtime,sportId) VALUES (64,'Chicago Bulls vs LA Lakers','2023-11-07',2);
INSERT INTO Evenimente(eventId,eventName,dateandtime,sportId) VALUES (707,'G2 Esports vs Furia Gaming','2024-04-03',3);
INSERT INTO Evenimente(eventId,eventName,dateandtime,sportId) VALUES (403,'Red Bull Ring','2023-12-01',4);
INSERT INTO Evenimente(eventId, eventName, dateandtime, sportId) VALUES (800, 'Wimbledon Finals', '2023-11-15', 5);
INSERT INTO Evenimente(eventId, eventName, dateandtime, sportId) VALUES (900, 'IPL Final', '2023-11-10', 6);
INSERT INTO Evenimente(eventId, eventName, dateandtime, sportId) VALUES (1000, 'Volleyball World Cup', '2023-12-01', 7);


UPDATE Evenimente
SET eventName = 'event finished'
WHERE dateandtime < GETDATE()

INSERT INTO BetTypes(betTypeId,betTypeName) VALUES (1,'Team 1 wins');
INSERT INTO BetTypes(betTypeId,betTypeName) VALUES (2,'Team 2 wins');
INSERT INTO BetTypes(betTypeId,betTypeName) VALUES (3,'Draw');
INSERT INTO BetTypes(betTypeId, betTypeName) VALUES (4, 'Total Goals Over 2.5');
INSERT INTO BetTypes(betTypeId, betTypeName) VALUES (5, 'Total Corner Kicks Under 6.5');
INSERT INTO BetTypes(betTypeId, betTypeName) VALUES (6, 'Set Winner');


INSERT INTO Bets(betId,eventId,betTypeId,dateandtime) VALUES(707,616,1,'2023-10-08');
INSERT INTO Bets(betId,eventId,betTypeId,dateandtime) VALUES(455,700,3,'2023-10-07');
INSERT INTO Bets(betId,eventId,betTypeId,dateandtime) VALUES(104,84,3,'2023-10-07');
INSERT INTO Bets(betId,eventId,betTypeId,dateandtime) VALUES(33,646,2,'2023-09-08');
INSERT INTO Bets(betId,eventId,betTypeId,dateandtime) VALUES(9,646,2,'2023-09-30');
INSERT INTO Bets(betId,eventId,betTypeId,dateandtime) VALUES(555,616,1,'2023-10-04');
INSERT INTO Bets(betId,eventId,betTypeId,dateandtime) VALUES(601,84,2,'2023-10-04');
INSERT INTO Bets(betId,eventId,betTypeId,dateandtime) VALUES(100,700,2,'2023-09-03');
INSERT INTO Bets(betId,eventId,betTypeId,dateandtime) VALUES(22,616,3,'2023-12-31');
INSERT INTO Bets(betId,eventId,betTypeId,dateandtime) VALUES(292,84,3,'2023-09-18');
INSERT INTO Bets(betId, eventId, betTypeId, dateandtime) VALUES (200, 800, 4, '2023-11-12');
INSERT INTO Bets(betId, eventId, betTypeId, dateandtime) VALUES (250, 900, 5, '2023-11-08');
INSERT INTO Bets(betId, eventId, betTypeId, dateandtime) VALUES (300, 1000, 6, '2023-11-25');
INSERT INTO Bets(betId, eventId, betTypeId, dateandtime) VALUES (300, 1000, 6, '2023-11-25');


DELETE FROM Bets WHERE betTypeId = 3 OR dateandtime < GETDATE()


INSERT INTO Users(userId,username,email,balance) VALUES (756,'sebastianB','sebastianboboc@gmail.com',400);
INSERT INTO Users(userId,username,email,balance) VALUES (731,'madalinC','madalin@regele.com',796);
INSERT INTO Users(userId,username,email,balance) VALUES (333,'andreim','andreimkt@gmail.com',800);
INSERT INTO Users(userId,username,email,balance) VALUES (404,'gbrl34','gabiharghita@gmail.com',5110);
INSERT INTO Users(userId,username,email,balance) VALUES (901,'bicadorul','dorubica@gmail.com',120);
INSERT INTO Users(userId, username, email, balance) VALUES (555, 'tennisFan', 'tennislover@gmail.com', 350);
INSERT INTO Users(userId, username, email, balance) VALUES (888, 'cricketKing', 'cricketking@live.com', 700);
INSERT INTO Users(userId, username, email, balance) VALUES (999, 'volleyballPro', 'vballpro@yahoo.com', 450);
INSERT INTO Users(userId)Values (902)
INSERT INTO Users(userId)Values (904)

INSERT INTO BetSelections(userIdbetId,betId,userId,outcome,amount) VALUES(756707,707,756,'win',400);
INSERT INTO BetSelections(userIdbetId,betId,userId,outcome,amount) VALUES(756292,292,756,'draw',1350);
INSERT INTO BetSelections(userIdbetId,betId,userId,outcome,amount) VALUES(73122,22,731,'win',30);
INSERT INTO BetSelections(userIdbetId,betId,userId,outcome,amount) VALUES(9019,9,901,'lose',55);
INSERT INTO BetSelections(userIdbetId,betId,userId,outcome,amount) VALUES(90133,33,901,'lose',88);
INSERT INTO BetSelections(userIdbetId,betId,userId,outcome,amount) VALUES(756555,555,756,'win',300);
INSERT INTO BetSelections(userIdbetId,betId,userId,outcome,amount) VALUES(73133,33,731,'win',4000);
INSERT INTO BetSelections(userIdbetId,betId,userId,outcome,amount) VALUES(40433,33,404,'lose',700);
INSERT INTO BetSelections(userIdbetId,betId,userId,outcome,amount) VALUES(404601,601,404,'draw',50);
INSERT INTO BetSelections(userIdbetId,betId,userId,outcome,amount) VALUES(90122,22,901,'draw',960);

UPDATE BetSelections
SET amount = 0
WHERE outcome = 'lose'

INSERT INTO UserActivities(activityId,userId,activityType,activityTime) VALUES(1,756,'bet placed','2023-10-08');
INSERT INTO UserActivities(activityId,userId,activityType,activityTime) VALUES(2,756,'cashed out','2023-10-09');
INSERT INTO UserActivities(activityId,userId,activityType,activityTime) VALUES(3,731,'created a new bet','2023-09-30');
INSERT INTO UserActivities(activityId,userId,activityType,activityTime) VALUES(7,731,'bet placed','2023-09-30');
INSERT INTO UserActivities(activityId,userId,activityType,activityTime) VALUES(8,901,'cashed out','2023-10-04');
INSERT INTO UserActivities(activityId,userId,activityType,activityTime) VALUES(4,404,'created a new bet','2023-10-04');
INSERT INTO UserActivities(activityId, userId, activityType, activityTime) VALUES (5, 555, 'bet placed', '2023-11-14');
INSERT INTO UserActivities(activityId, userId, activityType, activityTime) VALUES (6, 555, 'cashed out', '2023-11-15');
INSERT INTO UserActivities(activityId, userId, activityType, activityTime) VALUES (9, 888, 'created a new bet', '2023-11-10');
INSERT INTO UserActivities(activityId, userId, activityType, activityTime) VALUES (10, 888, 'bet placed', '2023-11-10');
INSERT INTO UserActivities(activityId, userId, activityType, activityTime) VALUES (11, 999, 'cashed out', '2023-12-02');


DELETE FROM UserActivities WHERE NOT (userId is NOT NULL)

INSERT INTO Results(resultId,eventId,teamId,dateAndTime) VALUES(31,616,3,'2023-10-11');
INSERT INTO Results(resultId,eventId,teamId,dateAndTime) VALUES(50,700,12,'2023-10-30'),(44,646,44,'2023-10-07');
INSERT INTO Results(resultId,eventId,teamId,dateAndTime) VALUES(29,84,91,'2023-10-01');
INSERT INTO Results(resultId, eventId, teamId, dateAndTime) VALUES (60, 800, 77, '2023-11-15');
INSERT INTO Results(resultId, eventId, teamId, dateAndTime) VALUES (70, 900, 12, '2023-11-10');
INSERT INTO Results(resultId, eventId, teamId, dateAndTime) VALUES (80, 1000, 33, '2023-12-01');


INSERT INTO BetPreferences(userIdbetTypeId,userId, betTypeId, betTypeName, username) VALUES (7561,756, 1, 'Team 1 wins', 'sebastianB');
INSERT INTO BetPreferences(userIdbetTypeId,userId, betTypeId, betTypeName, username) VALUES (7312,731, 2, 'Team 2 wins', 'madalinC');
INSERT INTO BetPreferences(userIdbetTypeId,userId, betTypeId, betTypeName, username) VALUES (3333,333, 3, 'Draw', 'andreim');
INSERT INTO BetPreferences(userIdbetTypeId,userId, betTypeId, betTypeName, username) VALUES (4044,404, 4, 'Total Goals Over 2.5', 'gbrl34');
INSERT INTO BetPreferences(userIdbetTypeId,userId, betTypeId, betTypeName, username) VALUES (9015,901, 5, 'Total Corner Kicks Under 6.5', 'bicadorul');
INSERT INTO BetPreferences(userIdbetTypeId,userId, betTypeId, betTypeName, username) VALUES (5556,555, 6, 'Set Winner', 'tennisFan');
INSERT INTO BetPreferences(userIdbetTypeId,userId, betTypeId, betTypeName, username) VALUES (8881,888, 1, 'Team 1 wins', 'cricketKing');
INSERT INTO BetPreferences(userIdbetTypeId,userId, betTypeId, betTypeName, username) VALUES (9992,999, 2, 'Team 2 wins', 'volleyballPro');


INSERT INTO BetSelections(userIdbetId, betId, userId, outcome, amount) VALUES (555200, 200, 555, 'win', 450);
INSERT INTO BetSelections(userIdbetId, betId, userId, outcome, amount) VALUES (731250, 250, 731, 'lose', 200);
INSERT INTO BetSelections(userIdbetId, betId, userId, outcome, amount) VALUES (888300, 300, 888, 'win', 800);

DELETE FROM BetSelections WHERE outcome like 'w%'


SELECT * FROM Users;
SELECT * FROM Sports;
SELECT * FROM Teams;
SELECT * FROM Evenimente;
SELECT * FROM Transactions;
SELECT * FROM BetTypes;
SELECT * FROM Bets;
SELECT * FROM UserActivities;
SELECT * FROM BetSelections;
SELECT * FROM Results;
SELECT * FROM BetPreferences;


--a)UNION with OR ->all users with id <500 or id >900
SELECT * FROM Users
WHERE userId < 50*10
UNION
SELECT* From Users
WHERE userId >9*10*10

--a)UNION ALL -> all bets that have "win" as the outcome or being place by user:731
SELECT * from BetSelections
WHERE outcome = 'win'
UNION ALL
SELECT * from BetSelections
WHERE userId = 73*10+1


--b) INTERESCT -> organizations that have teams in sports 1 & 3
SELECT teamName
FROM Teams
WHERE sportId = 1
INTERSECT
SELECT teamName
FROM Teams
WHERE sportId = 3;

--b)IN -> organizations that have teams in sports 1 & 3
SELECT teamName
FROM Teams
WHERE sportId = 1
AND teamName IN (
    SELECT teamName
    FROM Teams
    WHERE sportId = 3
);


--c)EXCEPT -> organizations that have teams in sport 1 but not in sport 3
SELECT teamName
FROM Teams
WHERE sportId = 1
EXCEPT
SELECT teamName
FROM Teams
WHERE sportId = 44-41;

--c)NOT IN -> organizations that have teams in sport 1 but not in sport 3
SELECT teamName
FROM Teams
WHERE sportId = 1
AND teamName NOT IN (
    SELECT teamName
    FROM Teams
    WHERE sportId = 3
);


--d) INNER JOIN -> teams,the events they've participated in and date&time of the events
SELECT t.teamName, e.eventName,r.dateAndTime
FROM Teams t
INNER JOIN Evenimente e ON t.sportId = e.sportId
INNER JOIN Results r ON e.eventId = r.eventId;

--d) LEFT OUTER JOIN ->creates a table with the bet preferences and their actual selections for each user
SELECT BP.userIdbetTypeId, BP.userId, BP.betTypeId, BP.betTypeName, BP.username,
       BS.userIdbetId, BS.outcome, BS.amount
FROM BetPreferences BP
LEFT JOIN BetSelections BS ON BP.userId = BS.userId;

--d)RIGHT JOIN -> Users without transactions
SELECT tr.transactionType,u.username
FROM Transactions tr
RIGHT JOIN Users u ON tr.userId = u.userId 
WHERE tr.transactionType IS NULL;

--d)LEFT JOIN -> Users without transactions
SELECT u.username,tr.transactionType
FROM Users u
LEFT JOIN Transactions tr ON u.userId = tr.userId 
WHERE tr.transactionType IS NULL;


--e) IN get the users that have placed bets on football
SELECT DISTINCT U.username
FROM Users U
WHERE U.userId IN (
    SELECT DISTINCT BS.userId
    FROM BetSelections BS
    WHERE BS.betId IN (
        SELECT DISTINCT B.betId
        FROM Bets B
        INNER JOIN Evenimente E ON B.eventId = E.eventId
        WHERE E.sportId = 1
    )
);

-- This gets the team that was bet on that will play in the last registered events
SELECT DISTINCT T.teamName
FROM Teams T
WHERE T.teamId IN (
    SELECT DISTINCT R.teamId
    FROM Results R
    WHERE R.eventId IN (
        SELECT DISTINCT B.eventId
        FROM Bets B
        WHERE B.dateandtime = (
            SELECT MAX(B1.dateandtime)
            FROM Bets B1
        )
    )
);


--f)EXISTS and a subquery in the WHERE clause  -> get the bet id on bets placed the upcoming 5 events
select TOP(5) Bets.betId,Bets.dateandtime
from Bets
WHERE EXISTS (Select eventName from Evenimente WHERE Evenimente.eventId = Bets.eventId AND Evenimente.dateandtime < GETDATE())
ORDER BY dateandtime

select Results.dateAndTime -- ->get the date and time of results from football matches
from Results
WHERE EXISTS(Select teamName from Teams WHERE Results.teamId = Teams.teamId AND Teams.sportId ='1')


--g)SELECT FROM inside another SELECT FROM
--> gets the teams that have participated in events that resulted in events with resultId > 50
SELECT T.teamId
FROM Teams as T
WHERE T.teamId IN(
 SELECT R.teamId 
 FROM Results as R
 WHERE R.resultId > 50
);

-- -> the first 3 users that have cashed out
SELECT TOP(3) U.email
FROM Users as U
WHERE U.userId IN(
 SELECT UA.userId
 FROM UserActivities as UA
 WHERE UA.activityType ='cashed out'
);


--h) GROUP BY & COUNT ->Display the teams that compete in multiple sports

SELECT teamName,COUNT(*)as teams_count
FROM Teams
GROUP BY teamName
HAVING COUNT(*) >1
ORDER BY teamName

-- GROUP BY & SUM->Display the ID's of the users with transactions > average

SELECT TR.userId,SUM(TR.amount) as total_amount
FROM Transactions as TR
GROUP BY userId
HAVING SUM(TR.amount) > (SELECT AVG(amount) from Transactions)
ORDER BY userId

-- GROUP BY & SUM -> Display the ID's of the users that've placed bets above the average
SELECT BS.userId,AVG(BS.amount) as total_betting_amount
FROM BetSelections as BS
GROUP BY userId
HAVING AVG(BS.amount) > (SELECT AVG(amount) from BetSelections)

--GROUP BY & MIN & MAX ->Display the users that have nor the smallest or the greatest ID

SELECT  DISTINCT US.username,min(US.userId) as minUserId,max(US.userId) as maxUserId
from Users as US
GROUP BY username
HAVING SUM(Us.userId) > (SELECT MIN(userId) from Users) and SUM(Us.userId) < (SELECT MAX(userId) from Users)


--i)ANY & ALL 
-- ANY with aggregate function SUM -> Gets the users that've made only one transaction
SELECT DISTINCT userId
FROM Transactions
WHERE amount = ANY(select SUM(amount) FROM Transactions GROUP BY userID)


--ALL with subquery in the WHERE CLAUSE -> The user with the biggest transaction
SELECT DISTINCT userId
FROM Transactions AS T1
WHERE amount > ALL (SELECT amount FROM Transactions AS T2 WHERE T1.userId <> T2.userId);

--ANY with subquery in the WHERE CLAUSE -> The users that have made transactions larger than at least one user
SELECT DISTINCT userId
FROM Transactions AS T1
WHERE amount > ANY (SELECT amount FROM Transactions AS T2 WHERE T1.userId <> T2.userId);

--ALL with aggregate function AVG -> Gets the users that've placed bets larger then the transactions average
SELECT DISTINCT userId
FROM BetSelections
WHERE amount > ALL (SELECT AVG(amount) FROM Transactions);


DROP TABLE Users;
DROP TABLE Sports;
DROP TABLE Teams;
DROP TABLE Evenimente;
DROP TABLE Transactions;
DROP TABLE BetTypes;
DROP TABLE Bets;
DROP TABLE UserActivities;
DROP TABLE BetSelections;
DROP TABLE Results;
DROP TABLE BetPreferences;

create table versionsTable(
	version INT
	)
insert into versionsTable VALUES(1)

create table proceduresTable(
	fromVersion INT,
	toVersion INT,
	PRIMARY KEY(fromVersion,toVersion),
	procedureName VARCHAR(100)
	)
INSERT INTO proceduresTable(fromVersion,toVersion,procedureName)
VALUES
	(1,2,'SetAmountToTinyInt'),
	(2,1,'undoChangeTypeOfAColumn'),
	(2,3,'addDefaultConstraint'),
	(3,2,'RemoveDefaultConstraint'),
	(3,4,'AddAColumn'),
	(4,3,'RemoveAColumn'),
	(4,5,'CreateANewTable'),
	(5,4,'RemoveNewlyCreatedTable'),
	(5,6,'SetPrimaryKey'),
	(6,5,'RemovePrimaryKey'),
	(6,7,'AddCandidatekey'),
	(7,6,'RemoveCandidateKey'),
	(7,8,'AddForeignKey'),
	(8,7,'RemoveForeignKey');


execute SetAmountToTinyInt
execute undoChangeTypeOfAColumn
execute addDefaultConstraint
execute RemoveDefaultConstraint
EXECUTE AddAColumn
Execute RemoveAColumn
EXECUTE CreateANewTable
EXECUTE RemoveNewlyCreatedTable
execute SetPrimaryKey
execute RemovePrimaryKey
execute AddCandidatekey
execute RemoveCandidateKey
execute AddForeignKey
execute RemoveForeignKey

drop table CashOutAction