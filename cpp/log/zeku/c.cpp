#include <iostream>
using namespace std;
struct ListNode {
    int val;
    struct ListNode* next;
    ListNode(int x)
        : val(x)
        , next(nullptr)
    {
    }
};
class Solution {
public:
    /**
     * 将一个链表 m 位置到 n 位置之间进行逆转
     *
     * 
     * @param head ListNode类 
     * @param m int整型 
     * @param n int整型 
     * @return ListNode类
     */
    ListNode* kNode(ListNode* head, int k)
    {
        while (k--)
            head = head->next;
        return head;
    }
    ListNode* reverseBetween(ListNode* head, int m, int n)
    {
        // write code here
        ListNode* fakeNode = new ListNode(0);
        fakeNode->next = head;
        auto pre = kNode(fakeNode, m - 1);
        auto p = pre->next;
        auto r = kNode(fakeNode, n + 1);
		auto l = p;
        for (int i = m ; i <= n; i++) {
            auto temp = p;
            p = p->next;
            temp->next = pre->next;
            pre->next = temp;
        }
        l->next = r;
		return fakeNode->next;
    }
};

int main()
{
	ListNode* head = new ListNode(1);
	auto p = head;
	for (int i = 2; i <= 5; i++) {
		p ->next = new ListNode(i);
		p = p->next;
	}
	Solution s;
	s.reverseBetween(head,2,4);
}