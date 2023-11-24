create procedure RemoveDefaultConstraint
as
begin
alter table Users
drop constraint default_email
end;
go;
