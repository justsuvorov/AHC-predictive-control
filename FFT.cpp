#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//Êëàññ êîìïëåêñíûõ ÷èñåë
class Complex
{
private:
    double _re, _im;
public:
    Complex() {
        double x, y; //Конструктор комплексного числа
        x = 0;
        y = 0;//
        _re = x; _im = y;
    }

    Complex(double r, double i) {//Конструктор комплексного числа
        _re = r; _im = i;
    }
    Complex(double r) { //
        _re = r; _im = 0;
    }

    //Действительная часть
    double Real() {
        return _re;
    }
    //Мнимая часть
    double Imag() {
        return _im;
    }
    //Модуль комплексного числа
    double Modul() {

        return sqrt(_re * _re + _im * _im);
    }
    //Сопряженная мнимая часть
    double Imconj() {
        return -_im;
    }
    //Аргумент комплексного числа
    double Argument()
    {
        return atan2(_im, _re);
    }
    //Возвездение в степень
    Complex Power(int n) {
        return Complex(pow(Modul(), n) * cos(n * Argument()), pow(Modul(), n) * sin(n * Argument()));
    }
    double  RePower(int n) {
        return pow(Modul(), n) * cos(n * Argument());
    }
    double  ImPower(int n) {
        return pow(Modul(), n) * sin(n * Argument());
    }
};


//Деление
Complex Division(Complex p1, Complex p2) {
    double re, im;
    re = (p1.Real() * p2.Real() + p1.Imag() * p2.Imag()) / (pow(p2.Real(), 2) + pow(p2.Imag(), 2));
    im = (p1.Imag() * p2.Real() - p1.Real() * p2.Imag()) / (pow(p2.Real(), 2) + pow(p2.Imag(), 2));
    return Complex(re, im);
}
//Сложение
Complex Add(Complex p1, Complex p2) {
    double re, im;
    re = p1.Real() + p2.Real();
    im = p1.Imag() + p2.Imag();
    return Complex(re, im);
}
// Разность
Complex Difference(Complex p1, Complex p2) {
    double re, im;
    re = p1.Real() - p2.Real();
    im = p1.Imag() - p2.Imag();
    return Complex(re, im);
}
// Умножение
Complex Cross(Complex p1, Complex p2) {
    double re, im;
    re = p1.Real() * p2.Real() - p1.Imag() * p2.Imag();
    im = p1.Real() * p2.Imag() + p1.Imag() * p2.Real();
    return Complex(re, im);
}

//Функция ускорения
float acceleration (float t){
return 0.103485 * cos(0.0389469*t) + 0.075664 * cos(0.172788 * t) + 0.0589298  * cos(0.306619 * t) + 2.1091 * cos(0.372153 * t) + 1.54287  * cos(0.463448 * t) + 1.07723 * cos(0.554742 * t) + 0.852001 * cos(0.617826 * t) + 0.563521 * cos(0.743301 * t) +  0.406525 * cos(0.868839 * t) + 0.345055 * cos(0.955735 * t) ;

}

Complex Exponenta (int m, int k, int n) {
	double omega;
	omega = 2 * 3.14 * m * k / (n /2 );
	return Difference(Complex(cos(omega)),Complex(0,-sin(omega)));
}

Complex filtered_data(int n, Complex c_k[], int t) {
	Complex result;
	result = Complex();
		 
		for (int k = 0; k < n; k++) {
		result = Add (result, Cross(c_k[k], Exponenta(-1*t, k, n)));
		}
		
	return 	Division(result,Complex(n));
	
}

int main() {
	srand(time(NULL));
	float sample_time;
	sample_time = 0.1; // Dремя дискретизации
	int n = 128; //Samples Number
	float data[n];   //Массив данных с датчика
	float time ;  //Период
	time = n * sample_time; 
	float result;
	//Массив данных с датчика
	for (int i = 0; i < n; i++ ) {
			
		result = acceleration (i * sample_time);
		data[i] = acceleration (i * sample_time) + rand() % 1 - 0.5;
	}
	
	Complex c_k[n];  //массив коэффициентов
	Complex Odd[n/2]; //массив нечетных коэффициентов
	Complex Even [n/2]; //массив четных коэффициентов
	
	// Нулевые значения коэффициентов
	for (int i = 0; i < n; i++) { 
		c_k[i] = Complex (0);
	}
	for (int i = 0; i < (n/2); i++) { 
		Odd[i] = Complex (0);
		Even[i] = Complex (0);
	}
	
	
	//FFT
	for (int k = 0; k < n/2; k++) {
		for (int m = 0; m < n/2; m++ ) {
			Even[k] = Add (Even[k], Cross (Complex(data[2*m]), Exponenta(m, k, n/2)));		
			Odd[k] = Add (Odd[k], Cross (Complex(data[2*m+1]), Exponenta(m, k, n/2)));	
			
		}
		c_k[k] = Add(Even[k],Cross(Exponenta(1, k, n), Odd[k]));
	}
	for (int k = n/2; k < n; k++) {
		c_k[k] = Difference(Even[k],Cross(Exponenta(1, k, n/2), Odd[k]));
	}
	//Реализация Фильтра
	cout <<"coefficients"<<endl;
	float ck_min = 4 ; // Число среза
	for (int k = 0; k < n; k++) {
		if(pow(c_k[k].Modul(),2) < ck_min) {c_k[k] = Complex (0);}
	cout <<c_k[k].Real()<<"  "<<c_k[k].Real()<<endl;
	
	}
	
	//Output 
	for (int t=0; t < 512; t+=10){
		cout<<"t = "<<t*sample_time<<"  a =  "<<filtered_data(n,c_k,t).Real()<<" m/s^2"<<endl;
	}
	
	
	return 0;
}