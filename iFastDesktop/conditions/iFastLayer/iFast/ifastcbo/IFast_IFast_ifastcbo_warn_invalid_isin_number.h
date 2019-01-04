﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_invalid_isin_number : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_invalid_isin_number() { }
		~CIFast_IFast_ifastcbo_warn_invalid_isin_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_ISIN_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("ISIN number does not exist, please select an existing one or leave it blank and select a fund and class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("ISIN number does not exist, please select an existing one or leave it blank and select a fund and class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro ISIN inexistant, veuillez sélectionner un numéro existant ou laisser ce champ vide et sélectionner un fonds et une classe.")); }

        // Actions
	};
}



