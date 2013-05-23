CREATE DATABASE  IF NOT EXISTS `store` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `store`;
-- MySQL dump 10.13  Distrib 5.5.16, for Win32 (x86)
--
-- Host: localhost    Database: store
-- ------------------------------------------------------
-- Server version	5.5.23

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Dumping routines for database 'store'
--
/*!50003 DROP PROCEDURE IF EXISTS `account_check_pwd` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `account_check_pwd`(
IN userid varchar(50),
IN password varchar(50),
OUT invalid int)
BEGIN
SELECT count(*)  INTO invalid  FROM user WHERE uid=userid AND pwd=password;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `account_get_randomkey` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `account_get_randomkey`(
IN userid varchar(50),
OUT randomKey varchar(50)
)
BEGIN
SELECT random_key  INTO randomKey  FROM user WHERE uid=userid;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `account_update_pwd` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `account_update_pwd`(
IN accountID varchar(50),
IN accountPwd varchar(50),
OUT returnVal int)
BEGIN
UPDATE user SET pwd=accountPwd WHERE uid=accountID;
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicineform_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicineform_get`(
)
BEGIN

SELECT * FROM medicine_form LIMIT 100;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicineform_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicineform_select`(
IN formID int)
BEGIN

SELECT * FROM medicine_form WHERE id=formID;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicineOTC_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicineOTC_get`(
)
BEGIN

SELECT * FROM medicine_otc LIMIT 100;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicineOTC_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicineOTC_select`(
IN OTCID int)
BEGIN

SELECT * FROM medicine_otc WHERE id=OTCID;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicinetype_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicinetype_get`(
)
BEGIN

SELECT * FROM medicine_type LIMIT 100;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicinetype_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicinetype_select`(
IN typeID int)
BEGIN

SELECT * FROM medicine_type WHERE id=typeID;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicineunit_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicineunit_get`(
)
BEGIN

SELECT * FROM medicine_unit LIMIT 100;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicineunit_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicineunit_select`(
IN unitID int)
BEGIN

SELECT * FROM medicine_unit WHERE id=unitID;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_add` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_add`(
IN medicineSN varchar(100),
IN medicineName varchar(100),
IN medicineSPec varchar(100),
IN medicineVendorID int,
IN unitID int,
IN retailPrice double,
IN typeID int,
IN OTCID int,
IN formID int,
OUT returnVal int)
BEGIN
-- Insert into Medicine
INSERT INTO medicine (sn, name, spec, vendor_id, unit_id, retail_price, type_id, otc_id, form_id, create_time, modify_time) VALUES (medicineSN, medicineName, medicineSpec, medicineVendorID, unitID, retailPrice, typeID, OTCID, formID, now(), now());
SET returnVal=row_count();

-- Update supplier's medicine count
IF (returnVal!=0) THEN
    UPDATE vendor SET medicine_count=medicine_count+returnVal WHERE id=medicineVendorID;
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_batch_delete_by_mid` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_batch_delete_by_mid`(
IN medicineID int,
OUT returnVal int)
BEGIN
DECLARE tempNum INT;

SELECT count(*) INTO tempNum FROM medicine_batch WHERE medicine_id=medicineID;
IF (tempNum > 0) THEN
    DELETE FROM medicine_batch WHERE medicine_id=medicineID;
    SET returnVal=row_count();
ELSE
    SET returnVal=1;
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_batch_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_batch_get`(
IN batchNum varchar(100),
IN medicineID int,
IN numPerPage int,
IN pageNum int,
OUT totalNum int,
OUT totalPage int)
BEGIN
DECLARE offset int;

IF (pageNum >= 0 && numPerPage > 0) THEN
    SET offset = numPerPage*pageNum;
    
    IF (batchNum=''|| batchNum is null) THEN
        SELECT COUNT(*) INTO totalNum FROM medicine_batch WHERE medicine_id=medicineID ORDER BY id DESC;
        SELECT * FROM medicine_batch WHERE medicine_id=medicineID ORDER BY id DESC LIMIT offset,numPerPage;
    ELSE
        SELECT COUNT(*) INTO totalNum FROM medicine_batch WHERE medicine_id=medicineID AND batch_num LIKE batchNum ORDER BY id DESC;
        SELECT * FROM medicine_batch WHERE medicine_id=medicineID AND batch_num LIKE batchNum ORDER BY id DESC LIMIT offset,numPerPage;
    END IF;
    
    SET totalPage = (totalNum - 1) / numPerPage + 1;
    
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_batch_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_batch_select`(
IN medicineID int,
IN medicineBatchNum varchar(100))
BEGIN

SELECT * FROM medicine_batch WHERE medicine_id=medicineID AND batch_num=medicineBatchNum LIMIT 1;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_batch_update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_batch_update`(
IN medicineID int,
IN batchNum varchar(100),
IN productDate datetime,
IN expireDate datetime,
OUT batchID int,
OUT returnVal int)
BEGIN
DECLARE srcProductDate datetime;
DECLARE srcExpireDate datetime;

SELECT id,product_date,expire_date INTO batchID,srcProductDate,srcExpireDate FROM medicine_batch WHERE medicine_id=medicineID AND batch_num=batchNum;
SET returnVal=found_rows();
IF (returnVal != 0) THEN
    IF (srcProductDate != productDate || srcExpireDate != expireDate) THEN
        UPDATE medicine_batch SET product_date=productDate,expire_date=expireDate WHERE id=batchID;
        SET returnVal=row_count();
    END IF;
ELSE
    INSERT INTO medicine_batch (medicine_id, batch_num, product_date, expire_date) 
            VALUES (medicineID, batchNum, productDate, expireDate);
    SET returnVal=row_count();
    SELECT last_insert_id() INTO batchID FROM medicine_batch LIMIT 1;
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_check_exist` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_check_exist`(
IN medicineID int,
OUT exist int
)
BEGIN
SELECT count(*)  INTO exist  FROM medicine WHERE id=medicineID;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_check_exist_by_sn` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_check_exist_by_sn`(
IN medicineSN varchar(100),
OUT exist int
)
BEGIN
SELECT count(*)  INTO exist  FROM medicine WHERE sn=medicineSN;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_delete` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_delete`(
IN medicineID int,
OUT returnVal int
)
BEGIN
DECLARE medicineVendorID int;
DECLARE medicineCount int;

-- get vendorID of the medicine
SELECT vendor_id INTO medicineVendorID FROM medicine WHERE id = medicineID; 

-- delete the medicine
DELETE FROM medicine WHERE id = medicineID; 
SET returnVal=row_count();

IF (returnVal!=0) THEN
    -- Update medicine count of the vendor
    SELECT medicine_count INTO medicineCount FROM vendor WHERE id = medicineVendorID LIMIT 1;
    IF (medicineCount>=returnVal) THEN
        UPDATE vendor SET medicine_count=medicine_count-returnVal WHERE id=medicineVendorID;
    END IF;
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_get`(
IN medicineSN varchar(100),
IN medicineName varchar(100),
IN medicineVendorID int,
IN numPerPage int,
IN pageNum int,
OUT totalNum int,
OUT totalPage int)
BEGIN
DECLARE offset int;

IF (pageNum >= 0 && numPerPage > 0) THEN
    SET offset = numPerPage*pageNum;
    
    SET @countSqlString = 'SELECT COUNT(*) INTO @totalNum FROM view_medicine WHERE 1=1';
    SET @sqlString = 'SELECT * FROM view_medicine WHERE 1=1';
    IF (medicineSN!='' && medicineSN is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND sn=\'',medicineSN, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND sn=\'',medicineSN, '\'');
    END IF;
    IF (medicineName!='' && medicineName is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND name LIKE \'',medicineName, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND name LIKE \'',medicineName, '\'');
    END IF;
    IF (medicineVendorID>=0 && medicineVendorID is not null) THEN
       SET @countSqlString = CONCAT(@countSqlString, ' AND vendor_id=',medicineVendorID);
       SET @sqlString = CONCAT(@sqlString, ' AND vendor_id=',medicineVendorID);
    END IF;
    SET @sqlString = CONCAT(@sqlString, ' ORDER BY id DESC LIMIT ',offset,',', numPerPage);
    
    PREPARE smtp FROM @countSqlString;
    EXECUTE smtp;
    SET totalNum=@totalNum;
	SET totalPage = (totalNum - 1) / numPerPage + 1;
    
    PREPARE smtp FROM @sqlString;
    EXECUTE smtp;
END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_select`(
IN medicineID int)
BEGIN

SELECT * FROM view_medicine WHERE id=medicineID LIMIT 1;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_select_by_sn` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_select_by_sn`(
IN medicineSN varchar(100))
BEGIN

SELECT * FROM view_medicine WHERE sn=medicineSN;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_update`(
IN oldID int,
IN medicineID int,
IN medicineSN varchar(100),
IN medicineName varchar(100),
IN medicineSpec varchar(100),
IN medicineVendorID int,
IN unitID int,
IN retailPrice double,
IN typeID int,
IN OTCID int,
IN formID int,
OUT returnVal int)
BEGIN
DECLARE oldVendorID INT;
DECLARE medicineCount INT;

-- Get old supplierID and vendorID of the medicine
SELECT vendor_id INTO oldVendorID FROM medicine WHERE id = oldID; 

-- Update the medicine
UPDATE medicine SET id=medicineID, sn=medicineSN, name=medicineName, spec=medicineSpec, vendor_id=medicineVendorID, unit_id=unitID, retail_price=retailPrice, type_id=typeID, otc_id=OTCID, form_id=formID, modify_time=now() WHERE id=oldID;
SET returnVal=row_count();

-- Update the medicine_count of the old supplier and new supplier
IF (returnVal != 0) THEN
    if ((oldVendorID != medicineVendorID) OR (oldVendorID is not null OR medicineVendorID is not null)) THEN
        SELECT medicine_count INTO medicineCount FROM vendor WHERE id = oldVendorID;
        IF (found_rows() > 0 AND medicineCount >= 1) THEN
            UPDATE vendor SET medicine_count=medicine_count-1 WHERE id=oldVendorID;
        END IF;
        UPDATE vendor SET medicine_count=medicine_count+1 WHERE id=medicineVendorID;
    END IF;
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `medicine_update_retail_price` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `medicine_update_retail_price`(
IN medicineID int,
IN retailPrice double,
OUT returnVal int)
BEGIN

-- Update the medicine
UPDATE medicine SET retail_price=retailPrice, modify_time=now() WHERE id=medicineID;
SET returnVal=row_count();

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `pos_add` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `pos_add`(
IN MAC varchar(45),
OUT posID int,
OUT returnVal int)
BEGIN
DECLARE pcID int;

INSERT INTO pc (pc_mac) VALUES (MAC);
SELECT last_insert_id() INTO pcID FROM pc LIMIT 1;

INSERT INTO pos (pc_id) VALUES (pcID);
SELECT last_insert_id() INTO posID FROM pos LIMIT 1;
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `pos_check_exist` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `pos_check_exist`(
IN posID int,
OUT exist int
)
BEGIN
SELECT count(*)  INTO exist  FROM view_pos WHERE id=posID;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `pos_check_exist_by_mac` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `pos_check_exist_by_mac`(
IN MAC varchar(45),
OUT exist int
)
BEGIN
SELECT count(*)  INTO exist  FROM view_pos WHERE pc_mac=MAC;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `pos_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `pos_get`(
IN numPerPage int,
IN pageNum int,
OUT totalNum int,
OUT totalPage int)
BEGIN
DECLARE offset int;

IF (pageNum >= 0 && numPerPage > 0) THEN
    SELECT COUNT(*)INTO totalNum FROM view_pos ORDER BY id;
    SET totalPage = (totalNum - 1) / numPerPage + 1;
    
    SET offset = numPerPage*pageNum;
    SELECT * FROM view_pos ORDER BY id LIMIT offset,numPerPage;

END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `pos_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `pos_select`(
IN MAC varchar(45))
BEGIN

SELECT * FROM view_pos WHERE pc_mac=MAC;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `pos_update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `pos_update`(
IN oldID int,
IN posID int,
IN pcID int,
OUT returnVal int)
BEGIN

-- Update the pos
UPDATE pos SET id=posID, pc_id=pcID WHERE id=oldID;
SET returnVal=row_count();

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `purchase_add` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `purchase_add`(
IN userID int,
IN supplierID int,
IN medicineID int,
IN number int,
IN purPrice double,
IN batchNum varchar(100),
IN productDate datetime,
IN expireDate datetime,
OUT returnVal int)
BEGIN
DECLARE batchID int;
DECLARE purchaseID int;
DECLARE storeID int;

-- Update medicine batch
CALL medicine_batch_update(medicineID, batchNum, productDate, expireDate, batchID, returnVal);
IF (returnVal > 0) THEN
	-- Insert into purchase
	INSERT INTO purchase (user_id, supplier_id, medicine_num, pur_price, create_time, modify_time, batch_id) 
				VALUES (userID, supplierID, number, purPrice, now(), now(), batchID);
	SET returnVal=row_count();
	SELECT last_insert_id() INTO purchaseID FROM purchase LIMIT 1;

	IF (returnVal > 0) THEN
		-- Update store
		CALL store_add_num(batchID, number, storeID, returnVal);
		SET returnVal=row_count();
		IF (returnVal <= 0) THEN
			DELETE FROM purchase WHERE id=purchaseID;
		END IF;
	END IF;
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `purchase_delete` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `purchase_delete`(
IN purchaseID int,
OUT returnVal int
)
BEGIN
DECLARE storeID int;
DECLARE supplierMedicineID int;
DECLARE medicineID int;
DECLARE medicineBatchID int;
DECLARE purMedicineNum int;
DECLARE storeMedicineNum int;

-- Update store
SELECT medicine_id, batch_id, medicine_num INTO medicineID, medicineBatchID, purMedicineNum FROM view_purchase WHERE id=purchaseID;

IF (found_rows() != 0) THEN
    CALL store_add_num(medicineID, medicineBatchID,-purMedicineNum, storeID, returnVal);
END IF;

DELETE FROM purchase WHERE id = purchaseID; 
SET returnVal=row_count();

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `purchase_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `purchase_get`(
IN purDateBegin varchar(20),
IN purDateEnd varchar(20),
IN medicineSN varchar(100),
IN medicineName varchar(100),
IN medicineBatchNum varchar(100),
IN supplierID int, 
IN numPerPage int,
IN pageNum int,
OUT totalNum int,
OUT totalPage int,
OUT totalPrice double)
BEGIN
DECLARE offset int;

IF (pageNum >= 0 && numPerPage > 0) THEN
    SET offset = numPerPage*pageNum;
    
    SET @countSqlString = 'SELECT COUNT(*),SUM(pur_price*medicine_num) INTO @totalNum,@totalPrice FROM view_purchase WHERE 1=1';
    SET @sqlString = 'SELECT * FROM view_purchase WHERE 1=1';
    IF (purDateBegin!='' && purDateBegin is not null && purDateEnd!='' && purDateEnd is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND DATEDIFF(create_time,\'',purDateBegin, '\')>=0');
        SET @sqlString = CONCAT(@sqlString, ' AND DATEDIFF(create_time,\'', purDateBegin,'\')>=0');
        SET @countSqlString = CONCAT(@countSqlString, ' AND DATEDIFF(create_time,\'', purDateEnd,'\')<=0');
        SET @sqlString = CONCAT(@sqlString, ' AND DATEDIFF(create_time,\'', purDateEnd,'\')<=0');
    END IF;
	IF (medicineSN!='' && medicineSN is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_sn=\'',medicineSN, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND medicine_sn=\'',medicineSN, '\'');
    END IF;
    IF (medicineName!='' && medicineName is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_name LIKE \'',medicineName, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND medicine_name LIKE \'',medicineName, '\'');
    END IF;
	IF (medicineBatchNum!='' && medicineBatchNum is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND batch_num =\'',medicineBatchNum, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND batch_num =\'',medicineBatchNum, '\'');
    END IF;
	IF (supplierID >= 0 && supplierID is not null) THEN
       SET @countSqlString = CONCAT(@countSqlString, ' AND supplier_id=',supplierID);
       SET @sqlString = CONCAT(@sqlString, ' AND supplier_id=',supplierID);
    END IF;
    SET @sqlString = CONCAT(@sqlString, ' ORDER BY id DESC LIMIT ',offset,',', numPerPage);
    
    PREPARE smtp FROM @countSqlString;
    EXECUTE smtp;
    SET totalPrice=@totalPrice;
    SET totalNum=@totalNum;
    SET totalPage = (totalNum - 1) / numPerPage + 1;
    
    PREPARE smtp FROM @sqlString;
    EXECUTE smtp;
    
    IF (found_rows() <= 0) THEN
        SET totalPrice=0;
        SET totalNum=0;
        SET totalPage = 0;
    END IF;
    
END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `purchase_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `purchase_select`(
IN purchaseID int)
BEGIN

SELECT * FROM view_purchase WHERE id=purchaseID LIMIT 1;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `retail_add` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `retail_add`(
IN pcID int,
IN retailSN varchar(100),
IN userID int,
IN totalPrice double,
IN inPrice double,
In outPrice double,
OUT retailID int,
OUT returnVal int)
BEGIN
INSERT INTO retail (pc_id,sn,user_id, create_time, total_price, in_price, out_price) 
VALUES (pcID,retailSN,userID, now(), totalPrice, inPrice, outPrice);
SELECT last_insert_id() INTO retailID FROM retail LIMIT 1;
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `retail_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `retail_get`(
IN posID int,
IN userID int,
IN retailDateBegin varchar(20),
IN retailDateEnd varchar(20),
IN numPerPage int,
IN pageNum int,
OUT totalNum int,
OUT totalPage int,
OUT totalPrice double)
BEGIN
DECLARE offset int;

IF (pageNum >= 0 && numPerPage > 0) THEN
    SET offset = numPerPage*pageNum;
    
    SET @countSqlString = 'SELECT COUNT(*),SUM(total_price) INTO @totalNum,@totalPrice FROM view_retail WHERE 1=1';
    SET @sqlString = 'SELECT * FROM view_retail WHERE 1=1';
    IF (posID!=-1 && posID is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND pos_id=\'',posID, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND pos_id=\'',posID, '\'');
    END IF;
    IF (userID!=-1 && userID is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND user_id=\'',userID, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND user_id=\'',userID, '\'');
    END IF;
    IF (retailDateBegin!='' && retailDateBegin is not null && retailDateEnd!='' && retailDateEnd is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND DATEDIFF(create_time,\'',retailDateBegin, '\')>=0');
        SET @sqlString = CONCAT(@sqlString, ' AND DATEDIFF(create_time,\'',retailDateBegin,'\')>=0');
        SET @countSqlString = CONCAT(@countSqlString, ' AND DATEDIFF(create_time,\'', retailDateEnd,'\')<=0');
        SET @sqlString = CONCAT(@sqlString, ' AND DATEDIFF(create_time,\'', retailDateEnd,'\')<=0');
    END IF;
    SET @sqlString = CONCAT(@sqlString, ' ORDER BY id DESC LIMIT ',offset,',', numPerPage);
    
    PREPARE smtp FROM @countSqlString;
    EXECUTE smtp;
    SET totalPrice=@totalPrice;
    SET totalNum=@totalNum;
    SET totalPage = (totalNum - 1) / numPerPage + 1;
        
    PREPARE smtp FROM @sqlString;
    EXECUTE smtp;
    
    IF (found_rows() <= 0) THEN
        SET totalPrice=0;
        SET totalNum=0;
        SET totalPage = 0;
    END IF;
    
END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `retail_item_add` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `retail_item_add`(
IN retailID int,
IN medicineID int,
IN medicinePrice double,
IN medicineNum int,
IN retailPrice double,
OUT returnVal int)
BEGIN
DECLARE storeID int;
DECLARE storeRetVal int;

INSERT INTO retail_item (retail_id, medicine_id, medicine_num, medicine_price, retail_price) 
	VALUES (retailID, medicineID, medicineNum, medicinePrice, retailPrice);
SET returnVal=row_count();
IF (returnVal != 0) THEN
	CALL store_add_num_by_mid(medicineID, -medicineNum, storeID, storeRetVal);
END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `retail_item_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `retail_item_get`(
IN retailID int
)
BEGIN

SELECT * FROM view_retail_item WHERE retail_id=retailID;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `retail_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `retail_select`(
IN retailID int)
BEGIN

SELECT * FROM view_retail WHERE id=retailID;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `store_add_num` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `store_add_num`(
IN batchID int,
IN addNum int,
OUT storeID int,
OUT returnVal int)
BEGIN
DECLARE storeByBatchID int;
DECLARE tempNum int;

SELECT id, medicine_num INTO storeByBatchID, tempNum FROM store_by_batch WHERE medicine_batch_id=batchID;
SET returnVal=found_rows();
IF (returnVal = 0) THEN
    INSERT INTO store_by_batch (medicine_batch_id,medicine_num, create_time, modify_time) 
        VALUES (batchID, addNum, now(), now());
ELSE
    SET tempNum = tempNum + addNum;
    IF (tempNum < 0) THEN
        SET tempNum = 0;
		UPDATE store_by_batch SET medicine_num = 0, modify_time=now() WHERE id=storeByBatchID;
    ELSE
        UPDATE store_by_batch SET medicine_num = tempNum, modify_time=now() WHERE id=storeByBatchID;
    END IF;
END IF;

SELECT last_insert_id() INTO storeID FROM store_by_batch LIMIT 1;
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `store_add_num_by_mid` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `store_add_num_by_mid`(
IN medicineID int,
IN addNum int,
OUT storeID int,
OUT returnVal int)
BEGIN
DECLARE done INT DEFAULT FALSE;
DECLARE preStoreID int;
DECLARE tempNum int;
DECLARE cur_batchSotre CURSOR for select id, medicine_num from view_store_by_batch WHERE medicine_id=medicineID;  
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
 
SET preStoreID = -1;
 
open cur_batchSotre;  
read_loop: LOOP 
    fetch cur_batchSotre into storeID, tempNum;  
    IF done THEN
      LEAVE read_loop;
    END IF;
    
    IF preStoreID!= -1 THEN
        DELETE FROM store_by_batch WHERE id=preStoreID;
        SET preStoreID = -1;
    END IF;
    
    SET tempNum = tempNum + addNum;
    SET addNum = 0;
    IF (tempNum <= 0) THEN
        SET addNum = tempNum;
        SET tempNum = 0;
        UPDATE store_by_batch SET medicine_num=0, modify_time=now() WHERE id=storeID;
        SET preStoreID = storeID;
    ELSE
        UPDATE store_by_batch SET medicine_num=tempNum, modify_time=now() WHERE id=storeID;
        LEAVE read_loop;
    END IF;
END LOOP; 
close cur_batchSotre;  

SELECT last_insert_id() INTO storeID FROM store_by_batch LIMIT 1;
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `store_batch_delete` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `store_batch_delete`(
IN storeID int,
OUT returnVal int
)
BEGIN
DELETE FROM store_by_batch WHERE id=storeID;
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `store_batch_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `store_batch_get`(
IN medicineSN varchar(100),
IN medicineName varchar(100),
IN expireDate varchar(20),
IN numPerPage int,
IN pageNum int,
OUT totalNum int,
OUT totalPage int)
BEGIN
DECLARE offset int;

IF (pageNum >= 0 && numPerPage > 0) THEN
    SET offset = numPerPage*pageNum;
    
    SET @countSqlString = 'SELECT COUNT(*) INTO @totalNum FROM view_store_by_batch WHERE 1=1';
    SET @sqlString = 'SELECT * FROM view_store_by_batch WHERE 1=1';
    IF (medicineSN!='' AND medicineSN is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_sn=\'',medicineSN, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND medicine_sn=\'',medicineSN, '\'');
    END IF;
    IF (medicineName!='' && medicineName is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_name LIKE \'',medicineName, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND medicine_name LIKE \'',medicineName, '\'');
    END IF;
    IF (expireDate!='' AND expireDate is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND DATEDIFF(expire_date,\'',expireDate,'\')<0');
        SET @sqlString = CONCAT(@sqlString, ' AND DATEDIFF(expire_date,\'',expireDate,'\')<0');
    END IF;
    SET @sqlString = CONCAT(@sqlString, ' ORDER BY id DESC LIMIT ',offset,',', numPerPage);
    
    PREPARE smtp FROM @countSqlString;
    EXECUTE smtp;
    SET totalNum=@totalNum;
    SET totalPage = (totalNum - 1) / numPerPage + 1;
    
    PREPARE smtp FROM @sqlString;
    EXECUTE smtp;
END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `store_batch_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `store_batch_select`(
IN storeID int)
BEGIN

SELECT * FROM view_store_by_batch WHERE id=storeID LIMIT 1;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `store_batch_update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `store_batch_update`(
IN storeID int,
IN medicineNum int,
OUT returnVal int)
BEGIN

UPDATE store_by_batch SET medicine_num = medicineNum WHERE id=storeID;

SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `store_delete` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `store_delete`(
IN medicineSN varchar(100),
OUT returnVal int
)
BEGIN
DECLARE done INT DEFAULT FALSE;
DECLARE storeByBatchID int;
DECLARE cur_batchSotre CURSOR for select id from view_store_by_batch WHERE medicine_sn=medicineSN;  
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
 
open cur_batchSotre;  
read_loop: LOOP 
    fetch cur_batchSotre into storeByBatchID;  
    IF done THEN
      LEAVE read_loop;
    END IF;
   
    DELETE FROM store_by_batch WHERE id=storeByBatchID;
    
END LOOP; 
close cur_batchSotre;  

SET returnVal=row_count();

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `store_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `store_get`(
IN medicineSN varchar(100),
IN medicineName varchar(100),
IN expireDate varchar(20),
IN medicineVendorID int,
IN numPerPage int,
IN pageNum int,
OUT totalNum int,
OUT totalPage int)
BEGIN
DECLARE offset int;

IF (pageNum >= 0 && numPerPage > 0) THEN
    SET offset = numPerPage*pageNum;
    
    SET @countSqlString = 'SELECT COUNT(*) INTO @totalNum FROM view_store WHERE 1=1';
    SET @sqlString = 'SELECT * FROM view_store WHERE 1=1';
    IF (medicineSN!='' && medicineSN is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_sn=\'',medicineSN, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND medicine_sn=\'',medicineSN, '\'');
    END IF;
    IF (medicineName!='' && medicineName is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_name LIKE \'',medicineName, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND medicine_name LIKE \'',medicineName, '\'');
    END IF;
    IF (expireDate!='' && expireDate is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND DATEDIFF(expire_date,\'',expireDate,'\')<0');
        SET @sqlString = CONCAT(@sqlString, ' AND DATEDIFF(expire_date,\'',expireDate,'\')<0');
    END IF;
    IF (medicineVendorID>=0 && medicineVendorID is not null) THEN
       SET @countSqlString = CONCAT(@countSqlString, ' AND vendor_id=',medicineVendorID);
       SET @sqlString = CONCAT(@sqlString, ' AND vendor_id=',medicineVendorID);
    END IF;
    SET @sqlString = CONCAT(@sqlString, ' ORDER BY id DESC LIMIT ',offset,',', numPerPage);
    
    PREPARE smtp FROM @countSqlString;
    EXECUTE smtp;
    SET totalNum=@totalNum;
    SET totalPage = (totalNum - 1) / numPerPage + 1;
    
    PREPARE smtp FROM @sqlString;
    EXECUTE smtp;
END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `store_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `store_select`(
IN medicineSN varchar(100))
BEGIN

SELECT * FROM view_store WHERE medicine_sn=medicineSN LIMIT 1;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `suppliermedicine_add` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `suppliermedicine_add`(
IN medicineID int,
IN medicineSupplierID int,
IN purPrice double,
OUT returnVal int)
BEGIN
-- Insert into Medicine
INSERT INTO supplier_medicine (medicine_id, supplier_id, pur_price, create_time, modify_time) VALUES (medicineID, medicineSupplierID, purPrice, now(), now());
SET returnVal=row_count();

IF (returnVal!=0) THEN
    -- Update medicine's supplier count
    UPDATE medicine SET supplier_count=supplier_count+1 WHERE id=medicineID;
    
    -- Update supplier's medicine count
    UPDATE supplier SET medicine_count=medicine_count+returnVal WHERE id=medicineSupplierID;
    
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `suppliermedicine_check_exist` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `suppliermedicine_check_exist`(
IN medicineId int,
IN supplierID int,
OUT exist int
)
BEGIN
SELECT count(*)  INTO exist  FROM supplier_medicine WHERE medicine_id=medicineId AND supplier_id=supplierID;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `suppliermedicine_check_exist_by_mid` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `suppliermedicine_check_exist_by_mid`(
IN supplierMedicineID int,
OUT exist int
)
BEGIN
SELECT count(*)  INTO exist  FROM supplier_medicine WHERE id=supplierMedicineID;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `suppliermedicine_delete` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `suppliermedicine_delete`(
IN supplierMedicineID int,
OUT returnVal int
)
BEGIN
DECLARE medicineID varchar(50);
DECLARE supplierID INT; 
DECLARE tempCount INT;

-- Get old supplierID and medicineID of the supplier_medicine
SELECT supplier_id, medicine_id INTO supplierID, medicineID FROM supplier_medicine WHERE id = supplierMedicineID; 

-- delete the medicine
DELETE FROM supplier_medicine WHERE id = supplierMedicineID; 
SET returnVal=row_count();

IF (returnVal!=0) THEN
    -- Update medicine_count of the supplier
    SELECT medicine_count INTO tempCount FROM supplier WHERE id=supplierID;
    IF (tempCount>=returnVal) THEN
        UPDATE supplier SET medicine_count=medicine_count-returnVal WHERE id=supplierID;
    ELSE
        UPDATE supplier SET medicine_count=0 WHERE id=supplierID;
    END IF;
    
    -- Update the supplier_count of the medicine
    SELECT supplier_count INTO tempCount FROM medicine WHERE id=medicineID;
    IF(tempCount >= 1) THEN
        UPDATE medicine SET supplier_count=supplier_count-1 WHERE id=medicineID;
    ELSE
        UPDATE medicine SET supplier_count=0 WHERE id=medicineID;
    END IF;

END IF;


    
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `suppliermedicine_delete_by_mid` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `suppliermedicine_delete_by_mid`(
IN medicineID int,
OUT returnVal int
)
BEGIN
DECLARE supplierMedicineId INT;
DECLARE supplierID INT;
DECLARE tempCount INT;
DECLARE done INT DEFAULT FALSE;
DECLARE cur_supplierMedicine CURSOR for select id, supplier_id 
from supplier_medicine WHERE medicine_id=medicineID;  
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

SET returnVal = 0;
open cur_supplierMedicine;  
read_loop: LOOP 
    fetch cur_supplierMedicine into supplierMedicineId, supplierID;  
    IF done THEN
      IF (returnVal = 0) THEN
        SET returnVal = 1;
      END IF;
      
      LEAVE read_loop;
    END IF;
    
    -- delete the medicine
    DELETE FROM supplier_medicine WHERE id=supplierMedicineId;
    SET returnVal = returnVal + 1;
    
    -- Update medicine_count of the supplier
    IF (supplierID >= 0) THEN
        SELECT medicine_count INTO tempCount FROM supplier WHERE id=supplierID;
        IF (tempCount>=1) THEN
            UPDATE supplier SET medicine_count=medicine_count-1 WHERE id=supplierID;
        ELSE
            UPDATE supplier SET medicine_count=0 WHERE id=supplierID;
        END IF;
    END IF;
   
    -- Update the supplier_count of the medicine
    IF (medicineID >= 0) THEN
        SELECT supplier_count INTO tempCount FROM medicine WHERE id=medicineID;
        IF(tempCount >= 1) THEN
            UPDATE medicine SET supplier_count=supplier_count-1 WHERE id=medicineID;
        ELSE
            UPDATE medicine SET supplier_count=0 WHERE id=medicineID;
        END IF;
    END IF;

END LOOP; 
close cur_supplierMedicine;  

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `suppliermedicine_delete_by_msid` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `suppliermedicine_delete_by_msid`(
IN medicineID int,
IN supplierID int,
OUT returnVal int
)
BEGIN
DECLARE tempCount INT;

-- delete the medicine
SET @sqlString = 'DELETE FROM supplier_medicine';
SET @sqlString = CONCAT(@sqlString, ' WHERE supplier_id=',supplierID);
SET @sqlString = CONCAT(@sqlString, ' AND medicine_id=',medicineID);
PREPARE smtp FROM @sqlString;
EXECUTE smtp;

SET returnVal=row_count();

IF (returnVal!=0) THEN
    -- Update medicine_count of the supplier
    IF (supplierID >= 0) THEN
        SELECT medicine_count INTO tempCount FROM supplier WHERE id=supplierID;
        IF (tempCount>=returnVal) THEN
            UPDATE supplier SET medicine_count=medicine_count-returnVal WHERE id=supplierID;
        ELSE
            UPDATE supplier SET medicine_count=0 WHERE id=supplierID;
        END IF;
    END IF;
    
    -- Update the supplier_count of the medicine
    IF (medicineID >= 0) THEN
        SELECT supplier_count INTO tempCount FROM medicine WHERE id=medicineID;
        IF(tempCount >= 1) THEN
            UPDATE medicine SET supplier_count=supplier_count-1 WHERE id=medicineID;
        ELSE
            UPDATE medicine SET supplier_count=0 WHERE id=medicineID;
        END IF;
    END IF;
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `suppliermedicine_delete_by_sid` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `suppliermedicine_delete_by_sid`(
IN supplierID int,
OUT returnVal int
)
BEGIN
DECLARE supplierMedicineId INT;
DECLARE medicineID INT;
DECLARE tempCount INT;
DECLARE done INT DEFAULT FALSE;
DECLARE cur_supplierMedicine CURSOR for select id, medicine_id 
from supplier_medicine WHERE supplier_id=supplierID;  
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

SET returnVal = 0;
open cur_supplierMedicine;  
read_loop: LOOP 
    fetch cur_supplierMedicine into supplierMedicineId, medicineID;  
    IF done THEN
      IF (returnVal = 0) THEN
        SET returnVal = 1;
      END IF;
      LEAVE read_loop;
    END IF;
    
    -- delete the medicine
    DELETE FROM supplier_medicine WHERE id=supplierMedicineId;
    SET returnVal = returnVal + 1;
    
    -- Update medicine_count of the supplier
    IF (supplierID >= 0) THEN
        SELECT medicine_count INTO tempCount FROM supplier WHERE id=supplierID;
        IF (tempCount>=1) THEN
            UPDATE supplier SET medicine_count=medicine_count-1 WHERE id=supplierID;
        ELSE
            UPDATE supplier SET medicine_count=0 WHERE id=supplierID;
        END IF;
    END IF;
   
    -- Update the supplier_count of the medicine
    IF (medicineID >= 0) THEN
        SELECT supplier_count INTO tempCount FROM medicine WHERE id=medicineID;
        IF(tempCount >= 1) THEN
            UPDATE medicine SET supplier_count=supplier_count-1 WHERE id=medicineID;
        ELSE
            UPDATE medicine SET supplier_count=0 WHERE id=medicineID;
        END IF;
    END IF;

END LOOP; 
close cur_supplierMedicine;  

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `suppliermedicine_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `suppliermedicine_get`(
IN supplierID int,
IN medicineSN varchar(100),
IN medicineName varchar(100),
IN medicineVendorID int,
IN numPerPage int,
IN pageNum int,
OUT totalNum int,
OUT totalPage int)
BEGIN
DECLARE offset int;

IF (pageNum >= 0 && numPerPage > 0) THEN
    SET offset = numPerPage*pageNum;
    
    SET @countSqlString = 'SELECT COUNT(*) INTO @totalNum FROM view_supplier_medicine WHERE 1=1';
    SET @sqlString = 'SELECT * FROM view_supplier_medicine WHERE 1=1';
    IF (supplierID>=0 && supplierID is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND supplier_id=',supplierID);
        SET @sqlString = CONCAT(@sqlString, ' AND supplier_id=',supplierID);
    END IF;
	  IF (medicineSN!='' && medicineSN is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_sn=\'',medicineSN, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND medicine_sn=\'',medicineSN, '\'');
    END IF;
     IF (medicineName!='' && medicineName is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_name LIKE \'',medicineName, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND medicine_name LIKE \'',medicineName, '\'');
    END IF;
    IF (medicineVendorID>=0 && medicineVendorID is not null) THEN
       SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_vendor_id=',medicineVendorID);
       SET @sqlString = CONCAT(@sqlString, ' AND medicine_vendor_id=',medicineVendorID);
    END IF;
    SET @sqlString = CONCAT(@sqlString, ' LIMIT ',offset,',', numPerPage);

    PREPARE smtp FROM @countSqlString;
    EXECUTE smtp;
    SET totalNum=@totalNum;
    SET totalPage = (totalNum - 1) / numPerPage + 1;
    
    PREPARE smtp FROM @sqlString;
    EXECUTE smtp;
    
END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `suppliermedicine_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `suppliermedicine_select`(
IN supplierMedicineID int)
BEGIN

SELECT * FROM supplier_medicine WHERE id=supplierMedicineID;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `suppliermedicine_select_by_mid` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `suppliermedicine_select_by_mid`(
IN medicineID INT,
IN supplierID INT)
BEGIN

SELECT * FROM supplier_medicine WHERE medicine_id=medicineID AND supplier_id=supplierID;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `suppliermedicine_update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `suppliermedicine_update`(
IN supplierMedicineId int,
IN medicineID varchar(50),
IN medicineSupplierID int,
IN purPrice double,
OUT returnVal int)
BEGIN
DECLARE oldMedicineID varchar(50);
DECLARE oldSupplierID INT; 
DECLARE tempCount INT;

-- Get old supplierID and vendorID of the supplier_medicine
SELECT supplier_id, medicine_id INTO oldSupplierID, oldMedicineID FROM supplier_medicine WHERE id = supplierMedicineId; 

-- Update the supplier_medicine
UPDATE supplier_medicine SET medicine_id=medicineID, supplier_id=medicineSupplierID, pur_price=purPrice, modify_time=now() WHERE id=supplierMedicineId;
SET returnVal=row_count();

IF (returnVal != 0) THEN
    -- Update the supplier_medicine of the old supplier and new supplier
    if (oldSupplierID != medicineSupplierID) THEN
        SELECT medicine_count INTO tempCount FROM supplier WHERE id = oldSupplierID;
        IF (tempCount >= returnVal) THEN
            UPDATE supplier SET medicine_count=medicine_count-returnVal WHERE id=oldSupplierID;
        ELSE 
            UPDATE supplier SET medicine_count=0 WHERE id=oldSupplierID;
        END IF;
        UPDATE supplier SET medicine_count=medicine_count+returnVal WHERE id=medicineSupplierID;
    END IF;
    
    if (oldMedicineID != medicineID) THEN
        SELECT supplier_count INTO tempCount FROM medicine WHERE id = oldMedicineID;
        IF(tempCount >= 1) THEN
            UPDATE medicine SET supplier_count=supplier_count-1 WHERE id=oldMedicineID;
        ELSE
            UPDATE medicine SET supplier_count=0 WHERE id=oldMedicineID;
        END IF;
        UPDATE medicine SET supplier_count=supplier_count+1 WHERE id=medicineID;
    END IF;
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `supplier_add` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `supplier_add`(
IN supplierName varchar(100),
IN supplierContact varchar(45),
IN supplierTelephone varchar(45),
IN supplierAddress varchar(100),
OUT returnVal int)
BEGIN
INSERT INTO supplier (name, contact, tel, address, create_time, modify_time) VALUES (supplierName, supplierContact, supplierTelephone, supplierAddress, now(), now());
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `supplier_check_exist` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `supplier_check_exist`(
IN supplierID int,
IN supplierName varchar(100),
OUT exist int
)
BEGIN
IF (supplierName='' || supplierName is null) THEN
        SELECT count(*)  INTO exist  FROM supplier WHERE id=supplierID;
    ELSE
        SELECT count(*)  INTO exist  FROM supplier WHERE id=supplierID AND name=supplierName;
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `supplier_check_others_exist` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `supplier_check_others_exist`(
IN currentID int,
IN supplierName varchar(100),
OUT exist int
)
BEGIN
IF (currentID is not null) THEN
    SELECT count(*)  INTO exist  FROM supplier WHERE name=supplierName AND id != currentID;
ELSE
    SELECT count(*)  INTO exist  FROM supplier WHERE name=supplierName;
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `supplier_delete` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `supplier_delete`(
IN supplierID int,
OUT returnVal int
)
BEGIN
DELETE FROM supplier WHERE id = supplierID; 
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `supplier_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `supplier_get`(
IN subName varchar(100),
IN numPerPage int,
IN pageNum int,
OUT totalNum int,
OUT totalPage int)
BEGIN
DECLARE offset int;

IF (pageNum >= 0 && numPerPage > 0) THEN

    SET offset = numPerPage*pageNum;

    IF (subName='' || subName is null) THEN
        SELECT COUNT(*) INTO totalNum FROM supplier ORDER BY id DESC;
        SELECT * FROM supplier ORDER BY id DESC LIMIT offset,numPerPage;
    ELSE
        SELECT COUNT(*) INTO totalNum FROM supplier WHERE name REGEXP subName ORDER BY id DESC;
        SELECT * FROM supplier WHERE name REGEXP subName ORDER BY id DESC LIMIT offset,numPerPage;
    END IF;

    SET totalPage = (totalNum - 1) / numPerPage + 1;

END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `supplier_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `supplier_select`(
IN supplierID int)
BEGIN

SELECT * FROM supplier WHERE id=supplierID;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `supplier_update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `supplier_update`(
IN supplierId int,
IN supplierName varchar(100),
IN supplierContact varchar(45),
IN supplierTelephone varchar(45),
IN supplierAddress varchar(100),
OUT returnVal int)
BEGIN
UPDATE supplier SET name=supplierName, contact=supplierContact, tel=supplierTelephone, address=supplierAddress, modify_time=now() WHERE id=supplierID;
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `user_add` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `user_add`(
IN userUID varchar(50),
IN userPassword varchar(50),
IN userName varchar(50),
IN userRandomkey varchar(50),
IN userRole int,
OUT returnVal int)
BEGIN
INSERT INTO user (uid, pwd, name, random_key, role_id, create_time) VALUES (userUID, userPassword, userName, userRandomkey, userRole, now());
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `user_check_exist` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `user_check_exist`(
IN userUID varchar(50),
OUT exist int
)
BEGIN
    SELECT count(*)  INTO exist  FROM user WHERE uid=userUID;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `user_delete` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `user_delete`(
IN userID int,
OUT returnVal int
)
BEGIN
DELETE FROM user WHERE id = userID; 
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `user_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `user_get`(
IN subString varchar(50),
IN userRole int,
IN numPerPage int,
IN pageNum int,
OUT totalNum int,
OUT totalPage int)
BEGIN
DECLARE offset int;

IF (pageNum >= 0 && numPerPage > 0) THEN
    SET offset = numPerPage*pageNum;
    
    SET @countSqlString = 'SELECT COUNT(*) INTO @totalNum FROM user WHERE 1=1';
    SET @sqlString = 'SELECT id, uid,name,role_id,create_time FROM user WHERE 1=1';
    IF (subString!='' && subString is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND name REGEXP \'',subString, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND name REGEXP \'',subString, '\'');
    END IF;
    IF (userRole != -1 && userRole is not null) THEN
       SET @countSqlString = CONCAT(@countSqlString, ' AND role_id=',userRole);
       SET @sqlString = CONCAT(@sqlString, ' AND role_id=',userRole);
    END IF;
    SET @sqlString = CONCAT(@sqlString, ' LIMIT ',offset,',', numPerPage);

    PREPARE smtp FROM @countSqlString;
    EXECUTE smtp;
    SET totalNum = @totalNum;
    SET totalPage = (totalNum - 1) / numPerPage + 1;
    
    PREPARE smtp FROM @sqlString;
    EXECUTE smtp;
    
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `user_role_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `user_role_get`(
)
BEGIN
SELECT * FROM user_role;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `user_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `user_select`(
IN userUID varchar(100)
)
BEGIN

SELECT id,uid,name,role_id, create_time  FROM user WHERE uid=userUID;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `user_update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `user_update`(
IN userID int,
IN userUID varchar(50),
IN userName varchar(50),
IN userRole int,
OUT returnVal int)
BEGIN
UPDATE user SET uid=userUID, name=userName, role_id=userRole WHERE id=userID;
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `vendor_add` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `vendor_add`(
IN vendorName varchar(100),
IN vendorTelephone varchar(45),
IN vendorAddress varchar(100),
OUT vendorID int,
OUT returnVal int)
BEGIN
INSERT INTO vendor (name, tel, address, create_time, modify_time) VALUES (vendorName, vendorTelephone, vendorAddress, now(), now());
SELECT last_insert_id() INTO vendorID FROM vendor LIMIT 1;
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `vendor_check_exist` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `vendor_check_exist`(
IN vendorID int,
IN vendorName varchar(100),
OUT exist int
)
BEGIN
    IF (vendorName='' || vendorName is null) THEN
        SELECT count(*)  INTO exist  FROM vendor WHERE id=vendorID;
    ELSE
        SELECT count(*)  INTO exist  FROM vendor WHERE id=vendorID AND name=vendorName;
    END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `vendor_check_others_exist` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `vendor_check_others_exist`(
IN currentID int,
IN vendorName varchar(100),
OUT exist int
)
BEGIN
IF (currentID is not null) THEN
    SELECT count(*)  INTO exist  FROM vendor WHERE name=vendorName AND id != currentID;
ELSE
    SELECT count(*)  INTO exist  FROM vendor WHERE name=vendorName;
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `vendor_delete` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `vendor_delete`(
IN vendorID int,
OUT returnVal int
)
BEGIN
DELETE FROM vendor WHERE id = vendorID; 
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `vendor_get` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `vendor_get`(
IN subName varchar(100),
IN numPerPage int,
IN pageNum int,
OUT totalNum int,
OUT totalPage int)
BEGIN
DECLARE offset int;

IF (pageNum >= 0 && numPerPage > 0) THEN
    SET offset = numPerPage*pageNum;
    
    IF (subName='' || subName is null) THEN
        SELECT COUNT(*) INTO totalNum FROM vendor ORDER BY id DESC;
        SELECT * FROM vendor ORDER BY id DESC LIMIT offset,numPerPage;
    ELSE
        SELECT COUNT(*) INTO totalNum FROM vendor WHERE name REGEXP subName ORDER BY id DESC;
        SELECT * FROM vendor WHERE name REGEXP subName ORDER BY id DESC LIMIT offset,numPerPage;
    END IF;
    
    SET totalPage = (totalNum - 1) / numPerPage + 1;
    
END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `vendor_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `vendor_select`(
IN vendorID int)
BEGIN

SELECT * FROM vendor WHERE id=vendorID;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `vendor_select_by_name` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `vendor_select_by_name`(
IN vendorName int)
BEGIN

SELECT * FROM vendor WHERE name=vendorName;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `vendor_update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `vendor_update`(
IN vendorId int,
IN vendorName varchar(100),
IN vendorTelephone varchar(45),
IN vendorAddress varchar(100),
OUT returnVal int)
BEGIN
UPDATE vendor SET name=vendorName, tel=vendorTelephone, address=vendorAddress, modify_time=now() WHERE id=vendorId;
SET returnVal=row_count();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-05-23 21:20:59
