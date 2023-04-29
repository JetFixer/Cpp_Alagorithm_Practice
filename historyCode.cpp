#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <deque>
#include <queue>
#include <stack>
#include <numeric>
#include <unordered_map>

#define pi 3.1415926535

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
};

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
	ListNode* nodePtr1 = list1, *nodePtr2 = list2;
	ListNode* listTemp = new ListNode;
	ListNode* ListAns = listTemp;

	while (nodePtr1 != NULL || nodePtr2 != NULL)
	{
		if (nodePtr1 == NULL)
		{
			listTemp->val = nodePtr2->val;
			listTemp->next = new ListNode;
			listTemp = listTemp->next;
			nodePtr2 = nodePtr2->next;
		}
		else if (nodePtr2 == NULL)
		{
			listTemp->val = nodePtr1->val;
			listTemp->next = new ListNode;
			listTemp = listTemp->next;
			nodePtr1 = nodePtr1->next;
		}
		else
		{
			if (nodePtr1->val < nodePtr2->val)
			{
				listTemp->val = nodePtr1->val;
				listTemp->next = new ListNode;
				listTemp = listTemp->next;
				nodePtr1 = nodePtr1->next;
			}
			else
			{
				listTemp->val = nodePtr2->val;
				listTemp->next = new ListNode;
				listTemp = listTemp->next;
				nodePtr1 = nodePtr2->next;
			}
		}
	}

	return ListAns;
}

vector<string> generateParenthesis(int n) {

	vector<string> vecAns{ "()" };
	if (n == 1) return vecAns;

	set<string> setAns{ "()" };
	int nSize = 4;

	for (; n > 1; n--)
	{
		for (auto it = setAns.begin(); it != setAns.end(); it++)
		{
			string strTemp = *it;
			vecAns.push_back(strTemp.append("()"));
			strTemp = *it;
			vecAns.push_back(strTemp.insert(0, "()"));
			strTemp = *it;
			vecAns.push_back(strTemp.insert(0, "(").append(")"));
		}

		setAns.insert(vecAns.begin(), vecAns.end());
		for (auto it = setAns.begin(); it != setAns.end(); it++)
		{
			string strTemp = *it;
			if (strTemp.size() < nSize) setAns.erase(it++);
		}
		vecAns.clear();
		vecAns.insert(vecAns.begin(), setAns.begin(), setAns.end());

		nSize += 2;
	}

    return vecAns;
}

ListNode* swapPairs(ListNode* head) {

	if (head == NULL || head->next == NULL) return head;

	ListNode* node1 = new ListNode;
	ListNode* node2 = new ListNode;
	//ListNode* node3 = new ListNode;
	ListNode* nodeHead = head->next;

	node1 = head;
	node2 = node1->next;
	//node3 = node2->next;

	while (node2 != NULL)
	{
		node1->next = node2->next;
		node2->next = node1;

		if (node1->next == NULL) break;

		node1 = node1->next;
		node2 = node1->next;
	}

	return nodeHead;

}

ListNode* reverseKGroup(ListNode* head, int k) {
	if (k == 1) return head;

	ListNode* nodeTemp = new ListNode;
	nodeTemp->next = head;
	vector<ListNode*> vecNodes{};

	for (int i = 0; i < k; i++)
	{
		if (nodeTemp->next == NULL) return head;
		vecNodes.push_back(nodeTemp->next);
		nodeTemp = nodeTemp->next;
	}

	ListNode* nodeAns = new ListNode;
	nodeAns->next = nodeTemp;

	vecNodes[0]->next = nodeTemp->next;
	for (int i = 1; i < vecNodes.size(); i++)
	{
		vecNodes[i]->next = vecNodes[i - 1];
	}

	nodeTemp = vecNodes[0];
	ListNode* nodeLast = new ListNode;
	nodeLast = vecNodes[0];

	while (1)
	{
		vecNodes.clear();
		for (int i = 0; i < k; i++)
		{
			if (nodeTemp->next == nullptr) break;
			vecNodes.push_back(nodeTemp->next);
			nodeTemp = nodeTemp->next;
		}

		if (vecNodes.size() < k) break;

		vecNodes[0]->next = nodeTemp->next;
		for (int i = 1; i < vecNodes.size(); i++)
		{
			vecNodes[i]->next = vecNodes[i - 1];
		}
		nodeLast->next = vecNodes[k - 1];
		nodeLast = vecNodes[0];
		nodeTemp = vecNodes[0];
	}

	return nodeAns->next;
}

