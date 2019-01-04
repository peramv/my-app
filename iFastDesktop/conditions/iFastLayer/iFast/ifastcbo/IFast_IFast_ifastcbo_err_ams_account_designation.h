﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_account_designation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_account_designation() { }
		~CIFast_IFast_ifastcbo_err_ams_account_designation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_ACCOUNT_DESIGNATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 1; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The account designation has not been set up for the AMS portfolio.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The account designation has not been set up for the AMS portfolio.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The account designation has not been set up for the AMS portfolio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La désignation du compte n'a pas été réglée pour le portefeuille de service de gestion de portefeuille.")); }

        // Actions
	};
}



