create procedure RemoveForeignKey
as
begin
alter table BetPreferences
drop constraint if exists betpf_fk
end;
go;