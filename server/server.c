#include"server.h"
#include <string.h>
ST_accountsDB_t accountsDB[255];
uint8_t currentIndexAccDb = -1;
ST_transaction_t transactionDB[255] = { 0 };
uint8_t trnscDbIndex;
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	uint8_t foundAccount = 0;
	for (int i = 0; i < 255; i++) {
		if (0 == strcmp(transData->cardHolderData.primaryAccountNumber, accountsDB[i].primaryAccountNumber)) {
			foundAccount = 1;
			if (currentIndexAccDb == 255)
				return INTERNAL_SERVER_ERROR;
			currentIndexAccDb++;
			if (accountsDB[i].balance < transData->terminalData.transAmount || transData->terminalData.transAmount>transData->terminalData.maxTransAmount)
			{
				return DECLINED_INSUFFECIENT_FUND;
			}
			if (accountsDB[i].state == BLOCKED)
				return DECLINED_STOLEN_CARD;

			accountsDB[i].balance -= transData->terminalData.transAmount;
			transactionDB[currentIndexAccDb]=*transData;
			return APPROVED;
		}
		
	}
	if (foundAccount == 0)
		return FRAUD_CARD;

	return APPROVED;
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {

	
		if (accountRefrence!=NULL)
			if (0 == strcmp(cardData->primaryAccountNumber, accountRefrence->primaryAccountNumber)) {
			
				return SERVER_OK;
			

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


	transactionDB[trnscDbIndex].cardHolderData = transData->cardHolderData;
	transactionDB[trnscDbIndex].terminalData = transData->terminalData;
	transactionDB[trnscDbIndex].transactionSequenceNumber +=1;
	trnscDbIndex++;

	return SERVER_OK;
}
void listSavedTransactions(void) {
	uint8_t* transStateVal[] = { "APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR" };
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

