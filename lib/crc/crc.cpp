unsigned int CRC16RTU(unsigned char* pszBuf, unsigned char unLength) {
    unsigned int CRC = 0xFFFF;
    unsigned long CRC_count;
    for (CRC_count = 0; CRC_count < unLength; CRC_count++) {
        int i;
        CRC = CRC ^ *(pszBuf + CRC_count);
        for (i = 0; i < 8; i++) {
            if (CRC & 1) {
                CRC >>= 1;
                CRC ^= 0xA001;
            } else {
                CRC >>= 1;
            }
        }
    }
    return CRC;
}