#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_doc_status_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_doc_status_blank() { }
		~CIFast_IFast_ifastcbo_err_doc_status_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DOC_STATUS_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("One or more documents have blank status. Please update status.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut d'un ou plusieurs des documents est manquant. Veuillez mettre à jour ce statut.")); }

        // Actions
	};
}



