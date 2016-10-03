/******************************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PICmicro(r) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PICmicro Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
********************************************************************/

#include "crypto_sw/block_cipher_sw.h"
#include "crypto_sw/src/block_cipher/block_cipher_sw_private.h"
#include "system_config.h"
#include <string.h>

BLOCK_CIPHER_SW_ERRORS BLOCK_CIPHER_SW_CBC_Initialize (BLOCK_CIPHER_SW_HANDLE handle, BLOCK_CIPHER_SW_CBC_CONTEXT * context, BLOCK_CIPHER_SW_FunctionEncrypt encryptFunction, BLOCK_CIPHER_SW_FunctionDecrypt decryptFunction, uint32_t blockSize, uint8_t * initializationVector, void * key, CRYPTO_SW_KEY_TYPE keyType)
{
    if ((keyType != CRYPTO_SW_KEY_SOFTWARE_EXPANDED) && (keyType != CRYPTO_SW_KEY_SOFTWARE))
    {
        return BLOCK_CIPHER_SW_ERROR_UNSUPPORTED_KEY_TYPE;
    }

    if (handle >= 0 && handle < CRYPTO_CONFIG_SW_BLOCK_HANDLE_MAXIMUM)
    {
        blockHandles[handle] = context;
    }
    else
    {
        return BLOCK_CIPHER_SW_ERROR_INVALID_HANDLE;
    }

    context->encrypt = encryptFunction;
    context->decrypt = decryptFunction;
    context->blockSize = blockSize;
    memcpy (context->initializationVector, initializationVector, blockSize);
    context->key = key;
    context->keyType = keyType;

    return BLOCK_CIPHER_SW_ERROR_NONE;
}

BLOCK_CIPHER_SW_ERRORS BLOCK_CIPHER_SW_CBC_Encrypt (BLOCK_CIPHER_SW_HANDLE handle, uint8_t * cipherText, uint32_t * numCipherBytes, uint8_t * plainText, uint32_t numPlainBytes, uint32_t options)
{
    uint8_t i;
    uint8_t __attribute__((aligned)) buffer[CRYPTO_CONFIG_SW_BLOCK_MAX_SIZE];
    BLOCK_CIPHER_SW_CBC_CONTEXT * context = (BLOCK_CIPHER_SW_CBC_CONTEXT *)BLOCK_CIPHER_SW_HandleResolve(handle);

    if (context == NULL)
    {
        return BLOCK_CIPHER_SW_ERROR_INVALID_HANDLE;
    }

    if (numCipherBytes != NULL)
    {
        *numCipherBytes = 0;
    }
    
    if((options & BLOCK_CIPHER_SW_OPTION_STREAM_START) == BLOCK_CIPHER_SW_OPTION_STREAM_START)
    {
        context->bytesRemaining = 0;

        //move the initialization vector into the remaining data buffer
        memcpy(context->remainingData, context->initializationVector, context->blockSize);
    }

    if((context->bytesRemaining + numPlainBytes) < context->blockSize)
    {
        //Append the new data to the end of the old data
        for(i=context->bytesRemaining;i<(context->bytesRemaining+numPlainBytes); i++)
        {
            context->remainingData[i] ^= *plainText++;
        }

        //increase the size of the number of bytes with the number of bytes
        //  that were remaining in the buffer before the function was called.
        context->bytesRemaining += numPlainBytes;

        //exit since there is not a complete block;
        return BLOCK_CIPHER_SW_ERROR_NONE;
    }

    //Append the new data to the end of the old data
    for(i=context->bytesRemaining;i<context->blockSize; i++)
    {
        context->remainingData[i] ^= *plainText++;
    }

    //increase the size of the number of bytes with the number of bytes
    //  that were remaining in the buffer before the function was called.
    numPlainBytes += context->bytesRemaining;

    while(1)
    {
        (*context->encrypt)(handle, buffer, context->remainingData, context->key);
        memcpy(cipherText,buffer,context->blockSize);

        numPlainBytes -= context->blockSize;
        if (numCipherBytes != NULL)
        {
            *numCipherBytes += context->blockSize;
        }

        //Save the results of this block to be used in the next block
        for(i=0;i<context->blockSize;i++)
        {
            context->remainingData[i] = *cipherText++;
        }

        //Continue with the remaining data left to process
        if(numPlainBytes >= context->blockSize)
        {
            //Get the next input block ready
            for(i=0;i<context->blockSize;i++)
            {
                context->remainingData[i] ^= *plainText++;
            }
        }
        else
        {
            if((options & BLOCK_CIPHER_SW_OPTION_PAD_MASK) != BLOCK_CIPHER_SW_OPTION_PAD_NONE)
            {
                // Add padding to the block
                BLOCK_CIPHER_SW_PaddingInsert(context->remainingData, context->blockSize, context->blockSize - context->bytesRemaining, options);

                // Since we have added padding, there is a full block of data.
                numPlainBytes = context->blockSize;

                // Clear the padding option so we don't come back to this section
                //   of code again.
                options &= ~BLOCK_CIPHER_SW_OPTION_PAD_MASK;
            }
            else
            {
                //If there isn't a complete block worth of data left and there
                //  isn't a padding specified, then continue the stream by exiting
                //  this routine.
                break;
            }
        }
    }

    //save the number of plain text bytes remaining in the buffer
    context->bytesRemaining = numPlainBytes;

    //Copy any remaining bytes to the buffer.
    for(i=0;i<numPlainBytes;i++)
    {
        context->remainingData[i] ^= *plainText++;
    }

    return BLOCK_CIPHER_SW_ERROR_NONE;
}

