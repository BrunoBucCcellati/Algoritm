#include <iostream>
#include "function.h"

using namespace std;

class Tochka
{
private:
    double x;
    double y;
public:
    Tochka(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    int GetX()
    {
        return x;
    }
    int GetY()
    {
        return y;
    }
};

class Otrezok
{
private:
    Tochka* start;
    Tochka* end;
    double M;
    double R;
    Otrezok* Next;
public:
    Otrezok(Tochka* _start, Tochka* _end)
    {
        start = _start;
        end = _end;
        M = abs((end->GetY() - start->GetY()) / (end->GetX() - start->GetX()));
        R = 0;
        Next = this;
    }
    void ChangeCharacteristic(double m)
    {
        R = characteristic(m, start->GetX(), end->GetX(), start->GetY(), end->GetY());
    }
    double GetCharacteristic()
    {
        return R;
    }
    void SetEnd(Tochka* _end)
    {
        end = _end;
        M = abs((end->GetY() - start->GetY()) / (end->GetX() - start->GetX()));
    }
    Tochka* GetEnd()
    {
        return end;
    }
    Tochka* GetStart()
    {
        return start;
    }
    Otrezok* GetNext()
    {
        return Next;
    }
    void SetNext(Otrezok* _Next)
    {
        Next = _Next;
    }
    double GetM()
    {
        return M;
    }
};

class Otrezki
{
private:
    Otrezok* Head;
    double Mmax;
    double m;
    double r;
    pair<double, double> x_Rmax;
    pair<double, double> y_Rmax;
public:
    Otrezki(Tochka* _start, Tochka* _end, double _r)
    {
        Head = new Otrezok(_start, _end);
        r = _r;
        if (Head->GetM() != 0)
        {
            Mmax = Head->GetM();
            m = r * Mmax;
        }
        else
        {
            Mmax = 0;
            m = 1;
        }
        Head->ChangeCharacteristic(m);
        x_Rmax.first = Head->GetStart()->GetX();
        x_Rmax.second = Head->GetEnd()->GetX();
        y_Rmax.first = Head->GetStart()->GetY();
        y_Rmax.second = Head->GetEnd()->GetY();
    }
    void Add(Tochka* tmp)
    {
        Otrezok* curr = Head;
        while (curr->GetEnd()->GetX() < tmp->GetX())
        {
            curr = curr->GetNext();
        }
        if (curr->GetEnd()->GetX() != tmp->GetX())
        {
            Otrezok* curr1 = new Otrezok(tmp, curr->GetEnd());
            curr->SetEnd(tmp);
            curr1->SetNext(curr->GetNext());
            curr->SetNext(curr1);
            //
            if (curr->GetM() >= curr1->GetM())
            {
                Mmax = curr->GetM();
                if (Mmax != 0)
                {
                    m = r * Mmax;
                }
                else
                {
                    m = 1;
                }
            }
            else
            {
                Mmax = curr1->GetM();
                if (Mmax != 0)
                {
                    m = r * Mmax;
                }
                else
                {
                    m = 1;
                }
            }
            //
            curr = Head->GetNext();
            while (curr != Head)
            {
                curr->ChangeCharacteristic(m);
                curr = curr->GetNext();
            }
            Head->ChangeCharacteristic(m);
            //
            double Rmax = curr->GetCharacteristic();
            curr = curr->GetNext();
            while (curr != Head)
            {
                if (curr->GetCharacteristic() > Rmax)
                {
                    Rmax = curr->GetCharacteristic();
                    x_Rmax.first = curr->GetStart()->GetX();
                    x_Rmax.second = curr->GetEnd()->GetX();
                    y_Rmax.first = curr->GetStart()->GetY();
                    y_Rmax.second = curr->GetEnd()->GetY();
                }
                curr = curr->GetNext();
            }
        }
    }
    double Getm()
    {
        return m;
    }
    pair <double, double> GetX_Rmax()
    {
        return x_Rmax;
    }
    pair <double, double> GetY_Rmax()
    {
        return y_Rmax;
    }
};

pair <double, double> Algoritm(double a, double b, double epsilon, double r)
{
    Tochka* A = new Tochka(a, y(a));
    Tochka* B = new Tochka(b, y(b));
    Otrezki interval = Otrezki(A, B, r);
    pair<double, double> pred_i_sled_shag;
    pred_i_sled_shag.first = a;
    pred_i_sled_shag.second = b;
    //
    pair <double, double> min_xy;
    while (abs(pred_i_sled_shag.second - pred_i_sled_shag.first) > epsilon)
    {
        min_xy.first = pred_i_sled_shag.second;
        min_xy.second = y(min_xy.first);
        pred_i_sled_shag.first = pred_i_sled_shag.second;
        pred_i_sled_shag.second = shag(interval.Getm(), interval.GetX_Rmax().first, interval.GetX_Rmax().second, interval.GetY_Rmax().first, interval.GetY_Rmax().second);
        interval.Add(new Tochka(pred_i_sled_shag.second, y(pred_i_sled_shag.second)));
    }
    return min_xy;
}

int main()
{
    double extrX = Algoritm(-10, 10, 0.01, 1).first;
    double extrY = Algoritm(-10, 10, 0.01, 1).second;
    cout << "Xmin = " << extrX << " " << "Ymin = " << extrY << endl;
}
