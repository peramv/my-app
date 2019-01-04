#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_status_may_need_to_flip_or_new_request_may_be_required_for_tax_year : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_status_may_need_to_flip_or_new_request_may_be_required_for_tax_year() { }
		~CIFast_IFast_ifastcbo_err_status_may_need_to_flip_or_new_request_may_be_required_for_tax_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STATUS_MAY_NEED_TO_FLIP_OR_NEW_REQUEST_MAY_BE_REQUIRED_FOR_TAX_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("May need to flip status to Request or create new request for applicable Tax Year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il pourrait être nécessaire de changer le statut pour Demande ou de créer une nouvelle demande pour l'année d'imposition applicable.")); }

        // Actions
	};
}



