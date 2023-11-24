create or alter procedure SetPrimaryKey
as
begin
alter table BetPreferences
ADD constraint pk_id PRIMARY KEY(userIdbetTypeId)
end;
go;