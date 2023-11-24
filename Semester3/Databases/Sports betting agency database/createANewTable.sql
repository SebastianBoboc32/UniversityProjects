create procedure CreateANewTable
AS
BEGIN
CREATE TABLE 
   CashOutAction(
		cashOutId INT PRimary key,
		playerId INT references Users(userId),
		amount INT,
		eventId INT references Evenimente(EventId)
		)
SELECT * FROM CashOutAction
END;
GO;


