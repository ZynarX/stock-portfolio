#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "stock.hpp"
#pragma once

class Portfolio
{
private:
    std::string name;
    std::vector<Stock> stocks;
    float cash_balance;

    std::vector<std::string> Split(std::string line, char split);
public:
    Portfolio(std::string Name, float Balance);

    void LoadFromFile(std::string filename);
    void SaveToFile(std::string filename);

    void AddStock(std::string symbol, float price, int shares, std::string date);
    bool RemoveStock(std::string symbol, int shares_to_sell);

    void set_name(std::string name);
    void set_balance(int balance);

    std::string get_name();
    std::vector<Stock> get_stocks();
    float get_balance();
};
