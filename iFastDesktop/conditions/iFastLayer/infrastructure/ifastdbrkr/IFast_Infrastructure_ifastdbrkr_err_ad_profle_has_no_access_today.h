﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_ad_profle_has_no_access_today : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_ad_profle_has_no_access_today() { }
		~CIFast_Infrastructure_ifastdbrkr_err_ad_profle_has_no_access_today() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_PROFLE_HAS_NO_ACCESS_TODAY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Changed by different operator.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Changed by different operator.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Geändert durch einen anderen Operator.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cambiado por otro operador.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Changé par un opérateur différent")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gewijzigd door een andere operator")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



