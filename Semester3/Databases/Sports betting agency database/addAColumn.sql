CREATE PROCEDURE AddAColumn
AS
BEGIN
	ALTER TABLE Results
	ADD Description VARCHAR(MAX)
	END;
	GO;

