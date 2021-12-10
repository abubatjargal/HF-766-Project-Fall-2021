import processing.serial.*;

Serial myPort;

void setup() {
  // Setup canvas
  size(1200,800);
  surface.setTitle("Control Panel");
  surface.setResizable(true);
  
  // Import images;
  setupButtons(300);

  String portName = Serial.list()[2];
  
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
}

void serialEvent(Serial myPort) {
  String msg = myPort.readStringUntil('\n');
}

void draw() {
  background(0);
  drawButtons();
}

// 1: Left
// 2: Right
// 3: LED Enabled
// 4: LED Disabled
// 5: Vibration Enabled
// 6: Vibration Disabled

void mousePressed() {
  if (leftButtonOver) {
    // LEFT BUTTON CLICK
    myPort.write('1');
  } else if (rightButtonOver) {
    // RIGHT BUTTON CLICK
    myPort.write('2');
  } else if (ledConfigButtonOver) {
    ledEnabled = !ledEnabled;
    if (ledEnabled) {
      myPort.write('3');
    } else {
      myPort.write('4');
    }
  } else if (vibrationConfigButtonOver) {
    vibrationEnabled = !vibrationEnabled;
    if (vibrationEnabled) {
      myPort.write('5');
    } else {
      myPort.write('6');
    }
  }
}
