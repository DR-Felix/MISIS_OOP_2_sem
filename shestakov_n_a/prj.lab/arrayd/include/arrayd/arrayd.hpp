#include <iosfwd>

class ArrayD {

public:
    /**
     * \detail ������� ������ ������� size, ����������� ���������� �� �������� �� ���������.
     *         ���� size = 0 ��������� ������ �� ����������
     * \param[in] size ������ �������
     * \throw std::invalid_argument ���� size < 0
     */
    explicit ArrayD(const std::ptrdiff_t size = 0);
    ArrayD(const ArrayD& other);
    ArrayD& operator=(const ArrayD& other);

    ArrayD(ArrayD&& other) noexcept; //�����������

    ~ArrayD(); //����������
    /**
     * \brief ������ � ��������� �� �������
     * \param[in] i ������ ������������� ��������
     * \return i-��� �������
     * \throw std::out_of_range ���� ������ ��� ��������� [0, size)
     */
    [[nodiscard]] double& operator[](const std::ptrdiff_t i);
    [[nodiscard]] const double& operator[](const std::ptrdiff_t i) const;

    /**
     * \return ������� ������ �������
     */
    [[nodiscard]] std::ptrdiff_t ssize() const noexcept;

    /**
     * \brief ��������� ������� �������
     * \param[in] new_size ����� ������ �������
     * \throw std::invalid_argument ���� ������� �������� new_size <= 0
     */
    void resize(const std::ptrdiff_t new_size);

    /**
     * \brief ��������� �������. ���� ������� ������������, ������ resize
     * \param[in] i ������ ��������, ������� ����� ��������
     * \param[in] value ��������, ������� ���� ��������
     * \throw std::out_of_range ���� ������ ��� ��������� [0, size]
     */
    void insert(const std::ptrdiff_t i, const double& value);

    /**
     * \brief ������� ������� �� ������� i
     * \param[in] i ������ ���������� ��������
     * \throw std::out_of_range ���� ������ ��� ��������� [0, size)
     */
    void remove(const std::ptrdiff_t i);

    //����/�����
    std::istream& ReadFrom(std::istream& istrm);
    std::ostream& WriteTo(std::ostream& ostrm);

private:
    std::ptrdiff_t ssize_{ 0 };
    std::ptrdiff_t capacity_{ 0 };
    double* data_{ nullptr };
};

std::ostream& operator<<(std::ostream& ostrm, ArrayD& array);
std::istream& operator>>(std::istream& istrm, ArrayD& array);