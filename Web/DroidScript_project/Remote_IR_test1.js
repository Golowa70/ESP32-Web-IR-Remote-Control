// app.SaveText("IP", "" );

let urlHeader = "http://";
var ip  = app.LoadText("IP"); //"http://192.168.1.183";
if(ip == undefined){
 ip = "192.168.1.183";   
}
let url = urlHeader + ip;


//Called when application is started.
function OnStart(){
      
  //Create a layout with objects vertically centered.
  lay = app.CreateLayout( "linear", "VCenter, FillXY" );  
  layBtns = app.CreateLayout( "linear", "VCenter,FillXY" );
 
  
  txt = app.CreateText("Enter IP address");
  txt.SetMargins( 0, 0.05, 0, 0 ); 
  lay.AddChild(txt);
  
  edt = app.CreateTextEdit(ip, 0.5);
  lay.AddChild(edt);
  edt.SetOnEnter(ipEnterHandler);
  
    
      //Create a button to send request.
  btn = app.CreateButton( "State", 0.3, 0.1 ); 
  btn.SetMargins( 0, 0.05, 0, 0 ); 
    btn.SetOnTouch( btn_OnTouch ); 
  layBtns.AddChild( btn ); 
  
  //Create a button to send request.
  btnON = app.CreateButton( "ON", 0.3, 0.1 ); 
  btnON.SetMargins( 0, 0.05, 0, 0 ); 
  btnON.SetOnTouch( btnON_OnTouch ); 
  layBtns.AddChild( btnON ); 
  
  //Create a button to send request.
  btnOFF = app.CreateButton( "OFF", 0.3, 0.1 ); 
  btnOFF.SetMargins( 0, 0.05, 0, 0 ); 
  btnOFF.SetOnTouch( btnOFF_OnTouch ); 
  layBtns.AddChild( btnOFF ); 
  
   //Create a button to send request.
  btnVolUp = app.CreateButton( "Vol UP", 0.3, 0.1 ); 
  btnVolUp.SetMargins( 0, 0.05, 0, 0 ); 
  btnVolUp.SetOnTouch( btnVolUp_OnTouch ); 
  layBtns.AddChild( btnVolUp ); 
  
   //Create a button to send request.
  btnVolDown = app.CreateButton( "Vol DOWN", 0.3, 0.1 ); 
  btnVolDown.SetMargins( 0, 0.05, 0, 0 ); 
  btnVolDown.SetOnTouch( btnVolDown_OnTouch ); 
  layBtns.AddChild( btnVolDown ); 
  
  lay.AddChild(layBtns);
  app.AddLayout( lay );
}

function btn_OnTouch()
{
        //Send request to remote server.
        var path = "/relay";
        
        //var params = "data=" + data.replace("\r","");
        app.HttpRequest( "get", url, path, "", HandleReply );
}

function btnON_OnTouch()
{
        //Send request to remote server.
        var path = "/relay/on";
        
        //var params = "data=" + data.replace("\r","");
        app.HttpRequest( "get", url, path, "", HandleReply );
}

function btnOFF_OnTouch()
{
        //Send request to remote server.
        var path = "/relay/off";
        
        //var params = "data=" + data.replace("\r","");
        app.HttpRequest( "get", url, path, "", HandleReply );
}

function btnVolUp_OnTouch()
{
        //Send request to remote server.
        var path = "/relay/vol_up";
        
        //var params = "data=" + data.replace("\r","");
        app.HttpRequest( "get", url, path, "", HandleReply );
}


function btnVolDown_OnTouch()
{
        //Send request to remote server.
        var path = "/relay/vol_down";
        
        //var params = "data=" + data.replace("\r","");
        app.HttpRequest( "get", url, path, "", HandleReply );
}

//Handle the servers reply.
function HandleReply( error, response )
{
      console.log(error);
      app.ShowPopup(response);
}


//  
function ipEnterHandler(){
     ip = edt.GetText();
     txt.SetText(ip);
     app.SaveText("IP", ip );
     lay.RemoveChild(edt);
     url = urlHeader + ip
}