vector<int> findSubstring(string s, vector<string>& words) {

	set<string> setTemp(words.begin(), words.end());
	vector<string> vecTemp = words;
	string strTemp = s;
	set<int> setAns{};
	bool bNSkip = true;
	int nLen = words[0].size();

	for (auto it = setTemp.begin(); it != setTemp.end(); it++)
	{
		int i = strTemp.find(*it);
		while (i < strTemp.size())
		{
			strTemp = strTemp.substr(i + nLen);
			for (int j = 0; j < vecTemp.size(); )
			{
				if (vecTemp[j] == *it&&bNSkip)
				{
					bNSkip = false;
					vecTemp.erase(vecTemp.begin() + j, vecTemp.begin() + j + 1);
					continue;
				}

				if (vecTemp[j] == strTemp.substr(0, nLen))
				{
					vecTemp.erase(vecTemp.begin() + j, vecTemp.begin() + j + 1);
					j = 0;
					strTemp = strTemp.substr(nLen);
					continue;
				}

				j++;
			}

			if (!vecTemp.size())
				setAns.insert(i);

			strTemp = s;
			i = strTemp.find(*it, i + 1);
			bNSkip = true;
			vecTemp = words;
		}
	}

	return vector<int>(setAns.begin(), setAns.end());
}

void nextPermutation(vector<int>& nums) {

	for (auto it = nums.begin(); it != nums.end(); )
	{
		if (*it < *(++it)) break;
		if (it == nums.end() - 1)
		{
			sort(nums.begin(), nums.end());
			return;
		}
	}

	int nLen = nums.size();
	for (int i = nLen-1; i > 0; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (nums[i] > nums[j])
			{
				nums.insert(nums.begin() + j, nums.begin() + i, nums.end());
				nums.erase(nums.begin() + nLen, nums.end());
				sort(nums.begin() + j+1, nums.end());
				return;
			}
		}
	}

	return;
}

int findTarget(vector<int>& vec, int& nTarget, int nLeft, int nRight)
{
	if (nTarget<vec[nLeft] || nTarget>vec[nRight - 1]) return -1;
	int nIndex = (nLeft + nRight) / 2;
	int npL = nLeft, npR = nRight;

	while (vec[nIndex] != nTarget)
	{
		if ((nIndex != nLeft && vec[nIndex] > nTarget&&vec[nIndex - 1] < nTarget) ||
			(nIndex != nRight - 1 && vec[nIndex]<nTarget&&vec[nIndex + 1]>nTarget))
			return -1;

		if (vec[nIndex] < nTarget)
		{
			npL = nIndex;
			nIndex = (nIndex + npR) / 2;
		}
		else
		{
			npR = nIndex + 1;
			nIndex = (nIndex + npL) / 2;
		}
	}

	return nIndex;
}

int search(vector<int>& nums, int target) {

	int nLen = nums.size();
	if (nLen == 1) return nums[0] == target ? 0 : -1;

	int nBase = nLen / 2;
	if (nums[0] < nums[nLen - 1]) nBase = 0;
	else if (nums[nLen - 2] > nums[nLen - 1]) nBase = nLen - 1;
	else
	{
		while (nums[nBase] > nums[nBase - 1])
		{
			if (nums[nBase] > nums[0]) nBase = (nBase + nLen) / 2;
			else nBase = nBase / 2;
		}
	}

	if (nBase)
	{
		if (target<nums[nBase] || target>nums[nBase - 1]) return -1;
	}
	else
	{
		if (target<nums[0] || target>nums[nLen - 1]) return -1;
	}

	if (target <= nums[nLen - 1])
		return findTarget(nums, target, nBase, nLen);
	else
		return findTarget(nums, target, 0, nBase);
}

bool isValidSudoku(vector<vector<char>>& board) {

	vector<int> vecColumn(9, 0);
	vector<int> vecSquare(9, 0);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] != '.')
				if (count(board[i].begin(), board[i].end(), board[i][j]) > 1) return false;

			if (board[j][i] != '.')
				if (vecColumn[board[j][i] - '0']++) return false;

			if (board[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3] != '.')
				if (vecSquare[board[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3] - '0']++) return false;
		}

		vecColumn = vector<int>(9, 0);
		vecSquare = vector<int>(9, 0);
	}

	return true;
}

//vector<vector<int>> vecAns{};
//vector<int> vecTemp{};

//void backward(vector<int>& candidates, int target, int nPos)
//{
//	if (nPos >= candidates.size())
//		return;
//	if (!target)
//	{
//		vecAns.push_back(vecTemp);
//		return;
//	}
//
//	for (int i = nPos; i < candidates.size(); i++)
//	{
//		if (candidates[i] <= target)
//		{
//			vecTemp.push_back(candidates[i]);
//			backward(candidates, target - candidates[i], i + 1);
//			vecTemp.pop_back();
//		}
//	}
//}

//vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
//
//	sort(candidates.begin(), candidates.end());
//	for (auto it = candidates.begin(); it != candidates.end(); it++)
//	{
//		if (*it > target)
//		{
//			candidates.erase(it, candidates.end());
//			break;
//		}
//	}
//
//	backward(candidates, target, 0);
//
//	return vecAns;
//}

