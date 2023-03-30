/**
 * @file basic.h
 * @author Zhonghao Han (hzh0602@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once
#include <functional>

template <typename T>
class ListNode {
   public:
    ListNode<T>* m_next;
    ListNode<T>* m_prev;

    T m_data;
    ListNode(T data) : m_data(data) {}
};

template <typename T>
class List {
   public:
    List() : m_head(nullptr) {}
    List(std::function<bool(ListNode<T>*, ListNode<T>*)> predicate) : m_head(nullptr), m_predicate(predicate) {}
    void add(ListNode<T>* node) {
        if (!m_head) {
            node->m_next = nullptr;
            node->m_prev = nullptr;
            m_head = node;
        } else {
            if (!m_predicate) {  // no predicate, insert to the start
                node->m_next = m_head;
                node->m_prev = nullptr;
                m_head->m_prev = node;
                m_head = node;
            } else {
                ListNode<T>* current = m_head;
                while (current->m_next && m_predicate(current, node)) {
                    current = current->m_next;
                }
                if (m_predicate(current, node)) {
                    node->m_next = nullptr;
                    node->m_prev = current;
                    current->m_next = node;
                } else {
                    node->m_prev = current->m_prev;
                    node->m_next = current;
                    if (current->m_prev) {
                        current->m_prev->m_next = node;
                    } else {
                        m_head = node;
                    }
                    current->m_prev = node;
                }
            }
        }
    }

    void remove(ListNode<T>* node) {
        if (node->m_prev) {
            node->m_prev->m_next = node->m_next;
        } else {
            head = node->m_next;
        }

        if (node->m_next) {
            node->m_next->m_prev = node->m_prev;
        }
    }

    void print() {
        ListNode<T>* current = m_head;
        while (current) {
            std::cout << current->m_data << std::endl;
            current = current->m_next;
        }
    }

    T head() {
        return m_head->m_data;
    }

   private:
    ListNode<T>*                                    m_head;
    std::function<bool(ListNode<T>*, ListNode<T>*)> m_predicate;
};
