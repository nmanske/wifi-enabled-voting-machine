<?php

require_once('../mysqli_connect.php');
ini_set('display_errors',1); 
error_reporting(E_ALL);
$query = "SELECT pin FROM current_pin";
$response = mysqli_query($dbc,$query);
while($row = mysqli_fetch_array($response)) {
    echo "CURRENT PIN: " . $row['pin'];
}
mysqli_close($dbc);

?>