void quicksort(vector<int>& nums, int l, int h)
{
	if (l >= h) return;

	int pivot = nums[l];
	int i = l, j = h;

	while (i < j)
	{
		while (nums[j] >= pivot && j > i) { j--; }
		while (nums[i] <= pivot && j > i) { i++; }
		if (i < j) { swap(nums[i], nums[j]); }
	}

	swap(nums[l], nums[i]);
	quicksort(nums, l, i - 1);
	quicksort(nums, i + 1, h);
}

int firstMissingPositive(vector<int>& nums) {

	quicksort(nums, 0, nums.size() - 1);
	if (nums[nums.size() - 1] <= 0) return 1;

	int nZero = 0;
	if (nums[0] <= 0)
		for (int i = 0, j = nums.size() - 1; i <= j; )
		{
			nZero = (i + j) / 2;
			if (nums[nZero] <= 0 && nums[nZero + 1] > 0)
			{
				nums.erase(nums.begin(), nums.begin() + nZero + 1);
				break;
			}
			else if (nums[nZero] <= 0) i = nZero + 1;
			else j = nZero - 1;
		}

	// for(int i=0, j=nums.size()-1; i<=j; )
	// {
	//     int k=(i+j)/2;
	//     if(nums[k]==k+1) i = k+1;
	//     else if(k==0||nums[k-1]==k) return k+1;
	//     else j = k-1;
	// }
	for (int i = 0, j = 1; i < nums.size(); i++)
	{
		if (i&&nums[i] == nums[i - 1]) continue;
		if (nums[i] == j) j++;
		else return j;
	}

	return nums[nums.size() - 1] + 1;
}

int trap(vector<int>& height) {

	if (height.size() <= 2) return 0;

	multimap<int, int> mapIndex{};
	for (int i = 0; i < height.size(); i++)
	{
		mapIndex.insert({ height[i], i });
	}

	auto itTemp = mapIndex.end();
	auto itl = --itTemp, ith = itTemp;
	if (itTemp->second < (--itTemp)->second)
		ith--;
	else
		itl--;

	int nAns = 0;
	int nHeight = itl->first < ith->first ? itl->first : ith->first;
	for (int i = itl->second + 1; i < ith->second; i++)
	{
		nAns += nHeight - height[i];
	}

	while (itl->second > 0 || ith->second < height.size() - 1)
	{
		if(itl->second>0)
			for (itTemp = itl; itTemp != mapIndex.begin(); )
			{
				if ((--itTemp)->second < itl->second)
				{
					nHeight = itTemp->first;
					for (int i = itTemp->second + 1; i < itl->second; i++)
					{
						nAns += nHeight - height[i];
					}
					itl = itTemp;
					break;
				}
			}

		if(ith->second<height.size()-1)
			for (itTemp = ith; itTemp != mapIndex.begin(); )
			{
				if ((--itTemp)->second > ith->second)
				{
					nHeight = itTemp->first;
					for (int i = ith->second + 1; i < itTemp->second; i++)
					{
						nAns += nHeight - height[i];
					}
					ith = itTemp;
					break;
				}
			}
	}

	return nAns;
}

int nAns = 0;
set<int> setAns{};

void step(vector<int>& nums, int nPos)
{
	if (!nums[nPos])
		return;

	if (nums.size() - 1 - nPos <= nums[nPos])
	{
		nAns++;
		setAns.insert(nAns);
		nAns--;
		return;
	}

	for (int i = 1; i <= nums[nPos]; i++)
	{
		nAns++;
		step(nums, nPos + i);
		nAns--;
	}
}

int jump(vector<int>& nums) {

	if (nums.size() == 1) return 0;

	step(nums, 0);

	auto it = setAns.begin();
	return *it;

}

vector<int> spiralOrder(vector<vector<int>>& matrix) {
	int m = matrix.size()-1;
	int n = matrix[0].size()-1;

	int nDir = 0;
	int nRound = 0;
	int pnPos[2] = { 0,0 };
	vector<int> vecAns{};

	while (vecAns.size() < (m+1)*(n+1))
	{
		vecAns.push_back(matrix[pnPos[0]][pnPos[1]]);

		switch (nDir)
		{
		case 0:
			if (pnPos[1] == n - nRound)
			{
				nDir = 1;
				pnPos[0]++;
			}
			else
				pnPos[1]++;
			break;
		case 1:
			if (pnPos[0] == m - nRound)
			{
				nDir = 2;
				pnPos[1]--;
			}
			else
				pnPos[0]++;
			break;
		case 2:
			if (pnPos[1] == nRound)
			{
				nDir = 3;
				pnPos[0]--;
			}
			else
				pnPos[1]--;
			break;
		case 3:
			if (pnPos[0] == 1 + nRound)
			{
				nRound++;
				nDir = 0;
				pnPos[1]++;
			}
			else
				pnPos[0]--;
			break;
		}
	}

	return vecAns;
}

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
	if (intervals.size() == 0) return vector<vector<int>>{newInterval};

	for (auto it = intervals.begin(); it != intervals.end(); )
	{
		if (newInterval[0] > (*it)[1])
		{
			it++;
			continue;
		}
		if (newInterval[1] < (*it)[0])
		{
			intervals.insert(it, newInterval);
			return intervals;
		}
		(*it)[0] = min((*it)[0], newInterval[0]);
		for (auto iu = it; iu != intervals.end(); iu++)
		{
			if (newInterval[1] < (*(iu + 1))[0] || *iu == intervals.back())
			{
				(*it)[1] = max((*iu)[1], newInterval[1]);
				intervals.erase(it + 1, iu + 1);
				return intervals;
			}
		}
	}

	intervals.push_back(newInterval);
	return intervals;
}

