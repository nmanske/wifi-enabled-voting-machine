<html> 
    <head>
        <title>[EE445L] S16 Election</title>
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
            input {
                text-align: center;
            }
            .pinbutton {
                text-align: center;
            }
        </style>
        <script>
            window.onload = function generateCurrentPIN() {
                var getCurrentPIN = localStorage.getItem('CurrentPIN', getCurrentPIN);
                document.getElementById("rnum").value = getCurrentPIN;
            }

            function generateRandPIN() {
                var pin_content = new Array();

                <?php
                require_once('../mysqli_connect.php');
                ini_set('display_errors',1); 
                error_reporting(E_ALL);
                $query = "SELECT pin FROM vote";
                $response = mysqli_query($dbc,$query);
                while($row = mysqli_fetch_array($response)) { ?>
                    pin_content.push('<?php echo $row["pin"];?>');
                <?php }
                mysqli_close($dbc); ?>

                do
                    var PIN = Math.ceil(9999*Math.random()).toString();
                while((PIN.indexOf('0') > -1) || (PIN.length != 4) || (pin_content.indexOf(PIN) > -1));
                document.getElementById("rnum").value = PIN;
                localStorage.setItem('CurrentPIN',PIN);
                new Image().src = "http://ec2-54-183-227-218.us-west-1.compute.amazonaws.com/insert_pin.php?pin=" + PIN;
            }
        </script>
    </head>
    <body bgcolor=lightgray>
        <hr>
        <h1><center>[EE445L] Spring 2016 Election</center></h1>
        <center><img src="pictures/longhorns_logo.png" alt="Longhorn Logo"></center>
        <hr>
        <br><br>

        <center><input type="text" id="rnum" size="6" style="font-size: 20pt; font-family:"Courier New";" readonly></center>
        <br>
        <center><div class="pinbutton"><input type="button" value="Generate PIN" name="generate" onclick="generateRandPIN()" style="font-size: 14pt;font-family:"Courier New";"></div></center>
        <br><br>
        <center><font face="courier new" size=5><a href="individual_votes.php">Individual Voting Submissions</a></font></center>
        <br><br>
        <center><font face="courier new" size=5><a href="combined_votes.php">Combined Voting Results</a></font></center>
    </body>
</html>
