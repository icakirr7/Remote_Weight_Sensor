<!DOCTYPE html>
<html>
  <head>
  <script type="text/javascript">
    
    function loadArduino()
{
  
  
  const xhttp=new XMLHttpRequest();
  xhttp.onload=function(){
    
    document.getElementById("myid").innerHTML=this.responseText;
  }
  xhttp.open("GET","esp-data.php",true);
  xhttp.send();
}

   </script>   
  <style>
        body
        {
          background-color: lightgrey;
        }
        #myid
        {
          text-align:center;
          color: black;
          background-color: lightblue;
          font-size: 50px;
          
          width:800px;
          margin:0 auto;
        }
    
      
        
</style>


<?php
//header("refresh: 2;");

$servername = "localhost";

// REPLACE with your Database name
$dbname = "example_esp_data";
// REPLACE with Database user
$username = "yordam";
// REPLACE with Database user password
$password = "1234";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql_t = "SELECT id,value1,reading_time FROM SensorData ORDER BY id DESC";
$sql=mysqli_query($conn,$sql_t);
$data=mysqli_fetch_array($sql);
$val=$data["value1"];

        
    



$conn->close();
?> 
<body onload="setInterval(loadArduino,100);">

<div>
<p id="myid"><br><?php echo $val; ?>gr<br><br><br>
<a  href="https://www.marmara.edu.tr/">
         <img alt="Qries" src="https://www.marmara.edu.tr/_assets/marmara/custom/images/marmara_universitesi_logo.png?v=1.1"
         width="288" height="90"></p>

 </div>

        

</body>

</html>