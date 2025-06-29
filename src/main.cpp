#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../include/stock.hpp"
#include "../include/portfolio.hpp"

#define FILE_PATH "data.csv"
constexpr size_t MIN_SIZE = 1;

Portfolio currentPortfolio("", 0);

std::vector<std::string> Split(std::string line, char split)
{
    std::vector<std::string> output = {};

    std::string string;

    for(int i = 0; i < line.length(); i++)
    {
        if(line[i] != split)
        {
            string += line[i];
        }
        else
        {
            output.push_back(string);
            string = "";
        }
    }

    output.push_back(string);

    return output;
}

void LoadData();
void ViewPortfolio();
void BuyStock();
void SellStock();
void SaveData();

int main()
{
    std::string name = "";
    float balance = -195736.84f;
    
    std::cout << "Enter your username: ";
    std::getline(std::cin, name);
    
    while(name == "");
    {
        std::cin.ignore();
        std::cout << "Enter your username: ";
        std::getline(std::cin, name);
    }

    do
    {
        try
        {
            std::cin.ignore();
            std::cout << "Enter account balance: $";
            std::cin >> balance;
        }
        catch(std::exception& e)
        {
            std::cerr << e.what() << '\n';
            balance = -195736.84f;
        }
    } while (balance == -195736.84f);

    currentPortfolio.set_name(name);
    currentPortfolio.set_balance(balance);

    try
    {
        LoadData();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    int option;

    do
    {
        try
        {
            std::cout << "------ STOCK PORTFOLIO ------\n1. View Portfolio\n2. Buy Stocks\n3. Sell Stocks\n4. Save & Exit\n\nChoose an option: ";
            std::cin >> option;

            if(option >= 1 && option <= 4)
            {
                switch(option)
                {
                    case 1:
                        ViewPortfolio();
                        break;
                    case 2:
                        BuyStock();
                        break;
                    case 3:
                        SellStock();
                        break;
                    case 4:
                        std::cout << "Saving...\n";
                        break;
                    default:
                        std::cout << "\nInvalid option!\n\n";
                        break;
                }
            }
            else
            {
                std::cout << "\nInvalid option!\n\n";
            }
        }
        catch(std::exception& e)
        {
            std::cout << "\nPlease enter a valid number!\n\n";
        }
    } while(option != 4);

    try
    {
        SaveData();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

void LoadData()
{
    currentPortfolio.LoadFromFile(FILE_PATH);
}

void ViewPortfolio()
{
    std::vector<Stock> stocks = currentPortfolio.get_stocks();

    if(stocks.size() >= MIN_SIZE)
    {
        int total_shares = 0;
        float total_price = 0.0f;
        float total_value = 0.0f;

        std::cout << "---- " << currentPortfolio.get_name() << "'s Portfolio ---- Cur. Balance: $" << std::to_string(currentPortfolio.get_balance()) << '\n';

        for(Stock curStock : stocks)
        {
            std::string stockSymbol = curStock.get_symbol();
            float stockPrice = curStock.get_price();
            int stockShares = curStock.get_shares();
            float stockValue = curStock.get_value();
            std::string stockDate = curStock.get_date();

            total_shares += stockShares;
            total_price += stockPrice;
            total_value += stockValue;

            std::cout << "-------------------------------------------- " << stockDate << " ---\n";

            std::cout << stockSymbol << " - Shares: " << std::to_string(stockShares) 
                      << "   Avg Price: $" << std::to_string(stockPrice) << "   Current: $" << std::to_string(stockPrice * stockShares)
                      << "   P/L: $" << std::to_string(stockValue) << std::endl;
        }

        std::cout << "-----------------------------------------------------------\n";

        std::cout << "ALL - Shares: " << std::to_string(total_shares) << "   Price: $" << std::to_string(total_price)
                  << "    Total: $" << std::to_string(total_price * total_shares) << "   P/L: $" << std::to_string(total_value) << std::endl;

        std::cout << "--- THE END ----------------------------------------------\n";
    }
}

void BuyStock()
{
    std::string stockSymbol = "";
    float stockPrice = -195736.84f;
    int stockShares = -1;
    std::string stockDate = "";

    do
    {
        std::cin.ignore();
        std::cout << "---- Buy Stock ----\n- Stock Symbol: ";
        std::getline(std::cin, stockSymbol);
    } while(stockSymbol == "");

    do
    {
        try
        {
            std::cin.ignore();
            std::cout << "- Stock Price: $";
            std::cin >> stockPrice;

            if(stockPrice <= 0)
            {
                stockPrice = -1.0f;
            }
        }
        catch(std::exception& e)
        {
            std::cerr << e.what() << '\n';
            stockPrice = -1.0f;
        }
    } while (stockPrice == -1.0f);

    do
    {
        try
        {
            std::cin.ignore();
            std::cout << "- Stock Shares: ";
            std::cin >> stockShares;

            if (stockShares <= 0)
            {
                stockShares = -1;
            }
            
        }
        catch(std::exception& e)
        {
            std::cerr << e.what() << '\n';
            stockShares = -1;
        }
    } while (stockPrice == -1);

    do
    {
        std::cin.ignore();

        std::cout << "- Stock Buy Date (DD/MM/YYYY): ";
        std::getline(std::cin, stockDate);

        size_t DATE_SIZE = 3;

        if(Split(stockDate, '/').size() != DATE_SIZE)
        {
            stockDate = "";
        }
    } while (stockDate == "");
    

    currentPortfolio.AddStock(stockSymbol, stockPrice, stockShares, stockDate);
}

void SellStock()
{
    std::string symbol = "";
    int shares = -1;

    do
    {
        std::cin.ignore();
        std::cout << "---- Sell Stock ----\n- Stock Symbol: ";
        std::getline(std::cin, symbol);
    } while (symbol == "");
    
    do
    {
        try
        {
            std::cin.ignore();
            std::cout << "- Shares to Sell: ";
            std::cin >> shares;

            if (shares < 0)
            {
                shares = -1;
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';
            shares = -1;
        }
    } while (shares == -1);

    bool result = currentPortfolio.RemoveStock(symbol, shares);

    if(!result)
    {
        std::cout << "Couldn't sell shares from specified symbol!\n";
    }
}

void SaveData()
{
    currentPortfolio.SaveToFile(FILE_PATH);
}
