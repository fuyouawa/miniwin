#pragma once
#include <miniwin/core/object.h>

#include <vector>
#include <typeindex>
#include <string>
#include <mutex>

namespace miniwin {
class Object::Impl {
public:
    explicit Impl(Object* owner);

    ~Impl();

    struct Connection
    {
        WeakObject sender;
        WeakObject receiver;
        internal::UniqueSlotObject slot_obj;
        std::type_index signal_info;
        ConnectionFlags connection_type;
        InvokeType invoke_type;
    };
    using SharedConnection = std::shared_ptr<Connection>;
    using WeakConnection = std::weak_ptr<Connection>;

    class ConnectionList : public List<SharedConnection> {
    public:
        std::mutex mutex_;
    };

    class ConnectionsManager
    {
    public:
        bool dirty_; // 一些连接已经被切断了, 但是并没有从列表中移除
        std::unordered_map<std::type_index, ConnectionList> map_;

        void ClearDirty();
    };

    static Disconnecter ConnectImpl(
        const SharedObject& sender,
        const std::type_info& signal_info,
        const SharedObject& receiver,
        internal::UniqueSlotObject&& slot_obj,
        ConnectionFlags connection_flags,
        InvokeType invoke_type);


    void Init(const SharedObject& parent);

    void EmitSignalImpl(const type_info& signal_info, const internal::SharedSlotArgsStore& args_store);

    bool DisconnectImpl(const SharedConnection& connection);

    Disconnecter AddConnection(SharedConnection&& connection);

    void SetParent(const SharedObject& parent);

    List<SharedObject> GetChildrenWithProcess();
    void DeleteChildren();

    bool is_widget_ = false;
    bool is_layout_ = false;
    bool deleting_ = false;
    bool orphaned_ = false;
    bool dirty_ = false;

    Object* owner_ = nullptr;
    SharedObject parent_;
    FlagsType flags_ = 0;
    String name_;
    std::mutex signal_mutex_;
    List<WeakConnection> connected_sender_connections_;    // 连接到的发送者
    ConnectionsManager connections_manager_;

private:
    List<SharedObject> children_;
    List<SharedObject> pending_addition_children_;
};
}
