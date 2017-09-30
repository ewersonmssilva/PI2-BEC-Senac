-- --------------------------------------------------------
-- Servidor:                     127.0.0.1
-- Versão do servidor:           5.6.36-log - MySQL Community Server (GPL)
-- OS do Servidor:               Win32
-- HeidiSQL Versão:              9.4.0.5174
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- Copiando estrutura do banco de dados para cisterna
CREATE DATABASE IF NOT EXISTS `cisterna` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `cisterna`;

-- Copiando estrutura para tabela cisterna.admin
CREATE TABLE IF NOT EXISTS `admin` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(220) NOT NULL,
  `email` varchar(220) NOT NULL,
  `usuario` varchar(220) NOT NULL,
  `senha` varchar(220) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

-- Copiando dados para a tabela cisterna.admin: 4 rows
/*!40000 ALTER TABLE `admin` DISABLE KEYS */;
INSERT INTO `admin` (`id`, `nome`, `email`, `usuario`, `senha`) VALUES
	(1, 'Cesar', 'cesar@senac.com.br', 'cesar@senac.com.br', '$2y$10$d8Hpwwj/DENEW4sBuUDvUuCw4/2QgEoWvs8YlAXASltHqw5w7vKDm'),
	(2, 'Kelly', 'kelly@senac.com.br', 'kelly@senac.com.br', '$2y$10$vbRUBxSLOCK00HsOd4Djxu.6I8JWzqMkhR2UwdMiCKvvB3lq/yD1u'),
	(3, 'Jessica', 'jessica@senac.com.br', 'jessica@senac.com.br', '$2y$10$3QR5vemGVmxMXNh68/XdHumXRSpK6UXdl7yK9dmqLfh4QSw.lKMPy'),
	(5, 'Ewerson Manoel dos Santos Silva', 'ewerson@msn.com', 'ewerson', '$2y$10$4RUoEog0Y72jcLMlUo97cuLC0/Llk05UJ7Br6lm8y9cD0s6x6hQP.');
/*!40000 ALTER TABLE `admin` ENABLE KEYS */;

