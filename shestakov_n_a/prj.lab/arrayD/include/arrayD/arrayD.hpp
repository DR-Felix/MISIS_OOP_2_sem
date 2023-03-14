#include <initializer_list>
#include <cstddef>
#include "iosfwd"


class ArrayD
{
public:

    ArrayD(int s = 0); //умолчательные конструкторы
    ArrayD(const ArrayD& other);
    ArrayD(std::initializer_list<double> list);
    ArrayD& operator=(const ArrayD& other);

    ArrayD(ArrayD&& other);

    ~ArrayD() = default; //деструктор

    double& operator[](int iter) const; //Оператор итерирования

    ptrdiff_t ssize() const; //Взятие размера, ptrdiff_t - беззнаковый целочисленный тип, исмпользуемый для записи максимально возможного
                            //размера любого массива, безопасно может быть помещен указатель (см. конфликт с машинным словом)

    void resize(const int& size); //изменение размера
    void insert(const int& i, const double& elem); //добавить элемент
    void remove(const int& i); //удалить элемент

    std::istream& ReadFrom(std::istream& istrm); //ввод
    std::ostream& WriteTo(std::ostream& ostrm); //вывод


private:
    double *data = nullptr; //nullptr - нулевой указатель, по большей мере для сохранности и чистки адреса
    ptrdiff_t ssize_ = 0; //размер массива
};

std::ostream& operator<<(std::ostream& ostrm, ArrayD& array);
std::istream& operator>>(std::istream& istrm, ArrayD& array); 

