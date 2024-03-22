#define SERVER_PORT 6000

#define STOP		1
#define STATS		2
#define COMPUTE		3

typedef union {
    float          timeAsFloat;
    unsigned char  timeBytes[4];
} ComputeTime;

typedef union {
    unsigned long int  numberAsLong;
    unsigned char      numberBytes[8];
} LargeNumber;

typedef union {
    unsigned  int  numberAsInt;
    unsigned char  numberBytes[4];
} StatsNumber;
