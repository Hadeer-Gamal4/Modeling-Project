#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

//------------>>>>          ICG         <<<<------------

class ICGCalculator {
public:
    // Constructor
    ICGCalculator() {}

    // Function to set parameters
    void setParameters(float a_val, float m_val, float xinitial_val, float n_val) {
        a = a_val;
        m = m_val;
        xinitial = xinitial_val;
        n = n_val;
        XI=xinitial;
        // Initializing the first index of x array
    }

    // Function to calculate and print r(n)
    void calculateICG() {
    	float test=XI,icg;
        for (int i = 0; i < n; ++i) {
            // Calculate x[i+1]
            icg = (a / test) ;
            while(icg>=m)
            {
            	icg-=m;
			}
            
            // Calculate r(n)
            double rn = icg / int(m);
            x[i]=rn;
            // Print r(n)
            cout <<fixed<<setprecision(3);
            cout << "r(" << i + 1 << ") = " << rn << std::endl;
            //to update the value each loob
            test=icg;
        }
    }

private:
    float a;          // Attribute 'a'
    float m;          // Attribute 'm'
    float xinitial;   // Attribute 'xinitial'
    float n;          // Attribute 'n'
    float XI;         
    float x[1000];    // Array to store x values, assuming a maximum size of 1000
};

//------------>>>>          KS TEST         <<<<------------

class kstest {
public:
    int n;

    void ks_test() {
        cout << "please enter number of data" << " :";
        cin >> n;
        double data[n];
        for (int i = 0; i < n; i++) {
            cout << "please enter data" << i << " :";
            cin >> data[i];
        }
        sort(data, data + n);
        double Dn;
        for (int i = 0; i < n; ++i) {
            double Fi = (double)(i) / n;
            double Dn_plus = (Fi - data[i]);
            double Dn_minus = (data[i] - Fi);
            Dn = max(Dn, max(Dn_plus, Dn_minus));
        }
        cout << Dn<<"\n";
        
            double testValue;
        std::cout << "Enter test value (0.10, 0.05, or 0.01): ";
        std::cin >> testValue;
        float dtest =sqrt(-.05*log(testValue/2))/sqrt(n);
        if(dtest>=testValue){
        	cout<<"accepted";
		}
		else{
			cout<<"not";
		}
    }
};

//------------>>>>          MRG         <<<<------------

void MRG(int terms, int a_terms, int mod, float x[], float a[])
{
    float term_arr[terms+1];

    for(int i=0; i < a_terms; i++)
    {
        term_arr[i] = x[i];
    }

    for(int i=0; i <= a_terms; i++)
    {
        term_arr[a_terms + i] = fmod(a[0]*term_arr[i] + a[1]*term_arr[i+1] + a[2]*term_arr[i+2], mod);
    }

    float rand_arr[terms+1];

    cout << "The values generated are: ";

    for(int x=0; x <= 2; x++)
    {
        rand_arr[x] = term_arr[x] / mod;

        cout << rand_arr[x] << " ";
    }

    for(int x=3; x <= terms; x++)
    {
        rand_arr[x] = term_arr[x] / mod;

        cout << rand_arr[x] << " ";

        if (rand_arr[x] < 0 || rand_arr[x] > 1)
        {
            cout << "Random values out of the range [0, 1]" << endl;
            cout << "Stopping the generation process..." << endl;

            return;
        }
    }

    cout << endl;
}

//------------>>>>          LFG         <<<<------------

class LFG {
public:
    int k, j;
    float m;
    int generate;
    float sum;

public:
    void lagged() {
        for (int i = 0; i < generate; i++)
        {
            sum = fmod((k + j), m); // Calculate a new value using LF
            
            if ( sum/m<0||sum/m > 1)
            {
                cout << "Random values out of the range [0, 1]" << endl;
                cout << "Stopping the generation process..." << endl;
                return;
			}
			else
            {
                cout << fixed << setprecision(2) << sum/m << " "<<endl; // cout the generated value
                k = j; // swap k and j for the next iteration
                j = sum;
            }
		    
		
       }
    } 
};

//------------>>>>          MSM         <<<<------------

typedef unsigned long long z;

 constexpr int max_size = 5000;

static auto numofDigits = [] (z startingNumber) -> int
{
string strNumber = to_string(startingNumber);

return strNumber.length();
};

static auto extractMiddle = [] (string sqrNumber , int sqrDigits , int digitNumber) -> int
{
    int index = (sqrDigits / 2) - (digitNumber / 2);
    
    int digits = digitNumber;
    string strResult;
    
    while (digits > 0)
    {
        strResult += sqrNumber[index++];
        digits--;
    }
    
    return stoi (strResult);
};
        
