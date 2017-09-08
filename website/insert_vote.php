<?php
	require_once('../mysqli_connect.php');

	$query = "INSERT INTO vote (pin, president, vice_president, tech_core, favorite_language, favorite_pet) VALUES ('$_POST[pin]','$_POST[president]','$_POST[vice_president]','$_POST[tech_core]','$_POST[favorite_language]','$_POST[favorite_pet]')";

	$response = @mysqli_query($dbc, $query);

	if($response){
		echo "1 vote added successfully!";
	} else {
		echo "Error: could not issue database query";
		echo mysqli_error($dbc);
	}
	mysqli_close($dbc);
?>
