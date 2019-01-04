#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_required_to_stop_grant_request_for_tax_year : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_required_to_stop_grant_request_for_tax_year() { }
		~CIFast_IFast_ifastcbo_err_required_to_stop_grant_request_for_tax_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REQUIRED_TO_STOP_GRANT_REQUEST_FOR_TAX_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("May need to stop Grant Request for applicable Tax Year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous pourriez devoir arrêter la demande de subvention pour l'année d'imposition applicable.")); }

        // Actions
	};
}



