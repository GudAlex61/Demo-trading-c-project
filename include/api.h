#pragma once
double getCryptoPrice(const std::string& cryptoId);
bool checkLiquidation(Positon& position);
double estimateLiquidation(Positon& position);
