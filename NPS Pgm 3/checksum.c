#include <stdio.h>
#include <stdio.h>

// Here we assume that we are transmitting 144 bits by making 9 parts and having 16 bits in each part.

int checksum() {
    unsigned int parts[9];
    unsigned int sum=0;
    printf("Enter all the 9 parts in HexaDecimal:\n");
    for (int i = 0; i < 9; i++) {
        scanf("%X", &parts[i]);
        sum += parts[i];
        while (sum >> 16)
            sum = (sum & 0xffff) + (sum >> 16);
    }
    return ~sum;
}

int main() {
    printf("--- SENDER ---\n");
    int sender_checksum = checksum();
    printf("Sent checksum: %x\n", sender_checksum);
    printf("\n--- RECV ---\n");
    int recv_checksum = checksum();
    printf("Recieved checksum: %x\n", recv_checksum);
    if (sender_checksum == recv_checksum) {
        printf("Matching checksums!\n");
        return 0;
    } else {
        printf("Mismatched checksums!\n");
        return 0;
    }

}
