#include <iostream>
#include <vector>
#include <string>
#pragma once

class Stock
{
private:
    std::string symbol;
    float buy_price;
    int shares;
    std::string purchase_date;
    float value;
public:
    Stock(std::string Symbol, float BuyPrice, int Shares, std::string PurchaseDate);

    std::string get_symbol();
    float get_price();
    int get_shares();
    std::string get_date();
    float get_value();

    void add_shares(int amount);

    void remove_shares(int shares_to_remove);
};
