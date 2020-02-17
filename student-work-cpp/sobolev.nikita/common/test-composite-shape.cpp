#include <boost/test/auto_unit_test.hpp>

#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double ALLOWABLE_ERROR = 0.001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTestSuite)

BOOST_AUTO_TEST_CASE(ImmutabilityofCompositeShapeParameters)
{
  sobolev::Rectangle rec({0.0, 0.0}, 2.0, 4.0);
  sobolev::Circle cir({2.0, 3.0}, 1.0);
  sobolev::CompositeShape composite(std::make_shared<sobolev::Rectangle>(rec));
  composite.add(std::make_shared<sobolev::Circle>(cir));
  const sobolev::rectangle_t compositeBefore = composite.getFrameRect();
  const double areaBefore = composite.getArea();
  const size_t countBefore = composite.getCount();

  composite.move(1.0, 1.0);
  BOOST_CHECK_CLOSE(compositeBefore.width, composite.getFrameRect().width, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(compositeBefore.height, composite.getFrameRect().height, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(areaBefore, composite.getArea(), ALLOWABLE_ERROR);
  BOOST_CHECK_EQUAL(countBefore, composite.getCount());

  composite.move({4.0, 6.0});
  BOOST_CHECK_CLOSE(compositeBefore.width, composite.getFrameRect().width, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(compositeBefore.height, composite.getFrameRect().height, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(areaBefore, composite.getArea(), ALLOWABLE_ERROR);
  BOOST_CHECK_EQUAL(countBefore, composite.getCount());
}

BOOST_AUTO_TEST_CASE(CompositeShapeAreaAfterScale)
{
  sobolev::Rectangle rec({0.0, 0.0}, 2.0, 4.0);
  sobolev::Circle cir({2.0, 3.0}, 1.0);
  sobolev::CompositeShape composite(std::make_shared<sobolev::Rectangle>(rec));
  composite.add(std::make_shared<sobolev::Circle>(cir));
  const double areaBefore1 = composite.getArea();
  const double scaleFactor1 = 2.0;

  composite.scale(scaleFactor1);
  BOOST_CHECK_CLOSE(areaBefore1 * scaleFactor1 * scaleFactor1, composite.getArea(), ALLOWABLE_ERROR);

  const double areaBefore2 = composite.getArea();
  const double scaleFactor2 = 0.5;

  composite.scale(scaleFactor2);
  BOOST_CHECK_CLOSE(areaBefore2 * scaleFactor2 * scaleFactor2, composite.getArea(), ALLOWABLE_ERROR);
}

BOOST_AUTO_TEST_CASE(CompositeShapeFrameRectAfterScale)
{
  sobolev::Rectangle rec({0.0, 0.0}, 2.0, 4.0);
  sobolev::Circle cir({2.0, 3.0}, 1.0);
  sobolev::CompositeShape composite(std::make_shared<sobolev::Rectangle>(rec));
  composite.add(std::make_shared<sobolev::Circle>(cir));
  const sobolev::rectangle_t frameRectBefore = composite.getFrameRect();
  const double scaleFactor = 3.0;

  composite.scale(scaleFactor);
  const sobolev::rectangle_t frameRectAfter = composite.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectBefore.width * scaleFactor, frameRectAfter.width, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(frameRectBefore.height * scaleFactor, frameRectAfter.height, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(frameRectBefore.pos.x, frameRectAfter.pos.x, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(frameRectBefore.pos.y, frameRectAfter.pos.y, ALLOWABLE_ERROR);
}

BOOST_AUTO_TEST_CASE(CompositeShapeFrameRectAfterRotate)
{
  sobolev::Rectangle rec({0.0, 0.0}, 2.0, 4.0);
  sobolev::Circle cir({2.0, 3.0}, 1.0);
  sobolev::CompositeShape composite(std::make_shared<sobolev::Rectangle>(rec));
  composite.add(std::make_shared<sobolev::Circle>(cir));
  const sobolev::rectangle_t frameRectBefore = composite.getFrameRect();
  const double areaBefore = composite.getArea();

  composite.rotate(90);
  const sobolev::rectangle_t frameRectAfter = composite.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectBefore.width, frameRectAfter.height, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(frameRectBefore.height, frameRectAfter.width, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(areaBefore, composite.getArea(), ALLOWABLE_ERROR);
}

BOOST_AUTO_TEST_CASE(CompositeShapeIncorrectParameters)
{
  sobolev::Rectangle rec({0.0, 0.0}, 2.0, 4.0);
  sobolev::Circle cir({2.0, 3.0}, 1.0);
  sobolev::CompositeShape composite(std::make_shared<sobolev::Rectangle>(rec));
  composite.add(std::make_shared<sobolev::Circle>(cir));

  BOOST_CHECK_THROW(composite.scale(-1.0), std::invalid_argument);
  BOOST_CHECK_THROW(composite.add(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(composite.remove(3), std::invalid_argument);
  BOOST_CHECK_THROW(composite[2], std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(CompositeShapeAfterAddShape)
{
  sobolev::Rectangle rec({0.0, 0.0}, 2.0, 4.0);
  sobolev::CompositeShape composite(std::make_shared<sobolev::Rectangle>(rec));
  const double areaBefore = composite.getArea();
  const size_t countBefore = composite.getCount();
  sobolev::Circle cir({2.0, 3.0}, 1.0);
  composite.add(std::make_shared<sobolev::Circle>(cir));
  const double areaCir = composite[1]->getArea();
  BOOST_CHECK_CLOSE(areaBefore + areaCir, composite.getArea(), ALLOWABLE_ERROR);
  BOOST_CHECK_EQUAL(countBefore + 1, composite.getCount());
}

BOOST_AUTO_TEST_CASE(CompositeShapeAfterDeleteByIndexShape)
{
  sobolev::Rectangle rec({0.0, 0.0}, 2.0, 4.0);
  sobolev::Circle cir({2.0, 3.0}, 1.0);
  sobolev::CompositeShape composite(std::make_shared<sobolev::Rectangle>(rec));
  composite.add(std::make_shared<sobolev::Circle>(cir));
  const double areaBefore = composite.getArea();
  const double areaSecondShape = composite[1]->getArea();
  const size_t countBefore = composite.getCount();

  composite.remove(1);
  BOOST_CHECK_CLOSE(composite.getArea(), areaBefore - areaSecondShape, ALLOWABLE_ERROR);
  BOOST_CHECK_EQUAL(countBefore - 1, composite.getCount());
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
  sobolev::Rectangle rec({0.0, 0.0}, 2.0, 4.0);
  sobolev::Circle cir({2.0, 3.0}, 1.0);
  sobolev::CompositeShape composite(std::make_shared<sobolev::Rectangle>(rec));
  composite.add(std::make_shared<sobolev::Circle>(cir));
  const double compositeArea = composite.getArea();
  const sobolev::rectangle_t compositeFrameRect = composite.getFrameRect();
  const size_t compositeCount = composite.getCount();
  sobolev::CompositeShape testComposite(composite);
  const double testCompositeArea = testComposite.getArea();
  const sobolev::rectangle_t testCompositeFrameRect = testComposite.getFrameRect();
  const size_t testCompositeCount = testComposite.getCount();

  BOOST_CHECK_CLOSE(compositeArea, testCompositeArea, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(compositeFrameRect.width, testCompositeFrameRect.width, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(compositeFrameRect.height, testCompositeFrameRect.height, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(compositeFrameRect.pos.x, testCompositeFrameRect.pos.x, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(compositeFrameRect.pos.y, testCompositeFrameRect.pos.y, ALLOWABLE_ERROR);
  BOOST_CHECK_EQUAL(compositeCount, testCompositeCount);
}

BOOST_AUTO_TEST_CASE(CopyOperator)
{
  sobolev::Rectangle rec({0.0, 0.0}, 2.0, 4.0);
  sobolev::Circle cir({2.0, 3.0}, 1.0);
  sobolev::CompositeShape composite(std::make_shared<sobolev::Rectangle>(rec));
  composite.add(std::make_shared<sobolev::Circle>(cir));
  const double compositeArea = composite.getArea();
  const sobolev::rectangle_t compositeFrameRect = composite.getFrameRect();
  const size_t compositeCount = composite.getCount();
  sobolev::CompositeShape testComposite = composite;
  const double testCompositeArea = testComposite.getArea();
  const sobolev::rectangle_t testCompositeFrameRect = testComposite.getFrameRect();
  const size_t testCompositeCount = testComposite.getCount();

  BOOST_CHECK_CLOSE(compositeArea, testCompositeArea, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(compositeFrameRect.width, testCompositeFrameRect.width, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(compositeFrameRect.height, testCompositeFrameRect.height, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(compositeFrameRect.pos.x, testCompositeFrameRect.pos.x, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(compositeFrameRect.pos.y, testCompositeFrameRect.pos.y, ALLOWABLE_ERROR);
  BOOST_CHECK_EQUAL(compositeCount, testCompositeCount);
}

BOOST_AUTO_TEST_SUITE_END()
