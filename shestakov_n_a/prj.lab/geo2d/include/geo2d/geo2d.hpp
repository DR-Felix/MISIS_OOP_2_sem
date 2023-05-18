#include <fstream>
#include <string>
#include <vector>

namespace geometry {
    class Figure {
    public:
        using Coordinates = std::tuple<double, double>;
    public:
        constexpr Figure() = default;
        ~Figure() = default;
        Figure(const Figure&) = default;
        Figure& operator=(const Figure&) = default;

        virtual void WriteTo(std::ofstream& ostream) const = 0;
        virtual void ReadFrom(std::istream& istream) = 0;
    };

    class Point : public Figure {
    public:
        constexpr Point() = default;
        ~Point() = default;
        Point(const Point&) = default;
        Point& operator=(const Point&) = default;

        explicit constexpr Point(const Coordinates& pt);

        void WriteTo(std::ofstream& ostream) const;
        void ReadFrom(std::istream& istream);
    private:
        Coordinates point_{ 0.0, 0.0 };
    };

    class Polyline : public Figure {
    public:
        constexpr Polyline() = default;
        ~Polyline() = default;
        Polyline(const Polyline&) = default;
        Polyline& operator=(const Polyline&) = default;

        Polyline(std::initializer_list<Coordinates> il);
        void WriteTo(std::ofstream& ostream) const;
        void ReadFrom(std::istream& istream);
    protected:
        std::vector<Coordinates> vertex_{ {0.0,0.0} };
    };


    class Elipse : public Figure {
    public:
        constexpr Elipse() = default;
        ~Elipse() = default;
        Elipse(const Elipse&) = default;
        Elipse& operator=(const Elipse&) = default;

        explicit constexpr Elipse(const Coordinates& center, const double& halfa, const double& halfb);

        void WriteTo(std::ofstream& ostream) const;
        void ReadFrom(std::istream& istream);
    private:
        Coordinates center_;
        double halfA_;
        double halfB_;
    };

    class Segment :public Figure, protected Polyline {
    public:
        constexpr Segment() = default;
        ~Segment() = default;
        Segment(const Segment&) = default;
        Segment& operator=(const Segment&) = default;

        Segment(std::initializer_list<Coordinates> il);
        void WriteTo(std::ofstream& ostream) const;
        void ReadFrom(std::istream& istream);
    private:
        std::string fill_colour{ "" };
    };
}
