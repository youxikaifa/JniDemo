#include <stdio.h>
#include <string.h>
#include "cal.h"

#define Nb 4
#define Nk 4
#define Nr 10
#define Multiply(x, y) \
(((y & 1) * x) ^ \
((y>>1 & 1) * xTime(x)) ^ \
((y>>2 & 1) * xTime(xTime(x))) ^ \
((y>>3 & 1) * xTime(xTime(xTime(x)))) ^ \
((y>>4 & 1) * xTime(xTime(xTime(xTime(x))))))
typedef unsigned char m_array[4][4];
typedef unsigned char uint8;

static m_array *state;
static uint8 RoundKey[176];
static const uint8 *EKey;
static const uint8 sBox[256] =
        {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67,
         0x2b, 0xfe, 0xd7, 0xab, 0x76,
         0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2,
         0xaf, 0x9c, 0xa4, 0x72, 0xc0,
         0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5,
         0xf1, 0x71, 0xd8, 0x31, 0x15,
         0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80,
         0xe2, 0xeb, 0x27, 0xb2, 0x75,
         0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6,
         0xb3, 0x29, 0xe3, 0x2f, 0x84,
         0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe,
         0x39, 0x4a, 0x4c, 0x58, 0xcf,
         0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02,
         0x7f, 0x50, 0x3c, 0x9f, 0xa8,
         0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda,
         0x21, 0x10, 0xff, 0xf3, 0xd2,
         0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e,
         0x3d, 0x64, 0x5d, 0x19, 0x73,
         0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8,
         0x14, 0xde, 0x5e, 0x0b, 0xdb,
         0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac,
         0x62, 0x91, 0x95, 0xe4, 0x79,
         0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4,
         0xea, 0x65, 0x7a, 0xae, 0x08,
         0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74,
         0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
         0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57,
         0xb9, 0x86, 0xc1, 0x1d, 0x9e,
         0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87,
         0xe9, 0xce, 0x55, 0x28, 0xdf,
         0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d,
         0x0f, 0xb0, 0x54, 0xbb, 0x16};
static const uint8 rsBox[256] =
        {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3,
         0x9e, 0x81, 0xf3, 0xd7, 0xfb,
         0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43,
         0x44, 0xc4, 0xde, 0xe9, 0xcb,
         0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95,
         0x0b, 0x42, 0xfa, 0xc3, 0x4e,
         0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2,
         0x49, 0x6d, 0x8b, 0xd1, 0x25,
         0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c,
         0xcc, 0x5d, 0x65, 0xb6, 0x92,
         0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46,
         0x57, 0xa7, 0x8d, 0x9d, 0x84,
         0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58,
         0x05, 0xb8, 0xb3, 0x45, 0x06,
         0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd,
         0x03, 0x01, 0x13, 0x8a, 0x6b,
         0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf,
         0xce, 0xf0, 0xb4, 0xe6, 0x73,
         0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37,
         0xe8, 0x1c, 0x75, 0xdf, 0x6e,
         0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62,
         0x0e, 0xaa, 0x18, 0xbe, 0x1b,
         0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0,
         0xfe, 0x78, 0xcd, 0x5a, 0xf4,
         0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10,
         0x59, 0x27, 0x80, 0xec, 0x5f,
         0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a,
         0x9f, 0x93, 0xc9, 0x9c, 0xef,
         0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb,
         0x3c, 0x83, 0x53, 0x99, 0x61,
         0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14,
         0x63, 0x55, 0x21, 0x0c, 0x7d};
static const uint8 rCon[16] =
        {0xef, 0x3a, 0x19, 0x3d, 0xca, 0x0b, 0x36, 0x89, 0xa8, 0x61, 0xf6,
         0x6c, 0xd8, 0xab, 0x4d, 0x9a};




