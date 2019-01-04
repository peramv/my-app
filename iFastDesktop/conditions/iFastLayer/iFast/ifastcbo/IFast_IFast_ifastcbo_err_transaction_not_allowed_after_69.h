#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transaction_not_allowed_after_69 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transaction_not_allowed_after_69() { }
		~CIFast_IFast_ifastcbo_err_transaction_not_allowed_after_69() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSACTION_NOT_ALLOWED_AFTER_69")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction cannot be processed after age 71.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktion darf nach dem Alter von 71 nicht weiterverarbeitet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La transacción no puede procesarse después de los 71 años")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction ne peut être traitée après l'âge de 71 ans.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Transactie kan niet meer worden verwerkt na de leeftijd van 71")); }

        // Actions
	};
}



