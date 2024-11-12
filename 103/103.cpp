#include "pch.h"
#include "CppUnitTest.h"
#include "../lab10.3/103.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace My103
{
	TEST_CLASS(My103)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            Product* products = new Product[3]{
               {"Product 1", 50.0, 10, "kg"},
               {"Product 2", 30.0, 5, "pcs"},
               {"Product 3", 40.0, 20, "m"}
            };
            int size = 3;

            // Сортуємо за загальною вартістю
            sortProducts(products, size);

            // Перевіряємо правильність сортування
            Assert::AreEqual(string(products[0].name), string("Product 2"));
            Assert::AreEqual(string(products[1].name), string("Product 3"));
            Assert::AreEqual(string(products[2].name), string("Product 1"));

            // Очищуємо пам'ять
            delete[] products;
		}
	};
}
