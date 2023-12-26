#ifndef HIERARCHY_H
#define HIERARCHY_H

class ACluster;     // Class to unite Governors
class AGovernor;    // Class to determine tasks to it`s own commander and information exchange inside system
class AProxy;       // Class without hardware/ Only operations inside governor
class ACommander;   // Class to connect hardware. Knows its governor and hardware interface.


class Data;        // Class to normalize data from every source
struct ProcessedCmd;
class IConverter;   // 

struct ArrayType
{
    char* data;
    int len;
};

enum TaskState
{
	NotDeligated = 0,
	Deligated,
	ExtraReturn,
    ExtraReturnOptional
};

enum OperationStatus
{
	OK = 0,
	Not_OK,
	ErrorCode
};


class Data
{   
    public:
    int raw_actual_index = 0;
    int processed_actual_index = 0;
    char* governor_code;
    char *raw;
    char *processed;
    int len_processed;
    int len_raw;


    virtual OperationStatus SetGovernorCode()= 0;

    public:
    Data(char* raw_string, int len_string);

    virtual OperationStatus CheckSum() = 0;
    virtual ArrayType* GetRawData();
    virtual ArrayType* GetProcData();

    char NextProc();
    char NextRaw();
    
    virtual ArrayType* NextArray() = 0;

    char GetProcIdx(int idx);
    char GetRawIdx(int idx);

    
};

struct Governors_List {
    AGovernor* 			    obj;
    Governors_List* 		next;
};

struct Proxy_List {
    AProxy* 			obj;
    char*               ProxyName;
    int                 NameLen;
    Proxy_List* 		next;
    
    
};
// Возможно стоит использовать энам

class ACluster
{   
    protected:
        Data*                   Deligate2Governor(Data* data);
        Governors_List*         Governors;
        Proxy_List*             Proxis;
        int                     num_governors;
        int                     num_proxy;

    public:
        ACluster(AGovernor *governors_list = 0, int governors_count = 0, AProxy* proxy_list = 0, int proxy_count = 0);
        virtual Data*       ProcessData(Data* data);
        OperationStatus     AddGovernor(AGovernor *new_module);
        OperationStatus     AddProxy(AProxy *new_module);//, char* ProxyName, int NameLen);

};

class AGovernor
{
    protected:
        void* Commander;
        Proxy_List* Proxis;
        Data*       DataHolder;
        char*       identifaction_string;

    public:
        AGovernor(void* Commander);
        virtual TaskState   CheckTask(Data* data);
        virtual Data*       ProcessData(Data* data);
        OperationStatus     AddCommander(void *new_module);
        OperationStatus     AddProxy(AProxy *new_module);//, char* ProxyName, int NameLen);
};

class AProxy
{
    protected:
        Data* innerDataHandler;
    public:
        virtual Data* ProcessData(Data* data);
};

class ACommander
{
    public:
        // virtual Data* ProcessData(Data* data);
        
};



#endif