#include <cmath>
#include <gtest/gtest.h>
#include <memory>
#include "../src/figures.h"
#include "../src/array.h"

using namespace std;

// Тесты для Point
TEST(PointTest, BasicCreation) {
    Point<int> p1(10, 20);
    EXPECT_EQ(p1.getX(), 10);
    EXPECT_EQ(p1.getY(), 20);
    
    Point<double> p2(3.14, 2.71);
    EXPECT_DOUBLE_EQ(p2.getX(), 3.14);
    EXPECT_DOUBLE_EQ(p2.getY(), 2.71);
}

TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

// Тесты для PointContainer
TEST(PointContainerTest, BasicOperations) {
    PointContainer<Point<int>> container;
    
    EXPECT_EQ(container.size(), 0);
    
    container.push_back(make_unique<Point<int>>(1, 2));
    container.push_back(make_unique<Point<int>>(3, 4));
    
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0].getX(), 1);
    EXPECT_EQ(container[1].getY(), 4);
}

TEST(PointContainerTest, MoveSemantics) {
    PointContainer<Point<int>> container1;
    container1.push_back(make_unique<Point<int>>(1, 2));
    
    PointContainer<Point<int>> container2 = std::move(container1);
    
    EXPECT_EQ(container1.size(), 0);
    EXPECT_EQ(container2.size(), 1);
    EXPECT_EQ(container2[0].getX(), 1);
}

// Тесты для Figure базового класса
class TestFigure : public Figure<int> {
public:
    Point<int> center() const override {
        if (this->points.size() == 0) return Point<int>(0, 0);
        int sum_x = 0, sum_y = 0;
        for (size_t i = 0; i < this->points.size(); ++i) {
            sum_x += this->points[i].getX();
            sum_y += this->points[i].getY();
        }
        return Point<int>(sum_x / this->points.size(), sum_y / this->points.size());
    }
    
    operator double() override {
        return this->points.size();
    }
};

TEST(FigureTest, BasicOperations) {
    TestFigure figure;
    figure.add_point(Point<int>(0, 0));
    figure.add_point(Point<int>(4, 0));
    figure.add_point(Point<int>(4, 4));
    figure.add_point(Point<int>(0, 4));
    
    EXPECT_EQ(figure.get_points_count(), 4);
    EXPECT_EQ(figure.get_point(0).getX(), 0);
    EXPECT_EQ(figure.get_point(3).getY(), 4);
}

// Тесты для Rhombus
TEST(RhombusTest, CenterCalculation) {
    Rhombus<int> rhombus;
    // Ромб с вершинами: (0,0), (2,2), (4,0), (2,-2)
    rhombus.add_point(Point<int>(0, 0));
    rhombus.add_point(Point<int>(2, 2));
    rhombus.add_point(Point<int>(4, 0));
    rhombus.add_point(Point<int>(2, -2));
    
    Point<int> center = rhombus.center();
    EXPECT_EQ(center.getX(), 2);
    EXPECT_EQ(center.getY(), 0);
}

TEST(RhombusTest, AreaCalculation) {
    Rhombus<int> rhombus;
    // Ромб с диагоналями 4 и 4 (квадрат)
    rhombus.add_point(Point<int>(0, 0));
    rhombus.add_point(Point<int>(2, 2));
    rhombus.add_point(Point<int>(4, 0));
    rhombus.add_point(Point<int>(2, -2));
    
    double area = static_cast<double>(rhombus);
    EXPECT_DOUBLE_EQ(area, 8.0);
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid<int> trapezoid;
    // Трапеция с основаниями 4 и 2, высотой 2
    trapezoid.add_point(Point<int>(0, 0));
    trapezoid.add_point(Point<int>(4, 0));
    trapezoid.add_point(Point<int>(3, 2));
    trapezoid.add_point(Point<int>(1, 2));
    
    double area = static_cast<double>(trapezoid);
    EXPECT_DOUBLE_EQ(area, 6.0);
}

// Тесты для Pentagon
TEST(PentagonTest, AreaCalculation) {
    Pentagon<double> pentagon;
    // Простой пятиугольник
    pentagon.add_point(Point<double>(0, 0));
    pentagon.add_point(Point<double>(2, 0));
    pentagon.add_point(Point<double>(3, 1));
    pentagon.add_point(Point<double>(2, 2));
    pentagon.add_point(Point<double>(0, 2));
    
    double area = static_cast<double>(pentagon);
    EXPECT_GT(area, 0);
}

