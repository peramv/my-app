#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_cash_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_cash_date() { }
		~CIFast_IFast_ifastcbo_err_invalid_cash_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CASH_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid cash date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Einlösedatum")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de efectivo no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date d'encaissement invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige contantdatum")); }

        // Actions
	};
}



