#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_regulatory_doc_status_needs_to_be_manually_updated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_regulatory_doc_status_needs_to_be_manually_updated() { }
		~CIFast_IFast_ifastcbo_warn_regulatory_doc_status_needs_to_be_manually_updated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REGULATORY_DOC_STATUS_NEEDS_TO_BE_MANUALLY_UPDATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Regulatory Document status may need to be manually updated.")); }

        // Actions
	};
}



