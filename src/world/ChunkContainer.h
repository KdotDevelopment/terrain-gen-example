#include <iostream>

struct ChunkContainer {
    uint8_t blockArray[16][16][16];
    int chunkX;
    int chunkY;
    int chunkZ;
};