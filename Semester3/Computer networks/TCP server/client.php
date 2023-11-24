 <?php

$host = "0.0.0.0";
$port = 5058;

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    echo "socket_create() failed: " . socket_strerror(socket_last_error()) . "\n";
}

$result = socket_connect($socket, $host, $port);
if ($result === false) {
    echo "socket_connect() failed: ($result) " . socket_strerror(socket_last_error()) . "\n";
}

function communicate($socket)
{
    while (true) {
        $input_data = readline("Type an array of numbers (comma-separated): ");
        if ($input_data) {
            $data = array_map('intval', explode(',', $input_data));
            $data_string = json_encode($data); // Serialize with JSON

            socket_write($socket, $data_string, strlen($data_string));
            $received_data = socket_read($socket, 1024);

            if ($received_data === false) {
                echo "Error reading data from the socket: " . socket_strerror(socket_last_error()) . "\n";
                break;
            }

            $received_data = json_decode($received_data, true);

            if ($received_data === null) {
                echo "Error decoding JSON data from the socket\n";
                break;
            }

            echo "Sorted data: " . implode(', ', $received_data) . "\n";
        } else {
            echo "Empty array\n";
            break;
        }
    }
}

communicate($socket);

socket_close($socket);

?>