void AES128_ECB_decrypt(uint8 *password, unsigned int password_len, uint8 *key,uint8 *original) //解密
{
    int i, k = password_len;
    unsigned char _original[k], _password[k];//, original[k];
    for (i = 0; i < k; ++i)
        _password[i] = password[i];
    memset(_original, 0, (size_t) k);
    memcpy(_password, password, (size_t) k);
    for (i = 0; i < (k / 16); ++i) {
        ECB_decrypt(_password + (i * 16), key, _original + (i * 16));
    }
    memcpy(original, _original, (size_t) k); //复制函数
    // return _original; 不安全 本地变量在函数外会销毁
}


int aes128TextLen(int len) {
    int k;
    if (len % 16 != 0)
        k = len + 16 - (len % 16);
    else
        k = len;
    return k;
}

void AES128_ECB_encrypt(uint8 *original, unsigned int original_len, uint8 *key,uint8 *password) //加密
{
    int i, k = aes128TextLen(original_len);
    unsigned char _original[k], _password[k];//, password[k];
    for (i = 0; i < original_len; ++i)
        _original[i] = original[i];
    for (i = original_len; i < k; ++i)
        _original[i] = 0x00;
    memset(_password, 0, k);
    for (i = 0; i < (k / 16); ++i) {
        ECB_encrypt(_original + (i * 16), key, _password + (i * 16));
    }
    memcpy(password, _password, (size_t) k);
//    return password;
}

void ECB_decrypt(const uint8 *input, const uint8 *key, uint8 *output) {
    BlockCopy(output, input);
    state = (m_array *) output;
    EKey = key;
    KeyExpansion();
    InvCipher();
}

void InvCipher(void) {
    uint8 round = 0;
    AddRoundKey(Nr);
    for (round = Nr - 1; round > 0; round--) {
        InvShiftRows();
        InvSubBytes();
        AddRoundKey(round);
        InvMixColumns();
    }
    InvShiftRows();
    InvSubBytes();
    AddRoundKey(0);
}

void InvSubBytes(void) {
    uint8 i, j;
    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            (*state)[j][i] = getSBoxInvert((*state)[j][i]);
}

uint8 getSBoxInvert(uint8 num) { return rsBox[num]; }

void InvMixColumns(void) {
    uint8 i, a, b, c, d;
    for (i = 0; i < 4; ++i) {
        a = (*state)[i][0];
        b = (*state)[i][1];
        c = (*state)[i][2];
        d = (*state)[i][3];
        (*state)[i][0] =
                (unsigned char) (Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^
                                 Multiply(d, 0x09));
        (*state)[i][1] =
                (unsigned char) (Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^
                                 Multiply(d, 0x0d));
        (*state)[i][2] =
                (unsigned char) (Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^
                                 Multiply(d, 0x0b));
        (*state)[i][3] =
                (unsigned char) (Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^
                                 Multiply(d, 0x0e));
    }
}

void InvShiftRows(void) {
    uint8 temp;
    temp = (*state)[3][1];
    (*state)[3][1] = (*state)[2][1];
    (*state)[2][1] = (*state)[1][1];
    (*state)[1][1] = (*state)[0][1];
    (*state)[0][1] = temp;
    temp = (*state)[0][2];
    (*state)[0][2] = (*state)[2][2];
    (*state)[2][2] = temp;
    temp = (*state)[1][2];
    (*state)[1][2] = (*state)[3][2];
    (*state)[3][2] = temp;
    temp = (*state)[0][3];
    (*state)[0][3] = (*state)[1][3];
    (*state)[1][3] = (*state)[2][3];
    (*state)[2][3] = (*state)[3][3];
    (*state)[3][3] = temp;
}

static uint8 getSBoxValue(uint8 num) { return sBox[num]; }


