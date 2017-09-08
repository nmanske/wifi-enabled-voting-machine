<?php
	require_once('../mysqli_connect.php');

	$query = "DELETE FROM current_pin";
	mysqli_query($dbc, $query);

	$query = "INSERT INTO current_pin VALUES ('$_GET[pin]')";
	$response = @mysqli_query($dbc, $query);

	if($response){
		echo "Pin " . $_GET['pin'] . " is now the current PIN!";
	} else {
		echo "Error: could not issue database query";
		echo mysqli_error($dbc);
	}
	mysqli_close($dbc);
?>
