import processing.serial.*;

Serial myPort;

void setup() {
  
  size(500,500);
  
  rectColor = color(0);
  rectHighlight = color(51);
  rectX = width/2-rectSize-10;
  rectY = height/2-rectSize/2;
  
  
  String portName = Serial.list()[2];
  
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
}

void serialEvent(Serial myPort) {
  String msg = myPort.readStringUntil('\n');
  println(msg);
}

void draw() {
  drawButton();
}

void mousePressed() {
  if (rectOver) {
    myPort.write('1');
  }
}
