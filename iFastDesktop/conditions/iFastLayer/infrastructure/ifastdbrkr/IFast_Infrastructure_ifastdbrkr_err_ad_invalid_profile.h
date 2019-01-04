﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_ad_invalid_profile : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_ad_invalid_profile() { }
		~CIFast_Infrastructure_ifastdbrkr_err_ad_invalid_profile() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_INVALID_PROFILE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this debit type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this debit type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Lastschriften-Art nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este tipo de débito.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce type de débit.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent dit type debet niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify debit type and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify debit type and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Datum und geben Sie es erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify debit type and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le type de débit et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het type debet en voer dit opnieuw in")); }
	};
}



