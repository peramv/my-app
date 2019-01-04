﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_pd_three_of_same_chars_not_allowed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_pd_three_of_same_chars_not_allowed() { }
		~CIFast_Infrastructure_ifastdbrkr_err_pd_three_of_same_chars_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_THREE_OF_SAME_CHARS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this fiduciary account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this fiduciary account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt dieses Treuhänder-Konto nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce esta cuenta fiduciaria.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce compte fiduciaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent dit fiduciaire account niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify account and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify account and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Konto und geben Sie es erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify account and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le compte et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de account en voer deze opnieuw in")); }
	};
}



