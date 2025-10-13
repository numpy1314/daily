#include <stdio.h>
#include <time.h>

// 方法1：暴力统计法（用于验证）
long long count_zeros_brute_force(long long n) {
    long long count = 0;
    for (long long i = 1; i <= n; i++) {
        long long num = i;
        while (num > 0) {
            if (num % 10 == 0) {
                count++;
            }
            num /= 10;
        }
    }
    return count;
}

// 方法2：数学公式法（高效）
long long count_zeros_mathematical(long long n) {
    if (n <= 0) return 0;
    
    long long count = 0;
    long long base = 1;
    
    while (base <= n) {
        // 计算高位、当前位和低位
        long long high = n / (base * 10);
        long long cur = (n / base) % 10;
        long long low = n % base;
        
        if (cur == 0) {
            // 当前位为0的情况
            count += (high - 1) * base + (low + 1);
        } else {
            // 当前位不为0的情况
            count += high * base;
        }
        
        base *= 10;
    }
    
    return count;
}

// 测试函数
void run_tests() {
    struct TestCase {
        long long n;
        long long expected;
    };
    
    struct TestCase test_cases[] = {
        {10, 1},      // 1-10: 10(1个0)
        {100, 11},    // 1-100: 10,20,...,90,100(2个0) = 9+2=11
        {202, 22},    // 手动计算验证
        {1000, 192},  // 已知结果
        {10000, 2893}, // 已知结果
        {100000, 38894} // 题目要求的结果
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf("测试结果:\n");
    printf("n\t\t期望\t\t数学法\t\t暴力法\t\t状态\n");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < num_tests; i++) {
        long long n = test_cases[i].n;
        long long expected = test_cases[i].expected;
        
        long long math_result = count_zeros_mathematical(n);
        long long brute_result = count_zeros_brute_force(n);
        
        char* math_status = (math_result == expected) ? "✓" : "✗";
        char* brute_status = (brute_result == expected) ? "✓" : "✗";
        
        printf("%-10lld\t%-10lld\t%-10lld\t%-10lld\t数学:%s 暴力:%s\n", 
               n, expected, math_result, brute_result, math_status, brute_status);
    }
}

// 性能测试函数
void performance_test() {
    printf("\n性能测试:\n");
    printf("n\t\t数学法(ms)\t暴力法(ms)\t结果\n");
    printf("------------------------------------------------\n");
    
    long long test_values[] = {1000, 10000, 100000, 1000000};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        long long n = test_values[i];
        
        // 测试数学方法
        clock_t start = clock();
        long long math_result = count_zeros_mathematical(n);
        clock_t math_time = clock() - start;
        
        // 测试暴力方法（对于大n可能很慢，所以限制测试范围）
        clock_t brute_time = 0;
        long long brute_result = 0;
        if (n <= 100000) {  // 限制暴力测试的范围
            start = clock();
            brute_result = count_zeros_brute_force(n);
            brute_time = clock() - start;
        }
        
        printf("%-10lld\t%-10.2f\t", n, ((double)math_time * 1000 / CLOCKS_PER_SEC));
        
        if (n <= 100000) {
            printf("%-10.2f\t", ((double)brute_time * 1000 / CLOCKS_PER_SEC));
            printf("数学:%lld 暴力:%lld %s\n", math_result, brute_result, 
                   (math_result == brute_result) ? "✓" : "✗");
        } else {
            printf("跳过暴力\t数学:%lld\n", math_result);
        }
    }
}

// 特定值详细分析
void detailed_analysis(long long n) {
    printf("\n详细分析 n = %lld:\n", n);
    
    long long math_result = count_zeros_mathematical(n);
    long long brute_result = 0;
    
    if (n <= 1000000) {  // 限制范围避免过长时间运行
        brute_result = count_zeros_brute_force(n);
    }
    
    printf("数学公式法结果: %lld\n", math_result);
    
    if (n <= 1000000) {
        printf("暴力统计法结果: %lld\n", brute_result);
        printf("结果一致性: %s\n", (math_result == brute_result) ? "✓ 一致" : "✗ 不一致");
    }
    
    // 显示一些包含0的数字示例
    printf("\n包含0的数字示例:\n");
    int count = 0;
    for (long long i = 1; i <= n && count < 10; i++) {
        long long num = i;
        int has_zero = 0;
        while (num > 0) {
            if (num % 10 == 0) {
                has_zero = 1;
                break;
            }
            num /= 10;
        }
        if (has_zero) {
            printf("%lld ", i);
            count++;
        }
    }
    printf("...\n");
}

int main() {
    printf("数字0出现次数统计测试程序\n");
    printf("==========================\n");
    
    // 运行基本测试
    run_tests();
    
    // 运行性能测试
    performance_test();
    
    // 对特定值进行详细分析
    detailed_analysis(100000);
    
    // 用户输入测试
    printf("\n自定义测试 (输入0退出):\n");
    long long n;
    while (1) {
        printf("请输入n: ");
        if (scanf("%lld", &n) != 1 || n <= 0) {
            break;
        }
        
        clock_t start = clock();
        long long result = count_zeros_mathematical(n);
        clock_t time_taken = clock() - start;
        
        printf("1到%lld中数字0出现次数: %lld\n", n, result);
        printf("计算时间: %.4f 毫秒\n\n", ((double)time_taken * 1000 / CLOCKS_PER_SEC));
    }
    
    printf("程序结束\n");
    return 0;
}