const char index_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<HTML>
  <HEAD>
    <META name='viewport' content='width=device-width, initial-scale=1'>
    <TITLE>ESP Web Template</TITLE>
    <SCRIPT>
    var xmlHttp=createXmlHttpObject();
    function createXmlHttpObject(){
     if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
     }else{
        xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');
     }
     return xmlHttp;
    }
    function process(){
      if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
        
      }
      setTimeout('process()',2000);
    }
    function handleServerResponse(){
     if(xmlHttp.readyState==4 && xmlHttp.status==200){
       xmlResponse=xmlHttp.responseXML;
       for(i=0;i<5;i++){
        xmldoc=xmlResponse.getElementsByTagName('response'+i)[0].firstChild.nodeValue;
        document.getElementById('resp'+i).innerHTML=xmldoc;
       }
       xmldoc=xmlResponse.getElementsByTagName('freeh')[0].firstChild.nodeValue;
       document.getElementById('freeheap').innerHTML=xmldoc;
       xmldoc=xmlResponse.getElementsByTagName('rst')[0].firstChild.nodeValue;
       document.getElementById('rstreason').innerHTML=xmldoc;
     }
    }
    </SCRIPT>
    <STYLE>
      h1 {
        font-size: 120%;
        color: blue;
        margin: 0 0 10px 0;
      }
    </STYLE>
  </HEAD>
  <BODY onload='process()'>
    <CENTER>
      <H1>Hello Web user</H1>
    </CENTER>
  </BODY>
</HTML>
)====="; 
