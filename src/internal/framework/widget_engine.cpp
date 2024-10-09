#include <fugui/internal/framework/widget_engine.h>
#include <fugui/internal/framework/widget_tree.h>
#include <fugui/internal/framework/core_application.h>
#include <format>
#include <fugui/tools/algorithm.h>
#include <fugui/core/widget.h>

namespace fugui {
namespace internal {
void RecursionPrintWidgetTree(WidgetTreeNode* root, size_t layer) {
	std::string str(layer * 4, ' ');
	auto status = !root->widget_->is_showing() ? " - [Hiding]" : "";
	str += std::format("{}{}\n", (const char*)root->widget_->id().c_str(), status);
	printf(str.c_str());
	for (auto& child : root->children_) {
		RecursionPrintWidgetTree(child.get(), layer + 1);
	}
}

void WidgetEngine::DealWithQueue() {
	assert(!internal::WidgetEngine::instance().is_painting());

	for (auto& [node, parent] : modify_parent_queue_) {
		if (node->initialized_) {
			node->parent_->OnRemoveChild(node);
		}
		else {
			assert(!node->parent_);
			node->initialized_ = true;
		}
		parent->OnAddChild(node);
	}
	modify_parent_queue_.clear();

	for (auto& node : close_node_queue_) {
		node->OnClose();
	}
	close_node_queue_.clear();

	for (auto& [node, b] : modify_visible_queue_) {
		node->OnModifyVisible(b);
	}
	modify_visible_queue_.clear();

	std::vector<Functor> functors;
	{
		std::lock_guard<std::mutex> lk{ func_queue_mutex_ };
		pending_functors_queue_.swap(functors);
	}
	for (auto& func : functors) {
		func();
	}
}

WidgetEngine::WidgetEngine()
	: root_{ std::make_shared<WidgetTreeNode>(nullptr, nullptr, true) },
	is_painting_{ false },
	ui_thread_id_{ std::this_thread::get_id() }
{}


void WidgetEngine::InitializeWidget(Widget* widget, Widget* parent) {
	assert(IsInUiThread());
	assert(!widget->owning_node_);
	auto node_ptr = WidgetTreeNode::Instantiate(widget);
	ModifyParent(widget, parent);
}

void WidgetEngine::CloseWidget(Widget* widget) {
	assert(IsInUiThread());
	auto node = widget->owning_node_;
	assert(node);
	assert(!node->closed_);
	assert(!IsContainer(close_node_queue_, node));
	assert(!node->is_root_);
	close_node_queue_.push_back(node);
}

Widget* WidgetEngine::GetParent(const Widget* const widget) {
	if (auto parent_node = widget->owning_node_->parent_) {
		return parent_node->widget_;
	}
	return nullptr;
}

void WidgetEngine::ModifyParent(Widget* widget, Widget* new_parent) {
	assert(IsInUiThread());
	assert(widget != new_parent);
	auto node = widget->owning_node_;
	auto parent = new_parent ? new_parent->owning_node_ : root_;

	assert(!node->closed_);
	if (node->initialized_) {
		assert(node->parent_ != parent);
		assert(std::ranges::find(parent->children_, node) == parent->children_.end());
	}
	if (!parent->is_root_) {
		if (parent->widget_->widget_type_ == Widget::Type::kMinimumControl) {
			throw std::invalid_argument("You cannot attach control's parent to a minimum control!");
		}
	}
	assert(std::ranges::find(
		modify_parent_queue_,
		node,
		[](auto& pair) { return pair.first; }
	) == modify_parent_queue_.end());
	modify_parent_queue_.emplace_back(node, parent);
}

void WidgetEngine::ModifyVisible(Widget* widget, bool b) {
	assert(IsInUiThread());
	auto node = widget->owning_node_;

	assert(std::ranges::find(
		modify_visible_queue_,
		node,
		[](auto& pair) { return pair.first; }
	) == modify_visible_queue_.end());

	if (*node->widget_->visible_sc_ == b)
		return;

	bool can_set = true;
	if (b) {
		if (!node->parent_->is_root_) {
			can_set = node->parent_->widget_->is_showing();
		}
	}
	node->widget_->resume_visible_ = b;
	if (can_set) {
		modify_visible_queue_.emplace_back(node, b);
	}
}

void WidgetEngine::InvokeInNextFrame(Functor&& func) {
	std::lock_guard<std::mutex> lk{ func_queue_mutex_ };
	pending_functors_queue_.push_back(std::move(func));
}

void WidgetEngine::PaintAll() {
	is_painting_ = true;
	root_->PaintChildren();
	is_painting_ = false;
}

bool WidgetEngine::IsEmpty() {
	return root_->children_.empty() &&
		modify_parent_queue_.empty() &&
		modify_visible_queue_.empty() &&
		close_node_queue_.empty();
}

void WidgetEngine::Thinking()
{
	assert(IsInUiThread());
	DealWithQueue();
	PaintAll();
}

void WidgetEngine::PrintTree() {
	for (auto& child : root_->children_) {
		RecursionPrintWidgetTree(child.get(), 0);
	}
}

bool WidgetEngine::IsInUiThread() {
	return std::this_thread::get_id() == ui_thread_id_;
}

void WidgetEngine::CloseAll() {
	for (auto& child : root_->children_) {
		CloseWidget(child->widget_);
	}
}
}
}