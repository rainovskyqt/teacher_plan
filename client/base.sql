-- --------------------------------------------------------
-- Хост:                         127.0.0.1
-- Версия сервера:               8.4.0 - MySQL Community Server - GPL
-- Операционная система:         Win64
-- HeidiSQL Версия:              12.7.0.6850
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

-- Дамп структуры для таблица ordo_dev.department
DROP TABLE IF EXISTS `department`;
CREATE TABLE IF NOT EXISTS `department` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `department_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.department: ~3 rows (приблизительно)
INSERT INTO `department` (`id`, `name`) VALUES
	(3, 'Кафедра ТиМ СЕиТА'),
	(1, 'Кафедра ТиМ ФК'),
	(2, 'Кафедра ТиМ ЦВС');

-- Дамп структуры для таблица ordo_dev.disciline_department
DROP TABLE IF EXISTS `disciline_department`;
CREATE TABLE IF NOT EXISTS `disciline_department` (
  `id` int NOT NULL AUTO_INCREMENT,
  `discipline_id` int DEFAULT NULL,
  `department_id` int DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK__department` (`department_id`),
  KEY `FK_disciline_department_discipline` (`discipline_id`),
  CONSTRAINT `FK__department` FOREIGN KEY (`department_id`) REFERENCES `department` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_disciline_department_discipline` FOREIGN KEY (`discipline_id`) REFERENCES `discipline` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.disciline_department: ~2 rows (приблизительно)
INSERT INTO `disciline_department` (`id`, `discipline_id`, `department_id`) VALUES
	(1, 1, 1),
	(2, 2, 1);

-- Дамп структуры для таблица ordo_dev.discipline
DROP TABLE IF EXISTS `discipline`;
CREATE TABLE IF NOT EXISTS `discipline` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.discipline: ~2 rows (приблизительно)
INSERT INTO `discipline` (`id`, `name`) VALUES
	(1, 'Социология'),
	(2, 'Философия');

-- Дамп структуры для таблица ordo_dev.educational_work
DROP TABLE IF EXISTS `educational_work`;
CREATE TABLE IF NOT EXISTS `educational_work` (
  `id` int NOT NULL AUTO_INCREMENT,
  `teacher_plan_id` int DEFAULT NULL,
  `discipline_id` int DEFAULT NULL,
  `work_form_id` int DEFAULT NULL,
  `group_id` int DEFAULT NULL,
  `comments` text,
  PRIMARY KEY (`id`),
  KEY `FK_educational_work_discipline` (`discipline_id`),
  KEY `FK_educational_work_group` (`group_id`),
  KEY `FK_educational_work_work_form` (`work_form_id`),
  KEY `FK_educational_work_teacher_plan` (`teacher_plan_id`),
  CONSTRAINT `FK_educational_work_discipline` FOREIGN KEY (`discipline_id`) REFERENCES `discipline` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_educational_work_group` FOREIGN KEY (`group_id`) REFERENCES `group` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_educational_work_teacher_plan` FOREIGN KEY (`teacher_plan_id`) REFERENCES `teacher_plan` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_educational_work_work_form` FOREIGN KEY (`work_form_id`) REFERENCES `work_form` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.educational_work: ~1 rows (приблизительно)
INSERT INTO `educational_work` (`id`, `teacher_plan_id`, `discipline_id`, `work_form_id`, `group_id`, `comments`) VALUES
	(1, 65, 1, 1, 1, 'Коментарий');

