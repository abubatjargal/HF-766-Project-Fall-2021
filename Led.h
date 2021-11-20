int ledBlink(int pin, int cycles, int onDuration, int offDuration) {

  // Input Validations
  if(pin < 2 || pin > 8 || cycles < 0 || onDuration < 0 || offDuration < 0){
    return 0;
  }
  
  for (int i = 0; i < cycles; i++){
    digitalWrite(pin, HIGH);
    delay(onDuration);
    digitalWrite(pin, LOW);
    delay(offDuration);
  }
  return 1;
}
