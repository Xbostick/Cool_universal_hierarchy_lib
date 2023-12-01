#ifndef HIERARCHY_GENERAL_H
#define HIERARCHY_GENERAL_H

#include "hierarchy.h"
#include <stdint.h>

/*--------Data_General-------*/


/*Обертка для записи-чтения из flash - памяти*/
class FlashData : public Data
{
    public:
        FlashMeta   data;
        FlashData(char* raw_string, int len);
        FlashData(Data* data);
};

/*--------Clusters_General-------*/

/*--------Governors_General-------*/

/*Читает - пишет данные по имени/индексу. Поволяет писать коммент, хранит маппинг в себе*/
class FlashGovernor : public AGovernor
{
    private:
        FlashMap_List* Mapped = nullptr;
        OperationStatus CreateMapped(FlashData* data);
        OperationStatus DeleteMapped(char* Name, int NameLen);
        OperationStatus DeleteMapped(int idx);
        FlashData* TakeMapped(char* Name, int NameLen);
        FlashData* TakeMapped(int idx);
    
    public:
        TaskState CheckTask(Data* data);
        Data* ProcessData(Data* data);
        Data* ProcessData(FlashData* data);
    
    

};

/*--------Proxy_General-------*/

/*--------Commander_General-------*/

class FlashCommander: public ACommander
{  
    public:
        OperationStatus WriteData(FlashData* data);
        OperationStatus ReadData(FlashData* data);
};

#endif

/*--------Other_General-------*/

struct FlashMeta{
    int32_t 			start;
    int32_t 			len;
    char*               Name;
    int                 NameLen;
    int                 idx;
    char*               Description;
    int                 DescriptionLen;
};

struct FlashMap_List{

    FlashMeta           data;
    FlashMap_List* 		next;    
};