-- Copiando estrutura para tabela cisterna.areas
CREATE TABLE IF NOT EXISTS `areas` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Nome` varchar(50) CHARACTER SET utf8 NOT NULL,
  `1_latitude` float(10,6) NOT NULL,
  `1_longitude` float(10,6) NOT NULL,
  `2_latitude` float(10,6) NOT NULL,
  `2_longitude` float(10,6) NOT NULL,
  `3_latitude` float(10,6) NOT NULL,
  `3_longitude` float(10,6) NOT NULL,
  `4_latitude` float(10,6) NOT NULL,
  `4_longitude` float(10,6) NOT NULL,
  `5_latitude` float(10,6) NOT NULL,
  `5_longitude` float(10,6) NOT NULL,
  `6_latitude` float(10,6) NOT NULL,
  `6_longitude` float(10,6) NOT NULL,
  `7_latitude` float(10,6) NOT NULL,
  `7_longitude` float(10,6) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Copiando dados para a tabela cisterna.areas: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `areas` DISABLE KEYS */;
/*!40000 ALTER TABLE `areas` ENABLE KEYS */;

-- Copiando estrutura para tabela cisterna.estados
CREATE TABLE IF NOT EXISTS `estados` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `CodigoUf` int(11) NOT NULL,
  `Nome` varchar(50) CHARACTER SET utf8 NOT NULL,
  `Uf` char(2) CHARACTER SET utf8 NOT NULL,
  `Regiao` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Copiando dados para a tabela cisterna.estados: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `estados` DISABLE KEYS */;
/*!40000 ALTER TABLE `estados` ENABLE KEYS */;

-- Copiando estrutura para tabela cisterna.medidas_cist
CREATE TABLE IF NOT EXISTS `medidas_cist` (
  `user_id` int(11) NOT NULL,
  `tipo` varchar(20) NOT NULL,
  `altura` int(11) NOT NULL,
  `largura` int(11) NOT NULL,
  `comprimento` int(11) NOT NULL,
  `capacidade` int(11) NOT NULL,
  `area_captacao` int(11) NOT NULL,
  `criado` datetime NOT NULL,
  `modificado` datetime DEFAULT NULL,
  PRIMARY KEY (`user_id`),
  CONSTRAINT `fk_medidas_cist_user_id` FOREIGN KEY (`user_id`) REFERENCES `usuarios` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Copiando dados para a tabela cisterna.medidas_cist: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `medidas_cist` DISABLE KEYS */;
/*!40000 ALTER TABLE `medidas_cist` ENABLE KEYS */;

-- Copiando estrutura para tabela cisterna.niveis_acessos
CREATE TABLE IF NOT EXISTS `niveis_acessos` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(50) NOT NULL,
  `criado` datetime NOT NULL,
  `modificado` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

-- Copiando dados para a tabela cisterna.niveis_acessos: ~3 rows (aproximadamente)
/*!40000 ALTER TABLE `niveis_acessos` DISABLE KEYS */;
INSERT INTO `niveis_acessos` (`id`, `nome`, `criado`, `modificado`) VALUES
	(1, 'Administrador', '2017-09-29 08:50:17', NULL),
	(2, 'Colaborador', '2017-09-29 08:50:40', NULL),
	(3, 'Cliente', '2017-09-29 08:51:26', NULL);
/*!40000 ALTER TABLE `niveis_acessos` ENABLE KEYS */;

-- Copiando estrutura para tabela cisterna.sensores
CREATE TABLE IF NOT EXISTS `sensores` (
  `user_id` int(11) NOT NULL,
  `s_ultrasson` int(11) NOT NULL,
  `s_fluxo` int(11) NOT NULL,
  `criado` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Copiando dados para a tabela cisterna.sensores: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `sensores` DISABLE KEYS */;
/*!40000 ALTER TABLE `sensores` ENABLE KEYS */;

-- Copiando estrutura para tabela cisterna.tipos_cist
CREATE TABLE IF NOT EXISTS `tipos_cist` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `formato` varchar(50) NOT NULL,
  `criado` datetime NOT NULL,
  `modificado` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Copiando dados para a tabela cisterna.tipos_cist: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `tipos_cist` DISABLE KEYS */;
/*!40000 ALTER TABLE `tipos_cist` ENABLE KEYS */;

-- Copiando estrutura para tabela cisterna.usuarios
CREATE TABLE IF NOT EXISTS `usuarios` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(220) NOT NULL,
  `email` varchar(520) NOT NULL,
  `cpf` varchar(11) NOT NULL,
  `ddd` int(2) DEFAULT NULL,
  `telefone` int(9) DEFAULT NULL,
  `endereco` varchar(255) NOT NULL,
  `cidade` varchar(255) NOT NULL,
  `estado` char(2) NOT NULL,
  `bairro` varchar(255) NOT NULL,
  `latitude` float(10,6) NOT NULL,
  `longitude` float(10,6) NOT NULL,
  `area` int(2) NOT NULL,
  `memb_familia` int(2) NOT NULL,
  `senha` varchar(50) DEFAULT 'senha',
  `type` varchar(30) DEFAULT NULL,
  `situacoe_id` int(11) DEFAULT '0',
  `niveis_acesso_id` int(11) DEFAULT NULL,
  `created` datetime DEFAULT NULL,
  `modified` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `cpf_UNIQUE` (`cpf`),
  UNIQUE KEY `id_UNIQUE` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

-- Copiando dados para a tabela cisterna.usuarios: ~2 rows (aproximadamente)
/*!40000 ALTER TABLE `usuarios` DISABLE KEYS */;
INSERT INTO `usuarios` (`id`, `nome`, `email`, `cpf`, `ddd`, `telefone`, `endereco`, `cidade`, `estado`, `bairro`, `latitude`, `longitude`, `area`, `memb_familia`, `senha`, `type`, `situacoe_id`, `niveis_acesso_id`, `created`, `modified`) VALUES
	(1, 'Ewerson Manoel dos Santos Silva', 'ewerson@msn.com', '30153791861', 11, 973786946, '', 'Guarulhos', 'SP', 'continental', -25.494970, -49.294357, 12, 5, 'senha', 'usuario', 0, NULL, NULL, NULL),
	(3, 'Manoel dos Santos Silva', 'ewerson@msn.com', '11153791861', 11, 2147483647, '', 'Guarulhos', 'SP', 'continental', -25.894970, -49.874355, 12, 5, 'senha', NULL, 0, NULL, NULL, NULL);
/*!40000 ALTER TABLE `usuarios` ENABLE KEYS */;

-- Copiando estrutura para tabela cisterna.vol_mensal
CREATE TABLE IF NOT EXISTS `vol_mensal` (
  `user_id` int(11) NOT NULL,
  `entrada` int(11) NOT NULL,
  `saida` int(11) NOT NULL,
  `criado` datetime NOT NULL,
  PRIMARY KEY (`user_id`),
  CONSTRAINT `fk_vol_mensal_user_id` FOREIGN KEY (`user_id`) REFERENCES `usuarios` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Copiando dados para a tabela cisterna.vol_mensal: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `vol_mensal` DISABLE KEYS */;
/*!40000 ALTER TABLE `vol_mensal` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
