create procedure RemoveCandidateKey
as
begin
alter table Users
drop constraint if exists users_ck
end;
go;