<html>
    <head>
        <title>[EE445L] Individual Voting Submissions</title>
        <style>
            h1 {
                font-family: "Courier New";
            }
            hr {
                display: block;
                height: 2px;
                border: 0;
                border-top: 1px solid #000;
                margin: 1em 0;
            }
            tr {
                background-color: white;
                text-align: center;
            }
            td {
                background-color: white;
                text-align: center;
            }
            .deletebutton {
                text-align: center;
            }
        </style>
    </head>
    <body bgcolor=lightgray>
    
    <hr>
    <h1><center>Individual Voting Submissions</center></h1>
    <hr>
    <?php

    require_once('../mysqli_connect.php');
    ini_set('display_errors',1); 
    error_reporting(E_ALL);

    $query = "SELECT submission_time, pin, president, vice_president, tech_core, favorite_language, favorite_pet FROM vote ORDER BY submission_time DESC";

    $response = @mysqli_query($dbc, $query);

    if ($response){
        echo '<table align="center" border="1" cellpadding="10" style="width:90%">
        <tr><td><b><u>Submission Time</u></b></td>
        <td><b><u>PIN</u></b></td>
        <td><b><u>President</u></b></td>
        <td><b><u>Vice President</u></b></td>
        <td><b><u>Tech Core</u></b></td>
        <td><b><u>Favorite Language</u></b></td>
        <td><b><u>Favorite Pet</u></b></td></tr>';

        while($row = mysqli_fetch_array($response)){
            echo '<tr><td>' .
            $row['submission_time'] . '</td><td>' .
            $row['pin'] . '</td><td>' .
            $row['president'] . '</td><td>' .
            $row['vice_president'] . '</td><td>' .
            $row['tech_core'] . '</td><td>' .
            $row['favorite_language'] . '</td><td>' .
            $row['favorite_pet'] . '</td></tr>';
        }

        echo '</table>';
    } else {
        echo "Error: could not issue database query";
        echo mysqli_error($dbc);
    }

    mysqli_close($dbc);

    ?>
    </body>
</html>
