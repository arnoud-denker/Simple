idf_component_register(SRCS 
"WifiEngine.cpp"
"WifiHttpsServer.cpp"
"WifiWebsocketHandler.cpp"
"WifiEngineSMART.cpp"

INCLUDE_DIRS "."
     
EMBED_TXTFILES 
"resources/certs/cacert.pem"
"resources/certs/prvtkey.pem"     
                    
REQUIRES
json
esp32 
freertos 
nvs_flash
esp_http_server
lwip
esp_netif
)
                     