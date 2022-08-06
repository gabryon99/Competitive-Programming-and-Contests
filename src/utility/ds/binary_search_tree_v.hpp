#ifndef CPC_BINARY_SEARCH_TREE_V_HPP
#define CPC_BINARY_SEARCH_TREE_V_HPP

#include "../utility.hpp"

#include <sstream>

namespace cpc::ds {

    template <std::totally_ordered NodeValue>
    class BinarySearchTreeV {

    private:

        using NodeIndex = int;

        struct NodeTree {

            bool m_dead = false;

            NodeValue m_value;
            NodeIndex m_left;
            NodeIndex m_right;

            explicit NodeTree(){}

            explicit NodeTree(NodeValue mValue, NodeIndex mLeft = -1, NodeIndex mRight = -1) :
                m_value(mValue), m_left(mLeft), m_right(mRight) {}
        };

        static constexpr NodeIndex EMPTY_INDEX = -1;

        NodeIndex root = -1;
        std::vector<NodeTree> m_nodes;

        // Contains "free" node
        std::deque<NodeIndex> m_tombstones;

        uint64_t size = 0;

        auto getFreeSlot() -> NodeIndex {
            auto top = m_tombstones[0];
            m_tombstones.pop_front();
            return top;
        }

        auto placeTombstone(NodeIndex index) -> void {
            // Say hello to the new dead node :)
            m_nodes[index].m_dead = true;
            m_tombstones.push_back(index);
        }

        auto getLeftChildIndex(NodeIndex node) -> NodeIndex {
            return m_nodes[node].m_left;
        }

        auto getRightChildIndex(NodeIndex node) -> NodeIndex {
            return m_nodes[node].m_right;
        }

        auto isEmptyNode(NodeIndex node) -> bool {
            return node == EMPTY_INDEX;
        }

        auto hasLeftChild(NodeIndex node) -> bool {
            return m_nodes[node].m_left != EMPTY_INDEX;
        }

        auto hasRightChild(NodeIndex node) -> bool {
            return m_nodes[node].m_right != EMPTY_INDEX;
        }

        auto insertNode(NodeValue value) -> NodeIndex {

            if (!m_tombstones.empty()) {

                // Come back from the death!
                auto freeSlot = getFreeSlot();

                m_nodes[freeSlot].m_value = value;
                m_nodes[freeSlot].m_dead = false;
                m_nodes[freeSlot].m_right = -1;
                m_nodes[freeSlot].m_left = -1;

                return freeSlot;
            }

            // Allocate a new node
            m_nodes.push_back(NodeTree(value));

            return m_nodes.size() - 1;
        }

        auto insert(NodeIndex node, NodeValue value) -> void {
            if (value < m_nodes[node].m_value) {
                if (!hasLeftChild(node)) {
                    m_nodes[node].m_left = insertNode(value);
                }
                else {
                    insert(getLeftChildIndex(node), value);
                }
            }
            else {
                if (!hasRightChild(node)) {
                    m_nodes[node].m_right = insertNode(value);
                }
                else {
                    insert(getRightChildIndex(node), value);
                }
            }
        }

        [[maybe_unused]]
        auto deleteNode(NodeIndex node, NodeValue valueToDelete) -> NodeIndex {

            if (isEmptyNode(node)) {
                return node;
            }

            if (valueToDelete < m_nodes[node].m_value) {
                m_nodes[node].m_left = deleteNode(getLeftChildIndex(node), valueToDelete);
            }
            else if (valueToDelete > m_nodes[node].m_value) {
                m_nodes[node].m_right = deleteNode(getRightChildIndex(node), valueToDelete);
            }
            else {

                // Node to delete!
                // We should place a tombstone! 🪦

                if (!hasLeftChild(node)) {
                    placeTombstone(node);
                    return getRightChildIndex(node);
                }
                else if (!hasRightChild(node)) {
                    placeTombstone(node);
                    return getLeftChildIndex(node);
                }

                // Two children
                m_nodes[node].m_value = minValue(getRightChildIndex(node));
                m_nodes[node].m_right = deleteNode(getRightChildIndex(node), m_nodes[node].m_value);
            }

            return node;
        }

        template<typename Function>
        auto visitInOrder(NodeIndex node, Function fun) -> void {
            if (node != EMPTY_INDEX) {
                visitInOrder(getLeftChildIndex(node), fun);
                fun(m_nodes[node].m_value);
                visitInOrder(getRightChildIndex(node), fun);
            }
        }

        template<typename Function>
        auto visitPreOrder(NodeIndex node, Function fun) -> void {
            if (node != EMPTY_INDEX) {
                fun(m_nodes[node].m_value);
                visitPreOrder(getLeftChildIndex(node), fun);
                visitPreOrder(getRightChildIndex(node), fun);
            }
        }

        template<typename Function>
        auto visitPostOrder(NodeIndex node, Function fun) -> void {
            if (node != EMPTY_INDEX) {
                visitPostOrder(getLeftChildIndex(node), fun);
                visitPostOrder(getRightChildIndex(node), fun);
                fun(m_nodes[node].m_value);
            }
        }

        template<typename Function>
        auto visitBFS(Function fun) -> void {

            std::deque<NodeIndex> indices{};

            indices.push_back(root);

            while (!indices.empty()) {

                auto index = indices.front();
                indices.pop_front();

                fun(m_nodes[index].m_value);

                if (hasLeftChild(index)) indices.push_back(getLeftChildIndex(index));
                if (hasRightChild(index)) indices.push_back(getRightChildIndex(index));

            }
        }

