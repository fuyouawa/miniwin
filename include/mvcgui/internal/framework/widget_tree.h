#pragma once
#include <memory>
#include <vector>


namespace mvcgui {
class Widget;

namespace internal {
class WidgetTreeNode;
using WidgetTreeNodePtr = std::shared_ptr<WidgetTreeNode>;

class WidgetTreeNode : public std::enable_shared_from_this<WidgetTreeNode>
{
public:
	WidgetTreeNode(Widget* widget, WidgetTreeNodePtr parent, bool is_root = false);
	~WidgetTreeNode();

	static WidgetTreeNodePtr Instantiate(Widget* widget);

	void Paint();
	void PaintChildren();

	void OnRemoveChild(WidgetTreeNodePtr node);
	void OnAddChild(WidgetTreeNodePtr node);
	void OnModifyVisible(bool b);
	void OnClose();

	void OnRecursionClose(bool is_in_children);
	void OnModifyChildrenVisible(bool b);

	bool closed_;
	bool initialized_;
	bool is_root_;
	WidgetTreeNodePtr parent_;
	std::vector<WidgetTreeNodePtr> children_;
	Widget* widget_;
};
}
}