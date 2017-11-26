<?php
session_start();
ob_start();
include_once("conexao.php");

$sql = "SELECT user_id, s_ultrasson, s_fluxo FROM sensores";
$resultado = mysqli_query($conn, $sql);


 $data = "var data = new google.visualization.DataTable();\n\r"
 ."data.addColumn('number', 'Segundos');\n\r"

 ."data.addColumn('number', 'Sens. Fluxo');\n\r\n\r"
 ."data.addRows([\n\r";
$contador = 0;

while ($row = mysqli_fetch_assoc($resultado)){

		$contador = $contador + 1;
		$fluxo = (int)$row['s_fluxo'];
		$data = $data."  [".$contador.", ".$fluxo."],\n\r";
		}
		$data = $data."]);\n\r";

mysqli_close($conn);
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
      google.charts.load('current', {'packages':['line']});
      google.charts.setOnLoadCallback(drawChart);

    function drawChart() {

      <?php echo $data; ?>

      var options = {
        chart: {
          title: 'Fluxo x contador',
          subtitle: 'Altura em Centimetros (CM)'
        },
        width: 900,
        height: 500,
        axes: {
          x: {
            0: {side: 'top'}
          }
        }
      };

      var chart = new google.charts.Line(document.getElementById('line_top_x'));

      chart.draw(data, google.charts.Line.convertOptions(options));
    }
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
<br>

  <div id="line_top_x"></div>
</body>
</html>
