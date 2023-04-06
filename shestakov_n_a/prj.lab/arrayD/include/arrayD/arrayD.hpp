#include <iosfwd>

class ArrayD {

public:
    /**
     * \detail создает массив размера size, заполненого элементами со значнием по умолчанию.
     *         если size = 0 аллокации памяти не происходит
     * \param[in] size размер массива
     * \throw std::invalid_argument если size < 0
     */
    explicit ArrayD(const std::ptrdiff_t size = 0);
    ArrayD(const ArrayD& other);
    ArrayD& operator=(const ArrayD& other);

    ArrayD(ArrayD&& other) noexcept; //копирование

    ~ArrayD(); //деструктор
    /**
     * \brief Доступ к элементам по индексу
     * \param[in] i индекс возвращаемого элемента
     * \return i-тый элемент
     * \throw std::out_of_range если индекс вне диапазона [0, size)
     */
    [[nodiscard]] double& operator[](const std::ptrdiff_t i);
    [[nodiscard]] const double& operator[](const std::ptrdiff_t i) const;

    /**
     * \return текущий размер массива
     */
    [[nodiscard]] std::ptrdiff_t ssize() const noexcept;

    /**
     * \brief Изменение размера массива
     * \param[in] new_size новый размер массива
     * \throw std::invalid_argument если входной параметр new_size <= 0
     */
    void resize(const std::ptrdiff_t new_size);

    /**
     * \brief Вставляет элемент. если размера недостаточно, делает resize
     * \param[in] i индекс элемента, который будет добавлен
     * \param[in] value значение, которое надо добавить
     * \throw std::out_of_range если индекс вне диапазона [0, size]
     */
    void insert(const std::ptrdiff_t i, const double& value);

    /**
     * \brief Удаляет элемент по индексу i
     * \param[in] i индекс удаляемого элемента
     * \throw std::out_of_range если индекс вне диапазона [0, size)
     */
    void remove(const std::ptrdiff_t i);

    //Ввод/вывод
    std::istream& ReadFrom(std::istream& istrm);
    std::ostream& WriteTo(std::ostream& ostrm);

private:
    std::ptrdiff_t ssize_{ 0 };
    std::ptrdiff_t capacity_{ 0 };
    double* data_{ nullptr };
};

std::ostream& operator<<(std::ostream& ostrm, ArrayD& array);
std::istream& operator>>(std::istream& istrm, ArrayD& array);
