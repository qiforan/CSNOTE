#include <list>
#include <mutex>
#include <algorithm>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_val)
{
	std::lock_guard<std::mutex> lock(some_mutex);
	some_list.push_back(new_val);
}

bool list_contains(int value_to_find)
{
	std::lock_guard<std::mutex> lock(some_mutex);
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}
