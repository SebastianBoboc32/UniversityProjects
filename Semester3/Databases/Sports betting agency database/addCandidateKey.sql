create procedure AddCandidateKey
as
begin
alter table Users
	add constraint users_ck UNIQUE(userId,username)
	end;
	go;