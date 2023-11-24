create procedure undoChangeTypeOfAColumn
AS
begin
alter table BetSelections
alter column Amount INT
END;
Go;
