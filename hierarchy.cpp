#include "hierarchy.h"
#include <stdio.h>
#include <string.h>
/*-------Data---------*/
Data::Data(char* raw_string, int len_string)
{  
    this->raw = new char[len_string];
    memcpy (this->raw, raw_string, len_string);
};

ArrayType* Data::GetRawData()
{
    ArrayType* output = new ArrayType;
    memcpy(output->data, this->raw, this->len_raw);
    output->len=this->len_raw;
    
    return output;
};

ArrayType* Data::GetProcData()
{
    if (this->processed == NULL) return NULL;
    
    ArrayType* output = new ArrayType;
    memcpy(output->data, this->processed, this->len_processed);
    output->len=this->len_raw;
    
    return output;
};

char Data::NextProc()
{   
    if (this->processed == NULL) return NULL;
    return *(this->processed + (this->processed_actual_index++));    
};

char Data::NextRaw()
{   
    return *(this->raw + (this->raw_actual_index++));    
};

char Data::GetProcIdx(int idx)
{   
    return *(this->processed + idx);    
};

char Data::GetRawIdx(int idx)
{   
    return *(this->raw + idx);    
};

/*-------Cluster---------*/
ACluster::ACluster(AGovernor *governors_list, int governors_count, AProxy* proxy_list, int proxy_count)
{
    for (int i = 0; i < governors_count; i++)
        this->AddGovernor(governors_list+i);
    for (int i = 0; i < proxy_count; i++)
        this->AddProxy(proxy_list+i);    
};

Data* ACluster:: Deligate2Governor(Data* data)
{
    TaskState status = TaskState::NotDeligated;
    Governors_List* currentGoverner = this->Governors;

    while (currentGoverner != NULL) {
        status = currentGoverner->obj->CheckTask(data);
        if (status != TaskState::NotDeligated)
            break;
		currentGoverner = currentGoverner->next;
    }
    if (status == TaskState::ExtraReturn)
        {
            Data* output = currentGoverner->obj->ProcessData(data);
            return output;
        }
        
    else
        return NULL;
};

OperationStatus ACluster:: AddGovernor(AGovernor *new_module)
{
    Governors_List* newModule = new Governors_List;
    newModule->obj = new_module;
    newModule->next = this->Governors;
    this->Governors = newModule;
    return OperationStatus::OK;
};

