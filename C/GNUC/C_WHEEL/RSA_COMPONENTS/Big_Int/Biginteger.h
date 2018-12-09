#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
/*
   Something I really need to declare here:
        1.The Biginteger saved int the array which named data,and I save it from 0 to length with the order small digit to high digit.
        2.I rule that when we don't set the base,the Biginteger's base is 5.
        3.I code something to make sure that two Bigintegers with different base can not do some math job,which i think is also the correct thing and way to build this class safely.
        4.The length_digit is only use for we to know the real length of the Biginteger,When I use the Biginteger to calculate it is useless.
        5.Base function:
        I build the base function which I rule that the value1 is more than value2.
        6.Base function has no moving for the *this,so we can use it as static function.
        7.From coding this project,i have knew that we can visit the same class object's private things.
        8.I am so tired to make more overload operator function for intor long long type!
        9.As for the Error Class,I surely can add the coding in that to update my programms , but it also no need,only when i try to do this job as my C++ homework!
        10.As for the two different numbers calculate,I rule that it is illeagle , but actually I return a Biginteger(Base:5 Data:0) to my users.Which I thnk can be a Warning message to users to change the base.
        11.As for the Error_Diff_Base Class , I rule that :
            1:Add Error.
            2.Sub Error.
            3.Mul Error.
           All this setting is all for debugger to make sure where are the wrongs.
        12.Set_base Function is dangerous,so don't try to change the Biginteger's base when it is not 0.
        13.As for the Div , In order to quickly get the quotient and the remainder,I try to Overload the % and / to use one Div function to get two result(Quotient and remainder).
        14.Carefully,In the Div function,I don't care about the two numbers who is bigger,value1 persents the dividend,value2 presents divisor.
        15.Print function and the Overload Function of cin and cout are the different things:
           Print function show the details of the Biginteger number,such as the
           Base , digits , Data
           But the cin , cout only print the data of the Biginteger number.Which only give the standout format of the Class Biginteger for the test.
           But I get some Question in here , The Overload cin and cout only in the class can be friend?
        16.For the lower speed of the division and mod and Quick_Pow_Mod function , I can only think about the fast algorithm for QPM function but it still lower when the number is so big such more than 4000 digit than python(I want to read the Code of the Python),and this Question also happened on DIvision and mod function.
        17.In order to keep the calculator is correct,the base is from 2 - 9,no longer than 10,the data is based on long long , it may overflow!
        18.The Construct function was ruled to must have the base!
 */

/*
   Error Class:
       1.Different Base Error
       2.Negative Pow Error
       3.String COnvert Error
 */
class Error_Con_Big{};
class Error_Diff_Base{
    private:
        int message;
    public:
        Error_Diff_Base(int a):message(a){};
        void print()
        {
            string mes;
            if(message == 1) mes = "Add";
            else if(message == 2) mes = "Sub";
            else if(message == 3) mes = "Mul";
            else if(message == 4) mes = "Div";
            else if(message == 5) mes = "Mod";
            else if(message == 6)
            {
                cout << "A = B But A.base != B.base!" << endl;
                return ;
            }
            else if(message == 7) mes = "Quick Pow Mod";
            else if(message == 8)
            {
                cout << "Try to change the Biginteger which is not zero" << endl;
                cout << "To the another Base.Warning!" << endl;
                return ;
            }
            cout << "Try to " << mes << " two different numbers!" << endl;
        }
};

class Error_Neg_Pow
{
    public:
        void print()
        {
            cout << "You try to pow the number with a negative number" << endl;
            cout << "Which won't get the Integer!" << endl;
        }
};

/*
   Error Define End!
 */
