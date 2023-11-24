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
