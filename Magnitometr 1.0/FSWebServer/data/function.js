function val(id){
 var v = document.getElementById(id).value;
 return v;
}

function createXmlHttpObject(){
  if(window.XMLHttpRequest){
    xmlHttp = new XMLHttpRequest();
  }else{
    xmlHttp = new ActiveXObject('Microsoft.XMLHTTP');
  }
  return xmlHttp;
}

function loadBlock(data) {
  for (var key in data) {
    if (document.getElementById(key)){
      document.getElementById(key).value = Number(data[key])/100000;
    }
  }
}

// ------------------------------------------------------------------------------------------------------ Загрузка

function load(){
  var xmlHttp=createXmlHttpObject();
  if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
    xmlHttp.open('GET','/configs.json',true);
    xmlHttp.responseType = "json";
    xmlHttp.onload = () => {
      console.log(xmlHttp.response);
      //data = JSON.parse(xmlHttp.response);
      loadBlock(xmlHttp.response);
    }
    xmlHttp.send()
  }
}

// ------------------------------------------------------------------------------------------------------ Автообновление

setInterval(WebRefresh,3000);

function WebRefresh(){
  var xml=createXmlHttpObject();
  xml.responseType = "json";
  xml.open('GET', '/Refresh', true);
  xml.onreadystatechange = function() {
    if (xml.readyState == 4 && xml.status == 200) {
      //document.getElementById("test").value = xmlHttp.responseText;
      //console.log(xml.responseText);
      console.log(xml.response);
      loadBlock(xml.response);
    }
  }
  xml.send();
}

// ------------------------------------------------------------------------------------------------------ Создание файлов

function createStrforSave(type){
  var str = "";
  for (i = 0; i < 11; i++){
    for (j = 0; j < 11; j++){
      str += document.getElementById((type + (11*j+i))).value + ";";
    }
    str += "\n";
  }
return str
}

function downloadFile(type){
  text = createStrforSave(type);
  //console.log(text);
  const url = window.URL.createObjectURL(new Blob([text], {type:'text/csv'}));
  const link = document.createElement("a");
  link.href = url;
  link.setAttribute("download", type);
  document.body.appendChild(link);
  link.click();
  document.body.removeChild(link);
  window.URL.revokeObjectURL(url);
}

// ------------------------------------------------------------------------------------------------------

function SetZero(){

}

function SaveSettings(){
  server = "/Settings?status=1";
  send_request(server);
}

function ResetSettings(){
  server = "/Settings?status=0";
  send_request(server);
}

function saveZero(number, zero){
  server = "/Zero?number=" + number + "=" + zero*100000;
  send_request(server);
}

function saveSens(number, sens){
  server = "/Sens?number=" + number + "=" + sens*100000;
  send_request(server);
}

function send_request(server){
  request = new XMLHttpRequest();
  request.open("GET", server, true);
  request.send();
}
