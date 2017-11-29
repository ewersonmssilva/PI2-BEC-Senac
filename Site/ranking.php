<table border="1" width="350">
<tr>
<th>ID</th>
<th>Nome</th>
<th>S. Ultra</th>
<th>S. fluxo</th>
</tr>

<?php
//$query = "SELECT score FROM table ORDER BY score DESC";
//$result = mysql_query($query);
include_once("conexao.php");
$sql = "SELECT * FROM sensores ORDER BY s_ultrasson ASC LIMIT 1,10";
$resultado = mysqli_query($conn, $sql);

//if(mysql_affected_rows()>0){
$lista = 0;

while($dado=mysqli_fetch_array($resultado)){

$lista ++; ?>

<tr>
  <td><?php echo $lista; ?></td>
  <td><?php echo $dado['user_id']; ?></td>
  <td><?php echo $dado['s_ultrasson']; ?></td>
  <td><?php echo $dado['s_fluxo']; ?></td>
</tr>
<?php } ?>
</table>
