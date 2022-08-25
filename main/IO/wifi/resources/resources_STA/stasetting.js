var websocket = new WebSocket("ws://" + location.hostname + "/");

function sendText(text) 
	{
   	websocket.send(text);
	}
 
websocket.onopen = function(evt) 
	{
  	console.log('WebSocket connection opened');
	}
websocket.onmessage = function(evt) 
	{
  	var msg = evt.data;
  	
  	var myJsonObj = JSON.parse(msg);
  	  	
  	if (("name" in myJsonObj)==1)
  		{
  		document.getElementById("name").value = myJsonObj.name;
  		}
  	
  	if (("location" in myJsonObj)==1)
		{
		document.getElementById("location").value = myJsonObj.location;
		}
		
   	if (("steermode" in myJsonObj)==1)
		{
		document.getElementById("steermode").value = myJsonObj.steermode;
		showmenudepsteer(myJsonObj.steermode);
		} 	
		
   	if (("perc" in myJsonObj)==1)
		{
		document.getElementById("perc").value = myJsonObj.perc;
		document.getElementById("perc_display").innerHTML = myJsonObj.perc;
		} 	

   	if (("timeonhour" in myJsonObj)==1)
		{
		document.getElementById("timeonhour").value = myJsonObj.timeonhour;
		} 	
   	if (("timeonmin" in myJsonObj)==1)
		{
		document.getElementById("timeonmin").value = myJsonObj.timeonmin;
		} 	

   	if (("timeoffhour" in myJsonObj)==1)
		{
		document.getElementById("timeoffhour").value = myJsonObj.timeoffhour;
		} 	
   	if (("timeoffmin" in myJsonObj)==1)
		{
		document.getElementById("timeoffmin").value = myJsonObj.timeoffmin;
		} 	



//   	if (("rise" in myJsonObj)==1)
//		{
//		document.getElementById("rise").innerHTML = myJsonObj.rise;
//		} 	
//   	if (("fall" in myJsonObj)==1)
//		{
//		document.getElementById("fall").innerHTML = myJsonObj.fall;
//		} 	


   	if (("limitlo" in myJsonObj)==1)
		{
		document.getElementById("limitlo").value = myJsonObj.limitlo;
		document.getElementById("limitlo_display").innerHTML = myJsonObj.limitlo;
		} 	
   	if (("limithi" in myJsonObj)==1)
		{
		document.getElementById("limithi").value = myJsonObj.limithi;
		document.getElementById("limithi_display").innerHTML = myJsonObj.limithi;
		} 	
   	if (("perc" in myJsonObj)==1)
		{
		document.getElementById("limitsh").value = myJsonObj.limitsh;
		document.getElementById("limitsh_display").innerHTML = myJsonObj.limitsh;
		} 			

//   	if (("limitlo" in myJsonObj)==1)
//		{
//		document.getElementById("limitlo").innerHTML = myJsonObj.limitlo;
//		} 	
//   	if (("limithi" in myJsonObj)==1)
//		{
//		document.getElementById("limithi").innerHTML = myJsonObj.limithi;
//		} 	
//   	if (("limitsh" in myJsonObj)==1)
//		{
//		document.getElementById("limitsh").innerHTML = myJsonObj.limitsh;
//		} 	

	}
	
websocket.onclose = function(evt) 
	{
  	console.log('Websocket connection closed');
	}

websocket.onerror = function(evt) 
	{
  	console.log('Websocket error: ' + evt);
	}


function showmenudepsteer(mode) 
    {
    if (mode=='wifi')
    	{
		document.getElementById("maxitable1").style.visibility = "visible" 
		document.getElementById("maxitable2").style.visibility = "visible" 
		document.getElementById("maxitable3").style.visibility = "visible" 
		document.getElementById("maxitable4").style.visibility = "visible" 
		}
	else
    	{
		document.getElementById("maxitable1").style.visibility = "hidden" 
		document.getElementById("maxitable2").style.visibility = "hidden" 
		document.getElementById("maxitable3").style.visibility = "hidden" 
		document.getElementById("maxitable4").style.visibility = "hidden" 
    	}
    }


function initDropdownList( id, min, max, increment, selectedval ) 
	{
    var select, i, option;
    
    select = document.getElementById( id );
    for ( i = min; i <= max; i += increment ) 
    	{
        option = document.createElement( 'option' );
        option.value = option.text = i;
        if (selectedval == i)
       	 	{
       	 	option.selected = true;
        	}
        	
        select.add( option );
    	}
	}

function steermodechanged(chosen) 
    {
	showmenudepsteer(chosen);
    }









