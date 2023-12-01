#ifndef HIERARCHY_GENERAL_H
#define HIERARCHY_GENERAL_H

#include "hierarchy.h"
#include <stdint.h>

/*--------Data_General-------*/


/*Обертка для записи-чтения из flash - памяти*/
class FlashData : public Data

{
    public:
    int32_t FlashAddres;
    FlashData(Data* data = NULL);
};

/*--------Clusters_General-------*/

/*--------Governors_General-------*/

/*Читает - пишет данные по имени/индексу. Поволяет писать коммент, хранит маппинг в себе*/
class FlashGovernor : public AGovernor
{
    private:
        FlashMap_List* Mapped;
        OperationStatus WriteData(Data* data);
        OperationStatus ReadData(Data* data);
    
    

};

/*--------Proxy_General-------*/

/*--------Commander_General-------*/

class FlashCommander: public ACommander
{

};

#endif

/*--------Other_General-------*/


struct FlashMap_List{
    int32_t 			start;
    int32_t 			len;
    char*               Name;
    int                 NameLen;
    int                 idx;
    char*               Description;
    int                 DescriptionLen;
    FlashMap_List* 		next;    
};