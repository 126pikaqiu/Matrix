//
// Created by asus on 2019/5/31.
//

#include "Bignum.h"

BigNum::BigNum(const int a) {
    len = 0;
    memset(cache,0, sizeof(cache));
    //convert to the number of 100 decimal
    int d = a;
    bool flag = false;
    if(a < 0){
        d = -a;
        flag = true;
    }
    while(d > MAXN){
        cache[len++] = d - (d / (MAXN + 1)) * (MAXN + 1);
        d = d / (MAXN + 1);
    }
    if(flag){
        cache[len++] = -d;
    }else{
        cache[len++] = d;
    }
}

BigNum::BigNum(const BigNum & bigNum): len(bigNum.len){
    memset(cache,0, sizeof(cache));
    for(int i = 0; i < len; i++)
        cache[i] = bigNum.cache[i];
}

BigNum::BigNum() {
    len = 1;
    memset(cache,0,sizeof(cache));
}

BigNum::BigNum(const char * s) {
    bool flag = false;
    int start = 0;
    if (s[0] == '-') {
        flag = true;
        start = 1;
    }
    const char *s1 = s + start;
    int t,k,index,l,i;
    memset(cache,0,sizeof(cache));
    l = strlen(s1);
    len = l / DLEN;
    if (l % DLEN)
        len++;
    index=0;
    for(i = l - 1; i >= 0; i -= DLEN)
    {
        t = 0;
        k = i - DLEN + 1;
        if(k<0)
            k=0;
        for(int j = k; j <= i;j++)
            t= t*10 + s1[j] -'0';
        cache[index++]=t;
    }
    if (flag) {
        cache[len - 1] = - cache[len - 1];
    }
}

/**
 * overloading the operator +. And there
 * is an improvement that when one of the
 * parameters is 0, the adding can work efficiently.
 * @param bigNum
 * @return
 */
const BigNum BigNum::operator+(const BigNum &bigNum) const {
    BigNum result(*this);
    int lenb = bigNum.len;
    int lena;
    if (bigNum.cache[0] == '0' && lenb == 1)
    {
        // the case bigNum is 0.
        return result;
    }
    if (cache[0] == '0' && len == 1)
    {
        // the case this is 0.
        strcpy(result.cache, bigNum.cache);
        return result;
    }
    // assign the larger length to the result's len.
    lena = len > lenb ? len : lenb;
    for(int j = 0 ; j < lena ; j++)
    {
        result.cache[j] +=bigNum.cache[j];
        if(result.cache[j] > MAXN)
        {
            result.cache[j + 1]++;
            result.cache[j] -= MAXN+1;
        }
    }
    // check if the result would carry.
    if(result.cache[lena] != 0)
        result.len = lena + 1;
    else
        result.len = lena;
    return result;
}

/**
 * overloading the operator -. If the value of
 * the highest bit is below 0, the result is below
 * 0.
 * @param bigNum
 * @return
 */
const BigNum BigNum::operator-(const BigNum &bigNum) const {
    BigNum left,right;
    bool flag; // the sign bit
    if(*this > bigNum){
        left = *this;
        right = bigNum;
        flag = false;
    }else{
        left = bigNum;
        right = *this;
        flag = true;
    }
    int big = left.len;
    for(int j = 0; j < big; j++ ){
        if(left.cache[j] < right.cache[j]){
            int i = j + 1;
            while (left.cache[j] == 0)
                j++;
            left.cache[j--] --;
            while (j > i)
                left.cache[j--] = MAXN;
            left.cache[i] += MAXN + 1 - right.cache[i];
        }else{
            left.cache[j] -= right.cache[j];
        }
    }
    while(left.cache[len - 1] == 0 && left.len > 1)
    {
        left.len--;
        big--;
    }
    if(flag)
        left.cache[big-1] = 0 - left.cache[big-1];
    return left;
}

/**
 * overloading the operator *.
 * @param T
 * @return
 */
const BigNum BigNum::operator*(const BigNum & bigNum) const {
    BigNum ret;
    int i,j,up;
    int temp,temp1;
    for(i = 0; i < len; i++){
        up = 0;
        for(j = 0; j < bigNum.len; j++){
            temp = cache[i] * bigNum.cache[j] + ret.cache[i + j] + up;
            if(temp > MAXN)
            {
                temp1 = temp - temp / (MAXN + 1) * (MAXN + 1);
                up = temp / (MAXN + 1);
                ret.cache[i + j] = temp1;
            }
            else
            {
                up = 0;
                ret.cache[i + j] = temp;
            }
        }
        if(up != 0)
            ret.cache[i + j] = up;
    }
    ret.len = i + j;
    while(ret.cache[ret.len - 1] == 0 && ret.len > 1)
        ret.len--;
    return ret;
}

bool BigNum::operator>(const BigNum & bigNum) const {
    int ln;
    if(len > bigNum.len)
        return true;
    else if(len == bigNum.len)
    {
        ln = len - 1;
        while(cache[ln] == bigNum.cache[ln] && ln >= 0)
            ln--;
        if(ln >= 0 && cache[ln] > bigNum.cache[ln])
            return true;
        else
            return false;
    }
    else
        return false;
}

ostream& operator<<(ostream& out,  const BigNum& b) {
    int i;
    cout << int(b.cache[b.len - 1]);
    for(i = b.len - 2 ; i >= 0 ; i--)
    {
        cout.width(DLEN);
        cout.fill('0');
        cout << int(b.cache[i]);
    }
    return out;
}