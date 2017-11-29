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
      google.charts.load('current', {'packages':['line']});
      google.charts.setOnLoadCallback(drawChart);

    function drawChart() {

      <?php echo $data; ?>

      var options = {
        chart: {
          title: 'Box Office Earnings in First Two Weeks of Opening',
          subtitle: 'in millions of dollars (USD)'
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
  <div id="line_top_x"></div>
</body>
</html>

