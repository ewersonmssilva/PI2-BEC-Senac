<?php
session_start();
ob_start();
include_once("conexao.php");

$sql = "SELECT consumo_mensal.id, usuarios.nome, consumo_mensal.litros
          FROM consumo_mensal INNER JOIN usuarios
            WHERE FIND_IN_SET( usuarios.id , consumo_mensal.id) ORDER BY consumo_mensal.id";



$resultado = mysqli_query($conn, $sql);

		?>
<html>
  <head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">

	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>PI 2 Senac</title>
	<link href="css/bootstrap.css" rel="stylesheet">
	<link href="css/signin.css" rel="stylesheet">

    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">
      google.charts.load('current', {packages:['corechart']});
      google.charts.setOnLoadCallback(drawStuff);

        function drawStuff() {
          var data = new google.visualization.DataTable();
          data.addColumn('string', 'Meses');
          data.addColumn('number', 'Litros');
          data.addRows([
		  <?
		  		while($ln = mysqli_fetch_assoc($resultado))
		{
			echo '["' .(string) $ln['nome'] . '", ' . (float)$ln['litros'] . '], ';
		}

		?>
          ]);

         var options = {
           title: 'Consumo Mensal em Litros',
           width: 900,
           height: 500,
           legend: 'none',
           bar: {groupWidth: '95%'},
           vAxis: { gridlines: { count: 4 } }
         };

         var chart = new google.visualization.ColumnChart(document.getElementById('number_format_chart'));
         chart.draw(data, options);

         document.getElementById('format-select').onchange = function() {
           options['vAxis']['format'] = this.value;
           chart.draw(data, options);
         };
      };
    </script>
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

            <li><a href="#contact">Contato</a></li>

	    <li><a href="#about">Sobre</a></li>

          </ul>

        </div><!--/.nav-collapse -->
      </div>
    </nav>
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
		<script src="js/bootstrap.min.js"></script>

    <select id="format-select">
      <option value="">none</option>
      <option value="decimal" selected>decimal</option>
      <option value="scientific">scientific</option>
      <option value="percent">percent</option>
      <option value="currency">currency</option>
      <option value="short">short</option>
      <option value="long">long</option>
    </select>
    <div id="number_format_chart">


  </body>
</html>
