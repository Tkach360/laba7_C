#pragma once
class AbstractBankService
{
public:
	virtual double getInterestAmount() = 0;

	virtual int getYears() = 0;
	virtual double getBody() = 0;
	virtual double getPercent() = 0;

};

