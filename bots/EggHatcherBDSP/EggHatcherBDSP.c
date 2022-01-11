/*
Pokemon Sword & Shield Turbo A button - Proof-of-Concept

Based on the LUFA library's Low-Level Joystick Demo
	(C) Dean Camera
Based on the HORI's Pokken Tournament Pro Pad design
	(C) HORI

This project implements a modified version of HORI's Pokken Tournament Pro Pad
USB descriptors to allow for the creation of custom controllers for the
Nintendo Switch. This also works to a limited degree on the PS3.

Since System Update v3.0.0, the Nintendo Switch recognizes the Pokken
Tournament Pro Pad as a Pro Controller. Physical design limitations prevent
the Pokken Controller from functioning at the same level as the Pro
Controller. However, by default most of the descriptors are there, with the
exception of Home and Capture. Descriptor modification allows us to unlock
these buttons for our use.
*/

#define STEPS_PER_CYCLE 255
#define STEPS_PER_LOOP 3.5
#include "../Joystick.h"
#include "Commands.h"
#include "Config.h"

// Main entry point.
int main(void)
{
    initNumLoops();
    // We'll start by performing hardware and peripheral setup.
    SetupHardware();
    // We'll then enable global interrupts for our use.
    GlobalInterruptEnable();
    // Once that's done, we'll enter an infinite loop.
    for (;;)
    {
        // We need to run our task to process and deliver data for our IN and OUT endpoints.
        HID_Task();
        // We also need to run the main USB management task.
        USB_USBTask();
    }
}

// Configures hardware and peripherals, such as the USB peripherals.
void SetupHardware(void)
{
    // We need to disable watchdog if enabled by bootloader/fuses.
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    // We need to disable clock division before initializing the USB hardware.
    //clock_prescale_set(clock_div_1);
    // We can then initialize our hardware and peripherals, including the USB stack.

#ifdef ALERT_WHEN_DONE
// Both PORTD and PORTB will be used for the optional LED flashing and buzzer.
#warning LED and Buzzer functionality enabled. All pins on both PORTB and \
PORTD will toggle when printing is done.
    DDRD = 0xFF; //Teensy uses PORTD
    PORTD = 0x0;
    //We'll just flash all pins on both ports since the UNO R3
    DDRB = 0xFF; //uses PORTB. Micro can use either or, but both give us 2 LEDs
    PORTB = 0x0; //The ATmega328P on the UNO will be resetting, so unplug it?
#endif
    // The USB stack should be initialized last.
    USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void)
{
    // We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void)
{
    // We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    // We setup the HID report endpoints.
    ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_OUT_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

    // We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void)
{
    // We can handle two control requests: a GetReport and a SetReport.

    // Not used here, it looks like we don't receive control request from the Switch.
}

// Process and deliver data from IN and OUT endpoints.
void HID_Task(void)
{
    // If the device isn't connected and properly configured, we can't do anything here.
    if (USB_DeviceState != DEVICE_STATE_Configured)
        return;

    // We'll start with the OUT endpoint.
    Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
    // We'll check to see if we received something on the OUT endpoint.
    if (Endpoint_IsOUTReceived())
    {
        // If we did, and the packet has data, we'll react to it.
        if (Endpoint_IsReadWriteAllowed())
        {
            // We'll create a place to store our data received from the host.
            USB_JoystickReport_Output_t JoystickOutputData;
            // We'll then take in that data, setting it up in our storage.
            while (Endpoint_Read_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData), NULL) != ENDPOINT_RWSTREAM_NoError)
                ;
            // At this point, we can react to this data.

            // However, since we're not doing anything with this data, we abandon it.
        }
        // Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
        Endpoint_ClearOUT();
    }

    // We'll then move on to the IN endpoint.
    Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
    // We first check to see if the host is ready to accept data.
    if (Endpoint_IsINReady())
    {
        // We'll create an empty report.
        USB_JoystickReport_Input_t JoystickInputData;
        // We'll then populate this report with what we want to send to the host.
        GetNextReport(&JoystickInputData);
        // Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
        while (Endpoint_Write_Stream_LE(&JoystickInputData, sizeof(JoystickInputData), NULL) != ENDPOINT_RWSTREAM_NoError)
            ;
        // We then send an IN packet on this endpoint.
        Endpoint_ClearIN();
    }
}

typedef enum
{
    PROCESS,
    DONE
} State_t;
State_t state = PROCESS;

#define ECHOES 2
int echoes = 0;
USB_JoystickReport_Input_t last_report;

Command tempCommand;
int durationCount = 0;

// start and end index of "Setup"
int commandIndex = 0;
int m_endIndex = 2;
uint8_t m_sequence = 0;

uint8_t m_eggCycles[] = {5, 10, 15, 20, 25, 30, 35, 40};
int m_loopCount = 0;
int m_numLoops;

