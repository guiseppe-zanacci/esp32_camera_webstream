#include "credentials.h"

const char* ssid = "Wifi_network_name"; // Wifi network to connect to
const char* password = "Wifi_password"; // Password to wifi

#ifdef LIVE_SERVER

const char* websockets_server_host = "Server_IP_or_URL"; // Your server IP or URL
const int websockets_server_port = 3001; // The port your server is listening on

#endif
#ifdef TEST_SERVER

const char* websockets_server_host = "Server_IP_or_URL"; // Your server IP or URL
const int websockets_server_port = 3001; // The port your server is listening on

#endif
