#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_review_sages_application_due_to_tax_jurisdiction_changes : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_review_sages_application_due_to_tax_jurisdiction_changes() { }
		~CIFast_IFast_ifastcbo_warn_review_sages_application_due_to_tax_jurisdiction_changes() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REVIEW_SAGES_APPLICATION_DUE_TO_TAX_JURISDICTION_CHANGES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Review SAGES Application due to Tax Jurisdiction changes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez revoir la demande de SEEAS en raison de changements de juridiction fiscale.")); }

        // Actions
	};
}



