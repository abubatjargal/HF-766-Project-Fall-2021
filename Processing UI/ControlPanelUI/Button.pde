int rectX, rectY;
int rectSize = 90;
color rectColor, rectHighlight;
boolean rectOver = false;

PFont f;

void setupButton() {
  rectColor = color(0);
  rectHighlight = color(51);
  rectX = width/2-rectSize-10;
  rectY = height/2-rectSize/2;
  
  printArray(PFont.list());
  f = createFont("SpaceMono-Regular.ttf", 18);
  textFont(f);
}

void drawButton() {
  update(mouseX, mouseY);
  
  if (rectOver) {
    fill(rectHighlight);
  } else {
    fill(rectColor);
  }
  stroke(255);
  rect(rectX, rectY, rectSize, rectSize);
  
  textAlign(LEFT);
  fill(255);
  text("Left", rectX + rectSize / 2 - 10, rectY + rectSize / 2 + 5);
}

void update(int x, int y) {
  if (overRect(rectX, rectY, rectSize, rectSize)) {
    rectOver = true;
  } else {
    rectOver = false;
  }
}

boolean overRect(int x, int y, int width, int height)  {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}
