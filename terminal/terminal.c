#include"terminal.h"
#include "..\card\card.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData){

	uint8_t trscnDate[1000];
	puts("kindly enter cardholder name ");
	gets_s(trscnDate, 999);
	uint8_t lentrscnDate = strlen(trscnDate);
	uint8_t chkFormat =0 ;
	if (lentrscnDate == 10) {
		uint8_t chkDay = trscnDate[0] >= '0' && trscnDate[0] <= '9' && trscnDate[1] >= '0' && trscnDate[1] <= '9';
		uint8_t chkMonth = trscnDate[3] >= '0' && trscnDate[3] <= '9' && trscnDate[4] >= '0' && trscnDate[4] <= '9';
		uint8_t chkYear = trscnDate[6] >= '0' && trscnDate[6] <= '9' && trscnDate[7] >= '0' && trscnDate[7] <= '9' && trscnDate[8] >= '0' && trscnDate[8] <= '9' && trscnDate[9] >= '0' && trscnDate[9] <= '9';
		uint8_t chkSep = trscnDate[2] == '/' && trscnDate[5] == '/';
		chkFormat = chkDay && chkMonth && chkSep;
	}
	if (10 > lentrscnDate  || trscnDate == NULL && chkFormat ==0)
		return WRONG_DATE;
	else
	{
		for (int i = 0; i++; i < 11 )
			termData->transactionDate[i] = trscnDate[i];



		return TERMINAL_OK;
	}
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	if ((cardData->cardExpirationDate[0] - termData->transactionDate[3]) > 0 && (cardData->cardExpirationDate[1] - termData->transactionDate[4]) > 0)
	{
		return TERMINAL_OK;



	}
	else
	{
		return EXPIRED_CARD;
	}

}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	uint8_t TransactionAmount[20];
	gets_s(TransactionAmount, 19);
	termData->transAmount=strtof(TransactionAmount);
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	else
		return TERMINAL_OK;

	 

} 

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	uint8_t maxAmount[20];
	gets_s(maxAmount, 19);
	termData->transAmount = strtof(maxAmount);
	if ( termData->maxTransAmount<=0)
		return INVALID_MAX_AMOUNT;
	else
		return TERMINAL_OK;



}