string childPermutation(vector<int> v, int k)
{
	string strTemp = "";
	int nSize = v.size();
	if (nSize == 1)
	{
		strTemp.push_back(v[0] + '0');
		return strTemp;
	}

	int nIndex = 1;
	for (int i = 1; i < nSize; nIndex *= i++) {}

	strTemp.push_back(v[(k-1)/ nIndex] + '0');
	v.erase(v.begin() + (k - 1) / nIndex, v.begin() + (k - 1) / nIndex + 1);
	return strTemp + childPermutation(v, k-nIndex*((k-1)/nIndex));
}

string getPermutation(int n, int k) {
	vector<int> vec{};
	for (int i = 1; i <= n; i++)
	{
		vec.push_back(i);
	}

	return childPermutation(vec, k);
}

int uniquePaths(int m, int n) {
	if (m == 1 || n == 1) return 1;

	vector<int> vecAns(n, 1);
	for (int y = 2; y < m; y++)
	{
		for (int x = 0; x < n; x++)
		{
			for (auto it = vecAns.begin()+1 + x; it != vecAns.end(); it++)
			{
				vecAns[x] += *it;
			}
		}
	}

	for (auto i : vecAns)
	{
		vecAns[0] += i;
	}

	return vecAns[0];
}

bool bAns = false;
void backtrack(vector<vector<char>>& board, string& word, vector<vector<int>>& vecBoard,
	string& strTemp, int& m, int& n, int x, int y) {
	if (x<0 || y<0 || x>=m || y>=n || vecBoard[x][y] || bAns) return;
	if (strTemp.size() > word.size()) return;
	if (strTemp == word)
	{
		bAns = true;
		return;
	}

	strTemp.push_back(board[x][y]);
	vecBoard[x][y] = 1;
	backtrack(board, word, vecBoard, strTemp, m, n, x + 1, y);
	backtrack(board, word, vecBoard, strTemp, m, n, x, y + 1);
	backtrack(board, word, vecBoard, strTemp, m, n, x - 1, y);
	backtrack(board, word, vecBoard, strTemp, m, n, x, y - 1);
	strTemp.pop_back();
	vecBoard[x][y] = 0;
}

bool exist(vector<vector<char>>& board, string word) {
	int m = board.size(), n = board[0].size();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			string strTemp = "";
			vector<vector<int>> vecBoard(m, vector<int>(n, 0));
			backtrack(board, word, vecBoard, strTemp, m, n, i, j);
			if (bAns) return true;
		}
	}
	return false;
}

int largestRectangleArea(vector<int>& heights) {
	vector<int> h(heights);
	sort(h.begin(), h.end());
	int nAns = h[0] * h.size();
	for (int i = 0; i < heights.size(); i++)
	{
		if (heights[i] == h[0]) continue;
		int l = 0, r = 0;
		for (int x = i - 1, y = i + 1; x >= 0 || y < heights.size(); x--, y++)
		{
			if (x >= 0 && heights[x] >= heights[i])
				l++;
			else if (x >= 0 && heights[x] < heights[i])
				x = -1;

			if (y < heights.size() && heights[y] >= heights[i])
				r++;
			else if (y < heights.size() && heights[y] < heights[i])
				y = heights.size();
		}
		nAns = max(nAns, heights[i] * (l + r + 1));
	}
	return nAns;
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	int i = 0;
	while (n > 0)
	{
		int l = i, r = m;
		while (l < r)
		{
			i = (l + r) / 2;
			if (r == 1 && nums2[0] <= nums1[i])
				break;
			if (l == m - 1 && nums2[0] >= nums1[i])
			{
				i = m; break;
			}
			if (nums2[0] < nums1[i - 1])
				r = i;
			else if (nums2[0] > nums1[i])
				l = i + 1;
			else
				break;
		}
		if (l == r) i = l;
		nums1.pop_back();
		nums1.insert(nums1.begin() + i, nums2[0]);
		nums2.erase(nums2.begin(), nums2.begin() + 1);
		m++, n--;
	}
}

vector<vector<int>> vecAns{ {} };
vector<int> vecTemp{};
vector<bool> vecBool{};

