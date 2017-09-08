<html>
    <head>
        <title>[EE445L] Combined Voting Results</title>
        <style>
            h1, h2 {
                font-family: "Courier New";
            }
            hr {
                display: block;
                height: 2px;
                border: 0;
                border-top: 1px solid #000;
            }
        </style>
    </head>
    <body bgcolor="lightgray">
    <script src="toggle_image.js"></script>
    <hr style="margin: 1em 0;">
    <h1><center>Combined Voting Results</center></h1>
    <hr style="margin: 1em 0;">

    <?php

    require_once('../mysqli_connect.php'); 
    include("../lib/pChart/class/pData.class.php");
    include("../lib/pChart/class/pDraw.class.php");
    include("../lib/pChart/class/pImage.class.php");
    include("../lib/pChart/class/pPie.class.php");

    ini_set('display_errors',1); 
    error_reporting(E_ALL);

    // Fetch data from MySQL database
    $query = "SELECT * FROM vote";
    $response = mysqli_query($dbc,$query);

    while($row = mysqli_fetch_array($response)) {
        $president_r[] = $row["president"];
        $vice_president_r[] = $row["vice_president"];
        $tech_core_r[] = $row["tech_core"];
        $favorite_language_r[] = $row["favorite_language"];
        $favorite_pet_r[] = $row["favorite_pet"];
    }

    $president = array_count_values(array_values(array_filter($president_r)));
    $vice_president = array_count_values(array_values(array_filter($vice_president_r)));
    $tech_core = array_count_values(array_values(array_filter($tech_core_r)));
    $favorite_language = array_count_values(array_values(array_filter($favorite_language_r)));
    $favorite_pet = array_count_values(array_values(array_filter($favorite_pet_r)));

    // =========================================================================================================================================

    /**********************
     * PRESIDENT PIE CHART
     **********************/

    // Dataset definition
    $data = new pData();
    $data->addPoints($president,"President");

    // Define abissa serie
    $data->addPoints(array("Bard","Patt","Telang","Valvano"),"presCandidates");
    $data->setAbscissa("presCandidates");

    // Create pChart object
    $presidentImage = new pImage(575,375,$data,TRUE);

    // Draw a solid background
    $backgroundSettings = array("R"=>220, "G"=>220, "B"=>220, "Dash"=>1, "DashR"=>127, "DashG"=>127, "DashB"=>127);
    $presidentImage->drawFilledRectangle(0,0,574,374,$backgroundSettings);

    // Set the default font properties
    $presidentImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));

    // Create the pPie object
    $presidentPie = new pPie($presidentImage,$data);

    // Write the legend box
    $presidentImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));
    $presidentPie->drawPieLegend(425,235,array("Style"=>LEGEND_BOX,"Mode"=>LEGEND_VERTICAL,"R"=>220,"G"=>220,"B"=>220,"Alpha"=>100,"Margin"=>9,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0));

    // Draw the border
    $presidentImage->drawRectangle(0,0,574,374,array("R"=>0,"G"=>0,"B"=>0));

    // Draw the pie chart (with percentage)
    $pieSettings = array("Radius"=>150,"Border"=>TRUE,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0,"WriteValues"=>PIE_VALUE_PERCENTAGE,"ValueR"=>0,"ValueG"=>0,"ValueB"=>0,"Precision"=>0);
    $presidentPie->draw2DPie(245,200,$pieSettings);

    // Render image (with percentage)
    $presidentImage->render("pictures/president_percentage.png");

    // =========================================================================================================================================

    // Create pChart object
    $presidentImage = new pImage(575,375,$data,TRUE);

    // Draw a solid background (for natural)
    $backgroundSettings = array("R"=>220, "G"=>220, "B"=>220, "Dash"=>1, "DashR"=>127, "DashG"=>127, "DashB"=>127);
    $presidentImage->drawFilledRectangle(0,0,574,374,$backgroundSettings);

    // Set the default font properties (for natural)
    $presidentImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));

    // Create the pPie object (for natural)
    $presidentPie = new pPie($presidentImage,$data);

    // Write the legend box (for natural)
    $presidentImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));
    $presidentPie->drawPieLegend(425,235,array("Style"=>LEGEND_BOX,"Mode"=>LEGEND_VERTICAL,"R"=>220,"G"=>220,"B"=>220,"Alpha"=>100,"Margin"=>9,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0));

    // Draw the border (for natural)
    $presidentImage->drawRectangle(0,0,574,374,array("R"=>0,"G"=>0,"B"=>0));

    // Draw the pie chart (for natural)
    $pieSettings = array("Radius"=>150,"Border"=>TRUE,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0,"WriteValues"=>PIE_VALUE_NATURAL,"ValueR"=>0,"ValueG"=>0,"ValueB"=>0,"Precision"=>0);
    $presidentPie->draw2DPie(245,200,$pieSettings);

    // Render image (for natural)
    $presidentImage->render("pictures/president_natural.png");

    // =========================================================================================================================================

    /****************************
     * VICE PRESIDENT PIE CHART
     ***************************/

    // Dataset definition
    $data = new pData();
    $data->addPoints($vice_president,"Vice President");

    // Define abissa serie
    $data->addPoints(array("Mahesh","Dylan","Ryan"),"vicePresCandidates");
    $data->setAbscissa("vicePresCandidates");

    // Create pChart object
    $vicePresidentImage = new pImage(575,375,$data,TRUE);

    // Draw a solid background
    $backgroundSettings = array("R"=>220, "G"=>220, "B"=>220, "Dash"=>1, "DashR"=>127, "DashG"=>127, "DashB"=>127);
    $vicePresidentImage->drawFilledRectangle(0,0,574,374,$backgroundSettings);

    // Set the default font properties
    $vicePresidentImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));

    // Create the pPie object
    $vicePresidentPie = new pPie($vicePresidentImage,$data);

    // Draw the pie chart (with percentage)
    $pieSettings = array("Radius"=>150,"Border"=>TRUE,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0,"WriteValues"=>PIE_VALUE_PERCENTAGE,"ValueR"=>0,"ValueG"=>0,"ValueB"=>0,"Precision"=>0);
    $vicePresidentPie->draw2DPie(245,200,$pieSettings);

     // Write the legend box
    $vicePresidentImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));
    $vicePresidentPie->drawPieLegend(425,235,array("Style"=>LEGEND_BOX,"Mode"=>LEGEND_VERTICAL,"R"=>220,"G"=>220,"B"=>220,"Alpha"=>100,"Margin"=>9,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0));

    // Draw the border
    $vicePresidentImage->drawRectangle(0,0,574,374,array("R"=>0,"G"=>0,"B"=>0));

    // Render image (with percentage)
    $vicePresidentImage->render("pictures/vice_percentage.png");

    // =========================================================================================================================================

    // Create pChart object
    $vicePresidentImage = new pImage(575,375,$data,TRUE);

    // Draw a solid background (for natural)
    $backgroundSettings = array("R"=>220, "G"=>220, "B"=>220, "Dash"=>1, "DashR"=>127, "DashG"=>127, "DashB"=>127);
    $vicePresidentImage->drawFilledRectangle(0,0,574,374,$backgroundSettings);

    // Set the default font properties (for natural)
    $vicePresidentImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));

    // Create the pPie object (for natural)
    $vicePresidentPie = new pPie($vicePresidentImage,$data);

    // Draw the pie chart (for natural)
    $pieSettings = array("Radius"=>150,"Border"=>TRUE,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0,"WriteValues"=>PIE_VALUE_NATURAL,"ValueR"=>0,"ValueG"=>0,"ValueB"=>0,"Precision"=>0);
    $vicePresidentPie->draw2DPie(245,200,$pieSettings);

    // Write the legend box (for natural)
    $vicePresidentImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));
    $vicePresidentPie->drawPieLegend(425,235,array("Style"=>LEGEND_BOX,"Mode"=>LEGEND_VERTICAL,"R"=>220,"G"=>220,"B"=>220,"Alpha"=>100,"Margin"=>9,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0));

    // Draw the border (for natural)
    $vicePresidentImage->drawRectangle(0,0,574,374,array("R"=>0,"G"=>0,"B"=>0));

    // Render image (for natural)
    $vicePresidentImage->render("pictures/vice_natural.png");

    // =========================================================================================================================================

    /***********************
     * TECH CORE PIE CHART
     ***********************/

    // Dataset definition
    $data = new pData();
    $data->addPoints($tech_core,"Tech Core");

    // Define abissa serie
    $data->addPoints(array("Embedded","Software","Other"),"techCoreOptions");
    $data->setAbscissa("techCoreOptions");

    // Create pChart object
    $techCoreImage = new pImage(575,375,$data,TRUE);

    // Draw a solid background
    $backgroundSettings = array("R"=>220, "G"=>220, "B"=>220, "Dash"=>1, "DashR"=>127, "DashG"=>127, "DashB"=>127);
    $techCoreImage->drawFilledRectangle(0,0,574,374,$backgroundSettings);

    // Set the default font properties
    $techCoreImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));

    // Create the pPie object
    $techCorePie = new pPie($techCoreImage,$data);

    // Write the legend box
    $techCoreImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));
    $techCorePie->drawPieLegend(425,235,array("Style"=>LEGEND_BOX,"Mode"=>LEGEND_VERTICAL,"R"=>220,"G"=>220,"B"=>220,"Alpha"=>100,"Margin"=>9,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0));

    // Draw the border
    $techCoreImage->drawRectangle(0,0,574,374,array("R"=>0,"G"=>0,"B"=>0));

    // Draw the pie chart (with percentage)
    $pieSettings = array("Radius"=>150,"Border"=>TRUE,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0,"WriteValues"=>PIE_VALUE_PERCENTAGE,"ValueR"=>0,"ValueG"=>0,"ValueB"=>0,"Precision"=>0);
    $techCorePie->draw2DPie(245,200,$pieSettings);

    // Render image (with percentage)
    $techCoreImage->render("pictures/core_percentage.png");

    // =========================================================================================================================================

    // Create pChart object
    $techCoreImage = new pImage(575,375,$data,TRUE);

    // Draw a solid background (for natural)
    $backgroundSettings = array("R"=>220, "G"=>220, "B"=>220, "Dash"=>1, "DashR"=>127, "DashG"=>127, "DashB"=>127);
    $techCoreImage->drawFilledRectangle(0,0,574,374,$backgroundSettings);

    // Set the default font properties (for natural)
    $techCoreImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));

    // Create the pPie object (for natural)
    $techCorePie = new pPie($techCoreImage,$data);

    // Write the legend box (for natural)
    $techCoreImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));
    $techCorePie->drawPieLegend(425,235,array("Style"=>LEGEND_BOX,"Mode"=>LEGEND_VERTICAL,"R"=>220,"G"=>220,"B"=>220,"Alpha"=>100,"Margin"=>9,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0));

    // Draw the border (for natural)
    $techCoreImage->drawRectangle(0,0,574,374,array("R"=>0,"G"=>0,"B"=>0));

    // Draw the pie chart (for natural)
    $pieSettings = array("Radius"=>150,"Border"=>TRUE,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0,"WriteValues"=>PIE_VALUE_NATURAL,"ValueR"=>0,"ValueG"=>0,"ValueB"=>0,"Precision"=>0);
    $techCorePie->draw2DPie(245,200,$pieSettings);

    // Render image (for natural)
    $techCoreImage->render("pictures/core_natural.png");

    // =========================================================================================================================================

    /******************************
     * FAVORITE LANGUAGE PIE CHART
     *****************************/

    // Dataset definition
    $data = new pData();
    $data->addPoints($favorite_language,"Favorite Language");

    // Define abissa serie
    $data->addPoints(array("C/C++","Java","Python","Other"),"languageOptions");
    $data->setAbscissa("languageOptions");

    // Create pChart object
    $languageImage = new pImage(575,375,$data,TRUE);

    // Draw a solid background
    $backgroundSettings = array("R"=>220, "G"=>220, "B"=>220, "Dash"=>1, "DashR"=>127, "DashG"=>127, "DashB"=>127);
    $languageImage->drawFilledRectangle(0,0,574,374,$backgroundSettings);

    // Set the default font properties
    $languageImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));

    // Create the pPie object
    $languagePie = new pPie($languageImage,$data);

    // Write the legend box
    $languageImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));
    $languagePie->drawPieLegend(425,235,array("Style"=>LEGEND_BOX,"Mode"=>LEGEND_VERTICAL,"R"=>220,"G"=>220,"B"=>220,"Alpha"=>100,"Margin"=>9,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0));

    // Draw the border
    $languageImage->drawRectangle(0,0,574,374,array("R"=>0,"G"=>0,"B"=>0));

    // Draw the pie chart (with percentage)
    $pieSettings = array("Radius"=>150,"Border"=>TRUE,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0,"WriteValues"=>PIE_VALUE_PERCENTAGE,"ValueR"=>0,"ValueG"=>0,"ValueB"=>0,"Precision"=>0);
    $languagePie->draw2DPie(245,200,$pieSettings);

    // Render image (with percentage)
    $languageImage->render("pictures/language_percentage.png");

    // =========================================================================================================================================

    // Create pChart object
    $languageImage = new pImage(575,375,$data,TRUE);

    // Draw a solid background (for natural)
    $backgroundSettings = array("R"=>220, "G"=>220, "B"=>220, "Dash"=>1, "DashR"=>127, "DashG"=>127, "DashB"=>127);
    $languageImage->drawFilledRectangle(0,0,574,374,$backgroundSettings);

    // Set the default font properties (for natural)
    $languageImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));

    // Create the pPie object (for natural)
    $languagePie = new pPie($languageImage,$data);

    // Write the legend box (for natural)
    $techCoreImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));
    $languagePie->drawPieLegend(425,235,array("Style"=>LEGEND_BOX,"Mode"=>LEGEND_VERTICAL,"R"=>220,"G"=>220,"B"=>220,"Alpha"=>100,"Margin"=>9,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0));

    // Draw the border (for natural)
    $languageImage->drawRectangle(0,0,574,374,array("R"=>0,"G"=>0,"B"=>0));

    // Draw the pie chart (for natural)
    $pieSettings = array("Radius"=>150,"Border"=>TRUE,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0,"WriteValues"=>PIE_VALUE_NATURAL,"ValueR"=>0,"ValueG"=>0,"ValueB"=>0,"Precision"=>0);
    $languagePie->draw2DPie(245,200,$pieSettings);

    // Render image (for natural)
    $languageImage->render("pictures/language_natural.png");

    // =========================================================================================================================================

    /******************************
     * FAVORITE LANGUAGE PIE CHART
     *****************************/

    // Dataset definition
    $data = new pData();
    $data->addPoints($favorite_pet,"Favorite Pet");

    // Define abissa serie
    $data->addPoints(array("Dogs","Cats","Birds","Fish"),"petOptions");
    $data->setAbscissa("petOptions");

    // Create pChart object
    $petImage = new pImage(575,375,$data,TRUE);

    // Draw a solid background
    $backgroundSettings = array("R"=>220, "G"=>220, "B"=>220, "Dash"=>1, "DashR"=>127, "DashG"=>127, "DashB"=>127);
    $petImage->drawFilledRectangle(0,0,574,374,$backgroundSettings);

    // Set the default font properties
    $petImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));

    // Create the pPie object
    $petPie = new pPie($petImage,$data);

    // Write the legend box
    $petImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));
    $petPie->drawPieLegend(425,235,array("Style"=>LEGEND_BOX,"Mode"=>LEGEND_VERTICAL,"R"=>220,"G"=>220,"B"=>220,"Alpha"=>100,"Margin"=>9,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0));

    // Draw the border
    $petImage->drawRectangle(0,0,574,374,array("R"=>0,"G"=>0,"B"=>0));

    // Draw the pie chart (with percentage)
    $pieSettings = array("Radius"=>150,"Border"=>TRUE,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0,"WriteValues"=>PIE_VALUE_PERCENTAGE,"ValueR"=>0,"ValueG"=>0,"ValueB"=>0,"Precision"=>0);
    $petPie->draw2DPie(245,200,$pieSettings);

    // Render image (with percentage)
    $petImage->render("pictures/pet_percentage.png");

    // =========================================================================================================================================

    // Create pChart object
    $petImage = new pImage(575,375,$data,TRUE);

    // Draw a solid background (for natural)
    $backgroundSettings = array("R"=>220, "G"=>220, "B"=>220, "Dash"=>1, "DashR"=>127, "DashG"=>127, "DashB"=>127);
    $petImage->drawFilledRectangle(0,0,574,374,$backgroundSettings);

    // Set the default font properties (for natural)
    $petImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));

    // Create the pPie object (for natural)
    $petPie = new pPie($petImage,$data);

    // Write the legend box (for natural)
    $techCoreImage->setFontProperties(array("FontName"=>"../lib/pChart/fonts/calibri.ttf","FontSize"=>15,"R"=>0,"G"=>0,"B"=>0));
    $petPie->drawPieLegend(425,235,array("Style"=>LEGEND_BOX,"Mode"=>LEGEND_VERTICAL,"R"=>220,"G"=>220,"B"=>220,"Alpha"=>100,"Margin"=>9,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0));

    // Draw the border (for natural)
    $petImage->drawRectangle(0,0,574,374,array("R"=>0,"G"=>0,"B"=>0));

    // Draw the pie chart (for natural)
    $pieSettings = array("Radius"=>150,"Border"=>TRUE,"BorderR"=>0,"BorderG"=>0,"BorderB"=>0,"WriteValues"=>PIE_VALUE_NATURAL,"ValueR"=>0,"ValueG"=>0,"ValueB"=>0,"Precision"=>0);
    $petPie->draw2DPie(245,200,$pieSettings);

    // Render image (for natural)
    $petImage->render("pictures/pet_natural.png");

    ?>

    <h2><center><u>President</u></center></h2>
    <center><img id="president" onclick="togglePresident()" src="pictures/president_percentage.png" alt="President Pie Chart"></center><br><br>
    <hr style="border-top:dashed 1px;">

    <h2><center><u>Vice President</u></center></h2>
    <center><img id="vice_president" onclick="toggleVicePresident()" src="pictures/vice_percentage.png" alt="Vice President Pie Chart"></center><br><br>
    <hr style="border-top:dashed 1px;">

    <h2><center><u>Tech Core</u></center></h2>
    <center><img id="tech_core" onclick="toggleTechCore()" src="pictures/core_percentage.png" alt="Tech Core Pie Chart"></center><br><br>
    <hr style="border-top:dashed 1px;">

    <h2><center><u>Favorite Language</u></center></h2>
    <center><img id="favorite_language" onclick="toggleLanguage()" src="pictures/language_percentage.png" alt="Language Pie Chart"></center><br><br>
    <hr style="border-top:dashed 1px;">

    <h2><center><u>Favorite Pet</u></center></h2>
    <center><img id="favorite_pet" onclick="togglePet()" src="pictures/pet_percentage.png" alt="Pet Pie Chart"></center><br><br>
    <hr style="border-top:dashed 1px;">

    </body>
</html>