﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_shareholerfeemodelcodeisneeded : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_shareholerfeemodelcodeisneeded() { }
		~CIFast_IFast_ifastcbo_warn_shareholerfeemodelcodeisneeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ShareholerFeeModelCodeIsNeeded")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("shareholder fee model code is missing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("shareholder fee model code is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de modèle de frais de l'actionnaire est manquant.")); }

        // Actions
	};
}



