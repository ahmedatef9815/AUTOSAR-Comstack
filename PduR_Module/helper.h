#include "PduR.h"
BufReq_ReturnType Com_StartOfReception (
 PduIdType id,
 const PduInfoType* info,
PduLengthType TpSduLength,
 PduLengthType* bufferSizePtr
);
BufReq_ReturnType Com_CopyRxData (
 PduIdType id,
 const PduInfoType* info,
 PduLengthType* bufferSizePtr
);
BufReq_ReturnType Com_CopyTxData (
 PduIdType id,
 const PduInfoType* info,
 const RetryInfoType* retry,
 PduLengthType* availableDataPtr
);

void Com_TpRxIndication (
 PduIdType id,
 Std_ReturnType result
);

void Com_TpTxConfirmation (
 PduIdType id,
 Std_ReturnType result
);
Std_ReturnType CanTp_Transmit (
PduIdType TxPduId,
const PduInfoType* PduInfoPtr
);


typedef enum {
	TP_DATACONF,
	TP_DATARETRY,
	TP_CONFPENDING
	
}TpDataStateType;