void backtrack(vector<int>& nums, int i) {
	// if(vecTemp.size())
	//     vecAns.push_back(vecTemp);
	if (i >= nums.size())
		return;

	if (i&&nums[i] == nums[i - 1] && !vecBool[i - 1])
		return;
	vecTemp.push_back(nums[i]);
	vecBool[i] = true;
	vecAns.push_back(vecTemp);
	backtrack(nums, i + 1);
	vecTemp.pop_back();
	vecBool[i] = false;
	backtrack(nums, i + 1);
}

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	vecBool = vector<bool>(nums.size(), false);
	backtrack(nums, 0);
	// set<vector<int>> setAns(vecAns.begin(),vecAns.end());
	// vecAns = vector<vector<int>>(setAns.begin(), setAns.end());
	return vecAns;
}

vector<string> vecAnsstr{};
vector<string> vecStr{};

void backtrack(int i, int& n, string& s) {
	if (vecStr.size())
	{
		if (vecStr.back().size() > 3)
			return;
		if (vecStr.back().size() > 1 && vecStr.back()[0] == '0')
			return;
		if (vecStr.back().size() == 3)
		{
			if (vecStr.back()[0] >= '3')
				return;
			else if (vecStr.back()[1] >= '6')
				return;
			else if (vecStr.back()[2] >= '6')
				return;
		}
		if (vecStr.size() == 4)
		{
			string temp = vecStr[0];
			temp.push_back('.');
			temp.append(vecStr[1]);
			temp.push_back('.');
			temp.append(vecStr[2]);
			temp.push_back('.');
			temp.append(vecStr[3]);
			vecAnsstr.push_back(temp);
			return;
		}
	}

	if (vecStr.size() == 3)
	{
		if (n - i > 0)
		{
			vecStr.push_back(s.substr(i));
			backtrack(n, n, s);
			vecStr.pop_back();
		}
		else
			return;
	}
	else
		for (int j = 1; j <= 3; j++)
		{
			if (n - i - j >= 0)
			{
				vecStr.push_back(s.substr(i, j));
				backtrack(i + j, n, s);
				vecStr.pop_back();
			}
		}
}

vector<string> restoreIpAddresses(string s) {
	int len = s.size();
	if (len < 4 || len>12) return vecAnsstr;

	backtrack(0, len, s);
	return vecAnsstr;
}

int findRadius(vector<int>& houses, vector<int>& heaters) {
	int ans = 0;
	for (int i : houses)
	{
		auto it = lower_bound(heaters.begin(), heaters.end(), i);
		if (it == heaters.begin())
			ans = max(ans, *it - i);
		else if (it == heaters.end())
			ans = max(ans, i - *it);
		else
			ans = max(ans, min(*it - i, i - *(it - 1)));
	}
	return ans;
}

int maximalRectangle(vector<vector<char>>& matrix) {
	int ans = 0;
	int row = matrix.size();
	int col = matrix[0].size();

	for (int i = 0; i < row; i++)
	{
		vector<int> heights(col, 0);
		vector<int> vl(col, 0);
		vector<int> vr(col, 0);
		stack<int> st;

		for (int y = 0; y < col; y++)
		{
			for (int x = i; x >= 0 && matrix[x][y]; x--, heights[y]++) {}
		}

		for (int y = 0; y < col; y++)
		{
			while (st.size() && heights[st.top()] >= heights[y]) { st.pop(); }
			vl[y] = st.empty() ? -1 : st.top();
			st.push(y);
		}

		st = stack<int>();

		for (int y = col - 1; y >= 0; y--)
		{
			while (st.size() && heights[st.top()] >= heights[y]) { st.pop(); }
			vr[y] = st.empty() ? col : st.top();
			st.push(y);
		}

		for (int y = 0; y < col; y++)
		{
			ans = max(ans, (vr[y] - vl[y] - 1)*heights[y]);
		}
	}

	return ans;
}

vector<int> ansp;
set<int> setHistory;//history pair
set<int> setPath;//pointed justnow

void searchpath(vector<vector<int>>& edges, int i, int j) {
	if (ansp.size()) return;
	if (setHistory.count(i))
	{
		ansp = edges[i];
		return;
	}

	if(i||j)
		setHistory.insert(i);

	for (int index = 0; index < edges.size(); index++)
	{
		if (edges[index][0] == edges[i][j] && !setPath.count(edges[index][1]))
		{
			setPath.insert(edges[index][1]);
			searchpath(edges, index, 1);
			setPath.erase(edges[index][1]);
		}
		if (edges[index][1] == edges[i][j] && !setPath.count(edges[index][0]))
		{
			setPath.insert(edges[index][0]);
			searchpath(edges, index, 0);
			setPath.erase(edges[index][0]);
		}
	}
}
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
	setPath.insert(edges[0][0]);
	searchpath(edges, 0, 0);
	return ansp;
}