// currently hatching column (1-6,7-12,etc.)
uint8_t m_column = 1;

void initNumLoops()
{
    int eggCycles = m_eggCycles[m_eggStepGroup] / 2 + m_eggCycles[m_eggStepGroup] % 2;
    m_numLoops = eggCycles * STEPS_PER_CYCLE / STEPS_PER_LOOP + 1;
}

// Prepare the next report for the host.
void GetNextReport(USB_JoystickReport_Input_t *const ReportData)
{
    // Prepare an empty report
    memset(ReportData, 0, sizeof(USB_JoystickReport_Input_t));
    ReportData->LX = STICK_CENTER;
    ReportData->LY = STICK_CENTER;
    ReportData->RX = STICK_CENTER;
    ReportData->RY = STICK_CENTER;
    ReportData->HAT = HAT_CENTER;

    // Repeat ECHOES times the last report
    if (echoes > 0)
    {
        memcpy(ReportData, &last_report, sizeof(USB_JoystickReport_Input_t));
        echoes--;
        return;
    }

    // States and moves management
    switch (state)
    {
    case PROCESS:
        // Get the next command sequence (new start and end)
        if (commandIndex == -1)
        {
            m_sequence++;

            if (m_endIndex == 71)
            {
                state = DONE;
                break;
            }
            else if (m_column > m_columnsOfEggs)
            {
                // Done press HOME
                commandIndex = 69;
                m_endIndex = 71;
                break;
            }

            if (m_sequence == 1)
            {
                // Pick up eggs from box
                commandIndex = 13 - ((m_column - 1) % 6) * 2;
                m_endIndex = 30;
            }
            else if (m_sequence == 2)
            {
                // Reset step counter
                commandIndex = 72;
                m_endIndex = 76;
            }
            else if (m_sequence == 3)
            {
                // Go back to corner
                commandIndex = 55;
                m_endIndex = 56;
            }
            else if (m_sequence == 4)
            {
                // turbo cycle
                commandIndex = 57;
                m_endIndex = 60;
                m_loopCount++;
                if (m_loopCount < m_numLoops)
                {
                    m_sequence--;
                    if (m_loopCount % 25 == 0)
                    {
                        // Left down to offset drifting
                        m_endIndex = 62;
                    }
                }
                else
                {
                    m_loopCount = 0;
                }
            }
            else if (m_sequence <= 9)
            {
                // Hatch 5 eggs
                commandIndex = 63;
                m_endIndex = 68;
            }
            else if (m_sequence == 10)
            {
                // Put eggs back to box
                commandIndex = 31;
                m_endIndex = (m_column % 6 == 0) ? 54 : 52;

                // Back to start
                m_column++;
                m_sequence = 0;
            }
        }

        memcpy_P(&tempCommand, &(m_command[commandIndex]), sizeof(Command));
        switch (tempCommand.button)
        {

        case UP_RIGHT:
            ReportData->LY = STICK_MIN;
            ReportData->LX = STICK_MAX;
            break;

        case UP_LEFT:
            ReportData->LY = STICK_MIN;
            ReportData->LX = STICK_MIN;
            break;

        case DOWN_RIGHT:
            ReportData->LY = STICK_MAX;
            ReportData->LX = STICK_MAX;
            break;

        case DOWN_LEFT:
            ReportData->LY = STICK_MAX;
            ReportData->LX = STICK_MIN;
            break;

        case X:
            ReportData->Button |= SWITCH_X;
            break;

        case Y:
            ReportData->Button |= SWITCH_Y;
            break;

        case UP:
            ReportData->LY = STICK_MIN;
            break;

        case DOWN:
            ReportData->LY = STICK_MAX;
            break;

        case LEFT:
            ReportData->LX = STICK_MIN;
            break;

        case RIGHT:
            ReportData->LX = STICK_MAX;
            break;

        case A:
            ReportData->Button |= SWITCH_A;
            break;

        case B:
            ReportData->Button |= SWITCH_B;
            break;

        case R:
            ReportData->Button |= SWITCH_R;
            break;

        case PLUS:
            ReportData->Button |= SWITCH_PLUS;
            break;

        case HOME:
            ReportData->Button |= SWITCH_HOME;
            break;

        default:
            // really nothing lol
            break;
        }

        durationCount++;

        if (durationCount > tempCommand.duration)
        {
            commandIndex++;
            durationCount = 0;

            // We reached the end of a command sequence
            if (commandIndex > m_endIndex)
            {
                commandIndex = -1;
            }
        }

        break;

    case DONE:
        return;
    }

    // Prepare to echo this report
    memcpy(&last_report, ReportData, sizeof(USB_JoystickReport_Input_t));
    echoes = ECHOES;
}