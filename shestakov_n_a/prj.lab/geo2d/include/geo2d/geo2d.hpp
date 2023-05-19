
void geometry::Point::WriteTo(std::ofstream& ostream) const {
    ostream << "\\fill(" << std::get<0>(point_) << ", " << std::get<1>(point_) << ") circle(2pt);" << std::endl;
}

void geometry::Point::ReadFrom(std::istream& istream) {
    istream >> std::get<0>(point_);
    istream >> std::get<1>(point_);
}

constexpr geometry::Point::Point(const Coordinates& pt)
    : point_(pt)
{
}

constexpr geometry::Elipse::Elipse(const Coordinates& center, const double& halfa, const double& halfb)
    : center_(center), halfA_(halfa), halfB_(halfb)
{
}

void geometry::Elipse::WriteTo(std::ofstream& ostream) const {
    ostream << "\\draw (" << std::get<0>(center_) << ", " << std::get<1>(center_) << ") ellipse (" << halfA_ << " and " << halfB_ << ");" << std::endl;
}

void geometry::Elipse::ReadFrom(std::istream& istream) {
    istream >> std::get<0>(center_);
    istream >> std::get<1>(center_);
    istream >> halfA_;
    istream >> halfB_;
}

geometry::Polyline::Polyline(std::initializer_list<Coordinates> il) {
    for (auto i : il) {
        vertex_.push_back(i);
    }
}

void geometry::Polyline::WriteTo(std::ofstream& ostream) const {
    for (size_t i = 0; i < vertex_.size(); ++i) {
        ostream << "\\draw (" << std::get<0>(vertex_[i]) << ", " << std::get<1>(vertex_[i]) << ")";
        if (i != vertex_.size() - 1) {
            ostream << " -- ";
        }
    }
    ostream << ";" << std::endl;
}

void geometry::Polyline::ReadFrom(std::istream& istream) {
    Coordinates x;
    istream >> std::get<0>(x) >> std::get<1>(x);
    vertex_.push_back(x);
}

//Определения методом для Segment
geometry::Segment::Segment(std::initializer_list<Coordinates> il) {
    for (auto i : il) {
        vertex_.push_back(i);
    }
}

void geometry::Segment::WriteTo(std::ofstream& ostream) const {
    ostream << "\\draw [fill=red, opacity = 1]";
    for (size_t i = 0; i < vertex_.size(); ++i) {
        ostream << "(" << std::get<0>(vertex_[i]) << ", " << std::get<1>(vertex_[i]) << ")";
        if (i != vertex_.size() - 1) {
            ostream << " -- ";
        }
    }
    ostream << ";" << std::endl;
}

void geometry::Segment::ReadFrom(std::istream& istream) {
    Coordinates x;
    istream >> std::get<0>(x) >> std::get<1>(x);
    vertex_.push_back(x);
}

namespace Style {
    class Color {
    private:
        std::string colorName = "";
        int R = 0;
        int G = 0;
        int B = 0;
        double A = 1.0;
    };

    class Width {
    public:
        void setWidth(double& num);
    private:
        double width_ = 1.0;
    };

    class Canvas : public geometry::Figure {
    public:
        constexpr Canvas() = default;
        ~Canvas() = default;
        Canvas(const Canvas&) = default;
        Canvas& operator=(const Canvas&) = default;

        explicit constexpr Canvas(const Coordinates& sp, const Coordinates& fp);
        Canvas(const Coordinates& sp, const Coordinates& fp, std::initializer_list<Figure*> shape);

        void AddShape(const Figure& shape);
        void ReadFrom(std::istream& istream);
        void WriteTo(std::ofstream& os) const;
    private:
        Coordinates startPoint_{ 0.0, 0.0 };
        Coordinates endPoint_{ 0.0, 0.0 };
        std::vector<const Figure*> shapes_;
    };
}

Style::Canvas::Canvas(const Coordinates& sp, const Coordinates& fp, std::initializer_list<Figure*> shapes) {
    startPoint_ = sp;
    endPoint_ = fp;
    for (auto i : shapes) {
        shapes_.push_back(i);
    }
}


constexpr Style::Canvas::Canvas(const Coordinates& sp, const Coordinates& fp)
    : startPoint_(sp), endPoint_(fp)
{
}

void Style::Canvas::WriteTo(std::ofstream& os) const {
    os << "\\documentclass[tikz]{standalone}" << std::endl;
    os << "\\begin{document}" << std::endl;
    os << "\\begin{tikzpicture}[xscale=1,yscale=-1]" << std::endl;
    os << "\t\\draw[help lines,use as bounding box] (" << std::get<0>(startPoint_) << "," << std::get<1>(startPoint_) << ") (" << std::get<0>(endPoint_) << "," << std::get<1>(endPoint_) << ");" << std::endl;
    for (const auto& shape : shapes_) {
        os << "\t ";
        shape->WriteTo(os);
    }
    os << "\\end{tikzpicture}" << std::endl;
    os << "\\end{document}" << std::endl;
}

void Style::Canvas::ReadFrom(std::istream& istream) {
    istream >> std::get<0>(startPoint_) >> std::get<1>(startPoint_);
    istream >> std::get<0>(endPoint_) >> std::get<1>(endPoint_);
}

void Style::Canvas::AddShape(const Figure& shape) {
    shapes_.push_back(&shape);
}
