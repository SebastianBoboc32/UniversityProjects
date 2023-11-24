create procedure AddForeignKey
as
begin
alter table BetPreferences
add constraint betpf_fk foreign key (betTypeId) references BetTypes(betTypeId) on delete cascade
end;
go;