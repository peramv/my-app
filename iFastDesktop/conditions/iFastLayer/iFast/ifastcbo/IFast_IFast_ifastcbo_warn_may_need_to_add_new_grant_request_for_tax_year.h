#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_may_need_to_add_new_grant_request_for_tax_year : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_may_need_to_add_new_grant_request_for_tax_year() { }
		~CIFast_IFast_ifastcbo_warn_may_need_to_add_new_grant_request_for_tax_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("May need to add new Grant Request for applicable Tax Year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il pourrait être nécessaire d'ajouter une nouvelle demande de subvention pour l'année d'imposition applicable.")); }

        // Actions
	};
}



