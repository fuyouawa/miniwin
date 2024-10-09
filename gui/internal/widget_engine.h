#pragma once
#include <fugui/tools/property.h>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>

namespace fugui {
class Widget;

namespace internal {
class WidgetTreeNode;
using WidgetTreeNodePtr = std::shared_ptr<WidgetTreeNode>;

class WidgetEngine : public Singleton<WidgetEngine>
{
	friend class CoreApplication;
	friend class WidgetTreeNode;
	friend class Singleton<WidgetEngine>;
public:
	using Functor = std::function<void()>;

	void InitializeWidget(Widget* widget, Widget* parent);
	void CloseWidget(Widget* widget);

	Widget* GetParent(const Widget* const widget);
	void ModifyParent(Widget* widget, Widget* new_parent);
	void ModifyVisible(Widget* widget, bool b);
	void InvokeInNextFrame(Functor&& func);

	bool IsEmpty();
	void Thinking();

	auto& root() { return root_; }
	auto is_painting() const { return is_painting_; }

	void PrintTree();

	bool IsInUiThread();

	void CloseAll();

private:
	WidgetEngine();

	void DealWithQueue();
	void PaintAll();

	bool is_painting_;
	WidgetTreeNodePtr root_;

	std::thread::id ui_thread_id_;
	std::vector<std::pair<WidgetTreeNodePtr, WidgetTreeNodePtr>> modify_parent_queue_;
	std::vector<std::pair<WidgetTreeNodePtr, bool>> modify_visible_queue_;
	std::vector<WidgetTreeNodePtr> close_node_queue_;
	std::vector<Functor> pending_functors_queue_;
	std::mutex func_queue_mutex_;
};
}
}