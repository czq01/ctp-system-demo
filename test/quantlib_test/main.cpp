#include <iostream>
#include <ql/quantlib.hpp>
#include <boost/shared_ptr.hpp>

int main(int, char* [])
{
    QuantLib::Calendar calendar = QuantLib::TARGET();
    QuantLib::Date todaysDate(6, QuantLib::December, 2018);
    QuantLib::Date settlementDate(6, QuantLib::December, 2018);
    QuantLib::Date maturity(6, QuantLib::December, 2018);

    QuantLib::Option::Type OptionType(QuantLib::Option::Call);
    QuantLib::Real stock = 100.00;
    QuantLib::Real strike = 90.00;
    QuantLib::Spread dividendYield = 0.00;
    QuantLib::Rate riskFreeRate = 0.05;
    QuantLib::Volatility volatility = 0.20;

    std::cout << "Option Start Date = " << todaysDate << std::endl;
    std::cout << "Option Settlement Date = " << settlementDate << std::endl;
    std::cout << "Option Maturity Date = " << maturity << std::endl;
    std::cout << "Option Type = " << OptionType << std::endl;
    std::cout << "Stock Price = " << stock << std::endl;
    std::cout << "Strike Price = " << strike << std::endl;
    std::cout << "Risk Free Rate" << riskFreeRate << std::endl;
    std::cout << "Dividend Yield = " << dividendYield << std::endl;
    std::cout << "Volatility = " << volatility << std::endl;

    boost::shared_ptr<QuantLib::Exercise> europeanExercise(new QuantLib::EuropeanExercise(maturity));
    boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(new QuantLib::PlainVanillaPayoff(OptionType, strike));
    QuantLib::VanillaOption europeanOption(payoff, europeanExercise);
    std::cout << "Price = " << europeanOption.NPV() << std::endl;

    return 0;
}