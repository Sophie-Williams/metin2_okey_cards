
SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for okay_event
-- ----------------------------
DROP TABLE IF EXISTS `okay_event`;
CREATE TABLE `okay_event` (
  `pid` int(11) DEFAULT NULL,
  `name` varchar(11) DEFAULT NULL,
  `points` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
