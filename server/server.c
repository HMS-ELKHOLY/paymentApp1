#include"server.h"
#include <string.h>
ST_accountsDB_t accountsDB[255] = { 
	{2000,RUNNING,"1234567891234567891"},
	{2000,BLOCKED,"2214569891234567894"},
};
uint8_t* transStateVal[] = { "APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR" };
ST_transaction_t transactionDB[255] = { 0 };
uint8_t trnscDbIndex=-1;
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	uint8_t accountFound=0;
	
	int i = 0;
	for (i=0; i < 255; i++) {
		if (isValidAccount(&transData->cardHolderData, &accountsDB[i]) == SERVER_OK)
			accountFound = 1;
			break;
	}
	if (accountFound == 0)
		return FRAUD_CARD;
	else
	{
		if (LOW_BALANCE == isAmountAvailable(&(transData->terminalData), &accountsDB[i]))
			return DECLINED_INSUFFECIENT_FUND;
		else if(BLOCKED_ACCOUNT==isBlockedAccount((accountsDB+i)))
		{
			return DECLINED_STOLEN_CARD;

			if (SAVING_FAILED == saveTransaction(transData))
				return INTERNAL_SERVER_ERROR;

		}
	}
	return APPROVED;
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {

	
	if (accountRefrence != NULL) {
		if (0 == strcmp(cardData->primaryAccountNumber, accountRefrence->primaryAccountNumber)) {
			//puts("YYY");
			return SERVER_OK;


		}
		puts(cardData->primaryAccountNumber);
		puts(accountRefrence->primaryAccountNumber);
	}
	return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence){
	if (accountRefrence->state == BLOCKED)
		return BLOCKED_ACCOUNT;
	return SERVER_OK;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence){
	if (accountRefrence->balance < termData->transAmount)
		return  LOW_BALANCE;
	return SERVER_OK;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData){

	if ((trnscDbIndex) == 255)
		return SAVING_FAILED;


	trnscDbIndex++;

	transactionDB[trnscDbIndex].cardHolderData = transData->cardHolderData;
	transactionDB[trnscDbIndex].terminalData = transData->terminalData;
	transactionDB[trnscDbIndex].transactionSequenceNumber +=1;
	
	
	return SERVER_OK;
}
void listSavedTransactions(void) {
	
	for (int i = 0; i < trnscDbIndex; i++)
	{
		printf("#########################");
		printf("Transaction Sequence Number: %d", transactionDB[trnscDbIndex].transactionSequenceNumber );
		printf("Transaction Date:%s", transactionDB[trnscDbIndex].terminalData.transactionDate);
		printf("Transaction Amount:%f", transactionDB[trnscDbIndex].terminalData.transAmount);
		printf("Transaction State:%s",transStateVal[ transactionDB[trnscDbIndex].transState]);
		printf("Transaction Max Amount::%f", transactionDB[trnscDbIndex].terminalData.maxTransAmount);
		printf("Cardholder Name:%s", transactionDB[trnscDbIndex].cardHolderData.cardHolderName);
		printf("PAN:%s", transactionDB[trnscDbIndex].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s", transactionDB[trnscDbIndex].cardHolderData.cardExpirationDate);
		printf("#########################");



	}

}
/**************************/
//testing
/**********************/
//is valid account
void isBlockedAccountTest(void)
{
	ST_accountsDB_t account1;
	account1.state = BLOCKED;
	ST_accountsDB_t account2;
	account2.state = RUNNING;
	uint8_t* serverState[] = { "SERVER_OK", "SAVING_FAILED", "TRANSACTION_NOT_FOUND", "ACCOUNT_NOT_FOUND", "LOW_BALANCE"," BLOCKED_ACCOUNT" };


		puts("#############################################################");
		printf("test case %d\n", 1);
		printf("tester hussien\n");
		printf("testing function isBlockedAccount \n");
		printf("Input Data : by tester\n");
		printf("If the account is running it will return SERVER_OK, else if the account is blocked it will return BLOCKED_ACCOUNT.\n");
		printf("Actual Result :");

		puts(serverState[isBlockedAccount(&account1)]);
		puts("#############################################################");

		puts("#############################################################");
		printf("test case %d\n", 2);
		printf("tester hussien\n");
		printf("testing function isBlockedAccount \n");
		printf("Input Data : by tester\n");
		printf("If the account is running it will return SERVER_OK, else if the account is blocked it will return BLOCKED_ACCOUNT.\n");
		printf("Actual Result :");

		puts(serverState[isBlockedAccount(&account2)]);
		puts("#############################################################");

}

 