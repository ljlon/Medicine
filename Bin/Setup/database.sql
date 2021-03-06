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
-- Table structure for table `medicine`
--

DROP TABLE IF EXISTS `medicine`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `medicine` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `sn` varchar(100) NOT NULL,
  `name` varchar(100) NOT NULL,
  `spec` varchar(100) DEFAULT NULL,
  `vendor_id` int(11) DEFAULT NULL,
  `create_time` datetime DEFAULT NULL,
  `modify_time` datetime DEFAULT NULL,
  `unit_id` int(11) DEFAULT NULL,
  `retail_price` double DEFAULT NULL,
  `type_id` int(11) DEFAULT NULL,
  `class_id` int(11) DEFAULT NULL,
  `otc_id` int(11) DEFAULT NULL,
  `form_id` int(11) DEFAULT NULL,
  `supplier_count` int(11) DEFAULT '0',
  `reg_num` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `SN_UNIQUE` (`sn`)
) ENGINE=InnoDB AUTO_INCREMENT=1045 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `medicine`
--

LOCK TABLES `medicine` WRITE;
/*!40000 ALTER TABLE `medicine` DISABLE KEYS */;
/*!40000 ALTER TABLE `medicine` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `medicine_batch`
--

DROP TABLE IF EXISTS `medicine_batch`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `medicine_batch` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `medicine_id` int(11) NOT NULL,
  `batch_num` varchar(100) NOT NULL,
  `product_date` datetime DEFAULT NULL,
  `expire_date` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1893 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `medicine_batch`
--

LOCK TABLES `medicine_batch` WRITE;
/*!40000 ALTER TABLE `medicine_batch` DISABLE KEYS */;
/*!40000 ALTER TABLE `medicine_batch` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `medicine_class`
--

DROP TABLE IF EXISTS `medicine_class`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `medicine_class` (
  `id` int(11) NOT NULL,
  `name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `medicine_class`
--

LOCK TABLES `medicine_class` WRITE;
/*!40000 ALTER TABLE `medicine_class` DISABLE KEYS */;
/*!40000 ALTER TABLE `medicine_class` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `medicine_form`
--

DROP TABLE IF EXISTS `medicine_form`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `medicine_form` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `medicine_form`
--

LOCK TABLES `medicine_form` WRITE;
/*!40000 ALTER TABLE `medicine_form` DISABLE KEYS */;
INSERT INTO `medicine_form` VALUES (0,'片剂'),(1,'胶囊剂'),(2,'注射剂'),(3,'颗粒剂'),(4,'溶液剂'),(5,'粉剂'),(6,'滴剂'),(7,'散剂'),(8,'贴剂'),(9,'涂剂'),(10,'膏剂'),(11,'霜剂'),(12,'丸剂'),(13,'凝胶剂'),(14,'喷雾剂'),(15,'洗剂'),(16,'栓剂'),(17,'其他剂型');
/*!40000 ALTER TABLE `medicine_form` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `medicine_otc`
--

DROP TABLE IF EXISTS `medicine_otc`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `medicine_otc` (
  `id` int(11) NOT NULL,
  `name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `medicine_otc`
--

LOCK TABLES `medicine_otc` WRITE;
/*!40000 ALTER TABLE `medicine_otc` DISABLE KEYS */;
INSERT INTO `medicine_otc` VALUES (0,'OTC类'),(1,'处方类');
/*!40000 ALTER TABLE `medicine_otc` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `medicine_type`
--

DROP TABLE IF EXISTS `medicine_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `medicine_type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `medicine_type`
--

LOCK TABLES `medicine_type` WRITE;
/*!40000 ALTER TABLE `medicine_type` DISABLE KEYS */;
INSERT INTO `medicine_type` VALUES (0,'中成药'),(1,'保健药'),(2,'中草药'),(3,'西药'),(4,'医疗器械');
/*!40000 ALTER TABLE `medicine_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `medicine_unit`
--

DROP TABLE IF EXISTS `medicine_unit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `medicine_unit` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `medicine_unit`
--

LOCK TABLES `medicine_unit` WRITE;
/*!40000 ALTER TABLE `medicine_unit` DISABLE KEYS */;
INSERT INTO `medicine_unit` VALUES (0,'盒'),(1,'瓶'),(2,'袋'),(3,'支');
/*!40000 ALTER TABLE `medicine_unit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pc`
--

DROP TABLE IF EXISTS `pc`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pc` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pc_mac` varchar(45) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `pc_mac_UNIQUE` (`pc_mac`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pc`
--

LOCK TABLES `pc` WRITE;
/*!40000 ALTER TABLE `pc` DISABLE KEYS */;
INSERT INTO `pc` VALUES (2,'60eb6918f10a');
/*!40000 ALTER TABLE `pc` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pos`
--

DROP TABLE IF EXISTS `pos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pos` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pc_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `pos_no_UNIQUE` (`pc_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pos`
--

LOCK TABLES `pos` WRITE;
/*!40000 ALTER TABLE `pos` DISABLE KEYS */;
INSERT INTO `pos` VALUES (2,2);
/*!40000 ALTER TABLE `pos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `purchase`
--

DROP TABLE IF EXISTS `purchase`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `purchase` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `medicine_num` int(11) NOT NULL,
  `pur_price` double NOT NULL,
  `create_time` datetime DEFAULT NULL,
  `purchase_time` datetime DEFAULT NULL,
  `batch_id` int(11) NOT NULL,
  `supplier_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=982 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `purchase`
--

LOCK TABLES `purchase` WRITE;
/*!40000 ALTER TABLE `purchase` DISABLE KEYS */;
/*!40000 ALTER TABLE `purchase` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `retail`
--

DROP TABLE IF EXISTS `retail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `retail` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) DEFAULT NULL,
  `create_time` datetime DEFAULT NULL,
  `total_price` double DEFAULT NULL,
  `in_price` double DEFAULT NULL,
  `out_price` double DEFAULT NULL,
  `sn` varchar(100) DEFAULT NULL,
  `pc_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `retail`
--

LOCK TABLES `retail` WRITE;
/*!40000 ALTER TABLE `retail` DISABLE KEYS */;
/*!40000 ALTER TABLE `retail` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `retail_item`
--

DROP TABLE IF EXISTS `retail_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `retail_item` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `retail_id` int(11) DEFAULT NULL,
  `medicine_id` int(11) DEFAULT NULL,
  `medicine_batch_num` varchar(100) DEFAULT NULL,
  `medicine_num` int(11) DEFAULT NULL,
  `medicine_price` double DEFAULT NULL,
  `retail_price` double DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `retail_item`
--

LOCK TABLES `retail_item` WRITE;
/*!40000 ALTER TABLE `retail_item` DISABLE KEYS */;
/*!40000 ALTER TABLE `retail_item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `store_by_batch`
--

DROP TABLE IF EXISTS `store_by_batch`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `store_by_batch` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `medicine_batch_id` int(11) NOT NULL,
  `medicine_num` int(11) NOT NULL,
  `create_time` datetime DEFAULT NULL,
  `modify_time` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `medicine_batch_id_UNIQUE` (`medicine_batch_id`)
) ENGINE=InnoDB AUTO_INCREMENT=1895 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `store_by_batch`
--

LOCK TABLES `store_by_batch` WRITE;
/*!40000 ALTER TABLE `store_by_batch` DISABLE KEYS */;
/*!40000 ALTER TABLE `store_by_batch` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `supplier`
--

DROP TABLE IF EXISTS `supplier`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `supplier` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `contact` varchar(45) NOT NULL,
  `tel` varchar(45) DEFAULT NULL,
  `address` varchar(45) DEFAULT NULL,
  `medicine_count` int(11) DEFAULT '0',
  `create_time` datetime DEFAULT NULL,
  `modify_time` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_UNIQUE` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `supplier`
--

LOCK TABLES `supplier` WRITE;
/*!40000 ALTER TABLE `supplier` DISABLE KEYS */;
/*!40000 ALTER TABLE `supplier` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `supplier_medicine`
--

DROP TABLE IF EXISTS `supplier_medicine`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `supplier_medicine` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `medicine_id` int(11) NOT NULL,
  `supplier_id` int(11) NOT NULL,
  `create_time` datetime DEFAULT NULL,
  `modify_time` datetime DEFAULT NULL,
  `pur_price` double DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=888 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `supplier_medicine`
--

LOCK TABLES `supplier_medicine` WRITE;
/*!40000 ALTER TABLE `supplier_medicine` DISABLE KEYS */;
/*!40000 ALTER TABLE `supplier_medicine` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uid` varchar(50) NOT NULL,
  `pwd` varchar(50) DEFAULT NULL,
  `name` varchar(50) DEFAULT NULL,
  `random_key` varchar(50) DEFAULT NULL,
  `role_id` int(11) DEFAULT '0',
  `create_time` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `uid_UNIQUE` (`uid`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (0,'0000','4df3cb619d95b5c03c64373541d022ff','管理员','090DD3E5',0,'2012-11-09 11:33:23');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_role`
--

DROP TABLE IF EXISTS `user_role`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_role` (
  `id` int(11) NOT NULL,
  `name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_role`
--

LOCK TABLES `user_role` WRITE;
/*!40000 ALTER TABLE `user_role` DISABLE KEYS */;
INSERT INTO `user_role` VALUES (0,'超级管理员'),(1,'管理员'),(2,'录入员'),(3,'收银员');
/*!40000 ALTER TABLE `user_role` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vendor`
--

DROP TABLE IF EXISTS `vendor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vendor` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `tel` varchar(45) DEFAULT NULL,
  `address` varchar(100) DEFAULT NULL,
  `medicine_count` int(11) DEFAULT '0',
  `create_time` datetime DEFAULT NULL,
  `modify_time` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  UNIQUE KEY `name_UNIQUE` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=520 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vendor`
--

LOCK TABLES `vendor` WRITE;
/*!40000 ALTER TABLE `vendor` DISABLE KEYS */;
/*!40000 ALTER TABLE `vendor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `view_medicine`
--

DROP TABLE IF EXISTS `view_medicine`;
/*!50001 DROP VIEW IF EXISTS `view_medicine`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `view_medicine` (
  `id` int(11),
  `sn` varchar(100),
  `name` varchar(100),
  `spec` varchar(100),
  `vendor_id` int(11),
  `vendor_name` varchar(100),
  `create_time` datetime,
  `modify_time` datetime,
  `unit_id` int(11),
  `unit_name` varchar(45),
  `retail_price` double,
  `type_id` int(11),
  `class_id` int(11),
  `otc_id` int(11),
  `form_id` int(11),
  `form_name` varchar(45),
  `supplier_count` int(11),
  `reg_num` varchar(100)
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `view_pos`
--

DROP TABLE IF EXISTS `view_pos`;
/*!50001 DROP VIEW IF EXISTS `view_pos`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `view_pos` (
  `id` int(11),
  `pc_id` int(11),
  `pc_mac` varchar(45)
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `view_purchase`
--

DROP TABLE IF EXISTS `view_purchase`;
/*!50001 DROP VIEW IF EXISTS `view_purchase`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `view_purchase` (
  `id` int(11),
  `user_id` int(11),
  `user_uid` varchar(50),
  `user_name` varchar(50),
  `medicine_id` int(11),
  `medicine_sn` varchar(100),
  `medicine_name` varchar(100),
  `medicine_form` varchar(45),
  `medicine_spec` varchar(100),
  `medicine_vendor_name` varchar(100),
  `medicine_num` int(11),
  `medicine_unit_name` varchar(45),
  `medicine_type_id` int(11),
  `pur_price` double,
  `create_time` datetime,
  `purchase_time` datetime,
  `batch_id` int(11),
  `batch_num` varchar(100),
  `product_date` datetime,
  `expire_date` datetime,
  `supplier_id` int(11),
  `supplier_name` varchar(45),
  `medicine_reg_num` varchar(100)
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `view_retail`
--

DROP TABLE IF EXISTS `view_retail`;
/*!50001 DROP VIEW IF EXISTS `view_retail`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `view_retail` (
  `id` int(11),
  `sn` varchar(100),
  `user_id` int(11),
  `user_uid` varchar(50),
  `user_name` varchar(50),
  `create_time` datetime,
  `total_price` double,
  `in_price` double,
  `out_price` double,
  `pos_id` int(11),
  `pc_id` int(11),
  `pc_mac` varchar(45)
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `view_retail_item`
--

DROP TABLE IF EXISTS `view_retail_item`;
/*!50001 DROP VIEW IF EXISTS `view_retail_item`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `view_retail_item` (
  `id` int(11),
  `retail_id` int(11),
  `medicine_id` int(11),
  `medicine_sn` varchar(100),
  `medicine_name` varchar(100),
  `medicine_vendor_name` varchar(100),
  `medicine_spec` varchar(100),
  `medicine_batch_num` varchar(100),
  `unit_name` varchar(45),
  `medicine_price` double,
  `medicine_num` int(11),
  `retail_price` double
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `view_store`
--

DROP TABLE IF EXISTS `view_store`;
/*!50001 DROP VIEW IF EXISTS `view_store`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `view_store` (
  `id` int(11),
  `medicine_id` int(11),
  `medicine_sn` varchar(100),
  `medicine_name` varchar(100),
  `medicine_spec` varchar(100),
  `vendor_id` int(11),
  `vendor_name` varchar(100),
  `retail_price` double,
  `medicine_unit_id` int(11),
  `medicine_unit_name` varchar(45),
  `medicine_num` decimal(32,0),
  `product_date` datetime,
  `expire_date` datetime,
  `create_time` datetime,
  `modify_time` datetime
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `view_store_by_batch`
--

DROP TABLE IF EXISTS `view_store_by_batch`;
/*!50001 DROP VIEW IF EXISTS `view_store_by_batch`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `view_store_by_batch` (
  `id` int(11),
  `medicine_id` int(11),
  `medicine_sn` varchar(100),
  `medicine_name` varchar(100),
  `medicine_spec` varchar(100),
  `vendor_name` varchar(100),
  `batch_num` varchar(100),
  `product_date` datetime,
  `expire_date` datetime,
  `retail_price` double,
  `medicine_unit_id` int(11),
  `medicine_unit_name` varchar(45),
  `medicine_num` int(11),
  `create_time` datetime,
  `modify_time` datetime
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `view_supplier_medicine`
--

DROP TABLE IF EXISTS `view_supplier_medicine`;
/*!50001 DROP VIEW IF EXISTS `view_supplier_medicine`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `view_supplier_medicine` (
  `id` int(11),
  `supplier_id` int(11),
  `pur_price` double,
  `create_time` datetime,
  `modify_time` datetime,
  `medicine_id` int(11),
  `medicine_sn` varchar(100),
  `medicine_name` varchar(100),
  `medicine_spec` varchar(100),
  `medicine_vendor_id` int(11),
  `medicine_vendor_name` varchar(100),
  `medicine_create_time` datetime,
  `medicine_modify_time` datetime,
  `medicine_unit_id` int(11),
  `medicine_unit_name` varchar(45),
  `medicine_retail_price` double,
  `medicine_type_id` int(11),
  `medicine_class_id` int(11),
  `medicine_otc_id` int(11),
  `medicine_form_id` int(11),
  `medicine_supplier_count` int(11)
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

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
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
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
IN regNum varchar(100),
OUT returnVal int)
BEGIN
-- Insert into Medicine
INSERT INTO medicine (sn, name, spec, vendor_id, unit_id, retail_price, type_id, otc_id, form_id, reg_num, create_time, modify_time) 
	VALUES (medicineSN, medicineName, medicineSpec, medicineVendorID, unitID, retailPrice, typeID, OTCID, formID, regNum, now(), now());
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
    
    SET totalPage = floor((totalNum - 1) / numPerPage + 1);
    
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
	  SET totalPage = floor((totalNum - 1) / numPerPage + 1);
    
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
IN regNum varchar(100),
OUT returnVal int)
BEGIN
DECLARE oldVendorID INT;
DECLARE medicineCount INT;

-- Get old supplierID and vendorID of the medicine
SELECT vendor_id INTO oldVendorID FROM medicine WHERE id = oldID; 

-- Update the medicine
UPDATE medicine SET id=medicineID, sn=medicineSN, name=medicineName, spec=medicineSpec, vendor_id=medicineVendorID, unit_id=unitID, retail_price=retailPrice, type_id=typeID, otc_id=OTCID, form_id=formID, reg_num=regNum, modify_time=now() WHERE id=oldID;
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
    SET totalPage = floor((totalNum - 1) / numPerPage + 1);
    
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
IN purchaseDate datetime,
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
	INSERT INTO purchase (user_id, supplier_id, medicine_num, pur_price, create_time, purchase_time, batch_id) 
				VALUES (userID, supplierID, number, purPrice, now(), purchaseDate, batchID);
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
DECLARE medicineBatchID int;
DECLARE purMedicineNum int;
DECLARE storeMedicineNum int;

-- Update store
SELECT batch_id, medicine_num INTO medicineBatchID, purMedicineNum FROM view_purchase WHERE id=purchaseID;

IF (found_rows() != 0) THEN
    CALL store_add_num(medicineBatchID,-purMedicineNum, storeID, returnVal);
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
IN medicineTypeID varchar(100),
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
        SET @countSqlString = CONCAT(@countSqlString, ' AND DATEDIFF(purchase_time,\'',purDateBegin, '\')>=0');
        SET @sqlString = CONCAT(@sqlString, ' AND DATEDIFF(purchase_time,\'', purDateBegin,'\')>=0');
        SET @countSqlString = CONCAT(@countSqlString, ' AND DATEDIFF(purchase_time,\'', purDateEnd,'\')<=0');
        SET @sqlString = CONCAT(@sqlString, ' AND DATEDIFF(purchase_time,\'', purDateEnd,'\')<=0');
    END IF;
	  IF (medicineSN!='' && medicineSN is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_sn=\'',medicineSN, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND medicine_sn=\'',medicineSN, '\'');
    END IF;
    IF (medicineName!='' && medicineName is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_name LIKE \'',medicineName, '\'');
        SET @sqlString = CONCAT(@sqlString, ' AND medicine_name LIKE \'',medicineName, '\'');
    END IF;
    IF (medicineTypeID !='' && medicineTypeID is not null) THEN
        SET @countSqlString = CONCAT(@countSqlString, ' AND medicine_type_id IN (',medicineTypeID, ')');
        SET @sqlString = CONCAT(@sqlString, ' AND medicine_type_id IN (',medicineTypeID, ')');
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
    SET totalPage = floor((totalNum - 1) / numPerPage + 1);
    
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
    SET totalPage = floor((totalNum - 1) / numPerPage + 1);
        
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
IN medicineBatchNum varchar(100),
IN medicinePrice double,
IN medicineNum int,
IN retailPrice double,
OUT returnVal int)
BEGIN
DECLARE storeID int;
DECLARE storeRetVal int;

INSERT INTO retail_item (retail_id, medicine_id, medicine_batch_num, medicine_num, medicine_price, retail_price) 
	VALUES (retailID, medicineID, medicineBatchNum, medicineNum, medicinePrice, retailPrice);
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
    IF (addNum > 0) THEN
        INSERT INTO store_by_batch (medicine_batch_id,medicine_num, create_time, modify_time) 
            VALUES (batchID, addNum, now(), now());
    END IF;
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
    SET totalPage = floor((totalNum - 1) / numPerPage + 1);
    
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
    SET totalPage = floor((totalNum - 1) / numPerPage + 1);
    
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
    SET totalPage = floor((totalNum - 1) / numPerPage + 1);
    
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

    SET totalPage = floor((totalNum - 1) / numPerPage + 1);

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
    SET totalPage = floor((totalNum - 1) / numPerPage + 1);
    
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
    
    SET totalPage = floor((totalNum - 1) / numPerPage + 1);
    
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
IN vendorName varchar(100))
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

--
-- Final view structure for view `view_medicine`
--

/*!50001 DROP TABLE IF EXISTS `view_medicine`*/;
/*!50001 DROP VIEW IF EXISTS `view_medicine`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `view_medicine` AS select `a`.`id` AS `id`,`a`.`sn` AS `sn`,`a`.`name` AS `name`,`a`.`spec` AS `spec`,`a`.`vendor_id` AS `vendor_id`,`b`.`name` AS `vendor_name`,`a`.`create_time` AS `create_time`,`a`.`modify_time` AS `modify_time`,`a`.`unit_id` AS `unit_id`,`c`.`name` AS `unit_name`,`a`.`retail_price` AS `retail_price`,`a`.`type_id` AS `type_id`,`a`.`class_id` AS `class_id`,`a`.`otc_id` AS `otc_id`,`a`.`form_id` AS `form_id`,`d`.`name` AS `form_name`,`a`.`supplier_count` AS `supplier_count`,`a`.`reg_num` AS `reg_num` from (((`medicine` `a` left join `vendor` `b` on((`a`.`vendor_id` = `b`.`id`))) left join `medicine_unit` `c` on((`a`.`unit_id` = `c`.`id`))) left join `medicine_form` `d` on((`a`.`form_id` = `d`.`id`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `view_pos`
--

/*!50001 DROP TABLE IF EXISTS `view_pos`*/;
/*!50001 DROP VIEW IF EXISTS `view_pos`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `view_pos` AS select `a`.`id` AS `id`,`a`.`pc_id` AS `pc_id`,`b`.`pc_mac` AS `pc_mac` from (`pos` `a` left join `pc` `b` on((`a`.`pc_id` = `b`.`id`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `view_purchase`
--

/*!50001 DROP TABLE IF EXISTS `view_purchase`*/;
/*!50001 DROP VIEW IF EXISTS `view_purchase`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `view_purchase` AS select `a`.`id` AS `id`,`a`.`user_id` AS `user_id`,`d`.`uid` AS `user_uid`,`d`.`name` AS `user_name`,`c`.`id` AS `medicine_id`,`c`.`sn` AS `medicine_sn`,`c`.`name` AS `medicine_name`,`c`.`form_name` AS `medicine_form`,`c`.`spec` AS `medicine_spec`,`c`.`vendor_name` AS `medicine_vendor_name`,`a`.`medicine_num` AS `medicine_num`,`c`.`unit_name` AS `medicine_unit_name`,`c`.`type_id` AS `medicine_type_id`,`a`.`pur_price` AS `pur_price`,`a`.`create_time` AS `create_time`,`a`.`purchase_time` AS `purchase_time`,`a`.`batch_id` AS `batch_id`,`b`.`batch_num` AS `batch_num`,`b`.`product_date` AS `product_date`,`b`.`expire_date` AS `expire_date`,`e`.`id` AS `supplier_id`,`e`.`name` AS `supplier_name`,`c`.`reg_num` AS `medicine_reg_num` from ((((`purchase` `a` left join `medicine_batch` `b` on((`a`.`batch_id` = `b`.`id`))) left join `view_medicine` `c` on((`b`.`medicine_id` = `c`.`id`))) left join `user` `d` on((`a`.`user_id` = `d`.`id`))) left join `supplier` `e` on((`a`.`supplier_id` = `e`.`id`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `view_retail`
--

/*!50001 DROP TABLE IF EXISTS `view_retail`*/;
/*!50001 DROP VIEW IF EXISTS `view_retail`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `view_retail` AS select `a`.`id` AS `id`,`a`.`sn` AS `sn`,`a`.`user_id` AS `user_id`,`b`.`uid` AS `user_uid`,`b`.`name` AS `user_name`,`a`.`create_time` AS `create_time`,`a`.`total_price` AS `total_price`,`a`.`in_price` AS `in_price`,`a`.`out_price` AS `out_price`,`c`.`id` AS `pos_id`,`a`.`pc_id` AS `pc_id`,`c`.`pc_mac` AS `pc_mac` from ((`retail` `a` left join `user` `b` on((`a`.`user_id` = `b`.`id`))) left join `view_pos` `c` on((`a`.`pc_id` = `c`.`pc_id`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `view_retail_item`
--

/*!50001 DROP TABLE IF EXISTS `view_retail_item`*/;
/*!50001 DROP VIEW IF EXISTS `view_retail_item`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `view_retail_item` AS select `a`.`id` AS `id`,`a`.`retail_id` AS `retail_id`,`a`.`medicine_id` AS `medicine_id`,`b`.`sn` AS `medicine_sn`,`b`.`name` AS `medicine_name`,`b`.`vendor_name` AS `medicine_vendor_name`,`b`.`spec` AS `medicine_spec`,`a`.`medicine_batch_num` AS `medicine_batch_num`,`b`.`unit_name` AS `unit_name`,`a`.`medicine_price` AS `medicine_price`,`a`.`medicine_num` AS `medicine_num`,`a`.`retail_price` AS `retail_price` from (`retail_item` `a` left join `view_medicine` `b` on((`a`.`medicine_id` = `b`.`id`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `view_store`
--

/*!50001 DROP TABLE IF EXISTS `view_store`*/;
/*!50001 DROP VIEW IF EXISTS `view_store`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `view_store` AS select `a`.`id` AS `id`,`c`.`medicine_id` AS `medicine_id`,`b`.`sn` AS `medicine_sn`,`b`.`name` AS `medicine_name`,`b`.`spec` AS `medicine_spec`,`b`.`vendor_id` AS `vendor_id`,`b`.`vendor_name` AS `vendor_name`,`b`.`retail_price` AS `retail_price`,`b`.`unit_id` AS `medicine_unit_id`,`b`.`unit_name` AS `medicine_unit_name`,sum(`a`.`medicine_num`) AS `medicine_num`,min(`c`.`product_date`) AS `product_date`,min(`c`.`expire_date`) AS `expire_date`,min(`a`.`create_time`) AS `create_time`,max(`a`.`modify_time`) AS `modify_time` from ((`store_by_batch` `a` left join `medicine_batch` `c` on((`a`.`medicine_batch_id` = `c`.`id`))) left join `view_medicine` `b` on((`c`.`medicine_id` = `b`.`id`))) group by `b`.`id` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `view_store_by_batch`
--

/*!50001 DROP TABLE IF EXISTS `view_store_by_batch`*/;
/*!50001 DROP VIEW IF EXISTS `view_store_by_batch`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `view_store_by_batch` AS select `a`.`id` AS `id`,`c`.`medicine_id` AS `medicine_id`,`b`.`sn` AS `medicine_sn`,`b`.`name` AS `medicine_name`,`b`.`spec` AS `medicine_spec`,`b`.`vendor_name` AS `vendor_name`,`c`.`batch_num` AS `batch_num`,`c`.`product_date` AS `product_date`,`c`.`expire_date` AS `expire_date`,`b`.`retail_price` AS `retail_price`,`b`.`unit_id` AS `medicine_unit_id`,`b`.`unit_name` AS `medicine_unit_name`,`a`.`medicine_num` AS `medicine_num`,`a`.`create_time` AS `create_time`,`a`.`modify_time` AS `modify_time` from ((`store_by_batch` `a` left join `medicine_batch` `c` on((`a`.`medicine_batch_id` = `c`.`id`))) left join `view_medicine` `b` on((`c`.`medicine_id` = `b`.`id`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `view_supplier_medicine`
--

/*!50001 DROP TABLE IF EXISTS `view_supplier_medicine`*/;
/*!50001 DROP VIEW IF EXISTS `view_supplier_medicine`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `view_supplier_medicine` AS select `d`.`id` AS `id`,`d`.`supplier_id` AS `supplier_id`,`d`.`pur_price` AS `pur_price`,`d`.`create_time` AS `create_time`,`d`.`modify_time` AS `modify_time`,`a`.`id` AS `medicine_id`,`a`.`sn` AS `medicine_sn`,`a`.`name` AS `medicine_name`,`a`.`spec` AS `medicine_spec`,`a`.`vendor_id` AS `medicine_vendor_id`,`b`.`name` AS `medicine_vendor_name`,`a`.`create_time` AS `medicine_create_time`,`a`.`modify_time` AS `medicine_modify_time`,`a`.`unit_id` AS `medicine_unit_id`,`c`.`name` AS `medicine_unit_name`,`a`.`retail_price` AS `medicine_retail_price`,`a`.`type_id` AS `medicine_type_id`,`a`.`class_id` AS `medicine_class_id`,`a`.`otc_id` AS `medicine_otc_id`,`a`.`form_id` AS `medicine_form_id`,`a`.`supplier_count` AS `medicine_supplier_count` from (((`supplier_medicine` `d` left join `medicine` `a` on((`d`.`medicine_id` = `a`.`id`))) left join `vendor` `b` on((`a`.`vendor_id` = `b`.`id`))) left join `medicine_unit` `c` on((`a`.`unit_id` = `c`.`id`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-06-15 19:14:29
