#include "hierarchy_general.h"
#include <string.h>

FlashData::FlashData(char* raw_string,int len, FlashMeta* meta = nullptr) : Data(raw_string, len)
{   
    if (meta == nullptr)
        this->meta = new FlashMeta;
    else
        this->meta = meta;
};

OperationStatus FlashGovernor::CreateMapped(FlashData* data)
{
    FlashMap_List* newModule = new FlashMap_List;
    memcpy(&newModule->data, data->meta, sizeof(data->meta));
    newModule->next = this->Mapped;
    this->Mapped = newModule;

    ((FlashCommander*)(this->Commander))->
        WriteData(data);    
    delete data;
    return OperationStatus::OK;
};

OperationStatus FlashGovernor::DeleteMapped(int idx)
{
    int i = 0;
    FlashMap_List* data_2_delete = new FlashMap_List;
    FlashMap_List* prev_data = new FlashMap_List;
    data_2_delete = this->Mapped;
    prev_data = this->Mapped;
    while (i != idx)
    {
        prev_data = data_2_delete;
        data_2_delete = data_2_delete->next;
    }
    prev_data->next = data_2_delete->next;
    delete data_2_delete;

    return OperationStatus::OK;
};

FlashData* FlashGovernor::TakeMapped(int idx)
{
    int i = 0;
    FlashMap_List* data_to_return = this->Mapped;
    
    while (i != idx)
    {
        data_to_return = data_to_return->next;
    }
    FlashData* data_from_flash = ((FlashCommander*)(this->Commander))->
                                                    ReadData(&data_to_return->data);
    
    return data_from_flash;
};

TaskState FlashGovernor::CheckTask(Data* data)
{
    if (strstr(this->identifaction_string, data->governor_code))
        return TaskState::Deligated;
    else    
        return TaskState::NotDeligated;
};

Data* FlashGovernor::ProcessData(Data* data)
{
    if (strstr(this->identifaction_string, data->governor_code))
};