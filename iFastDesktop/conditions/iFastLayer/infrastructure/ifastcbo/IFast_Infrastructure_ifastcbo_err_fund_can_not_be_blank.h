#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_fund_can_not_be_blank : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_fund_can_not_be_blank() { }
		~CIFast_Infrastructure_ifastcbo_err_fund_can_not_be_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CAN_NOT_BE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pointer to object is not valid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Pointer to object is not valid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Zeiger zum Objekt ist nicht gültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Puntero a objeto no es válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pointeur à objet invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Pointer naar object is ongeldig")); }

        // Actions
	};
}