const int Volume = 205;        //Calulate that base(5):20000 / base(8):12500
class Biginteger
{
    private:
        bool sign;      //Sign : + | -
        int base;       //Define the base of the number - 1e5 / 100000 - Suggest 1e5 to 1e10
        int length;     //Define the length of the number
        int length_digit;       //Define the digit number of the Biginteger
        long long data[Volume];       //array to save all the digists
    public:
        //Create function
        Biginteger();
        Biginteger(const Biginteger&);
        Biginteger(int,int);
        Biginteger(long long,int);
        Biginteger(string,int);
        //Base operator
        void Add(const Biginteger&,const Biginteger&,Biginteger&) const;
        void Sub(const Biginteger&,const Biginteger&,Biginteger&) const;
        void Mul(const Biginteger&,const Biginteger&,Biginteger&) const;
        void Div(const Biginteger&,const Biginteger&,Biginteger&,Biginteger&) const;
        void Pow(const Biginteger&,int,Biginteger&)const;
        int Compare(const Biginteger&,const Biginteger&) const;      //True:a >= b / False:b > a
        int Compare(const Biginteger&,int) const;
        int CompareNoSign(const Biginteger&,const Biginteger&) const;
        //Overload Base function
        Biginteger operator+(const Biginteger&) const;
        Biginteger operator-(const Biginteger&) const;
        Biginteger operator*(const Biginteger&) const;
        Biginteger operator/(const Biginteger&) const;
        Biginteger operator=(const Biginteger&);    //Use set function
        Biginteger operator^(const int) const;
        Biginteger operator%(const Biginteger&) const;
        bool operator==(const Biginteger&) const;
    	friend ostream& operator << (ostream& out,Biginteger& p)
    	{
 	        if(!p.sign) out << '-';          // negative number!
	        for(int i = p.length - 1;i >= 0;i--)
    	    {
                if(i == p.length - 1) out << p.data[i];
                else
                {
            	    int digit = 0;
                    long long t = p.data[i];
                    while(t > 0) digit ++,t /= 10;
                    for(int j = 1;j <= (p.base - digit);j++) out << '0';
                    if(p.data[i]) out << p.data[i];  //Prepare not print 0 again
                }
            }
            cout << endl;
            return out;
        }
        friend istream& operator >> (istream& in,Biginteger& p)
        {
            cout << "Ready to Create the Biginteger number with the int or long long or string!" << endl;
            string a;
            cout << "Base:";
            int Cbase;
            in >> Cbase;
            cout << "Data: ";
            in >> a;
            p.set(a,Cbase);
            return in;
        }
        friend Biginteger Quick_P_M(Biginteger&,int,Biginteger&);        //Quick pow mod Algorithm
        friend Biginteger Quick_P_M(Biginteger&,long long,Biginteger&);        //Quick pow mod Algorithm
        friend Biginteger Quick_P_M(Biginteger&,Biginteger&,Biginteger&);        //Quick pow mod Algorithm
        friend bool Miller_Rabin(Biginteger&);
        friend Biginteger Random_Prime(int,int);
        friend Biginteger Extend_GCD(Biginteger,Biginteger,Biginteger&,Biginteger&);
        //Print the Biginteger for Debug or necessary Uses
        friend void Create_Key(int,int,int,Biginteger&,Biginteger&,Biginteger&);
        friend Biginteger Encoding(Biginteger&,Biginteger&,Biginteger&);
        friend Biginteger Decoding(Biginteger&,Biginteger&,Biginteger&);
        void print();        //Use the get_length_digit function
        //Set and Get
        void set(string,int);
        void set(const Biginteger&);
        void set(int,int);
        void set(long long,int);
        inline void set_sign(bool a)
        {
            sign = a;
        }
        void set_base(int);   //int rule from 5 to 8
        void set_length(int l)    //Warning:This function is dangerous,use it that make sure your code is correct!
        {
            length = l;
        }
        void change_sign();   //Change the Biginteger's sign
        inline int get_base()
        {
            return base;
        }
        inline bool get_sign()
        {
            return sign;
        }
        inline int get_length_data()
        {
            return length;
        }
        int get_length_digit() const;
        //Function for changing base
};
