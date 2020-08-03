// Setting values to specific addresses in memory
volatile unsigned char* TCCR0A = 0x800044;
volatile unsigned char* TCCR0B = 0x800045;
volatile unsigned char* TOIE0 = 0x80006e;
volatile unsigned char* TCCR1B = 0x800081;
volatile unsigned char* TCCR1A = 0x800080;
volatile unsigned char* TCCR2B = 0x8000B1;
volatile unsigned char* TCCR2A = 0x8000B0;
volatile unsigned char* ADCSRA = 0x80007A;
volatile unsigned char* UCSR0B = 0x8000C1;

volatile unsigned short* STACKPOINTER = 0x80005D;
volatile unsigned char* DDRB = 0x800024;
volatile unsigned char* PORTB = 0x800025;

volatile unsigned short* X = 0x80003A;

// Variables for the program
volatile unsigned int* VAR_0_u32 = 0x800100;
volatile unsigned char* VAR_1_u8 = 0x800104;
volatile unsigned int* VAR_2_u32 = 0x800105;


// Called when the RESET Interrupt is triggered
void reset()
{
    // Set the stack pointer to 0x8FF
    *STACKPOINTER = 0x08FF; 

    // Zero the region from 0x100 to 0x108
    // unsigned short* i = 0x800100;
    // do
    // {
    //     *(i++) = 0;
    // } while (i != 0x109);
    *VAR_0_u32 = 0;
    *VAR_1_u8 = 0;
    *VAR_2_u32 = 0;
    
    // Call what is presumably setup
    func0();
}

// Mysterious interrupt handler, possibly somekind of timer for the mills and micro functions
void INT_H1()
{
    // Lots of registers are backed up, but can be ignored here because C!

    if (3 + *VAR_1_u8 < 0x7D) // The three is added here because the variable gets reused in the else branch to avoid the extra += 3
    {
        *VAR_1_u8 += 0x86;
    }
    else
    {
        *VAR_1_u8 += 3;
        *VAR_2_u32 += 1;
    }

    *VAR_0_u32 += 1;
    
    // Restore the stuff that was backed up and return from interrupt
}

// Presumably setup with some extra code there
void func0()
{
    // Set WGM01
    *TCCR0A |= 0b010;
    // Set WGM00
    *TCCR0A |= 0b001;

    // Set CS01
    *TCCR0B |= 0b010;
    // Set CS00
    *TCCR0B |= 0b001;

    // Set TOIE0
    *TOIE0 = 1;

    // Clear TCCR1B
    *TCCR1B = 0;

    // Set CS11
    *TCCR1B |= 0b010;
    // Set CS10
    *TCCR1B |= 0b001;

    // Set WGM10
    *TCCR1A |= 0b001;

    // Set CS22
    *TCCR2B |= 0b010;

    // Set WGM20
    *TCCR1A |= 0b001;

    // Set ADPS2
    *ADCSRA |= 0b100;
    // Set ADPS1
    *ADCSRA |= 0b010;
    // Set ADPS0
    *ADCSRA |= 0b001;
    // Set ADEB
    *ADCSRA |= 0b10000000;

    // Clear UCSR0B
    *UCSR0B = 0;

    // void setup()
    //{
        // // Set the Direction for pins B5, B4, and B3 to output
        *DDRB = 0x38;

        // // Turn on pins B3 - B5
        *PORTB = 0x38;
    //}
    
    for(;;)
    {
        // There is some extra odd stuff here
        *X = 0;
        do {*X -= 0;} while (*X == 0);

        // Call...... Something? gave an address of zero in the code, which would go to the beginning of restart() again...
    }

    cli(); // From the avr library, just connects down to the assembly instruction
    for (;;) {}
}
