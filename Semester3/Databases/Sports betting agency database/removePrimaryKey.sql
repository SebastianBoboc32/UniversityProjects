create or alter procedure RemovePrimaryKey
as
begin
alter table BetPreferences
drop constraint if exists pk_id
end;
go;

