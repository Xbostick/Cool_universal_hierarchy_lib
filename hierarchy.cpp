#include "hierarchy.h"
#include <stdio.h>
#include <string.h>

/*-------Data---------*/
Data::Data(char* raw_string)
{  
    this->raw = new char;
    memcpy (this->raw, raw_string, strlen(raw_string));
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

OperationStatus ACluster:: AddProxy(AProxy *new_module)
{
    Proxy_List* newModule = new Proxy_List;
    newModule->obj = new_module;
    newModule->next = this->Proxis;
    this->Proxis = newModule;
    return OperationStatus::OK;
};

OperationStatus AGovernor::AddCommander(void *new_module)
{
    this->Commander = new_module;
    
    return OperationStatus::OK;
};


OperationStatus AGovernor:: AddProxy(AProxy *new_module)
{
    Proxy_List* newModule = new Proxy_List;
    newModule->obj = new_module;
    newModule->next = this->Proxis;
    this->Proxis = newModule;
    return OperationStatus::OK;
};


