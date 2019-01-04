#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_bank_record_should : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_bank_record_should() { }
		~CIFast_IFast_ifastdbrkr_err_bank_record_should() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANK_RECORD_SHOULD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank record should be a distribution to cash and paytype should be E,W,F or T.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Bank record should be a distribution to cash and paytype should be E,W,F or T.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bankeintrag sollte eine Verteilung an Bargeld sein und Zahlungsart sollte E,W,F oder T sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de banco debe ser una distribución a efectivo y el tipo de pago debe ser E,W,F o T.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement bancaire devrait être une distribution en argent et le type de paiement devrait être E, W, F ou T.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bankrecord moet een distributie voor contant zijn en het betalingstype moet E,W,F of T zijn")); }

        // Actions
	};
}