void middle_square(int numberofiterations, z startingNumber )
{
    
    if ((numofDigits(startingNumber)) % 2 != 0)
    {
        cout << "number of digits of initial number has to be even." << endl;
        return;
    }
    int numberofDigits = numofDigits(startingNumber);
    auto processed_number = startingNumber;
    string sqrStr , temp;
    
    int result;
    
    cout << "i" << "\t" << " Xi" << "\t" << "  X^2*i" << "\t\t" << " Ri" << endl;
    
    for (int i = 0 ; i <= numberofiterations ; i++)
    {
        z squared = processed_number*processed_number;
        sqrStr = to_string(squared);
        int sqrNumDigits = numofDigits(squared);
        if (sqrNumDigits < 2 * numberofDigits)
        {
            temp = to_string (squared);
            while (sqrNumDigits < 2 * numberofDigits)
            {
                temp.insert(0,1,'0');
                sqrNumDigits++;
            }
            
            
            
            result = extractMiddle(temp , sqrNumDigits , numberofDigits);
        }
        else
        {
            result = extractMiddle(sqrStr , sqrNumDigits , numberofDigits);
            
             temp = to_string(squared);
        }
      
        double r;
        r = static_cast<float>(result) / 10000;
        
        cout << i << "\t" << processed_number << "\t" << temp << "\t" << fixed << setprecision(4) << r << endl;
                
        processed_number = result;  

    }
    
}

int main() {
    int choice = 0;

    cout << "\t \t \t \t " << "\\ ^_^ /" << "\t \t \t \t " << "\\ ^_^ /" << endl << endl;

    cout << "-------------->>>>>> !Welcome to the Random Number Generator! <<<<<<-------------------" << endl << endl;

    cout << "What kind of RNG do u wanna use?" << endl << "Write the corresponding number of the wanted RNG." << endl;

    cout << "1) ICG" << endl
         << "2) KS Test" << endl
         << "3) MRG" << endl
         << "4) LFG" << endl
         << "5) MSM" << endl;

    cin >> choice;

    if(choice == 1)
    {
        // Declare an object of ICGCalculator
        ICGCalculator icg;

        // Ask user to enter parameters
        int a, m, xinitial, n;
        cout << "Enter value of a: ";
        cin >> a;
        cout << "Enter value of m: ";
        cin >> m;
        cout << "Enter value of xinitial: ";
        cin >> xinitial;
        cout << "Enter value of n: ";
        cin >> n;

        // Set parameters
        icg.setParameters(a, m, xinitial, n);

        // Calculate and print r(n)
        icg.calculateICG();

        cout << endl << endl << "\t\t\t\t\t" << "\\ ^_^ /" << endl << endl;
    }
    else if(choice == 2)
    {
        kstest obj;
        obj.ks_test();

        cout << endl << endl << "\t\t\t\t\t" << "\\ ^_^ /" << endl << endl;
    }
    else if(choice == 3)
    {
        int terms=0, mod=0, a_terms=0;

        cout << "Enter the number of terms: ";
        cin >> terms;

        cout << "Enter the mod: ";
        cin >> mod;

        cout << "Enter the number of multiplier terms: ";
        cin >> a_terms;

        float a[a_terms], x[a_terms];

        cout << "Enter the multipliers, make sure u enter " << a_terms << " multipliers: " << endl;
        for(int i=0; i < a_terms; i++)
        {
            cout << i+1 << ") ";
            cin >> a[i];
        }

        cout << "Enter the initial terms, make sure u enter " << a_terms << " terms: " << endl;
        for(int i=0; i < a_terms; i++)
        {
            cout << i+1 << ") ";
            cin >> x[i];
        }

        MRG(terms, a_terms, mod, x, a);

        cout << endl << endl << "\t\t\t\t\t" << "\\ ^_^ /" << endl << endl;
    }
    else if(choice == 4)
    {
        LFG lfg;

        cout << "How many numbers do you need?" << endl;
        cin >> lfg.generate;
        cout << "Please enter the first value: " << endl;
        cin >> lfg.k;
        cout << "Please enter the second value: " << endl;
        cin >> lfg.j;
        cout << "Please enter the modulus value: " << endl;
        cin >> lfg.m;

        cout << "Generated numbers: ";
        lfg.lagged();

        cout << endl << endl << "\t\t\t\t\t" << "\\ ^_^ /" << endl << endl;
    }
    else if(choice == 5)
    {
        int number;
        int iterations;  
    
        cout << "enter the number" << endl;
        cin >>number;
    
        cout << "number of iterations " << endl;
        cin >> iterations;
    
        middle_square(iterations , number);

        cout << endl << endl << "\t\t\t\t\t" << "\\ ^_^ /" << endl << endl;
    }
    else
    {
        cout << "You haven't entered the right response...... :(" << endl;
        cout << "Please re-run the program again and choose a number >BETWEEN< 1 and 5 :)" << endl;
        cout << "Have a great day" << endl;
    }

    return 0;
}