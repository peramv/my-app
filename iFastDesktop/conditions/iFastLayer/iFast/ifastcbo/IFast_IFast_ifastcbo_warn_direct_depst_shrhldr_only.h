#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_direct_depst_shrhldr_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_direct_depst_shrhldr_only() { }
		~CIFast_IFast_ifastcbo_warn_direct_depst_shrhldr_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DIRECT_DEPST_SHRHLDR_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Direct Deposit EFT Banking setup is available only to default banking of non-registered client held account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le réglage bancaire de TEF par dépôt direct n'est disponible que pour l'information bancaire par défaut des comptes non enregistrés détenus pas des clients.")); }

        // Actions
	};
}



