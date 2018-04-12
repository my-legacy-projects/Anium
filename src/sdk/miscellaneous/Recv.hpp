#ifndef ANIUM_RECV_HPP
#define ANIUM_RECV_HPP

#include <cstdint>

struct RecvProp;

struct DVariant {
    union {
        float mFloat;
        long mInt;
        char* mString;
        void* data;
        float vector[3];
        int64_t mInt64;
    };
    int type;

};

struct CRecvProxyData {
    const RecvProp* recvProp;
    DVariant value;
    int element;
    int objectID;

};

struct RecvTable {
    RecvProp* pProps;
    int nProps;
    void* decoder;
    char* netTableName;
    bool initialized;
    bool mainList;

};

using RecvVarProxyFn = void (*)(const CRecvProxyData*, void*, void*);

struct RecvProp {
    char* name;
    int type;
    int flags;
    int strBufferSize;
    bool insideArray;
    const void* extraData;
    RecvProp* arrayProp;
    void* arrayLengthProp;
    RecvVarProxyFn proxy;
    void* proxyDataTable;
    RecvTable* dataTable;
    int offset;
    int elementStride;
    int elements;
    const char* parentName;

};

#endif  // ANIUM_RECV_HPP
