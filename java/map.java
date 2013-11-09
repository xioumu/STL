public static Map<BigInteger, BigInteger> dic;
public static BigInteger gao(BigInteger n) {
    if (dic.containsKey(n) == false) {
        dic.put(n, res3);
    }
    return dic.get(n);
}
public static void main(String[] args) {
    dic = new HashMap();
    dic.clear();
    gao(x);
}
