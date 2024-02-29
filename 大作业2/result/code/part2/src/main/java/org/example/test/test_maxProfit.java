package org.example.test;

import org.example.code.code;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * @program: part2
 * @description:
 * @author: CuiJieXiang_1023
 * @create: 2023-11-20 13:43
 **/
public class test_maxProfit {
    @Test
    public void test_maxProfit() {
        code c = new code();

        // 测试案例
        assertEquals(7, c.maxProfit(new int[]{7, 1, 5, 3, 6, 4}));
        assertEquals(0, c.maxProfit(new int[]{7, 6, 4, 3, 1}));
        assertEquals(4, c.maxProfit(new int[]{1, 2, 3, 4, 5}));
        assertEquals(0, c.maxProfit(new int[]{5, 4, 3, 2, 1}));
        assertEquals(0, c.maxProfit(new int[]{1}));
        assertEquals(0, c.maxProfit(new int[]{}));
    }
}