void KeyExpansion(void) {
    uint8 i, j, k, temp[4];
    for (i = 0; i < Nk; ++i) {
        RoundKey[(i * 4) + 0] = EKey[(i * 4) + 0];
        RoundKey[(i * 4) + 1] = EKey[(i * 4) + 1];
        RoundKey[(i * 4) + 2] = EKey[(i * 4) + 2];
        RoundKey[(i * 4) + 3] = EKey[(i * 4) + 3];
    }
    for (; (i < (Nb * (Nr + 1))); ++i) {
        for (j = 0; j < 4; ++j)
            temp[j] = RoundKey[(i - 1) * 4 + j];
        if (i % Nk == 0) {
            k = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = k;
            temp[0] = getSBoxValue(temp[0]);
            temp[1] = getSBoxValue(temp[1]);
            temp[2] = getSBoxValue(temp[2]);
            temp[3] = getSBoxValue(temp[3]);
            temp[0] = temp[0] ^ rCon[i / Nk];
        }
        RoundKey[i * 4 + 0] = RoundKey[(i - Nk) * 4 + 0] ^ temp[0];
        RoundKey[i * 4 + 1] = RoundKey[(i - Nk) * 4 + 1] ^ temp[1];
        RoundKey[i * 4 + 2] = RoundKey[(i - Nk) * 4 + 2] ^ temp[2];
        RoundKey[i * 4 + 3] = RoundKey[(i - Nk) * 4 + 3] ^ temp[3];
    }
}

void AddRoundKey(uint8 round) {
    uint8 i, j;
    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            (*state)[i][j] ^= RoundKey[round * Nb * 4 + i * Nb + j];
}

static void SubBytes(void) {
    uint8 i, j;
    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            (*state)[j][i] = getSBoxValue((*state)[j][i]);
}

static void ShiftRows(void) {
    uint8 temp;
    temp = (*state)[0][1];
    (*state)[0][1] = (*state)[1][1];
    (*state)[1][1] = (*state)[2][1];
    (*state)[2][1] = (*state)[3][1];
    (*state)[3][1] = temp;
    temp = (*state)[0][2];
    (*state)[0][2] = (*state)[2][2];
    (*state)[2][2] = temp;
    temp = (*state)[1][2];
    (*state)[1][2] = (*state)[3][2];
    (*state)[3][2] = temp;
    temp = (*state)[0][3];
    (*state)[0][3] = (*state)[3][3];
    (*state)[3][3] = (*state)[2][3];
    (*state)[2][3] = (*state)[1][3];
    (*state)[1][3] = temp;
}

uint8 xTime(uint8 x) { return (uint8) ((x << 1) ^ (((x >> 7) & 1) * 0x1b)); }

static void MixColumns(void) {
    uint8 i, Tmp, Tm, t;
    for (i = 0; i < 4; ++i) {
        t = (*state)[i][0];
        Tmp = (*state)[i][0] ^ (*state)[i][1] ^ (*state)[i][2] ^ (*state)[i]
        [3];
        Tm = (*state)[i][0] ^ (*state)[i][1];
        Tm = xTime(Tm);
        (*state)[i][0] ^= Tm ^ Tmp;
        Tm = (*state)[i][1] ^ (*state)[i][2];
        Tm = xTime(Tm);
        (*state)[i][1] ^= Tm ^ Tmp;
        Tm = (*state)[i][2] ^ (*state)[i][3];
        Tm = xTime(Tm);
        (*state)[i][2] ^= Tm ^ Tmp;
        Tm = (*state)[i][3] ^ t;
        Tm = xTime(Tm);
        (*state)[i][3] ^= Tm ^ Tmp;
    }
}


static void Cipher(void) {
    uint8 round = 0;
    AddRoundKey(0);
    for (round = 1; round < Nr; ++round) {
        SubBytes();
        ShiftRows();
        MixColumns();
        AddRoundKey(round);
    }
    SubBytes();
    ShiftRows();
    AddRoundKey(Nr);
}


void BlockCopy(uint8 *output, const uint8 *input) {
    uint8 i;
    for (i = 0; i < 16; ++i)
        output[i] = input[i];
}

void ECB_encrypt(const uint8 *input, const uint8 *key, uint8 *output) {
    BlockCopy(output, input);
    state = (m_array *) output;
    EKey = key;
    KeyExpansion();
    Cipher();
}


