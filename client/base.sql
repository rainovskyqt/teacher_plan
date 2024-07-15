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


-- Дамп структуры базы данных ordo_dev
CREATE DATABASE IF NOT EXISTS `ordo_dev` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `ordo_dev`;

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

-- Дамп данных таблицы ordo_dev.disciline_department: ~0 rows (приблизительно)

-- Дамп структуры для таблица ordo_dev.discipline
DROP TABLE IF EXISTS `discipline`;
CREATE TABLE IF NOT EXISTS `discipline` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.discipline: ~3 rows (приблизительно)
INSERT INTO `discipline` (`id`, `name`) VALUES
	(1, '-'),
	(2, 'Социология'),
	(3, 'Философия');

-- Дамп структуры для таблица ordo_dev.educational_work
DROP TABLE IF EXISTS `educational_work`;
CREATE TABLE IF NOT EXISTS `educational_work` (
  `id` int NOT NULL AUTO_INCREMENT,
  `teacher_plan_id` int DEFAULT NULL,
  `discipline_id` int DEFAULT NULL,
  `work_form_id` int DEFAULT NULL,
  `group_id` int DEFAULT NULL,
  `comments` text,
  `order_place` int DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_educational_work_discipline` (`discipline_id`),
  KEY `FK_educational_work_group` (`group_id`),
  KEY `FK_educational_work_work_form` (`work_form_id`),
  KEY `FK_educational_work_teacher_plan` (`teacher_plan_id`),
  CONSTRAINT `FK_educational_work_discipline` FOREIGN KEY (`discipline_id`) REFERENCES `discipline` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_educational_work_group` FOREIGN KEY (`group_id`) REFERENCES `group` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_educational_work_teacher_plan` FOREIGN KEY (`teacher_plan_id`) REFERENCES `teacher_plan` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_educational_work_work_form` FOREIGN KEY (`work_form_id`) REFERENCES `educational_work_form` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=47 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.educational_work: ~2 rows (приблизительно)
INSERT INTO `educational_work` (`id`, `teacher_plan_id`, `discipline_id`, `work_form_id`, `group_id`, `comments`, `order_place`) VALUES
	(45, 65, 3, 3, 3, NULL, 0),
	(46, 65, 1, 1, 1, NULL, 0);

-- Дамп структуры для таблица ordo_dev.educational_work_form
DROP TABLE IF EXISTS `educational_work_form`;
CREATE TABLE IF NOT EXISTS `educational_work_form` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=34 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.educational_work_form: ~14 rows (приблизительно)
INSERT INTO `educational_work_form` (`id`, `name`) VALUES
	(1, '-'),
	(2, 'Лекции'),
	(3, 'Сем./практ.'),
	(4, 'Рук. КР и ВКР(б)'),
	(5, 'Рук. ВКР(м)'),
	(6, 'Конс. перед аттест.'),
	(7, 'Зачет'),
	(8, 'Экзамен'),
	(9, 'Конс. по дисц.'),
	(10, 'Практика'),
	(11, 'Рецензир.'),
	(12, 'ГЭК'),
	(13, 'Вступ. испыт.'),
	(14, 'Руков. кафедрой');

-- Дамп структуры для таблица ordo_dev.educational_work_hours
DROP TABLE IF EXISTS `educational_work_hours`;
CREATE TABLE IF NOT EXISTS `educational_work_hours` (
  `id` int NOT NULL AUTO_INCREMENT,
  `month` int DEFAULT NULL,
  `week` int DEFAULT NULL,
  `value` int DEFAULT NULL,
  `type` int DEFAULT NULL,
  `plan_work_id` int DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_educational_work_hours_educational_work` (`plan_work_id`),
  CONSTRAINT `FK_educational_work_hours_educational_work` FOREIGN KEY (`plan_work_id`) REFERENCES `educational_work` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=233 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.educational_work_hours: ~22 rows (приблизительно)
INSERT INTO `educational_work_hours` (`id`, `month`, `week`, `value`, `type`, `plan_work_id`) VALUES
	(211, 4, 4, 1, 1, 45),
	(212, 4, 1, 4, 1, 45),
	(213, 4, 1, 44, 1, 45),
	(214, 5, 4, 4, 1, 45),
	(215, 5, 4, 44, 1, 45),
	(216, 2, 4, 2, 1, 45),
	(217, 2, 4, 23, 1, 45),
	(218, 1, 2, 6, 1, 45),
	(219, 1, 2, 65, 1, 45),
	(220, 6, 3, 2, 1, 45),
	(221, 6, 3, 22, 1, 45),
	(222, 6, 3, 223, 1, 45),
	(223, 3, 2, 6, 1, 45),
	(224, 3, 2, 68, 1, 45),
	(225, 12, 1, 2, 1, 45),
	(226, 12, 1, 22, 1, 45),
	(227, 9, 4, 1, 1, 45),
	(228, 10, 1, 1, 1, 45),
	(229, 5, 3, 1, 1, 45),
	(230, 5, 1, 1, 1, 45),
	(231, 12, 2, 1, 1, 45),
	(232, 6, 2, 7, 1, 46);

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

-- Дамп структуры для таблица ordo_dev.generic_work
DROP TABLE IF EXISTS `generic_work`;
CREATE TABLE IF NOT EXISTS `generic_work` (
  `id` int NOT NULL AUTO_INCREMENT,
  `work_type` int NOT NULL,
  `assigned_user_id` int DEFAULT NULL,
  `assigned_date` date DEFAULT NULL,
  `first_complite_user_id` int DEFAULT NULL,
  `first_complite_date` date DEFAULT NULL,
  `second_complite_user_id` int DEFAULT NULL,
  `second_complite_date` date DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_generic_work_teacher_plan_works_type` (`work_type`),
  KEY `FK_generic_work_user` (`assigned_user_id`),
  KEY `FK_generic_work_user_2` (`first_complite_user_id`),
  KEY `FK_generic_work_user_3` (`second_complite_user_id`),
  CONSTRAINT `FK_generic_work_teacher_plan_works_type` FOREIGN KEY (`work_type`) REFERENCES `teacher_plan_works_type` (`id`),
  CONSTRAINT `FK_generic_work_user` FOREIGN KEY (`assigned_user_id`) REFERENCES `user` (`id`),
  CONSTRAINT `FK_generic_work_user_2` FOREIGN KEY (`first_complite_user_id`) REFERENCES `user` (`id`),
  CONSTRAINT `FK_generic_work_user_3` FOREIGN KEY (`second_complite_user_id`) REFERENCES `user` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.generic_work: ~0 rows (приблизительно)

-- Дамп структуры для таблица ordo_dev.generic_work_form
DROP TABLE IF EXISTS `generic_work_form`;
CREATE TABLE IF NOT EXISTS `generic_work_form` (
  `id` int NOT NULL AUTO_INCREMENT,
  `work_type` int NOT NULL DEFAULT '0',
  `chapter` varchar(10) NOT NULL DEFAULT '0',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL DEFAULT '0',
  `max_year_count` int NOT NULL DEFAULT '0',
  `max_unit_count` int DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK__teacher_plan_works_type` (`work_type`),
  CONSTRAINT `FK__teacher_plan_works_type` FOREIGN KEY (`work_type`) REFERENCES `teacher_plan_works_type` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.generic_work_form: ~39 rows (приблизительно)
INSERT INTO `generic_work_form` (`id`, `work_type`, `chapter`, `name`, `max_year_count`, `max_unit_count`) VALUES
	(1, 2, '2.1.1', 'Разработка рабочих программ учебных дисциплин, подготовка фондов оценочных средств по дисциплинам учебного плана', 50, NULL),
	(2, 2, '2.1.2', 'Переработка рабочей программы учебной дисциплины, фондов оценочных средств по дисциплинам учебного плана', 20, NULL),
	(3, 2, '2.1.3', 'Внесение изменений в рабочую программу учебной дисциплины', 3, NULL),
	(4, 2, '2.2.1', 'Разработка тезисов или конспекта лекции: По вновь вводимой теме', 8, NULL),
	(5, 2, '2.2.2', 'Разработка тезисов или конспекта лекции: По ранее читавшейся теме', 3, NULL),
	(6, 2, '2.3.1', 'Разработка тестов по дисциплинам:Разработка новых', 30, NULL),
	(7, 2, '2.3.2', 'Разработка тестов по дисциплинам:Корректировка имеющихся', 6, NULL),
	(8, 2, '2.4.1', 'Составление заданий и подбор различных документов при подготовке: К учебным занятиям (для курсовых работ, домашних заданий, лабораторных работ, РГР, заданий на практику и др.)', 20, NULL),
	(9, 2, '2.4.2', 'Составление заданий и подбор различных документов при подготовке: К открытым занятиям (показательным (мастер-классам), проверочным)', 6, NULL),
	(10, 2, '2.5.1', 'Выпускные квалификационные работы:Разработка тематики (перечня тем)', 12, NULL),
	(11, 2, '2.5.2', 'Выпускные квалификационные работы:Разработка методических рекомендаций для обучающихся по подготовке и защите ВКР', 20, NULL),
	(12, 2, '2.6.1', 'Курсовые работы:Разработка тематики (перечня тем)', 6, NULL),
	(13, 2, '2.6.2', 'Курсовые работы:Разработка методических рекомендаций для обучающихся по подготовке и защите курсовых работ', 10, NULL),
	(14, 2, '2.6.3', 'Курсовые работы:Участие в публичной защите курсовой работы', 4, NULL),
	(15, 2, '2.7.1', 'Разработка материалов для проведения зачетов:Разработка новых', 8, NULL),
	(16, 2, '2.7.2', 'Разработка материалов для проведения зачетов:Корректировка имеющихся', 4, NULL),
	(17, 2, '2.8.1', 'Составление экзаменационных билетов:Разработка новых', 12, NULL),
	(18, 2, '2.8.2', 'Составление экзаменационных билетов:Корректировка имеющихся', 4, NULL),
	(19, 2, '2.9.1', 'Составление примерного перечня вопросов для формирования билетов для государственных экзаменов:Разработка нового перечня', 18, NULL),
	(20, 2, '2.9.2', 'Составление примерного перечня вопросов для формирования билетов для государственных экзаменов:Корректировка имеющегося', 6, NULL),
	(21, 2, '2.10.1', 'Обучение с применением дистанционных образовательных технологий: Групповые консультации с использованием видео-конференц-связи', 20, NULL),
	(22, 2, '2.10.2', 'Обучение с применением дистанционных образовательных технологий: Индивидуальное консультационно-методическое сопровождение обучающихся при изучении образовательного контента с применением ДОТ', 20, NULL),
	(23, 2, '2.10.3', 'Обучение с применением дистанционных образовательных технологий: Проверка и рецензирование контрольной работы (практического задания) по теме (разделу, модулю) (с использованием ДОТ)', 20, NULL),
	(24, 2, '2.11.1', 'Разработка, обновление программы вступительных испытаний', 10, NULL),
	(25, 2, '2.11.2', 'Разработка материалов (слайдов) для мультиме-дийного сопровождения занятия в электронной версии', 4, NULL),
	(26, 2, '2.11.3', 'Рецензирование реферата у аспирантов, соискателей и материалов диссертационного исследования докторантов', 0, NULL),
	(27, 2, '2.11.4', 'Руководство соискателем ', 25, NULL),
	(28, 2, '2.11.5', 'Изучение, анализ и внедрение в учебный процесс современной учебной и научно-методической литературы по преподаваемым дисциплинам', 30, NULL),
	(29, 2, '2.11.6', 'Написание учебника', 150, NULL),
	(30, 2, '2.11.7', 'Переиздание учебника ', 50, NULL),
	(31, 2, '2.11.8', 'Написание пособия, курса лекций, практикума, справочника, сборника задач, методических рекомендаций', 80, NULL),
	(32, 2, '2.11.9', 'Переиздание пособия, курса лекций, практикума, справочника, сборника задач, методических рекомендаций', 40, NULL),
	(33, 2, '2.11.10', 'Рецензирование учебников и учебных пособий', 6, NULL),
	(34, 2, '2.11.11.1', 'Организация и проведение учебно-методических конференций: Внутривузовских', 20, NULL),
	(35, 2, '2.11.11.2', 'Организация и проведение учебно-методических конференций: Кафедральных', 4, NULL),
	(36, 2, '2.11.12', 'Разработка, освоение и методическое обеспечение новых технологий и технологических приемов обучения (деловые и ситуационные игры, тренажеры, автоматизированные системы обучения и др.)', 20, NULL),
	(37, 2, '2.11.13', 'Индивидуальное консультационно-методическое сопровождение обучающихся при изучении образовательного контента по очной форме обучения', 0, NULL),
	(38, 2, '2.11.14', 'Организация учебной и учебно-методической работы на кафедре', 50, NULL),
	(39, 2, '2.11.15', 'Заполнение контрольных листов текущей аттестации', 2, NULL);

-- Дамп структуры для таблица ordo_dev.group
DROP TABLE IF EXISTS `group`;
CREATE TABLE IF NOT EXISTS `group` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Дамп данных таблицы ordo_dev.group: ~3 rows (приблизительно)
INSERT INTO `group` (`id`, `name`) VALUES
	(1, '-'),
	(2, '101-А'),
	(3, '101-СП');

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

-- Дамп данных таблицы ordo_dev.teacher_plan: ~0 rows (приблизительно)
INSERT INTO `teacher_plan` (`id`, `user_id`, `department_id`, `post_id`, `year_id`, `rate`, `status_id`, `approved_user_id`, `approved_date`, `department_boss_sign_id`, `protocol_number`, `protocol_date`) VALUES
	(65, 27, 3, 2, 1, 0.25, 1, NULL, NULL, NULL, NULL, NULL);

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

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
