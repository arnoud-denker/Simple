var websocket = new WebSocket("ws://" + location.hostname + "/ws");

function sendText(text) 
	{
   	websocket.send(text);
	}

websocket.onopen = function(evt) 
	{
  	console.log('WebSocket connection opened');
    websocket.send("wsopen");
	}

websocket.onmessage = function(evt) 
	{
  	var msg = evt.data;
  	console.log(msg);
  	
  	var myJsonObj = JSON.parse(msg);

  	if (("name" in myJsonObj)==1)
  		{
  		document.getElementById("name").innerHTML = myJsonObj.name;
  		}
  	
  	if (("location" in myJsonObj)==1)
		{
		document.getElementById("location").innerHTML = myJsonObj.location;
		}
		
  	if (("ap" in myJsonObj)==1)
		{
		document.getElementById("ap").innerHTML = myJsonObj.ap;
		}		
 	
   	if (("steermode" in myJsonObj)==1)
		{
		document.getElementById("steermode").innerHTML = myJsonObj.steermode;
		} 	
 	
   	if (("runningstate" in myJsonObj)==1)
		{
		document.getElementById("runningstate").innerHTML = myJsonObj.runningstate;
		} 	
 	
  	if (("hidstatus" in myJsonObj)==1)
		{
		document.getElementById("hidstatus").innerHTML = myJsonObj.hidstatus;
		}

  	if (("output_p" in myJsonObj)==1)
		{
		document.getElementById("output_p").innerHTML = myJsonObj.output_p;
		}
			  	
  	if (("output_w" in myJsonObj)==1)
		{
		document.getElementById("output_w").innerHTML = myJsonObj.output_w;
		}

  	if (("tamb1" in myJsonObj)==1)
		{
		document.getElementById("tamb1").innerHTML = myJsonObj.tamb1;
		}
  	
  	if (("currentime" in myJsonObj)==1)
		{
		document.getElementById("currentime").innerHTML = myJsonObj.currentime;
		}
		
  	if (("timeleft" in myJsonObj)==1)
		{
		document.getElementById("timeleft").innerHTML = myJsonObj.timeleft;
		}

	//timer = 0;
	}
	
websocket.onclose = function(evt) 
	{
  	console.log('Websocket connection closed');
	}

websocket.onerror = function(evt) 
	{
  	console.log('Websocket error: ' + evt);
	}
	

var timer = 0;
function timerUp()
	{
	timer++;

	if (timer == 10)
		{
		websocket.send("timer");
		console.log('timer');
		timer = 0;
		}

//	if (timer == 0)
//		{
//		document.getElementById('error').innerHTML='';
//		}
//	else if (timer == 10)
//		{
//		document.getElementById('error').innerHTML='Connection lost, trying to reload page';
//		}
//	else if (timer > 10)
//		{
//		timer= 0;
//		location.reload();
//		}
	}	
