#include <algorithm>
#include <memory>

#include <yoga/Yoga.h>

#include "./Node.hh"
#include "./Layout.hh"
#include "./Size.hh"

static YGSize globalMeasureFunc(YGNodeRef nodeRef, float width, YGMeasureMode widthMode, float height, YGMeasureMode heightMode)
{
    Node const & node = *reinterpret_cast<Node const *>(YGNodeGetContext(nodeRef));

    Size size = node.callMeasureFunc(width, widthMode, height, heightMode);
    YGSize ygSize = { static_cast<float>(size.width), static_cast<float>(size.height) };

    return ygSize;
}

Node::Node(void)
: m_self()
, m_node(YGNodeNew())
, m_parentNode()
, m_childNodes{}
, m_measureFunc(nullptr)
{
    YGNodeSetContext(m_node, reinterpret_cast<void *>(this));
}

Node::~Node(void)
{
    YGNodeFree(m_node);
}

void Node::reset(void)
{
    m_parentNode.reset();
    m_childNodes.clear();

    m_measureFunc.reset(nullptr);

    YGNodeReset(m_node);
}

void Node::copyStyle(Node const & other)
{
    YGNodeCopyStyle(m_node, other.m_node);
}

void Node::setPositionType(int positionType)
{
    YGNodeStyleSetPositionType(m_node, static_cast<YGPositionType>(positionType));
}

void Node::setPosition(int edge, double position)
{
    YGNodeStyleSetPosition(m_node, static_cast<YGEdge>(edge), position);
}

void Node::setAlignContent(int alignContent)
{
    YGNodeStyleSetAlignContent(m_node, static_cast<YGAlign>(alignContent));
}

void Node::setAlignItems(int alignItems)
{
    YGNodeStyleSetAlignItems(m_node, static_cast<YGAlign>(alignItems));
}

void Node::setAlignSelf(int alignSelf)
{
    YGNodeStyleSetAlignSelf(m_node, static_cast<YGAlign>(alignSelf));
}

void Node::setFlexDirection(int flexDirection)
{
    YGNodeStyleSetFlexDirection(m_node, static_cast<YGFlexDirection>(flexDirection));
}

void Node::setFlexWrap(int flexWrap)
{
    YGNodeStyleSetFlexWrap(m_node, static_cast<YGWrap>(flexWrap));
}

void Node::setJustifyContent(int justifyContent)
{
    YGNodeStyleSetJustifyContent(m_node, static_cast<YGJustify>(justifyContent));
}

void Node::setMargin(int edge, double margin)
{
    YGNodeStyleSetMargin(m_node, static_cast<YGEdge>(edge), margin);
}

void Node::setOverflow(int overflow)
{
    YGNodeStyleSetOverflow(m_node, static_cast<YGOverflow>(overflow));
}

void Node::setFlex(double flex)
{
    YGNodeStyleSetFlex(m_node, flex);
}

void Node::setFlexBasis(double flexBasis)
{
    YGNodeStyleSetFlexBasis(m_node, flexBasis);
}

void Node::setFlexGrow(double flexGrow)
{
    YGNodeStyleSetFlexGrow(m_node, flexGrow);
}

void Node::setFlexShrink(double flexShrink)
{
    YGNodeStyleSetFlexShrink(m_node, flexShrink);
}

void Node::setWidth(double width)
{
    YGNodeStyleSetWidth(m_node, width);
}

void Node::setHeight(double height)
{
    YGNodeStyleSetHeight(m_node, height);
}

void Node::setMinWidth(double minWidth)
{
    YGNodeStyleSetMinWidth(m_node, minWidth);
}

void Node::setMinHeight(double minHeight)
{
    YGNodeStyleSetMinHeight(m_node, minHeight);
}

void Node::setMaxWidth(double maxWidth)
{
    YGNodeStyleSetMaxWidth(m_node, maxWidth);
}

void Node::setMaxHeight(double maxHeight)
{
    YGNodeStyleSetMaxHeight(m_node, maxHeight);
}

void Node::setAspectRatio(double aspectRatio)
{
    YGNodeStyleSetAspectRatio(m_node, aspectRatio);
}

void Node::setBorder(int edge, double border)
{
    YGNodeStyleSetBorder(m_node, static_cast<YGEdge>(edge), border);
}

void Node::setPadding(int edge, double padding)
{
    YGNodeStyleSetPadding(m_node, static_cast<YGEdge>(edge), padding);
}

int Node::getPositionType(void) const
{
    return YGNodeStyleGetPositionType(m_node);
}

double Node::getPosition(int edge) const
{
    return YGNodeStyleGetPosition(m_node, static_cast<YGEdge>(edge));
}

int Node::getAlignContent(void) const
{
    return YGNodeStyleGetAlignContent(m_node);
}

int Node::getAlignItems(void) const
{
    return YGNodeStyleGetAlignItems(m_node);
}

int Node::getAlignSelf(void) const
{
    return YGNodeStyleGetAlignSelf(m_node);
}

int Node::getFlexDirection(void) const
{
    return YGNodeStyleGetFlexDirection(m_node);
}

