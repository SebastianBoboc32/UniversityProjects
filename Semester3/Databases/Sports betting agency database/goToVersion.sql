CREATE OR ALTER PROCEDURE goToVersion(@newVersion INT) 
AS

	DECLARE @curr INT
	DECLARE @procedureName VARCHAR(100)
	SELECT @curr = version FROM versionsTable

	IF  @newVersion > (SELECT MAX(toVersion) FROM proceduresTable)
		RAISERROR ('Bad version', 10, 1)
	ELSE
	BEGIN
		IF @newVersion = @curr
			PRINT('Already on this version!');
		ELSE
		BEGIN
			IF @curr > @newVersion
			BEGIN
				WHILE @curr > @newVersion
				BEGIN
					SELECT @procedureName = procedureName FROM proceduresTable 
					WHERE fromVersion = @curr AND toVersion = @curr - 1
					PRINT('executing: ' + @procedureName);
					EXEC(@procedureName)
					SET @curr = @curr - 1
				END
			END

			IF @curr < @newVersion
			BEGIN
				WHILE @curr < @newVersion
					BEGIN
						SELECT @procedureName = procedureName FROM proceduresTable
						WHERE fromVersion = @curr AND toVersion = @curr + 1
						PRINT('executing: ' + @procedureName);
						EXEC (@procedureName)
						SET @curr = @curr + 1
					END
			END

			UPDATE versionsTable SET version = @newVersion
		END
	END

GO


EXEC goToVersion 3
SELECT * FROM proceduresTable;