-- Дамп структуры для таблица ordo_dev.educational_years
DROP TABLE IF EXISTS `educational_years`;
CREATE TABLE IF NOT EXISTS `educational_years` (
  `id` int NOT NULL AUTO_INCREMENT,
  `begin_year` varchar(255) NOT NULL,
  `end_year` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `educationalyears_begin_year` (`begin_year`),
  UNIQUE KEY `educationalyears_end_year` (`end_year`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.educational_years: ~2 rows (приблизительно)
INSERT INTO `educational_years` (`id`, `begin_year`, `end_year`) VALUES
	(1, '2024', '2025'),
	(2, '2023', '2024');

-- Дамп структуры для таблица ordo_dev.group
DROP TABLE IF EXISTS `group`;
CREATE TABLE IF NOT EXISTS `group` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.group: ~1 rows (приблизительно)
INSERT INTO `group` (`id`, `name`) VALUES
	(1, '101-А'),
	(2, '101-СП');

-- Дамп структуры для таблица ordo_dev.post
DROP TABLE IF EXISTS `post`;
CREATE TABLE IF NOT EXISTS `post` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `post_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.post: ~3 rows (приблизительно)
INSERT INTO `post` (`id`, `name`) VALUES
	(2, 'Доцент'),
	(1, 'Преподаватель'),
	(3, 'Профессор');

-- Дамп структуры для таблица ordo_dev.rang
DROP TABLE IF EXISTS `rang`;
CREATE TABLE IF NOT EXISTS `rang` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `rang_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.rang: ~2 rows (приблизительно)
INSERT INTO `rang` (`id`, `name`) VALUES
	(2, 'Д.м.н.'),
	(1, 'К.п.н.');

-- Дамп структуры для таблица ordo_dev.staff
DROP TABLE IF EXISTS `staff`;
CREATE TABLE IF NOT EXISTS `staff` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL,
  `department_id` int NOT NULL,
  `post_id` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `staff_user_id` (`user_id`),
  KEY `staff_department_id` (`department_id`),
  KEY `staff_post_id` (`post_id`),
  CONSTRAINT `staff_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`id`),
  CONSTRAINT `staff_ibfk_2` FOREIGN KEY (`department_id`) REFERENCES `department` (`id`),
  CONSTRAINT `staff_ibfk_3` FOREIGN KEY (`post_id`) REFERENCES `post` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.staff: ~2 rows (приблизительно)
INSERT INTO `staff` (`id`, `user_id`, `department_id`, `post_id`) VALUES
	(22, 27, 1, 1),
	(23, 27, 3, 2);

-- Дамп структуры для таблица ordo_dev.teacher_plan
DROP TABLE IF EXISTS `teacher_plan`;
CREATE TABLE IF NOT EXISTS `teacher_plan` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL,
  `department_id` int NOT NULL,
  `post_id` int NOT NULL,
  `year_id` int NOT NULL,
  `rate` decimal(3,2) NOT NULL,
  `status_id` int NOT NULL,
  `approved_user_id` int DEFAULT NULL,
  `approved_date` date DEFAULT NULL,
  `department_boss_sign_id` int DEFAULT NULL,
  `protocol_number` varchar(255) DEFAULT NULL,
  `protocol_date` date DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `teacherplan_user_id` (`user_id`),
  KEY `teacherplan_department_id` (`department_id`),
  KEY `teacherplan_post_id` (`post_id`),
  KEY `teacherplan_year_id` (`year_id`),
  KEY `teacherplan_status_id` (`status_id`),
  KEY `teacherplan_approved_user_id` (`approved_user_id`),
  KEY `teacherplan_department_boss_sign_id` (`department_boss_sign_id`),
  CONSTRAINT `teacher_plan_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`id`),
  CONSTRAINT `teacher_plan_ibfk_2` FOREIGN KEY (`department_id`) REFERENCES `department` (`id`),
  CONSTRAINT `teacher_plan_ibfk_3` FOREIGN KEY (`post_id`) REFERENCES `post` (`id`),
  CONSTRAINT `teacher_plan_ibfk_4` FOREIGN KEY (`year_id`) REFERENCES `educational_years` (`id`),
  CONSTRAINT `teacher_plan_ibfk_5` FOREIGN KEY (`status_id`) REFERENCES `teacher_plan_status` (`id`),
  CONSTRAINT `teacher_plan_ibfk_6` FOREIGN KEY (`approved_user_id`) REFERENCES `user` (`id`),
  CONSTRAINT `teacher_plan_ibfk_7` FOREIGN KEY (`department_boss_sign_id`) REFERENCES `user` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=66 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.teacher_plan: ~1 rows (приблизительно)
INSERT INTO `teacher_plan` (`id`, `user_id`, `department_id`, `post_id`, `year_id`, `rate`, `status_id`, `approved_user_id`, `approved_date`, `department_boss_sign_id`, `protocol_number`, `protocol_date`) VALUES
	(65, 27, 3, 2, 1, 0.50, 1, NULL, NULL, NULL, NULL, NULL);

-- Дамп структуры для таблица ordo_dev.teacher_plan_status
DROP TABLE IF EXISTS `teacher_plan_status`;
CREATE TABLE IF NOT EXISTS `teacher_plan_status` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `teacherplanstatus_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.teacher_plan_status: ~3 rows (приблизительно)
INSERT INTO `teacher_plan_status` (`id`, `name`) VALUES
	(1, 'В разработке'),
	(2, 'На утверждении'),
	(3, 'Утвержден');

-- Дамп структуры для таблица ordo_dev.teacher_plan_total_hours
DROP TABLE IF EXISTS `teacher_plan_total_hours`;
CREATE TABLE IF NOT EXISTS `teacher_plan_total_hours` (
  `id` int NOT NULL AUTO_INCREMENT,
  `teacher_plan_id` int NOT NULL,
  `work_type_id` int NOT NULL,
  `first_semester` int NOT NULL,
  `second_semester` int NOT NULL,
  `order_place` int DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `teacherplantotalhours_teacher_plan_id` (`teacher_plan_id`),
  KEY `teacherplantotalhours_work_type_id` (`work_type_id`),
  CONSTRAINT `FK_teacher_plan_total_hours_teacher_plan` FOREIGN KEY (`teacher_plan_id`) REFERENCES `teacher_plan` (`id`),
  CONSTRAINT `teacher_plan_total_hours_ibfk_2` FOREIGN KEY (`work_type_id`) REFERENCES `teacher_plan_works_type` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=187 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.teacher_plan_total_hours: ~0 rows (приблизительно)

-- Дамп структуры для таблица ordo_dev.teacher_plan_works_type
DROP TABLE IF EXISTS `teacher_plan_works_type`;
CREATE TABLE IF NOT EXISTS `teacher_plan_works_type` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `order` int DEFAULT NULL,
  `enable` tinyint DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `teacherplanworkstype_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.teacher_plan_works_type: ~5 rows (приблизительно)
INSERT INTO `teacher_plan_works_type` (`id`, `name`, `order`, `enable`) VALUES
	(1, 'Учебная работа', 1, 1),
	(2, 'Учебно-методическая работа', 2, 1),
	(3, 'Научно-исследовательская работа', 3, 1),
	(4, 'Воспитательная и спортивная работа', 4, 1),
	(5, 'Другие виды работ', 5, 1);

-- Дамп структуры для таблица ordo_dev.user
DROP TABLE IF EXISTS `user`;
CREATE TABLE IF NOT EXISTS `user` (
  `id` int NOT NULL AUTO_INCREMENT,
  `login` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `surname` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `middle_name` varchar(255) DEFAULT NULL,
  `rang_id` int DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_login` (`login`),
  KEY `user_rang_id` (`rang_id`),
  CONSTRAINT `user_ibfk_1` FOREIGN KEY (`rang_id`) REFERENCES `rang` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.user: ~1 rows (приблизительно)
INSERT INTO `user` (`id`, `login`, `password`, `surname`, `name`, `middle_name`, `rang_id`) VALUES
	(27, 'teacher', 'deb1536f480475f7d593219aa1afd74c', 'Иванов', 'Перт', 'Сергеевич', 1);

-- Дамп структуры для таблица ordo_dev.work_form
DROP TABLE IF EXISTS `work_form`;
CREATE TABLE IF NOT EXISTS `work_form` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.work_form: ~13 rows (приблизительно)
INSERT INTO `work_form` (`id`, `name`) VALUES
	(1, 'Лекции'),
	(2, 'Сем./практ.'),
	(3, 'Рук. КР и ВКР(б)'),
	(4, 'Рук. ВКР(м)'),
	(5, 'Конс. перед аттест.'),
	(6, 'Зачет'),
	(7, 'Экзамен'),
	(8, 'Конс. по дисц.'),
	(9, 'Практика'),
	(10, 'Рецензир.'),
	(11, 'ГЭК'),
	(12, 'Вступ. испыт.'),
	(13, 'Руков. кафедрой');

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
