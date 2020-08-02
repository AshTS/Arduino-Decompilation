void setup()
{
  // Set the Direction for pins B5, B4, and B3 to output
  DDRB = 0b111000;
  
  // Turn on pins B3 - B5
  PORTB = 0b111000;
}
void loop()
{

}
