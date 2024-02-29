package org.example.code;

/**
 * @program: part2
 * @description:
 * @author: CuiJieXiang_1023
 * @create: 2023-11-20 12:18
 **/
public class code {

    public int findDuplicate(int[] nums) {
        // 初始化快慢指针
        int slow = nums[0];
        int fast = nums[0];

        // 快指针每次前进两步，慢指针每次前进一步，直到两指针相遇
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // 将慢指针重置为起始位置，并继续前进，直到与快指针相遇
        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        // 返回重复的整数
        return slow;
    }

    public int findOddOccurrence(int[] nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;  // 使用异或运算找到出现奇数次的数字
        }
        return result;
    }

    public int maxProfit(int[] prices) {
        int maxProfit = 0;

        for (int i = 1; i < prices.length; i++) {
            // 如果当前价格高于前一天的价格，说明可以获利，累加到总利润中
            if (prices[i] > prices[i - 1]) {
                maxProfit += prices[i] - prices[i - 1];
            }
        }

        return maxProfit;
    }
}
