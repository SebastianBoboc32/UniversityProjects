create or alter procedure SetAmountToTinyInt
as
begin
	alter table BetSelections
	alter column amount smallint
	end;
	go;


