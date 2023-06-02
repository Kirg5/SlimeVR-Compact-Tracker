#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000UL

int main(void)
{
    // Set PB1 and PB2 as outputs
    DDRB |= (1 << PB1) | (1 << PB2);

    // Enable internal pull-up resistor on PB0
    PORTB |= (1 << PB0);

    // Set initial states of PB1 and PB2
    PORTB &= ~(1 << PB1);
    PORTB |= (1 << PB2);

    // Variables to keep track of button clicks
    uint8_t clicks = 0;
    uint32_t last_click = 0;
    uint32_t press_duration = 0;

    while (1)
    {
        // Check if the button is pressed
        if (!(PINB & (1 << PB0)))
        {
            // Record the press duration if the button is pressed
            if (press_duration == 0)
            {
                press_duration = millis();
            }

            // If it's been less than 1 second since the last click
            if (clicks > 0 && (millis() - last_click) < 1000)
            {
                // Do nothing
            }
            else
            {
                // If the press duration is greater than 1 second, toggle PB1 state
                if ((millis() - press_duration) > 1000)
                {
                    PORTB ^= (1 << PB1);
                }
                // Otherwise, turn PB2 on for 50ms
                else
                {
                    PORTB &= ~(1 << PB2);
                    _delay_ms(100);
                    PORTB |= (1 << PB2);
                }

                // Record the current time and increment the click counter
                last_click = millis();
                clicks++;
            }
        }
        else
        {
            // Reset the click counter and press duration if the button is not pressed
            clicks = 0;
            press_duration = 0;
        }
    }
}

// Returns the number of milliseconds since the program started
uint32_t millis()
{
    static uint32_t ms = 0;
    ms++;
    _delay_ms(1);
    return ms;
}
