idf_component_register(SRCS
"." 
"main.cpp" 
"Simple.cpp"
"IO/wifi/WifiUserland.cpp"
"IO/wifi/WifiSTA.cpp"
"IO/wifi/WifiAP.cpp"
                  
INCLUDE_DIRS "."

EMBED_FILES 
"resources/resources_AP/aproot.html" 
"resources/resources_STA/staroot.html"
"resources/resources_STA/staroot.js"
"resources/resources_STA/stasetting.js"
"resources/resources_STA/stasetting.html"
"resources/dimlux.css" 
"resources/favicon.ico"

REQUIRES
"json" 
"lwip"
"esp_http_server"
"esp_netif"
"esp_hw_support"
"wifi"
)
                    
