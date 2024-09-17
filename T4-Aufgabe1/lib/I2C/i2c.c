#include "i2c.h"

void I2C_Initialize()
{
    //----- Initial Settings -----
    I2C_RCC_Enable();

    GPIO_Enable(GPIOA_BASE);
    GPIO_Enable(GPIOB_BASE);

    GPIO_SetMode(I2C_SCL, GPIO_MODE_AF);
    GPIO_SetMode(I2C_SDA, GPIO_MODE_AF);

    GPIO_SetOutputType(I2C_SCL, GPIO_OTYPE_OD);
    GPIO_SetOutputType(I2C_SDA, GPIO_OTYPE_OD);

    // ----- Initialisierung -----
    // Clear PE bit
    I2C_CR1_ClearPE();

    // Configure ANFOFF and DNF
    I2C_ConfigANFOFF(I2C_ANFILTER_ENABLED);
    I2C_ConfigDNF(I2C_DNF_DISBLED);

    // PRESC, SDADEL, SCLDEL, SCLH, SCLL in I2C_TIMINGR
    I2C_TIMINGR_Config();

    // NOSTRETCH
    I2C_NOSTRETCH_Config(I2C_STRETCHING_ENABLED);

    // Set PE bit
    I2C_CR1_SetPE();
}

void I2C_SendData()
{
    I2C_MasterSendInit();
    while (1)
    {
        if (I2C_ISR_isNACKF())
        {
            break;
        }
        else
        {
            if (I2C_ISR_isTXIS())
            {
                I2C_TXDR_Write(1);
                delay_ms(5);
                if (I2C_isNBYTESTransmitted())
                {
                    I2C_ICR |= (1 << 5); // write 1 to clear STOPCF
                    break;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
    }
    I2C_CR2 &= ~(0x3FFFFFF << 0); // Reset I2C_RC2
}
void I2C_GetData()
{
    I2C_MasterGetInit();
}

// Hilfefunktionen
void I2C_RCC_Enable(void)
{
    uint32_t volatile *adresse = (uint32_t *)(0x40021000 + 0x58);
    *adresse |= (1 << 21);
}

void I2C_CR1_ClearPE()
{
    I2C_CR1 &= ~(1 << 0);
}

void I2C_CR1_SetPE()
{
    I2C_CR1 |= (1 << 0);
}

void I2C_ConfigANFOFF(int state)
{
    I2C_CR1 &= ~(1 << 12);
    I2C_CR1 |= (state << 12);
}

void I2C_ConfigDNF(int state)
{
    I2C_CR1 &= ~(0b1111 << 8);
    I2C_CR1 |= (state << 8);
}

void I2C_TIMINGR_Config()
{
    // PRESC
    I2C_TIMINGR &= ~(0b1111 << 28);
    I2C_TIMINGR |= (3 << 28);

    // SDADEL
    I2C_TIMINGR &= ~(0b1111 << 16);
    I2C_TIMINGR |= (0x2 << 16);

    // SCLDEL
    I2C_TIMINGR &= ~(0b1111 << 20);
    I2C_TIMINGR |= (0x4 << 20);

    // SCLH
    I2C_TIMINGR &= ~(0b11111111 << 8);
    I2C_TIMINGR |= (0xC3 << 8);

    // SCLL
    I2C_TIMINGR &= ~(0b11111111 << 0);
    I2C_TIMINGR |= (0xC7 << 0);
}

void I2C_NOSTRETCH_Config(int state)
{
    I2C_CR1 &= ~(1 << 17);
    I2C_CR1 |= (state << 17);
}

// SendData()

void I2C_MasterSendInit()
{
    // NBYTES = 1
    I2C_CR2 &= ~(0b11111111 << 16);
    I2C_CR2 |= (1 << 16);

    // AUTOEND = 1
    I2C_CR2 |= (1 << 25);

    I2C_ConfigSlaveAddress();

    // Transfer-Richtung RD_WRN = 0 (write transfer)
    I2C_CR2 &= ~(1 << 10);

    // Set I2C_CR2.START
    I2C_CR2 |= (1 << 13);
}

void I2C_ConfigSlaveAddress()
{
    // 7 bit mode (ADD10 = 0)
    I2C_CR2 &= ~(1 << 11);

    // Slave address
    I2C_CR2 &= ~(0b1111111 << 1);
    I2C_CR2 |= (87 << 1);
}

int I2C_ISR_isNACKF()
{
    return ((I2C_ISR >> 4) & 1);
}

int I2C_ISR_isTXIS()
{
    return ((I2C_ISR >> 1) & 1);
}
void I2C_TXDR_Write(int data)
{
    I2C_TXDR &= ~(0b11111111 << 0);
    I2C_TXDR |= (data << 0);
}

int I2C_isNBYTESTransmitted()
{
    return ((I2C_CR2 >> 14) & 1); // Check STOP bit in I2C_CR2
}

void I2C_MasterGetInit()
{
    // NBYTES = 3
    I2C_CR2 &= ~(0b11111111 << 16);
    I2C_CR2 |= (3 << 16);

    // AUTOEND = 1
    I2C_CR2 |= (1 << 25);

    // Transfer-Richtung RD_WRN = 1 (read transfer)
    I2C_CR2 |= (1 << 10);

    // TXIE aktivieren
    I2C_CR1 |= (1 << 2);

    // Priorität festlegen
    NVIC_SetPriority(I2C1_EV_IRQn, 2);
    // Interrupt aktivieren
    NVIC_EnableIRQ(I2C1_EV_IRQn);

    // Set I2C_CR2.START
    I2C_CR2 |= (1 << 13);
}

void I2C1_EV_IRQHandler()
{
    while (1)
    {
        if (I2C_ISR_isRXNE())
        {
            I2C_RCDR_Read();
        }
        else
        {
            continue;
        }
    }
}

int I2C_ISR_isRXNE()
{
    return ((I2C_ISR >> 2) & 1);
}

int I2C_RCDR_Read()
{
    return I2C_RXDR;
}