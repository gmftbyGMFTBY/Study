#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "./Biginteger.h"         //Load the .h file

using namespace std;

Biginteger::Biginteger()
{
    sign = true;
    base = 5;
    length = 1;
    memset(data,0,sizeof(data));
}

Biginteger::Biginteger(const Biginteger& given)
{
    memset(data,0,sizeof(data));
    sign = given.sign;
    base = given.base;
    length = given.length;
    for(int i = 0;i < length;i++) data[i] = given.data[i];
}

Biginteger::Biginteger(int given,int Cbase)
{
    memset(data,0,sizeof(data));
    if(given < 0) sign = false,given = 0 - given;
    else sign = true;
    base = Cbase;
    length = 0;
    long long BASE = pow(10,base);
    while(given > BASE)
    {
        data[length++] = given % BASE;
        given /= BASE;
    }
    data[length++] = given;
}

Biginteger::Biginteger(long long given,int Cbase)
{
    memset(data,0,sizeof(data));
    if(given < 0) sign = false,given = 0 - given;
    else sign = true;
    base = Cbase;
    length = 0;
    long long BASE = pow(10,base);
    while(given > BASE)
    {
        data[length++] = given % BASE;
        given /= BASE;
    }
    data[length++] = given;
}

Biginteger::Biginteger(string given,int Cbase)
{
    try
    {
        for(int i = 0;i < given.length();i++)
        {
            if((given[i] >= 48 && given[i] <= 57) || given[0] == '-') continue;
            else throw Error_Con_Big();
        }
        base= Cbase;
        length = 0;
        if(given[0] != '-') sign = true;
        else sign = false;
        int length_given = given.length();
        long long sum = 0;
        long long fack_base = 1;
        long long BASE = pow(10,base);
        for(int i = length_given - 1;i >= 0;i--)
        {
            if(i == 0 && given[i] == '-') break;
            else
            {
                if(fack_base == BASE)
                {
                    i++;
                    data[length++] = sum;
                    fack_base = 1;
                    sum = 0;
                }
                else
                {
                    sum += (int(given[i]) - 48)*fack_base;
                    fack_base *= 10;
                }
            }
        }
        if(sum)
        {
            length++;
            data[length - 1] = sum;
        }
        else if(sum == 0 && length == 0) data[length++] = 0;   //In order to escape the case which the Biginteger is 0.
    }
    catch(Error_Con_Big e)
    {
        cout << "String can not convert to Biginteger!" << endl;
    }
}

void Biginteger::print()
{
    length_digit = get_length_digit();      //Renew the length_digit
    for(int i = 0;i < 80;i++) cout << '#' ;
    cout << endl;
    cout << "Base:" << base << endl;
    cout << "Length:" << length << endl;
    cout << "Length_Digit:" << length_digit << endl;        //The Length of the data is not need for my users.
    cout << "Data:" << endl;
    if(!sign) cout << '-';          // negative number!
    for(int i = length - 1;i >= 0;i--)
    {
        if(i == length - 1) cout << data[i];
        else
        {
            int digit = 0;
            long long t = data[i];
            while(t > 0) digit ++,t /= 10;
            for(int j = 1;j <= (base - digit);j++) cout << '0';
            if(data[i]) cout << data[i];  //Prepare not print 0 again
        }
    }
    cout << endl;
    for(int i = 0;i < 80;i++) cout << '#' ;
    cout << endl;
}

//All the memset function in Overload set is just for safe.
void Biginteger::set(const Biginteger& given)
{
    memset(data,0,sizeof(data));
    sign = given.sign;
    base = given.base;
    length = given.length;
    for(int i = 0;i < length;i++) data[i] = given.data[i];
}

void Biginteger::set(string value,int Cbase)
{
    this->base = Cbase;   //In order not to throw error in set() function
    Biginteger result(value,Cbase);
    *this = result;
}

void Biginteger::set(int given,int Cbase)
{
    memset(data,0,sizeof(data));
    if(given < 0) sign = false;
    else sign = true;
    base = Cbase;
    length = 1;
    data[0] = given;
}

void Biginteger::set(long long given,int Cbase)
{
    memset(data,0,sizeof(data));
    if(given < 0) sign = false;
    else sign = true;
    base = Cbase;
    length = 1;
    data[0] = given;
}

