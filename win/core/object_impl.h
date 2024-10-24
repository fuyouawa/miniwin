#pragma once
#include <miniwin/core/object.h>

#include <vector>
#include <typeindex>
#include <string>

namespace miniwin {
class Object::Impl {
public:
    explicit Impl(Object* owner);

    ~Impl();

    struct Connection
    {
        const Object* sender;
        const Object* receiver;
        internal::SlotObjectPtr slot_obj;
        std::type_index signal_info;
        ConnectionFlags connection_type;
        InvokeType invoke_type;
    };
    using ConnectionPtr = std::shared_ptr<Connection>;

    using ConnectionList = std::vector<ConnectionPtr>;

    class ConnectionsManager
    {
    public:
        bool dirty_; // һЩ�����Ѿ����ж���, ���ǲ�û�д��б����Ƴ�
        std::unordered_map<std::type_index, ConnectionList> map_;

        void ClearDirty();
    };

    static Disconnecter ConnectImpl(
        const Object* sender,
        const std::type_info& signal_info,
        const Object* receiver,
        internal::SlotObjectPtr&& slot_obj,
        ConnectionFlags connection_flags,
        InvokeType invoke_type);

    void EmitSignalImpl(const type_info& type_info, const internal::SlotArgsStoreSharedPtr& args_store);

    bool DisconnectImpl(
        const std::type_info& signal_info,
        const ConnectionPtr& connection);

    Disconnecter AddConnectionWithoutLock(const std::type_info& signal_info, ConnectionPtr conn);

    void SetParent(Object* parent);

    void DeleteChildren();

    bool deleting_ = false;
    Object* owner_ = nullptr;
    Object* parent_ = nullptr;
    String name_;
    FlagsType flags_;
    std::vector<Object*> children_;
    std::vector<ConnectionPtr> connected_sender_connections_;    // ���ӵ��ķ�����
    ConnectionsManager connections_manager_;
};
}