BLOCK_CIPHER_SW_ERRORS BLOCK_CIPHER_SW_CBC_Decrypt (BLOCK_CIPHER_SW_HANDLE handle, uint8_t * plainText, uint32_t * numPlainBytes, uint8_t * cipherText, uint32_t numCipherBytes, uint32_t options)
{
    uint8_t i;
    BLOCK_CIPHER_SW_CBC_CONTEXT * context = (BLOCK_CIPHER_SW_CBC_CONTEXT *)BLOCK_CIPHER_SW_HandleResolve(handle);

    if (context == NULL)
    {
        return BLOCK_CIPHER_SW_ERROR_INVALID_HANDLE;
    }

    if (numPlainBytes != NULL)
    {
        *numPlainBytes = 0;
    }

    if((options & BLOCK_CIPHER_SW_OPTION_STREAM_START) == BLOCK_CIPHER_SW_OPTION_STREAM_START)
    {
        context->bytesRemaining = 0;
    }

    if((context->bytesRemaining + numCipherBytes) < context->blockSize)
    {
        memcpy(&context->remainingData[context->bytesRemaining],cipherText,numCipherBytes);

        //increase the size of the number of bytes with the number of bytes
        //  that were remaining in the buffer before the function was called.
        context->bytesRemaining += numCipherBytes;

        //exit since there is not a complete block;
        return BLOCK_CIPHER_SW_ERROR_NONE;
    }

    //increase the size of the number of bytes with the number of bytes
    //  that were remaining in the buffer before the function was called.
    numCipherBytes += context->bytesRemaining;

    //Append the new data to the end of the old data
    memcpy(&context->remainingData[context->bytesRemaining], cipherText, context->blockSize-context->bytesRemaining);
    context->bytesRemaining = context->blockSize;

    while(1)
    {
        (*context->decrypt)(handle, plainText, context->remainingData, context->key);

        numCipherBytes -= context->blockSize;
        if (numPlainBytes != NULL)
        {
            *numPlainBytes += context->blockSize;
        }

        //Complete the decryption cycle by performing the XOR operation with
        //  either the cipher text from the last block or the initialization
        //  vector.
        for(i=0;i<context->blockSize;i++)
        {
            *plainText++ ^= ((uint8_t *)context->initializationVector)[i];
        }

        //Save the cipher text from this block for use in the next block
        //Complete the decryption cycle by performing the XOR operation with
        //  the either the cipher text for the last block or the initialization
        //  vector.
        for(i=0;i<context->blockSize;i++)
        {
            ((uint8_t *)context->initializationVector)[i] = ((uint8_t *)context->remainingData)[i];
        }

        cipherText += context->blockSize;

        if(numCipherBytes >= context->blockSize)
        {
            //Get the next input block ready
            memcpy(context->remainingData, cipherText, context->blockSize);
        }
        else
        {
            //If there isn't a complete block worth of data left then exit the
            //  loop.
            break;
        }
    }

    //save the number of plain text bytes remaining in the buffer
    context->bytesRemaining = numCipherBytes;

    //Copy any remaining bytes to the buffer.
    memcpy(context->remainingData, cipherText, numCipherBytes);
    cipherText += numCipherBytes;

    return BLOCK_CIPHER_SW_ERROR_NONE;
}


