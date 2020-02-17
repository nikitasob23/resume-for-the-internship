#include "matrix.hpp"

#include <iostream>

sobolev::Matrix::Layer::Layer(sobolev::Shape::ptr *arr, size_t size) :
  size_(size),
  figures_(std::make_unique<Shape::ptr[]>(size))
{
  for (size_t i = 0; i < size_; i++)
  {
    figures_[i] = arr[i];
  }
}

sobolev::Shape::ptr sobolev::Matrix::Layer::operator [](size_t index) const
{
  if (index >= size_)
  {
    throw std::invalid_argument("Index is out of array");
  }

  return figures_[index];
}

size_t sobolev::Matrix::Layer::getSize() const
{
  return size_;
}

sobolev::Matrix::Matrix() :
  rows_(0),
  numberOfFigures(0)
{ }

sobolev::Matrix::Matrix(const sobolev::Matrix &other) :
  rows_(other.rows_),
  columns_(new size_t[other.rows_]),
  figures_(std::make_unique<Shape::ptr[]>(other.numberOfFigures)),
  numberOfFigures(other.numberOfFigures)
{
  for (size_t i = 0; i < numberOfFigures; i++)
  {
    figures_[i] = other.figures_[i];
  }

  for (size_t i = 1; i < rows_; i++)
  {
    columns_[i] = other.columns_[i];
  }
}

sobolev::Matrix::Matrix(sobolev::Matrix &&other) :
  rows_(other.rows_),
  columns_(std::move(other.columns_)),
  figures_(std::move(other.figures_)),
  numberOfFigures(other.numberOfFigures)
{ }

sobolev::Matrix &sobolev::Matrix::operator =(const sobolev::Matrix &other)
{
  if (this != &other)
  {
    rows_ = other.rows_;
    numberOfFigures = other.numberOfFigures;

    Shape::arrayPtr tmpFigures = std::make_unique<Shape::ptr[]>(other.numberOfFigures);
    for (size_t i = 0; i < numberOfFigures; i++)
    {
      tmpFigures[i] = other.figures_[i];
    }
    figures_.swap(tmpFigures);

    std::unique_ptr<size_t[]> tmpColumns = std::make_unique<size_t[]>(other.rows_);
    for (size_t i = 1; i < rows_; i++)
    {
      tmpColumns[i] = other.columns_[i];
    }
    columns_.swap(tmpColumns);
  }

  return *this;
}

sobolev::Matrix &sobolev::Matrix::operator =(sobolev::Matrix &&other)
{
  if (this != &other)
  {
    rows_ = other.rows_;
    columns_ = std::move(other.columns_);
    figures_ = std::move(other.figures_);
    numberOfFigures = other.numberOfFigures;
  }

  return *this;
}

sobolev::Matrix::Layer sobolev::Matrix::operator [](size_t row) const
{
  if (row >= rows_)
  {
    throw std::invalid_argument("Index is out of array");
  }

  size_t index = 0;
  for (size_t i = 0; i < row; i++)
  {
    index += columns_[i];
  }

  return Layer(&figures_[index], columns_[row]);
}

void sobolev::Matrix::add(Shape::ptr shape, size_t row)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Can't be empty");
  }

  if (row > rows_)
  {
    throw std::invalid_argument("Argument must be less than or equal to the number of lines");
  }

  std::unique_ptr<Shape::ptr[]> tmpFigures = std::make_unique<Shape::ptr[]>(numberOfFigures + 1);

  size_t figureCounter = 0;
  size_t tmpCounter = 0;

  for (size_t tmpRow = 0; tmpRow < rows_; tmpRow++)
  {
    for (size_t column = 0; column < columns_[tmpRow]; column++)
    {
      tmpFigures[tmpCounter++] = figures_[figureCounter++];
    }

    if (row == tmpRow)
    {
      tmpFigures[tmpCounter++] = shape;
      columns_[tmpRow]++;
    }
  }

  if (row == rows_)
  {
    std::unique_ptr<size_t[]> tmpColumns = std::make_unique<size_t[]>(rows_ + 1);

    for (size_t tmpRow = 0; tmpRow < rows_; tmpRow++)
    {
      tmpColumns[tmpRow] = columns_[tmpRow];
    }

    tmpFigures[tmpCounter] = shape;
    tmpColumns[rows_] = 1;
    rows_++;
    columns_.swap(tmpColumns);
  }

  numberOfFigures++;
  figures_.swap(tmpFigures);
}

size_t sobolev::Matrix::getRows() const
{
  return rows_;
}

size_t sobolev::Matrix::getNumberOfFigures() const
{
  return numberOfFigures;
}

void sobolev::Matrix::printInfo() const
{
  std::cout << "MATRIX" << std::endl;
  std::cout << "Number of rows: " << rows_ << std::endl;
  std::cout << "Number of figures: " << numberOfFigures << std::endl;
}
