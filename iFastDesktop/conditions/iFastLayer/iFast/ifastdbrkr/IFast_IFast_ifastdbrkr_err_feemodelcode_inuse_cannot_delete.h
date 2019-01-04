#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_feemodelcode_inuse_cannot_delete : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_feemodelcode_inuse_cannot_delete() { }
		~CIFast_IFast_ifastdbrkr_err_feemodelcode_inuse_cannot_delete() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEEMODELCODE_INUSE_CANNOT_DELETE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FeeModelCode is in use by FundSponsor, Account or Shareholder - cannot delete")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FeeModelCode is in use by FundSponsor, Account or Shareholder - cannot delete")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de modèle de frais est en cours d'utilisation par le promoteur de fonds, le compte ou l'actionnaire – suppression impossible.")); }

        // Actions
	};
}