        auto lookup(NodeIndex node, NodeValue key) -> bool {

            if (isEmptyNode(node)) {
                return false;
            }

            if (key == m_nodes[node].m_value) {
                return true;
            }

            if (key < m_nodes[node].m_value) {
                return lookup(getLeftChildIndex(node), key);
            }

            return lookup(getRightChildIndex(node), key);
        }

        auto findSuccessor(NodeIndex node, NodeValue key) -> std::optional<NodeValue> {

            if (isEmptyNode(node)) {
                return std::nullopt;
            }

            if (m_nodes[node].m_value <= key) {
                return findSuccessor(getRightChildIndex(node), key);
            }

            if (auto left = findSuccessor(getLeftChildIndex(node), key)) {
                return left;
            }

            return m_nodes[node].m_value;
        }

        auto minValue(NodeIndex node) -> NodeValue {

            auto minVal = m_nodes[node].m_value;

            while (hasLeftChild(node)) {
                minVal = m_nodes[getLeftChildIndex(node)].m_value;
                node = getLeftChildIndex(node);
            }

            return minVal;
        }

        auto findPredecessor(NodeIndex node, NodeValue key) -> std::optional<NodeValue> {

            if (isEmptyNode(node)) {
                return std::nullopt;
            }

            if (m_nodes[node].m_value >= key) {
                return findPredecessor(getLeftChildIndex(node), key);
            }

            if (auto right = findPredecessor(getRightChildIndex(node), key)) {
                return right;
            }

            return m_nodes[node].m_value;
        }

    public:

        enum class VisitType {
            BFS,
            IN_ORDER,
            PRE_ORDER,
            POST_ORDER,
        };

        BinarySearchTreeV() {}

        BinarySearchTreeV<NodeValue>(std::initializer_list<NodeValue> values) {
            for (auto& val: values) {
                insert(val);
            }
        }

        auto lookup(NodeValue v) -> bool {
            return lookup(root, v);
        }

        auto findSuccessor(NodeValue value) -> std::optional<NodeValue> {
            return findSuccessor(root, value);
        }

        auto findPredecessor(NodeValue value) -> std::optional<NodeValue> {
            return findPredecessor(root, value);
        }

        auto minimum() -> NodeValue {

            auto node = root;
            while (hasLeftChild(node)) {
                node = getLeftChildIndex(node);
            }

            return m_nodes[node].m_value;
        }

        auto maximum() -> NodeValue {

            auto node = root;
            while (hasRightChild(node)) {
                node = getRightChildIndex(node);
            }

            return m_nodes[node].m_value;
        }

        template<typename Function>
        auto visit(VisitType type, Function fun) -> void {

            if (m_nodes[root].m_dead) {
                return;
            }

            switch (type) {
                case VisitType::BFS: {
                    visitBFS(fun);
                    break;
                }
                case VisitType::IN_ORDER: {
                    visitInOrder(root, fun);
                    break;
                }
                case VisitType::POST_ORDER: {
                    visitPostOrder(root, fun);
                    break;
                }
                case VisitType::PRE_ORDER: {
                    visitPreOrder(root, fun);
                    break;
                }
            }
        }

        [[maybe_unused]]
        auto insert(NodeValue key) -> BinarySearchTreeV<NodeValue>& {

            if (size == 0) {

                // Is there a tombstone free?
                if (!m_tombstones.empty()) {
                    root = getFreeSlot();
                    m_nodes[root].m_right = EMPTY_INDEX;
                    m_nodes[root].m_left = EMPTY_INDEX;
                    m_nodes[root].m_value = key;
                    m_nodes[root].m_dead = false;
                }
                else {
                    root = 0;
                    m_nodes.push_back(NodeTree(key));
                }

                size++;

                return *this;
            }

            insert(root, key);
            size++;

            return *this;
        }

        auto printEdge(std::stringstream& stream, NodeIndex from, NodeIndex to) -> void {
            stream << "\t" << from << "->" << to << ";\n";
        }

        auto printInvisibleNode(std::stringstream& stream, NodeIndex from, int& invs) -> void {
            stream << "\t" << invs << "[label=\"/\"];\n";
            stream << "\t" << from << "->" << invs << ";\n";
            invs++;
        }

        auto graphviz() -> std::string {

            int invs = m_nodes.size();

            std::stringstream stream;
            std::deque<NodeIndex> indices{};
            indices.push_back(root);

            stream << "digraph BST {\n\tnode[ shape = plaintext ];\n";

            while (!indices.empty()) {

                auto index = indices.front();
                indices.pop_front();

                stream << "\t" << index << "[label=\"" << m_nodes[index].m_value << "\"];\n";

                if (hasLeftChild(index)) {
                    printEdge(stream, index, getLeftChildIndex(index));
                    indices.push_back(getLeftChildIndex(index));
                }
                else {
                    printInvisibleNode(stream, index, invs);
                }

                if (hasRightChild(index)) {
                    printEdge(stream, index, getRightChildIndex(index));
                    indices.push_back(getRightChildIndex(index));
                }
                else {
                    printInvisibleNode(stream, index, invs);
                }
            }

            stream << "}";

            return stream.str();
        }

        auto deleteKey(NodeValue value) -> void {

            deleteNode(root, value);
            size--;

            auto tombstones = m_tombstones.size();
            auto delta = m_nodes.capacity() - m_nodes.size();

            if (tombstones >= delta) {

                // The graveyard is pretty full...
                compact();
            }
        }

        auto compact() -> void {

        }
    };
}


#endif //CPC_BINARY_SEARCH_TREE_V_HPP
