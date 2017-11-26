<?php
session_start();
include_once("conexao.php");
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
		<?php
		if(isset($_SESSION['msg'])){
			echo $_SESSION['msg'];
			unset($_SESSION['msg']);
		}
		?>
<form id="cadastro" name="cadastro" method="post" action="processa_cad.php" onsubmit="return validaCampo(); return false;">
<div style="position:absolute; top: 80px; left: 20px;">
  <table width="800" border="0">
    <tr>
      <td width="87">Nome:</td>
      <td width="528"><input name="nome" type="text" id="nome" size="70" maxlength="60" />
        <span class="style1">*</span></td>
    </tr>
    <tr>
      <td>Email:</td>
      <td><input name="email" type="text" id="email" size="70" maxlength="60" />
      <span class="style1">*</span></td>
    </tr>
    <td>CPF:</td>
      <td><input name="cpf" type="text" id="cpf" size="13" maxlength="11" />
      <span class="style1">*</span>
      <span class="style3">Apenas n&uacute;meros</span> </td>
    </tr>
    <tr>
      <td>DDD:</td>
      <td><input name="ddd" type="text" id="ddd" size="4" maxlength="2" />
      Telefone:
        <input name="telefone" type="text" id="telefone" />
        <span class="style3">Apenas n&uacute;meros</span> </td>
    </tr>
    <tr>
      <td>Endere&ccedil;o:</td>
      <td><input name="endereco" type="text" id="endereco" size="70" maxlength="70" />
        <span class="style1">*</span></td>
    </tr>
    <tr>
      <td>Cidade:</td>
      <td><input name="cidade" type="text" id="cidade" maxlength="20" />
        <span class="style1">*</span></td>
    </tr>
    <tr>
      <td>Estado:</td>
      <td><select name="estado" id="estado">
        <option>Selecione...</option>
        <option value="AC">AC</option>
        <option value="AL">AL</option>
        <option value="AP">AP</option>
        <option value="AM">AM</option>
        <option value="BA">BA</option>
        <option value="CE">CE</option>
        <option value="ES">ES</option>
        <option value="DF">DF</option>
        <option value="MA">MA</option>
        <option value="MT">MT</option>
        <option value="MS">MS</option>
        <option value="MG">MG</option>
        <option value="PA">PA</option>
        <option value="PB">PB</option>
        <option value="PR">PR</option>
        <option value="PE">PE</option>
        <option value="PI">PI</option>
        <option value="RJ">RJ</option>
        <option value="RN">RN</option>
        <option value="RS">RS</option>
        <option value="RO">RO</option>
        <option value="RR">RR</option>
        <option value="SC">SC</option>
        <option value="SP">SP</option>
        <option value="SE">SE</option>
        <option value="TO">TO</option>
          </select>
        <span class="style1">*      </span></td>
    </tr>
    <tr>
      <td>Bairro:</td>
      <td><input name="bairro" type="text" id="bairro" maxlength="20" />
        <span class="style1">*</span></td>
    </tr>
    <tr>
      <td>Latitude:</td>
      <td><input name="latitude" type="text" size="15" id="latitude" maxlength="12" />
        <span class="style1">*</span></td>
    </tr>
    <tr>
      <td>Longitude:</td>
      <td><input name="longitude" type="text" size="15" id="longitude" maxlength="12" />
        <span class="style1">*</span></td>
    </tr>
    <tr>
      <td>&Aacute;rea:</td>
      <td><input name="area" type="text" id="area" size="4" maxlength="2" />
          <span class="style1">*</span></td>
    </tr>
        <tr>
      <td>Nr. Pessoas:</td>
      <td><input name="memb_familia" type="text" id="memb_familia" size="4" maxlength="2" />
          <span class="style1">*</span></td>
    </tr>   
    <tr>
      <td colspan="2"><p><br>
        <input name="cadastrar" type="submit" id="cadastrar" value="Concluir o Cadastro!" />
        <br /><br>
          <input name="limpar" type="reset" id="limpar" value="Limpar Campos preenchidos!" />
          <br /><br>
          <span class="style1">* Campos com * s&atilde;o obrigat&oacute;rios!          </span></p>
      <p>&nbsp; </p></td>
    </tr>
  </table>
  </div>
</form>
	</body>
</html>
