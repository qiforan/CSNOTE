#include <iostream>
#include <vector>
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
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 
     * @param a ListNode类vector 指向这些数链的开头
     * @return ListNode类
     */
    ListNode* solve(vector<ListNode*>& a)
    {
		ListNode* head = NULL;
		ListNode* tail = head;
		while(1){
			ListNode* temp = tail;
			for(int i = 0; i < a.size(); i++){
				if(a[i]){
					if(tail == nullptr){
						tail = head = a[i];
					}
					else{
						tail->next = a[i];
						tail = tail->next;
					}
					a[i] = a[i]->next;
				}
			}
			if(temp == tail)
				break;
		}
		return head;
		
    }
};

int main()
{
    return 0;
}