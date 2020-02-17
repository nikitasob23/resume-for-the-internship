#include <iostream>

#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "split.hpp"

int main()
{
  sobolev::Rectangle rec({4.0, 3.0}, 4.0, 2.0);
  sobolev::Circle cir1({7.0, 5.0}, 2.0);
  sobolev::Circle cir2({11.0, 2.0}, 1.0);

  sobolev::Shape *shape = &rec;
  std::cout << "Rectangle before changes:" << std::endl;
  shape->printInfo();
  shape->move(1.0, 2.0);
  shape->move({5.0, 3.0});
  shape->scale(2.0);
  shape->rotate(90);
  std::cout << "Rectangle after changes:" << std::endl;
  shape->printInfo();

  shape = &cir1;
  std::cout << "Circle before changes:" << std::endl;
  shape->printInfo();
  shape->move(3.0, 2.0);
  shape->move({1.0, 1.0});
  shape->scale(4.0);
  std::cout << "Circle after changes:" << std::endl;
  shape->printInfo();

  sobolev::CompositeShape compositeShape(std::make_shared<sobolev::Rectangle>(rec));
  compositeShape.add(std::make_shared<sobolev::Circle>(cir1));
  compositeShape.add(std::make_shared<sobolev::Circle>(cir2));
  std::cout << "Composite Shape before changes:" << std::endl;
  compositeShape.printInfo();
  compositeShape.move(2.0, 2.0);
  compositeShape.move({0.0, 0.0});
  compositeShape.scale(2.0);
  compositeShape.rotate(180);
  std::cout << "Composite Shape after changes:" << std::endl;
  compositeShape.printInfo();

  compositeShape.remove(1);
  std::cout << "Composite Shape after delete shape:" << std::endl;
  compositeShape.printInfo();

  sobolev::Matrix matrix = sobolev::split(compositeShape);
  matrix[0][0]->printInfo();
  matrix[0][1]->printInfo();

  matrix.add(std::make_shared<sobolev::Circle>(cir1), 1);
  matrix.printInfo();

  return 0;
}
