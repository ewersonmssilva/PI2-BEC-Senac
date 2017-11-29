<?php
session_start();
if(!empty($_SESSION['id'])){
	//echo "$var <br>";
	echo "<br><br>&nbsp;&nbsp;&nbsp;&nbsp;<b>Olá ".$_SESSION['nome'].", Seja bem vindo(a) a área administrativa</b><br>";
	echo "<br><br>&nbsp;&nbsp;&nbsp;&nbsp;<b><font color=\"#FF0000\">Atenção: Não se esqueça de sair da sessão quando terminar!</font></b><br>";
}else{
	$_SESSION['msg'] = "Área restrita";
	header("Location: login.php");
}
?>

<!DOCTYPE html>
<html lang="pt-br">
	<head>
		<meta charset="utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=edge">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<title>PI 2 Senac</title>
		<link href="css/bootstrap.css" rel="stylesheet">
		<link href="css/signin.css" rel="stylesheet">
	</head>
	<body>
      <!-- Fixed navbar -->
    <nav class="navbar navbar-inverse navbar-fixed-top">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
            <span class="sr-only">Navegação</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="index.php">PI 2 Senac</a>
        </div>
        <div id="navbar" class="navbar-collapse collapse">
          <ul class="nav navbar-nav">
            <li class="active"><a href="index.php">Home</a></li>
            <li><a href="g_linhas.php">Graficos</a></li>
            <li><a href="administrativo.php">Admin</a></li>
            <li><a href="cadastrar_user.php">Cadastrar</a></li>
            <li><a href="#contact">Contato</a></li>
			      <li><a href="#about">Sobre</a></li>
			      <li><a href="sair.php">Sair</a></li>
          </ul>
        </div><!--/.nav-collapse -->
      </div>
    </nav>
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
		<script src="js/bootstrap.min.js"></script>
	</body>
</html>
