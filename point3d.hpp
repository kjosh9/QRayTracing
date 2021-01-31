#ifndef POINT3D_H
#define POINT3D_H


class point3D {

public:
    point3D();

    point3D(double x, double y, double z);

    point3D(const point3D& rhs);

    ~point3D();

    bool operator==(const point3D& rhs);

    point3D& operator=(const point3D& rhs);

    double x();

    double y();

    double z();

    point3D operator-(const point3D &rhs);

    point3D operator+(const point3D &rhs);

    point3D operator*(const point3D &rhs);

    double dot(const point3D &rhs);

    point3D norm();

    point3D operator*(double scalar);

private:
    double _xPos;
    double _yPos;
    double _zPos;
};

#endif // POINT3D_H
