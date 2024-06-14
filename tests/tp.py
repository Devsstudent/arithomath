# Aucun n'import ne doit être fait dans ce fichier


def nombre_entier(n: int) -> str:
    return ("S" * n + "0")


def S(n: str) -> str:
    return f'S{n}'


def addition(a: str, b: str) -> str:
    count = a.count('S')
    count += b.count('S')
    return ("S" * count + "0")


def multiplication(a: str, b: str) -> str:
    count = a.count('S')
    count *= b.count('S')
    return ("S" * count + "0")


def facto_ite(n: int) -> int:
    if (n == 0) :
        return 1
    i = 0
    res = n;
    while n > 1 :
        res *= (n - 1)
        n -= 1
    return res


def facto_rec(n: int) -> int:
    if n == 0:
        return 1
    if (n <= 1) :
        return  1
    return facto_rec(n - 1) * n


def fibo_rec(n: int) -> int:
    if (n == 0):
        return 0
    if (n <= 1):
        return 1
    return fibo_rec(n - 1) + fibo_rec(n - 2)


def fibo_ite(n: int) -> int:
    fn2 = 0
    fn1 = 1
    for _ in range(n) :
        f_n = fn2 + fn1
        fn2 = fn1
        fn1 = f_n
    return fn2

def golden_phi(n: int) -> int:
    return (fibo_rec(n + 1) / fibo_rec(n));

def sqrt5(n: int) -> int:
    return 2 * golden_phi(n) - 1

def pow(a: float, n: int) -> float:
    p = 0
    res = 1
    while (p < n) :
        res *= a
        p += 1
    return res
