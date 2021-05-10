
//==============================================================================
//                             COM port Selection
//==============================================================================

/* When the user clicks on the button,
toggle between hiding and showing the dropdown content */
function getPortList() {
  var portrqst = new XMLHttpRequest();
  portrqst.open("GET","list_ports",true);
  portrqst.onreadystatechange = function(){
    //get response text, parse space seperated list
    var str = portrqst.responseText;
    var strArray = str.split(" ");

    //kill all children
    var root = document.getElementById("myDropdown");
    while(root.firstChild){
      root.removeChild(root.firstChild);
    }

    //package list into options
    for(var i = 0; i < strArray.length; i++){
      var option = document.createElement("p");
      var text = document.createTextNode(strArray[i]);
      option.id = strArray[i];
      option.classList.add();

      option.onclick = function(event){
        //send request to server to open port selected
        var name = event.target.id;
        var openrqst = new XMLHttpRequest();
        var port = "open_port/" + name;
        openrqst.open("GET",port,true);

        openrqst.onreadystatechange = function(){
          //update the success of opening port
          var successMsg = openrqst.responseText;
          var textfield = document.getElementById("portname");
          textfield.value = name + " " + successMsg;
        }

        openrqst.send();
      };

      option.appendChild(text);
      root.appendChild(option);
    }

    //show options
    root.classList.toggle("show");
  }
  portrqst.send();
}

// Close the dropdown menu if the user clicks outside of it
window.onclick = function(event) {
  if (!event.target.matches('.dropbtn')) {

    var dropdowns = document.getElementsByClassName("portselect-content");
    var i;
    for (i = 0; i < dropdowns.length; i++) {
      var openDropdown = dropdowns[i];
      if (openDropdown.classList.contains('show')) {
        openDropdown.classList.remove('show');
      }
    }
  }
}
