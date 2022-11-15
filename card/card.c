#include "card.h"

 


/**Implement getCardHolderName function*/


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	uint8_t crdHldrName[1000];
	puts("kindly enter cardholder name ");
	gets_s(crdHldrName, 999);
	uint8_t lenName = strlen(crdHldrName);
	puts(crdHldrName);
	puts(crdHldrName);
	puts(crdHldrName);
	if (20 > lenName || 24 < lenName || crdHldrName == NULL)
		return WRONG_NAME;
	else
	{
		for (int i = 0; i++; i < 25)
			cardData->cardHolderName[i] = crdHldrName[i];

		

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
		for (int i = 0; i++; i < 6)
			cardData->cardExpirationDate[i] = crdExpDate[i];

		

		return CARD_OK;
	}

}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {


	uint8_t crdPAN[1000];
	puts("kindly enter expiry date   ");
	gets_s(crdPAN, 999);
	uint8_t lencrdPAN = strlen(crdPAN);
	
	if (16 > lencrdPAN || 19 < lencrdPAN || crdPAN == NULL )
		return WRONG_PAN;
	else
	{
		for (int i = 0; i++; i < 16)
			cardData->primaryAccountNumber[i] = crdPAN[i];



		return CARD_OK;
	}
}


