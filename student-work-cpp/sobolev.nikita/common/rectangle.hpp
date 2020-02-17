#ifndef RectangleHPP
#define RectangleHPP

#include "shape.hpp"

namespace sobolev
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &center, double width, double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t &newPoint) override;
    void scale(double coefficient) override;
    void rotate(double degrees) override;
    void printInfo() const override;

  private:
    point_t center_;
    double width_;
    double height_;
    point_t corners_[4];
  };
}

#endif
