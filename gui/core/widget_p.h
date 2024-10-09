#include <gui/tools/scope_variable.h>
#include <memory>

namespace fugui {
namespace internal {
class WidgetTreeNode;
class WidgetEngine;
using WidgetTreeNodePtr = std::shared_ptr<WidgetTreeNode>;

class WidgetPrivate
{
public:
    ScopeCondition enable_sc_;
    ScopeCondition visible_sc_;
    ScopeVariable<Vector2> size_sc_;
    WidgetTreeNodePtr owning_node_;
    bool resume_visible_;
    bool is_painting_children_;
    bool initialized_;
    int flags_;
    WidgetType widget_type_;

    WidgetPrivate()
	    : enable_sc_(true),
	      visible_sc_(true),
	      resume_visible_(false),
	      is_painting_children_(false),
	      initialized_(false),
	      flags_(0), widget_type_()
    {
    }
};
}
}