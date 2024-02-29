package org.example.test;


import org.example.code.code;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * @program: part2
 * @description:
 * @author: CuiJieXiang_1023
 * @create: 2023-11-20 12:43
 **/
public class test_findDuplicate {

    @Test
    public void testAdd() {
        code c = new code();
        // 测试案例
        assertEquals(2, c.findDuplicate(new int[]{1, 3, 4, 2, 2}));
        assertEquals(3, c.findDuplicate(new int[]{5, 6, 3, 2, 4, 1, 7, 3}));
        assertEquals(3, c.findDuplicate(new int[]{5, 6, 3, 2, 4, 1, 8, 7, 3}));
        assertEquals(1, c.findDuplicate(new int[]{1, 1, 2, 3, 4, 5}));
        assertEquals(4, c.findDuplicate(new int[]{1, 2, 3, 4, 4, 5}));
        assertEquals(9, c.findDuplicate(new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10}));
        assertEquals(5, c.findDuplicate(new int[]{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}));
        assertEquals(3, c.findDuplicate(new int[]{1, 2, 3, 3, 4, 5, 6, 7, 8, 9}));
        assertEquals(1, c.findDuplicate(new int[]{1, 1}));
    }
}
