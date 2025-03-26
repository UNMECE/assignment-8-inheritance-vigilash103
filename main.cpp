#include <iostream>
#include <string>  
#include <cmath>
#include <memory>
#include <vector>

#define E0 8.85e-12
#define M_PI 3.14159265358979323846 
#define permeability 1.26e-6

class Field 
{
    protected:
        double *value;
    public:
        Field(){value = new double [3]; value[0] = 0; value[1] = 0; value[2] = 0;}
        Field(double nx, double ny, double nz) {value = new double [3]; value[0] = nx; value[1] = ny; value[2] = nz;}
        ~Field(){delete [] value;}

        void printMagnitude()
        {
            std::cout << "Magnitude: " << *value << std::endl;
        }
};

class ElectricField : public Field
{
    private:
        std::unique_ptr<double> E;
    public:
        ElectricField(): Field(){}
        ElectricField(double x, double y, double z) : Field(x, y, z) {}
        ~ElectricField(){}

        void calEF(double Q, double r)
        {
            E = std::make_unique<double>(Q/(4*M_PI*pow(r,2)*E0));
            std::cout << "Electric Field: " << *E << std::endl;
        }

        double getEF()
        {
            return *E;
        }
};

class MagneticField : public Field
{
    private:
        std::unique_ptr<double> M;
    public:
        MagneticField(): Field(){}
        MagneticField(double x, double y, double z) : Field(mx, my, mz) {}
        ~MagneticField(){}

        double getMF()
        {
            return *M;
        }

        void calMF(double I, double r)
        {
            M = std::make_unique<double>((I*2*M_PI*r)/permeability);
            std::cout << "Magnetic Field: " << *M << std::endl;
        }
};

int main()
{
    ElectricField e1(0, 1e5, 1e3);
    MagneticField m1(0, 1e5, 1e3);

    double Q = 1e-5;
    double r = 1e-6;
    double I = 1e-2;

    e1.calEF(Q, r);
    m1.calMF(I, r);

    std::cout << "Electric Field at a certain distance " << r << "is: " << e1.getEF() << std::endl;
    std::cout << "Magnetic Field at a certain distance " << r << "is: " << m1.getMF() << std::endl;

    ElectricField e2(0, 2e5, 6e3);
    ElectricField e3(0, 3e5, 9e3);
    ElectricField eSum = e2 + e3;
    std::cout << "Electric Field Sum: " << eSum << std::endl;

    return 0;
}