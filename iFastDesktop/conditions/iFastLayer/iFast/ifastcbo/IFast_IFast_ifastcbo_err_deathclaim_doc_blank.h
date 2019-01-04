#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deathclaim_doc_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deathclaim_doc_blank() { }
		~CIFast_IFast_ifastcbo_err_deathclaim_doc_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEATHCLAIM_DOC_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("One or more death claim documents have status blank. Please update status.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut d'un ou plusieurs des documents de sinistre-décès est manquant. Veuillez mettre à jour ce statut.")); }

        // Actions
	};
}



