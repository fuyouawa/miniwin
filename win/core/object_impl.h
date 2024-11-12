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
    using SharedConnection = std::shared_ptr<Connection>;

    using ConnectionList = List<SharedConnection>;

    class ConnectionsManager
    {
    public:
        bool dirty_; // 一些连接已经被切断了, 但是并没有从列表中移除
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

    void Init(Object* parent);

    void EmitSignalImpl(const type_info& type_info, const internal::SlotArgsStoreSharedPtr& args_store);

    bool DisconnectImpl(
        const std::type_info& signal_info,
        const SharedConnection& connection);

    Disconnecter AddConnectionWithoutLock(const std::type_info& signal_info, SharedConnection conn);

    void SetParent(Object* parent);

    List<Object*> GetChildrenWithClear();
    void DeleteChildren();

    bool is_widget_ = false;
    bool deleting_ = false;

    Object* owner_ = nullptr;
    Object* parent_ = nullptr;
    FlagsType flags_ = 0;
    String name_;
    List<SharedConnection> connected_sender_connections_;    // 连接到的发送者
    ConnectionsManager connections_manager_;

    struct ChildItem {
        bool orphaned;
        Object* obj;
    };
    bool dirty_ = false;
    List<ChildItem> child_items_;
    List<Object*> children_cache_;
};
}
