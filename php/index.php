<?php
$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "zigbee";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT * FROM CMD";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
        echo "<table>";
        echo "<tr>";
                echo "<th>NODE_ID</th>";
                echo "<th>TIME    </th>";
                echo "<th>LED_STATUS</th>";
                echo "<th>DIM</th>";
                echo "<th>STATUS</th>";
            echo "</tr>";
    while($row =mysqli_fetch_array($result)) {
//      echo "+------+------+--------------+". "<br>";
//        echo "| " . $row["NODE_ID"]. "  | " . $row["LED_STATUS"]. " | " . $row["TIME"]. " | <br>";
//      echo "+------+------+--------------+". "<br>";
        echo "<tr>";
                echo "<td>" . $row['NODE_ID'] . "</td>";
                echo "<td>" . $row['TIME'] . "</td>";
                echo "<td>" . $row['LED_STATUS'] . "</td>";
                echo "<td>" . $row['LED_DIM'] . "</td>";
                echo "<td>" . $row['NODE_STATUS'] . "</td>";

            echo "</tr>";
  }
//      echo "+------+------+--------------+". "<br>";
echo "<table>";
} else {
    echo "0 results";
}
//
$sql = "SELECT * FROM mapping";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
        echo "<table>";
        echo "<tr>";
                echo "<th>NODE_ID</th>";
                echo "<th>IP address    </th>";
            echo "</tr>";
    while($row =mysqli_fetch_array($result)) {
//      echo "+------+------+--------------+". "<br>";
//        echo "| " . $row["NODE_ID"]. "  | " . $row["LED_STATUS"]. " | " . $row["TIME"]. " | <br>";
//      echo "+------+------+--------------+". "<br>";
        echo "<tr>";
                echo "<td>" . $row['ID'] . "</td>";
                echo "<td>" . $row['IP'] . "</td>";

            echo "</tr>";
  }
//      echo "+------+------+--------------+". "<br>";
echo "<table>";
} else {
    echo "0 results";
}

//
$conn->close();
?>

