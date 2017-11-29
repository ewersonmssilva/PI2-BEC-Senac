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
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">


google.charts.load('current', {packages: ['corechart', 'bar']});
google.charts.setOnLoadCallback(drawTopX);

function drawTopX() {

<?php echo $data; ?>

      var options = {
        chart: {
          title: 'Motivation and Energy Level Throughout the Day',
          subtitle: 'Based on a scale of 1 to 10'
        },
        axes: {
          x: {
            0: {side: 'top'}
          }
        },
        hAxis: {
          title: 'Time of Day',
          format: 'h:mm a',
          viewWindow: {
            min: [7, 30, 0],
            max: [17, 30, 0]
          }
        },
        vAxis: {
          title: 'Rating (scale of 1-10)'
        }
      };

      var materialChart = new google.charts.Bar(document.getElementById('chart_div'));
      materialChart.draw(data, options);
    }
    </script>
  </head>
  <body>
    <div id="columnchart_material" style="width: 800px; height: 500px;"></div>
  </body>
</html>
