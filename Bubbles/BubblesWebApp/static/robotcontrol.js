
//==============================================================================
//                              Global Variables
//==============================================================================

// Last mode selected variables
var last_mode = "";

// Last manual command selected
var last_command = "";

//last color set
var last_color = "ffffff"

//==============================================================================
//                           Mode Select Functions
//==============================================================================

/**
 * Sends a mode change back to Bubbles server to change hardware state
 * @param mode will only work if "off","auton",or"manual"
 */
function setMode(mode){
  //if a duplicate then ignore
  if(mode == last_mode){
    return;
  }
  last_mode = mode;

  //send request to server
  request = new XMLHttpRequest();
  request.open("GET","set_mode/" + mode,true);
  request.send();
}

/**
 * Opens the mode tab that has been clicked. Does the formatting work then
 * routes the mode data to the setMode function for server request
 * @param event is the click event
 * @param mode is the new hardware mode to set
 */
function openMode(event, mode){
    // Declare all variables
    var i, tabcontent, tablinks;

    // Get all elements with class="tabcontent" and hide them
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }

    // Get all elements with class="tablinks" and remove the class "active"
    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }

    // Show the current tab, and add an "active" class to the button that
    // opened the tab
    document.getElementById(mode).style.display = "block";
    event.currentTarget.className += " active";

    //call the mode set to server
    setMode(mode);
}

//==============================================================================
//                          Manual Command Functions
//==============================================================================

/**
 * Sets the new command for the manual mode movement of Bubbles.
 * @param command is either "forward","left""right","backward",or"stop"
 */
function setManualCommand(command){
  //if a duplicate then ignore
  if(command == last_command && last_mode != "manual"){
    return;
  }
  last_command = command;

  //send request to server
  request = new XMLHttpRequest();
  request.open("GET","move/" + command,true);
  request.send();
}

//==============================================================================
//                           Keyboard Handler
//==============================================================================

/**
 * Keyboard handler for mapping keys to the respective control buttons for
 * Bubbles.
 * @param event is the key event that occured that must be mapped to command
 */
function keypressed(event){
  var keyCd = ('charCode' in event) ? event.charCode : event.keyCode;
/*
  if(keyCd == 49){                                        // 1 = set mode off
    document.getElementById("off_btn").click();
  }

  if(keyCd == 50){                                        // 2 = set mode auton
    document.getElementById("auton_btn").click();
  }

  if(keyCd == 51){                                        //3 = set mode manual
    document.getElementById("manual_btn").click();
  }
*/
  if(last_mode == "manual" && (keyCd == 87 || keyCd == 119)){  //wW = move fwd
    document.getElementById("forward_btn").click();
  }

  if(last_mode == "manual" && (keyCd == 65 || keyCd == 97)){   //aA = move left
    document.getElementById("left_btn").click();
  }

  if(last_mode == "manual" && (keyCd == 83 || keyCd == 115)){  //sS = move bwd
    document.getElementById("backward_btn").click();
  }

  if(last_mode == "manual" && (keyCd == 68 || keyCd == 100)){  //dD = move right
    document.getElementById("right_btn").click();
  }

  if(last_mode == "manual" && keyCd == 32){                    //(space) = STOP
    document.getElementById("stop_btn").click();
  }

  if(last_mode == "manual" && (keyCd == 72 || keyCd == 104)){  //Hh = Head home
    document.getElementById("neck_home_btn").click();
  }

  if(last_mode == "manual" && (keyCd == 73 || keyCd == 105)){ //Ii = Head up
    document.getElementById("neck_up_btn").click();
  }

  if(last_mode == "manual" && (keyCd == 75 || keyCd == 107)){ //Kk = Head down
    document.getElementById("neck_down_btn").click();
  }
}

//==============================================================================
//                        Head LED control
//==============================================================================

/**
 * Sets the current color selected in the LED module
 */
function setColor(){
  request = new XMLHttpRequest();
  request.open("GET",'set_color/'+last_color,true);
  request.send();
}

/**
 * Changes the current color when a text box changes. Note that the color
 * channels will error correct for invalid data input
 */
function changeColor(){
  //get color channels
  var rtextbox = document.getElementById("r_channel");
  var gtextbox = document.getElementById("g_channel");
  var btextbox = document.getElementById("b_channel");

  //parse each for number content and check bounds for valid 0-255 range
  var r = parseInt(rtextbox.value);
  var g = parseInt(gtextbox.value);
  var b = parseInt(btextbox.value);
  if(isNaN(r) || r < 0){
    rtextbox.value = r = 0;
  }else if(r > 255){
    rtextbox.value = r = 255;
  }
  if(isNaN(g) || g < 0){
    gtextbox.value = g = 0;
  } else if(g > 255){
    gtextbox.value = g = 255;
  }
  if(isNaN(b) || b < 0){
    btextbox.value = b = 0;
  }else if(b > 255){
    btextbox.value = b = 255;
  }

  //compute new color for LEDs
  var rStr = r.toString(16);
  var gStr = g.toString(16);
  var bStr = b.toString(16)
  var hexColor = (rStr.length < 2 ? "0" : "") + rStr
                 + (gStr.length < 2 ? "0" : "") + gStr
                 + (bStr.length < 2 ? "0" : "") + bStr;

  //assign color to state var and to display
  last_color = hexColor;
  console.log(last_color);
  document.getElementById("rgb_selected").style.backgroundColor = "#" + hexColor;
}

//==============================================================================
//                            Head Position Control
//==============================================================================

/**
 * Sets the next positional step of Bubbles' head
 * @param pos is direction "up","down","home"
 */
function setNeckCommand(pos){

  //only move head in manual
  if(last_mode != "manual"){
    return;
  }

  //send head request
  request = new XMLHttpRequest();
  request.open("GET",'move_head/'+pos,true);
  request.send();
}