int subarraySum(vector<int>& nums, int k) {
	int total = accumulate(nums.begin(), nums.end(), 0);
	int sum = 0;
	int ans = 0;
	unordered_map<int, set<int>> mapVal{ {0,{-1}} };
	for (int i = 0; i < nums.size(); i++)
	{
		sum += nums[i];
		if (mapVal.count(sum))
			mapVal[sum].insert(i);
		else
			mapVal[sum] = set<int>{ i };
	}

	sum = 0;
	if (mapVal.count(total - sum - k))
	{
		for (auto it = mapVal[total - sum - k].begin(); it != mapVal[total - sum - k].end(); it++)
		{
			if (nums.size() - 1 - *it) ans++;
			else break;
		}
	}
	for (int n = nums.size() - 1; n >= 0; n--)
	{
		sum += nums[n];
		if (mapVal.count(total - sum - k))
		{
			for (auto it = mapVal[total - sum - k].begin(); it != mapVal[total - sum - k].end(); it++)
			{
				if (*it < n - 1) ans++;
				else break;
			}
		}
	}

	return ans;
}

bool submerge(string& s, int i, int total, vector<string>& wordDict) {
	int len = total - i;

	for (string str : wordDict)
	{
		int tmp = str.size();
		if (tmp > len) continue;

		if (str == s.substr(i, tmp))
			if (submerge(s, i + tmp, total, wordDict)) return true;
	}

	return false;
}

bool wordBreak(string s, vector<string>& wordDict) {
	return submerge(s, 0, s.size(), wordDict);
}

set<vector<int>> bad;
vector<vector<int>> ox;
bool bUseless = false;

void findgroup(vector<vector<char>>& board, int i, int j, int& row, int& col) {
	if (bUseless || i < 0 || j < 0 || i >= row || j >= col || board[i][j] == 'X') return;

	if (i == 0 || j == 0 || i == row - 1 || j == col - 1 || bad.count(vector<int>{i, j}))
	{
		for (auto v : ox)
		{
			bad.insert(v);
		}
		bUseless = true;
		ox.clear();
		return;
	}

	ox.push_back(vector<int>{i, j});

	findgroup(board, i + 1, j, row, col);
	findgroup(board, i - 1, j, row, col);
	findgroup(board, i, j + 1, row, col);
	findgroup(board, i, j - 1, row, col);
}

void solve(vector<vector<char>>& board) {
	int row = board.size();
	int col = board[0].size();

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == 'X') continue;

			findgroup(board, i, j, row, col);

			for (auto v : ox)
			{
				board[v[0]][v[1]] = 'X';
			}
			ox.clear();
			bUseless = false;
		}
	}
}

vector<vector<int>> pathland;

void find1island(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& island) {
	if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || !grid[i][j] || pathland[i][j]) return;

	island.push_back({ i,j });
	pathland[i][j] = 1;
	find1island(grid, i + 1, j, island);
	find1island(grid, i, j + 1, island);
	find1island(grid, i - 1, j, island);
	find1island(grid, i, j - 1, island);
}

bool inboundary(int row, int col, int i, int j) {
	return i >= 0 && j >= 0 && i < row&&j < col;
}

int shortestBridge(vector<vector<int>>& grid) {
	int row = grid.size(), col = grid[0].size();
	pathland = vector<vector<int>>(grid.size(), vector<int>(grid[0].size(), 0));
	vector<vector<int>> island1;

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (!grid[i][j]) continue;
			find1island(grid, i, j, island1);
			break;
		}
	}

	queue<vector<int>> q;
	queue<vector<int>> qNext;
	for (auto v : island1)
	{
		grid[v[0]][v[1]] = 2;
		q.push(v);
	}

	int ans = 0;
	while (q.size())
	{
		vector<int> v = q.front();
		q.pop();

		if (inboundary(row, col, v[0], v[1] + 1))
		{
			int i = (grid[v[0]][v[1] + 1]);
			if (i == 1) return ans;
			if (i == 0)
			{
				grid[v[0]][v[1] + 1] = 2;
				qNext.push({ v[0], v[1] + 1 });
			};
		}
		if (inboundary(row, col, v[0], v[1] - 1))
		{
			int i = (grid[v[0]][v[1] - 1]);
			if (i == 1) return ans;
			if (i == 0)
			{
				grid[v[0]][v[1] - 1] = 2;
				qNext.push({ v[0], v[1] - 1 });
			}
		}
		if (inboundary(row, col, v[0] + 1, v[1]))
		{
			int i = (grid[v[0] + 1][v[1]]);
			if (i == 1) return ans;
			if (i == 0)
			{
				grid[v[0] + 1][v[1]] = 2;
				qNext.push({ v[0] + 1, v[1] });
			}
		}
		if (inboundary(row, col, v[0] - 1, v[1]))
		{
			int i = (grid[v[0] - 1][v[1]]);
			if (i == 1) return ans;
			if (i == 0)
			{
				grid[v[0] - 1][v[1]] = 2;
				qNext.push({ v[0] - 1, v[1] });
			}
		}

		if (q.empty())
		{
			q = qNext;
			qNext = queue<vector<int>>();
			ans++;
		}
	}

	return ans;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

vector<vector<int>> sumpath;
vector<int> sumtmp;