//This function only measure the 0(Biginteger) else wrongs may come!
void Biginteger::set_base(int given)
{
    try
    {
        if(!(this->length == 1 && this->data[0] == 0)) throw Error_Diff_Base(8);
        base = given;
    }
    catch(Error_Diff_Base e)
    {
        e.print();
    }
}

void Biginteger::change_sign()
{
    if(sign == true) sign = false;
    else sign = true;
}

int Biginteger::get_length_digit() const
{
    int key = 1;        //The last digits must not be the 0,it must be at least the 1
    int comp = 10;
    while(comp <= data[length - 1])
    {
        key += 1;
        comp *= 10;
    }
    if(length == 0) return key;
    else return key + base*(length - 1);
}

//Base functions
void Biginteger::Add(const Biginteger& value1,const Biginteger& value2,Biginteger& result) const
{
    long long BASE = pow(10,base);
    int max_length = max(value1.length , value2.length);
    long long sum = 0;        //We have rule that the base from 5 to 8
    int carry = 0;
    result.length = max_length;
    for(int i = 0;i < max_length;i++)
    {
        sum = value1.data[i] + value2.data[i] + carry;
        if(sum >= BASE)
        {
            sum -= BASE;
            carry += 1;
        }
        else carry = 0;
        result.data[i] = sum;
    }
    if(carry) result.data[++result.length] = 1;
}

void Biginteger::Sub(const Biginteger& value1,const Biginteger& value2,Biginteger& result) const
{
    long long BASE = pow(10,base);
    int max_length = max(value1.length , value2.length);
    int borrow = 0;
    result.length = max_length;
    for(int i = 0;i < max_length;i++)
    {
        if( (value1.data[i] > value2.data[i]) || ((value1.data[i] == value2.data[i]) && borrow == 0) )
        {
            result.data[i] = value1.data[i] - value2.data[i] - borrow;
            borrow = 0;
        }
        else
        {
            result.data[i] = BASE + value1.data[i] - value2.data[i] - borrow;
            borrow = 1;
        }
    }
    //At least the result.length is 1.
    while( (result.data[result.length - 1] == 0 ) && result.length>1)
    {
        result.length--;
    }
}

int Biginteger::Compare(const Biginteger& value1,const Biginteger& value2) const    //1 > 2 :return 1 / 1 < 2 :return -1 / 1 = 2 :return 0
{
    int length1 = value1.get_length_digit();
    int length2 = value2.get_length_digit();
    if(value1.sign && value2.sign)
    {
        if(length1 > length2) return 1;
        else if(length2 < length2) return -1;
        else
        {
            for(int i = length1 - 1;i >= 0;i--)
            {
                if(value1.data[i] > value2.data[i]) return 1;
                else if(value1.data[i] < value2.data[i]) return -1;
            }
            return 0;
        }
    }
    else if(value1.sign && !value2.sign) return 1;
    else if(!value1.sign && value2.sign) return -1;
    else
    {
        if(length1 > length2) return -1;
        else if(length1 < length2) return 1;
        else
        {
            for(int i = length1 - 1;i >= 0;i--)
            {
                if(value1.data[i] > value2.data[i]) return -1;
                else if(value1.data[i] < value2.data[i]) return 1;
            }
            return 0;
        }
    }
}

int Biginteger::Compare(const Biginteger& value1,int value2) const
{
    Biginteger f(value2,value1.base);
    return Biginteger::Compare(value1,f);
}

int Biginteger::CompareNoSign(const Biginteger& value1,const Biginteger& value2) const
{
    int length1 = value1.get_length_digit();
    int length2 = value2.get_length_digit();
    if(length1 > length2) return 1;
    else if(length1 < length2) return -1;
    else
    {
        for(int i = value1.length - 1;i >= 0;i--)
        {
            if(value1.data[i] > value2.data[i]) return 1;
            else if(value1.data[i] < value2.data[i]) return -1;
        }
        return 0;
    }
}

//Overload Base function
Biginteger Biginteger::operator+(const Biginteger& value) const
{
    try
    {
        if(this->base != value.base) throw Error_Diff_Base(1);
        Biginteger result(0,this->base);
        if(sign == value.sign)
        {
            result.set_sign(sign);
            Biginteger::Add(*this , value , result);
        }
        else
        {
            if(Biginteger::CompareNoSign(*this , value) >= 0)
            {
                Biginteger::Sub(*this , value , result);
                result.set_sign(sign);
            }
            else
            {
                Biginteger::Sub(value , *this , result);
                result.set_sign(value.sign);
            }
        }
        result.base = base;
        return result;
    }
    catch(Error_Diff_Base e)
    {
        e.print();
        return Biginteger();
    }
}

