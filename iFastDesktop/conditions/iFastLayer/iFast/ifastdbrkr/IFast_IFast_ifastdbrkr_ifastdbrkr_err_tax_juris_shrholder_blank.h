#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_tax_juris_shrholder_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_tax_juris_shrholder_blank() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_tax_juris_shrholder_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_TAX_JURIS_SHRHOLDER_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Jurisdiction of Shareholder is blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tax Jurisdiction of Shareholder is blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La champ de juridiction fiscale de l'actionnaire est vide.")); }

        // Actions
	};
}