void findpath(TreeNode* node, int& target, int sum) {
	if (!node) return;

	sumtmp.push_back(node->val);

	if (node->left == NULL && node->right == NULL)
	{
		if (sum + node->val == target) sumpath.push_back(sumtmp);
	}
	else
	{
		findpath(node->left, target, sum + node->val);
		findpath(node->left, target, sum + node->val);
	}

	sumtmp.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
	findpath(root, targetSum, 0);
	return sumpath;
}

int leastInterval(vector<char>& tasks, int n) {
	int len = tasks.size();
	vector<int> nums(26);
	for (char& ch : tasks) ++nums[ch - 'A'];
	sort(nums.begin(), nums.end(), greater<int>());

	int count = 1;
	while (count < 26 && nums[count] == nums[0]) count++;
	return max((n + 1)*(nums[0] - 1) + count, len);
}

string removeDuplicateLetters(string s) {
	vector<int> times(26, 0);
	for (const char& ch : s) ++times[ch - 'a'];

	stack<int> st;
	for (int i = 0; i < s.size(); ++i) {
		while (st.size() && s[st.top()] > s[i] && times[s[st.top()] - 'a'] > 1) {
			--times[s[st.top()] - 'a'];
			st.pop();
		}
		if (st.empty() || s[st.top()] < s[i] || times[s[i] - 'a'] == 1) st.push(i);
	}

	deque<int> tmp;
	while (st.size()) {
		tmp.push_front(st.top());
		st.pop();
	}
	string ans;
	for (const int& i : tmp) ans.push_back(s[i]);
	return ans;
}

string reverseWords(string s) {
	int ll = 0, lr = 0;
	while (s[ll] == ' ') ++ll;
	s.erase(0, ll);
	lr = ll = 0;

	int rr = s.size() - 1, rl;
	while (s[rr] == ' ') --rr;
	s.erase(rr + 1);
	rl = rr;

	while (lr < rl) {
		while (s[lr] != ' ') {
			++lr;
			if (lr > rl) break;
		}
		while (s[rl] != ' ') {
			--rl;
			if (rl < lr) break;
		}
		if (lr > rl) break;

		string sl = s.substr(ll, lr - ll);
		string sr = s.substr(rl + 1, rr - rl);

		s.erase(rl + 1, rr - rl);
		s.insert(rl + 1, sl);
		s.erase(ll, lr - ll);
		s.insert(ll, sr);

		int lenl = lr - ll, lenr = rr - rl;
		ll += lenr;
		rr -= lenl;

		int countr = 0;
		while (s[rr] == ' ') { --rr; ++countr; }
		if (countr > 1) s.erase(rr + 1, countr - 1);

		int countl = 0;
		while (s[ll] == ' ') { ++ll; ++countl; }
		if (countl > 1) s.erase(ll - countl, countl - 1);

		lr = ll, rl = rr;
	}

	return s;
}

int numberOfSubarrays(vector<int>& nums, int k) {
	vector<int> odds{ 1 };
	int cnt = 0, ans = 0;

	for (int& i : nums) {
		if (i % 2) {
			if (cnt >= k) ans += odds[cnt] * odds[cnt - k];
			odds.push_back(1);
			++cnt;
		}
		else ++odds[cnt];
	}

	if (!nums.back() % 2) ans += odds[cnt] * odds[cnt - k];
	return ans;
}