// Тесты для Array
TEST(ArrayTest, BasicOperations) {
    Array<int> arr;
    
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0);
    
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    EXPECT_FALSE(arr.empty());
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, CopyAndMoveSemantics) {
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    
    // Тестирование копирования
    Array<int> arr2 = arr1;
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 1);
    
    // Тестирование перемещения
    Array<int> arr3 = std::move(arr1);
    EXPECT_EQ(arr1.size(), 0);
    EXPECT_EQ(arr3.size(), 2);
    EXPECT_EQ(arr3[1], 2);
}

TEST(ArrayTest, ResizeAndReserve) {
    Array<double> arr;
    
    arr.resize(5);
    EXPECT_EQ(arr.size(), 5);
    EXPECT_GE(arr.capacity(), 5);
    
    arr.reserve(20);
    EXPECT_GE(arr.capacity(), 20);
    EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayFigureTest, StoreFigures) {
    Array<shared_ptr<Figure<int>>> figures;
    
    auto rhombus = make_shared<Rhombus<int>>();
    rhombus->add_point(Point<int>(0, 0));
    rhombus->add_point(Point<int>(2, 2));
    rhombus->add_point(Point<int>(4, 0));
    rhombus->add_point(Point<int>(2, -2));
    
    auto trapezoid = make_shared<Trapezoid<int>>();
    trapezoid->add_point(Point<int>(0, 0));
    trapezoid->add_point(Point<int>(4, 0));
    trapezoid->add_point(Point<int>(3, 2));
    trapezoid->add_point(Point<int>(1, 2));
    
    figures.push_back(rhombus);
    figures.push_back(trapezoid);
    
    EXPECT_EQ(figures.size(), 2);
    EXPECT_GT(static_cast<double>(*figures[0]), 0);
    EXPECT_GT(static_cast<double>(*figures[1]), 0);
}

TEST(ArrayFigureTest, TotalAreaCalculation) {
    Array<shared_ptr<Figure<double>>> figures;
    
    auto rhombus = make_shared<Rhombus<double>>();
    rhombus->add_point(Point<double>(0, 0));
    rhombus->add_point(Point<double>(2, 2));
    rhombus->add_point(Point<double>(4, 0));
    rhombus->add_point(Point<double>(2, -2));
    
    auto trapezoid = make_shared<Trapezoid<double>>();
    trapezoid->add_point(Point<double>(0, 0));
    trapezoid->add_point(Point<double>(4, 0));
    trapezoid->add_point(Point<double>(3, 2));
    trapezoid->add_point(Point<double>(1, 2));
    
    figures.push_back(rhombus);
    figures.push_back(trapezoid);
    
    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_area += static_cast<double>(*figures[i]);
    }
    
    EXPECT_GT(total_area, 0);
    EXPECT_NEAR(total_area, 8.0 + 6.0, 0.1);
}

// Тесты для концептов
TEST(ConceptTest, PointableConcept) {
    EXPECT_TRUE(Pointable<int>);
    EXPECT_TRUE(Pointable<double>);
    EXPECT_TRUE(Pointable<float>);
    EXPECT_TRUE(Pointable<long>);
}

// Интеграционные тесты
TEST(IntegrationTest, CompleteWorkflow) {
    Array<shared_ptr<Figure<double>>> figures;
    
    auto rhombus = make_shared<Rhombus<double>>();
    rhombus->add_point(Point<double>(0, 0));
    rhombus->add_point(Point<double>(2, 2));
    rhombus->add_point(Point<double>(4, 0));
    rhombus->add_point(Point<double>(2, -2));
    figures.push_back(rhombus);
    
    auto trapezoid = make_shared<Trapezoid<double>>();
    trapezoid->add_point(Point<double>(0, 0));
    trapezoid->add_point(Point<double>(4, 0));
    trapezoid->add_point(Point<double>(3, 2));
    trapezoid->add_point(Point<double>(1, 2));
    figures.push_back(trapezoid);
    
    auto pentagon = make_shared<Pentagon<double>>();
    pentagon->add_point(Point<double>(0, 0));
    pentagon->add_point(Point<double>(2, 0));
    pentagon->add_point(Point<double>(3, 1));
    pentagon->add_point(Point<double>(2, 2));
    pentagon->add_point(Point<double>(0, 2));
    figures.push_back(pentagon);
    
    EXPECT_EQ(figures.size(), 3);
    
    for (size_t i = 0; i < figures.size(); ++i) {
        Point<double> center = figures[i]->center();
        EXPECT_FALSE(isnan(center.getX()));
        EXPECT_FALSE(isnan(center.getY()));
    }
    
    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        double area = static_cast<double>(*figures[i]);
        EXPECT_GT(area, 0);
        total_area += area;
    }
    EXPECT_GT(total_area, 0);
}