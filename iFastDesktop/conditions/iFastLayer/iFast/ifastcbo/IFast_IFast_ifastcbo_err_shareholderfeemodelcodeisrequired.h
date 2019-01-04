#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_shareholderfeemodelcodeisrequired : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_shareholderfeemodelcodeisrequired() { }
		~CIFast_IFast_ifastcbo_err_shareholderfeemodelcodeisrequired() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ShareholderFeeModelCodeIsRequired")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder fee model code is missing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Shareholder fee model code is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de modèle de frais de l'actionnaire est manquant.")); }

        // Actions
	};
}