int main()
{
	set<int> s  { 1,3,5,7,2,43,9 };
	vector<int> v{ 1,3,4,4,5,2,1,3 };

	vector<int>::iterator it = find(v.begin(), v.end(), 11);

	int i = distance(v.end(), it);

	if (distance(v.end(), it))
	{
		bool bl;
	}
	
	map<int, string> m = { {1,"awd"}, {22, "d21"}, {3, "dd9"} };

	map<string, int> si = { {"aa", 1}, {"ee", 2},{"bb", 3} };

	m.insert({ 5,"dlk" });

	m[19] = "mmc";
	m[10] = "mmc";

	auto it2 = m.begin();

	auto it3 = si.find("kk");

	if (it3 == si.end())
	{
		cout << 5;
	}

	si.erase("aa");

	int qq = si.size();

	cout << it2->second;

	ListNode* list1 = new ListNode;
	list1->val = 1; list1->next = new ListNode;
	list1->next->val = 2; list1->next->next = new ListNode;
	list1->next->next->val = 3; list1->next->next->next = new ListNode;
	list1->next->next->next->val = 4; list1->next->next->next->next = new ListNode;
	list1->next->next->next->next->val = 5;

	//ListNode* lis = swapPairs(list1);
	//ListNode* lis = reverseKGroup(list1, 2);

	ListNode* list2 = new ListNode;
	list2->val = 1; list2->next = new ListNode;
	list2->next->val = 3; list2->next->next = new ListNode;
	list2->next->next->val = 4;

	for (auto it = v.begin(); it != v.end(); it++)
	{
		if (*it == 3 || *it == 5) { it = v.erase(it); it--; }
	}

	string str = "barfoofoobarthefoobarman";
	vector<string> words = { "bar","foo","the" };

	//vector<int> vecfind = findSubstring(str, words);

	vector<int> vecin = { 1,2,7,4,3,1 };

	nextPermutation(vecin);

	//mergeTwoLists(list1, list2);

	//generateParenthesis(3);

	vector<int> vecfind = { 6, 7, 8, 1, 2, 3, 4, 5 };
	
	//search(vecfind, 6);

	vector<vector<char>> board = { {'5', '3', '.', '.', '7', '.', '.', '.', '.'}, {'6', '.', '.', '1', '9', '5', '.', '.', '.'}, {'.', '9', '8', '.', '.', '.', '.', '6', '.'}, {'8', '.', '.', '.', '6', '.', '.', '.', '3'}, {'4', '.', '.', '8', '.', '3', '.', '.', '1'}, {'7', '.', '.', '.', '2', '.', '.', '.', '6'}, {'.', '6', '.', '.', '.', '.', '2', '8', '.'}, {'.', '.', '.', '4', '1', '9', '.', '.', '5'}, {'.', '.', '.', '.', '8', '.', '.', '7', '9'} };
	//isValidSudoku(board);

	vector<int> candidates{ 2,3,6,7 };
	for (auto it = candidates.begin(); it!=candidates.end(); it++)
	{
		if (*it > 6)
		{
			candidates.erase(it, candidates.end());
			break;
		}
	}

	candidates = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	//combinationSum2(candidates, 8);

	//quicksort(vecfind, 0, vecfind.size() - 1);

	vector<int> vecmis{ 0,2,2,4,0,1,0,1,3 };
	//firstMissingPositive(vecmis);

	vector<int> height{ 0,2,0 };
	//trap(height);

	string test1 = "23";
	string test2(3,'0');

	test1 = to_string(54)+ test2 + test1;

	int val = atoi(test1.c_str());

	vector<int> jump{ 1,2,1,1,1 };
	//step(jump, 0);

	string strst1 = "bet";
	string strst2 = "teb";

	sort(strst1.begin(), strst1.end());
	sort(strst2.begin(), strst2.end());

	vector<vector<int>> matrix{ {1,2,3,4},{5,6,7,8},{9,10,11,12} };
	//spiralOrder(matrix);

	vector<vector<int>> interval = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
	vector<int> newinter = { 4,8 };
	insert(interval, newinter);

	char ch = 5 + '0';

	//getPermutation(4, 9);

	//uniquePaths(3, 7);

	vector<vector<char>> vecboard = { {'a','b','c','e'}, {'s','f','c','s'},{'a','d','e','e'} };
	string word = "abcced";
	//exist(vecboard, word);

	//largestRectangleArea(v);

	time_t t = time(NULL);
	struct tm stime;
	localtime_s(&stime, &t);

	stime.tm_year+1900;
	stime.tm_mon+1;
	stime.tm_mday;
	stime.tm_hour;
	stime.tm_min;
	stime.tm_sec;

	string s5 = to_string(1);

	vector<int> vmerge1 = { 4,0,0,0,0,0 };
	vector<int> vmerge2 = { 1,2,3,5,6 };
	//merge(vmerge1, 1, vmerge2, 5);

	vector<int> numset{1,1,2,2};
	//subsetsWithDup(numset);

	//restoreIpAddresses("101023");

	deque<int> dq(5);
	queue<int> q(dq);

	list<int> l1 = { 1,2,3 };
	list<int> l2(5);

	stack<int> st(dq);

	priority_queue<int, vector<int>, less<int>> pq;

	vector<int> house{ 1,2,3,4 };
	vector<int> heater{ 2 };

	//int radius = findRadius(house, heater);

	//vector<vector<int>> rectan{ {1,0,1,0,0}, {1,0,1,1,1}, {1,1,1,1,1}, {1,0,0,1,0} };
	//maximalRectangle(rectan);


	vector<vector<int>> edges{ {9, 10}, { 5, 8 }, { 2, 6 }, { 1, 5 }, { 3, 8 }, { 4, 9 }, { 8, 10 }, { 4, 10 }, { 6, 8 }, { 7, 9 } };
	//findRedundantConnection(edges);

	vector<int> subarray{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

	//subarraySum(subarray, 0);

	vector<string> wordDict{ "leet", "code" };
	//wordBreak("leetcode", wordDict);

	vector<vector<char>> oxboard = {{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
	//solve(oxboard);

	vector<vector<int>> lake = { {0,1},{1,0} };

	//shortestBridge(lake);

	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);

	//pathSum(root, 3);

	//leastInterval(tasks, 36);

	//removeDuplicateLetters("bccab");

	//reverseWords("  Bob    Loves  Alice   ");

	vector<int> odds{ 1,1,2,1,1 };
	//numberOfSubarrays(odds, 3);

	// long long longnum;
	// cin >> longnum;

	int minusnum = -10;
	minusnum = minusnum / 0xFFFFFFFF;

	return 0;
}
