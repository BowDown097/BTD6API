//
// These types are human added, they're not in il2cppinspector for some reason.
//

typedef struct Il2CppException : public Il2CppObject
{
    Il2CppString* className;
    Il2CppString* message;
    Il2CppObject* _data;
    Il2CppException* inner_ex;
    Il2CppString* _helpURL;
    Il2CppArray* trace_ips;
    Il2CppString* stack_trace;
    Il2CppString* remote_stack_trace;
    int remote_stack_index;
    Il2CppObject* _dynamicMethods;
    il2cpp_hresult_t hresult;
    Il2CppString* source;
    Il2CppObject* safeSerializationManager;
    Il2CppArray* captured_traces;
    Il2CppArray* native_trace_ips;
} Il2CppException;

struct Il2CppExceptionWrapper
{
    Il2CppException* ex;

    Il2CppExceptionWrapper(Il2CppException* ex) : ex(ex) {}
};