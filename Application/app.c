#include "app.h"
void appStart(void) {

	/********************__card__*****************************/
	ST_cardData_t Card;
	EN_cardError_t CardHolderName_ErrorState = getCardHolderName(&Card);
	if (WRONG_NAME == CardHolderName_ErrorState)
	{
		puts("WRONG_NAME");
		return;
	}
	EN_cardError_t CardPAN_ErrorState = getCardPAN(&Card);
	if (WRONG_PAN == CardPAN_ErrorState)
	{
		puts("WRONG_PAN");
		return;
	}

	EN_cardError_t CardExpDate_ErrorState = getCardExpiryDate(&Card);
	if (WRONG_EXP_DATE == CardExpDate_ErrorState)
	{
		puts("WRONG_EXP_DATE");
		return;
	}


	/********************__terminal__*****************************/
	ST_terminalData_t terminal;
	EN_terminalError_t DateErrorState = getTransactionDate(&terminal);
	if (WRONG_DATE == DateErrorState)
	{
		puts("worng date");
		return;

	}
	if (EXPIRED_CARD == isCardExpired(&Card, &terminal))
	{
		puts("EXPIRED_CARD");
		return;
	}
	puts("ok");
	if (INVALID_AMOUNT == getTransactionAmount(&terminal))
	{
		puts("INVALID_AMOUNT");
		return;
	}
	if (INVALID_MAX_AMOUNT == setMaxAmount(&terminal))
	{
		puts("INVALID_MAX_AMOUNT");
		return;
	}
	if (EXCEED_MAX_AMOUNT == isBelowMaxAmount(&terminal))
	{
		puts("EXCEED_MAX_AMOUNT");
		return;
	}

	ST_transaction_t transData;
	transData.cardHolderData = Card;
	transData.terminalData = terminal;
	EN_transState_t transDataState = recieveTransactionData(&transData);
	if (APPROVED != transDataState)
	{
		puts(transStateVal[transDataState]);
		return;
	}

	puts("Success");
	return;



}