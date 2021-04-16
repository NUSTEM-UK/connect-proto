typedef void (*GenericFP)(void *, ...);
// typedef void (*GenericFP)();

typedef struct {
    String targetDevice;
    GenericFP call;
    int queueVar1;
    float queueVar2;
    char * queueVar3;
    int startPos;
    int endPos;
    const char * animationType;
    float animationDuration;
} deviceQueueItem;
