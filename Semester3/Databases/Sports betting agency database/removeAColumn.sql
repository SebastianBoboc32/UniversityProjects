create procedure RemoveAColumn
AS
BEGIN
 Alter Table Results 
 drop column if exists Description
 END;
 GO;
