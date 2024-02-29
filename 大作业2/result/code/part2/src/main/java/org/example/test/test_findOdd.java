package org.example.test;


import org.example.code.code;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * @program: part2
 * @description:
 * @author: CuiJieXiang_1023
 * @create: 2023-11-20 13:41
 **/
public class test_findOdd {


    @Test
    public void test_findOddOccurrence() {
        code c = new code();

        // 测试案例
        assertEquals(8, c.findOddOccurrence(new int[]{2, 3, 5, 7, 8, 7, 3, 2, 5, 9, 9}));
        assertEquals(3, c.findOddOccurrence(new int[]{3, 5, 4, 8, 3, 5, 3, 8, 4}));
        assertEquals(5, c.findOddOccurrence(new int[]{2, 3, 2, 3, 4, 4, 5}));
        assertEquals(1, c.findOddOccurrence(new int[]{1}));
        assertEquals(1, c.findOddOccurrence(new int[]{1, 2, 2}));
        assertEquals(0, c.findOddOccurrence(new int[]{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8}));
        assertEquals(7, c.findOddOccurrence(new int[]{6, 7, 8, 6, 8}));
        assertEquals(100, c.findOddOccurrence(new int[]{100, 200, 300, 400, 500, 200, 300, 400, 500}));
        assertEquals(9, c.findOddOccurrence(new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8}));
    }
}
