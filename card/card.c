#include "card.h"

 


/**Implement getCardHolderName function*/


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	uint8_t crdHldrName[1000];
	puts("kindly enter cardholder name ");
	gets_s(crdHldrName, 999);
	uint8_t lenName = strlen(crdHldrName);
	
	if (20 > lenName || 24 < lenName || crdHldrName == NULL)
		return WRONG_NAME;
	else
	{
		for (int i = 0; i<25; i++)
			cardData->cardHolderName[i] = crdHldrName[i];

		
	//	puts(cardData->cardHolderName);
		return CARD_OK;
	}
	
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {


	uint8_t crdExpDate[1000];
	puts("kindly enter expiry date   ");
	gets_s(crdExpDate, 999);
	uint8_t lenDate = strlen(crdExpDate);
	uint8_t validFormat=0;
	if ((crdExpDate[0] >= '0' && crdExpDate[0] <= '9') && (crdExpDate[1] >= '0' && crdExpDate[1] <= '9') && (crdExpDate[3] >= '0' && crdExpDate[3] <= '9') && (crdExpDate[4] >= '0' && crdExpDate[4] <= '9') && crdExpDate[2] == '/')
		validFormat = 1;
	if (5 > lenDate || 5 < lenDate || crdExpDate == NULL || validFormat==0)
		return WRONG_EXP_DATE;
	else
	{
		for (int i = 0; i<6; i ++)
			cardData->cardExpirationDate[i] = crdExpDate[i];

		

		return CARD_OK;
	}

}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {


	uint8_t crdPAN[1000];
	puts("kindly PAN   ");
	gets_s(crdPAN, 999);
	uint8_t lencrdPAN = strlen(crdPAN);
	
	if (16 > lencrdPAN || 19 < lencrdPAN || crdPAN == NULL )
		return WRONG_PAN;
	else
	{
		for (int i = 0; i<20; i ++)
			cardData->primaryAccountNumber[i] = crdPAN[i];

		puts(crdPAN);
		puts(cardData->primaryAccountNumber);
		return CARD_OK;
	}
}


/*TESTING*****************************************************/



void getCardHolderNameTest(void) {
	ST_cardData_t  cardData;
	for (int i = 0; i < 3; i++) {

		puts("#############################################################");
		printf("test case %d\n", i);
		printf("tester hussien\n");
		printf("testing function getCardHolderName\n");
		printf("Input Data : by tester\n");
		printf("Expected Result : worong name if 20 > lenName || 24 < lenName || crdHldrName == NULL\n card ok otherwise\n");
		uint8_t* cardState[] = { "CARD_OK", "WRONG_NAME", "WRONG_EXP_DATE", "WRONG_PAN" };
		printf("Actual Result :");

		puts(cardState[getCardHolderName(&cardData)]);
		puts("#############################################################");
	}
	
}