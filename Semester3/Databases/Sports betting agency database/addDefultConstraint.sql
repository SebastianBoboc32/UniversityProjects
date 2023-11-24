create procedure addDefaultConstraint
as
begin
alter table Users
add constraint default_email
default '' for email
end;
go;
