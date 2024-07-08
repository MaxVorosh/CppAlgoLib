#include "functional"

#pragma once

namespace SegmentTree {


// T should have copy constructor
template <typename T>
class SegmentTree {
private:
    struct SegmentNode {
        T val;
        SegmentNode* l;
        SegmentNode* r;
        
        SegmentNode(T& _val, SegmentNode* _l=nullptr, SegmentNode* _r=nullptr) {
            val = _val;
            l = _l;
            r = _r;
        }
    };

    SegmentNode* root;
    std::function<T(T, T)> func;
    std::size_t size;

    SegmentNode* build_tree(T* values, std::size_t l, std::size_t r, std::function<T(T, T)> tfunc) {
        if (l + 1 == r) {
            SegmentNode* node = new SegmentNode(values[l]);
            return node;
        }
        std::size_t m = (l + r) / 2;
        SegmentNode* left = build_tree(values, l, m, tfunc);
        SegmentNode* right = build_tree(values, m, r, tfunc);
        T new_val = tfunc(left->val, right->val);
        SegmentNode* node = new SegmentNode(new_val, left, right);
        return node;
    }

    void destroy_tree(SegmentNode* troot) {
        if (troot == nullptr) {
            return;
        }
        destroy_tree(troot->l);
        destroy_tree(troot->r);
        delete troot;
    }

    void update_tree(SegmentNode* troot, std::size_t lv, std::size_t rv, std::size_t ind, T& val) {
        if (lv + 1 == rv) {
            troot->val = val;
            return;
        }
        std::size_t m = (lv + rv) / 2;
        if (m > ind) {
            update_tree(troot->l, lv, m, ind, val);
        }
        else {
            update_tree(troot->r, m, rv, ind, val);
        }
    }

    T get_tree_segment(SegmentNode* troot, std::size_t lv, std::size_t rv, std::size_t l, std::size_t r) {
        if (lv == l && rv == r) {
            return troot->val;
        }
        std::size_t m = (lv + rv) / 2;
        if (l >= m) {
            return get_tree_segment(troot->r, m, rv, l, r);
        }
        if (r <= m) {
            return get_tree_segment(troot->l, lv, m, l, r);
        }
        return func(get_tree_segment(troot->l, lv, m, l, m), get_tree_segment(troot->r, m, rv, m, r));
    }

public:
    SegmentTree(T* values, std::size_t _size, std::function<T(T, T)> _func) {
        if (_size == 0) {
            throw std::logic_error("Wrong size");
        }
        root = build_tree(values, 0, _size, _func);
        func = _func;
        size = _size;
    }

    ~SegmentTree() {
        destroy_tree(root);
    }

    void update(std::size_t ind, T& val) {
        if (ind >= size) {
            throw std::logic_error("Wrong index");
        }
        update_tree(root, 0, size, ind, val);
    }

    T get_segment(std::size_t l, std::size_t r) {
        if (r <= l || r >= size) {
            throw std::logic_error("Wrong segment");
        }
        return get_tree_segment(root, 0, size, l, r);
    } 

};

}