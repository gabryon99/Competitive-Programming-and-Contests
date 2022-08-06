#ifndef CPC_BINAR_SEARCH_TREE_HPP
#define CPC_BINAR_SEARCH_TREE_HPP

#include "../utility.hpp"

namespace cpc::ds {

    template <std::totally_ordered NodeValue>
    class BinarySearchTree {

    private:

        struct NodeTree {

            NodeValue m_value;
            std::shared_ptr<NodeTree> m_left{nullptr};
            std::shared_ptr<NodeTree> m_right{nullptr};

            NodeTree(NodeValue mValue, const std::shared_ptr<NodeTree> &mLeft, const std::shared_ptr<NodeTree> &mRight)
                    : m_value(mValue), m_left(mLeft), m_right(mRight) {}
        };

        std::shared_ptr<NodeTree> root{};

        auto insertNode(std::shared_ptr<NodeTree>& node, NodeValue&& value) -> void {
            if (value < node->m_value) {
                if (!node->m_left) {
                    node->m_left = std::make_shared<NodeTree>(std::move(value), nullptr, nullptr);
                }
                else {
                    insertNode(node->m_left, std::move(value));
                }
            }
            else {
                if (!node->m_right) {
                    node->m_right = std::make_shared<NodeTree>(std::move(value), nullptr, nullptr);
                }
                else {
                    insertNode(node->m_right, std::move(value));
                }
            }
        }

        [[maybe_unused]]
        auto deleteNode(std::shared_ptr<NodeTree>& node, NodeValue value) -> std::shared_ptr<NodeTree> {

            if (!node) {
                return nullptr;
            }

            if (value < node->m_value) {
                node->m_left = deleteNode(node->m_left, value);
                return node;
            }
            else if (value > node->m_value) {
                node->m_right = deleteNode(node->m_right, value);
                return node;
            }

            // The node value is equal to key to delete
            if (!node->m_left) {
                return node->m_right;
            }
            else if (!node->m_right) {
                return node->m_left;
            }
            else {
                // The current node has two children!
                node->m_right = lift(node->m_right, node);
                return node;
            }
        }

        auto lift(std::shared_ptr<NodeTree>& node, std::shared_ptr<NodeTree>& toDelete) -> std::shared_ptr<NodeTree> {
            if (node->m_left) {
                node->m_left = lift(node->m_left, toDelete);
                return node;
            }
            else {
                toDelete->m_value = std::move(node->m_value);
                return node->m_right;
            }
        }

        template<typename Function>
        auto visitInOrder(std::shared_ptr<NodeTree>& node, Function fun) -> void {
            if (node) {
                visitInOrder(node->m_left, fun);
                fun(node->m_value);
                visitInOrder(node->m_right, fun);
            }
        }

        template<typename Function>
        auto visitPreOrder(std::shared_ptr<NodeTree>& node, Function fun) -> void {
            if (node) {
                fun(node->m_value);
                visitPreOrder(node->m_left, fun);
                visitPreOrder(node->m_right, fun);
            }
        }

        template<typename Function>
        auto visitPostOrder(std::shared_ptr<NodeTree>& node, Function fun) -> void {
            if (node) {
                visitPostOrder(node->m_left, fun);
                visitPostOrder(node->m_right, fun);
                fun(node->m_value);
            }
        }

        auto lookup(std::shared_ptr<NodeTree>& node, NodeValue value) -> bool {
            if (node) {
                if (node->m_value == value) {
                    return true;
                }
                if (value > node->m_value) {
                    return lookup(node->m_right, value);
                }

                return lookup(node->m_left, value);
            }
            return false;
        }

        auto findSuccessor(std::shared_ptr<NodeTree>& node, NodeValue key) -> std::optional<NodeValue> {

            if (!node) {
                return std::nullopt;
            }

            if (node->m_value <= key) {
                return findSuccessor(node->m_right, key);
            }

            if (auto left = findSuccessor(node->m_left, key)) {
                return left;
            }

            return node->m_value;
        }

        auto findPredecessor(std::shared_ptr<NodeTree>& node, NodeValue key) -> std::optional<NodeValue> {

            if (!node) {
                return std::nullopt;
            }

            if (node->m_value >= key) {
                return findPredecessor(node->m_left, key);
            }

            if (auto right = findPredecessor(node->m_right, key)) {
                return right;
            }

            return node->m_value;
        }

    public:

        enum class VisitType {
            IN_ORDER,
            PRE_ORDER,
            POST_ORDER,
        };

        BinarySearchTree<NodeValue>(std::initializer_list<NodeValue> values) {
            for (auto val: values) {
                insert(std::move(val));
            }
        }

        template<typename Function>
        auto visit(VisitType type, Function fun) -> void {
            switch (type) {
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

        auto deleteKey(NodeValue value) -> void {
            deleteNode(root, value);
        }

        auto lookup(NodeValue v) -> bool {
            return lookup(this->root, v);
        }

        auto findSuccessor(NodeValue value) -> std::optional<NodeValue> {
            return findSuccessor(root, value);
        }

        auto findPredecessor(NodeValue value) -> std::optional<NodeValue> {
            return findPredecessor(root, value);
        }

        auto minimum() const -> NodeValue {

            auto node = root;
            while (node->m_left) {
                node = node->m_left;
            }

            return node->m_value;
        }

        auto maximum() const -> NodeValue {

            auto node = root;
            while (node->m_right) {
                node = node->m_right;
            }

            return node->m_value;
        }

        [[maybe_unused]]
        auto insert(NodeValue&& value) -> BinarySearchTree<NodeValue>& {

            if (!root) {
                root = std::make_shared<NodeTree>(std::move(value), nullptr, nullptr);
                return *this;
            }

            insertNode(root, std::move(value));

            return *this;
        }

    };
}

#endif //CPC_BINAR_SEARCH_TREE_HPP
