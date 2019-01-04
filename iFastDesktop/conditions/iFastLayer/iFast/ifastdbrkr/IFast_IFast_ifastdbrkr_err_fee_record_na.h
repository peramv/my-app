#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fee_record_na : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fee_record_na() { }
		~CIFast_IFast_ifastdbrkr_err_fee_record_na() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_RECORD_NA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee record not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fee record not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provisionseintrag nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de comisiones no está disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement des frais n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kostenrecord is niet beschikbaar")); }

        // Actions
	};
}