int Node::getFlexWrap(void) const
{
    return YGNodeStyleGetFlexWrap(m_node);
}

int Node::getJustifyContent(void) const
{
    return YGNodeStyleGetJustifyContent(m_node);
}

double Node::getMargin(int edge) const
{
    return YGNodeStyleGetMargin(m_node, static_cast<YGEdge>(edge));
}

int Node::getOverflow(void) const
{
    return YGNodeStyleGetOverflow(m_node);
}

double Node::getFlexBasis(void) const
{
    return YGNodeStyleGetFlexBasis(m_node);
}

double Node::getFlexGrow(void) const
{
    return YGNodeStyleGetFlexGrow(m_node);
}

double Node::getFlexShrink(void) const
{
    return YGNodeStyleGetFlexShrink(m_node);
}

double Node::getWidth(void) const
{
    return YGNodeStyleGetWidth(m_node);
}

double Node::getHeight(void) const
{
    return YGNodeStyleGetHeight(m_node);
}

double Node::getMinWidth(void) const
{
    return YGNodeStyleGetMinWidth(m_node);
}

double Node::getMinHeight(void) const
{
    return YGNodeStyleGetMinHeight(m_node);
}

double Node::getMaxWidth(void) const
{
    return YGNodeStyleGetMaxWidth(m_node);
}

double Node::getMaxHeight(void) const
{
    return YGNodeStyleGetMaxHeight(m_node);
}

double Node::getAspectRatio(void) const
{
    return YGNodeStyleGetAspectRatio(m_node);
}

double Node::getBorder(int edge) const
{
    return YGNodeStyleGetBorder(m_node, static_cast<YGEdge>(edge));
}

double Node::getPadding(int edge) const
{
    return YGNodeStyleGetPadding(m_node, static_cast<YGEdge>(edge));
}

void Node::insertChild(std::shared_ptr<Node> child, unsigned index)
{
    YGNodeInsertChild(m_node, child->m_node, index);

    child->m_parentNode = m_self.lock();
    m_childNodes.insert(std::next(m_childNodes.begin(), index), child);
}

void Node::removeChild(std::shared_ptr<Node> child)
{
    auto it = std::find(m_childNodes.begin(), m_childNodes.end(), child);

    if (it == m_childNodes.end())
        return;

    child->m_parentNode.reset();
    m_childNodes.erase(it);

    YGNodeRemoveChild(m_node, child->m_node);
}

unsigned Node::getChildCount(void) const
{
    return YGNodeGetChildCount(m_node);
}

std::shared_ptr<Node> Node::getParent(void)
{
    return m_parentNode;
}

std::shared_ptr<Node> Node::getChild(unsigned index)
{
    if (index >= this->getChildCount())
        return std::shared_ptr<Node>();

    return *std::next(m_childNodes.begin(), index);
}

void Node::setMeasureFunc(nbind::cbFunction & measureFunc)
{
    m_measureFunc.reset(new nbind::cbFunction(measureFunc));

    YGNodeSetMeasureFunc(m_node, &globalMeasureFunc);
}

void Node::unsetMeasureFunc(void)
{
    m_measureFunc.reset(nullptr);

    YGNodeSetMeasureFunc(m_node, nullptr);
}

Size Node::callMeasureFunc(double width, int widthMode, double height, int heightMode) const
{
    return m_measureFunc->call<Size>(width, widthMode, height, heightMode);
}

void Node::markDirty(void)
{
    YGNodeMarkDirty(m_node);
}

bool Node::isDirty(void) const
{
    return YGNodeIsDirty(m_node);
}

void Node::setHasNewLayout(bool hasNewLayout)
{
    YGNodeSetHasNewLayout(m_node, hasNewLayout);
}

void Node::calculateLayout(double width, double height, int direction)
{
    YGNodeCalculateLayout(m_node, width, height, static_cast<YGDirection>(direction));
}

bool Node::hasNewLayout(void) const
{
    return YGNodeGetHasNewLayout(m_node);
}

double Node::getComputedLeft(void) const
{
    return YGNodeLayoutGetLeft(m_node);
}

double Node::getComputedRight(void) const
{
    return YGNodeLayoutGetRight(m_node);
}

double Node::getComputedTop(void) const
{
    return YGNodeLayoutGetTop(m_node);
}

double Node::getComputedBottom(void) const
{
    return YGNodeLayoutGetBottom(m_node);
}

double Node::getComputedWidth(void) const
{
    return YGNodeLayoutGetWidth(m_node);
}

double Node::getComputedHeight(void) const
{
    return YGNodeLayoutGetHeight(m_node);
}

Layout Node::getComputedLayout(void) const
{
    Layout layout;

    layout.left = YGNodeLayoutGetLeft(m_node);
    layout.right = YGNodeLayoutGetRight(m_node);

    layout.top = YGNodeLayoutGetTop(m_node);
    layout.bottom = YGNodeLayoutGetBottom(m_node);

    layout.width = YGNodeLayoutGetWidth(m_node);
    layout.height = YGNodeLayoutGetHeight(m_node);

    return layout;
}