Biginteger Biginteger::operator-(const Biginteger& value) const 
{
    try
    {
        if(this->base != value.base) throw Error_Diff_Base(2);
        Biginteger result(0,this->base);
        if(sign != value.sign) 
        {
            Biginteger::Add(*this , value , result);
            result.set_sign(sign);
        }
        else
        {
            if(Biginteger::CompareNoSign(*this , value) >= 0)
            {
                Biginteger::Sub(*this , value , result);
                result.sign = sign;
            }
            else
            {
                Biginteger::Sub(value , *this , result);
                if(sign) result.sign = false;
                else result.sign = true;
            }
        }
        result.base = base;
        return result;
    }
    catch(Error_Diff_Base e)
    {
        e.print();
        return Biginteger();
    }
}

void Biginteger::Mul(const Biginteger& value1,const Biginteger& value2,Biginteger& result) const
{
    long long BASE = pow(10,base);
    long long sum = 0;      // Save the result ith digit the number.
    long long carry = 0;
    result.length = value1.length + value2.length - 1;
    /*
       i foreach:The result foreach in data.
       j foreach:The value2 foreach in data.
       i-j foreach:The value1 foreach in data.
     */
    for(int i = 0;i < result.length;i++)
    {
        sum = carry;     //Get the last digit(As for result) carry.
        carry = 0;       //Clear the last digit(As for result) carry.
        for(int j = 0;j < value2.length;j++)
        {
            /*
               Next row of the coding to sure that:
               We can get the value1 and value2 number to create
               the ith number of the result data.
             */
            if((i - j) >= 0 && ((i - j) < value1.length))
            {
                long long mul = value1.data[i-j];
                mul *= value2.data[j];
                carry += mul / BASE;
                sum += mul % BASE;
            }
        }
        carry += sum / BASE;
        sum = sum % BASE;
        result.data[i] = sum;
    }
    if(carry)
    {
        result.length ++;
        result.data[result.length - 1] = carry;
    }
}

Biginteger Biginteger::operator*(const Biginteger& value) const 
{
    try
    {
        if(this->base != value.base) throw Error_Diff_Base(3);
        Biginteger result(0,this->base);
        Biginteger::Mul(*this,value,result);
        if(this->sign == value.sign) result.sign = true;
        else result.sign = false;
        return result;
    }
    catch(Error_Diff_Base e)
    {
        e.print();
        return Biginteger();
    }
}

Biginteger Biginteger::operator=(const Biginteger& value)
{
    try
    {
        if(this->base != value.base) throw Error_Diff_Base(6);
        memset(data,0,sizeof(data));
        this->sign = value.sign;
        this->base = value.base;
        this->length = value.length;
        for(int i = value.length - 1;i >= 0;i--) this->data[i] = value.data[i];
        return *this;    //This code try to make sure a = b = c
    }
    catch(Error_Diff_Base e)
    {
        e.print();
        return Biginteger();
    }
}

/*In order to make it easy,i use base 5 Biginteger number to calculate
  When I finish all the work i will add some base choice into the function.
 */
void Biginteger::Div(const Biginteger& value1,const Biginteger& value2,Biginteger& quotient, Biginteger& remainder) const
{
    Biginteger BASE(10,value1.base);
    Biginteger q(0,this->base);             //Save to add quotient
    Biginteger result1(value1);     //Not to change value1
    Biginteger result2(value2);     //Not to change value2
    while(Biginteger::CompareNoSign(result1,value2) >= 0)
    {
        int pos = 0;
        Biginteger help = value2;  //Save the pre status of result2
        result2 = value2;
        while(Biginteger::CompareNoSign(help,result1) < 0)
        {
            result2 = help;
            help = result2 * BASE;
            pos ++;
        }
        int sub = 0;
        while(Biginteger::CompareNoSign(result1,result2) >= 0)
        {
            result1 = result1 - result2;
            sub ++;
        }
        Biginteger w(sub,value1.base);
        pos --;
        while(pos > 0)
        {
            w = w * BASE;
            pos --;
        }
        q = q + w;
    }
    quotient = q;
    remainder = result1;
}

