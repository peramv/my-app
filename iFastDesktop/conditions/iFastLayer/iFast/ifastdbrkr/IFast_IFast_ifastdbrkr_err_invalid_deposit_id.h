#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_deposit_id : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_deposit_id() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_deposit_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_DEPOSIT_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Deposit ID.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Deposit ID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Depot-ID.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Identificación de depósito no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de dépôt invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig deposito-ID")); }

        // Actions
	};
}



