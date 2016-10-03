/*********************************************************************
 *
 *                    SHA-2 Function Library Headers
 *
 *********************************************************************
 * FileName:        sha256.h
 * Dependencies:    None
 * Processor:       PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2012 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *        ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *        used in conjunction with a Microchip ethernet controller for
 *        the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 * IMPORTANT:  The implementation and use of third party algorithms, 
 * specifications and/or other technology may require a license from 
 * various third parties.  It is your responsibility to obtain 
 * information regarding any applicable licensing obligations.
 *
 ********************************************************************/
 
#include <stdint.h>

/****************************************************************************
  Section:
    Data Types
  ***************************************************************************/

// Enumeration for selecting output bit length
typedef enum
{
    SHA2_224,           // SHA-224 hash
    SHA2_256            // SHA-256 hash
} SHA256_BIT_LENGTH;

// Context storage for hash operation
typedef struct
{
    uint32_t h[8];                                              // Hash state
    uint32_t totalBytes;                                        // Total number of bytes hashed so far
    uint8_t partialBlock[64] __attribute__((aligned(4)));       // Beginning of next 64 byte block
    uint32_t * workingBuffer;                                   // 64 32-bit words for the working buffer
    SHA256_BIT_LENGTH length;                                   // Type of hash being calculated (SHA-224 or 256)
} SHA256_CONTEXT;


/****************************************************************************
  Section:
    Function Prototypes
  ***************************************************************************/

// *****************************************************************************
/*
  Function:
    void SHA256_Initialize (SHA256_CONTEXT * context, SHA256_BIT_LENGTH length, uint32_t * workingBuffer);

  Summary:
    Initializes a SHA-256 context to perform a SHA-256 hash.

  Description:
    This routine initializes a hash context for the SHA-256 hash.
    
  Precondition:
    None.

  Parameters:
    context - The context to initialize.
    length - Digest bit length to use with the SHA-256 algorithm.  SHA2_224 or SHA2_256.
    workingBuffer - A working buffer used by the module to calculate the hash.  If 
        the CRYPTO_HASH_CONFIG_SHA_SMALL_RAM macro is defined in sha_config.h, this 
        buffer must contain 16 uint32_t words.  Otherwise, this buffer must contain 
        64 32-bit words, but performance will be slightly improved.

  Returns:
    None.

  Example:
    <code>
    // Initialization for CRYPTO_HASH_CONFIG_SHA_SMALL_RAM
    uint32_t buffer[16];
    SHA256_CONTEXT context;
    SHA256_Initialize (&context, SHA2_256, buffer);
    </code>

  Remarks:
    You must initialize a context before calculating a SHA-256 hash.
*/
void SHA256_Initialize (SHA256_CONTEXT * context, SHA256_BIT_LENGTH length, uint32_t * workingBuffer);

// *****************************************************************************
/*
  Function:
    void SHA256_DataAdd (SHA256_CONTEXT * context, uint8_t * data, uint32_t len);

  Summary:
    Adds data to a hash being calculated.

  Description:
    This routine adds data to a SHA-256 hash being calculated.  When the data 
    length reaches a block size (64 bytes), this function will calculate the hash 
    over that block and store the current hash value in the hash context.
    
  Precondition:
    The hash context must be initialized with SHA256_Initialize.

  Parameters:
    context - The context of the hash being calculated.
    data - The data being added.
    len - The length of the data being added.

  Returns:
    None.

  Example:
    <code>
    // Initialization for CRYPTO_HASH_CONFIG_SHA_SMALL_RAM
    uint8_t data[] = "Hello.";
    uint32_t buffer[16];
    SHA256_CONTEXT context;

    SHA256_Initialize (&context, SHA2_256, buffer);

    SHA256_DataAdd (&context, data, 6);
    </code>

  Remarks:
    None.
*/
void SHA256_DataAdd (SHA256_CONTEXT * context, uint8_t * data, uint32_t len);

// *****************************************************************************
/*
  Function:
    void SHA256_Calculate (SHA256_CONTEXT * context, uint8_t * result);

  Summary:
    Finishes calculating a hash.

  Description:
    This routine finishes calculating a SHA-256 hash.  It will automatically add 
    the padding required by the hashing algorithm and return the hash digest.
    
  Precondition:
    The hash context must be initialized with SHA256_Initialize.

  Parameters:
    context - The context of the hash being calculated.
    result - A buffer to store the calculated hash digest.  32 bytes for SHA-256,
        28 bytes for SHA-224.

  Returns:
    None.

  Example:
    <code>
    // Initialization for CRYPTO_HASH_CONFIG_SHA_SMALL_RAM
    uint8_t data[] = "Hello.";
    uint32_t buffer[16];
    SHA256_CONTEXT context;
    uint8_t digest[32];

    SHA256_Initialize (&context, SHA2_256, buffer);

    SHA256_DataAdd (&context, data, 6);
    SHA256_Calculate (&context, digest);
    </code>

  Remarks:
    None.
*/
void SHA256_Calculate (SHA256_CONTEXT * context, uint8_t * result);











