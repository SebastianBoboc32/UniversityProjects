create table dentists(
	dentist_id int primary key,
	dentist_name varchar(100) unique,
	phone_number char(10),
	email varchar(100)
);

INSERT INTO dentists VALUES
(1,'dentist_1','0707070707','email@example.co'),
(2,'dentist_2','0707070707','email@example.co'),
(3,'dentist_3','0707070707','email@example.co'),
(4,'dentist_4','0707070707','email@example.co'),
(5,'dentist_5','0707070707','email@example.co'),
(6,'dentist_6','0707070707','email@example.co'),
(7,'dentist_7','0707070707','email@example.co')

create table patients(
	patient_id int primary key,
	patient_name varchar(100) unique,
	phone_number char(10),
	email varchar(100),
	phy_address varchar(100)
);

INSERT INTO patients VALUES
(1,'patient_1','0707070707','email@example.co','addr1'),
(2,'patient_2','0707070707','email@example.co','addr1'),
(3,'patient_3','0707070707','email@example.co','addr1'),
(4,'patient_4','0707070707','email@example.co','addr1'),
(5,'patient_5','0707070707','email@example.co','addr1'),
(6,'patient_6','0707070707','email@example.co','addr1'),
(7,'patient_7','0707070707','email@example.co','addr1'),
(8,'patient_8','0707070707','email@example.co','addr1')


create table dental_services(
	service_id int primary key,
	d_service_name varchar(100) unique,
	fee int 
);

INSERT INTO dental_services VALUES
(1,'service_1',100),
(2,'service_2',100),
(3,'service_3',100),
(4,'service_4',100),
(5,'service_5',100),
(6,'service_6',100)


create table treatment_plans(
	t_plan_id int primary key,
	duration int,
	plan_name varchar(100),
	fee int,
	service_id int references dental_services(service_id)
);

INSERT INTO treatment_plans VALUES
(1,2,'plan_1',100,2),
(2,2,'plan_2',100,6),
(3,2,'plan_3',100,1),
(4,2,'plan_4',100,4),
(5,2,'plan_5',100,3),
(6,2,'plan_6',100,5),
(7,2,'plan_7',100,2),
(8,2,'plan_8',100,1),
(9,2,'plan_9',100,5),
(10,2,'plan_10',10,4),
(11,2,'plan_11',100,1),
(12,2,'plan_12',100,3),
(13,2,'plan_13',100,2),
(14,2,'plan_14',100,5)

create table appointments(
	appointment_id int primary key,
	information varchar(100),
	date_of_appointment date,
	hour_of_app int,
	minutes_of_app int,
	plan_id int references treatment_plans(t_plan_id),
	patient_id int references patients(patient_id)
);

INSERT INTO appointments VALUES
(1,'information','2024-02-12',6,12,10,1),
(2,'information','2024-02-13',6,12,1,2),
(3,'information','2024-01-22',6,12,12,3),
(4,'information','2024-05-12',6,12,11,4),
(5,'information','2024-06-12',6,12,4,5),
(6,'information','2024-02-15',6,12,5,6),
(7,'information','2024-02-20',6,12,6,6),
(8,'information','2024-03-21',6,12,7,7),
(9,'information','2024-02-01',6,12,9,8),
(10,'information','2024-02-10',6,12,8,1)

create table dentists_plans(
	dentist_id int references dentists(dentist_id),
	plan_id int references treatment_plans(t_plan_id)

);

INSERT INTO dentists_plans VALUES
(1,2),
(3,1),
(4,10),
(5,12),
(6,3),
(7,4),
(1,5),
(2,5),
(3,5),
(4,1),
(5,4)

create or alter procedure add_patient
@patient_id INT,
@patient_name VARCHAR(100),
@phone_number char(10),
@email varchar(100),
@phy_addr varchar(100)
AS
	BEGIN
		 IF EXISTS (
						SELECT * FROM patients WHERE patient_name = @patient_name
					)
					BEGIN
						 RAISERROR('Patient already in db',10,1);
					END
		ELSE
		BEGIN
			 INSERT INTO patients VALUES (@patient_id,@patient_name,@phone_number,@email,@phy_addr)
		END
END

EXEC add_patient @patient_id = 17,@patient_name ='andrei',@phone_number = '0123456789',@email = 'email@email.com',@phy_addr = 'cluj'
EXEC add_patient @patient_id = 18,@patient_name ='alex',@phone_number = '0123456789',@email = 'email@email.com',@phy_addr = 'cluj'
SELECT * FROM patients

CREATE OR ALTER VIEW february_patients AS
	SELECT patient_name FROM patients WHERE patient_id IN
	(
		SELECT patient_id FROM appointments WHERE date_of_appointment LIKE '2024-02%'
	)

SELECT * FROM february_patients

CREATE or alter FUNCTION demanded_dentists
(@begin_hour INT, @end_hour INT)
RETURNS TABLE
AS
	RETURN 
		SELECT d.dentist_name,ap.hour_of_app
		FROM dentists d JOIN dentists_plans dp ON d.dentist_id = dp.dentist_id
		JOIN treatment_plans tp ON dp.plan_id = tp.t_plan_id
		JOIN appointments ap ON ap.appointment_id = tp.t_plan_id
		WHERE ap.hour_of_app > @begin_hour AND ap.hour_of_app < @end_hour
		--GROUP BY d.dentist_name HAVING count(d.dentist_name) >6

SELECT * FROM demanded_dentists(1,17)			
			