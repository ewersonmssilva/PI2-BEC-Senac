<?php
session_start();
ob_start();
include_once("conexao.php");

//Receber os dados do formulário
$dados = filter_input_array(INPUT_POST, FILTER_DEFAULT);

//Salvar os dados no bd
$result_markers = "INSERT INTO usuarios(nome, email, cpf, ddd, telefone, endereco, cidade, estado, bairro, latitude, longitude, area, memb_familia) 
				VALUES 
				('".$dados['nome']."', '".$dados['email']."', '".$dados['cpf']."', '".$dados['ddd']."', '".$dados['telefone']."', '".$dados['endereço']."', '".$dados['cidade']."', '".$dados['estado']."', '".$dados['bairro']."', '".$dados['latitude']."', '".$dados['longitude']."', '".$dados['area']."', '".$dados['memb_familia']."')";

$resultado_markers = mysqli_query($conn, $result_markers);
if(mysqli_insert_id($conn)){
	$_SESSION['msg'] = "<span style='color: green';>Endereço cadastrado com sucesso!</span>";
	header("Location: cadastrar_user.php");
}else{
	$_SESSION['msg'] = "<span style='color: red';>Erro: Endereço não foi cadastrado com sucesso!</span>";
	header("Location: cadastrar_user.php");	
}