#include <iostream>

void task();

int main()
{
  try
  {
    task();
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what();
    return 1;
  }

  return 0;
}