Biginteger Biginteger::operator/(const Biginteger& value1) const
{
    try
    {
        if(this->base != value1.base) throw Error_Diff_Base(4);
        Biginteger quotient(0,this->base);
        Biginteger remainder(0,this->base);
        Biginteger p(*this);
        Biginteger w(value1);   //Const not to change the value1
        p.sign = w.sign = true;
        Biginteger::Div(p,w,quotient,remainder);
        if(this->sign == value1.sign) quotient.sign = true;
        else quotient.sign = false;
        return quotient;
    }
    catch(Error_Diff_Base e)
    {
        e.print();
        return Biginteger();
    }
}

Biginteger Biginteger::operator%(const Biginteger& value) const
{
    try
    {
        if(this->base != value.base) throw Error_Diff_Base(5);
        Biginteger a(0,this->base);
        Biginteger b(0,this->base);
        Biginteger::Div(*this,value,a,b);
        return b;
    }
    catch(Error_Diff_Base e)
    {
        e.print();
        return Biginteger();
    }
}

void Biginteger::Pow(const Biginteger& value1,int value2,Biginteger& result) const
{
    Biginteger BASE(value1);
    while(value2 != 0)
    {
        if(value2 & 1) result = result * BASE;
        BASE = BASE * BASE;
        value2 >>= 1;
    }
}

Biginteger Biginteger::operator^(const int value) const
{
    try
    {
        cout << "Hello " << endl;
        if(value < 0) throw Error_Neg_Pow();
        else if(value == 0) return Biginteger(1,this->base);
        else
        {
            Biginteger result(1,this->base);
            if(value & 1) result.sign = this->sign;
            else result.sign = true;
            Biginteger::Pow(*this,value,result);
            return result;
        }
    }
    catch(Error_Neg_Pow e)
    {
        e.print();
        return Biginteger();
    }
}

//Friend function for Biginteger Class
Biginteger Quick_P_M(Biginteger& value1,int value2,Biginteger& mod)
{
    try
    {
        if(value1.base != mod.base) throw Error_Diff_Base(7);
        Biginteger result(1,value1.base);
        Biginteger BASE(value1 % mod);
        while(value2 != 0)
        {
            if(value2 & 1)
            {
                result = (result * BASE) % mod;
            }
            value2 >>= 1;
            BASE = (BASE * BASE) % mod;
        }
        return result;
    }
    catch(Error_Diff_Base e)
    {
        e.print();
        return Biginteger();
    }
}

Biginteger Quick_P_M(Biginteger& value1,long long value2,Biginteger& mod)
{
    try
    {
        if(value1.base != mod.base) throw Error_Diff_Base(7);
        Biginteger result(1,value1.base);
        Biginteger BASE(value1 % mod);
        while(value2 != 0)
        {
            if(value2 & 1)
            {
                result = (result * BASE) % mod;
            }
            value2 >>= 1;
            BASE = (BASE * BASE) % mod;
        }
        return result;
    }
    catch(Error_Diff_Base e)
    {
        e.print();
        return Biginteger();
    }
}

Biginteger Quick_P_M(Biginteger& value1,Biginteger& value2,Biginteger& mod)
{
    try
    {
        if(value1.base != mod.base) throw Error_Diff_Base(7);
        Biginteger result(1,value1.base);
        Biginteger BASE(value1 % mod);
        Biginteger two(2,value1.base);
        while(!(value2.length == 1 && value2.data[0] == 0))
        {
            if(value2.data[0] & 1)
            {
                result = (result * BASE) % mod;
            }
            value2 = value2 / two;
            BASE = (BASE * BASE) % mod;
        }
        return result;
    }
    catch(Error_Diff_Base e)
    {
        e.print();
        return Biginteger();
    }
}

bool Biginteger::operator==(const Biginteger& a) const
{
    if(this->length != a.length) return false;
    for(int i = a.length;i >= 0;i--)
    {
        if(this->data[i] != a.data[i]) return false;
    }
    return true;
}

//////Friend Fucntion for the API - Begin to Define!
/*
   The Witness number counts 11 , Enough for the test for me.
   As for the Miller-Rabin Algorithm , 20 times test for prime
   can make the number is prime which possible is in 0.9968287
   Which I think can be used to judge the Prime.
*/
//True - Prime / False - Unprime
bool Miller_Rabin(Biginteger& x)
{ 
    int prime[20]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};
    int pow = 0;        //  The pow of the Biginteger is int can solve most of the cases
    Biginteger two(2,x.base);
    Biginteger one(1,x.base);
    Biginteger y(0,x.base);
    Biginteger x_m_1 = x - one;    // X - 1 
    Biginteger b = x_m_1;
    while(!(b.data[0] & 1))
    {
        pow ++;
        b = b / two;
    }
    for(int i = 0;i < 20;i++)
    {
        Biginteger test(prime[i],x.base);
        test = Quick_P_M(test , b , x);
        for(int i = 1;i <= pow;i++)
        {
            y = Quick_P_M(test , 2 , x);
            if((y.length == 1 && y.data[0] == 1) && one.Compare(test , one) != 0 && one.Compare(test , x_m_1) != 0)
                return false;
            test = y;
        }
        if(!(test.length == 1 && test.data[0] == 1)) return false;     //Fermat test is not satisfay.
    }
    return true;
}


