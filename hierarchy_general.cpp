#include "hierarchy_general.h"


FlashData::FlashData( char* raw_string = nullptr,int len = 0) : Data(raw_string, len)
{

};

FlashData::FlashData(FlashMeta meta, char* raw_string = nullptr, int len = 0): Data(raw_string, len)
{
    this->_meta = meta;
};
/*--------------Governonr---------*/

/*Creates new mapping data space after last mapped adress*/
OperationStatus FlashGovernor::CreateMapped(FlashData* data)
{
    if (data->_meta.start == 0)
        data->_meta.start = this->Mapped->data->start + 1;
    FlashMap_List* block = new FlashMap_List;
    block->data = &data->_meta;
    block->next = this->Mapped;
};

OperationStatus FlashGovernor::DeleteMapped()