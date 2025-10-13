def count_zeros(n):
    """
    统计从1到n的整数中，数字0在十进制表示中出现的总次数
    
    参数:
    n: 整数，统计范围的上限
    
    返回:
    数字0出现的总次数
    """
    if n <= 0:
        return 0
    
    count = 0
    base = 1
    
    while base <= n:
        # 计算高位、当前位和低位
        high = n // (base * 10)
        cur = (n // base) % 10
        low = n % base
        
        if cur == 0:
            # 当前位为0的情况
            count += (high - 1) * base + (low + 1)
        else:
            # 当前位不为0的情况
            count += high * base
        
        base *= 10
    
    return count

# 测试函数
def test_count_zeros():
    """测试函数"""
    test_cases = [
        (10, 1),      # 1-10: 10(1个0)
        (100, 11),    # 1-100: 10,20,...,90,100(2个0) = 9+2=11
        (1000, 192),  # 已知结果
        (10000, 2893), # 已知结果
        (100000, 38894) # 题目要求的结果
    ]
    
    print("测试结果:")
    for n, expected in test_cases:
        result = count_zeros(n)
        status = "✓" if result == expected else "✗"
        print(f"1-{n}: 期望={expected}, 实际={result} {status}")

# 计算1到100000中0的出现次数
n = 100000
result = count_zeros(n)
print(f"\n从1到{n}的整数中，数字0出现的总次数为: {result}")

# 运行测试
test_count_zeros()