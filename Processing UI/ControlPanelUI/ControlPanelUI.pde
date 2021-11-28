import processing.serial.*;

Serial myPort;

void setup() {
  // Setup canvas
  size(1200,500);
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

void mousePressed() {
  if (leftButtonOver) {
    // LEFT BUTTON CLICK
    myPort.write('1');
  } else if (rightButtonOver) {
    // RIGHT BUTTON CLICK
    myPort.write('2');
  }
}
