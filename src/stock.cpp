#include <iostream>
#include <string>
#include <vector>
#include "../include/stock.hpp"

Stock::Stock(std::string Symbol, float BuyPrice, int Shares, std::string PurchaseDate)
{
    this->symbol = Symbol;
    this->buy_price = BuyPrice;
    this->shares = Shares;
    this->purchase_date = PurchaseDate;

    this->value = this->buy_price * this->shares;
}

std::string Stock::get_symbol()
{
    return this->symbol;
}

float Stock::get_price()
{
    return this->buy_price;
}

int Stock::get_shares()
{
    return this->shares;
}

void Stock::add_shares(int amount)
{
    this->shares += amount;
}

std::string Stock::get_date()
{
    return this->purchase_date;
}

float Stock::get_value()
{
    return this->value;
}

void Stock::remove_shares(int shares_to_remove)
{
    this->shares -= shares_to_remove;
}
