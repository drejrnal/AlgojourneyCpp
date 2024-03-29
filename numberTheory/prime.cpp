//
// Created by luoxiYun on 2021/3/28.
//

/*常见结论：
 * (1) 把合数n表示成p * q的形式时，一个数总是小于等于sqrt(n),另一个数总是大于sqrt(n)
 * (2) 任何一个合数均能被分解为质数的连乘积
 */

/*
 * 对给定的整数n进行素因子分解时，从2到sqrt(n) 从2开始，如果n能被2整除，则n不断除以2，直到不能被2整除；
 * 然后从3开始，以此类推。如果碰到合数，因为此时的n已经是该合数的素因子最大限度相除以后的状态，因此该合数不可能整除n，
 * 因此最后分解的结果全部是素数
 */

/*
 * 埃拉托色尼素数筛选法
 *  bool isPrime[n] 算法结束后，将1~n 是否为素数的情况存放在该数组中
 */
