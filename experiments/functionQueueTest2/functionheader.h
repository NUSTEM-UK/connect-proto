typedef void (*GenericFP)(void *, ...);
// typedef void (*GenericFP)();

typedef struct {
    String targetDevice;
    GenericFP call;
    int queueVar1;
    float queueVar2;
    String queueVar3;
} deviceQueueItem;
