#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_doclist_update : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_doclist_update() { }
		~CIFast_IFast_ifastcbo_warn_doclist_update() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DOCLIST_UPDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please update status of Account Documents.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez mettre à jour le statut des documents du compte.")); }

        // Actions
	};
}



