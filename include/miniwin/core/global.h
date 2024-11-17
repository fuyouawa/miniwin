#pragma once
#include <memory>

#include <miniwin/defs.h>

namespace miniwin {
using FlagsType = int32_t;
using WidgetId = uint16_t;

class Object;
using SharedObject = std::shared_ptr<Object>;
using SharedConstObject = std::shared_ptr<const Object>;
using WeakObject = std::weak_ptr<Object>;
using WeakConstObject = std::weak_ptr<const Object>;

class Widget;
using SharedWidget = std::shared_ptr<Widget>;
using SharedConstWidget = std::shared_ptr<const Widget>;
using WeakWidget = std::weak_ptr<Widget>;
using WeakConstWidget = std::weak_ptr<const Widget>;

class AbstractItemModel;
using SharedItemModel = std::shared_ptr<AbstractItemModel>;
using SharedConstItemModel = std::shared_ptr<const AbstractItemModel>;
using WeakItemModel = std::weak_ptr<AbstractItemModel>;
using WeakConstItemModel = std::weak_ptr<const AbstractItemModel>;

class AbstractItemView;
using SharedItemView = std::shared_ptr<AbstractItemView>;
using SharedConstItemView = std::shared_ptr<const AbstractItemView>;
using WeakItemView = std::weak_ptr<AbstractItemView>;
using WeakConstItemView = std::weak_ptr<const AbstractItemView>;

class AbstractItemDelegate;
using SharedItemDelegate = std::shared_ptr<AbstractItemDelegate>;
using SharedConstItemDelegate = std::shared_ptr<const AbstractItemDelegate>;
using WeakItemDelegate = std::weak_ptr<AbstractItemDelegate>;
using WeakConstItemDelegate = std::weak_ptr<const AbstractItemDelegate>;

class ItemSelectionModel;
using SharedItemSelectionModel = std::shared_ptr<ItemSelectionModel>;
using SharedConstItemSelectionModel = std::shared_ptr<const ItemSelectionModel>;
using WeakItemSelectionModel = std::weak_ptr<ItemSelectionModel>;
using WeakConstItemSelectionModel = std::weak_ptr<const ItemSelectionModel>;

class Window;
using SharedWindow = std::shared_ptr<Window>;
using SharedConstWindow = std::shared_ptr<const Window>;
using WeakWindow = std::weak_ptr<Window>;
using WeakConstWindow = std::weak_ptr<const Window>;
}
