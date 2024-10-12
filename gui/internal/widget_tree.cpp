// #include <gui/internal/widget_tree.h>
// #include <gui/core/widget_impl.h>
//
// namespace fugui {
// namespace internal {
// WidgetTreeNode::WidgetTreeNode(Widget* widget, WidgetTreeNodePtr parent, bool is_root)
// 	: widget_{ widget },
// 	parent_{ parent },
// 	closed_{ false },
// 	initialized_{ false },
// 	is_root_{ is_root }
// {
// }
//
// WidgetTreeNode::~WidgetTreeNode() {
// 	if (!closed_ && !is_root_) {
// 		OnClose();
// 	}
// }
//
// WidgetTreeNodePtr WidgetTreeNode::Instantiate(Widget* widget) {
// 	auto node = std::make_shared<WidgetTreeNode>(widget, nullptr);
// 	widget->impl_->owning_node_ = node;
// 	return node;
// }
//
// void WidgetTreeNode::Paint() {
// 	assert(!closed_);
// 	assert(initialized_);
// 	assert(!is_root_);
// 	widget_->OnEnter();
// 	if (!parent_->is_root_) {
// 		assert(parent_->widget_);
// 		if (!parent_->widget_->is_showing()) {
// 			assert(parent_->widget_->impl_->visible_sc_ == widget_->impl_->visible_sc_);
// 		}
// 	}
// 	if (widget_->is_showing()) {
// 		widget_->OnPaintBegin();
// 	}
// 	widget_->OnUpdate();
// 	PaintChildren();
// 	if (widget_->is_showing()) {
// 		widget_->OnPaintEnd();
// 	}
// 	widget_->OnExit();
// }
//
// void WidgetTreeNode::PaintChildren() {
// 	for (auto& child : children_) {
// 		assert(child->parent_.get() == this);
// 		child->Paint();
// 	}
// }
//
// void WidgetTreeNode::OnRemoveChild(WidgetTreeNodePtr node) {
// 	auto found_node = std::ranges::find(children_, node);
// 	assert(found_node != children_.end());
// 	assert((*found_node)->parent_.get() == this);
// 	(*found_node)->parent_.reset();
// 	children_.erase(found_node);
// }
//
// void WidgetTreeNode::OnAddChild(WidgetTreeNodePtr node) {
// 	assert(!node->parent_);
// 	node->parent_ = shared_from_this();
// 	children_.push_back(node);
// }
//
// void WidgetTreeNode::OnModifyVisible(bool b) {
// 	widget_->impl_->resume_visible_ = b;
// 	widget_->impl_->visible_sc_.set_control(b);
// 	OnModifyChildrenVisible(b);
// }
//
// void WidgetTreeNode::OnClose() {
// 	assert(!closed_);
// 	OnRecursionClose(false);
// 	parent_->OnRemoveChild(shared_from_this());
// }
//
// void WidgetTreeNode::OnRecursionClose(bool is_in_children) {
// 	for (auto& child : children_) {
// 		child->OnRecursionClose(true);
// 	}
// 	widget_->Destroy();
// 	widget_->impl_->owning_node_.reset();
// 	children_.clear();
// 	if (is_in_children) {
// 		parent_.reset();
// 	}
// 	closed_ = true;
// }
//
// void WidgetTreeNode::OnModifyChildrenVisible(bool b) const
// {
// 	widget_->impl_->visible_sc_.set_control(b ? widget_->impl_->resume_visible_ : b);
// 	for (auto& child : children_) {
// 		child->OnModifyChildrenVisible(b);
// 	}
// }
// }
// }