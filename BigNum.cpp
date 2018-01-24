#include <iostream>
#include <vector>
#include <sstream>
#define BASE 10
using namespace std;
//TO DO Include Negative numbers as Well
class BigNum
{
private:
    std::vector<int> value;
    int sign;
    BigNum(vector<int> a)
    {
        value = a;
    }

    vector<int> getVector()
    {
        return value;
    }
public:
    BigNum(string data)
    {
        
        
        for (int i = data.size() - 1; i >= 0 ; --i)
        {
            
            char a = data.at(i);
            int temp = stoi(&(a));
            
            value.push_back(temp);
        }
    }


    
    string getStringValue()
    {
        string temp;
        for (int i = value.size() - 1; i >= 0; --i)
        {            
            string temp_str;
            stringstream temp_strm;
            temp_strm << value[i];
            temp_strm >> temp_str;
            temp.append(temp_str);

        }

        return temp;
    }


    BigNum operator +(BigNum b)
    {
        std::vector<int> solution, vector_b;
        vector_b = b.getVector();
        
        int carry = 0, digit, sum, size_greater, size_smaller, size_this = value.size(), size_b = vector_b.size(),num1 ,num2;
        size_greater = (size_this < size_b)?size_b:size_this;
        size_smaller = (size_this < size_b)?size_this:size_b;
        bool isCarry;
        for (int i = 0; i < size_greater || isCarry ; ++i)
        {
            num1 = ((i < size_this)?value[i]:0);
            num2 = ((i < size_b)?vector_b[i]:0);
            
            sum = num1 + num2 + carry;
           
            digit = sum % BASE;
            carry = sum / BASE;

            isCarry = (carry > 0);
            
            solution.push_back(digit);           
        }
        
        BigNum result(solution);
        return result;

    }
    
    BigNum operator*(int v)
    {
       int carry = 0, digit, sum = 0, product = 0;
       std::vector<int> solution;
       bool isCarry;
       for (int i = 0; i < (int)value.size() || isCarry; ++i)
       {
           
            product = value[i] * v;
            sum = product + carry;
            
            digit = sum % BASE;
            carry = sum / BASE;

            solution.push_back(digit);
            isCarry = (0 < carry);
       }
       
       BigNum result(solution);
       return result;
    }
    
    //TO DO: Update to include operation on 2 negative numbers
    bool operator<(BigNum b)
    {
        vector<int> value2 = b.getVector();
        if(value.size() == value2.size())
        {
            for (int i = value.size() - 1; 0 <= i ; --i)
            {
                if (value[i] != value2[i])
                {
                    return (value[i] < value2[i]);
                }
            }

        }

        return (value.size() < value2.size());
    }      
    BigNum operator-(BigNum b)
    {


        std::vector<int> value2 = b.getVector(), solution;
        int carry = 0, diff, digit;
        bool isCarry;
        for (int i = 0; i < value.size() || isCarry; ++i) 
        {
            isCarry = false;
            diff = value[i] - carry - ((i < value2.size())?value2[i]:0);
            carry = 0;

            if(diff < 0)
            {
                diff = diff + BASE;
                carry = 1;
                isCarry = true;
            }
           
            solution.push_back(diff);
        }

        return solution;

    }

    BigNum operator*(BigNum b)
    {
        BigNum solution("0"), temp2("0");
        int carry = 0, digit, multiplier, product;
        std::vector<int> v1 = value, v2 = b.getVector(), line1;
        size_t size_a = value.size(), size_b = b.getVector.size();
        
        for (int i = 0; i < (int)size_b; ++i)
        {
            multiplier = v2[i];
            
            temp = v1*multiplier;

            solution = solution + temp;
        }
        /*
        for (int i = 0; i < v1.size(); ++i)
        {
            std::vector<int> line2;
            multiplier = v1[i];
            for (int j = 0 ; j < v2.size() ; j++)
            {
                 
                product = multiplier*v2[j] + carry;
                digit = product % 10;
                carry = product / 10;
                
                line2.push_back(digit);
                
            }

            BigNum a(line2);
            solution = solution + a;
        }
        */
        return solution;

    }

};

int main(int argc, char const *argv[])
{
    BigNum a("2222222"), b("7"), c("0");
    c = a - b;
    cout << c.getStringValue() << endl;    
    cout << (2222222 - 7) << endl;     
    return 0;
}