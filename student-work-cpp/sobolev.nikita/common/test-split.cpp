#include <boost/test/auto_unit_test.hpp>

#include "split.hpp"
#include "matrix.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

BOOST_AUTO_TEST_SUITE(SplitTestSuite)

BOOST_AUTO_TEST_CASE(CorrectWorkOfSplit)
{
  sobolev::Rectangle rec1({7.0, 6.0}, 4.0, 2.0);
  sobolev::Rectangle rec2({10.0, 3.0}, 4.0, 2.0);
  sobolev::Circle cir1({4.0, 4.0}, 2.0);
  sobolev::Circle cir2({10.0, 8.0}, 2.0);

  sobolev::CompositeShape composite;
  composite.add(std::make_shared<sobolev::Circle>(cir1));
  composite.add(std::make_shared<sobolev::Rectangle>(rec1));
  composite.add(std::make_shared<sobolev::Rectangle>(rec2));
  composite.add(std::make_shared<sobolev::Circle>(cir2));

  sobolev::Matrix matrix = sobolev::split(composite);

  BOOST_CHECK_EQUAL(matrix.getRows(), 2);
  BOOST_CHECK_EQUAL(matrix[0].getSize(), 3);
  BOOST_CHECK_EQUAL(matrix[1].getSize(), 1);
  BOOST_CHECK_EQUAL(matrix[0][0]->getArea(), cir1.getArea());
  BOOST_CHECK_EQUAL(matrix[1][0]->getArea(), rec1.getArea());
  BOOST_CHECK_EQUAL(matrix.getNumberOfFigures(), 4);
}

BOOST_AUTO_TEST_SUITE_END()
