idf_component_register(SRCS
"." 
"main.cpp" 
"Simple.cpp"
"IO/wifi/WifiUserland.cpp"
"IO/wifi/WifiSTA.cpp"
"IO/wifi/WifiAP.cpp"
                  
INCLUDE_DIRS "."

EMBED_FILES 
"IO/wifi/resources/resources_AP/aproot.html" 
"IO/wifi/resources/resources_STA/staroot.html"
"IO/wifi/resources/resources_STA/staroot.js"
"IO/wifi/resources/resources_STA/stasetting.js"
"IO/wifi/resources/resources_STA/stasetting.html"
"IO/wifi/resources/dimlux.css" 
"IO/wifi/resources/favicon.ico"

REQUIRES
"json" 
"lwip"
"esp_http_server"
"esp_netif"
"esp_hw_support"
"wifi"
)
                    
