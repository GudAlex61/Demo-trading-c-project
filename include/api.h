#pragma once
#include "MakingAPosition.h"

double getCryptoPrice(const std::string& cryptoId);
bool checkLiquidation(Position& position);
double estimateLiquidation(Position& position);
