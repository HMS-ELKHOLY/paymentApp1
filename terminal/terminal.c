#include"terminal.h"
#include "..\card\card.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData){

	uint8_t trscnDate[1000];
	puts("kindly enter transction date ");
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
		for (int i = 0; i < 11; i++)
			termData->transactionDate[i] = trscnDate[i];



		return TERMINAL_OK;
	}
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	uint8_t chkMnth = ((cardData->cardExpirationDate[0] - termData->transactionDate[3]) >= 0 && (cardData->cardExpirationDate[1] - termData->transactionDate[4]) >= 0);
	uint8_t chkYear = ((cardData->cardExpirationDate[3] - termData->transactionDate[8]) >= 0 && (cardData->cardExpirationDate[4] - termData->transactionDate[9]) >= 0);

	if (chkMnth!=0 && chkYear!=0)
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
	puts("enter amount");
	gets_s(TransactionAmount, 19);
	termData->transAmount=strtof(TransactionAmount,NULL);
	if (termData->transAmount <=0)
		return INVALID_AMOUNT;
	else
		return TERMINAL_OK;

	 

} 

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	uint8_t maxAmount[20];
	gets_s(maxAmount, 19);
	termData->maxTransAmount= strtof(maxAmount,NULL);
	if ( termData->maxTransAmount<=0)
		return INVALID_MAX_AMOUNT;
	else
		return TERMINAL_OK;



}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	return TERMINAL_OK;

}

/***********Testing****************/

/*getTransactionDateTest*/
void getTransactionDateTest(void)
{	
	uint8_t* terminalState[] = { "TERMINAL_OK", "WRONG_DATE", "EXPIRED_CARD", "INVALID_CARD", "INVALID_AMOUNT", "EXCEED_MAX_AMOUNT", "INVALID_MAX_AMOUNT" };

	ST_terminalData_t  terminalData;
	for (int i = 0; i < 3; i++) {

		puts("#############################################################");
		printf("test case %d\n", i);
		printf("tester hussien\n");
		printf("testing function getCardHolderName\n");
		printf("Input Data : by tester\n");
		printf("Expected Result : if the transaction date is NULL or is less than 10 characters or wrong format will return the WRONG_DATE error, else return TERMINAL_OK.\n");
		printf("Actual Result :");

		puts(terminalState[getTransactionDate(&terminalData)]);
		puts("#############################################################");
	}

}
/*isCardExpired test*/
void isCardExpiredTest(void) {
	/**test cases goes here*********************/


	/**make sure here*******************************/
}
void getTransactionAmountTest(void) {

	uint8_t* terminalState[] = { "TERMINAL_OK", "WRONG_DATE", "EXPIRED_CARD", "INVALID_CARD", "INVALID_AMOUNT", "EXCEED_MAX_AMOUNT", "INVALID_MAX_AMOUNT" };

	ST_terminalData_t  terminalData;
	for (int i = 0; i < 6; i++) {

		puts("#############################################################");
		printf("test case %d\n", i);
		printf("tester hussien\n");
		printf("testing function getTransactionAmount\n");
		printf("Input Data : by tester\n");
		printf("Expected Result : If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return TERMINAL_OK.\n");
		printf("Actual Result :");

		puts(terminalState[getTransactionAmount(&terminalData)]);
		puts("#############################################################");
	}


}

/*isBelowMaxAmountTEST*****/

void isBelowMaxAmountTest(void) {

	uint8_t* terminalState[] = { "TERMINAL_OK", "WRONG_DATE", "EXPIRED_CARD", "INVALID_CARD", "INVALID_AMOUNT", "EXCEED_MAX_AMOUNT", "INVALID_MAX_AMOUNT" };
	
	ST_terminalData_t  terminalDataArray[3];
	terminalDataArray[0].transAmount = 1000;
	terminalDataArray[0].maxTransAmount = 2000;
	terminalDataArray[1].transAmount = 1000;
	terminalDataArray[1].maxTransAmount = 1000;
	terminalDataArray[2].transAmount = 4000;
	terminalDataArray[2].maxTransAmount = 2000;
	
	uint8_t* terminalStateEXpected[3] = { TERMINAL_OK ,TERMINAL_OK ,EXCEED_MAX_AMOUNT };
	for (int i = 0; i < 3; i++) {

		puts("#############################################################");
		printf("test case %d\n", i);
		printf("tester hussien\n");
		printf("testing function isBelowMaxAmountTest\n");
		printf("Input Data :tans amount %f max trans amount %f \n", terminalDataArray[i].transAmount,terminalDataArray[i].maxTransAmount);
		printf("Expected Result : If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return TERMINAL_OK.\n");
		uint8_t index = terminalStateEXpected[i];
		printf("Expected Result for this case : %s.\n", terminalState[index]);

		printf("Actual Result :");

		puts(terminalState[isBelowMaxAmount(&terminalDataArray[i])]);
		puts("#############################################################");
	}


}
/*****************setMaxAmount****************/
void setMaxAmountTest(void) {

	uint8_t* terminalState[] = { "TERMINAL_OK", "WRONG_DATE", "EXPIRED_CARD", "INVALID_CARD", "INVALID_AMOUNT", "EXCEED_MAX_AMOUNT", "INVALID_MAX_AMOUNT" };

	ST_terminalData_t  terminalData ;
	for (int i = 0; i < 4; i++) {

		puts("#############################################################");
		printf("test case %d\n", i);
		printf("tester hussien\n");
		printf("testing function setMaxAmountTest \n");

		printf("If transaction max amount less than or equal to 0 will return the INVALID_MAX_AMOUNT error, else return TERMINAL_OK.\n");
		printf("Input Data by tester");
		printf("Expected Result : If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return TERMINAL_OK.\n");
		
		printf("Actual Result :");

		puts(terminalState[setMaxAmount(&terminalData)]);
		puts("#############################################################");
	}


}