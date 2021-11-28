int leftRectX, leftRectY;
int rightRectX, rightRectY;
int rectSize;
color rectColor, rectHighlight;

boolean leftButtonOver = false;
boolean rightButtonOver = false;

PFont f;

PImage carImage;

// Load car image for button and set size constraints
void setupButtons(int size) {
  carImage = loadImage("car.png");
  
  // Default color is gray. Highlight color is white.
  rectColor = color(140);
  rectHighlight = color(255);
  
  rectSize = size;
  
  // Constrain to right side of window
  rightRectX = int(width - size - 50);
  rightRectY = 20;
  
  // Constrain to left side of window
  leftRectX = int(50);
  leftRectY = 20;
}

void drawButtons() {
  drawLeftButton();
  drawRightButton();
  update(mouseX, mouseY);
}

// Draw left button
void drawLeftButton() {
  // Change highlight color if mouse is within bounds
  if (leftButtonOver) {
    stroke(rectHighlight);
    fill(rectHighlight);
  } else {
    stroke(rectColor);
    fill(rectColor);
  }
  strokeWeight(4);
  
  // TEXT
  textAlign(CENTER);
  textSize(50);
  text("LEFT", rectSize / 2 + 50, rectSize + 80);
  
  // IMAGE
  imageMode(CORNER);
  image(carImage, leftRectX, leftRectY, rectSize, rectSize);
  
  // BORDER RECT
  noFill();
  rect(leftRectX, leftRectY, rectSize, rectSize);
}

// Draw right button
void drawRightButton() {
  // Change highlight color if mouse is within bounds
  if (rightButtonOver) {
    stroke(rectHighlight);
    fill(rectHighlight);
  } else {
    stroke(rectColor);
    fill(rectColor);
  }
  strokeWeight(4);
  
  // TEXT
  textAlign(CENTER);
  textSize(50);
  text("RIGHT", width - rectSize / 2 - 50, rectSize + 80);
  
  // Reflect car image
  translate(width, 0);
  scale(-1, 1);
  
  // IMAGE
  imageMode(CORNER);
  image(carImage, leftRectX, leftRectY, rectSize, rectSize);
  
  // BORDER RECT
  noFill();
  rect(leftRectX, leftRectY, rectSize, rectSize);
}

// Check if mouse is hovering over left and right buttons
void update(int x, int y) {
  if (overRect(leftRectX, leftRectY, rectSize, rectSize)) {
    leftButtonOver = true;
  } else {
    leftButtonOver = false;
  }
  
  if (overRect(rightRectX, rightRectY, rectSize, rectSize)) {
    rightButtonOver = true;
  } else {
    rightButtonOver = false;
  }
}

// Returns true if mouse is within given bounds
boolean overRect(int x, int y, int width, int height)  {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}
