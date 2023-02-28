<?php
    date_default_timezone_set("Europe/Zurich");
    setcookie("contentGet", $_GET["contentGet"]);
    setcookie("contentPost", $_POST["contentPost"]);
    setcookie("lastvisit", date(DATE_RFC2822));
?>

<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>HTML Result Page for Testing</title>
</head>

<body>

<h1>Testing result</h1>

<p>content post : <?php if( isset($_POST["contentPost"]) ) {echo $_POST["contentPost"];} ?></p>
<p>content get : <?php if( isset($_GET["contentGet"]) ) {echo $_GET["contentGet"];} ?></p>
<p>content lastvisit : <?php echo $_COOKIE["lastvisit"]; ?></p>

<?php

    echo '<pre>';
    var_dump($_COOKIE);
    echo '</pre>';

    echo '<pre>';
    var_dump($_ENV);
    echo '</pre>';

    echo '<pre>';
    var_dump($_POST);
    echo '</pre>';

    echo '<pre>';
    var_dump($_GET);
    echo '</pre>';
?>

</body>

</html>
