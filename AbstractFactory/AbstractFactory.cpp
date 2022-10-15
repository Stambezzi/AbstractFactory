#include <iostream>
#include <map>

enum EDrinkType
{
    eCocaCola,
    eCoffee
};

class Drink
{
public:
    virtual ~Drink() = default;
    virtual void Serve() = 0;
};

class CocaCola : public Drink
{
public:
    CocaCola(int ml) : fMl(ml) {}
    void Serve() override
    {
        std::cout << "Here are your " << fMl << "ml of CocaCola\n";
    }
private:
    int fMl;
};

class Coffee : public Drink
{
public:
    Coffee(int ml) : fMl(ml) {}
    void Serve() override
    {
        std::cout << "Here is your " << fMl << "ml of Coffee Arabica\n";
    }
private:
    int fMl;
};

class AbstractDrinkFactory
{
public:
    virtual ~AbstractDrinkFactory() = default;
    virtual std::unique_ptr<Drink> Create(int ml) = 0;
};

class CocaColaFactory : public AbstractDrinkFactory
{
public:
    std::unique_ptr<Drink> Create(int ml) override
    {
        return std::make_unique<CocaCola>(ml);
    }
};

class CoffeeFactory : public AbstractDrinkFactory
{
public:
    std::unique_ptr<Drink> Create(int ml) override
    {
        return std::make_unique<Coffee>(ml);
    }
};

class DrinkFactory
{
public:
    DrinkFactory()
    {
        fFactories[EDrinkType::eCocaCola] = std::make_unique<CocaColaFactory>();
        fFactories[EDrinkType::eCoffee] = std::make_unique<CoffeeFactory>();
    }

    std::unique_ptr<Drink> Create(EDrinkType drinkType, int ml)
    {
        return fFactories[drinkType]->Create(ml);
    }

private:
    std::map<EDrinkType, std::unique_ptr<AbstractDrinkFactory>> fFactories;
};

int main()
{
    DrinkFactory factory;
    auto cocaCola   = factory.Create(EDrinkType::eCocaCola, 500);
    auto coffee     = factory.Create(EDrinkType::eCoffee, 50);
       
    cocaCola->Serve();
    coffee->Serve();
}