//RAND_MAX is 2**31-1 ,which is enough for my rule for Base(2-9)

//Create the digit of the Random Biginteger Prime
Biginteger Random_Prime(int digit,int base)
{
    int BASE = pow(10,base);
    int length = ceil(digit * 1.0 / base);
    int lost_digit = digit % base;
    int LOST_BASE;
    if(lost_digit != 0) LOST_BASE = pow(10,lost_digit);
    else LOST_BASE = BASE;

    srand(time(NULL));
    Biginteger ans(0,base);
    ans.length = length;
    ans.sign = true;

    //Create a possible number which is odd.
    for(int i = 0;i < length - 1 ;i++)
    {
        ans.data[i] = rand() % BASE;
        if(i == 0 && (ans.data[0] % 2 == 0)) ans.data[0] += 1;
    }
    ans.data[length - 1] = rand() % LOST_BASE;
    if(ans.length == 1 && (ans.data[0] % 2 == 0)) ans.data[0] += 1;
    //If the ans can not be made sure once , try to search around odd number.
    if(ans.length == 1 && ans.data[0] == 1) ans.data[0] = 3;   //Miller-Rabin!
    Biginteger Ptwo(2,base);
    while(true)
    {
        if(Miller_Rabin(ans)) return ans;
        else ans = ans + Ptwo;   //After search.
    }
}

Biginteger Extend_GCD(Biginteger a,Biginteger b,Biginteger& x,Biginteger& y)
{
    if(b == Biginteger(0,b.base))
    {
        x = Biginteger(1,x.base);
        y = Biginteger(0,x.base);
        return a;
    }
    Biginteger xp(0,a.base);
    Biginteger yp(0,a.base);
    //cout << "a: " << a;
    //cout << "b: " << b;
    Biginteger t = Extend_GCD(b , a % b , xp , yp);
    x = yp;
    y = xp - (a / b) * yp;
    //cout <<"x: " <<x;
    //cout <<"y: "<<xp <<" - " << '('<<a<<" / "<<b<<')' <<'*'<<yp<<" = "<< y;
    return t;    //Return the GCD
}

void Create_Key(int digit1,int digit2,int base,Biginteger& Module,Biginteger& Public,Biginteger& Private)
{
    clock_t begin = clock();
    Biginteger p = Random_Prime(digit1,base);
    Biginteger q = Random_Prime(digit2,base);
    clock_t end = clock();
    cout << "Time: "<< (end - begin)/CLOCKS_PER_SEC << 's' << endl;
    cout << "Create two Big Prime Successfully!" << endl;
    cout << "First:" << endl << p;
    cout << "Second:" << endl << q;
    Biginteger one(1,base);
    Module = p * q;    //Public Module
    Biginteger Euler = (p - one) * (q - one);

    Public = Biginteger(65537,base);
    Biginteger x(0,base);
    Biginteger y(0,base);
    Extend_GCD(Public , Euler , x , y);
    Private = x;
    if(Private.sign == false) Private = Euler + Private;  //Create the Positive Number!
    cout << Euler;
}

/*
RSA:
    Encoding: 0 1 2
        0 - The Text wait to encoding
        1 - The Public Key to Encoding
        2 - The Public Module
    Decoding: 0 1 2
        0 - The Text had been encoded
        1 - The Private Key to Decoding
        2 - The Public Module
 */

Biginteger Encoding(Biginteger& text,Biginteger& PublicK,Biginteger& M)
{
    Biginteger result(0,text.base);
    result = Quick_P_M(text , PublicK , M);
    return result;
}

Biginteger Decoding(Biginteger& text,Biginteger& PrivateK,Biginteger& M)
{
    Biginteger result(0,text.base);
    result = Quick_P_M(text , PrivateK , M);
    return result;
}

///End Define for the API
