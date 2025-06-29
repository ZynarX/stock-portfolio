#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/portfolio.hpp"

Portfolio::Portfolio(std::string Name, float Balance)
{
    this->name = Name;
    this->cash_balance = Balance;
}

std::vector<std::string> Portfolio::Split(std::string line, char split)
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

void Portfolio::LoadFromFile(std::string filename)
{
    std::ifstream fileContent;
    fileContent.open(filename);

    std::vector<std::string> lines;

    if(fileContent.is_open())
    {
        std::string line;

        while(std::getline(fileContent, line))
        {
            lines.push_back(line);
        }

        fileContent.close();
    }
    else
    {
        std::cout << "Couldn't open file!";
    }

    for(std::string line : lines)
    {

        std::vector<std::string> data = this->Split(line, ',');

        std::string symbol;
        float price;
        int shares;
        std::string purchase_date;

        try
        {
            symbol = data[0];
            price = std::stof(data[1]);
            shares = std::stoi(data[2]);
            purchase_date = data[3];

            Stock curStock(symbol, price, shares, purchase_date);
            this->stocks.push_back(curStock);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
void Portfolio::SaveToFile(std::string filename)
{
    std::ofstream outputFile;
    outputFile.open(filename, std::ios::out | std::ios::trunc);

    if(outputFile.is_open())
    {
        for(Stock curStock : this->stocks)
        {
            std::string symbol = curStock.get_symbol();
            float price = curStock.get_price();
            int shares = curStock.get_shares();
            std::string date = curStock.get_date();
            float value = curStock.get_value();

            outputFile << symbol << "," << std::to_string(price) << "," << std::to_string(shares) << "," << date << "," << std::to_string(value) << '\n';
        }
    }
}

void Portfolio::AddStock(std::string symbol, float price, int shares, std::string date)
{

    for(Stock& curStock : this->stocks)
    {
        if (curStock.get_symbol() == symbol)
        {
            curStock.add_shares(shares);

            return;
        }
    }

    Stock newStock(symbol, price, shares, date);
    this->stocks.push_back(newStock);
}
bool Portfolio::RemoveStock(std::string symbol, int shares_to_sell)
{
    Stock* stock = nullptr;

    for(Stock curStock : this->stocks)
    {
        if(curStock.get_symbol() == symbol)
        {
            stock = &curStock;
        }
    }

    try
    {
        if(stock->get_shares() >= shares_to_sell)
        {
            stock->remove_shares(shares_to_sell);
            this->cash_balance += shares_to_sell * stock->get_price();

            return true;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
    return false;
}
void Portfolio::UpdateMarketPrice(Stock* stock, float new_price)
{

}

void Portfolio::set_name(std::string name)
{
    this->name = name;
}
void Portfolio::set_balance(int balance)
{
    this->cash_balance = balance;
}

std::string Portfolio::get_name()
{
    return this->name;
}
std::vector<Stock> Portfolio::get_stocks()
{
    return this->stocks;
}
float Portfolio::get_balance()
{
    return this->cash_balance;
}
