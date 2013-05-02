CREATE DATABASE  IF NOT EXISTS `store` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `store`;
-- MySQL dump 10.13  Distrib 5.5.16, for Win32 (x86)
--
-- Host: localhost    Database: store
-- ------------------------------------------------------
-- Server version	5.5.24

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
  `medicine_spec` varchar(100),
  `medicine_vendor_name` varchar(100),
  `medicine_num` int(11),
  `medicine_unit_name` varchar(45),
  `pur_price` double,
  `create_time` datetime,
  `modify_time` datetime,
  `batch_num` varchar(100),
  `product_date` datetime,
  `expire_date` datetime
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
  `unit_name` varchar(45),
  `medicine_price` double,
  `medicine_num` int(11),
  `retail_price` double
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
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

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
-- Table structure for table `medicine`
--

DROP TABLE IF EXISTS `medicine`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `medicine` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `sn` varchar(100) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL DEFAULT '',
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
  PRIMARY KEY (`id`),
  UNIQUE KEY `SN_UNIQUE` (`sn`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

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
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

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
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `store_by_batch`
--

DROP TABLE IF EXISTS `store_by_batch`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `store_by_batch` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `medicine_batch_id` int(11) DEFAULT NULL,
  `medicine_num` int(11) DEFAULT NULL,
  `create_time` datetime DEFAULT NULL,
  `modify_time` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `medicine_batch_id_UNIQUE` (`medicine_batch_id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

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
-- Table structure for table `medicine_type`
--

DROP TABLE IF EXISTS `medicine_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `medicine_type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `medicine_batch`
--

DROP TABLE IF EXISTS `medicine_batch`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `medicine_batch` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `medicine_id` int(11) DEFAULT NULL,
  `batch_num` varchar(100) DEFAULT NULL,
  `product_date` datetime DEFAULT NULL,
  `expire_date` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `purchase`
--

DROP TABLE IF EXISTS `purchase`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `purchase` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) DEFAULT NULL,
  `medicine_num` int(11) DEFAULT NULL,
  `pur_price` double DEFAULT NULL,
  `create_time` datetime DEFAULT NULL,
  `modify_time` datetime DEFAULT NULL,
  `batch_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=37 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

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
  `supplier_count` int(11)
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

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
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

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
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

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
-- Table structure for table `retail_item`
--

DROP TABLE IF EXISTS `retail_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `retail_item` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `retail_id` int(11) DEFAULT NULL,
  `medicine_id` int(11) DEFAULT NULL,
  `medicine_num` int(11) DEFAULT NULL,
  `medicine_price` double DEFAULT NULL,
  `retail_price` double DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

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
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

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
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

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
/*!50001 VIEW `view_purchase` AS select `a`.`id` AS `id`,`a`.`user_id` AS `user_id`,`d`.`uid` AS `user_uid`,`d`.`name` AS `user_name`,`c`.`id` AS `medicine_id`,`c`.`sn` AS `medicine_sn`,`c`.`name` AS `medicine_name`,`c`.`spec` AS `medicine_spec`,`c`.`vendor_name` AS `medicine_vendor_name`,`a`.`medicine_num` AS `medicine_num`,`c`.`unit_name` AS `medicine_unit_name`,`a`.`pur_price` AS `pur_price`,`a`.`create_time` AS `create_time`,`a`.`modify_time` AS `modify_time`,`b`.`batch_num` AS `batch_num`,`b`.`product_date` AS `product_date`,`b`.`expire_date` AS `expire_date` from (((`purchase` `a` left join `medicine_batch` `b` on((`a`.`batch_id` = `b`.`id`))) left join `view_medicine` `c` on((`b`.`medicine_id` = `c`.`id`))) left join `user` `d` on((`a`.`user_id` = `d`.`id`))) */;
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
/*!50001 VIEW `view_retail_item` AS select `a`.`id` AS `id`,`a`.`retail_id` AS `retail_id`,`a`.`medicine_id` AS `medicine_id`,`b`.`sn` AS `medicine_sn`,`b`.`name` AS `medicine_name`,`b`.`unit_name` AS `unit_name`,`a`.`medicine_price` AS `medicine_price`,`a`.`medicine_num` AS `medicine_num`,`a`.`retail_price` AS `retail_price` from (`retail_item` `a` left join `view_medicine` `b` on((`a`.`medicine_id` = `b`.`id`))) */;
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
/*!50001 VIEW `view_medicine` AS select `a`.`id` AS `id`,`a`.`sn` AS `sn`,`a`.`name` AS `name`,`a`.`spec` AS `spec`,`a`.`vendor_id` AS `vendor_id`,`b`.`name` AS `vendor_name`,`a`.`create_time` AS `create_time`,`a`.`modify_time` AS `modify_time`,`a`.`unit_id` AS `unit_id`,`c`.`name` AS `unit_name`,`a`.`retail_price` AS `retail_price`,`a`.`type_id` AS `type_id`,`a`.`class_id` AS `class_id`,`a`.`otc_id` AS `otc_id`,`a`.`form_id` AS `form_id`,`a`.`supplier_count` AS `supplier_count` from ((`medicine` `a` left join `vendor` `b` on((`a`.`vendor_id` = `b`.`id`))) left join `medicine_unit` `c` on((`a`.`unit_id` = `c`.`id`))) */;
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
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-05-02 10:16:05
